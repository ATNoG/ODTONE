//=============================================================================
// Brief   : Netlink interface for 802.3 devices
// Authors : André Prata <andreprata@av.it.pt>
//-----------------------------------------------------------------------------
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

#define MAC_ALEN 18

#include "if_8023.hpp"
#include <boost/thread.hpp>
#include <boost/scope_exit.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

#include <odtone/mih/tlv_types.hpp>

#include <odtone/logger.hpp>
#include <iostream>
#include <stdexcept>

#include "nlwrap/nlwrap.hpp"

using namespace odtone;

static logger log_("if_8023", std::cout);

///////////////////////////////////////////////////////////////////////////////

#define IF_OPER_UP 6
int handle_nl_event(nl_msg *msg, void *arg)
{
	if_8023::ctx_data *ctx = static_cast<if_8023::ctx_data *>(arg);

	nlwrap::nl_msg m(msg);
	::ifinfomsg *ifi = static_cast< ::ifinfomsg * >(m.payload());

	if (m.type() != RTM_NEWLINK) {
		return NL_SKIP;
	}

	if (ifi->ifi_index != ctx->_ifindex) {
		return NL_SKIP;
	}

	mih::link_tuple_id lid;
	lid.type = mih::link_type_ethernet;
	lid.addr = ctx->_mac;

	boost::optional<mih::link_addr> old_router;

	nlwrap::rtnl_link_cache cache;
	nlwrap::rtnl_link link(cache.get_by_ifindex(ctx->_ifindex));

	bool active = link.get_operstate() == IF_OPER_UP;
	if (active != ctx->_active) {
		ctx->_active = active;

		if (active) {
			log_(0, "(event) IF_OPER_UP");

			boost::optional<mih::link_addr> new_router;
			boost::optional<bool> ip_renew;
			boost::optional<mih::ip_mob_mgmt> mobility_management;
			ctx->_ios.dispatch(boost::bind(ctx->_up_handler.get(),
			                               lid,
			                               old_router,
			                               new_router,
			                               ip_renew,
			                               mobility_management));
		} else {
			log_(0, "(event) ~IF_OPER_UP");
			mih::link_dn_reason rs = mih::link_dn_reason(mih::link_dn_reason_explicit_disconnect);;

			ctx->_ios.dispatch(boost::bind(ctx->_down_handler.get(), lid, old_router, rs));
		}
	}

	return NL_SKIP;
}

void recv_forever(nlwrap::rtnl_socket &sock, nlwrap::nl_cb &cb)
{
	while (!cb.finish()) {
		sock.receive(cb);
	}

	throw std::runtime_error("Unexpected netlink error, code " + boost::lexical_cast<std::string>(cb.error_code()));
}

///////////////////////////////////////////////////////////////////////////////

if_8023::if_8023(boost::asio::io_service &ios, mih::mac_addr mac) : _ctx(ios)
{
	// set variables
	_ctx._mac = mac;

	nlwrap::rtnl_link_cache cache;
	nlwrap::rtnl_link link(cache.get_by_addr(mac.address()));

	_ctx._ifindex = link.ifindex();
	_ctx._active = link.get_operstate() == IF_OPER_UP;

	// initalize socket
	_socket.join_multicast_group(RTMGRP_LINK);
	_callback.custom(handle_nl_event, &_ctx);

	boost::thread rcv(boost::bind(recv_forever, boost::ref(_socket), boost::ref(_callback)));
}

if_8023::~if_8023()
{
}

unsigned int if_8023::ifindex()
{
	return _ctx._ifindex;
}

mih::mac_addr if_8023::mac_address()
{
	return _ctx._mac;
}

mih::link_id if_8023::link_id()
{
	mih::link_id id;
	id.type = mih::link_type_ethernet;
	id.addr = _ctx._mac;

	return id;
}

bool if_8023::link_up()
{
	nlwrap::rtnl_link_cache cache;
	nlwrap::rtnl_link link(cache.get_by_ifindex(_ctx._ifindex));

	return link.get_flags() & IFF_RUNNING;
}

mih::op_mode_enum if_8023::get_op_mode()
{
	nlwrap::rtnl_link_cache cache;
	nlwrap::rtnl_link link(cache.get_by_ifindex(_ctx._ifindex));

	if (!(link.get_flags() & IFF_UP)) {
		return mih::op_mode_powered_down;
	}

	// No powersave support

	return mih::op_mode_normal;
}

void if_8023::set_op_mode(const mih::link_ac_type_enum &mode)
{
	log_(0, "(command) Setting link op_mode");

	nlwrap::rtnl_link change;

	switch (mode) {
	case odtone::mih::link_ac_type_none:
		return;
		break;

	case odtone::mih::link_ac_type_power_down:
		change.unset_flags(IFF_UP);
		break;

	case odtone::mih::link_ac_type_power_up:
		change.set_flags(IFF_UP);
		break;

	case odtone::mih::link_ac_type_disconnect:
		// TODO
		break;

	case odtone::mih::link_ac_type_low_power:
	default:
		throw std::runtime_error("Mode not supported");
		break;
	}

	nlwrap::rtnl_link_cache cache;
	nlwrap::rtnl_link link(cache.get_by_ifindex(_ctx._ifindex));
	cache.change(link, change);
}

void if_8023::link_up_callback(const link_up_handler &h)
{
	_ctx._up_handler = h;
}

void if_8023::link_down_callback(const link_down_handler &h)
{
	_ctx._down_handler = h;
}

// EOF ////////////////////////////////////////////////////////////////////////
