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

#include <odtone/mihf/transaction_manager.hpp>
#include <odtone/mihf/log.hpp>
#include <odtone/mihf/transmit.hpp>

namespace odtone { namespace mihf {

transaction_manager *transaction_manager::ptr_instance = NULL;

transaction_manager::transaction_manager()
	: _dst_mutex(),
	  _src_mutex(),
	  _timer(mihf::io_service, boost::posix_time::seconds(1)),
	  _timer_thread(boost::bind(&transaction_manager::timer, this))
{
}

transaction_manager *transaction_manager::instance()
{
	if (ptr_instance == NULL)
        ptr_instance = new transaction_manager();

	return ptr_instance;
}

std::ostream & operator<<(std::ostream &os, dst_transaction_ptr &t)
{
	os << "dst_transaction: " << t->peer_mihf_id.to_string()
	   << "::"
	   << (int) t->tid
	   << std::endl;

	os << "\tstate:              ";
	switch (t->state)
		{
		case DST_INIT: os << "init\n"; break;
		case DST_WAIT_RESPONSE_PRM: os << "wait response prm\n"; break;
		case DST_SEND_RESPONSE: os << "send response\n"; break;
		case DST_FAILURE: os << "failure\n"; break;
		case DST_SUCCESS: os << "success\n"; break;
		}

	os << "\ttransaction status: ";
	switch (t->transaction_status)
		{
		case ONGOING: os << "ongoing\n"; break;
		case SUCCESS: os << "success\n"; break;
		case FAILURE: os << "failure\n"; break;
		}

	return os;
}

std::ostream & operator<<(std::ostream &os, const src_transaction_ptr &t)
{
	os << "src_transaction: " << t->peer_mihf_id.to_string()
	   << "::"
	   << (int) t->tid
	   << std::endl;

	os << "\tstate:              ";
	switch (t->state)
		{
		case SRC_INIT: os << "init\n"; break;
		case SRC_WAIT_RESPONSE_MSG: os << "wait response msg\n";break;
		case SRC_WAIT_ACK: os << "wait ack\n"; break;
		case SRC_PROCESS_MSG: os << "process msg\n"; break;
		case SRC_FAILURE: os << "failure\n"; break;
		case SRC_SUCCESS: os << "success\n"; break;
		}

	os << "\ttransaction status: ";
	switch (t->transaction_status)
		{
		case ONGOING: os << "ongoing\n"; break;
		case SUCCESS: os << "success\n"; break;
		case FAILURE: os << "failure\n"; break;
		}

	return os;
}



template <class Set, class SetIterator, class TransactionPtr>
bool find(Set &set,
		  SetIterator it,
		  TransactionPtr &t,
		  boost::mutex &mutex,
		  mih::id id,
		  uint16 tid)
{
	boost::mutex::scoped_lock lock(mutex);

	for(it = set.begin(); it != set.end(); it++)
        {
			if(((*it)->peer_mihf_id == id) && (*it)->tid == tid)
				{
					t = *it;
					return true;
				}
        }

	return false;
}

void transaction_manager::new_src_transaction(mih::message_ptr& m)
{
	log(1, "(tmanager) created new source transaction with destination: ", m->destination().to_string());

	src_transaction_ptr t(new src_transaction_t);

	m->ackreq(true); // FIXME: read from config file
	m->tid(1122);  // FIXME: generate random tid and check if not in use

	t->out = m;
	t->mid = m->mid();
	t->msg_out_avail = true;

	run_transaction(t);

	if (t->transaction_status == ONGOING)
        {
			boost::mutex::scoped_lock lock(_src_mutex);
			_src_transactions.insert(t);
        }
}



void transaction_manager::message_in(mih::message_ptr& in)
{
	// TODO: FIXME: check page 143 when adding support for MIH service
	// specific TLVs or a fragment payload
	if (in->ackrsp() ||
		((in->opcode() == mih::operation::response) && !in->ackrsp()))
        {
			// src
			src_transaction_ptr t;
			src_transaction_set::iterator it;

			if (find(_src_transactions, it, t, _src_mutex, in->source(), in->tid()))
				{
					t->in = in;
					t->msg_in_avail = true;

					if (t->start_ack_requestor)
						tas->ack_requestor(t);

					run_transaction(t);
				}
			else
				{
					new_dst_transaction(in);
				}
        }
	else
        {
			dst_transaction_ptr t;
			dst_transaction_set::iterator it;

			if (find(_dst_transactions, it, t, _dst_mutex, in->destination(), in->tid()))
				{
					t->in = in;
					t->msg_in_avail = true;

					if (t->start_ack_requestor)
						tas->ack_requestor(t);

					if (t->start_ack_responder)
						tas->ack_responder(t);

					run_transaction(t);
				}
			else
				{
					new_dst_transaction(in);
				}
        }
}


void transaction_manager::new_dst_transaction(mih::message_ptr& m)
{
	log(1, "(tmanager) created new destination transaction with source: ", m->destination().to_string());

	dst_transaction_ptr t(new dst_transaction_t);
	t->in = m;
	t->mid = m->mid();
	t->msg_in_avail = true;

	run_transaction(t);

	if (t->transaction_status == ONGOING)
        {
			boost::mutex::scoped_lock lock(_dst_mutex);
			_dst_transactions.insert(t);
        }
}

void transaction_manager::message_out(mih::message_ptr& out)
{
	if (out->opcode() == mih::operation::response)
		{
			dst_transaction_ptr t;
			dst_transaction_set::iterator it;
			if (find(_dst_transactions, it, t, _dst_mutex, out->destination(), out->tid()))
				{
					t->out = out;
					t->msg_out_avail = true;

					run_transaction(t);
				}
			else
				{
					new_src_transaction(out);
				}
		}
	else if ((out->opcode() == mih::operation::indication) ||
			 (out->opcode() == mih::operation::request))
		{
			src_transaction_ptr t;
			src_transaction_set::iterator it;
			if (find(_src_transactions, it, t, _src_mutex, out->destination(), out->tid()))
				{
					t->out = out;
					t->msg_out_avail = true;

					if (t->start_ack_requestor)
						tas->ack_requestor(t);

					if (t->start_ack_responder)
						tas->ack_responder(t);

					run_transaction(t);
				}
			else
				{
					new_src_transaction(out);
				}
		}
}

void transaction_manager::run_transaction(dst_transaction_ptr t)
{
	switch (t->state)
        {
        case DST_INIT: goto _init_lbl_;
        case DST_WAIT_RESPONSE_PRM: goto _wait_response_prm_lbl_;
        case DST_SEND_RESPONSE: goto _send_response_lbl_;
        case DST_FAILURE: goto _failure_lbl_;
        case DST_SUCCESS: goto _success_lbl_;
        }

 _init_lbl_:
	{
        t->transaction_status    = ONGOING;
        t->opcode                = t->in->opcode();
        t->tid                   = t->in->tid();
        t->transaction_stop_when = 15; // FIXME
        //    t->is_multicast          = t->in->get_is_multicast();
        t->peer_mihf_id          = t->in->source();
        t->my_mihf_id            = t->in->destination();
        t->start_ack_responder   = /* ( */t->in->ackreq() /* && !t->in->is_multicast) */;
        t->msg_in_avail          = false;

		log(5, t);

        t->out.reset(new mih::message);
        t->msg_out_avail       = sac->process(t->in, t->out);

        if (t->start_ack_responder)
			tas->ack_responder(t);

        if (t->opcode == mih::operation::request)
			goto _wait_response_prm_lbl_;
        else if ((t->opcode == mih::operation::indication) || (t->opcode == mih::operation::response))
			goto _success_lbl_;
	}

 _wait_response_prm_lbl_:
	{
        t->state = DST_WAIT_RESPONSE_PRM;
		log(5, t);

        if (t->transaction_stop_when == 0)
			goto _failure_lbl_;

        if (t->msg_out_avail && (!t->start_ack_responder || t->out->ackrsp()))
			goto _send_response_begin_lbl_;

        return;
	}

 _send_response_begin_lbl_:
	{
        t->state = DST_SEND_RESPONSE;
		log(5, t);

        t->start_ack_requestor  = t->out->ackreq();
        t->ack_requestor_status = ONGOING;

        transmit(t->out);

        // ??
        // if (t->start_ack_requestor)
		// 	tas->ack_requestor(t);
	}

 _send_response_lbl_:
	{
        if (!t->start_ack_requestor || t->ack_requestor_status == SUCCESS)
			goto _success_lbl_;
        else if (t->ack_requestor_status == FAILURE)
			goto _failure_lbl_;

        return;
	}

 _failure_lbl_:
	{
        t->state              = DST_FAILURE;
        t->transaction_status = FAILURE;

		log(5, t);

        goto _exit_lbl;
	}

 _success_lbl_:
	{
        t->state              = DST_SUCCESS;
        t->transaction_status = SUCCESS;

		log(5, t);
	}

 _exit_lbl:
	_dst_transactions.erase(t);

	return;
}


void transaction_manager::run_transaction(src_transaction_ptr t)
{
	log(1, "(tmanager) running source transaction");

	switch (t->state)
        {
        case SRC_INIT: goto _init_lbl_;
        case SRC_WAIT_RESPONSE_MSG: goto _wait_response_msg_lbl_;
        case SRC_WAIT_ACK: goto _wait_ack_lbl_;
        case SRC_PROCESS_MSG: goto _process_msg_lbl_;
        case SRC_FAILURE: goto _failure_lbl_;
        case SRC_SUCCESS: goto _success_lbl_;
        }

 _init_lbl_:
	{
        t->transaction_status    = ONGOING;
        t->response_received     = false;
        t->transaction_stop_when = 15; // FIXME: read from config
        t->opcode                = t->out->opcode();
        //    t->is_multicast          = t->out->is_multicast;
        t->start_ack_requestor   = /* ( */ t->out->ackreq() /* && !t->is_multicast) */;
        t->tid                   = t->out->tid();
        t->my_mihf_id            = t->out->source();
        t->peer_mihf_id          = t->out->destination();

		log(5, t);

        transmit(t->out);

        if (t->opcode == mih::operation::response)
			{
				if (t->start_ack_requestor)
					{
						t->ack_requestor_status = ONGOING;
						goto _wait_ack_lbl_;
					}
				else
					goto _success_lbl_;
			}
        else if (t->opcode == mih::operation::indication)
			goto _success_lbl_;
        else if (t->opcode == mih::operation::request)
			goto _wait_response_msg_lbl_;

        assert(0);
	}

 _wait_ack_lbl_:
	{
        t->state = SRC_WAIT_ACK;
		log(5, t);

        if (t->ack_requestor_status == SUCCESS)
			goto _success_lbl_;
        else if (t->ack_requestor_status == FAILURE)
			goto _failure_lbl_;

        return;
	}

 _wait_response_msg_lbl_:
	{
        t->state = SRC_WAIT_RESPONSE_MSG;
		log(5, t);

        if (t->msg_in_avail)
			goto _process_msg_lbl_;
        else if (t->transaction_stop_when == 0)
			{
				if (t->response_received)
					goto _success_lbl_;
				else
					goto _failure_lbl_;
			}

        return;
	}

 _process_msg_lbl_:
	{
        t->state = SRC_PROCESS_MSG;
		log(5, t);

        t->start_ack_responder = t->in->ackreq();

        t->msg_out_avail = false;

        if (t->start_ack_responder)
			tas->ack_responder(t);

        sac->process(t->in, t->out);
        t->msg_in_avail = false;
        t->response_received = true;

        if (t->is_multicast)
			goto _wait_response_msg_lbl_;
        else
			goto _success_lbl_;
	}

 _failure_lbl_:
	{
        t->transaction_status = FAILURE;
        t->state = SRC_FAILURE;

        log(5, t);
        goto _exit_lbl;
	}

 _success_lbl_:
	{
        t->transaction_status = SUCCESS;
        t->state = SRC_SUCCESS;

        log(5, t);
        _src_transactions.erase(t);
	}

 _exit_lbl:
	_src_transactions.erase(t);

	return;
}


template <class Set, class SetIterator>
void transaction_manager::run_timer(Set &set,
									SetIterator &it,
									boost::mutex &mutex)
{
	if (set.size() > 0)
        {
			boost::mutex::scoped_lock lock(mutex);
			Set delete_these;

			for(it = set.begin(); it != set.end(); it++)
				{
					if (--((*it)->transaction_stop_when) == 0)
						{
							run_transaction(*it);

							if ((*it)->transaction_status == ONGOING)
								delete_these.insert(*it);
						}

					if ((*it)->start_ack_requestor)
						{
							if (--((*it)->retransmission_when) == 0)
								{
									tas->ack_requestor(*it);
									run_transaction(*it);
								}
						}

					if ((*it)->transaction_status != ONGOING)
						delete_these.insert(*it);
				}

			for (it = delete_these.begin(); it != delete_these.end(); it++)
				set.erase(*it);
        }
}

void transaction_manager::timer()
{
	_timer.expires_at(_timer.expires_at() + boost::posix_time::seconds(1));
	_timer.async_wait(boost::bind(&transaction_manager::timer, this));

	src_transaction_set::iterator src_it;
	run_timer(_src_transactions, src_it, _src_mutex);

	dst_transaction_set::iterator dst_it;
	run_timer(_dst_transactions, dst_it, _dst_mutex);
}

} /* namespace mihf */ } /* namespace odtone */
