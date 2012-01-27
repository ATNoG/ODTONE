//==============================================================================
// Brief   : Service Access Controller
// Authors : Simao Reis <sreis@av.it.pt>
//------------------------------------------------------------------------------
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

#ifndef ODTONE_MIHF_SERVICE_ACCESS_CONTROLLER_HPP
#define ODTONE_MIHF_SERVICE_ACCESS_CONTROLLER_HPP

///////////////////////////////////////////////////////////////////////////////
#include "utils.hpp"
#include "transmit.hpp"
#include "meta_message.hpp"

///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

/**
 * Check if there's a handler for this message and call it, else
 * discard message.
 *
 * @param in The input message.
 * @param out The output message.
 */
bool sac_process_message(meta_message_ptr& in, meta_message_ptr& out);

/**
 * This class is called for every message received from a local entity.
 * It checks if there is a handler for this message and call it, else
 * discard message.
 */
class sac_dispatch {
public:
	/**
	 * Construct a Service Access Controller.
	 *
	 * @param t The transmit module.
	 */
	sac_dispatch(transmit &t);

	/**
	 * Check if there is a handler for this message and call it, else
	 * discard message.
	 *
	 * @param in The input message.
	 */
	void operator()(meta_message_ptr &msg);
protected:
	transmit &_transmit;	/**< The transmit module.	*/
};

/**
 * Registering a callback handler for a MIH message identifier.
 * This should only be used on MIHF initialization because it's not thread safe.
 *
 * @param mid The MIH Message identifier.
 * @param func The handler function.
 */
void sac_register_callback(uint mid, handler_t f);

} /* namespace mihf */ } /* namespace odtone */

#endif
