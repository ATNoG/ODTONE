//==============================================================================
// Brief   : DHCP User
// Authors : Carlos Guimaraes <cguimaraes@av.it.pt>
//------------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2009-2012 Universidade Aveiro
// Copyright (C) 2009-2012 Instituto de Telecomunicações - Pólo Aveiro
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//==============================================================================

#include "dhcp_usr.hpp"
#include "log.hpp"

#include <odtone/mih/request.hpp>
#include <odtone/mih/response.hpp>
#include <odtone/mih/confirm.hpp>
#include <odtone/mih/indication.hpp>
#include <odtone/mih/tlv_types.hpp>
#include <odtone/mih/types/address.hpp>

#include <boost/bind.hpp>
#include <boost/foreach.hpp>

namespace odtone {

///////////////////////////////////////////////////////////////////////////////
/**
 * Construct the DHCP-User.
 *
 * @param io The io_service object that DHCP-User will use to
 * dispatch handlers for any asynchronous operations performed on the socket.
 * @param cfg Configuration options.
 * @param nic Mapping of the local network interfaces.
 * @param version The DHCP version to use.
 */
dhcp_user::dhcp_user(boost::asio::io_service& io,
					 const mih::config& cfg,
                     std::map<std::string, std::string> nic,
                     ushort version)
	: _mihf(cfg, io, boost::bind(&dhcp_user::event_handler, this, _1, _2)),
	  _control(version, nic, boost::bind(&dhcp_user::dhcp_results_handler, this, _1))
{
	_nic       = nic;
	_mihfid = mih::id("local-mihf");

	// Register with MIHF
	mih::message m;

	m << mih::indication(mih::indication::user_register);
	m.destination(mih::id("local-mihf"));

	_mihf.async_send(m, boost::bind(&dhcp_user::user_reg_handler, this, boost::cref(cfg), _2));
}

/**
 * Destruct the DHCP-User.
 */
dhcp_user::~dhcp_user()
{
}

/**
 * User registration handler.
 *
 * @param cfg Configuration options.
 * @param ec Error Code.
 */
void dhcp_user::user_reg_handler(const mih::config& cfg,
                                 const boost::system::error_code& ec)
{
	if (ec) {
		ODTONE_LOG(1, __FUNCTION__, " error: ", ec.message());
		return;
	}

	ODTONE_LOG(0, "DHCP-User register result: ", ec.message());

	// Request the capabilities of the local MIHF
	mih::message msg;
	msg << mih::request(mih::request::capability_discover, _mihfid);

	_mihf.async_send(msg, boost::bind(&dhcp_user::cap_disc_handler, this, _1, _2));

	ODTONE_LOG(0, "sent a Capability_Discover.request towards its local MIHF");
}

/**
 * Capability Discover handler.
 *
 * @param msg Received message.
 * @param ec Error Code.
 */
void dhcp_user::cap_disc_handler(mih::message& msg,
                                 const boost::system::error_code& ec)
{
	if (ec) {
		ODTONE_LOG(0, __FUNCTION__, " error: ", ec.message());
		return;
	}

	mih::status st;
	boost::optional<mih::net_type_addr_list> ntal;
	boost::optional<mih::mih_evt_list> evt;

	msg >> mih::confirm()
		& mih::tlv_status(st)
		& mih::tlv_net_type_addr_list(ntal)
		& mih::tlv_event_list(evt);

	ODTONE_LOG(0, "received a Capability_Discover.confirm with status ",
			st.get(), " and the following capabilities:");

	if (ntal) {
		for (mih::net_type_addr_list::iterator i = ntal->begin(); i != ntal->end(); ++i) {
			ODTONE_LOG(0,  *i);
		}
	} else {
		ODTONE_LOG(0,  "none");
	}

	if(evt) {
		if(!evt->get(mih::mih_evt_link_up) || !evt->get(mih::mih_evt_link_down)) {
			ODTONE_LOG(1, "cannot register for link_up and link_down events");
			return;
		}
	} else {
		ODTONE_LOG(1, "cannot register for link_up and link_down events");
		return;
	}

	//
	// event subscription
	//
	// For every interface the MIHF sent in the
	// Capability_Discover.response send an Event_Subscribe.request
	// for link_up and link_down events
	//
	if (ntal && evt) {
		for (mih::net_type_addr_list::iterator i = ntal->begin(); i != ntal->end(); ++i) {
			mih::message req;
			mih::link_tuple_id li;

			if (i->nettype.link.which() == 1) {
				li.addr = i->addr;
				li.type = boost::get<mih::link_type>(i->nettype.link);

				req << mih::request(mih::request::event_subscribe, _mihfid)
					& mih::tlv_link_identifier(li)
					& mih::tlv_event_list(evt);

				_mihf.async_send(req, boost::bind(&dhcp_user::subscription_handler, this, _1, _2));

				ODTONE_LOG(0, "sent Event_Subscribe.request");
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
void dhcp_user::subscription_handler(mih::message& msg,
                                     const boost::system::error_code& ec)
{
	if (ec) {
		ODTONE_LOG(0, __FUNCTION__, " error: ", ec.message());
		return;
	}

	mih::status st;
	msg >> mih::confirm()
		& mih::tlv_status(st);

	ODTONE_LOG(0, "received a Event_Subscribe.confirm with status ", st.get());
}

/**
 * Default MIH event handler.
 *
 * @param msg Received message.
 * @param ec Error code.
 */
void dhcp_user::event_handler(mih::message& msg,
                              const boost::system::error_code& ec)
{
	if (ec) {
		ODTONE_LOG(0, __FUNCTION__, " error: ", ec.message());
		return;
	}

	switch (msg.mid()) {
		case mih::indication::link_up:
		{
			ODTONE_LOG(0, "received a local event \"link_up\"");

			// There is no need to decode all TLVs because only
			// Link Identifier information is needed.
			mih::link_tuple_id li;
			msg >> mih::indication(mih::indication::link_up)
			    & mih::tlv_link_identifier(li);

			boost::mutex::scoped_lock lock(_mutex);

			// Map between Link Identifier and NIC
			boost::optional<std::string> ifname = find_nic(li.addr);
			if(ifname.is_initialized()) {
				// Check if there is an active session for the requested
				// interface
				std::vector<std::string>::const_iterator it;
				it = std::find(_sessions.begin(), _sessions.end(), ifname.get());
				if (it == _sessions.end()) {
					_sessions.push_back(ifname.get());
					_control.new_session(ifname.get());
				} else {
					ODTONE_LOG(0, "This interface has an active session.");
				}
			}
		}
		break;

		case mih::indication::link_down:
		{
			ODTONE_LOG(0, "received a local event \"link_down\"");
			mih::link_tuple_id li;
			msg >> mih::indication(mih::indication::link_down)
			    & mih::tlv_link_identifier(li);

			boost::mutex::scoped_lock lock(_mutex);

			// Map between Link Identifier and NIC
			boost::optional<std::string> ifname = find_nic(li.addr);
			if(ifname.is_initialized()) {
				// If there is an active session for the requested interface
				std::vector<std::string>::iterator it;
				it = std::find(_sessions.begin(), _sessions.end(), ifname.get());
				if (it == _sessions.end()) {
					ODTONE_LOG(0, "This interface does not have an active session");
				} else {
					_control.shutdown_session(ifname.get());
					_sessions.erase(it, it+1);
				}
			}
		}
		break;

		case mih::indication::capability_discover:
		{
			ODTONE_LOG(0, "received a \"capability_discover\" indication");

			boost::mutex::scoped_lock lock(_mutex);

			// For each active session request MoS from its DHCP Server
			BOOST_FOREACH(std::string ifname, _sessions) {
				_requests.push_back(msg.tid());
				_control.request(ifname);
			}
		}
		break;

		default:
		{
			ODTONE_LOG(0, "received a unknown message. Discarding it...");
		}
		break;
	}
}

/**
 * DHCP IEEE 802.21 results handler.
 *
 * @param pos_list List of discovered PoS.
 */
void dhcp_user::dhcp_results_handler(mih::mos_dscv &pos_list)
{
	mih::message rsp;
	mih::status st = mih::status_success;

	rsp << mih::response(mih::response::capability_discover)
		& mih::tlv_status(st)
		& mih::tlv_mos_dscv(pos_list);

	if(_requests.size() != 0) {
		rsp.destination(mih::id(""));
		BOOST_FOREACH(uint16 tid, _requests) {
			rsp.tid(tid);

			_mihf.async_send(rsp, [this](mih::message& msg, const boost::system::error_code& ec) {
				    if (ec) {
				        ODTONE_LOG(0, __FUNCTION__, " error: ", ec.message());
				        return;
				    } else {
						ODTONE_LOG(0, "Sent DHCP discovery results to the MIHF");
					}
			});
		}
		
		_requests.clear();
	} else {
		rsp.tid(0);
		rsp.destination(mih::id(""));

		_mihf.async_send(rsp, [this](mih::message& msg, const boost::system::error_code& ec) {
		        if (ec) {
		            ODTONE_LOG(0, __FUNCTION__, " error: ", ec.message());
		            return;
		        } else {
					ODTONE_LOG(0, "Sent DHCP discovery results to the MIHF");
				}
		});
	}
}

/**
 * Find and retrieve the network interface name identifier associated
 * with a given link address.
 *
 * @param addr The link address of the interface to find.
 * @return The network interface name identifier.
 */
boost::optional<std::string> dhcp_user::find_nic(mih::link_addr addr)
{
	boost::optional<std::string> nic;
	std::string hw_addr;

	switch (addr.which()) {
		case 0: {
			mih::mac_addr* tmp = boost::get<mih::mac_addr>(&addr);
			hw_addr = tmp->address();
		} break;

 		case 1: { 
			ODTONE_LOG(0, "Not supported yet");
		} break;

		case 2: {
			ODTONE_LOG(0, "Not supported yet");
		} break;

		case 3: {
			mih::l2_3gpp_addr* tmp = boost::get<mih::l2_3gpp_addr>(&addr);
			hw_addr = tmp->value;
		} break;

		case 4: {
			mih::l2_3gpp2_addr* tmp = boost::get<mih::l2_3gpp2_addr>(&addr);
			hw_addr = tmp->value;
		} break;

		case 5: {
			mih::other_l2_addr* tmp = boost::get<mih::other_l2_addr>(&addr);
			hw_addr = tmp->value;
		} break;

		default: {
			ODTONE_LOG(0, "Invalid Link Address");
			return nic;
		} break;
	}

	// map link address with interface name
	std::map<std::string, std::string>::const_iterator it;
	it = _nic.find(hw_addr);
	if (it != _nic.end()) {
		nic = it->second;
	}

	return nic;
}

} /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
