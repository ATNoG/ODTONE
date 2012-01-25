//==============================================================================
// Brief   : Message OUT
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
#include "message_out.hpp"

#include <odtone/random.hpp>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

/**
 * Construct a message output module.
 *
 * @param tpool The transaction pool module.
 * @param lpool The local transaction pool module.
 * @param f The message handler.
 * @param netsap The netsap module.
 */
message_out::message_out(transaction_pool &tpool, local_transaction_pool &lpool,
                         handler_t &f, net_sap &netsap)
	: _tpool(tpool),
	  _lpool(lpool),
	  process_message(f),
	  _netsap(netsap)
{
	_tid = mih::rand16();
}

/**
 * Create a new source transaction for the outgoing message.
 *
 * @param m The output message.
 */
void message_out::new_src_transaction(meta_message_ptr& m)
{
	src_transaction_ptr t(new src_transaction_t(process_message, _netsap));

	_tid++;
	if (_tid == 0)		// don't send a message with a
		_tid = 1;	// transaction id of 0

	_lpool.set_remote_tid(m->destination().to_string(), m->tid(), _tid);
	m->tid(_tid);

	t->out = m;
	t->mid = m->mid();
	t->msg_out_avail = true;

	t->run();

	if (t->transaction_status == ONGOING)
		_tpool.add(t);
}

/**
 * Checks, in the transaction pool, if the outgoing message belongs to a pending
 * transaction. If true it runs the transaction, otherwise it creates a new
 * transaction.
 *
 * @param out The output message.
 */
void message_out::operator()(meta_message_ptr& out)
{
	out->ackreq(true);	// FIXME: read from config file

	if (out->opcode() == mih::operation::response) {
		dst_transaction_ptr t;
		dst_transaction_set::iterator it;

		_tpool.find(out->destination(), out->tid(), t);

		if (t) {
			t->out = out;
			t->msg_out_avail = true;

			if (t->start_ack_requestor)
				t->ack_requestor();

			if (t->start_ack_responder)
				t->ack_responder();

			if(t->transaction_status == ONGOING)
				t->run();

			if (t->transaction_status != ONGOING && t->ack_requestor_status != ONGOING)
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

			if (t->start_ack_requestor)
				t->ack_requestor();

			if (t->start_ack_responder)
				t->ack_responder();

			if(t->transaction_status == ONGOING)
				t->run();

			if (t->transaction_status != ONGOING && t->ack_requestor_status != ONGOING)
				_tpool.del(t);
		} else {
			new_src_transaction(out);
		}
	}
}


} /* namespace mihf */ } /* namespace odtone */
