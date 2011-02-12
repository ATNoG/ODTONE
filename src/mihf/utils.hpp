//==============================================================================
// Brief   : Utilities
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

/**
 * Send a message using a TCP socket.
 *
 * @param io io_service.
 * @param msg output message.
 * @param ip destination IP Address.
 * @param port destination port.
 */
void tcp_send(boost::asio::io_service &io,
	      meta_message_ptr &msg,
	      const char *ip,
	      uint16 port);

/**
 * Send a message using a UDP socket.
 *
 * @param io io_service.
 * @param msg output message.
 * @param ip destination IP Address.
 * @param port destination port.
 */
void udp_send(boost::asio::io_service &io,
	      meta_message_ptr &msg,
	      const char *ip,
	      uint16 port);

/**
 * Forward request to its destination.
 *
 * @param in MIH Message to forward.
 * @param lpool local transaction pool module.
 * @param t transmit module.
 */
void forward_request(meta_message_ptr &in,
		     local_transaction_pool &lpool,
		     transmit &t);

/**
 * Check if the message destination is this MIHF.
 *
 * @param msg MIH Message.
 * @return true if this MIHF is the message destination or false otherwise.
 */
bool this_mihf_is_destination(meta_message_ptr &msg);

/**
 * Check if the message is a multicast message.
 *
 * @param msg MIH Message.
 * @return true if this is a multicast message or false otherwise.
 */
bool is_multicast(meta_message_ptr &msg);


} /* namespace utils */ } /* namespace mihf */ } /* namespace odtone */

#endif
