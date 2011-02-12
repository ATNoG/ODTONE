//==============================================================================
// Brief   : Message IN
// Authors : Simao Reis <sreis@av.it.pt>
//------------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2009-2011 Universidade Aveiro
// Copyright (C) 2009-2011 Instituto de Telecomunicações - Pólo Aveiro
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//==============================================================================

///////////////////////////////////////////////////////////////////////////////
#include "message_in.hpp"
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

/**
 * Message IN constructor.
 *
 * @param tpool transaction pool module.
 * @param f process message handler.
 * @param netsap netsap module.
 */
message_in::message_in(transaction_pool &tpool, handler_t &f, net_sap &netsap)
	: _tpool(tpool),
	  process_message(f),
	  _netsap(netsap)
{
}

/**
 * The message_in checks the transaction_pool for a pending transaction for the
 * incoming message, or if a new source transaction must be created and then
 * added to the transaction pool. Then proceeds to run the newly created, or
 * found, transaction.
 *
 * @param m input message.
 */
void message_in::operator()(meta_message_ptr& in)
{
	// TODO: FIXME: check page 143 when adding support for fragment payload
	if ((in->ackrsp() && (in->opcode() == mih::operation::request || in->opcode() == mih::operation::indication))
		    ||
	   (!in->ackrsp() && in->opcode() == mih::operation::response)
	        ||
	   (in->ackrsp() && in->opcode() == mih::operation::response && in->has_service_specific_tlv()))
	{		
		// src
		src_transaction_ptr t;
		_tpool.find(in->source(), in->tid(), t);

		if (t) {
			t->in = in;
			t->msg_in_avail = true;

			if (t->start_ack_requestor)
				t->ack_requestor();

			if (t->start_ack_responder)
				t->ack_responder();

			if(!(in->ackrsp() == true && in->opcode() == mih::operation::request))
				t->run();

			if (t->transaction_status != ONGOING)
				_tpool.del(t);
		} else {
			new_dst_transaction(in);
		}
        } else {
		dst_transaction_ptr t;
		_tpool.find(in->source(), in->tid(), t);

		if (t) {
			t->in = in;
			t->msg_in_avail = true;

			if (t->start_ack_requestor)
				t->ack_requestor();

			t->run();

			if (t->start_ack_responder && t->transaction_status == ONGOING)
				t->ack_responder();

			if (t->transaction_status != ONGOING)
				_tpool.del(t);
		} else {
			new_dst_transaction(in);
		}
        }
}

/**
 * Create a new destination transaction for the incoming message.
 *
 * @param m input message.
 */
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
