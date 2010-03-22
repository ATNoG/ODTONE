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
#include "dst_transaction.hpp"
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {


dst_transaction_t::dst_transaction_t(handler_t &f)
	: transaction_t(f)
{
	state = DST_INIT;
}

void dst_transaction_t::run()
{
	switch (state)
        {
        case DST_INIT: goto _init_lbl_;
        case DST_WAIT_RESPONSE_PRM: goto _wait_response_prm_lbl_;
        case DST_SEND_RESPONSE: goto _send_response_lbl_;
        case DST_FAILURE: goto _failure_lbl_;
        case DST_SUCCESS: goto _success_lbl_;
        }

  _init_lbl_:
	{
		transaction_status    = ONGOING;
		opcode                = in->opcode();
		tid                   = in->tid();
		transaction_stop_when = 15; // FIXME
		//    is_multicast          = in->get_is_multicast();
		peer_mihf_id          = in->source();
		my_mihf_id            = in->destination();
		start_ack_responder   = in->ackreq() /*&& !in->is_multicast)*/;
		msg_in_avail          = false;

		out.reset(new mih::message);
		msg_out_avail = process_message(in, out);

		// if (start_ack_responder)
		// 	tas->ack_responder(t);

		if (opcode == mih::operation::request)
			goto _wait_response_prm_lbl_;
		else if ((opcode == mih::operation::indication)
			 || (opcode == mih::operation::response))
			goto _success_lbl_;
	}

  _wait_response_prm_lbl_:
	{
		state = DST_WAIT_RESPONSE_PRM;

		if (transaction_stop_when == 0)
			goto _failure_lbl_;

		if (msg_out_avail && (!start_ack_responder || out->ackrsp()))
			goto _send_response_begin_lbl_;

		return;
	}

  _send_response_begin_lbl_:
	{
		state = DST_SEND_RESPONSE;

		start_ack_requestor  = out->ackreq();
		ack_requestor_status = ONGOING;

		// transmit.send(out);

		// ?? probably not
		// if (start_ack_requestor)
		// 	tas->ack_requestor(t);
	}

  _send_response_lbl_:
	{
		if (!start_ack_requestor || ack_requestor_status == SUCCESS)
			goto _success_lbl_;
		else if (ack_requestor_status == FAILURE)
			goto _failure_lbl_;

		return;
	}

  _failure_lbl_:
	{
		state              = DST_FAILURE;
		transaction_status = FAILURE;

		return;
	}

  _success_lbl_:
	{
		state              = DST_SUCCESS;
		transaction_status = SUCCESS;
	}

	return;
}


} /* namespace mihf */ } /* namespace odtone */
