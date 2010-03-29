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

#ifndef ODTONE_MIHF_MESSAGE_IN__HPP
#define ODTONE_MIHF_MESSAGE_IN__HPP

///////////////////////////////////////////////////////////////////////////////
#include "transaction_pool.hpp"
#include "utils.hpp"
#include "net_sap.hpp"
#include "meta_message.hpp"

#include <odtone/debug.hpp>

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

class message_in
{
public:
	message_in(transaction_pool &tpool, handler_t &f, net_sap &netsap);

	void operator()(meta_message_ptr& msg);

protected:
	void new_dst_transaction(meta_message_ptr& msg);

	transaction_pool &_tpool;
	handler_t &process_message;
	net_sap &_netsap;
};

} /* namespace mihf */ } /* namespace odtone */


#endif
