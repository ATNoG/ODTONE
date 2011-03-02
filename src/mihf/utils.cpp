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
///////////////////////////////////////////////////////////////////////////////

using namespace boost::asio;

namespace odtone { namespace mihf { namespace utils {

static const mih::id default_local_mihfid = mih::id("local-mihf");

/**
 * Check if the message destination is this MIHF.
 *
 * @param msg MIH Message.
 * @return true if this MIHF is the message destination or false otherwise.
 */
bool this_mihf_is_destination(meta_message_ptr &msg)
{
	return ((mihfid == msg->destination()) ||
		(default_local_mihfid == msg->destination()));
}

/**
 * Check if the message is a multicast message.
 *
 * @param msg MIH Message.
 * @return true if this is a multicast message or false otherwise.
 */
bool is_multicast(meta_message_ptr &msg)
{
	return (msg->destination().to_string().length() == 0);
}

/**
 * Handle completion of a send operation.
 *
 * @param ec error code.
 */
static void send_handler(const boost::system::error_code &ec)
{
	if (ec)
		ODTONE_LOG(1, "Error sending message. Error code: ", ec.message());
}

/**
 * Send a message using a TCP socket.
 *
 * @param io io_service.
 * @param msg output message.
 * @param ip destination IP Address.
 * @param port destination port.
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
 * Send a message using a UDP socket.
 *
 * @param io io_service.
 * @param msg output message.
 * @param ip destination IP Address.
 * @param port destination port.
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
 * Forward request to its destination.
 *
 * @param in MIH Message to forward.
 * @param lpool local transaction pool module.
 * @param t transmit module.
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





} /* namespace utils */ } /* namespace mihf */ } /* namespace odtone */
