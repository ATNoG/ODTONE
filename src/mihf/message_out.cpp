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
#include "message_out.hpp"

#include <odtone/random.hpp>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

message_out::message_out(transaction_pool &tpool)
	: _tpool(tpool)
{
	_tid = mih::rand16();
}

void message_out::new_src_transaction(mih::message_ptr& m)
{
	src_transaction_ptr t(new src_transaction_t);

	m->ackreq(true); // FIXME: read from config file

	_tid++;
	if (_tid == 0)		// don't send a message with a
		_tid = 1;	// transaction id of 0

	m->tid(_tid);

	t->out = m;
	t->mid = m->mid();
	t->msg_out_avail = true;

	t->run();

	if (t->transaction_status == ONGOING)
		_tpool.add(t);
}


void message_out::operator()(mih::message_ptr& out)
{
	if (out->opcode() == mih::operation::response) {
		dst_transaction_ptr t;
		dst_transaction_set::iterator it;

		_tpool.find(out->destination(), out->tid(), t);

		if (t) {
			t->out = out;
			t->msg_out_avail = true;

			t->run();

			if (t->transaction_status != ONGOING)
				_tpool.del(t);
		} else {
			new_src_transaction(out);
		}
	} else if ((out->opcode() == mih::operation::indication) || (out->opcode() == mih::operation::request)) {

		src_transaction_ptr t;
		_tpool.find(out->destination(), out->tid(), t);

		if (t) {
			t->out = out;
			t->msg_out_avail = true;

			// if (t->start_ack_requestor)
			// 	tas->ack_requestor(t);

			// if (t->start_ack_responder)
			// 	tas->ack_responder(t);

			t->run();

			if (t->transaction_status != ONGOING)
				_tpool.del(t);
		} else {
			new_src_transaction(out);
		}
	}
}


} /* namespace mihf */ } /* namespace odtone */
