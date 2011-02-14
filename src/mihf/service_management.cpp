//==============================================================================
// Brief   : Service Management
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

///////////////////////////////////////////////////////////////////////////////
#include "service_management.hpp"

#include "log.hpp"
#include "utils.hpp"
#include "mihfid.hpp"
#include "transmit.hpp"

#include <odtone/mih/types/capabilities.hpp>
#include <odtone/mih/request.hpp>
#include <odtone/mih/response.hpp>
#include <odtone/mih/confirm.hpp>
#include <odtone/mih/indication.hpp>
#include <odtone/mih/tlv_types.hpp>

#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

///////////////////////////////////////////////////////////////////////////////

extern odtone::uint16 kConf_MIHF_Link_Response_Time_Value;

namespace odtone { namespace mihf {

/**
 * Service management constructor.
 *
 * @param lpool local transction pool.
 * @param link_abook link book.
 * @param t transmit module.
 * @param lrpool link response pool.
 * @param enable_broadcast true if response to broadcast
 *                         Capability_Discover.request is enable or false otherwise.
 */
service_management::service_management(local_transaction_pool &lpool,
										link_book &link_abook,
										user_book &user_abook,
										transmit &t,
										link_response_pool &lrpool,
										bool enable_broadcast)
	: _lpool(lpool),
	  _link_abook(link_abook),
	  _user_abook(user_abook),
	  _transmit(t),
	  _lrpool(lrpool)
{
	_enable_broadcast = enable_broadcast;
}

/**
 * Handler responsible for asking capabilities to known local Link SAPs,
 * process those capabilities and answer with a Capability Discover response
 * message to the requestor.
 *
 * @param src_id MIHF ID from the requestor.
 * @param tid MIH Transaction ID.
 * @param t transmit module.
 * @param lpool local transction pool.
 * @param link_abook link book.
 * @param lrpool link response pool.
 */
void link_capability_discover_response_handler(mih::id src_id,
	                                           uint16 tid,
	                                           transmit &t,
	                                           local_transaction_pool &lpool,
	                                           link_book &link_abook,
	                                           link_response_pool &lrpool)
{
	mih::net_type_addr_list  capabilities_list_net_type_addr;
	mih::event_list	         capabilities_event_list;
	mih::command_list        capabilities_cmd_list;
	meta_message_ptr out(new meta_message());

	boost::this_thread::sleep(boost::posix_time::milliseconds(kConf_MIHF_Link_Response_Time_Value));

	std::vector<mih::octet_string> ids = link_abook.get_ids();
	odtone::uint num_link = ids.size();
	if(num_link != 0) {
		capabilities_event_list.full();
		capabilities_cmd_list.full();
	}

	std::vector<mih::octet_string>::iterator it_link;
	for(it_link = ids.begin(); it_link != ids.end(); it_link++) {
		// Delete unanswered Link SAP from known Link SAPs list
		if(!lrpool.check(tid, *it_link)) {
			link_abook.del(*it_link);
			lpool.del(*it_link, tid);
			num_link--;
		}
		else {
			// fill LinkAddressList
			link_entry a;
			mih::net_type_addr nta;

			a = link_abook.get(*it_link);

			nta.nettype.link = a.link_id.type;
			nta.addr = a.link_id.addr;
			capabilities_list_net_type_addr.push_back(nta);

			// fill capabilities
			pending_link_response tmp = lrpool.find(tid, *it_link);
			lrpool.del(tid, *it_link);

			capabilities_event_list.common(tmp.cap.event_list);
			capabilities_cmd_list.common(tmp.cap.command_list);
		}
	}

	if(num_link == 0) {
		capabilities_event_list.clear();
		capabilities_cmd_list.clear();
	}

	// Send Capability_Discover.response to the user
	log(1, "(mism) setting response to Capability_Discover.request");
	*out << mih::response(mih::response::capability_discover)
	    & mih::tlv_status(mih::status_success)
	    & mih::tlv_net_type_addr_list(capabilities_list_net_type_addr)
	    & mih::tlv_event_list(capabilities_event_list)
	    & mih::tlv_command_list(capabilities_cmd_list);

	out->tid(tid);
	out->destination(src_id);
	out->source(mihfid);

	t(out);
}

/**
 * Asks for local Link SAPs capabilities by sending a Capability Request message
 * to all known Link SAPs. Also responsible for launch the thread that will
 * respond to the requestor.
 *
 * @param in input message.
 * @return always false, because it does not send any response directly.
 */
bool service_management::forward_to_link_capability_discover_request(meta_message_ptr &in)
{
	mih::id src_tmp = in->source();
	uint16  tid = in->tid();

	// Asks for local Link SAPs capabilities
	log(1, "(mism) gathering information about local Link SAPs capabilities");

	*in << mih::request(mih::request::capability_discover);

	std::vector<mih::octet_string> ids = _link_abook.get_ids();
	std::vector<mih::octet_string>::iterator it;
	for ( it=ids.begin(); it < ids.end(); it++ ) {
		in->destination(mih::id(*it));
		utils::forward_request(in, _lpool, _transmit);
	}

	// Lauched the thread responsible for respond to the capability discover
	boost::thread(link_capability_discover_response_handler,
	              src_tmp,
	              tid,
	              boost::ref(_transmit),
	              boost::ref(_lpool),
	              boost::ref(_link_abook),
	              boost::ref(_lrpool));

	// Do not respond to the request. The thread lauched will be
	// responsible for that.
	return false;
}

/**
 * Capability Discover Request message handler.
 *
 * @param in input message.
 * @param out output message.
 * @return true if the response is sent immediately or false otherwise.
 */
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

		mih::event_list     capabilities_event_list;
		mih::command_list   capabilities_cmd_list;
		mih::net_type_addr_list  capabilities_list_net_type_addr;

		*in << mih::request(mih::request::capability_discover)
			& mih::tlv_status(mih::status_success)
			& mih::tlv_net_type_addr_list(capabilities_list_net_type_addr)
			& mih::tlv_event_list(capabilities_event_list)
			& mih::tlv_command_list(capabilities_cmd_list);

		utils::forward_request(in, _lpool, _transmit);
		return false;
	// destination mihf identifier is this mihf
	} else if (utils::this_mihf_is_destination(in)) {
		return forward_to_link_capability_discover_request(in);
	// message was broadcasted?
	} else if (utils::is_multicast(in)) {
		if (_enable_broadcast) {
			return forward_to_link_capability_discover_request(in);
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

/**
 * Capability Discover Response message handler.
 *
 * @param in input message.
 * @param out output message.
 * @return true if the response is sent immediately or false otherwise.
 */
bool service_management::capability_discover_response(meta_message_ptr &in,
						      meta_message_ptr &)
{
	log(1, "(mism) received Capability_Discover.response from ",
	    in->source().to_string());

	// do we have a request from a user?
	if (_lpool.set_user_tid(in)) {
		log(1, "forwarding Capability_Discover.response to ",
		    in->destination().to_string());
		in->opcode(mih::operation::confirm);
		_transmit(in);
		return false;
	}

	// set source id to broadcast id and check if there's a
	// broadcast request from a user
	in->source(mih::id(""));
	if (_lpool.set_user_tid(in))  {
		log(1, "forwarding Capability_Discover.response to ",
		    in->destination().to_string());
		in->opcode(mih::operation::confirm);
		_transmit(in);
		return false;
	}

	log(1, "no pending transaction for this message, discarding");
	return false;
}

/**
 * Capability Discover Confirm message handler.
 *
 * @param in input message.
 * @param out output message.
 * @return true if the response is sent immediately or false otherwise.
 */
bool service_management::capability_discover_confirm(meta_message_ptr &in,
						      meta_message_ptr &out)
{
	log(1, "(mism) received Capability_Discover.confirm from ",
	    in->source().to_string());

	if (_lpool.set_user_tid(in)) {
		mih::status st;
		boost::optional<mih::event_list> event;
		boost::optional<mih::command_list> command;

		*in >> mih::confirm()
		       & mih::tlv_status(st)
		       & mih::tlv_event_list(event)
		       & mih::tlv_command_list(command);

		if(st == mih::status_success) {
			_lrpool.add(in->source().to_string(),
			           in->tid(),
			           event.get(),
			           command.get());
		}

		return false;
	}

	log(1, "no pending transaction for this message, discarding");
	return false;
}

/**
 * Link Register Indication message handler.
 *
 * @param in input message.
 * @param out output message.
 * @return true if the response is sent immediately or false otherwise.
 */
bool service_management::link_register_indication(meta_message_ptr &in,
	                                       meta_message_ptr &out)
{
	log(1, "(mism) received Link_Register.indication from ",
	    in->source().to_string());

	// Add Link SAP to the list of known Link SAPs
	mih::status st;
	mih::link_id link_id;

	mih::octet_string ip(in->ip());

	*in >> odtone::mih::indication()
		& odtone::mih::tlv_interface_type_addr(link_id);

	_link_abook.add(in->source().to_string(), ip, in->port(), link_id);

	return false;
}

/**
 * User Register Indication message handler.
 *
 * @param in input message.
 * @param out output message.
 * @return true if the response is sent immediately or false otherwise.
 */
bool service_management::user_register_indication(meta_message_ptr &in,
	                                          meta_message_ptr &out)
{
	log(1, "(mism) received User_Register.indication from ",
	    in->source().to_string());

	// Add MIH User to the list of known MIH Users
	mih::status st;
	bool mbbhandover;

	mih::octet_string ip(in->ip());

	*in >> odtone::mih::indication()
		& odtone::mih::tlv_mbb_handover_support(mbbhandover);

	_user_abook.add(in->source().to_string(), ip, in->port(), mbbhandover);

	return false;
}

} /* namespace mihf */ } /* namespace odtone */
