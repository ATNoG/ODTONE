//==============================================================================
// Brief   : Transaction Pool
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

#ifndef ODTONE_MIHF_TRANSACTION_POOL__HPP
#define ODTONE_MIHF_TRANSACTION_POOL__HPP

///////////////////////////////////////////////////////////////////////////////
#include "dst_transaction.hpp"
#include "src_transaction.hpp"

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>
///////////////////////////////////////////////////////////////////////////////

using namespace boost::asio;

namespace odtone { namespace mihf {

/**
 * This class allows to store active remote transactions.
 */
class transaction_pool
	: private boost::noncopyable
{
public:
	/**
	 * Construct a transaction pool.
	 *
	 * @param io The io_service object that transaction pool module will
	 * use to dispatch handlers for any asynchronous operations performed on
	 * the socket.
	 */
	transaction_pool(io_service &io);

	/**
	 * Add a new source transaction entry in the transaction pool.
	 *
	 * @param t The source transaction pointer.
	 */
	void add(src_transaction_ptr &t);

	/**
	 * Add a new destination transaction entry in the transaction pool.
	 *
	 * @param t The destination transaction pointer.
	 */
	void add(dst_transaction_ptr &t);

	/**
	 * Remove an existing source transaction entry from the transaction pool.
	 *
	 * @param t The source transaction pointer to be removed.
	 */
	void del(const src_transaction_ptr &t);

	/**
	 * Remove a existing destination transaction entry from the transaction pool.
	 *
	 * @param t destination transaction pointer to be removed.
	 */
	void del(const dst_transaction_ptr &t);

	/**
	 * Searchs for a source transaction in the transaction pool.
	 *
	 * @param id The MIH destination identifier to search for.
	 * @param tid The transaction identifier to search for.
	 * @param t The source transaction pointer.
	 */
	void find(const mih::id &id, uint16 tid, src_transaction_ptr &t);

	/**
	 * Searchs for a destination transaction in the transaction pool.
	 *
	 * @param id The MIH source identifier to search for.
	 * @param tid The transaction identifier to search for.
	 * @param t The destination transaction pointer.
	 */
	void find(const mih::id &id, uint16 tid, dst_transaction_ptr &t);
private:
	/**
	 * Decrements each transaction timer existente in the transaction pool.
	 */
	void tick();

	/**
	 * Decrements the timer of each transaction only if its value is
	 * greater than 0.
	 *
	 * @param set The transaction type.
	 * @param it The transaction.
	 * @param mutex The mutex.
	 */
	template <class Set, class SetIterator>
	void dec(Set &set, SetIterator &it, boost::mutex &mutex);

	boost::asio::deadline_timer _timer;	/**< Transaction decrement timer.	*/

	boost::mutex            _dst_mutex;	/**< Destination mutex.	*/
	boost::mutex            _src_mutex;	/**< Source mutex.		*/

	dst_transaction_set     _dst;		/**< List of active source transactions.	*/
	src_transaction_set     _src;		/**< List of active source transactions.	*/
};

} /* namespace mihf */ } /* namespace odtone */

#endif
