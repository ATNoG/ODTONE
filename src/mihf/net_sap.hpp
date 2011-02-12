//==============================================================================
// Brief   : Netsap
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
 * This class, when called, checks if the MIH destination identifier is in the
 * remote address book, if so the message is sent using on of udp_send or tcp_send.
 */
class net_sap
{
public:
	/**
	 * Netsap constructor.
	 *
	 * @param io io_service.
	 * @param abook address_book module.
	 */
	net_sap(io_service &io, address_book &abook);

	/**
	 * Send the message to the peer MIHF.
	 *
	 * @param msg output message.
	 */
	void send(meta_message_ptr &msg);
private:
	io_service &_io;
	address_book &_abook;
};

} /* namespace mihf */ } /* namespace odtone */

#endif
