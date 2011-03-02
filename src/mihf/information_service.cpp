//==============================================================================
// Brief   : Information Service
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
#include "information_service.hpp"
#include "log.hpp"
#include "utils.hpp"
#include "mihfid.hpp"
#include "transmit.hpp"

#include <odtone/debug.hpp>
#include <odtone/mih/request.hpp>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

/**
 * Information service constructor.
 *
 * @param lpool local transction pool.
 * @param t transmit module.
 */
information_service::information_service(local_transaction_pool &lpool,
					 transmit &t)
	: _lpool(lpool),
	  _transmit(t)
{
}

/**
 * Get Information Request message handler.
 *
 * Currently Information_Service messages are handled by a default local
 * Information server. If this MIHF is the destination of the message,
 * forward it to the default server. Add a local transaction indicating
 * where to send the response.
 *
 * @param in input message.
 * @param out output message.
 * @return true if the response is sent immediately or false otherwise.
 */
bool information_service::get_information_request(meta_message_ptr &in,
						  meta_message_ptr &out)
{
	ODTONE_LOG(1, "(miis) received a Get_Information.request from",
	    in->source().to_string());

	if(utils::this_mihf_is_destination(in)) {
		//
		// Kick this message to Information Service.
		//
		in->destination(mih::id("miis"));
		in->opcode(mih::operation::indication);
		_lpool.add(in);
		in->source(mihfid);
		_transmit(in);

		return false;
	} else {
		utils::forward_request(in, _lpool, _transmit);
		return false;
	}

	return false;
}

/**
 * Get Information Response message handler.
 *
 * Currently Information_Service messages are handled by a default local
 * server. If this MIHF is the destination of the message, check for a
 * pending transaction and forward the message.
 *
 * @param in input message.
 * @param out output message.
 * @return true if the response is sent immediately or false otherwise.
 */
bool information_service::get_information_response(meta_message_ptr &in,
						   meta_message_ptr &out)
{
	ODTONE_LOG(1, "(miis) received Get_Information.response from ",
	    in->source().to_string());

	if(!_lpool.set_user_tid(in)) {
		ODTONE_LOG(1, "(mics) warning: no local transaction for this msg ",
		    "discarding it");
		return false;
	}

	in->source(mihfid);
	in->opcode(mih::operation::confirm);

	ODTONE_LOG(1, "(miis) forwarding Get_Information.response to ",
	    in->destination().to_string());

	_transmit(in);

	return false;
}

/**
 * MIH Push Information Request message handler.
 *
 * Currently Information_Service messages are handled by a default local
 * Information server. If this MIHF is the destination of the message,
 * forward it to the default server. Add a local transaction indicating
 * where to send the response.
 *
 * @param in input message.
 * @param out output message.
 * @return true if the response is sent immediately or false otherwise.
 */
bool information_service::push_information_request(meta_message_ptr &in,
						   meta_message_ptr &out)
{
	ODTONE_LOG(1, "(miis) received a Get_Information.request from",
	    in->source().to_string());

	if(utils::this_mihf_is_destination(in)) {
		//
		// Kick this message to Information Service.
		//
		in->destination(mih::id("miis"));
		_lpool.add(in);
		in->source(mihfid);
		_transmit(in);

		return false;
	} else {
		utils::forward_request(in, _lpool, _transmit);
		return false;
	}

	return false;
}

/**
 * MIH Push Information Indication message handler.
 *
 * Currently Information_Service messages are handled by a default local
 * server. If this MIHF is the destination of the message, check for a
 * pending transaction and forward the message.
 *
 * @param in input message.
 * @param out output message.
 * @return true if the response is sent immediately or false otherwise.
 */
bool information_service::push_information_indication(meta_message_ptr &in,
						      meta_message_ptr &out)
{
	ODTONE_LOG(1, "(miis) received Push_Information.indication from ",
	    in->source().to_string());

	if(!_lpool.set_user_tid(in)) {
		ODTONE_LOG(1, "(mics) warning: no local transaction for this msg ",
		    "discarding it");

		return false;
	}

	in->source(mihfid);

	ODTONE_LOG(1, "(miis) forwarding Push_Information.indication to ",
	    in->destination().to_string());

	_transmit(in);

	return false;
}

} /* namespace mihf */ } /* namespace odtone */
