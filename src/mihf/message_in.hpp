//==============================================================================
// Brief   : Message IN
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
 * The message_in checks the transaction_pool for a pending transaction for the
 * incoming message, or if a new source transaction must be created and then
 * added to the transaction pool. Then proceeds to run the newly created, or
 * found, transaction.
 */
class message_in
{
public:
	/**
	 * Message IN constructor.
	 *
	 * @param tpool transaction pool module.
	 * @param f process message handler.
	 * @param netsap netsap module.
	 */
	message_in(transaction_pool &tpool, handler_t &f, net_sap &netsap);

	/**
	 * The message_in checks the transaction_pool for a pending transaction for the
	 * incoming message, or if a new source transaction must be created and then
	 * added to the transaction pool. Then proceeds to run the newly created, or
	 * found, transaction.
	 *
	 * @param m input message.
	 */
	void operator()(meta_message_ptr& msg);

protected:
	/**
	 * Create a new destination transaction for the incoming message.
	 *
	 * @param m input message.
	 */
	void new_dst_transaction(meta_message_ptr& msg);

	transaction_pool &_tpool;
	handler_t &process_message;
	net_sap &_netsap;
};

} /* namespace mihf */ } /* namespace odtone */


#endif
