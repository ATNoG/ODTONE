//=============================================================================
// Brief   : Netlink socket RAI wrapper
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

#include "nl_socket.hpp"

#include <netlink/route/link.h>

#include <stdexcept>

namespace nlwrap {

nl_socket::nl_socket()
{
	_sock = ::nl_socket_alloc();
	if (!_sock) {
		throw std::runtime_error("Error allocating netlink socket");
	}
}

nl_socket::~nl_socket()
{
	if (_sock) {
		::nl_close(_sock);
		::nl_socket_free(_sock);
	}
}

nl_socket::operator ::nl_sock *()
{
	return _sock;
}

void nl_socket::join_multicast_group(int group)
{
	if (::nl_socket_add_membership(_sock, group)) {
		throw std::runtime_error("Error joining multicast group");
	}
}

void nl_socket::send(nl_msg &msg)
{
	if (::nl_send_auto_complete(_sock, msg) < 0) {
		throw std::runtime_error("Error sending netlink message");
	}
}

void nl_socket::receive(nl_cb &cb)
{
	::nl_recvmsgs(_sock, cb);
}

}

// EOF ////////////////////////////////////////////////////////////////////////
