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
#include "tcp_server.hpp"

#include "log.hpp"

#include <boost/bind.hpp>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

session::session(io_service &io)
	: _sock(io)
{
	// TODO: read max buffer size from config file (??)
	_buff = odtone::buffer<uint8>(1500);
}

ip::tcp::socket& session::socket()
{
	return _sock;
}

void session::start()
{
	void *rbuf = _buff.get();
	size_t rlen = _buff.size();

	_sock.async_read_some(boost::asio::buffer(rbuf, rlen),
			      boost::bind(&session::handle_read,
					  this,
					  placeholders::error,
					  placeholders::bytes_transferred));
}

void session::handle_read(const boost::system::error_code &e, size_t rbytes)
{
	if (!e) {
		// TODO: process message
	} else {
		delete this;
	}
}

tcp_server::tcp_server(io_service &io, ip::tcp ipv, const char* ip, uint16 port)
	: _io(io),
	  _acceptor(io, ip::tcp::endpoint(ip::address::from_string(ip), port))
{
}

void tcp_server::start()
{
	session *new_session = new session(_io);
	_acceptor.async_accept(new_session->socket(),
			       boost::bind(&tcp_server::handle_accept,
					   this,
					   new_session,
					   placeholders::error));
}

void tcp_server::handle_accept(session *new_session,
			       const boost::system::error_code &e)
{
	if (!e) {
		new_session->start();
		new_session = new session(_io);

		_acceptor.async_accept(new_session->socket(),
				       boost::bind(&tcp_server::handle_accept,
						   this,
						   new_session,
						   placeholders::error));
	} else {
		delete new_session;
	}
}

void send_handler(const boost::system::error_code &ec, size_t)
{
	if (ec) {
		log(1, "(tcp_server) error sending message. Error code: ", ec);
	}
}

void tcp_server::send(mih::message_ptr &msg, const char *ip, uint16 port)
{
	ip::tcp::endpoint ep(ip::address::from_string(ip), port);
	ip::tcp::socket sock(_io);

	sock.connect(ep);

	mih::frame_vla fm;
	void *sbuff;
	size_t slen;

	msg->get_frame(fm);
	sbuff = fm.get();
	slen = fm.size();

	boost::asio::async_write(sock,
				 boost::asio::buffer(sbuff, slen),
				 send_handler);

}

} /* namespace mifh */ } /* namespace odtone */
