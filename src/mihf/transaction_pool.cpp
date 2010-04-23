//
// Copyright (c) 2007-2009 2009 Universidade Aveiro - Instituto de
// Telecomunicacoes Polo Aveiro
// This file is part of ODTONE - Open Dot Twenty One.
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//
// Author:     Simao Reis <sreis@av.it.pt>
//

///////////////////////////////////////////////////////////////////////////////
#include "transaction_pool.hpp"
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

transaction_pool::transaction_pool(io_service &io)
	: _timer(io, boost::posix_time::seconds(1)),
	  _dst_mutex(),
	  _src_mutex()
{
	// start timer
	_timer.expires_at(_timer.expires_at() + boost::posix_time::seconds(1));
	_timer.async_wait(boost::bind(&transaction_pool::tick, this));
}

template <class Set, class SetIterator>
void transaction_pool::dec(Set &set,
			    SetIterator &it,
			    boost::mutex &mutex)
{
	Set del_these;

	{
		boost::mutex::scoped_lock lock(mutex);

		for(it = set.begin(); it != set.end(); it++) {

			(*it)->transaction_stop_when--;
			if ((*it)->transaction_stop_when == 0) {
				(*it)->run();

				if ((*it)->transaction_status == ONGOING)
					del_these.insert(*it);
			}

			if ((*it)->start_ack_requestor) {
				(*it)->retransmission_when--;
				if ((*it)->retransmission_when == 0) {
					(*it)->ack_requestor();
					(*it)->run();
				}
			}

			if ((*it)->transaction_status != ONGOING)
				del_these.insert(*it);
		}
	}

	// delete finished transactions
	for (it = del_these.begin(); it != del_these.end(); it++)
		del(*it);
}

void transaction_pool::tick()
{
	_timer.expires_at(_timer.expires_at() + boost::posix_time::seconds(1));
	_timer.async_wait(boost::bind(&transaction_pool::tick, this));

	src_transaction_set::iterator src_it;
	if (_src.size() > 0)
		dec(_src, src_it, _src_mutex);

	dst_transaction_set::iterator dst_it;
	if (_dst.size() > 0)
		dec(_dst, dst_it, _dst_mutex);
}


void transaction_pool::add(src_transaction_ptr &t)
{
	boost::mutex::scoped_lock lock(_src_mutex);
	_src.insert(t);
}

void transaction_pool::add(dst_transaction_ptr &t)
{
	boost::mutex::scoped_lock lock(_dst_mutex);
	_dst.insert(t);
}

void transaction_pool::del(const src_transaction_ptr &t)
{
	boost::mutex::scoped_lock lock(_src_mutex);
	_src.erase(t);
}

void transaction_pool::del(const dst_transaction_ptr &t)
{
	boost::mutex::scoped_lock lock(_dst_mutex);
	_dst.erase(t);
}

void transaction_pool::find(const mih::id &id, uint16 tid, src_transaction_ptr &t)
{
	boost::mutex::scoped_lock lock(_src_mutex);
	src_transaction_set::iterator it;

	for(it = _src.begin(); it != _src.end(); it++) {
		if(((*it)->peer_mihf_id == id) && (*it)->tid == tid) {
			t = *it;
			return;
		}
        }
}

void transaction_pool::find(const mih::id &id, uint16 tid, dst_transaction_ptr &t)
{
	boost::mutex::scoped_lock lock(_dst_mutex);
	dst_transaction_set::iterator it;

	for(it = _dst.begin(); it != _dst.end(); it++) {
		if(((*it)->peer_mihf_id == id) && (*it)->tid == tid) {
			t = *it;
			return;
		}
        }
}


} /* namespace mihf */ } /* namespace odtone */
