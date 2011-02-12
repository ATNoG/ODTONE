//==============================================================================
// Brief   : Transmit
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

#ifndef ODTONE_MIHF_TRANSMIT_HPP
#define ODTONE_MIHF_TRANSMIT_HPP

///////////////////////////////////////////////////////////////////////////////
#include "link_book.hpp"
#include "user_book.hpp"
#include "message_out.hpp"
#include "meta_message.hpp"

#include <odtone/base.hpp>
#include <odtone/debug.hpp>

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
///////////////////////////////////////////////////////////////////////////////

using namespace boost::asio;

namespace odtone { namespace mihf {

/**
 * This class is used by the MIHFs services and checks if the MIH destination
 * identifier of the message is in the local address book. If it is, the message
 * is for a local SAP and the udp_send method is called to send the message. If
 * it's not in the local address book the message is forwarded to the message_out.
 */
class transmit
	: private boost::noncopyable
{
public:
	/**
	 * Transmit module constructor.
	 *
	 * @param io io_service.
	 * @param user_abook user book module.
	 * @param link_abook link book module.
	 * @param msg_out output message.
	 */
	transmit(io_service &io,
			 user_book &user_abook,
			 link_book &link_abook,
			 message_out &msg_out);

	/**
	 * Send message to a local entity. If the output message destination is a peer
	 * MIHF redirect it to the message_out module.
	 *
	 * @param msg output message.
	 */
	void operator()(meta_message_ptr& msg);

private:
	io_service &_io;
	user_book &_user_abook;
	link_book &_link_abook;
	message_out &_msg_out;

};

} /* namespace mihf */ } /* namespace odtone */

#endif
