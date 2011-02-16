//==============================================================================
// Brief   : Service Access Controller
// Authors : Simao Reis <sreis@av.it.pt>
//------------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2009-2011 Universidade Aveiro
// Copyright (C) 2009-2011 Instituto de Telecomunicações - Pólo Aveiro
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
 * Checks if the message id is supported by the MIHF, but doesn't try to send
 * the message directly, it just returns to the transaction state machine that
 * called it.
 *
 * @param in input message.
 * @param out output message.
 */
bool sac_process_message(meta_message_ptr& in, meta_message_ptr& out);

/**
 * This class is called by the local communications listening service and checks
 * if the message id is supported. If so, the message is processed by a previously
 * declared handler.
 */
class sac_dispatch {
public:
	/**
	 * Service Access Controller constructor.
	 *
	 * @param t transmit module.
	 */
	sac_dispatch(transmit &t);

	/**
	 * Check if there's a handler for this message and call it, else
	 * discard message.
	 *
	 * @param in input message.
	 */
	void operator()(meta_message_ptr &msg);
protected:
	transmit &_transmit;
};

/**
 * Registering a callback handler for a MIH message.
 * This should only be used on MIHF initialization because it's not thread safe.
 *
 * @param mid MIH Message ID.
 * @param func handler function.
 */
void sac_register_callback(uint mid, handler_t f);

} /* namespace mihf */ } /* namespace odtone */

#endif
