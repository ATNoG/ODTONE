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


struct pending_transaction
{
	mih::octet_string	user;
	mih::octet_string	destination;
	uint16              tid;
	bool                ack;
};

class local_transaction_pool
{
public:
	local_transaction_pool();

	void add(meta_message_ptr& in);
	void del(const mih::octet_string user, uint16 tid);

	std::list<pending_transaction>::iterator
	find(const mih::octet_string &from);

	bool set_user_tid(meta_message_ptr &msg);

protected:
	std::list<pending_transaction> _transactions;
	boost::mutex _mutex;
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace mihf */ } /* namespace odtone */


#endif
