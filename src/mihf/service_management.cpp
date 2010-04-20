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
				       transmit &t,
	bool enable_broadcast)
	: _lpool(lpool),
	  _transmit(t)
{
	_enable_broadcast = enable_broadcast;
}

bool set_capability_discover_response(meta_message_ptr &in, meta_message_ptr &out)
{
	log(1, "(mism) setting response to broadcast Capability_Discover.request ");

	*out << mih::response(mih::response::capability_discover)
		& mih::tlv_status(mih::status_success)
		& mih::tlv_net_type_addr_list(capabilities_list_net_type_addr)
		& mih::tlv_event_list(capabilities_event_list);

	out->tid(in->tid());
	out->destination(in->source());
	out->source(mihfid);

	return true;
}


bool service_management::capability_discover_request(meta_message_ptr& in,
						     meta_message_ptr& out)
{
	log(1, "(mism) received Capability_Discover.request from ",
	    in->source().to_string(), " with destination ",
	    in->destination().to_string());

	// user requested broadcasting of a capability discover
	if (utils::is_multicast(in) && in->is_local()) {
		// piggyback
		log(4, "(mism) piggybacking capability discover in broadcast");
		*in << mih::request(mih::request::capability_discover)
			& mih::tlv_status(mih::status_success)
			& mih::tlv_net_type_addr_list(capabilities_list_net_type_addr)
			& mih::tlv_event_list(capabilities_event_list);

		utils::forward_request(in, _lpool, _transmit);
		return false;
	// destination mihf identifier is this mihf
	} else if (utils::this_mihf_is_destination(in)) {
		return set_capability_discover_response(in, out);
	// message was broadcasted?
	} else if (utils::is_multicast(in)) {
		if (_enable_broadcast) {
			return set_capability_discover_response(in, out);
		} else {
			log(3, "(mism) response to broadcast Capability_Discover.request disabled ");
			return false;
		}
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
	if (_lpool.set_user_tid(in)) {
		log(1, "forwarding Capability_Discover.response to ",
		    in->destination().to_string());
		_transmit(in);
		return false;
	}

	// set source id to broadcast id and check if there's a
	// broadcast request from a user
	in->source(mih::id(""));
	if (_lpool.set_user_tid(in))  {
		log(1, "forwarding Capability_Discover.response to ",
		    in->destination().to_string());
		_transmit(in);
		return false;
	}

	log(1, "no pending transaction for this message, discarding");
	return false;
}


} /* namespace mihf */ } /* namespace odtone */
