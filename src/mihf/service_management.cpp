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
#include "service_management.hpp"

#include "log.hpp"
#include "utils.hpp"
#include "mihfid.hpp"
#include "transmit.hpp"

#include <odtone/mih/types/capabilities.hpp>
#include <odtone/mih/request.hpp>
#include <odtone/mih/response.hpp>
#include <odtone/mih/tlv_types.hpp>
///////////////////////////////////////////////////////////////////////////////

// TODO: request from link sap
extern odtone::mih::event_list		capabilities_event_list;
extern odtone::mih::net_type_addr_list  capabilities_list_net_type_addr;

namespace odtone { namespace mihf {

service_management::service_management(local_transaction_pool &lpool,
				       transmit &t)
	: _lpool(lpool),
	  _transmit(t)
{
}


bool service_management::capability_discover_request(meta_message_ptr& in,
						     meta_message_ptr& out)
{
	log(1, "(mism) received Capability_Discover.request from ",
	    in->source().to_string(), " with destination ",
	    in->destination().to_string());

	if (utils::is_local_request(in)) {
		*out << mih::response(mih::response::capability_discover)
			& mih::tlv_status(mih::status_success)
			& mih::tlv_net_type_addr_list(capabilities_list_net_type_addr)
			& mih::tlv_event_list(capabilities_event_list);

		out->tid(in->tid());
		out->destination(in->source());
		out->source(mihfid);

		return true;
	} else {
		utils::forward_request(in, _lpool, _transmit);
		return false;
	}

	return false;
}


bool service_management::capability_discover_response(meta_message_ptr &in,
						      meta_message_ptr &)
{
	log(1, "received Capability_Discover.response from ",
	    in->source().to_string());

	// do we have a request from a user?
	pending_transaction p;
	if (!_lpool.get(in->source().to_string(), p)) {
		log(1, "no pending transaction for this message, discarding");
		return false;
	}

	log(1, "forwarding Capability_Discover.response to ", p.user);

	in->tid(p.tid);
	in->destination(mih::id(p.user));

	_transmit(in);

	return false;
}


} /* namespace mihf */ } /* namespace odtone */
