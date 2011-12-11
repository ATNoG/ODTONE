//=============================================================================
// Brief   : MIH User Example
// Authors : Bruno Santos <bsantos@av.it.pt>
//------------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2009-2011 Universidade Aveiro
// Copyright (C) 2009-2011 Instituto de Telecomunicações - Pólo Aveiro
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//==============================================================================

#include <odtone/base.hpp>
#include <odtone/debug.hpp>
#include <odtone/logger.hpp>
#include <odtone/mih/request.hpp>
#include <odtone/mih/response.hpp>
#include <odtone/mih/indication.hpp>
#include <odtone/mih/confirm.hpp>
#include <odtone/mih/tlv_types.hpp>
#include <odtone/sap/user.hpp>
#include <boost/utility.hpp>
#include <boost/bind.hpp>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////

namespace po = boost::program_options;

using odtone::uint;
using odtone::ushort;

odtone::logger log_("mih_usr", std::cout);

///////////////////////////////////////////////////////////////////////////////
/**
 * This class provides an implementation of an IEEE 802.21 MIH-User.
 */
class mih_user : boost::noncopyable {
public:
	/**
	 * Construct the MIH-User.
	 *
	 * @param cfg Configuration options.
	 * @param io The io_service object that the IEEE 802.21 driver will use to
	 * dispatch handlers for any asynchronous operations performed on the socket. 
	 */
	mih_user(const odtone::mih::config& cfg, boost::asio::io_service& io);

	/**
	 * Destruct the MIH-User.
	 */
	~mih_user();

protected:
	/**
	 * User registration handler.
	 *
	 * @param msg Received message.
	 * @param ec Error Code.
	 */
	void user_reg_handler(const odtone::mih::config& cfg, const boost::system::error_code& ec);

	/**
	 * Default MIH event handler.
	 *
	 * @param msg Received message.
	 * @param ec Error code.
	 */
	void event_handler(odtone::mih::message& msg, const boost::system::error_code& ec);

	/**
	 * Capability Discover handler.
	 *
	 * @param msg Received message.
	 * @param ec Error Code.
	 */
	void capability_discover_confirm(odtone::mih::message& msg, const boost::system::error_code& ec);

	/**
	 * Event subscribe handler.
	 *
	 * @param msg Received message.
	 * @param ec Error Code.
	 */
	void event_subscribe_response(odtone::mih::message& msg, const boost::system::error_code& ec);

private:
	odtone::sap::user _mihf;	/**< User SAP helper.		*/
	odtone::mih::id   _mihfid;	/**< MIHF destination ID.	*/
};

/**
 * Construct the MIH-User.
 *
 * @param cfg Configuration options.
 * @param io The io_service object that the IEEE 802.21 driver will use to
 * dispatch handlers for any asynchronous operations performed on the socket. 
 */
mih_user::mih_user(const odtone::mih::config& cfg, boost::asio::io_service& io)
	: _mihf(cfg, io, boost::bind(&mih_user::event_handler, this, _1, _2))
{
	odtone::mih::message m;

	m << odtone::mih::indication(odtone::mih::indication::user_register)
	    & odtone::mih::tlv_mbb_handover_support(true);
	m.destination(odtone::mih::id("local-mihf"));

	_mihf.async_send(m, boost::bind(&mih_user::user_reg_handler, this, boost::cref(cfg), _2));
}

/**
 * Destruct the MIH-User.
 */
mih_user::~mih_user()
{
}

/**
 * User registration handler.
 *
 * @param msg Received message.
 * @param ec Error Code.
 */
void mih_user::user_reg_handler(const odtone::mih::config& cfg, const boost::system::error_code& ec)
{
	log_(0, "MIH-User register result: ", ec.message());

	odtone::mih::message msg;

	odtone::mih::octet_string destination = cfg.get<odtone::mih::octet_string>(odtone::sap::kConf_MIH_SAP_dest);
	_mihfid.assign(destination.c_str());

	//
	// Let's fire a capability discover request to get things moving
	//
	msg << odtone::mih::request(odtone::mih::request::capability_discover, _mihfid);

	_mihf.async_send(msg, boost::bind(&mih_user::capability_discover_confirm, this, _1, _2));

	log_(0, "MIH-User has sent a Capability_Discover.request towards its local MIHF");
}

/**
 * Default MIH event handler.
 *
 * @param msg Received message.
 * @param ec Error code.
 */
void mih_user::event_handler(odtone::mih::message& msg, const boost::system::error_code& ec)
{
	if (ec) {
		log_(0, __FUNCTION__, " error: ", ec.message());
		return;
	}

	switch (msg.mid()) {
	case odtone::mih::indication::link_up:
		log_(0, "MIH-User has received a local event \"link_up\"");
		break;

	case odtone::mih::indication::link_down:
		log_(0, "MIH-User has received a local event \"link_down\"");
		break;

	case odtone::mih::indication::link_detected:
		log_(0, "MIH-User has received a local event \"link_detected\"");
		break;

	case odtone::mih::indication::link_going_down:
		log_(0, "MIH-User has received a local event \"link_going_down\"");
		break;

	case odtone::mih::indication::link_handover_imminent:
		log_(0, "MIH-User has received a local event \"link_handover_imminent\"");
		break;
	case odtone::mih::indication::link_handover_complete:
		log_(0, "MIH-User has received a local event \"link_handover_complete\"");
		break;
	}
}

/**
 * Capability Discover handler.
 *
 * @param msg Received message.
 * @param ec Error Code.
 */
void mih_user::capability_discover_confirm(odtone::mih::message& msg, const boost::system::error_code& ec)
{
	if (ec) {
		log_(0, __FUNCTION__, " error: ", ec.message());
		return;
	}

	odtone::mih::status st;
	boost::optional<odtone::mih::net_type_addr_list> ntal;
	boost::optional<odtone::mih::event_list> evt;

	msg >> odtone::mih::confirm()
		& odtone::mih::tlv_status(st)
		& odtone::mih::tlv_net_type_addr_list(ntal)
		& odtone::mih::tlv_event_list(evt);

	log_(0, "MIH-User has received a Capability_Discover.response with status ",
			st.get(), " and the following capabilities:");

	if (ntal) {
		for (odtone::mih::net_type_addr_list::iterator i = ntal->begin(); i != ntal->end(); ++i)
			log_(0,  *i);

	} else {
		log_(0,  "none");
	}

	//
	// event subscription
	//
	// For every interface the MIHF sent in the
	// Capability_Discover.response send an Event_Subscribe.request
	// for all availabe events
	//
	if (ntal && evt) {
		for (odtone::mih::net_type_addr_list::iterator i = ntal->begin(); i != ntal->end(); ++i) {
			odtone::mih::message req;
			odtone::mih::link_tuple_id li;

			if (i->nettype.link.which() == 1)
				{
					li.addr = i->addr;
					li.type = boost::get<odtone::mih::link_type>(i->nettype.link);

					req << odtone::mih::request(odtone::mih::request::event_subscribe, _mihfid)
						& odtone::mih::tlv_link_identifier(li)
						& odtone::mih::tlv_event_list(evt);

					_mihf.async_send(req, boost::bind(&mih_user::event_subscribe_response, this, _1, _2));

					log_(0, "MIH-User has sent Event_Subscribe.request");
				}
		}
	}
}

/**
 * Event subscribe handler.
 *
 * @param msg Received message.
 * @param ec Error Code.
 */
void mih_user::event_subscribe_response(odtone::mih::message& msg, const boost::system::error_code& ec)
{
	log_(0, __FUNCTION__, "(", msg.tid(), ")");

	if (ec) {
		log_(0, __FUNCTION__, " error: ", ec.message());
		return;
	}

	odtone::mih::status st;

	msg >> odtone::mih::response()
		& odtone::mih::tlv_status(st);

	log_(0, "status: ", st.get());
}

int main(int argc, char** argv)
{
	odtone::setup_crash_handler();

	try {
		boost::asio::io_service ios;

		// declare MIH Usr available options
		po::options_description desc(odtone::mih::octet_string("MIH Usr Configuration"));
		desc.add_options()
			("help", "Display configuration options")
			(odtone::sap::kConf_File, po::value<std::string>()->default_value("mih_usr.conf"), "Configuration file")
			(odtone::sap::kConf_Receive_Buffer_Len, po::value<uint>()->default_value(4096), "Receive buffer length")
			(odtone::sap::kConf_Port, po::value<ushort>()->default_value(1234), "Listening port")
			(odtone::sap::kConf_MIH_SAP_id, po::value<std::string>()->default_value("user"), "MIH-User ID")
			(odtone::sap::kConf_MIH_Handover, po::value<bool>()->default_value("true"), "MIH-User handover support")
			(odtone::sap::kConf_MIHF_Ip, po::value<std::string>()->default_value("127.0.0.1"), "Local MIHF IP address")			
			(odtone::sap::kConf_MIHF_Local_Port, po::value<ushort>()->default_value(1025), "Local MIHF communication port")
			(odtone::sap::kConf_MIH_SAP_dest, po::value<std::string>()->default_value(""), "MIHF destination");

		odtone::mih::config cfg(desc);
		cfg.parse(argc, argv, odtone::sap::kConf_File);

		if (cfg.help()) {
			std::cerr << desc << std::endl;
			return EXIT_SUCCESS;
		}

		mih_user usr(cfg, ios);

		ios.run();

	} catch(std::exception& e) {
		log_(0, "exception: ", e.what());
	}
}

// EOF ////////////////////////////////////////////////////////////////////////
