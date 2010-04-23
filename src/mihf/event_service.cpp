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

#include "event_service.hpp"

#include "log.hpp"
#include "mihfid.hpp"
#include "transmit.hpp"
#include "utils.hpp"

#include <odtone/debug.hpp>
#include <odtone/mih/request.hpp>
#include <odtone/mih/response.hpp>
#include <odtone/mih/indication.hpp>
#include <odtone/mih/tlv_types.hpp>

///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

event_service::event_service(local_transaction_pool &lpool, transmit &t)
	: _lpool(lpool),
	  _transmit(t)
{
}

// subscribe user to all events, set in the events bitmap, from
// link identifier
mih::status event_service::subscribe(const mih::id &user,
				     mih::link_tuple_id &link,
				     mih::event_list &events)
{
//  TODO: add support for evt_cfg_info

	event_registration_t reg;
	reg.user.assign(user.to_string());
	reg.link = link;

	boost::mutex::scoped_lock lock(_event_mutex);

	for(int i = 0; i < 32; i++) {
		if (events.get((mih::event_list_enum) i)) {
			reg.event = (mih::event_list_enum) i;
			_event_subscriptions.push_back(reg);

			if (link.addr.which() == 1) {
				mih::mac_addr mac =
					boost::get<mih::mac_addr>(link.addr);

				log(3, "(mies) added subscription ", reg.user,
				    ":", mac.address(), ":", reg.event);
			}
		}
	}

	return mih::status_success;
}

// This MIHF is the destination of the
// Event_Subscribe.request. Deserialize the message, subscribe the
// user and send a response
bool event_service::local_event_subscribe_request(meta_message_ptr &in,
						  meta_message_ptr &out)
{
	mih::event_list		events;
	mih::link_tuple_id	link;

	*in >> mih::request(mih::request::event_subscribe)
		& mih::tlv_link_identifier(link)
		& mih::tlv_event_list(events);

	mih::status st = subscribe(in->source(), link, events);

	*out << mih::response(mih::response::event_subscribe)
		& mih::tlv_status(st)
		& mih::tlv_link_identifier(link)
		& mih::tlv_event_list(events);

	out->tid(in->tid());
	out->source(mihfid);
	out->destination(in->source());

	return true;
}

// Check if this MIHF is the destination of the message or if it needs
// to forward the message to a peer MIHF.
bool event_service::event_subscribe_request(meta_message_ptr &in,
					    meta_message_ptr &out)
{
	log(1, "(mies) received Event_Subscribe.request from ",
	    in->source().to_string());

	if (utils::this_mihf_is_destination(in))  {
		return local_event_subscribe_request(in, out);
	} else {
		utils::forward_request(in, _lpool, _transmit);
		return false;
	}

	return false;
}

// A peer MIHF sent a Event_Subscribe.response, check if we have a
// pending transaction with a local user. If so, then add a
// subscription of the user to the link and events that came in the
// response.
bool event_service::event_subscribe_response(meta_message_ptr &in,
					     meta_message_ptr&)
{
	log(1, "(mies) received Event_Subscribe.response from ",
	    in->source().to_string());

	// do we have a request from a user?
	if (!_lpool.set_user_tid(in)) {
		log(1, "(mics) warning: no local transaction for this msg ",
		    "discarding it");
		return false;
	}

	mih::status        st;
	mih::link_tuple_id link;
	mih::event_list    events;
	mih::message       pin;

	// parse incoming message to (event_registration_t) reg
	*in >>  mih::response()
		& mih::tlv_status(st)
		& mih::tlv_link_identifier(link)
		& mih::tlv_event_list(events);

	// add a subscription
	if (st == mih::status_success)
		st = subscribe(mih::id(in->destination().to_string()), link, events);

	log(1, "(mies) forwarding Event_Subscribe.response to ",
	    in->destination().to_string());

	// forward to user
	_transmit(in);

	return false;
}

mih::status event_service::unsubscribe(const mih::id &user,
				       mih::link_tuple_id &link,
				       mih::event_list &events)
{
	boost::mutex::scoped_lock lock(_event_mutex);

	std::list<event_registration_t>::iterator it;

	for(it = _event_subscriptions.begin();
	    it != _event_subscriptions.end();
	    it++) {
		if (it->link == link &&
		    (it->user.compare(user.to_string()) == 0) &&
		    events.get((mih::event_list_enum) it->event)) {
			break;
		}
	}

	if (it != _event_subscriptions.end()) {
		_event_subscriptions.erase(it);
		return mih::status_success;
	}

	return mih::status_failure;
}


// This MIHF is the destination of the Event_Unsubscribe.request.
// Deserialize message, unsubscribe user and send a response
bool event_service::local_event_unsubscribe_request(meta_message_ptr &in,
						    meta_message_ptr &out)
{
	mih::status st;
	mih::link_tuple_id link;
	mih::event_list events;

	*in >> mih::request(mih::request::event_unsubscribe)
		& mih::tlv_link_identifier(link)
		& mih::tlv_event_list(events);

	st = unsubscribe(in->source(), link, events);

	*out << mih::response(mih::response::event_unsubscribe)
		& mih::tlv_status(st)
		& mih::tlv_link_identifier(link)
		& mih::tlv_event_list(events);

	out->tid(in->tid());
	out->destination(in->source());

	return true;
}

// Check if this MIHF is the destination of the request and
// proceed to unsubscribe the source mih identifier or if we need to
// forward the message.
bool event_service::event_unsubscribe_request(meta_message_ptr &in,
					      meta_message_ptr &out)
{
	log(1, "(mies) received Event_Unsubscribe.request from ",
	    in->source().to_string());

	if (utils::this_mihf_is_destination(in)) {
		return local_event_unsubscribe_request(in, out);
	} else {
		utils::forward_request(in, _lpool, _transmit);
		return false;
	}

	return false;
}

// A peer MIHF sent a Event_Unubscribe.response, check if we have a
// pending transaction with a local user. If so, then remove the
// subscription of the user to the link and events that came in the
// response.
bool event_service::event_unsubscribe_response(meta_message_ptr &in,
					       meta_message_ptr &)
{
	log(1, "(mies) received Event_Unsubscribe.response from ",
	    in->source().to_string());

	// do we have a request from a user?
	if (!_lpool.set_user_tid(in)) {
		log(1, "(mics) warning: no local transaction for this msg ",
		    "discarding it");

		return false;
	}

	mih::status		st;
	mih::link_tuple_id	link;
	mih::event_list		events;
	mih::message		pin;

	// parse incoming message to (event_registration_t) reg
	*in >>  mih::response()
		& mih::tlv_status(st)
		& mih::tlv_link_identifier(link)
		& mih::tlv_event_list(events);

	// remove subscription
	if (st == mih::status_success)
		st = unsubscribe(mih::id(in->destination().to_string()), link, events);

	log(1, "(mies) forwarding Event_Unsubscribe.response to ",
	    in->destination().to_string());

	// forward to user
	_transmit(in);

	return false;
}

// send message for all users subscribed to event from link identifier
void event_service::msg_forward(meta_message_ptr &msg,
				mih::link_tuple_id &li,
				mih::event_list_enum event)
{
	std::list<event_registration_t>::iterator it;
	int i = 0; // for logging purposes

	msg->source(mihfid);
	for(it = _event_subscriptions.begin();
	    it != _event_subscriptions.end();
	    it++, i++) {
		if ((it->event == event)  &&(it->link == li)) {
			log(3, i, " (mies) found registration of user: ",
			    it->user, " for event type ", event);
			msg->destination(mih::id(it->user));
			_transmit(msg);
		}
	}
}


// parse link_identifier from incoming message and forward
// message to subscribed users
void event_service::link_event_forward(meta_message_ptr &msg,
				       mih::event_list_enum event)
{
	mih::link_tuple_id li;
	*msg >> mih::response()
		& mih::tlv_link_identifier(li);

	msg_forward(msg, li, event);
}


// log received message type, and forward it
bool event_service::link_up_indication(meta_message_ptr &in, meta_message_ptr&)
{
	// if(in->payload().size() == 0)
	// 	return false;
	log(1, "(mies) received Link_Up.indication from ",
	    in->source().to_string());

	link_event_forward(in, mih::link_up);

	return false;
}


// log received message type, and forward it
bool event_service::link_down_indication(meta_message_ptr &in, meta_message_ptr&)
{
	// if(in->payload().size() == 0)
	// 	return false;
	log(1, "(mies) received Link_Down.indication from ",
	    in->source().to_string());

	link_event_forward(in, mih::link_down);

	return false;
}


// parse link identifiers from list and for each one forward the
// message to the subscribed users
bool event_service::link_detected_indication(meta_message_ptr &in,
					     meta_message_ptr &out)
{
	// if(in->payload().size() == 0)
	// 	return false;

	log(1, "(mies) received Link_Detected.indication from ",
	    in->source().to_string());
	// link detected info from incoming message
	mih::link_det_info_list		list_ids;

	// link detected info on outgoing message
	mih::link_det_info_list		list_rsp;
	mih::link_det_info_list::iterator	it;

	*in >>  mih::response()
		& mih::tlv_link_det_info_list(list_ids);

	for(it = list_ids.begin(); it != list_ids.end(); it++) {
		// construct new link detected indication message
		// with just the link detected in the payload
		list_rsp.push_back(*it);

		*out << mih::indication(mih::indication::link_detected)
			& mih::tlv_link_det_info_list(list_rsp);

		// forward message to subscribed users
		msg_forward(out, it->id, mih::link_detected);

		list_rsp.clear();

		// FIXME: clear out before continuing
	}

	return false;
}


bool event_service::link_going_down_indication(meta_message_ptr &in,
					       meta_message_ptr&)
{
	// if(in->payload().size() == 0)
	// 	return false;
	log(1, "(mies) received Link_Going_Down.indication from ",
	    in->source().to_string());

	link_event_forward(in, mih::link_going_down);

	return false;
}


bool event_service::link_handover_imminent_indication(meta_message_ptr &in,
						      meta_message_ptr&)
{
	// if(in->payload().size() == 0)
	// 	return false;
	log(1, "(mies) received Link_Handover_Imminent.indication from ",
	    in->source().to_string());

	link_event_forward(in, mih::link_handover_imminent);

	return false;
}


bool event_service::link_handover_complete_indication(meta_message_ptr &in,
						      meta_message_ptr&)
{
	// if(in->payload().size() == 0)
	// 	return false;
	log(1, "(mies) received Link_Handover_Complete.indication from ",
	    in->source().to_string());

	link_event_forward(in, mih::link_handover_complete);

	return false;
}


bool event_service::link_pdu_transmit_status_indication(meta_message_ptr &in,
							meta_message_ptr&)
{
	// if(in->payload().size() == 0)
	// 	return false;
	log(1, "(mies) received Link_PDU_Transmit_Status.indication from ",
	    in->source().to_string());

	link_event_forward(in, mih::link_pdu_transmit_status);

	return false;
}

} /* namespace mihf */ } /* namespace odtone */
// EOF ////////////////////////////////////////////////////////////////////////
