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

#ifndef __NLWRAP_GENL_SOCKET_
#define __NLWRAP_GENL_SOCKET_

#include <boost/noncopyable.hpp>
#include <string>

#include <linux/nl80211.h>

#include <netlink/socket.h>

#include "genl_msg.hpp"
#include "genl_cb.hpp"

namespace nlwrap {

/**
 * This class provides a RAI wrapper for the nl_sock datatype on the GENERIC_NETLINK protocol.
 */
class genl_socket : boost::noncopyable {

public:
	/**
	 * Construct a new genl_socket object.
	 * Automatically attempts allocation and connection to the GENERIC protocol.
	 */
	genl_socket();

	/**
	 * Destruct the object. Frees and closes the underlying socket.
	 */
	~genl_socket();

	/**
	 * Allow direct usage of the nl_sock pointer.
	 */
	operator ::nl_sock *();

	/**
	 * Send a message on this socket.
	 *
	 * @param msg The message to send.
	 */
	void send(genl_msg &msg);

	/**
	 * Attempt receiving a message on this socket, and handle it in a callback.
	 *
	 * @param cb The callback to handle de message with.
	 */
	void receive(genl_cb &cb);

	/**
	 * Get a family_id for a family, on this socket.
	 *
	 * @param family The family name.
	 */
	int family_id(std::string family);

	/**
	 * Get the multicast_id of a group in this socket.
	 *
	 * @param group The multicast group name.
	 */
	int multicast_id(std::string group);

	/**
	 * Join a multicast group in this socket.
	 *
	 * @param group The multicast group to join.
	 */
	void join_multicast_group(std::string group);

private:
	::nl_sock *_sock;
};

}

// EOF ////////////////////////////////////////////////////////////////////////

#endif /* __NLWRAP_GENL_SOCKET_ */
