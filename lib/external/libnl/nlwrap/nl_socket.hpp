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

#ifndef __NLWRAP_NL_SOCKET_
#define __NLWRAP_NL_SOCKET_

#include <boost/noncopyable.hpp>

#include <netlink/socket.h>
#include "nl_msg.hpp"
#include "nl_cb.hpp"

namespace nlwrap {
	
/**
 * This class provides a RAI wrapper for the nl_sock datatype on the ROUTE_NETLINK protocol.
 */
class nl_socket : boost::noncopyable {

public:
	/**
	 * Construct a new nl_socket object.
	 * Automatically allocates the underlying nl_sock struct
	 */
	nl_socket();

	/**
	 * Destruct the object.
	 * Automatically disconnects and frees the underlying socket.
	 */
	~nl_socket();

	/**
	 * Allow direct usage of the underlying struct pointer.
	 */
	operator ::nl_sock *();

	/**
	 * Join a multicast group in this socket.
	 *
	 * @param group The multicast group to join.
	 */
	void join_multicast_group(int group);

	/**
	 * Send a message on this socket.
	 *
	 * @param msg The message to send.
	 */
	void send(nl_msg &msg);

	/**
	 * Attempt receiving a message on this socket, and handle it in a callback.
	 *
	 * @param cb The callback to handle de message with.
	 */
	void receive(nl_cb &cb);

protected:
	::nl_sock *_sock;
};

}

// EOF ////////////////////////////////////////////////////////////////////////

#endif /* __NLWRAP_NL_SOCKET_ */
