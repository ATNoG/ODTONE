//==============================================================================
// Brief   : TCP Listener
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
#include "tcp_listener.hpp"
#include "log.hpp"
#include "mihfid.hpp"

#include <odtone/bind_rv.hpp>
#include <boost/bind.hpp>

///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

/**
 * Construct a TCP session.
 *
 * @param io The io_service object that TCP session will use to
 * dispatch handlers for any asynchronous operations performed on
 * the socket.
 * @param d The dispatch function.
 */
session::session(io_service &io, dispatch_t &d, bool enable_multicast)
	: _sock(io),
	  _dispatch(d)
{
	_enable_multicast = enable_multicast;
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
 * Start a new session.
 */
void session::start()
{
	odtone::buffer<uint8> buff = odtone::buffer<uint8>(1500);
	void *rbuf = buff.get();
	size_t rlen = buff.size();

	_sock.async_read_some(boost::asio::buffer(rbuf, rlen),
			      boost::bind(&session::handle_read,
					  this,
					  odtone::bind_rv(buff),
					  placeholders::bytes_transferred,
					  placeholders::error));
}

/**
 * Handle the reception of an asynchronous message.
 *
 * @param buff The input message bytes.
 * @param rbytes The number of bytes of the input message.
 * @param error The error code.
 */
void session::handle_read(odtone::buffer<uint8> &buff,
			  size_t rbytes,
			  const boost::system::error_code &e)
{
	if (!e) {
		// Decode IP address
		mih::octet_string ip;
		uint16 scope = 0;
		if(_sock.remote_endpoint().address().is_v4()) {
			boost::asio::ip::address_v4 ip_addr = _sock.remote_endpoint().address().to_v4();
			ip = ip_addr.to_string();
		} else if(_sock.remote_endpoint().address().is_v6()) {
			boost::asio::ip::address_v6 ip_addr = _sock.remote_endpoint().address().to_v6();
			scope = ip_addr.scope_id();
			ip_addr.scope_id(0);
			ip = ip_addr.to_string();
		}
		// Decode port
		uint16 port = _sock.remote_endpoint().port();

		mih::frame *pud = mih::frame::cast(buff.get(), rbytes);
		if(pud) {
			ODTONE_LOG(1, "(tcp) received ", rbytes, " bytes from ", ip , " : ", port);

			meta_message_ptr in(new meta_message(ip, scope, port, *pud));

			// discard messages if multicast messages are not supported
			if(utils::is_multicast(in) && !_enable_multicast) {
				ODTONE_LOG(1, "(tcp) Discarding message! Reason: ",
							  "multicast messages are not supported");
			} else {
				_dispatch(in);
			}
		}

		// close socket because we're not using it anymore
		 _sock.close();
	} else {
		delete this;
	}
}

/**
 * Construct a TCP Listener.
 *
 * @param io The io_service object that TCP listener module will use to
 * dispatch handlers for any asynchronous operations performed on
 * the socket.
 * @param buff_size The receive buffer length.
 * @param ipv The IP protocol type.
 * @param ip The IP address to be aware.
 * @param port The listening port.
 * @param d The dispatch function.
 */
tcp_listener::tcp_listener(io_service &io,
			   uint16 buff_size,
			   ip::tcp ipv,
			   const char* ip,
			   uint16 port,
			   dispatch_t &d,
			   bool enable_multicast)
	: _io(io),
	  _acceptor(io),
	  _dispatch(d)
{
	_enable_multicast = enable_multicast;

	_acceptor.open(ipv);
	_acceptor.set_option(boost::asio::socket_base::receive_buffer_size(buff_size));
	_acceptor.set_option(boost::asio::socket_base::reuse_address(true));
	_acceptor.bind(boost::asio::ip::tcp::endpoint(ip::address::from_string(ip), port));
}

/**
 * Start the TCP listener socket.
 */
void tcp_listener::start()
{
	session *new_session = new session(_io, _dispatch, _enable_multicast);
	_acceptor.listen();
	_acceptor.async_accept(new_session->socket(),
			       boost::bind(&tcp_listener::handle_accept,
					   this,
					   new_session,
					   placeholders::error));
}

/**
 * TCP accept handler.
 *
 * @param new_session The session to handle the connection.
 * @param error_code The error code.
 */
void tcp_listener::handle_accept(session *new_session,
			       const boost::system::error_code &e)
{
	if (!e) {
		new_session->start();
		new_session = new session(_io, _dispatch, _enable_multicast);

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
