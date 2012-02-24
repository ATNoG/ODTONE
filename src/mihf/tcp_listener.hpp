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
	 * Construct a TCP session.
	 *
	 * @param io The io_service object that TCP session will use to
	 * dispatch handlers for any asynchronous operations performed on
	 * the socket.
	 * @param d The dispatch function.
	 * @param enable_multicast True if multicast messages are allowed or false
	 * 						   otherwise.
	 */
	session(io_service &io, dispatch_t &d, bool enable_multicast);

	/**
	 * Get session's socket.
	 *
	 * @return The session's Socket.
	 */
	ip::tcp::socket &socket();

	/**
	 * Start a new session.
	 */
	void start();

	/**
	 * Handle the reception of an asynchronous message.
	 *
	 * @param buff The input message bytes.
	 * @param rbytes The number of bytes of the input message.
	 * @param error The error code.
	 */
	void handle_read(odtone::buffer<uint8> &buff,
			 size_t rbytes,
			 const boost::system::error_code& error);

private:
	ip::tcp::socket		_sock;		/**< Session TCP socket.			*/
	ip::tcp::endpoint	_rmt_endp;	/**< Remote endpoint.				*/
	dispatch_t			&_dispatch;	/**< Session dispatch function.		*/

	bool _enable_multicast;			/**< Multicast messages allowed?	*/
};

/**
 * This class is a wrapper around the boost::asio::ip::tcp and it is
 * responsible for handling TCP communications.
 */
class tcp_listener {
public:
	/**
	 * Construct a TCP Listener.
	 *
	 * @param io The io_service object that TCP listener will use to
	 * dispatch handlers for any asynchronous operations performed on
	 * the socket.
	 * @param buff_size The receive buffer length.
	 * @param ipv The IP protocol type.
	 * @param ip The IP address to be aware.
	 * @param port The listening port.
	 * @param d The dispatch function.
	 * @param enable_multicast True if multicast messages are allowed or false
	 * 						   otherwise.
	 */
	tcp_listener(io_service &io,
		     uint16 buff_size,
		     ip::tcp ipv,
		     const char* ip,
		     uint16 port,
		     dispatch_t &d,
		     bool enable_multicast);

	/**
	 * Start the TCP listener socket.
	 */
	void start();

	/**
	 * TCP accept handler.
	 *
	 * @param new_session The session to handle the connection.
	 * @param error_code The error code.
	 */
	void handle_accept(session *s, const boost::system::error_code &e);

private:
	io_service &_io;				/**< The io_service object.			*/
	ip::tcp::acceptor _acceptor;	/**< TCP session acceptor.			*/
	dispatch_t &_dispatch;			/**< Session dispatch function.		*/

	bool _enable_multicast;			/**< Multicast messages allowed?	*/
};

} /* namespace mifh */ } /* namespace odtone */
