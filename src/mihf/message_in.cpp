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
#include "message_in.hpp"
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

message_in::message_in(transaction_pool &tpool, handler_t &f, net_sap &netsap)
	: _tpool(tpool),
	  process_message(f),
	  _netsap(netsap)
{
}


void message_in::operator()(meta_message_ptr& in)
{
	// TODO: FIXME: check page 143 when adding support for MIH service
	// specific TLVs or a fragment payload
	if (in->ackrsp() ||
	    ((in->opcode() == mih::operation::response) && !in->ackrsp())) {
		// src
		src_transaction_ptr t;
		_tpool.find(in->source(), in->tid(), t);

		if (t) {
			t->in = in;
			t->msg_in_avail = true;

			// if (t->start_ack_requestor)
			// 	tas->ack_requestor(t);

			t->run();

			if (t->transaction_status != ONGOING)
				_tpool.del(t);
		} else {
			new_dst_transaction(in);
		}
        } else {
		dst_transaction_ptr t;
		_tpool.find(in->destination(), in->tid(), t);

		if (t) {
			t->in = in;
			t->msg_in_avail = true;

			// if (t->start_ack_requestor)
			// 	tas->ack_requestor(t);

			// if (t->start_ack_responder)
			// 	tas->ack_responder(t);

			t->run();

			if (t->transaction_status != ONGOING)
				_tpool.del(t);
		} else {
			new_dst_transaction(in);
		}
        }
}


void message_in::new_dst_transaction(meta_message_ptr& m)
{
	dst_transaction_ptr t(new dst_transaction_t(process_message, _netsap));
	t->in = m;
	t->mid = m->mid();
	t->msg_in_avail = true;

	t->run();

	if (t->transaction_status == ONGOING)
		_tpool.add(t);
}


} /* namespace mihf */ } /* namespace odtone */
