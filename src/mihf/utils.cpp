//==============================================================================
// Brief   : Utilities
// Authors : Simao Reis <sreis@av.it.pt>
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
 * @param io The io_service object that Link SAP I/O Service will use to
 * dispatch handlers for any asynchronous operations performed on
 * the socket.
 * @param msg The output message.
 * @param ip The IP address of the destination of the message.
 * @param port The port of the destination of the message.
 */
void tcp_send(io_service &io, meta_message_ptr &msg, const char *ip, uint16 port)
{
	ip::tcp::socket sock(io);

	//
	// broadcast if no destination mihf is given
	//
	if (is_multicast(msg)) {
		boost::asio::socket_base::broadcast option(true);
		sock.set_option(option);
		ip = "ff02::1";
	}

	ip::tcp::endpoint ep(ip::address::from_string(ip), port);

	sock.connect(ep);

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
 * @param io The io_service object that Link SAP I/O Service will use to
 * dispatch handlers for any asynchronous operations performed on
 * the socket.
 * @param msg The output message.
 * @param ip The IP address of the destination of the message.
 * @param port The port of the destination of the message.
 */
void udp_send(io_service &io, meta_message_ptr &msg, const char *ip, uint16 port)
{
	ip::udp::socket sock(io, ip::udp::endpoint(ip::udp::v4(), 0));

	//
	// broadcast if no destination mihf is given
	//
	if (is_multicast(msg)) {
		boost::asio::socket_base::broadcast option(true);
		sock.set_option(option);
		ip = "ff02::1";
	}

	ip::udp::endpoint ep(ip::address::from_string(ip), port);

	//	msg->source(mihfid);
	mih::frame_vla fm;
	void *sbuff;
	size_t slen;

	msg->get_frame(fm);
	sbuff = fm.get();
	slen = fm.size();

	sock.async_send_to(boost::asio::buffer(sbuff, slen),
			   ep,
			   boost::bind((&send_handler),
				       placeholders::error));
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
 */
void update_local_capabilities(address_book &abook, link_book &lbook)
{
	mih::net_type_addr_list  capabilities_list_net_type_addr;
	mih::event_list	         capabilities_event_list;
	mih::command_list        capabilities_cmd_list;

	const std::vector<mih::octet_string> link_sap_list = lbook.get_ids();
	capabilities_event_list.full();
	capabilities_cmd_list.full();

	BOOST_FOREACH(mih::octet_string id, link_sap_list) {
		link_entry link_sap;
		link_sap = lbook.get(id);
		if(link_sap.status) {
			// fill LinkAddressList
			mih::net_type_addr nta;

			nta.nettype.link = link_sap.link_id.type;
			nta.addr = link_sap.link_id.addr;
			capabilities_list_net_type_addr.push_back(nta);

			// fill capabilities
			capabilities_event_list.common(link_sap.event_list);
			capabilities_cmd_list.common(link_sap.cmd_list);
		}
	}

	// If the MIHF does not have any active Link SAP
	if(capabilities_list_net_type_addr.size() == 0) {
		capabilities_event_list.clear();
		capabilities_cmd_list.clear();
	}

	// Update MIHF capabilities
	address_entry mihf;
	mihf.capabilities_list_net_type_addr = capabilities_list_net_type_addr;
	mihf.capabilities_event_list = capabilities_event_list;
	mihf.capabilities_cmd_list = capabilities_cmd_list;

	abook.add(mihfid_t::instance()->to_string(), mihf);
}



} /* namespace utils */ } /* namespace mihf */ } /* namespace odtone */
