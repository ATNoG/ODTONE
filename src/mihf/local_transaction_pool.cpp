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

void local_transaction_pool::add(mih::message_ptr& in)
{
	pending_transaction p;

	p.user.assign(in->source().to_string());
	p.destination.assign(in->destination().to_string());
	p.tid = in->tid();

	log(3, "(local transactions) added transaction ", p.user, ":",
	    p.destination, ":", p.tid);

	_transactions.push_back(p);
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

bool local_transaction_pool::get(const mih::octet_string &from,
				 pending_transaction &p)
{
	std::list<pending_transaction>::iterator it;
	it = find(from);

	if (it != _transactions.end()) {
		p = *it;
		_transactions.erase(it);

		return true;
	}

	return false;
}

} /* namespace mihf */ } /* namespace odtone */
