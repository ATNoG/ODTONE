//
// Copyright (c) 2007-2009 2009 Universidade Aveiro - Instituto de
// Telecomunicacoes Polo Aveiro
// This file is part of ODTONE - Open Dot Twenty One.
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//
// Author:     Simao Reis <sreis@av.it.pt>
//

///////////////////////////////////////////////////////////////////////////////
#include "service_access_controller.hpp"
#include "meta_message.hpp"
#include "log.hpp"

#include <odtone/debug.hpp>
#include <odtone/mih/config.hpp>
#include <odtone/mih/request.hpp>
#include <odtone/mih/response.hpp>
#include <odtone/mih/indication.hpp>

#include <map>
///////////////////////////////////////////////////////////////////////////////


namespace odtone { namespace mihf {

static std::map<uint, handler_t> _callbacks;

//
// This should __only__ be used on MIHF initialization because it's
// __not__ thread safe.
//
void sac_register_callback(uint mid, handler_t func)
{
	_callbacks[mid] = func;
}

sac_dispatch::sac_dispatch(transmit &t)
	: _transmit(t)
{
}

void sac_dispatch::operator()(meta_message_ptr& in)
{
	/** __no__ authentication at this point */

	uint mid = in->mid();

	log(1, "(sac) dispatching message with mid: ", mid);
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
		if (process_message(in, out))
		 	_transmit(out);
        } else {
		log(1, "(sac) (warning) message with mid: ", mid,
		    " unknown, discarding.");
	}
}

bool sac_process_message(meta_message_ptr& in, meta_message_ptr& out)
{
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
		out->tid(in->tid());

		return rsp;
	} else {
		log(1, "(sac) (warning) message with mid: ", mid,
		    " unknown, discarding.");
	}

	return false;
}

} /* namespace mihf */ } /* namespace odtone */
