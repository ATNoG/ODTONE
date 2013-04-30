//==============================================================================
// Brief   : Link SAP
// Authors : Bruno Santos <bsantos@av.it.pt>
//------------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2009-2013 Universidade Aveiro
// Copyright (C) 2009-2013 Instituto de Telecomunicações - Pólo Aveiro
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//==============================================================================

///////////////////////////////////////////////////////////////////////////////
#include <odtone/debug.hpp>
#include <iostream>
#include <odtone/mih/types/base.hpp>
#include <odtone/mih/message.hpp>
#include <odtone/mih/indication.hpp>
#include <odtone/mih/request.hpp>
#include <odtone/mih/response.hpp>
#include <odtone/mih/confirm.hpp>
#include <odtone/mih/tlv_types.hpp>
#include <boost/bind.hpp>
#include "link_sap.hpp"

///////////////////////////////////////////////////////////////////////////////
extern odtone::mih::link_id       link_id;
extern odtone::mih::link_evt_list capabilities_event_list;
extern odtone::mih::link_cmd_list capabilities_command_list;
namespace link_sap {

///////////////////////////////////////////////////////////////////////////////
/**
 * Construct the Link SAP.
 *
 * @param cfg Configuration options.
 * @param io The io_service object that Link SAP will use to
 * dispatch handlers for any asynchronous operations performed on the socket. 
 */
link_sap::link_sap(const odtone::mih::config& cfg, boost::asio::io_service& io)
	: _mihf(cfg, io, boost::bind(&link_sap::default_handler, this, _1, _2))
{
	init();
}

/**
 * Destruct the Link SAP.
 */
link_sap::~link_sap()
{
}

/**
 * Update the state of the interface. If the state has been changed
 * notify its local MIHF
 *
 * @param it Interface information.
 */
void link_sap::update(nic::interface* it)
{
	std::pair<nic::interface_map::iterator, bool> ifi;
	std::auto_ptr<nic::interface> itc(it);
	bool update = false;

	ifi = _ifmap.insert(*it);
	if (ifi.second) {
		itc.release();
		update = true;

	} else {
		boost::logic::tribool prev = ifi.first->up(it->up());
		update = (prev != it->up());
	}

	if (update) {
		odtone::mih::message msg;
		odtone::mih::link_tuple_id lid;
		odtone::mih::link_dn_reason rc(odtone::mih::link_dn_reason_explicit_disconnect);

		lid.type = it->type();
		lid.addr = it->link_addr();

		if (it->up())
			msg << odtone::mih::indication(odtone::mih::indication::link_up)
				& odtone::mih::tlv_link_identifier(lid);

		else if (!it->up())
			msg << odtone::mih::indication(odtone::mih::indication::link_down)
				& odtone::mih::tlv_link_identifier(lid)
				& odtone::mih::tlv_link_dn_reason(rc);
		else
			return;

		_mihf.async_send(msg);
	}
}

/**
 * Default MIH event handler.
 *
 * @param msg Received message.
 * @param ec Error code.
 */
void link_sap::default_handler(odtone::mih::message& msg, const boost::system::error_code& ec)
{
	if (ec)
		return;

	odtone::mih::status st;

	switch (msg.mid()) {
	case odtone::mih::request::capability_discover:
		{
			odtone::mih::message m;

			// fill the status
			st = odtone::mih::status_success;

			m << odtone::mih::confirm(odtone::mih::confirm::capability_discover)
				& odtone::mih::tlv_status(st)
				& odtone::mih::tlv_link_evt_list(capabilities_event_list)
				& odtone::mih::tlv_link_cmd_list(capabilities_command_list);
			m.tid(msg.tid());

			_mihf.async_send(m);
		}
		break;

	case odtone::mih::request::event_subscribe:
		{
			odtone::mih::link_evt_list events;
			msg >> odtone::mih::request()
				& odtone::mih::tlv_link_evt_list(events);

			odtone::mih::message m;

			// fill the status
			st = odtone::mih::status_success;

			m << odtone::mih::confirm(odtone::mih::confirm::event_subscribe)
				& odtone::mih::tlv_status(st)
				& odtone::mih::tlv_link_evt_list(events);
			m.tid(msg.tid());

			_mihf.async_send(m);

			break;
		}

	case odtone::mih::request::event_unsubscribe:
		{
			odtone::mih::link_evt_list events;
			msg >> odtone::mih::request()
				& odtone::mih::tlv_link_evt_list(events);

			odtone::mih::message m;

			// fill the status
			st = odtone::mih::status_success;

			m << odtone::mih::confirm(odtone::mih::confirm::event_unsubscribe)
				& odtone::mih::tlv_status(st)
				& odtone::mih::tlv_link_evt_list(events);
			m.tid(msg.tid());

			_mihf.async_send(m);

			break;
		}
	case odtone::mih::request::link_get_parameters:
		{
			odtone::mih::link_param_list lpl;
			odtone::mih::link_states_rsp_list lsrl;
			odtone::mih::link_desc_rsp_list ldrl;


			odtone::mih::message m;

			// fill the status
			st = odtone::mih::status_success;

			m << odtone::mih::confirm(odtone::mih::confirm::link_get_parameters)
				& odtone::mih::tlv_status(st)
				& odtone::mih::tlv_link_parameters_status_list(lpl)
				& odtone::mih::tlv_link_states_rsp(lsrl)
				& odtone::mih::tlv_link_descriptor_rsp(ldrl);
			m.tid(msg.tid());

			_mihf.async_send(m);

			break;
		}

	case odtone::mih::request::link_configure_thresholds:
		{
			odtone::mih::link_cfg_param_list lcpl;
			msg >> odtone::mih::request()
			       & odtone::mih::tlv_link_cfg_param_list(lcpl);

			odtone::mih::message m;

			// fill the status
			st = odtone::mih::status_failure;
			odtone::mih::link_cfg_status_list lcsl;

			m << odtone::mih::confirm(odtone::mih::confirm::link_configure_thresholds)
				& odtone::mih::tlv_status(st)
				& odtone::mih::tlv_link_cfg_status_list(lcsl);
			m.tid(msg.tid());

			_mihf.async_send(m);

			break;
		}

	default:
		{
			odtone::mih::message m;

			st = odtone::mih::status_failure;

			m << odtone::mih::confirm(odtone::mih::confirm::capability_discover)
				& odtone::mih::tlv_status(st);

			_mihf.async_send(m);
		}
	}
}

/**
 * Initialization of Link SAP. Responsible for sending Link SAP register message
 * to the local MIHF.
 */
void link_sap::init()
{
	odtone::mih::message m;

	m << odtone::mih::indication(odtone::mih::indication::link_register)
	    & odtone::mih::tlv_interface_type_addr(link_id);

	_mihf.async_send(m);
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace link_sap */

// EOF ////////////////////////////////////////////////////////////////////////
