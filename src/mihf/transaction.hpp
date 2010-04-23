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

#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

///////////////////////////////////////////////////////////////////////////////
#include "types.hpp"
#include "net_sap.hpp"
#include "meta_message.hpp"

#include <odtone/mih/types/identification.hpp>

#include <set>
#include <boost/shared_ptr.hpp>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

// forward declare mihf class, and the global variable to access other
// services, such as the trasaction_manager and net_sap
// class mihf;
// extern mihf mihf;

enum status_t
	{
        ONGOING,
        SUCCESS,
        FAILURE
	};

enum ack_responder_state_t
	{
        ACK_RSP_INIT,
        ACK_RSP_RETURN_ACK,
        ACK_RSP_PIGGYBACKING,
        ACK_RSP_RETURN_DUPLICATE
	};

enum ack_requestor_state_t
	{
        ACK_REQ_INIT,
        ACK_REQ_WAIT_ACK,
        ACK_REQ_RETRANSMIT,
        ACK_REQ_SUCCESS,
        ACK_REQ_FAILURE
	};

class transaction_t
{
public:
	transaction_t(handler_t &f, net_sap &netsap);

	// inter-state machine variables
	uint16   opcode;
	uint16   mid;
	status_t ack_requestor_status;
	unsigned transaction_stop_when;
	unsigned retransmission_when;

	// exported state machine variables
	uint16             tid;
	mih::id             my_mihf_id;
	mih::id             peer_mihf_id;
	meta_message_ptr in;
	bool             msg_in_avail;
	meta_message_ptr out;
	bool             msg_out_avail;
	status_t         transaction_status;
	bool             start_ack_requestor;
	bool             start_ack_responder;

	// intra-state machine variables
	bool        is_multicast;
	bool        response_received;

	// ack related variables
	ack_requestor_state_t ack_req_state;
	ack_responder_state_t ack_rsp_state;

	// intra-state
	meta_message_ptr dup;
	meta_message_ptr ack;
	unsigned    rtxctr;

	void ack_responder()
		{
			switch(ack_rsp_state)
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
				// ack = (new mih::message);

				ack->ackrsp(true);
				ack->opcode((mih::operation::type)opcode);
				ack->tid(tid);
				ack->source(my_mihf_id);
				ack->destination(peer_mihf_id);

				if (msg_out_avail)
					goto _rsp_piggybacking_lbl_;
				else
					goto _rsp_return_ack_lbl_;

				return;
			}

		  _rsp_return_ack_lbl_:
			{
				ack_rsp_state = ACK_RSP_RETURN_ACK;
				ack->mid(mid);

				_netsap.send(ack);

				if (msg_in_avail)
					msg_in_avail = false;
				else if (msg_out_avail)
					goto _rsp_piggybacking_lbl_;

				return;
			}

		  _rsp_piggybacking_lbl_:
			{
				ack_rsp_state = ACK_RSP_PIGGYBACKING;

				out->ackrsp(true);
				dup = out;

				if (msg_in_avail)
					goto _rsp_return_duplicate_lbl_;

				return;
			}

		  _rsp_return_duplicate_lbl_:
			{
				ack_rsp_state = ACK_RSP_RETURN_DUPLICATE;
				if (msg_in_avail) {
					_netsap.send(dup);
					msg_in_avail = false;
				}
			}
		}

	void ack_requestor()
		{
			switch (ack_req_state)
			{
			case ACK_REQ_INIT: goto _req_init_lbl_;
			case ACK_REQ_WAIT_ACK: goto _req_wait_ack_lbl_;
			case ACK_REQ_RETRANSMIT: goto _req_retransmit_lbl_;
			case ACK_REQ_SUCCESS: goto _req_success_lbl_;
			case ACK_REQ_FAILURE: goto _req_failure_lbl_;
			}

		  _req_init_lbl_:
			{
				rtxctr = 0;
				// unconditional transition to wait_ack
			}

		  _req_wait_ack_begin_lbl_:
			{
				ack_req_state = ACK_REQ_WAIT_ACK;
				retransmission_when = 5; // FIXME
			}

		  _req_wait_ack_lbl_:
			{
				if (retransmission_when == 0) {
					if  (rtxctr < 2)
						goto _req_retransmit_lbl_;
					else
						goto _req_failure_lbl_;
				}

				if ((msg_in_avail && in->ackrsp()))
					goto _req_success_lbl_;

				return;
			}

		  _req_retransmit_lbl_:
			{
				ack_req_state = ACK_REQ_RETRANSMIT;

				_netsap.send(out);
				rtxctr++;

				goto _req_wait_ack_begin_lbl_;
			}

		  _req_failure_lbl_:
			{
				ack_requestor_status = FAILURE;
				return;
			}

		  _req_success_lbl_:
			{
				ack_requestor_status = SUCCESS;
				return;
			}
		}

protected:
	handler_t &process_message;
	net_sap &_netsap;
};

// Compare method for inserting transactions in a set
template <class TransactionPtr>
class transaction_compare
{
public:
	// Check if the peer mihf ids and transaction ids are different
	bool operator()(const TransactionPtr &a, const TransactionPtr &b)
	{
		if (a->peer_mihf_id == b->peer_mihf_id)
			return (a->tid != b->tid);

		return true;
	}
};

} /* namespace mihf */ } /* namespace odtone */


#endif
