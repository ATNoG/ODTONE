//==============================================================================
// Brief   : Transaction
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
#include "transaction.hpp"
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

/**
 * Constructor a remote transaction.
 *
 * @param f The transaction handler.
 * @param netsap The netsap module.
 */
transaction_t::transaction_t(handler_t &f, net_sap &netsap)
	: ack(new meta_message()),
	  process_message(f),
	  _netsap(netsap)
{
	opcode                = 0;
	mid                   = 0;
	ack_requestor_status  = ONGOING;
	transaction_stop_when = 0;
	retransmission_when   = 0;
	tid                   = 0;
	// my_mihf_id         = 0;
	// peer_mihf_id       = 0;
	transaction_status    = ONGOING;
	start_ack_requestor   = false;
	start_ack_responder   = false;
	is_multicast          = false;
	response_received     = false;
	ack_req_state         = ACK_REQ_INIT;
	ack_rsp_state         = ACK_RSP_INIT;
	msg_in_avail			= false;
	msg_out_avail			= false;
}

} /* namespace mihf */ } /* namespace odtone */
