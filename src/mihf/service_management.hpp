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

#ifndef ODTONE_MIHF_SERVICE_MANAGEMENT_HPP
#define ODTONE_MIHF_SERVICE_MANAGEMENT_HPP

///////////////////////////////////////////////////////////////////////////////
#include "local_transaction_pool.hpp"

#include <odtone/base.hpp>
#include <odtone/mih/types.hpp>
#include <odtone/mih/message.hpp>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {


class service_management {
public:
	service_management(local_transaction_pool &lpool);

	bool capability_discover_request(mih::message_ptr &in,
					 mih::message_ptr &out);
	bool capability_discover_response(mih::message_ptr&in,
					  mih::message_ptr &out);

private:
	local_transaction_pool &_lpool;
};

} /* namespace mihf */ } /* namespace odtone */

#endif
