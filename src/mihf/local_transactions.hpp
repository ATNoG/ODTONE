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

#ifndef ODTONE_MIHF_LOCAL_TRANSACTIONS_HPP
#define ODTONE_MIHF_LOCAL_TRANSACTIONS_HPP

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/mih/types.hpp>
#include <odtone/mih/message.hpp>

#include <list>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {


struct pending_transaction_t
{
	mih::octet_string	user;
	mih::octet_string	destination;
	uint16				tid;
};

class local_transaction_t
{
public:
	static local_transaction_t* instance();
	~local_transaction_t();

	void add(mih::message_ptr& in);
	void remove(pending_transaction_t &p);
	std::list<pending_transaction_t>::iterator find(mih::octet_string &from);
	bool get(mih::octet_string &from, pending_transaction_t &p);

protected:
	local_transaction_t();
	static local_transaction_t *ptr_instance;
	std::list<pending_transaction_t> _pending_transactions;
};

#define local_transactions local_transaction_t::instance()

///////////////////////////////////////////////////////////////////////////////
} /* namespace mihf */ } /* namespace odtone */


#endif
