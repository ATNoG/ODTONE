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

#include <odtone/debug.hpp>
#include <odtone/buffer.hpp>
#include <odtone/mih/message.hpp>

#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>

#include "transaction.hpp"
#include "src_transaction.hpp"
#include "dst_transaction.hpp"

namespace odtone { namespace mihf {

extern boost::asio::io_service io_service;

class generic_server
	: private boost::noncopyable
{
public:
	// bind to @ip and @port and create @num_threads for processing messages
	generic_server(boost::asio::io_service& io);
	~generic_server();

	void init(const char *ip, const uint16 port, uint concurrency);

	// Send message @msg to @port @ip
	void send_to(mih::message_ptr& msg, const char *ip, uint16 port);

	boost::asio::io_service& get_io_service();

protected:


	// Handle completion of an asynchronous accept operation
	void handle_receive(buffer<uint8>& buff,
						size_t rbytes,
						const boost::system::error_code& ec);

	virtual void process_message(mih::message_ptr& msg) = 0;


	// Used to listen for incoming messages
	boost::asio::ip::udp::socket _sock;
};

} /* namespace mihf */ } /* namespace odtone */

#endif
