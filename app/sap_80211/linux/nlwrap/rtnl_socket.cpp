//=============================================================================
// Brief   : RTNetlink socket RAI wrapper
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

#include "rtnl_socket.hpp"

#include <netlink/route/link.h>

#include <stdexcept>

namespace nlwrap {

rtnl_socket::rtnl_socket()
{
	_sock = ::nl_socket_alloc();
	if (!_sock) {
		throw std::runtime_error("Error allocating netlink socket");
	}

	if (::nl_connect(_sock, NETLINK_ROUTE)) {
		throw std::runtime_error("Error connecting to ROUTE protocol");
	}
}

rtnl_socket::~rtnl_socket()
{
	if (_sock) {
		::nl_close(_sock);
		::nl_socket_free(_sock);
	}
}

rtnl_socket::operator ::nl_sock *()
{
	return _sock;
}

}

// EOF ////////////////////////////////////////////////////////////////////////
