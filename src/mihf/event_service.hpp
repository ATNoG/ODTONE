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

#ifndef ODTONE_MIHF_EVENT_SERVICE_HPP
#define ODTONE_MIHF_EVENT_SERVICE_HPP

///////////////////////////////////////////////////////////////////////////////
#include "local_transaction_pool.hpp"
#include "transmit.hpp"
#include "meta_message.hpp"

#include <odtone/base.hpp>
#include <odtone/mih/types.hpp>

#include <boost/thread/mutex.hpp>
#include <list>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {


struct event_registration_t
{
	mih::octet_string	user;
	mih::link_tuple_id	link;
	mih::event_list_enum	event;
	// mih::list<evt_cfg_info>	cfg_list;
};


class event_service
	: boost::noncopyable {
public:
	event_service(local_transaction_pool &lpool, transmit &t);

	bool event_subscribe_request(meta_message_ptr &in,
				     meta_message_ptr &out);
	bool event_subscribe_response(meta_message_ptr &in,
				      meta_message_ptr &out);
	bool event_unsubscribe_request(meta_message_ptr &in,
				       meta_message_ptr &out);
	bool event_unsubscribe_response(meta_message_ptr &in,
					meta_message_ptr &out);
	bool link_up_indication(meta_message_ptr &in,
				meta_message_ptr &out);
	bool link_down_indication (meta_message_ptr &in,
				   meta_message_ptr &out);
	bool link_detected_indication(meta_message_ptr &in,
				      meta_message_ptr &out);
	bool link_going_down_indication(meta_message_ptr &in,
					meta_message_ptr &out);
	bool link_handover_imminent_indication(meta_message_ptr &in,
					       meta_message_ptr &out);
	bool link_handover_complete_indication(meta_message_ptr &in,
					       meta_message_ptr &out);
	bool link_pdu_transmit_status_indication(meta_message_ptr &in,
						 meta_message_ptr &out);

protected:
	local_transaction_pool	&_lpool;
	transmit		&_transmit;

	std::list<event_registration_t>	 _event_subscriptions;
	boost::mutex			 _event_mutex;

	void msg_forward(meta_message_ptr& msg,
			 mih::link_tuple_id &li,
			 mih::event_list_enum event);

	void link_event_forward(meta_message_ptr &msg,
				mih::event_list_enum event);

	bool local_event_subscribe_request(meta_message_ptr &in,
					   meta_message_ptr &out);
	bool local_event_unsubscribe_request(meta_message_ptr &in,
					     meta_message_ptr &out);

	mih::status subscribe(const mih::id &user, mih::link_tuple_id &link,
			      mih::event_list &events);
	mih::status unsubscribe(const mih::id &user, mih::link_tuple_id &link,
				mih::event_list &events);

};

///////////////////////////////////////////////////////////////////////////////
} /* namespace mihf */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif
