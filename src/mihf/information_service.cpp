//==============================================================================
// Brief   : Information Service
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
 * Construct the information service.
 *
 * @param lpool The local transaction pool module.
 * @param t The transmit module.
 * @param user_abook The user book module.
 */
information_service::information_service(local_transaction_pool &lpool,
										 transmit &t,
										 user_book &user_abook)
	: _lpool(lpool),
	  _transmit(t),
	  _user_abook(user_abook)
{
}

/**
 * Get Information Request message handler.
 *
 * @param in The input message.
 * @param out The output message.
 * @return True if the response is sent immediately or false otherwise.
 */
bool information_service::get_information_request(meta_message_ptr &in,
						  meta_message_ptr &out)
{
	ODTONE_LOG(1, "(miis) received a Get_Information.request from ",
	    in->source().to_string());

	if(utils::this_mihf_is_destination(in)) {
		//
		// Kick this message to Information Service.
		//
		boost::optional<mih::octet_string> info_user = _user_abook.information_user();
		if(!info_user.is_initialized()) {
			ODTONE_LOG(1, "There are no information MIH-users known by the MIHF");
			return false;
		}


		in->destination(mih::id(info_user.get()));
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
 * @param in The input message.
 * @param out The output message.
 * @return True if the response is sent immediately or false otherwise.
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
 * @param in The input message.
 * @param out The output message.
 * @return True if the response is sent immediately or false otherwise.
 */
bool information_service::push_information_request(meta_message_ptr &in,
						   meta_message_ptr &out)
{
	ODTONE_LOG(1, "(miis) received a Get_Information.request from ",
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
 * @param in The input message.
 * @param out The output message.
 * @return True if the response is sent immediately or false otherwise.
 */
bool information_service::push_information_indication(meta_message_ptr &in,
						      meta_message_ptr &out)
{
	ODTONE_LOG(1, "(miis) received Push_Information.indication from ",
	    in->source().to_string());

	if(!_lpool.set_user_tid(in)) {
		ODTONE_LOG(1, "(miis) warning: no local transaction for this msg ",
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
