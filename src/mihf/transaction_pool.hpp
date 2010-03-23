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

class transaction_pool
	: private boost::noncopyable
{
public:
	transaction_pool(io_service &io);

	void add(src_transaction_ptr &t);
	void add(dst_transaction_ptr &t);

	void del(const src_transaction_ptr &t);
	void del(const dst_transaction_ptr &t);

	void find(const mih::id &id, uint16 tid, src_transaction_ptr &t);
	void find(const mih::id &id, uint16 tid, dst_transaction_ptr &t);
private:
	void tick();

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
