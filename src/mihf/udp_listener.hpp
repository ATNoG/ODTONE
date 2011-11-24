//==============================================================================
// Brief   : UDP Listener
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

#ifndef GENERIC_SERVER_HPP
#define GENERIC_SERVER_HPP

///////////////////////////////////////////////////////////////////////////////
#include "utils.hpp"

#include <odtone/debug.hpp>
#include <odtone/buffer.hpp>

#include <boost/asio.hpp>
///////////////////////////////////////////////////////////////////////////////

using namespace boost::asio;

namespace odtone { namespace mihf {

/**
 * The classes udp_listener is a wrapper around the boost::asio::ip::udp and is
 * responsible for handling UDP communications.
 */
class udp_listener
{
public:
	/**
	 * UDP Listener constructor.
	 *
	 * @param io io_service.
	 * @param buff_size Receive Buffer Length.
	 * @param ipv IP protocol.
	 * @param ip IP Address.
	 * @param port listening port.
	 * @param d dispatch function.
	 */
	udp_listener(io_service& io,
		     uint16 buff_size,
		     ip::udp ipv,
		     const char *ip,
		     uint16 port,
		     dispatch_t &d);

	/**
	 * Start UDP listener socket.
	 */
	void start();

	/**
	 * Handle completion of an asynchronous accept operation.
	 *
	 * @param buff input message bytes.
	 * @param rbytes number of bytes of the input message.
	 * @param error error code.
	 */
	void handle_receive(buffer<uint8>& buff,
			    size_t rbytes,
			    const boost::system::error_code& ec);

protected:
	io_service		&_io;
	ip::udp::socket		 _sock;
	dispatch_t		&_dispatch;
	ip::udp::endpoint	 _rmt_endp;

};

} /* namespace mihf */ } /* namespace odtone */

#endif
