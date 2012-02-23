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

#ifndef __NLWRAP_RTNL_SOCKET_
#define __NLWRAP_RTNL_SOCKET_

#include <boost/noncopyable.hpp>

#include <netlink/socket.h>

namespace nlwrap {
	
/**
 * This class provides a RAI wrapper for the nl_sock datatype on the ROUTE_NETLINK protocol.
 */
class rtnl_socket : boost::noncopyable {

public:
	/**
	 * Construct a new rtnl_socket object.
	 * Automatically allocates the underlying nl_sock struct, and attempts
	 * connection to the ROUTE_NETLINK protocol.
	 */
	rtnl_socket();

	/**
	 * Destruct the object.
	 * Automatically disconnects and frees the underlying socket.
	 */
	~rtnl_socket();

	/**
	 * Allow direct usage of the underlying struct pointer.
	 */
	operator ::nl_sock *();

private:
	::nl_sock *_sock;
};

}

// EOF ////////////////////////////////////////////////////////////////////////

#endif /* __NLWRAP_RTNL_SOCKET_ */
