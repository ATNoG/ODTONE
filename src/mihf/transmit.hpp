//==============================================================================
// Brief   : Transmit
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
 * This class is used by the MIHFs services to send a message.
 */
class transmit
	: private boost::noncopyable
{
public:
	/**
	 * Construct a transmit module.
	 *
	 * @param io The io_service object that transmit module will use to
	 * dispatch handlers for any asynchronous operations performed on
	 * the socket.
	 * @param user_abook The user book module.
	 * @param link_abook The link book module.
	 * @param msg_out The output message.
	 * @param port Port used to send the messages.
	 */
	transmit(io_service &io,
			 user_book &user_abook,
			 link_book &link_abook,
			 message_out &msg_out,
			 uint16 port);

	/**
	 * Send message to a local entity. If the output message destination is a peer
	 * MIHF redirect it to the message_out module.
	 *
	 * @param msg The output message.
	 */
	void operator()(meta_message_ptr& msg);

private:
	io_service &_io;		/**< The io_service object.				*/
	user_book &_user_abook;	/**< The user book module.				*/
	link_book &_link_abook;	/**< The link book module.				*/
	message_out &_msg_out;	/**< The message output module.			*/
	uint16 _port;			/**< Port used to send the messages.	*/
};

} /* namespace mihf */ } /* namespace odtone */

#endif
