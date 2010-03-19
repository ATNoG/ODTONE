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

#ifndef ODTONE_MIHF_MESSAGE_OUT__HPP
#define ODTONE_MIHF_MESSAGE_OUT__HPP

///////////////////////////////////////////////////////////////////////////////
#include "transaction_pool.hpp"

#include <odtone/debug.hpp>
#include <odtone/mih/message.hpp>

#include <boost/noncopyable.hpp>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

class message_out
	: private boost::noncopyable
{
public:
	message_out(transaction_pool &tpool);

	void operator()(mih::message_ptr& msg);

protected:
	void new_src_transaction(mih::message_ptr& msg);

	transaction_pool &_tpool;
	uint16 _tid;
};

} /* namespace mihf */ } /* namespace odtone */


#endif
