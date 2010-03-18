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


#ifndef DST_TRANSACTION_HPP
#define DST_TRANSACTION_HPP

///////////////////////////////////////////////////////////////////////////////
#include "transaction.hpp"

#include <boost/shared_ptr.hpp>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {


enum dst_transaction_state_t
	{
        DST_INIT,
        DST_WAIT_RESPONSE_PRM,
        DST_SEND_RESPONSE,
        DST_FAILURE,
        DST_SUCCESS
	};

class dst_transaction_t
	: public transaction_t
{
public:
	dst_transaction_t();

	void run();

	dst_transaction_state_t state;
};

typedef boost::shared_ptr< dst_transaction_t > dst_transaction_ptr;

typedef std::set<dst_transaction_ptr,
		 transaction_compare<dst_transaction_ptr > >dst_transaction_set;

  } /* namespace mihf */
} /* namespace odtone */


#endif
