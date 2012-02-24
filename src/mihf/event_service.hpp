//==============================================================================
// Brief   : Event Service
// Authors : Simao Reis <sreis@av.it.pt>
//           Carlos Guimarães <cguimaraes@av.it.pt>
//------------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2009-2012 Universidade Aveiro
// Copyright (C) 2009-2012 Instituto de Telecomunicações - Pólo Aveiro
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
#include "address_book.hpp"
#include "link_book.hpp"
#include "user_book.hpp"
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
	mih::octet_string		user;	/**< MIH-User/MIHF identifier.	*/
	mih::link_tuple_id		link;	/**< Link identifier.			*/
	mih::mih_evt_list_enum	event;	/**< Event subscribed.			*/

	/**
	 * Check if the MAC_ADDR is equal to another MAC_ADDR.
	 *
	 * @param other The MAC_ADDR to compare with.
	 * @return True if they are equal or false otherwise.
	 */
	bool operator==(const event_registration_t& other) const
	{
		return ((user == other.user) && (link == other.link) && (event == other.event));
	}
};

/**
 * This class is responsible for handling the messages associated with
 * the event service.
 */
class event_service
	: boost::noncopyable {
public:
	/**
	 * Construct the event service.
	 *
	 * @param io The io_service object that event service module will use to
	 * dispatch handlers for any asynchronous operations performed on
	 * the socket.
	 * @param lpool The local transaction pool module.
	 * @param t The transmit module.
	 * @param abook The address book module.
	 * @param lbook The link book module.
	 * @param ubook The user book module.
	 */
	event_service(io_service &io, local_transaction_pool &lpool,
				  transmit &t, address_book &abook, link_book &lbook,
				  user_book &ubook);

	/**
	 * Event Subscribe Request message handler.
	 *
	 * @param in The input message.
	 * @param out The output message.
	 * @return True if the response is sent immediately or false otherwise.
	 */
	bool event_subscribe_request(meta_message_ptr &in,
				     meta_message_ptr &out);

	/**
	 * Event Subscribe Response message handler.
	 *
	 * @param in The input message.
	 * @param out The output message.
	 * @return True if the response is sent immediately or false otherwise.
	 */
	bool event_subscribe_response(meta_message_ptr &in,
				      meta_message_ptr &out);

	/**
	 * Event Subscribe Confirm message handler.
	 *
	 * @param in The input message.
	 * @param out The output message.
	 * @return True if the response is sent immediately or false otherwise.
	 */
	bool event_subscribe_confirm(meta_message_ptr &in,
				     meta_message_ptr &out);

	/**
	 * Event Unsubscribe Request message handler.
	 *
	 * @param in The input message.
	 * @param out The output message.
	 * @return True if the response is sent immediately or false otherwise.
	 */
	bool event_unsubscribe_request(meta_message_ptr &in,
				       meta_message_ptr &out);

	/**
	 * Event Unsubscribe Response message handler.
	 *
	 * @param in The input message.
	 * @param out The output message.
	 * @return True if the response is sent immediately or false otherwise.
	 */
	bool event_unsubscribe_response(meta_message_ptr &in,
					meta_message_ptr &out);

	/**
	 * Event Unsubscribe Confirm message handler.
	 *
	 * @param in The input message.
	 * @param out The output message.
	 * @return True if the response is sent immediately or false otherwise.
	 */
	bool event_unsubscribe_confirm(meta_message_ptr &in,
				       meta_message_ptr &out);

	/**
	 * Link Up Indication message handler.
	 *
	 * @param in The input message.
	 * @param out The output message.
	 * @return True if the response is sent immediately or false otherwise.
	 */
	bool link_up_indication(meta_message_ptr &in,
				meta_message_ptr &out);

	/**
	 * Link Down Indication message handler.
	 *
	 * @param in The input message.
	 * @param out The output message.
	 * @return True if the response is sent immediately or false otherwise.
	 */
	bool link_down_indication (meta_message_ptr &in,
				   meta_message_ptr &out);

	/**
	 * Link Detected Indication message handler.
	 *
	 * @param in The input message.
	 * @param out The output message.
	 * @return True if the response is sent immediately or false otherwise.
	 */
	bool link_detected_indication(meta_message_ptr &in,
				      meta_message_ptr &out);

	/**
	 * Link Going Down Indication message handler.
	 *
	 * @param in The input message.
	 * @param out The output message.
	 * @return True if the response is sent immediately or false otherwise.
	 */
	bool link_going_down_indication(meta_message_ptr &in,
					meta_message_ptr &out);

	/**
	 * Link Parameters Report Indication message handler.
	 *
	 * @param in The input message.
	 * @param out The output message.
	 * @return True if the response is sent immediately or false otherwise.
	 */
	bool link_parameters_report_indication(meta_message_ptr &in,
				   meta_message_ptr &out);


	/**
	 * Link Handover Imminent Indication message handler.
	 *
	 * @param in The input message.
	 * @param out The output message.
	 * @return True if the response is sent immediately or false otherwise.
	 */
	bool link_handover_imminent_indication(meta_message_ptr &in,
					       meta_message_ptr &out);

	/**
	 * Link Handover Complete Indication message handler.
	 *
	 * @param in The input message.
	 * @param out The output message.
	 * @return True if the response is sent immediately or false otherwise.
	 */
	bool link_handover_complete_indication(meta_message_ptr &in,
					       meta_message_ptr &out);

	/**
	 * Link PDU Transmit Status Indication message handler.
	 *
	 * @param in The input message.
	 * @param out The output message.
	 * @return True if the response is sent immediately or false otherwise.
	 */
	bool link_pdu_transmit_status_indication(meta_message_ptr &in,
						 meta_message_ptr &out);

protected:
	/**
	 * Forward the message for all users subscribed to event from the
	 * Link SAP.
	 *
	 * @param msg The MIH Message.
	 * @param li The link identifier.
	 * @param event The related event.
	 */
	void msg_forward(meta_message_ptr& msg,
			 mih::link_tuple_id &li,
			 mih::mih_evt_list_enum event);

	/**
	 * Parse the link identifier from incoming message and forwards the
	 * message to subscribed users
	 *
	 * @param msg The MIH Message.
	 * @param event The related event.
	 */
	void link_event_forward(meta_message_ptr &msg,
				mih::mih_evt_list_enum event);

	/**
	 * Deserialize the message, subscribe the user and send a response immediatly
	 * if the events are already subscribed with the Link SAP. Otherwise, the MIHF
	 * sends a request to the Link SAP to subscribe the desired events.
	 *
	 * @param in The input message.
	 * @param out The output message.
	 * @return True if the response is sent immediately or false otherwise.
	 */
	bool local_event_subscribe_request(meta_message_ptr &in,
					   meta_message_ptr &out);

	/**
	 * Deserialize message, unsubscribe user and send a response to the
	 * requestor.
	 *
	 * @param in The input message.
	 * @param out The output message.
	 * @return True if the response is sent immediately or false otherwise.
	 */
	bool local_event_unsubscribe_request(meta_message_ptr &in,
					     meta_message_ptr &out);

	/**
	 * Make a subscription for a given user.
	 *
	 * @param user The MIH-User/MIHF that request the subscription.
	 * @param link The link to make the subscription.
	 * @param events The events to subscribe.
	 * @return The status of the operation.
	 */
	mih::status subscribe(const mih::id &user, mih::link_tuple_id &link,
			      mih::mih_evt_list &events);

	/**
	 * Unsubscribe the events related to a given user.
	 *
	 * @param user The MIH-User/MIHF that request the unsubscription.
	 * @param link The link to make the unsubscription.
	 * @param events The events to unsubscribe.
	 * @return The status of the operation.
	 */
	mih::status unsubscribe(const mih::id &user, mih::link_tuple_id &link,
				mih::mih_evt_list &events);

	/**
	 * Check if there is events subscribed to a given Link SAP, which
	 * are not required anymore.
	 *
	 * @param in The input message.
	 * @param link The link to make the unsubscription.
	 * @param events The events to unsubscribed.
	 */
	void link_unsubscribe(meta_message_ptr &in,
	                      mih::link_tuple_id &link,
	                      mih::mih_evt_list &events);

	/**
	 * Handler responsible for setting a failure Link Event Subscribe
	 * response.
	 *
	 * @param ec Error code.
	 * @param in The input message.
	 */
	void link_event_subscribe_response_timeout(const boost::system::error_code &ec,
											   meta_message_ptr &in);

private:
	io_service				&_io;			/**< The io_service object.			*/
	local_transaction_pool	&_lpool;		/**< Local transaction pool module.	*/
	transmit				&_transmit;		/**< Transmit module.				*/
	address_book            &_abook;		/**< Address book module.			*/
	link_book               &_link_abook;	/**< Link book module.				*/
	user_book               &_user_abook;	/**< User book module.				*/

	std::list<event_registration_t>	_event_subscriptions;	/**< List of subscription.	*/
	boost::mutex					_event_mutex;			/**< Mutex.	*/

	/** Timer map. */
	std::map<uint16, boost::shared_ptr<boost::asio::deadline_timer> > _timer;
	boost::mutex _mutex;	/**< Mutex.	*/
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace mihf */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif
