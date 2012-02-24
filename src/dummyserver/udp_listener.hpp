//==============================================================================
// Brief   : UDP Listener
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

#ifndef GENERIC_SERVER_HPP
#define GENERIC_SERVER_HPP

///////////////////////////////////////////////////////////////////////////////
#include "../mihf/utils.hpp"

#include <odtone/debug.hpp>
#include <odtone/buffer.hpp>

#include <boost/asio.hpp>
///////////////////////////////////////////////////////////////////////////////

using namespace boost::asio;

namespace odtone { namespace mihf {

/**
 * This class is a wrapper around the boost::asio::ip::udp and it is
 * responsible for handling UDP communications.
 */
class udp_listener
{
public:
	/**
	 * Construct a UDP Listener.
	 *
	 * @param io The io_service object that UDP Listener service will use to
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
	udp_listener(io_service& io,
		     uint16 buff_size,
		     ip::udp ipv,
		     const char *ip,
		     uint16 port,
		     dispatch_t &d,
		     bool enable_multicast);

	/**
	 * Start the UDP listener socket.
	 */
	void start();

	/**
	 * Handle the reception of an asynchronous message.
	 *
	 * @param buff The input message bytes.
	 * @param rbytes The number of bytes of the input message.
	 * @param error The error code.
	 */
	void handle_receive(buffer<uint8>& buff,
						size_t rbytes,
						const boost::system::error_code& error);

protected:
	io_service			&_io;		/**< The io_service object.			*/
	ip::udp::socket		_sock;		/**< UDP socket.					*/
	dispatch_t			&_dispatch;	/**< Dispatch function.				*/
	ip::udp::endpoint	_rmt_endp;	/**< Remote endpoint.				*/

	bool _enable_multicast;			/**< Multicast messages allowed?	*/
};

} /* namespace mihf */ } /* namespace odtone */

#endif
