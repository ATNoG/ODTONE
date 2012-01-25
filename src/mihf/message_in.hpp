//==============================================================================
// Brief   : Message IN
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

#ifndef ODTONE_MIHF_MESSAGE_IN__HPP
#define ODTONE_MIHF_MESSAGE_IN__HPP

///////////////////////////////////////////////////////////////////////////////
#include "transaction_pool.hpp"
#include "utils.hpp"
#include "net_sap.hpp"
#include "meta_message.hpp"

#include <odtone/debug.hpp>

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

/**
 * This class manages the incoming messages.
 */
class message_in
{
public:
	/**
	 * Construct a message input module.
	 *
	 * @param tpool The transaction pool module.
	 * @param f The message handler.
	 * @param netsap The netsap module.
	 */
	message_in(transaction_pool &tpool, handler_t &f, net_sap &netsap);

	/**
	 * Checks, in the transaction pool, if the incoming message belongs to a pending
	 * transaction. If true it runs the transaction, otherwise it creates a new
	 * transaction.
	 *
	 * @param msg The output message.
	 */
	void operator()(meta_message_ptr& msg);

protected:
	/**
	 * Create a new destination transaction for the incoming message.
	 *
	 * @param msg The input message.
	 */
	void new_dst_transaction(meta_message_ptr& msg);

	transaction_pool &_tpool;	/**< The transaction pool module.	*/
	handler_t &process_message;	/**< The message handler.			*/
	net_sap &_netsap;			/**< The netsap module.				*/
};

} /* namespace mihf */ } /* namespace odtone */


#endif
