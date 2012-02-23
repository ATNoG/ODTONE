//=============================================================================
// Brief   : GENetlink socket RAI wrapper
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

#include "genl_socket.hpp"

#include <netlink/netlink.h>
#include <netlink/genl/genl.h>
#include <netlink/genl/ctrl.h>

#include <errno.h>

#include <iostream>

namespace nlwrap {

struct handler_args {
	const char *group;
	int id;
};

int family_handler(::nl_msg *msg, void *arg);

genl_socket::genl_socket()
{
	_sock = ::nl_socket_alloc();
	if (!_sock) {
		throw "Error allocating socket";
	}

	if (::genl_connect(_sock)) {
		throw "Error connecting to GENERIC protocol";
	}
}

genl_socket::~genl_socket()
{
	if (_sock) {
		::nl_close(_sock);
		::nl_socket_free(_sock);
	}
}

genl_socket::operator nl_sock *()
{
	return _sock;
}

void genl_socket::send(genl_msg &msg)
{
	if (::nl_send_auto_complete(_sock, msg) < 0) {
		throw "Error sending netlink message";
	}
}

void genl_socket::receive(genl_cb &cb)
{
	::nl_recvmsgs(_sock, cb);
}

int genl_socket::family_id(std::string family)
{
	return ::genl_ctrl_resolve(_sock, family.c_str());
}

int genl_socket::multicast_id(std::string group)
{
	genl_socket s;
	genl_msg m(s.family_id("nlctrl"), CTRL_CMD_GETFAMILY, 0);
	m.put_family_name("nl80211");

	genl_cb cb;
	s.send(m);

	handler_args grp = { group.c_str(), -ENOENT };
	cb.custom(family_handler, static_cast<void *>(&grp));

	while (!cb.finish()) {
		s.receive(cb);
	}

	if (cb.error()) {
		throw "Error getting multicast id";
	}

	return grp.id;
}

void genl_socket::join_multicast_group(std::string group)
{
	if(::nl_socket_add_membership(_sock, multicast_id(group))) {
		throw "Error joining multicast group";
	}
}

int family_handler(nl_msg *msg, void *arg) {
	handler_args *grp = (handler_args *)arg;
	::nlattr *tb[CTRL_ATTR_MAX + 1];
	::genlmsghdr *gnlh = static_cast< ::genlmsghdr * >(::nlmsg_data(::nlmsg_hdr(msg)));
	::nlattr *mcgrp;
	int rem_mcgrp;

	::nla_parse(tb, CTRL_ATTR_MAX, ::genlmsg_attrdata(gnlh, 0), ::genlmsg_attrlen(gnlh, 0), NULL);

	if (!tb[CTRL_ATTR_MCAST_GROUPS]) {
		return NL_SKIP;
	}

	mcgrp = static_cast< ::nlattr * >(::nla_data(tb[CTRL_ATTR_MCAST_GROUPS]));
	rem_mcgrp = ::nla_len(tb[CTRL_ATTR_MCAST_GROUPS]);
	for ( ; ::nla_ok(mcgrp, rem_mcgrp); mcgrp = ::nla_next(mcgrp, &(rem_mcgrp))) {
	// causes compilation warning, conversion from void* to nlattr*
	//nla_for_each_nested(mcgrp, tb[CTRL_ATTR_MCAST_GROUPS], rem_mcgrp) {
		::nlattr *tb_mcgrp[CTRL_ATTR_MCAST_GRP_MAX + 1];

		::nla_parse(tb_mcgrp, CTRL_ATTR_MCAST_GRP_MAX, static_cast< ::nlattr * >(::nla_data(mcgrp)), ::nla_len(mcgrp), NULL);

		if (!tb_mcgrp[CTRL_ATTR_MCAST_GRP_NAME] || !tb_mcgrp[CTRL_ATTR_MCAST_GRP_ID]) {
			continue;
		}
		if (::strncmp(static_cast<char *>(::nla_data(tb_mcgrp[CTRL_ATTR_MCAST_GRP_NAME])),
			grp->group, ::nla_len(tb_mcgrp[CTRL_ATTR_MCAST_GRP_NAME]))) {
			continue;
		}
		grp->id = ::nla_get_u32(tb_mcgrp[CTRL_ATTR_MCAST_GRP_ID]);
		break;
	}

	return NL_SKIP;
}

}

// EOF ////////////////////////////////////////////////////////////////////////
