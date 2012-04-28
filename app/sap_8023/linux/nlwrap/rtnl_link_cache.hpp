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

#ifndef __NLWRAP_RTNL_LINK_CACHE_
#define __NLWRAP_RTNL_LINK_CACHE_

#include <boost/noncopyable.hpp>
#include <string>

#include "rtnl_socket.hpp"
#include "rtnl_link.hpp"

namespace nlwrap {

/**
 * This class provides a RAI wrapper for the rtnl_link_cache datatype
 */
class rtnl_link_cache : boost::noncopyable {

public:
	/**
	 * Construct a new rtnl_link_cache object.
	 * Automatically allocates a struct counterpart.
	 */
	rtnl_link_cache();

	/**
	 * Destruct the object. Frees the underlying struct.
	 */
	~rtnl_link_cache();

	/**
	 * Get a link by IFINDEX.
	 *
	 * @param ifindex The IFINDEX of the desired link.
	 *
	 * @return The specified link.
	 */
	rtnl_link get_by_ifindex(int ifindex);

	/**
	 * Get a link by device name
	 *
	 * @param name The device name of the desired link.
	 *
	 * @return The specified link.
	 */
	rtnl_link get_by_name(std::string name);

	/**
	 * Get a link by MAC address.
	 *
	 * @param address The MAC address of the desired link.
	 *
	 * @return The specified link.
	 */
	rtnl_link get_by_addr(std::string address);

	/**
	 * Change a link in the system.
	 *
	 * @param original The original link.
	 * @param changes The changes to apply.
	 */
	void change(rtnl_link &original, rtnl_link &changes);

private:
	bool         _own;
	rtnl_socket  _socket;
	::nl_cache  *_cache;
};

}

// EOF ////////////////////////////////////////////////////////////////////////

#endif /* __NLWRAP_RTNL_LINK_CACHE_ */
