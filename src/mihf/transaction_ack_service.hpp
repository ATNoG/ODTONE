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

#ifndef TRANSACTION_ACK_SERVICE_HPP
#define TRANSACTION_ACK_SERVICE_HPP

///////////////////////////////////////////////////////////////////////////////
#include "transmit.hpp"
#include "transaction.hpp"

#include <boost/noncopyable.hpp>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

class transaction_ack_service
	: private boost::noncopyable
{

public:
	transaction_ack_service();

	template <class TransactionPtr>
	void ack_responder(TransactionPtr t)
		{
			switch(t->ack_rsp_state)
			{
			case ACK_RSP_INIT:
				goto _rsp_init_lbl_;
			case ACK_RSP_RETURN_ACK:
				goto _rsp_return_ack_lbl_;
			case ACK_RSP_PIGGYBACKING:
				goto _rsp_piggybacking_lbl_;
			case ACK_RSP_RETURN_DUPLICATE:
				goto _rsp_return_duplicate_lbl_;
			}

		  _rsp_init_lbl_:
			{
				// t->ack = (new mih::message);

				t->ack->ackrsp(true);
				t->ack->opcode((mih::operation::type)t->opcode);
				t->ack->tid(t->tid);
				t->ack->source(t->my_mihf_id);
				t->ack->destination(t->peer_mihf_id);

				if (t->msg_out_avail)
					goto _rsp_piggybacking_lbl_;
				else
					goto _rsp_return_ack_lbl_;

				return;
			}

		  _rsp_return_ack_lbl_:
			{
				t->ack_rsp_state = ACK_RSP_RETURN_ACK;
				t->ack->mid(t->mid);

				// transmit(t->ack);

				if (t->msg_in_avail)
					t->msg_in_avail = false;
				else if (t->msg_out_avail)
					goto _rsp_piggybacking_lbl_;

				return;
			}

		  _rsp_piggybacking_lbl_:
			{
				t->ack_rsp_state = ACK_RSP_PIGGYBACKING;

				t->out->ackrsp(true);
				t->dup = t->out;

				if (t->msg_in_avail)
					goto _rsp_return_duplicate_lbl_;

				return;
			}

		  _rsp_return_duplicate_lbl_:
			{
				t->ack_rsp_state = ACK_RSP_RETURN_DUPLICATE;
				if (t->msg_in_avail) {
					// transmit(t->dup);
					t->msg_in_avail = false;
				}
			}
		}

	template <class TransactionPtr>
	void ack_requestor(TransactionPtr t)
		{
			switch (t->ack_req_state)
			{
			case ACK_REQ_INIT: goto _req_init_lbl_;
			case ACK_REQ_WAIT_ACK: goto _req_wait_ack_lbl_;
			case ACK_REQ_RETRANSMIT: goto _req_retransmit_lbl_;
			case ACK_REQ_SUCCESS: goto _req_success_lbl_;
			case ACK_REQ_FAILURE: goto _req_failure_lbl_;
			}

		  _req_init_lbl_:
			{
				t->rtxctr = 0;
				// unconditional transition to wait_ack
			}

		  _req_wait_ack_begin_lbl_:
			{
				t->ack_req_state = ACK_REQ_WAIT_ACK;
				t->retransmission_when = 5; // FIXME
			}

		  _req_wait_ack_lbl_:
			{
				if (t->retransmission_when == 0) {
					if  (t->rtxctr < 2)
						goto _req_retransmit_lbl_;
					else
						goto _req_failure_lbl_;
				}

				if ((t->msg_in_avail && t->in->ackrsp()))
					goto _req_success_lbl_;

				return;
			}

		  _req_retransmit_lbl_:
			{
				t->ack_req_state = ACK_REQ_RETRANSMIT;

				// transmit(t->out);
				t->rtxctr++;

				goto _req_wait_ack_begin_lbl_;
			}

		  _req_failure_lbl_:
			{
				t->ack_requestor_status = FAILURE;
				return;
			}

		  _req_success_lbl_:
			{
				t->ack_requestor_status = SUCCESS;
				return;
			}
		}
};

} /* namespace mihf */ } /* namespace odtone */


#endif
