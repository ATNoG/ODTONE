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

#ifndef SRC_TRANSACTION_HPP
#define SRC_TRANSACTION_HPP

#include "transaction.hpp"

namespace odtone { namespace mihf {

enum src_transaction_state_t
	{
        SRC_INIT,
        SRC_WAIT_RESPONSE_MSG,
        SRC_PROCESS_MSG,
        SRC_WAIT_ACK,
        SRC_FAILURE,
        SRC_SUCCESS
	};


class src_transaction_t
	: public transaction_t
{
public:
	src_transaction_t();
	void dump();

	src_transaction_state_t state;
};


typedef boost::shared_ptr< src_transaction_t > src_transaction_ptr;

typedef std::set<src_transaction_ptr,
				 transaction_compare<src_transaction_ptr > >src_transaction_set;

  } /* namespace mihf */
} /* namespace odtone */

#endif
