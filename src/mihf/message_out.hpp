//==============================================================================
// Brief   : Message OUT
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

#ifndef ODTONE_MIHF_MESSAGE_OUT__HPP
#define ODTONE_MIHF_MESSAGE_OUT__HPP

///////////////////////////////////////////////////////////////////////////////
#include "transaction_pool.hpp"
#include "net_sap.hpp"
#include "meta_message.hpp"

#include <odtone/base.hpp>
#include <odtone/debug.hpp>

#include <boost/noncopyable.hpp>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

/**
 * This class checks, in the transaction pool, if the outgoing message belongs to a pending
 * transaction, if so the transaction is run and eventually the message is sent.
 */
class message_out
{
public:
	/**
	 * Message OUT constructor.
	 *
	 * @param tpool transaction pool module.
	 * @param f process message handler.
	 * @param netsap netsap module.
	 */
	message_out(transaction_pool &tpool, handler_t &f, net_sap &netsap);

	/**
	 * Checks, in the transaction pool, if the outgoing message belongs to a pending
	 * transaction, if so the transaction is run and eventually the message is sent.
	 *
	 * @param m output message.
	 */
	void operator()(meta_message_ptr& msg);

protected:
	/**
	 * Create a new source transaction for the outgoing message.
	 *
	 * @param m output message.
	 */
	void new_src_transaction(meta_message_ptr& msg);

	transaction_pool &_tpool;
	uint16 _tid;
	handler_t &process_message;
	net_sap &_netsap;
};

} /* namespace mihf */ } /* namespace odtone */


#endif
