//==============================================================================
// Brief   : Event Service
// Authors : Simao Reis <sreis@av.it.pt>
//           Carlos Guimarães <cguimaraes@av.it.pt>
//------------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2009-2011 Universidade Aveiro
// Copyright (C) 2009-2011 Instituto de Telecomunicações - Pólo Aveiro
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//==============================================================================


#ifndef ODTONE_MIHF_EVENT_SERVICE_HPP
#define ODTONE_MIHF_EVENT_SERVICE_HPP

///////////////////////////////////////////////////////////////////////////////
#include "local_transaction_pool.hpp"
#include "link_book.hpp"
#include "transmit.hpp"
#include "meta_message.hpp"

#include <odtone/base.hpp>
#include <odtone/mih/types.hpp>

#include <boost/thread/mutex.hpp>
#include <list>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

/**
 * Struct to store events registrations.
 */
struct event_registration_t
{
	mih::octet_string	user;
	mih::link_tuple_id	link;
	mih::event_list_enum	event;
};

/**
 * This class is responsible for handling the events messages types.
 */
class event_service
	: boost::noncopyable {
public:
	/**
	 * Event service constructor.
	 *
	 * @param lpool local transction pool.
	 * @param t transmit module.
	 * @param link_abook link book.
	 */
	event_service(local_transaction_pool &lpool, transmit &t, link_book &lbook);

	/**
	 * Event Subscribe Request message handler.
	 *
	 * @param in input message.
	 * @param out output message.
	 * @return true if the response is sent immediately or false otherwise.
	 */
	bool event_subscribe_request(meta_message_ptr &in,
				     meta_message_ptr &out);

	/**
	 * Event Subscribe Response message handler.
	 *
	 * @param in input message.
	 * @param out output message.
	 * @return true if the response is sent immediately or false otherwise.
	 */
	bool event_subscribe_response(meta_message_ptr &in,
				      meta_message_ptr &out);

	/**
	 * Event Subscribe Confirm message handler.
	 *
	 * @param in input message.
	 * @param out output message.
	 * @return true if the response is sent immediately or false otherwise.
	 */
	bool event_subscribe_confirm(meta_message_ptr &in,
				     meta_message_ptr &out);

	/**
	 * Event Unsubscribe Request message handler.
	 *
	 * @param in input message.
	 * @param out output message.
	 * @return true if the response is sent immediately or false otherwise.
	 */
	bool event_unsubscribe_request(meta_message_ptr &in,
				       meta_message_ptr &out);

	/**
	 * Event Unsubscribe Response message handler.
	 *
	 * @param in input message.
	 * @param out output message.
	 * @return true if the response is sent immediately or false otherwise.
	 */
	bool event_unsubscribe_response(meta_message_ptr &in,
					meta_message_ptr &out);

	/**
	 * Event Unsubscribe Confirm message handler.
	 *
	 * @param in input message.
	 * @param out output message.
	 * @return true if the response is sent immediately or false otherwise.
	 */
	bool event_unsubscribe_confirm(meta_message_ptr &in,
				       meta_message_ptr &out);

	/**
	 * Link Up Indication message handler.
	 *
	 * @param in input message.
	 * @param out output message.
	 * @return true if the response is sent immediately or false otherwise.
	 */
	bool link_up_indication(meta_message_ptr &in,
				meta_message_ptr &out);

	/**
	 * Link Down Indication message handler.
	 *
	 * @param in input message.
	 * @param out output message.
	 * @return true if the response is sent immediately or false otherwise.
	 */
	bool link_down_indication (meta_message_ptr &in,
				   meta_message_ptr &out);

	/**
	 * Link Detected Indication message handler.
	 *
	 * @param in input message.
	 * @param out output message.
	 * @return true if the response is sent immediately or false otherwise.
	 */
	bool link_detected_indication(meta_message_ptr &in,
				      meta_message_ptr &out);

	/**
	 * Link Going Down Indication message handler.
	 *
	 * @param in input message.
	 * @param out output message.
	 * @return true if the response is sent immediately or false otherwise.
	 */
	bool link_going_down_indication(meta_message_ptr &in,
					meta_message_ptr &out);

	/**
	 * Link Parameters Report Indication message handler.
	 *
	 * @param in input message.
	 * @param out output message.
	 * @return true if the response is sent immediately or false otherwise.
	 */
	bool link_parameters_report_indication(meta_message_ptr &in,
				   meta_message_ptr &out);


	/**
	 * Link Handover Imminent Indication message handler.
	 *
	 * @param in input message.
	 * @param out output message.
	 * @return true if the response is sent immediately or false otherwise.
	 */
	bool link_handover_imminent_indication(meta_message_ptr &in,
					       meta_message_ptr &out);

	/**
	 * Link Handover Complete Indication message handler.
	 *
	 * @param in input message.
	 * @param out output message.
	 * @return true if the response is sent immediately or false otherwise.
	 */
	bool link_handover_complete_indication(meta_message_ptr &in,
					       meta_message_ptr &out);

	/**
	 * Link PDU Transmit Status Indication message handler.
	 *
	 * @param in input message.
	 * @param out output message.
	 * @return true if the response is sent immediately or false otherwise.
	 */
	bool link_pdu_transmit_status_indication(meta_message_ptr &in,
						 meta_message_ptr &out);

protected:
	local_transaction_pool	&_lpool;
	transmit		&_transmit;
	link_book               &_link_abook;
	std::map<mih::octet_string, mih::event_list> _link_subscriptions;

	std::list<event_registration_t>	 _event_subscriptions;
	boost::mutex			 _event_mutex;

	/**
	 * Send message for all users subscribed to event from link identifier
	 *
	 * @param msg MIH Message.
	 * @param li link identifier
	 * @param event event
	 */
	void msg_forward(meta_message_ptr& msg,
			 mih::link_tuple_id &li,
			 mih::event_list_enum event);

	/**
	 * Parse link_identifier from incoming message and forward
	 * message to subscribed users
	 *
	 * @param msg MIH Message.
	 * @param event event
	 */
	void link_event_forward(meta_message_ptr &msg,
				mih::event_list_enum event);

	/**
	 * This MIHF is the destination of the Event_Subscribe.request.
	 * Deserialize the message, subscribe the user and send a response immediatly
	 * if the events are already subscribed with the Link SAP. Otherwise, the MIHF
	 * send a request to the Link SAP to subscribe the desired events.
	 *
	 * @param in input message.
	 * @param out output message.
	 * @return true if the response is sent immediately or false otherwise.
	 */
	bool local_event_subscribe_request(meta_message_ptr &in,
					   meta_message_ptr &out);

	/**
	 * This MIHF is the destination of the Event_Unsubscribe.request.
	 * Deserialize message, unsubscribe user and send a response
	 *
	 * @param in input message.
	 * @param out output message.
	 * @return true if the response is sent immediately or false otherwise.
	 */
	bool local_event_unsubscribe_request(meta_message_ptr &in,
					     meta_message_ptr &out);

	/**
	 * Subscribe user to all events, set in the events bitmap, from
	 * link identifier.
	 *
	 * @param user user that request the subscription.
	 * @param link link to make the subscription.
	 * @param events events to subscribe.
	 * @return MIH Status value of the operation.
	 */
	mih::status subscribe(const mih::id &user, mih::link_tuple_id &link,
			      mih::event_list &events);

	/**
	 * Unsubscribe user to all events, set in the events bitmap, from
	 * link identifier.
	 *
	 * @param user user that request the unsubscription.
	 * @param link link to make the unsubscription.
	 * @param events events to unsubscribe.
	 * @return MIH Status value of the operation.
	 */
	mih::status unsubscribe(const mih::id &user, mih::link_tuple_id &link,
				mih::event_list &events);

	/**
	 * Check if there is events subscribed to a given Link SAP that are not needed
	 * anymore.
	 *
	 * @param in input message.
	 * @param link link to make the unsubscription.
	 * @param events events to unsubscribed.
	 */
	void link_unsubscribe(meta_message_ptr &in,
	                      mih::link_tuple_id &link,
	                      mih::event_list &events);

};

///////////////////////////////////////////////////////////////////////////////
} /* namespace mihf */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif
