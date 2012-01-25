//==============================================================================
// Brief   : Local Transaction Pool
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
 * Struct to store active local transaction.
 */
struct pending_transaction
{
	mih::octet_string	user;			/**< The MIH source identifier.			*/
	mih::octet_string	destination;	/**< The MIH destination identifier.	*/
	uint16              ltid;			/**< The local transaction identifier.		*/
	uint16              rtid;			/**< The remote transaction identifier.		*/
};

/**
 * This class allows to store the active local transactions.
 */
class local_transaction_pool
{
public:
	/**
	 * Construct a Local Transaction Pool.
	 */
	local_transaction_pool();

	/**
	 * Add a new entry in the Local Transaction Pool.
	 *
	 * @param in The input message.
	 */
	void add(meta_message_ptr& in);

	/**
	 * Set the remote transaction identifier related to a given local transaction.
	 *
	 * @param dst The identifier of the destination of the transaction.
	 * @param ltid The local transaction identifier.
	 * @param rtid The remote transaction identifier.
	 */
	void set_remote_tid(const mih::octet_string &dst, const uint16 ltid,
	                    const uint16 rtid);

	/**
	 * Remove an existing entry from the Local Transaction Pool.
	 *
	 * @param id The MIH source identifier.
	 * @param tid The transaction identifier.
	 * @return True if removed or false otherwise.
	 */
	bool del(const mih::octet_string user, uint16 tid);

	/**
	 * Searchs for a record in the Local Transaction Pool.
	 *
	 * @param from The MIH source identifier.
	 * @param tid The MIH transaction identifier.
	 * @return The list of active transaction from the given source.
	 */
	std::list<pending_transaction>::iterator
	find(const mih::octet_string &from, uint16 tid);

	/**
	 * Check the existence of an active transaction. It also set the
	 * MIH destination and the transaction identifier in the given message.
	 *
	 * @param msg The MIH Message.
	 * @return True if there is an active transaction or false otherwise.
	 */
	bool set_user_tid(meta_message_ptr &msg);

protected:
	std::list<pending_transaction> _transactions;	/**< The list of active local transactions.	*/
	boost::mutex _mutex;							/**< The mutex.								*/
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace mihf */ } /* namespace odtone */


#endif
