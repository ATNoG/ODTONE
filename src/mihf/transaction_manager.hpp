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

#ifndef TRANSACTION_MANAGER_HPP
#define TRANSACTION_MANAGER_HPP

///////////////////////////////////////////////////////////////////////////////

#include "dst_transaction.hpp"
#include "src_transaction.hpp"
#include "transaction_ack_service.hpp"
#include "service_access_controller.hpp"

#include <odtone/debug.hpp>
#include <odtone/mih/message.hpp>

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/noncopyable.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

    class transaction_manager
      : private boost::noncopyable
    {
    public:
      ~transaction_manager();
      static transaction_manager *instance();

      void message_in(mih::message_ptr& msg);
      void message_out(mih::message_ptr& msg);

    protected:

      transaction_manager();
      static transaction_manager *ptr_instance;

      void new_dst_transaction(mih::message_ptr& msg);
      void run_transaction(dst_transaction_ptr t);

      void new_src_transaction(mih::message_ptr& msg);
      void run_transaction(src_transaction_ptr t);

      void timer();
      template <class Set, class SetIterator>
      void run_timer(Set &set, SetIterator &it, boost::mutex &mutex);

      boost::mutex            _dst_mutex;
      dst_transaction_set     _dst_transactions;
      boost::mutex            _src_mutex;
      src_transaction_set     _src_transactions;

      boost::asio::deadline_timer _timer;
      boost::thread               _timer_thread;

	    uint16 _tid;
    };

#define tmanager transaction_manager::instance()

  } /* namespace mihf */
} /* namespace odtone */


#endif
