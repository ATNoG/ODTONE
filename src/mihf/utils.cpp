//
// Copyright (c) 2007-2009 2009 Universidade Aveiro - Instituto de
// Telecomunicacoes Polo Aveiro
// This file is part of ODTONE - Open Dot Twenty One.
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//
// Author:     Simao Reis <sreis@av.it.pt>
//

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

bool is_local_request(mih::message_ptr &in)
{
	return ((in->destination().to_string().length() == 0) ||
			(mihfid == in->destination()));
}

static void send_handler(const boost::system::error_code &ec)
{
	if (ec)
		log(1, "Error sending message. Error code: ", ec.message());
}

void tcp_send(io_service &io, mih::message_ptr &msg, const char *ip, uint16 port)
{
	ip::tcp::endpoint ep(ip::address::from_string(ip), port);
	ip::tcp::socket sock(io);

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

void udp_send(io_service &io, mih::message_ptr &msg, const char *ip, uint16 port)
{
	ip::udp::socket sock(io, ip::udp::endpoint(ip::udp::v4(), 0));
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

void forward_request(mih::message_ptr &in,
		     local_transaction_pool &lpool,
		     transmit &t)
{
	log(1, "(utils) forwarding request to ", in->destination().to_string());
	lpool.add(in);
	in->source(mihfid);
	t(in);
}





} /* namespace utils */ } /* namespace mihf */ } /* namespace odtone */
