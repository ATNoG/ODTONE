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
#include "utils.hpp"

#include <odtone/base.hpp>
#include <odtone/mih/message.hpp>
#include <odtone/buffer.hpp>

#include <boost/asio.hpp>
///////////////////////////////////////////////////////////////////////////////

using namespace boost::asio;

namespace odtone { namespace mihf {

/**
 * This class represents a session of a TCP communication with a peer MIHF.
 */
class session {
public:
	/**
	 * TCP session constructor.
	 *
	 * @param io io_service.
	 * @param d dispatch function.
	 */
	session(io_service &io, dispatch_t &d);

	/**
	 * Get session's socket.
	 *
	 * @return The session's Socket.
	 */
	ip::tcp::socket &socket();

	/**
	 * Start Session.
	 */
	void start();

	/**
	 * Handle completion of an asynchronous accept operation.
	 *
	 * @param buff input message bytes.
	 * @param rbytes number of bytes of the input message.
	 * @param error error code.
	 */
	void handle_read(odtone::buffer<uint8> &buff,
			 size_t rbytes,
			 const boost::system::error_code& error);

private:
	ip::tcp::socket		 _sock;
	ip::tcp::endpoint	 _rmt_endp;
	dispatch_t		&_dispatch;
};

/**
 * The classes tcp_listener is a wrapper around the boost::asio::ip::tcp and is
 * responsible for handling TCP communications.
 */
class tcp_listener {
public:
	/**
	 * TCP Listener constructor.
	 *
	 * @param io io_service.
	 * @param buff_size Receive Buffer Length.
	 * @param ipv IP protocol.
	 * @param ip IP Address.
	 * @param port listening port.
	 * @param d dispatch function.
	 */
	tcp_listener(io_service &io,
		     uint16 buff_size,
		     ip::tcp ipv,
		     const char* ip,
		     uint16 port,
		     dispatch_t &d);

	/**
	 * Start TCP listener socket.
	 */
	void start();

	/**
	 * TCP accept handler.
	 *
	 * @param new_session session.
	 * @param error_code error code.
	 */
	void handle_accept(session *s, const boost::system::error_code &e);

private:
	io_service &_io;
	ip::tcp::acceptor _acceptor;
	dispatch_t &_dispatch;
};

} /* namespace mifh */ } /* namespace odtone */
