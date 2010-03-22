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
#include "src_transaction.hpp"
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

src_transaction_t::src_transaction_t(handler_t &f)
	: transaction_t(f)
{
	state = SRC_INIT;
}

void src_transaction_t::run()
{
	switch (state)
        {
        case SRC_INIT: goto _init_lbl_;
        case SRC_WAIT_RESPONSE_MSG: goto _wait_response_msg_lbl_;
        case SRC_WAIT_ACK: goto _wait_ack_lbl_;
        case SRC_PROCESS_MSG: goto _process_msg_lbl_;
        case SRC_FAILURE: goto _failure_lbl_;
        case SRC_SUCCESS: goto _success_lbl_;
        }

  _init_lbl_:
	{
		transaction_status    = ONGOING;
		response_received     = false;
		transaction_stop_when = 15; // FIXME: read from config
		opcode                = out->opcode();
		//    is_multicast          = out->is_multicast;
		start_ack_requestor   = out->ackreq() /* && !is_multicast) */;
		tid                   = out->tid();
		my_mihf_id            = out->source();
		peer_mihf_id          = out->destination();

		// transmit.send(out);

		if (opcode == mih::operation::response) {
			if (start_ack_requestor) {
				ack_requestor_status = ONGOING;
				goto _wait_ack_lbl_;
			}
			else
				goto _success_lbl_;
		}
		else if (opcode == mih::operation::indication)
			goto _success_lbl_;
		else if (opcode == mih::operation::request)
			goto _wait_response_msg_lbl_;

		assert(0); // failsafe
	}

  _wait_ack_lbl_:
	{
		state = SRC_WAIT_ACK;

		if (ack_requestor_status == SUCCESS)
			goto _success_lbl_;
		else if (ack_requestor_status == FAILURE)
			goto _failure_lbl_;

		return;
	}

  _wait_response_msg_lbl_:
	{
		state = SRC_WAIT_RESPONSE_MSG;

		if (msg_in_avail)
			goto _process_msg_lbl_;
		else if (transaction_stop_when == 0) {
			if (response_received)
				goto _success_lbl_;
			else
				goto _failure_lbl_;
		}

		return;
	}

  _process_msg_lbl_:
	{
		state = SRC_PROCESS_MSG;

		start_ack_responder = in->ackreq();

		msg_out_avail = false;

		// if (start_ack_responder)
		// 	tas->ack_responder(t);

		process_message(in, out);
		msg_in_avail = false;
		response_received = true;

		if (is_multicast)
			goto _wait_response_msg_lbl_;
		else
			goto _success_lbl_;
	}

  _failure_lbl_:
	{
		transaction_status = FAILURE;
		state = SRC_FAILURE;
		return;
	}

  _success_lbl_:
	{
		transaction_status = SUCCESS;
		state = SRC_SUCCESS;
	}

	return;
}


} /* namespace mihf */ } /* namespace odtone */
