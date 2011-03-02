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

///////////////////////////////////////////////////////////////////////////////
#include "service_access_controller.hpp"
#include "meta_message.hpp"
#include "log.hpp"
#include "mihfid.hpp"

#include <odtone/debug.hpp>
#include <odtone/mih/config.hpp>
#include <odtone/mih/request.hpp>
#include <odtone/mih/response.hpp>
#include <odtone/mih/indication.hpp>

#include <map>
///////////////////////////////////////////////////////////////////////////////


namespace odtone { namespace mihf {

static std::map<uint, handler_t> _callbacks;

/**
 * Registering a callback handler for a MIH message.
 * This should only be used on MIHF initialization because it's not thread safe.
 *
 * @param mid MIH Message ID.
 * @param func handler function.
 */
void sac_register_callback(uint mid, handler_t func)
{
	_callbacks[mid] = func;
}

/**
 * Service Access Controller constructor.
 *
 * @param t transmit module.
 */
sac_dispatch::sac_dispatch(transmit &t)
	: _transmit(t)
{
}

/**
 * Checks if the message id is supported by the MIHF, but doesn't try to send
 * the message directly, it just returns to the transaction state machine that
 * called it.
 *
 * @param in input message.
 */
void sac_dispatch::operator()(meta_message_ptr& in)
{
	/** __no__ authentication at this point */

	uint mid = in->mid();

	ODTONE_LOG(1, "(sac) dispatching message with mid: ", mid);
	//
	// no thread safety because insertion should __only__ be made
	// on MIHF initialization
	//
	std::map<uint, handler_t>::iterator it;
	it = _callbacks.find(mid);

	if(it != _callbacks.end()) {
		handler_t process_message = it->second;
		meta_message_ptr out(new meta_message);

		out->tid(in->tid());
		// send response if it was generated
		if (process_message(in, out))
		 	_transmit(out);
        } else {
		ODTONE_LOG(1, "(sac) (warning) message with mid: ", mid,
		    " unknown, discarding.");
	}
}

/**
 * Check if there's a handler for this message and call it, else
 * discard message.
 *
 * @param in input message.
 * @param out output message.
 */
bool sac_process_message(meta_message_ptr& in, meta_message_ptr& out)
{
	// discard messages that this MIHF broadcasted to itself
	if (in->source() == mihfid)
		return false;

	/** __no__ authentication at this point */

	uint mid = in->mid();

	//
	// no thread safety because insertion should __only__ be made
	// on MIHF initialization
	//
	std::map<uint, handler_t>::iterator it;
	it = _callbacks.find(mid);

	if(it != _callbacks.end()) {
		handler_t process_message = it->second;

		bool rsp = process_message(in, out);

		// set ip and port of response message
		out->ip(in->ip());
		out->port(in->port());

		// response message must have the same tid
		out->tid(in->tid());

		return rsp;
	} else {
		ODTONE_LOG(1, "(sac) (warning) message with mid: ", mid,
		    " unknown, discarding.");
	}

	return false;
}

} /* namespace mihf */ } /* namespace odtone */
