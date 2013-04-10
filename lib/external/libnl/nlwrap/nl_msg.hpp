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

#ifndef __NLWRAP_NL_MSG_
#define __NLWRAP_NL_MSG_

#include <boost/noncopyable.hpp>
#include <vector>
#include <string>

#include <netlink/msg.h>

namespace nlwrap {

/**
 * This class provides a RAI wrapper for the nl_msg datatype
 */
class nl_msg : boost::noncopyable {

public:
	/**
	 * Construct a new nl_msg object. Allocates a new nl_msg counterpart.
	 */
	nl_msg();

	/**
	 * Construct a message from an already allocate nl_msg object
	 * and automatically attempt parsing TLV elements.
	 *
	 * @warning This does not deallocate the object upon destruction.
	 *
	 * @param nl_msg The preallocated nl_msg object.
	 */
	nl_msg(::nl_msg *msg);

	/**
	 * Destruct the nl_msg object.
	 * Frees the nl_msg counterpart, if allocated in the object's context.
	 */
	~nl_msg();

	/**
	 * Allow direct usage of the underlying nl_msg pointer.
	 */
	operator ::nl_msg *();

	/**
	 * Get the message type of a parsed message.
	 *
	 * @return The message type of the parsed message.
	 */
	uint16_t type();

	/**
	 * Get the message payload of a parsed message.
	 *
	 * @return The parsed message payload.
	 */
	void *payload();

	/**
	 * Put a list of SSIDs in this message.
	 *
	 * @param ssids The list of ssids.
	 */
	void put_ssids(std::vector<std::string> ssids);

	/**
	 * Put a CQM threshold configuration in the message.
	 * 
	 * @param rssi_threshold The RSSI threshold for the configuration.
	 * @param hysteresis the hysteresis value.
	 */
	void put_cqm(int rssi_threshold, int hysteresis);

protected:
	::nl_msg *_msg;

private:
	bool      _own;
};

}

// EOF ////////////////////////////////////////////////////////////////////////

#endif /* __NLWRAP_NL_MSG_ */
