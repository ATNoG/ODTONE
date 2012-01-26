//==============================================================================
// Brief   : Netsap
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

#ifndef ODTONE_MIHF_NET_SAP__HPP
#define ODTONE_MIHF_NET_SAP__HPP

///////////////////////////////////////////////////////////////////////////////
#include "address_book.hpp"
#include "meta_message.hpp"

#include <odtone/base.hpp>
#include <odtone/debug.hpp>
#include <odtone/mih/types/capabilities.hpp>

#include <boost/asio.hpp>

using namespace boost::asio;
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

/**
 * This class provides the methods to send the messages to remote MIHFs.
 */
class net_sap
{
public:
	/**
	 * Construct a netsap module.
	 *
	 * @param io The io_service object that netsap module will use to
	 * dispatch handlers for any asynchronous operations performed on
	 * the socket.
	 * @param abook The address book module.
	 * @param port Port used to send the messages.
	 */
	net_sap(io_service &io, address_book &abook, uint16 port);

	/**
	 * Send the message to a peer MIHF.
	 *
	 * @param msg The output message.
	 */
	void send(meta_message_ptr &msg);
private:
	io_service &_io;		/**< The io_service object.				*/
	address_book &_abook;	/**< The address book module.			*/
	uint16 _port;			/**< Port used to send the messages.	*/
};

} /* namespace mihf */ } /* namespace odtone */

#endif
