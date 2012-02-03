//==============================================================================
// Brief   : ICMP Link SAP
// Authors : Carlos Guimarães <cguimaraes@av.it.pt>
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

///////////////////////////////////////////////////////////////////////////////
#include "link_sap.hpp"

#include <odtone/bind_rv.hpp>
#include <odtone/logger.hpp>

#include <odtone/mih/indication.hpp>
#include <odtone/mih/request.hpp>
#include <odtone/mih/confirm.hpp>
#include <odtone/mih/tlv_types.hpp>

#include <odtone/net/ip/icmp/icmp.hpp>
#include <odtone/net/ip/icmp/icmp_parser.hpp>

#include <boost/bind.hpp>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////

namespace link_sap {

///////////////////////////////////////////////////////////////////////////////
static odtone::logger log_("link_sap", std::cout);

/**
 * Construct a Link SAP module.
 *
 * @param cfg Configuration information.
 * @param io The io_service object that ICMP Link SAP will use to dispatch
 * handlers for any asynchronous operations performed on the socket.
 * @param ifname Interface name.
 * @param link_id Link identifier.
 * @param capabilities_event_list Supported events.
 * @param capabilities_command_list Supported commands.
 */
link_sap::link_sap(const odtone::mih::config& cfg,
					boost::asio::io_service& io,
					odtone::mih::octet_string ifname,
					odtone::mih::link_id link_id,
					odtone::mih::link_evt_list capabilities_event_list,
					odtone::mih::link_cmd_list capabilities_command_list)
	: _mihf(cfg, io, boost::bind(&link_sap::ieee80221_handler, this, _1, _2)),
	  _icmp_sock(io),
	  _ifname(ifname),
	  _link_id(link_id),
	  _capabilities_event_list(capabilities_event_list),
	  _capabilities_command_list(capabilities_command_list)
{
	register_local_mihf();

	// Init the ICMP socket
	boost::asio::ip::multicast::join_group mo(boost::asio::ip::address_v6::from_string("ff02::2"));
	_icmp_sock.open(boost::asio::ip::icmp::socket::protocol_type::v6());
#ifndef _WIN32
	_icmp_sock.set_option(odtone::net::ip::icmp::filter(true, ND_ROUTER_SOLICIT));
#endif
	_icmp_sock.set_option(mo);

	// Bind the socket to a specific interface
#ifndef _WIN32
	struct ifreq ifr;
	memset(&ifr, 0, sizeof(ifr));
	strncpy(ifr.ifr_name, _ifname.c_str(), sizeof(ifr.ifr_name) - 1);
	if(setsockopt(_icmp_sock.native(), SOL_SOCKET, SO_BINDTODEVICE, (void *)&ifr, sizeof(ifr)) < 0) {
		log_(0, "Cannot bind to specific interface.");
		throw("Cannot bind to specific interface.");
	}
#endif

	icmp_recv_async();
}

/**
 * Destruct a Link SAP module.
 */
link_sap::~link_sap()
{
}

/**
 * ICMP message handler.
 *
 * @param buff Message byte buffer.
 * @param rbytes Size of the received message.
 * @param error Error code.
 */
void link_sap::icmp_handler(odtone::buffer<uint8>& buff, size_t rbytes, const boost::system::error_code& ec)
{
	icmp_recv_async();

	odtone::net::link::address_mac laddr;
	if (!odtone::net::ip::icmp_rs_parse(buff.get(), rbytes, laddr)) {
		log_(0, "Received invalid router solicitation from ", laddr);
		return;
	}

	log_(0, "Received router solicitation from ", laddr);

	odtone::mih::message msg;
	odtone::mih::link_tuple_id lid;

	lid.type = _link_id.type;
	lid.addr = _link_id.addr;
	odtone::mih::mac_addr mn_addr(laddr.to_string());
	lid.poa_addr = mn_addr;

	msg << odtone::mih::indication(odtone::mih::indication::link_up)
			& odtone::mih::tlv_link_identifier(lid);

	_mihf.async_send(msg);

	log_(0, "Sent Link Up indication to the local-mihf");
}

/**
 * IEEE 802.21 message handler.
 *
 * @param buff Received message.
 * @param error Error code.
 */
void link_sap::ieee80221_handler(odtone::mih::message& msg, const boost::system::error_code& ec)
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
				& odtone::mih::tlv_link_evt_list(_capabilities_event_list)
				& odtone::mih::tlv_link_cmd_list(_capabilities_command_list);
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
 * Register the Link SAP with the local MIHF.
 */
void link_sap::register_local_mihf()
{
	odtone::mih::message m;

	m << odtone::mih::indication(odtone::mih::indication::link_register)
	    & odtone::mih::tlv_interface_type_addr(_link_id);

	_mihf.async_send(m);
}

/**
 * Asynchronously receive an ICMP message.
 */
void link_sap::icmp_recv_async()
{
	odtone::buffer<uint8> buff;
	void* rbuff;
	size_t rlen;

	buff = odtone::buffer<uint8>(1500);
	rbuff = buff.get();
	rlen = buff.size();

	_icmp_sock.async_receive(boost::asio::buffer(rbuff, rlen),
								  bind(&link_sap::icmp_handler,
									  this,
									  odtone::bind_rv(buff),
									  boost::asio::placeholders::bytes_transferred,
									  boost::asio::placeholders::error));
}
///////////////////////////////////////////////////////////////////////////////
} /* namespace link_sap */

// EOF ////////////////////////////////////////////////////////////////////////
