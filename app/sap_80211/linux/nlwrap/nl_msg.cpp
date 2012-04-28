//=============================================================================
// Brief   : Netlink message RAI wrapper
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

#include "nl_msg.hpp"

#include <stdexcept>

namespace nlwrap {

nl_msg::nl_msg()
{
	_msg = ::nlmsg_alloc();
	if (!_msg) {
		throw std::runtime_error("Error allocating netlink message");
	}
	_own = true;
}

nl_msg::nl_msg(::nl_msg *msg)
{
	_own = false;
	_msg = msg;
}

nl_msg::~nl_msg()
{
	if (_own && _msg) {
		::nlmsg_free(_msg);
	}
}

nl_msg::operator ::nl_msg *()
{
	return _msg;
}

}
