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
#include "utils.hpp"

#include <odtone/mih/message.hpp>
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
	transaction_t(handler_t &f);

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
	mih::message_ptr in;
	bool             msg_in_avail;
	mih::message_ptr out;
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
	mih::message_ptr dup;
	mih::message_ptr ack;
	unsigned    rtxctr;

protected:
	handler_t &process_message;
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
