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
#include "information_service.hpp"
#include "log.hpp"
#include "utils.hpp"
#include "mihfid.hpp"
#include "transmit.hpp"

#include <odtone/debug.hpp>
#include <odtone/mih/request.hpp>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

information_service::information_service(local_transaction_pool &lpool)
	: _lpool(lpool)
{
}

bool information_service::get_information_request(mih::message_ptr &in,
						  mih::message_ptr &out)
{
	log(1, "(miis) received a Get_Information.request from",
	    in->source().to_string());

	if(utils::is_local_request(in)) {
		//
		// Kick this message to Information Service.
		//
		in->destination(mih::id("miis"));
		in->opcode(mih::operation::indication);
		_lpool.add(in);
		in->source(mihfid);
		// transmit(in);

		return false;
	} else 	{
		return utils::forward_request(in);
	}

	return false;
}


bool information_service::get_information_response(mih::message_ptr &in,
						   mih::message_ptr &out)
{
	log(1, "(miis) received Get_Information.response from ",
	    in->source().to_string());

	pending_transaction p;
	if(!_lpool.get(in->source().to_string(), p)) {
		log(1, "(mics) warning: no local transaction for this msg ",
		    "discarding it");
		return false;
	}

	in->tid(p.tid);
	in->destination(mih::id(p.user));

	in->source(mihfid);
	in->opcode(mih::operation::confirm);

	log(1, "(miis) forwarding Get_Information.response to ", p.user);

	// transmit(in);

	return false;
}


bool information_service::push_information_request(mih::message_ptr &in,
						   mih::message_ptr &out)
{
	log(1, "(miis) received a Get_Information.request from",
	    in->source().to_string());

	if(utils::is_local_request(in)) {
		//
		// Kick this message to Information Service.
		//
		in->destination(mih::id("miis"));
		_lpool.add(in);
		in->source(mihfid);
		// transmit(in);

		return false;
	} else {
		return utils::forward_request(in);
	}

	return false;
}


bool information_service::push_information_indication(mih::message_ptr &in,
						      mih::message_ptr &out)
{
	log(1, "(miis) received Push_Information.indication from ",
	    in->source().to_string());

	pending_transaction p;

	if(!_lpool.get(in->source().to_string(), p)) {
		log(1, "(mics) warning: no local transaction for this msg ",
		    "discarding it");

		return false;
	}

	in->tid(p.tid);
	in->source(mihfid);
	in->destination(mih::id(p.user));

	log(1, "(miis) forwarding Push_Information.indication to ", p.user);

	// transmit(in);

	return false;
}

} /* namespace mihf */ } /* namespace odtone */
