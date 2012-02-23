//=============================================================================
// Brief   : RTNetlink link cache RAI wrapper
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

#include "rtnl_link_cache.hpp"

namespace nlwrap {

#define ETH_ALEN 18

rtnl_link_cache::rtnl_link_cache()
{
	if (::rtnl_link_alloc_cache(_socket, AF_UNSPEC, &_cache)) {
		throw "Error allocating link cache";
	}
}

rtnl_link_cache::~rtnl_link_cache()
{
	if (_cache) {
		::nl_cache_free(_cache);
	}
}

rtnl_link rtnl_link_cache::get_by_ifindex(int ifindex)
{
	// when "returned" the copy constructor is called, so it gets its own memory
	return rtnl_link(::rtnl_link_get(_cache, ifindex));
}

rtnl_link rtnl_link_cache::get_by_name(std::string name)
{
	// when "returned" the copy constructor is called, so it gets its own memory
	return rtnl_link(::rtnl_link_get_by_name(_cache, name.c_str()));
}

rtnl_link rtnl_link_cache::get_by_addr(std::string address)
{
	// when "returned" the copy constructor is called, so it gets its own memory
	::rtnl_link *l = reinterpret_cast< ::rtnl_link * >(::nl_cache_get_first(_cache));
	while (l != NULL) {
		::nl_addr *addr = ::rtnl_link_get_addr(l);
		if (addr) {
			char mac_addr[ETH_ALEN];
			::nl_addr2str(addr, mac_addr, ETH_ALEN);

			if (address == mac_addr) {
				return rtnl_link(reinterpret_cast< ::rtnl_link * >(::nl_object_clone(reinterpret_cast< ::nl_object * >(l))));
			}
		}

		l = reinterpret_cast< ::rtnl_link * >(::nl_cache_get_next(reinterpret_cast< ::nl_object * >(l)));
	}

	throw "No such link";
}

void rtnl_link_cache::change(rtnl_link &original, rtnl_link &changes)
{
	if (::rtnl_link_change(_socket, original, changes, 0)) {
		throw "Error changing link";
	}
}

}

// EOF ////////////////////////////////////////////////////////////////////////
