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

#ifndef __NLWRAP_RTNL_LINK_
#define __NLWRAP_RTNL_LINK_

#include <string>

#define _LINUX_IF_H // workaround
#include <netlink/route/link.h>

namespace nlwrap {

/**
 * This class provides a RAI wrapper for the rtnl_link datatype
 */
class rtnl_link {

public:

	/**
	 * Construct a new rtnl_link object.
	 * Automatically allocates the underlying rtnl_link struct.
	 */
	rtnl_link();

	/**
	 * Construct an rtnl_link object from a preallocated rtnl_link struct.
	 * 
	 * @warning This does not deallocate the object upon destruction.
	 *
	 * @param link The preallocated rtnl_link struct.
	 */
	rtnl_link(::rtnl_link *link);

	/**
	 * Copy constructor from another rtnl_link object.
	 *
	 * @warning Unlike rtnl_link(::rtnl_link *),
	 *          this effectively copies the object,
	 *          and deallocates it on destruction.
	 *
	 * @param copy The object to copy.
	 */
	explicit rtnl_link(const rtnl_link &copy);

	/**
	 * Destruct the object. Frees the underlying rtnl_link struct, if allocated on this obect's context.
	 */
	~rtnl_link();

	/**
	 * Allow direct usage of the underlying rtnl_link pointer.
	 */
	operator ::rtnl_link *();

	/**
	 * Similar to constructing from a rtnl_link struct pointer.
	 *
	 * @param link The struct pointer to construct from.
	 */
	rtnl_link &operator =(::rtnl_link *link);

	/**
	 * Get the MAC address from this link.
	 *
	 * @return The MAC address of this link.
	 */
	std::string address();

	/**
	 * Get the IFINDEX of this link.
	 *
	 * @return The IFINDEX of this link.
	 */
	int ifindex();

	/**
	 * Get the device name of this link.
	 *
	 * @return The device name of this link.
	 */
	std::string name();

	/**
	 * Get the current flags from this link.
	 *
	 * @return The flags from this link.
	 */
	unsigned int get_flags();

	/**
	 * Set flags on this link.
	 *
	 * @param flags The flags to set on this link.
	 */
	void set_flags(unsigned int flags);

	/**
	 * Unset flags on this link.
	 *
	 * @param flags The flags to unset on this link.
	 */
	void unset_flags(unsigned int flags);

	/**
	 * Get this link's operstate flags.
	 *
	 * @return The current operstate flags for this link.
	 */
	uint8_t get_operstate();

private:
	bool         _own;
	::rtnl_link *_link;
};

}

// EOF ////////////////////////////////////////////////////////////////////////

#endif /* __NLWRAP_RTNL_LINK_ */
