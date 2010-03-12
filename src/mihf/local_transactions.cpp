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
#include "local_transactions.hpp"
#include "log.hpp"
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

local_transaction_t *local_transaction_t::ptr_instance = NULL;

local_transaction_t* local_transaction_t::instance()
{
	if (ptr_instance == NULL)
		ptr_instance = new local_transaction_t();

	return ptr_instance;
}

local_transaction_t::local_transaction_t()
{
}

local_transaction_t::~local_transaction_t()
{
	if(ptr_instance)
		delete ptr_instance;
}

void local_transaction_t::add(mih::message_ptr& in)
{
	pending_transaction_t p;

	p.user.assign(in->source().to_string());
	p.destination.assign(in->destination().to_string());
	p.tid = in->tid();

	log(3, "(local transactions) added transaction ", p.user, ":", p.destination, ":", p.tid);

	_pending_transactions.push_back(p);
}

std::list<pending_transaction_t>::iterator
local_transaction_t::find(mih::octet_string &from)
{
	std::list<pending_transaction_t>::iterator it;

	for(it = _pending_transactions.begin();
		it != _pending_transactions.end();
		it++)
		{
			if (it->destination == from)
				break;
		}
	return it;
}

bool local_transaction_t::get(mih::octet_string	&from, pending_transaction_t &p)
{
	std::list<pending_transaction_t>::iterator it;
	it = find(from);

	if (it != _pending_transactions.end())
		{
			p = *it;
			// p.user.assign(it->user);
			// p.destination.assign(it->destination);
			// p.tid = it->tid;
			_pending_transactions.erase(it);

			return true;
		}

	return false;
}

} /* namespace mihf */ } /* namespace odtone */
