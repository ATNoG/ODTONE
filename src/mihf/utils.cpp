//==============================================================================
// Brief   : Utilities
// Authors : Simao Reis <sreis@av.it.pt>
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

///////////////////////////////////////////////////////////////////////////////
#include "utils.hpp"
#include "log.hpp"
#include "mihfid.hpp"

#include <odtone/base.hpp>
#include <odtone/mih/types.hpp>
#include <odtone/mih/tlv.hpp>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
///////////////////////////////////////////////////////////////////////////////

using namespace boost::asio;

namespace odtone { namespace mihf { namespace utils {

static const mih::id default_local_mihfid = mih::id("local-mihf");

/**
 * Check if the message destination is this MIHF.
 *
 * @param msg The input message.
 * @return True if this MIHF is the message destination or false otherwise.
 */
bool this_mihf_is_destination(meta_message_ptr &msg)
{
	return ((mihfid == msg->destination()) ||
		(default_local_mihfid == msg->destination()));
}

/**
 * Check if the message is a multicast message.
 *
 * @param msg The input message.
 * @return True if this is a multicast message or false otherwise.
 */
bool is_multicast(meta_message_ptr &msg)
{
	return (msg->destination().to_string().length() == 0);
}

/**
 * Handle completion of a send operation.
 *
 * @param ec The error code.
 */
static void send_handler(const boost::system::error_code &ec)
{
	if (ec)
		ODTONE_LOG(1, "Error sending message. Error code: ", ec.message());
}

/**
 * Send a message using a TCP socket.
 *
 * @param io The io_service object that TCP socket will use to
 * dispatch handlers for any asynchronous operations performed on
 * the socket.
 * @param msg The output message.
 * @param dst_ip The IP address of the destination of the message.
 * @param dst_port The port of the destination of the message.
 * @param src_port The source port used to send the message.
 */
void tcp_send(boost::asio::io_service &io, meta_message_ptr &msg,
			  const char *dst_ip, uint16 dst_port, uint16 src_port)
{
	ip::tcp::socket sock(io);

	//
	// broadcast if no destination mihf is given
	//
	if (is_multicast(msg)) {
		boost::asio::socket_base::broadcast option(true);
		sock.set_option(option);
	}

	sock.connect(ip::tcp::endpoint(ip::address::from_string(dst_ip), dst_port));

	mih::frame_vla fm;
	void *sbuff;
	size_t slen;

	msg->get_frame(fm);
	sbuff = fm.get();
	slen = fm.size();

	boost::asio::async_write(sock,
				 boost::asio::buffer(sbuff, slen),
				 boost::bind((&send_handler),
					     placeholders::error));
	sock.close();
}

/**
 * Send a message using an UDP socket.
 *
 * @param io The io_service object that UDP socket will use to
 * dispatch handlers for any asynchronous operations performed on
 * the socket.
 * @param msg The output message.
 * @param dst_ip The IP address of the destination of the message.
 * @param dst_port The port of the destination of the message.
 * @param src_port The source port used to send the message.
 */
void udp_send(boost::asio::io_service &io, meta_message_ptr &msg,
			  const char *dst_ip, uint16 dst_port, uint16 src_port)
{
	ip::udp::socket sock(io);
	mih::frame_vla fm;
	void *sbuff;
	size_t slen;

	msg->get_frame(fm);
	sbuff = fm.get();
	slen = fm.size();

	ip::udp::endpoint ep(ip::address::from_string(dst_ip), dst_port);
	if (strcmp(dst_ip, "ff02::1") == 0) {
		if(ep.address().is_v4())
			sock.open(ip::udp::v4());
		else if(ep.address().is_v6())
			sock.open(ip::udp::v6());

		// Set socket flags
		sock.set_option(boost::asio::socket_base::reuse_address(true));
		boost::asio::socket_base::broadcast option(true);
		sock.set_option(option);

		if(ep.address().is_v4())
			sock.bind(ip::udp::endpoint(ip::address_v4::any(), src_port));
		else if(ep.address().is_v6())
			sock.bind(ip::udp::endpoint(ip::address_v6::any(), src_port));

		// FIXME: Proper and portable way to discover the available interfaces
		for(int i = 1; i <= 5; i++) {
			try {
				sock.set_option(ip::multicast::outbound_interface(i));
				sock.set_option(ip::multicast::enable_loopback(false));

				sock.async_send_to(boost::asio::buffer(sbuff, slen),
						   ep,
						   boost::bind((&send_handler),
						   placeholders::error));
			} catch(...) {
				return;
			}
		}
	} else {
		if(ep.address().is_v4())
			sock.open(ip::udp::v4());
		else if(ep.address().is_v6())
			sock.open(ip::udp::v6());

		// Set socket flags
		sock.set_option(boost::asio::socket_base::reuse_address(true));

		if(ep.address().is_v4())
			sock.bind(ip::udp::endpoint(ip::address_v4::any(), src_port));
		else if(ep.address().is_v6())
			sock.bind(ip::udp::endpoint(ip::address_v6::any(), src_port));

		if(ep.address().is_v6())
			ep.address().to_v6().scope_id(msg->scope());

		sock.async_send_to(boost::asio::buffer(sbuff, slen),
				   ep,
				   boost::bind((&send_handler),
						   placeholders::error));
	}

	sock.close();
}

/**
 * Forward the request to its destination.
 *
 * @param in The MIH Message to forward.
 * @param lpool The local transaction pool module.
 * @param t The transmit module.
 */
void forward_request(meta_message_ptr &in,
		     local_transaction_pool &lpool,
		     transmit &t)
{
	ODTONE_LOG(1, "(utils) forwarding request to ", in->destination().to_string());
	lpool.add(in);
	in->source(mihfid);
	t(in);
}

/**
 * Update the capabilities of the local MIHF.
 *
 * @param abook The address book module.
 * @param lbook The link book module.
 * @param ubook The user book module.
 */
void update_local_capabilities(address_book &abook, link_book &lbook, user_book &ubook)
{
	mih::net_type_addr_list  capabilities_list_net_type_addr;
	mih::mih_evt_list	     capabilities_event_list;
	mih::mih_cmd_list        capabilities_cmd_list;
	mih::iq_type_list        capabilities_query_type;

	capabilities_event_list.full();
	capabilities_cmd_list.full();

	// Get capabilities from Link SAPs
	const std::vector<mih::octet_string> link_sap_list = lbook.get_ids();
	BOOST_FOREACH(mih::octet_string id, link_sap_list) {
		mih::mih_evt_list events;
		mih::mih_cmd_list commands;

		link_entry link_sap;
		link_sap = lbook.get(id);
		if(link_sap.status) {
			// fill LinkAddressList
			mih::net_type_addr nta;

			nta.nettype.link = link_sap.link_id.type;
			nta.addr = link_sap.link_id.addr;
			capabilities_list_net_type_addr.push_back(nta);

			// fill capabilities
			// Since the two bitmaps have the same values
			// we can assign them directly
			for (size_t i = 0; i < 32; ++i) {
				if(link_sap.event_list.get((mih::link_evt_list_enum)i)) {
					events.set((mih::mih_evt_list_enum)i);
				}
			}

			if(link_sap.cmd_list.get(mih::cmd_link_get_parameters))
				commands.set(mih::mih_cmd_link_get_parameters);
			if(link_sap.cmd_list.get(mih::cmd_link_configure_thresholds))
				commands.set(mih::mih_cmd_link_configure_thresholds);
			if(link_sap.cmd_list.get(mih::cmd_link_action))
				commands.set(mih::mih_cmd_link_actions);

			capabilities_event_list.common(events);
			capabilities_cmd_list.common(commands);
		}
	}

	// If the MIHF does not have any active Link SAP
	if(capabilities_list_net_type_addr.size() == 0) {
		boost::optional<mih::net_type_addr_list>	empty_list_net_type_addr;
		boost::optional<mih::mih_evt_list>			empty_event_list;
		boost::optional<mih::mih_cmd_list>			empty_cmd_list;

		abook.set_link_address_list(mihfid_t::instance()->to_string(), empty_list_net_type_addr);
		abook.set_event_list(mihfid_t::instance()->to_string(), empty_event_list);
		abook.set_command_list(mihfid_t::instance()->to_string(), empty_cmd_list);
	} else {
		abook.set_link_address_list(mihfid_t::instance()->to_string(), capabilities_list_net_type_addr);
		abook.set_event_list(mihfid_t::instance()->to_string(), capabilities_event_list);
		abook.set_command_list(mihfid_t::instance()->to_string(), capabilities_cmd_list);
	}


	// Get capabilities from MIH-Users
	bool has_cmd = false;
	bool has_iq = false;
	const std::vector<mih::octet_string> user_sap_list = ubook.get_ids();
	BOOST_FOREACH(mih::octet_string id, user_sap_list) {
		mih::mih_cmd_list commands;
		mih::iq_type_list queries;

		user_entry user_sap;
		user_sap = ubook.get(id);

		// fill capabilities
		if(user_sap.supp_cmd.is_initialized()) {
			for (size_t i = 3; i < 32; ++i) {
				if(user_sap.supp_cmd->get((mih::mih_cmd_list_enum)i)) {
					commands.set((mih::mih_cmd_list_enum)i);
					has_cmd = true;
				}
			}
		}

		if(user_sap.supp_iq.is_initialized()) {
			for (size_t i = 0; i < 32; ++i) {
				if(user_sap.supp_iq->get((mih::iq_type_list_enum)i)) {
					queries.set((mih::iq_type_list_enum)i);
					has_iq = true;
				}
			}
		}

		capabilities_cmd_list.merge(commands);
		capabilities_query_type.merge(queries);
	}

	// If the MIHF does not have any active Link SAP
	if(has_cmd) {
		abook.set_command_list(mihfid_t::instance()->to_string(), capabilities_cmd_list);
	} else {
		boost::optional<mih::mih_cmd_list> empty_cmd_list;
		abook.set_command_list(mihfid_t::instance()->to_string(), empty_cmd_list);
	}

	if(has_iq) {
		abook.set_query_list(mihfid_t::instance()->to_string(), capabilities_query_type);
	} else {
		boost::optional<mih::iq_type_list> empty_query_type;
		abook.set_query_list(mihfid_t::instance()->to_string(), empty_query_type);
	}
}



} /* namespace utils */ } /* namespace mihf */ } /* namespace odtone */
