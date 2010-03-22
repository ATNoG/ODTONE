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
#include <odtone/base.hpp>
#include <odtone/mih/message.hpp>
#include <odtone/mih/types.hpp>

#include <boost/function.hpp>
#include <boost/bind.hpp>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

//
//
typedef boost::function<bool (mih::message_ptr&, mih::message_ptr&)> handler_t;

namespace utils {

void tcp_send(boost::asio::io_service &io, mih::message_ptr &msg, const char *ip, uint16 port);
void udp_send(boost::asio::io_service &io, mih::message_ptr &msg, const char *ip, uint16 port);

bool is_local_request(mih::message_ptr &in);

// A user sent a MIH request message, set the MIH source field and
// forward the message to the required destination.
bool forward_request(mih::message_ptr &in);

} /* namespace utils */ } /* namespace mihf */ } /* namespace odtone */

#endif
