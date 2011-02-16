//==============================================================================
// Brief   : Transaction Pool
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
 * This class allows to store a pool of active transactions.
 */
class transaction_pool
	: private boost::noncopyable
{
public:
	/**
	 * Constructor for Transaction Pool.
	 *
	 * @param io io_service.
	 */
	transaction_pool(io_service &io);

	/**
	 * Add a new source transaction entry in the transaction pool.
	 *
	 * @param t source transaction pointer.
	 */
	void add(src_transaction_ptr &t);

	/**
	 * Add a new destination transaction entry in the transaction pool.
	 *
	 * @param t destination transaction pointer.
	 */
	void add(dst_transaction_ptr &t);

	/**
	 * Remove a existing source transaction entry from the transaction pool.
	 *
	 * @param t source transaction pointer.
	 */
	void del(const src_transaction_ptr &t);

	/**
	 * Remove a existing destination transaction entry from the transaction pool.
	 *
	 * @param t destination transaction pointer.
	 */
	void del(const dst_transaction_ptr &t);

	/**
	 * Find the source transaction of a given MIHF ID and transaction ID
	 * in the transaction pool.
	 *
	 * @param id MIHF MIH Identifier.
	 * @param tid Transaction ID.
	 * @param t source transaction pointer.
	 */
	void find(const mih::id &id, uint16 tid, src_transaction_ptr &t);

	/**
	 * Find the destination transaction of a given MIHF ID and transaction ID
	 * in the transaction pool.
	 *
	 * @param id MIHF MIH Identifier.
	 * @param tid Transaction ID.
	 * @param t destination transaction pointer.
	 */
	void find(const mih::id &id, uint16 tid, dst_transaction_ptr &t);
private:
	/**
	 * Decrements each transaction timer that exist in the transaction pool. This is
	 * set in response to a regular one-second tick.
	 */
	void tick();

	/**
	 * This procedure decrements the timer of each transaction only if its value is
	 * greater than 0.
	 *
	 * @param set transaction type.
	 * @param it transaction.
	 * @param mutex mutex.
	 */
	template <class Set, class SetIterator>
	void dec(Set &set, SetIterator &it, boost::mutex &mutex);

	boost::asio::deadline_timer _timer;

	boost::mutex            _dst_mutex;
	boost::mutex            _src_mutex;

	dst_transaction_set     _dst;
	src_transaction_set     _src;
};

} /* namespace mihf */ } /* namespace odtone */

#endif
