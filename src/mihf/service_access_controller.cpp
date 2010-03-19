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
#include "service_access_controller.hpp"

#include "log.hpp"
#include "transmit.hpp"

#include <odtone/debug.hpp>
#include <odtone/mih/message.hpp>
#include <odtone/mih/config.hpp>
#include <odtone/mih/request.hpp>
#include <odtone/mih/response.hpp>
#include <odtone/mih/indication.hpp>
///////////////////////////////////////////////////////////////////////////////

#define REGISTER(func, obj, mid) _callbacks[mid] = boost::bind(&func, boost::ref(obj), _1, _2);;

namespace odtone { namespace mihf {

service_access_controller::service_access_controller(service_management &sm,
						     event_service &mies,
						     command_service &mics,
						     information_service &miis)
	: _sm(sm),
	  _mies(mies),
	  _mics(mics),
	  _miis(miis)
{
	//
	//	callbacks for service management messages
	//
	REGISTER(service_management::capability_discover_request, _sm, mih::request::capability_discover);
	REGISTER(service_management::capability_discover_response, _sm, mih::response::capability_discover);

	//
	// callbacks for event service messages
	//
	REGISTER(event_service::event_subscribe_request, _mies,  mih::request::event_subscribe);
	REGISTER(event_service::event_subscribe_response, _mies, mih::response::event_subscribe);
	REGISTER(event_service::link_up_indication, _mies, mih::indication::link_up);
	REGISTER(event_service::link_down_indication, _mies, mih::indication::link_down);
	REGISTER(event_service::link_detected_indication, _mies, mih::indication::link_detected);
	REGISTER(event_service::link_going_down_indication, _mies, mih::indication::link_going_down);
	REGISTER(event_service::link_handover_imminent_indication, _mies, mih::indication::link_handover_imminent);
	REGISTER(event_service::link_handover_complete_indication, _mies, mih::indication::link_handover_complete);
	REGISTER(event_service::event_unsubscribe_request, _mies, mih::request::event_unsubscribe);
	REGISTER(event_service::event_unsubscribe_response, _mies, mih::response::event_unsubscribe);
	// REGISTER(event_service::link_pdu_transmit_status_indication, _mies, mih::indication::link_pdu_transmit_status);

	//
	// callbacks for command service events
	//
	REGISTER(command_service::link_get_parameters_request,_mics, mih::request::link_get_parameters);
	REGISTER(command_service::link_get_parameters_response,_mics, mih::response::link_get_parameters);
	REGISTER(command_service::link_configure_thresholds_request,_mics, mih::request::link_configure_thresholds);
	REGISTER(command_service::link_configure_thresholds_response,_mics, mih::response::link_configure_thresholds);
	REGISTER(command_service::link_actions_request,_mics, mih::request::link_actions);
	REGISTER(command_service::link_actions_response,_mics, mih::response::link_actions);

	REGISTER(command_service::net_ho_candidate_query_request, _mics, mih::request::net_ho_candidate_query);
	REGISTER(command_service::net_ho_candidate_query_response, _mics, mih::response::net_ho_candidate_query);

	REGISTER(command_service::mn_ho_candidate_query_request, _mics, mih::request::mn_ho_candidate_query);
	REGISTER(command_service::mn_ho_candidate_query_response, _mics, mih::response::mn_ho_candidate_query);

	REGISTER(command_service::n2n_ho_query_resources_request, _mics, mih::request::n2n_ho_query_resources);
	REGISTER(command_service::n2n_ho_query_resources_response, _mics, mih::response::n2n_ho_query_resources);

	REGISTER(command_service::mn_ho_commit_request, _mics, mih::request::mn_ho_commit);
	REGISTER(command_service::mn_ho_commit_response, _mics, mih::response::mn_ho_commit);

	REGISTER(command_service::n2n_ho_commit_request, _mics, mih::request::n2n_ho_commit);
	REGISTER(command_service::n2n_ho_commit_response, _mics, mih::response::n2n_ho_commit);

	REGISTER(command_service::n2n_ho_complete_request, _mics, mih::request::n2n_ho_complete);
	REGISTER(command_service::n2n_ho_complete_response, _mics, mih::response::n2n_ho_complete);

	REGISTER(information_service::get_information_request, _miis, mih::request::get_information);
	REGISTER(information_service::get_information_response, _miis, mih::response::get_information);

	REGISTER(information_service::push_information_request, _miis, mih::request::push_information);
	REGISTER(information_service::push_information_indication, _miis, mih::indication::push_information);
}


void service_access_controller::dispatch(mih::message_ptr& in)
{
	/** __no__ authentication at this point */

	uint mid = in->mid();

	log(1, "(sac) dispatching message with mid: ", mid);
	if(_callbacks.find(mid) != _callbacks.end()) {
		handler_t process_message = _callbacks[mid];
		mih::message_ptr out(new mih::message);

		out->tid(in->tid());

		if (process_message(in, out))
			transmit(out);
        } else {
		log(1, "(sac) (warning) message with mid: ", mid, " unknown, discarding.");
	}
}

bool service_access_controller::process(mih::message_ptr& in,
					mih::message_ptr& out)
{
	/** __no__ authentication at this point */

	uint mid = in->mid();

	if (_callbacks.find(mid) != _callbacks.end()) {
		handler_t process_message = _callbacks[mid];

		bool rsp = process_message(in, out);
		out->tid(in->tid());

		return rsp;
        }

	return false;
}

} /* namespace mihf */ } /* namespace odtone */
