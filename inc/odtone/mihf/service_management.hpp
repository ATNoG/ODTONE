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

#include <odtone/base.hpp>
#include <odtone/mih/types.hpp>
#include <odtone/mih/message.hpp>

namespace odtone { namespace mihf {

//
extern mih::event_list			capabilities_event_list;
extern mih::net_type_addr_list  capabilities_list_net_type_addr;
//

class service_management {
public:
	bool capability_discover_request(mih::message_ptr &in, mih::message_ptr &out);
	bool capability_discover_response(mih::message_ptr&in, mih::message_ptr &out);

};

} /* namespace mihf */ } /* namespace odtone */

#endif
