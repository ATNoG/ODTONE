//=============================================================================
// Brief   : Netlink callback RAI wrapper
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

#ifndef __NLWRAP_NL_CB_
#define __NLWRAP_NL_CB_

#include <boost/noncopyable.hpp>

#include <netlink/msg.h>

namespace nlwrap {

/**
 * This class provides a RAI wrapper for the nl_cb datatype
 */
class nl_cb : boost::noncopyable {

public:
	/**
	 * Construct a genl_cb object.
	 * Allocs memory for a new nl_cb and locally defines standard callbacks.
	 */
	nl_cb();

	/**
	 * Construct a genl_cb object.
	 * Allocs memory for a new nl_cb and locally defines standard callbacks,
	 * plus a provided one for VALID message types.
	 *
	 * @param func The handler for valid messages.
	 * @param arg Parameter to pass do the handler.
	 */
	nl_cb(::nl_recvmsg_msg_cb_t func, void *arg);

	/**
	 * Destroy the genl_cb object. Deallocates the nl_cb counterpart.
	 */
	~nl_cb();

	/**
	 * Allow direct usage of nl_cb pointer when needed.
	 */
	operator ::nl_cb *();

	/**
	 * Provide a custom handler for an already constructed callback.
	 *
	 * @param func The handler for valid messages.
	 * @param arg Parameter to pass do the handler.
	 */
	void custom(::nl_recvmsg_msg_cb_t func, void *arg);

	/**
	 * Check if finish (or error) was already handled on this callback.
	 *
	 * @return True if finish (or error) was handled, false otherwise.
	 */
	bool finish();

	/**
	 * Check if an error was handled by this callback.
	 *
	 * @return True if an error ocurred on this callback, false otherwise.
	 */
	bool error();

	/**
	 * Get the current error code for this callback.
	 *
	 * @return The current error code for this callback.
	 *         If negative, check the meaning from errno.h.
	 */
	int error_code();

private:
	::nl_cb *_cb;
	int      _err;
};

}

// EOF ////////////////////////////////////////////////////////////////////////

#endif /* __NLWRAP_NL_CB_ */
