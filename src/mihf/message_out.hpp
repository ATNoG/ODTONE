//==============================================================================
// Brief   : Message OUT
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

#ifndef ODTONE_MIHF_MESSAGE_OUT__HPP
#define ODTONE_MIHF_MESSAGE_OUT__HPP

///////////////////////////////////////////////////////////////////////////////
#include "transaction_pool.hpp"
#include "local_transaction_pool.hpp"
#include "net_sap.hpp"
#include "meta_message.hpp"

#include <odtone/base.hpp>
#include <odtone/debug.hpp>

#include <boost/noncopyable.hpp>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

/**
 * This class manages the outgoing messages.
 */
class message_out
{
public:
	/**
	 * Construct a message output module.
	 *
	 * @param tpool The transaction pool module.
	 * @param lpool The local transaction pool module.
	 * @param f The message handler.
	 * @param netsap The netsap module.
	 */
	message_out(transaction_pool &tpool, local_transaction_pool &lpool,
	            handler_t &f, net_sap &netsap);

	/**
	 * Checks, in the transaction pool, if the outgoing message belongs to a pending
	 * transaction. If true it runs the transaction, otherwise it creates a new
	 * transaction.
	 *
	 * @param msg The output message.
	 */
	void operator()(meta_message_ptr& msg);

protected:
	/**
	 * Creates a new source transaction for the outgoing message.
	 *
	 * @param msg The output message.
	 */
	void new_src_transaction(meta_message_ptr& msg);

	transaction_pool &_tpool;		/**< The transaction pool module.			*/
	local_transaction_pool &_lpool;	/**< The transaction pool module.			*/
	uint16 _tid;					/**< The current transaction identifier.	*/
	handler_t &process_message;		/**< The message handler.					*/
	net_sap &_netsap;				/**< The netsap module.						*/
};

} /* namespace mihf */ } /* namespace odtone */


#endif
