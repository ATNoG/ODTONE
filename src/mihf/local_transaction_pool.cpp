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
#include "local_transaction_pool.hpp"
#include "log.hpp"
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

local_transaction_pool::local_transaction_pool()
{
}

void local_transaction_pool::add(meta_message_ptr& in)
{
	pending_transaction p;

	p.user.assign(in->source().to_string());
	p.destination.assign(in->destination().to_string());
	p.tid = in->tid();
	p.ack = in->ackreq();

	log(3, "(local transactions) added transaction ", p.user, ":",
	    p.destination, ":", p.tid, ":", p.ack);

	{
		boost::mutex::scoped_lock lock(_mutex);
		_transactions.push_back(p);
	}
}

void local_transaction_pool::del(const mih::octet_string user,
                                 uint16 tid)
{
	std::list<pending_transaction>::iterator it;
	it = find(user);

	if (it != _transactions.end()) {
		if(it->tid == tid) {
			boost::mutex::scoped_lock lock(_mutex);
			_transactions.erase(it);
		}
	}
}

std::list<pending_transaction>::iterator
local_transaction_pool::find(const mih::octet_string &from)
{
	std::list<pending_transaction>::iterator it;

	for(it = _transactions.begin(); it != _transactions.end(); it++) {
		if (it->destination == from)
			break;
	}
	return it;
}

// check if there's a pending transaction with the msg's mih source
// identifier and set the transaction id and destination appropriately
bool local_transaction_pool::set_user_tid(meta_message_ptr &msg)
{
	boost::mutex::scoped_lock lock(_mutex);

	std::list<pending_transaction>::iterator it;
	it = find(msg->source().to_string());

	if (it != _transactions.end()) {

		msg->tid(it->tid);
		msg->destination(mih::id(it->user));
		msg->ackreq(it->ack);

		_transactions.erase(it);
		return true;
	}

	return false;
}

} /* namespace mihf */ } /* namespace odtone */
