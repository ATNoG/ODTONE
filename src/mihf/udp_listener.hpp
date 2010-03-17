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

#ifndef GENERIC_SERVER_HPP
#define GENERIC_SERVER_HPP

///////////////////////////////////////////////////////////////////////////////
#include <odtone/debug.hpp>
#include <odtone/buffer.hpp>
#include <odtone/mih/message.hpp>

#include <boost/asio.hpp>
///////////////////////////////////////////////////////////////////////////////

using namespace boost::asio;

namespace odtone { namespace mihf {

class udp_listener
{
public:
	// bind to @ip and @port and create @num_threads for processing messages
	udp_listener(io_service& io, ip::udp ipv, const char *ip, uint16 port);

	void start();

	// Handle completion of an asynchronous accept operation
	void handle_receive(buffer<uint8>& buff,
			    size_t rbytes,
			    const boost::system::error_code& ec);

protected:
	io_service &_io;
	ip::udp::socket _sock;
};

} /* namespace mihf */ } /* namespace odtone */

#endif
