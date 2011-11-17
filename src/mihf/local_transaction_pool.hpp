//==============================================================================
// Brief   : Local Transaction Pool
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

#ifndef ODTONE_MIHF_LOCAL_TRANSACTION_POOL__HPP
#define ODTONE_MIHF_LOCAL_TRANSACTION_POOL__HPP

///////////////////////////////////////////////////////////////////////////////
#include "meta_message.hpp"

#include <odtone/base.hpp>
#include <odtone/mih/types.hpp>

#include <boost/thread.hpp>
#include <list>

///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

/**
 * Struct to store pending transaction informations.
 */
struct pending_transaction
{
	mih::octet_string	user;
	mih::octet_string	destination;
	uint16              tid;
};

/**
 * This class allows to store a pool of active local transactions.
 */
class local_transaction_pool
{
public:
	/**
	 * Local Transaction Pool constructor.
	 */
	local_transaction_pool();

	/**
	 * Add a new local transaction entry in the Local Transaction Pool.
	 *
	 * @param in input message.
	 */
	void add(meta_message_ptr& in);

	/**
	 * Remove a existing local transaction entry from the Local Transaction Pool
	 *
	 * @param id MIH User MIH Identifier.
	 * @param tid MIH Message Transaction ID.
	 */
	void del(const mih::octet_string user, uint16 tid);

	/**
	 * Find a local transaction entry in the Local Transaction Pool
	 *
	 * @param from MIH Identifier.
	 */
	std::list<pending_transaction>::iterator
	find(const mih::octet_string &from);

	/**
	 * Check if there is a pending transaction with the msg's mih source
	 * identifier and set the transaction id and destination appropriately.
	 *
	 * @param msg MIH Message.
	 * @return true if there is a pending transaction or false otherwise.
	 */
	bool set_user_tid(meta_message_ptr &msg);

protected:
	std::list<pending_transaction> _transactions;
	boost::mutex _mutex;
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace mihf */ } /* namespace odtone */


#endif
