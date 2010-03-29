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

#ifndef ODTONE_MIHF_UTILS_HPP
#define ODTONE_MIHF_UTILS_HPP

///////////////////////////////////////////////////////////////////////////////
#include "transmit.hpp"
#include "local_transaction_pool.hpp"

#include <odtone/base.hpp>
#include "meta_message.hpp"
#include <odtone/mih/types.hpp>

#include <boost/function.hpp>
#include <boost/bind.hpp>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf { namespace utils {

void tcp_send(boost::asio::io_service &io,
	      meta_message_ptr &msg,
	      const char *ip,
	      uint16 port);

void udp_send(boost::asio::io_service &io,
	      meta_message_ptr &msg,
	      const char *ip,
	      uint16 port);

void forward_request(meta_message_ptr &in,
		     local_transaction_pool &lpool,
		     transmit &t);

bool is_local_request(meta_message_ptr &msg);

bool is_multicast(meta_message_ptr &msg);


} /* namespace utils */ } /* namespace mihf */ } /* namespace odtone */

#endif
