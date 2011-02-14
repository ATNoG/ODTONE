//==============================================================================
// Brief   : TCP Listener
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
#include "tcp_listener.hpp"
#include "log.hpp"
#include <boost/bind.hpp>

///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

/**
 * TCP session constructor.
 *
 * @param io io_service.
 * @param d dispatch function.
 */
session::session(io_service &io, dispatch_t &d)
	: _sock(io),
	  _dispatch(d)
{
}

/**
 * Get session's socket.
 *
 * @return The session's Socket.
 */
ip::tcp::socket& session::socket()
{
	return _sock;
}

/**
 * Start Session.
 */
void session::start()
{
	odtone::buffer<uint8> buff = odtone::buffer<uint8>(1500);
	void *rbuf = buff.get();
	size_t rlen = buff.size();

	_sock.async_read_some(boost::asio::buffer(rbuf, rlen),
			      boost::bind(&session::handle_read,
					  this,
					  odtone::move(buff),
					  placeholders::bytes_transferred,
					  placeholders::error));
}

/**
 * Handle completion of an asynchronous accept operation.
 *
 * @param buff input message bytes.
 * @param rbytes number of bytes of the input message.
 * @param error error code.
 */
void session::handle_read(odtone::buffer<uint8> &buff,
			  size_t rbytes,
			  const boost::system::error_code &e)
{
	if (!e) {
		mih::octet_string ip(_sock.remote_endpoint().address().to_string());
		uint16 port = _sock.remote_endpoint().port();

		mih::frame *pud = mih::frame::cast(buff.get(), rbytes);
		if(pud) {
			log(1, "(tcp) received ", rbytes, " bytes from ", ip , ":", port);

			meta_message_ptr in(new meta_message(ip, port, *pud));
			_dispatch(in);
                }
		// close socket because we're not using it anymore
		 _sock.close();
	} else {
		delete this;
	}
}

/**
 * TCP Listener constructor.
 *
 * @param io io_service.
 * @param ipv IP protocol.
 * @param ip IP Address.
 * @param port listening port.
 * @param d dispatch function.
 */
tcp_listener::tcp_listener(io_service &io,
			   ip::tcp ipv,
			   const char* ip,
			   uint16 port,
			   dispatch_t &d)
	: _io(io),
	  _acceptor(io, ip::tcp::endpoint(ip::address::from_string(ip), port)),
	  _dispatch(d)
{
}

/**
 * Start TCP listener socket.
 */
void tcp_listener::start()
{
	session *new_session = new session(_io, _dispatch);
	_acceptor.async_accept(new_session->socket(),
			       boost::bind(&tcp_listener::handle_accept,
					   this,
					   new_session,
					   placeholders::error));
}

/**
 * TCP accept handler.
 *
 * @param s session.
 * @param error_code error code.
 */
void tcp_listener::handle_accept(session *new_session,
			       const boost::system::error_code &e)
{
	if (!e) {
		new_session->start();
		new_session = new session(_io, _dispatch);

		_acceptor.async_accept(new_session->socket(),
				       boost::bind(&tcp_listener::handle_accept,
						   this,
						   new_session,
						   placeholders::error));
	} else {
		delete new_session;
	}
}

} /* namespace mifh */ } /* namespace odtone */
