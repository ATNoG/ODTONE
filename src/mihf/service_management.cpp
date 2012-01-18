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
///////////////////////////////////////////////////////////////////////////////

extern odtone::uint16 kConf_MIHF_Link_Response_Time_Value;
extern odtone::uint16 kConf_MIHF_Link_Delete_Value;

namespace odtone { namespace mihf {

/**
 * Construct the service management.
 *
 * @param io The io_service object that Link SAP I/O Service will use to
 * dispatch handlers for any asynchronous operations performed on
 * the socket.
 * @param lpool The local transaction pool module.
 * @param link_abook The link book module.
 * @param user_abook The user book module.
 * @param address_abook The address book module.
 * @param t The transmit module.
 * @param lrpool The link response pool module.
 */
service_management::service_management(io_service &io,
										local_transaction_pool &lpool,
										link_book &link_abook,
										user_book &user_abook,
										address_book &address_book,
										transmit &t,
										link_response_pool &lrpool)
	: _lpool(lpool),
	  _link_abook(link_abook),
	  _user_abook(user_abook),
	  _abook(address_book),
	  _transmit(t),
	  _lrpool(lrpool),
	  _discover(io, lpool, address_book, user_abook, t)
{
}

/**
 * Asks for the capabilities of all local Link SAPs.
 *
 * @param in The input message.
 * @param out The output message.
 * @return Always false, because it does not send any response directly.
 */
bool service_management::link_capability_discover_request(meta_message_ptr &in,
														  meta_message_ptr &out)
{
	// Asks for local Link SAPs capabilities
	ODTONE_LOG(1, "(mism) gathering information about local Link SAPs capabilities");

	*out << mih::request(mih::request::capability_discover);
	out->tid(in->tid());
	out->destination(in->source());

	// Check if the Link SAP is still active
	uint16 fails = _link_abook.fail(out->destination().to_string());
	if(fails > kConf_MIHF_Link_Delete_Value) {
		mih::octet_string dst = out->destination().to_string();
		_link_abook.inactive(dst);

		// Update MIHF capabilities
		utils::update_local_capabilities(_abook, _link_abook);
	}
	else {
		ODTONE_LOG(1, "(mics) forwarding Link_Capability_Discover.request to ",
			out->destination().to_string());
		utils::forward_request(out, _lpool, _transmit);
	}

	return false;
}

/**
 * Piggyback local MIHF Capabilities in request message.
 *
 * @param in input message.
 * @param out output message.
 */
void service_management::piggyback_capabilities(meta_message_ptr& in,
												meta_message_ptr& out)
{
	address_entry mihf_info;

	// Get local capabilities
	address_entry mihf_cap = _abook.get(mihfid_t::instance()->to_string());

	*out << mih::request(mih::request::capability_discover)
			& mih::tlv_net_type_addr_list(mihf_cap.capabilities_list_net_type_addr)
			& mih::tlv_event_list(mihf_cap.capabilities_event_list)
			& mih::tlv_command_list(mihf_cap.capabilities_cmd_list)
			& mih::tlv_query_type_list(mihf_cap.capabilities_query_type)
			& mih::tlv_transport_option_list(mihf_cap.capabilities_trans_list)
			& mih::tlv_mbb_ho_supp_list(mihf_cap.capabilities_mbb_ho_supp);

	out->tid(in->tid());
	out->source(in->source());
	out->destination(in->destination());
	out->ackreq(in->ackreq());
}

/**
 * Parse all capabilities from MIH Capability Discover message and stores
 * them.
 *
 * @param in input message.
 * @param out output message.
 */
void service_management::get_capabilities(meta_message_ptr& in,
										  meta_message_ptr& out)
{
	address_entry mihf_info;
	mihf_info.ip = in->ip();
	mihf_info.port = in->port();

	if(in->opcode() == mih::operation::request) {
		*in >> mih::request(mih::request::capability_discover)
				& mih::tlv_net_type_addr_list(mihf_info.capabilities_list_net_type_addr)
				& mih::tlv_event_list(mihf_info.capabilities_event_list)
				& mih::tlv_command_list(mihf_info.capabilities_cmd_list)
				& mih::tlv_query_type_list(mihf_info.capabilities_query_type)
				& mih::tlv_transport_option_list(mihf_info.capabilities_trans_list)
				& mih::tlv_mbb_ho_supp_list(mihf_info.capabilities_mbb_ho_supp);
	} else if(in->opcode() == mih::operation::response) {
		mih::status st;
		*in >> mih::response(mih::response::capability_discover)
			& mih::tlv_status(st)
			& mih::tlv_net_type_addr_list(mihf_info.capabilities_list_net_type_addr)
			& mih::tlv_event_list(mihf_info.capabilities_event_list)
			& mih::tlv_command_list(mihf_info.capabilities_cmd_list)
			& mih::tlv_query_type_list(mihf_info.capabilities_query_type)
			& mih::tlv_transport_option_list(mihf_info.capabilities_trans_list)
			& mih::tlv_mbb_ho_supp_list(mihf_info.capabilities_mbb_ho_supp);
	}

	_abook.add(in->source().to_string(), mihf_info);
}

/**
 * Set response to MIH Capability Discover message.
 *
 * @param in input message.
 * @param out output message.
 */
void service_management::set_capability_discover_response(meta_message_ptr& in,
														  meta_message_ptr& out)
{
	// Create and piggyback local capabilities in response message
	address_entry mihf_cap = _abook.get(mihfid_t::instance()->to_string());

	*out << mih::response(mih::response::capability_discover)
			& mih::tlv_status(mih::status_success)
			& mih::tlv_net_type_addr_list(mihf_cap.capabilities_list_net_type_addr)
			& mih::tlv_event_list(mihf_cap.capabilities_event_list)
			& mih::tlv_command_list(mihf_cap.capabilities_cmd_list)
			& mih::tlv_query_type_list(mihf_cap.capabilities_query_type)
			& mih::tlv_transport_option_list(mihf_cap.capabilities_trans_list)
			& mih::tlv_mbb_ho_supp_list(mihf_cap.capabilities_mbb_ho_supp);

	out->tid(in->tid());
	out->source(mihfid);
	out->destination(in->source());
	out->ackreq(in->ackreq());
}

/**
 * Send Capability Discover Indication message to all MIH Users.
 *
 * @param in input message.
 * @param out output message.
 */
void service_management::send_indication(meta_message_ptr& in,
										 meta_message_ptr& out)
{
	std::vector<mih::octet_string> ids = _user_abook.get_ids();
	in->opcode(mih::operation::indication);
	for (std::vector<mih::octet_string>::iterator it = ids.begin(); it < ids.end(); ++it) {
		in->destination(mih::id(*it));
		_transmit(in);
		ODTONE_LOG(3, "(mism) Capability_Discover.indication sent to ",
				  in->destination().to_string());
	}
}

/**
 * Capability Discover Request message handler.
 *
 * @param in The input message.
 * @param out The output message.
 * @return True if the response is sent immediately or false otherwise.
 */
bool service_management::capability_discover_request(meta_message_ptr& in,
													 meta_message_ptr& out)
{
	ODTONE_LOG(1, "(mism) received Capability_Discover.request from ",
	    in->source().to_string(), " with destination ",
	    in->destination().to_string());

	// User requests the capabilities of a remote MIHF
	if (in->is_local() && !utils::this_mihf_is_destination(in)) {
		// Multicast && Discover Module ON
		boost::optional<mih::octet_string> disc_user = _user_abook.discovery_user();
		if(utils::is_multicast(in) && disc_user.is_initialized()) {
			_discover.request(in, out);
			return false;
		}
		// Multicast && Discover Module OFF
		piggyback_capabilities(in, out);
		utils::forward_request(out, _lpool, _transmit);
		return false;
	// User requets the capabilitties of the local MIHF
	} else if (in->is_local() && utils::this_mihf_is_destination(in)) {
		set_capability_discover_response(in, out);
		return true;
	// Remote requets received
	} else if (utils::this_mihf_is_destination(in)) {
		send_indication(in, out);
		get_capabilities(in, out);
		set_capability_discover_response(in, out);
		return true;
	// Multicast request received
	} else if (utils::is_multicast(in)) {
		send_indication(in, out);
		get_capabilities(in, out);
		set_capability_discover_response(in, out);
		return true;
	} else {
			ODTONE_LOG(3, "(mism) response to broadcast Capability_Discover.request disabled ");
			return false;
	}

	return false;
}

/**
 * Capability Discover Response message handler.
 *
 * @param in The input message.
 * @param out The output message.
 * @return True if the response is sent immediately or false otherwise.
 */
bool service_management::capability_discover_response(meta_message_ptr &in,
						      meta_message_ptr &out)
{
	ODTONE_LOG(1, "(mism) received Capability_Discover.response from ",
	    in->source().to_string());

	// Check if it is a discovery message
	if(in->is_local()) {
		user_entry user = _user_abook.get(in->source().to_string());
		if(user.role == mih::user_role_discovery) {
			_discover.response(in, out);
			return false;
		}
	}

	// Store remote MIHF capabilities
	get_capabilities(in, out);

	// do we have a request from a user?
	if (_lpool.set_user_tid(in)) {
		ODTONE_LOG(1, "forwarding Capability_Discover.response to ",
		    in->destination().to_string());
		in->opcode(mih::operation::confirm);
		_transmit(in);
		return false;
	}

	// set source id to broadcast id and check if there's a
	// broadcast request from a user
	mih::id tmp	= in->source();
	in->source(mih::id(""));
	if (_lpool.set_user_tid(in))  {
		ODTONE_LOG(1, "forwarding Capability_Discover.response to ",
		    in->destination().to_string());
		in->opcode(mih::operation::confirm);
		in->source(tmp);
		_transmit(in);
		return false;
	}

	ODTONE_LOG(1, "no pending transaction for this message, discarding");
	return false;
}

/**
 * Capability Discover Confirm message handler.
 *
 * @param in The input message.
 * @param out The output message.
 * @return True if the response is sent immediately or false otherwise.
 */
bool service_management::capability_discover_confirm(meta_message_ptr &in,
						      meta_message_ptr &out)
{
	ODTONE_LOG(1, "(mism) received Capability_Discover.confirm from ",
	    in->source().to_string());

	_link_abook.reset(in->source().to_string());

	if(!_lpool.set_user_tid(in)) {
		ODTONE_LOG(1, "no pending transaction for this message, discarding");
		return false;
	}

	mih::status st;
	boost::optional<mih::event_list> event;
	boost::optional<mih::command_list> command;

	*in >> mih::confirm(mih::confirm::capability_discover)
	       & mih::tlv_status(st)
	       & mih::tlv_event_list(event)
	       & mih::tlv_command_list(command);

	if(st == mih::status_success) {
		// Update Link SAP capabilities in the Link Book
		_link_abook.update_capabilities(in->source().to_string(), event.get(), command.get());

		// Update MIHF capabilities
		utils::update_local_capabilities(_abook, _link_abook);
	}

	return false;
}

/**
 * Link Register Indication message handler.
 *
 * @param in The input message.
 * @param out The output message.
 * @return True if the response is sent immediately or false otherwise.
 */
bool service_management::link_register_indication(meta_message_ptr &in,
	                                       meta_message_ptr &out)
{
	ODTONE_LOG(1, "(mism) received Link_Register.indication from ",
	    in->source().to_string());

	// Add Link SAP to the list of known Link SAPs
	mih::status st;
	mih::link_id link_id;

	mih::octet_string ip(in->ip());

	*in >> odtone::mih::indication()
		& odtone::mih::tlv_interface_type_addr(link_id);

	// Add Link SAP to the list of known Link SAPs
	_link_abook.add(in->source().to_string(), in->ip(), in->port(), link_id);

	// Update MIHF network type address
	address_entry mihf_cap = _abook.get(mihfid_t::instance()->to_string());

	// Set Network Type Address
	mih::net_type_addr nta;
	nta.nettype.link = link_id.type;
	nta.addr = link_id.addr;

	if(mihf_cap.capabilities_list_net_type_addr.is_initialized()) {
		mihf_cap.capabilities_list_net_type_addr.get().push_back(nta);
	} else {
		mih::net_type_addr_list ntal;
		ntal.push_back(nta);
		mihf_cap.capabilities_list_net_type_addr = ntal;
	}
	_abook.add(mihfid_t::instance()->to_string(), mihf_cap);

	// Request the Link SAP capabilities
	link_capability_discover_request(in, out);

	return false;
}

/**
 * User Register Indication message handler.
 *
 * @param in The input message.
 * @param out The output message.
 * @return True if the response is sent immediately or false otherwise.
 */
bool service_management::user_register_indication(meta_message_ptr &in,
	                                          meta_message_ptr &out)
{
	ODTONE_LOG(1, "(mism) received User_Register.indication from ",
	    in->source().to_string());

	// Add MIH User to the list of known MIH Users
	mih::status st;
	mih::user_role role;

	mih::octet_string ip(in->ip());

	*in >> odtone::mih::indication()
		& odtone::mih::tlv_user_role(role);

	_user_abook.add(in->source().to_string(), ip, in->port(), role);

	return false;
}

} /* namespace mihf */ } /* namespace odtone */
