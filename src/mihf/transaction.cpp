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

#include <odtone/mihf/transaction.hpp>

namespace odtone { namespace mihf {

    transaction_t::transaction_t()
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

  } /* namespace mihf */
} /* namespace odtone */
