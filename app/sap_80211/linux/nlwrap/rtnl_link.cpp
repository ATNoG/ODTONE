//=============================================================================
// Brief   : RTNetlink link RAI wrapper
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

#include "rtnl_link.hpp"

namespace nlwrap {

#define ETH_ALEN 18

rtnl_link::rtnl_link()
{
	_link = ::rtnl_link_alloc();
	if (!_link) {
		throw "Error allocating rtnl_link";
	}

	_own = true;
}

rtnl_link::rtnl_link(::rtnl_link *link)
{
	_link = link;
	_own = false;
}

rtnl_link::rtnl_link(const rtnl_link &copy)
{
	_link = reinterpret_cast< ::rtnl_link * >(::nl_object_clone(reinterpret_cast< ::nl_object * >(copy._link)));
	if (!_link) {
		throw "Error cloning rtnl_link";
	}

	_own = true;
}

rtnl_link::~rtnl_link()
{
	if (_own && _link) {
		::rtnl_link_put(_link);
	}
}

rtnl_link::operator ::rtnl_link *()
{
	return _link;
}

rtnl_link &rtnl_link::operator =(::rtnl_link *link)
{
	if (_own && _link) {
		::rtnl_link_put(_link);
	}

	_link = link;
	_own = false;

	return *this;
}

std::string rtnl_link::address()
{
	char mac_addr[ETH_ALEN];
	::nl_addr *addr = ::rtnl_link_get_addr(_link);
	if (!addr) {
		throw "Error getting link address";
	}

	::nl_addr2str(addr, mac_addr, ETH_ALEN);
	return std::string(mac_addr);
}

int rtnl_link::ifindex()
{
	int ifindex = ::rtnl_link_get_ifindex(_link);
	if (ifindex == 0) {
		throw "Error getting link if index";
	}

	return ifindex;
}

std::string rtnl_link::name()
{
	char *name = ::rtnl_link_get_name(_link);
	if (!name) {
		throw "Error getting link name";
	}

	return std::string(name);
}

unsigned int rtnl_link::get_flags()
{
	return ::rtnl_link_get_flags(_link);
}

void rtnl_link::set_flags(unsigned int flags)
{
	::rtnl_link_set_flags(_link, flags);
}

void rtnl_link::unset_flags(unsigned int flags)
{
	::rtnl_link_unset_flags(_link, flags);
}

}

// EOF ////////////////////////////////////////////////////////////////////////
