//==============================================================================
// Brief   : Discover Service
// Authors : Carlos Guimarães <cguimaraes@av.it.pt>
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

#ifndef ODTONE_MIHF_DISCOVER_SERVICE_HPP
#define ODTONE_MIHF_DISCOVER_SERVICE_HPP

///////////////////////////////////////////////////////////////////////////////
#include "meta_message.hpp"
#include "local_transaction_pool.hpp"
#include "transmit.hpp"
#include "address_book.hpp"
#include "user_book.hpp"

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

class discover_service {
public:
	discover_service(io_service &io,
					 local_transaction_pool &lpool,
					 address_book &abook,
					 user_book &user_abook,
					 transmit &t);

	void request(meta_message_ptr& in, meta_message_ptr& out);

	void response(meta_message_ptr& in, meta_message_ptr& out);

protected:
	void request_pos_capabilities(meta_message_ptr& out, mih::mos_info &pos);

private:
	io_service						&_io;
	local_transaction_pool			&_lpool;
	address_book					&_abook;
	user_book						&_user_abook;
	transmit						&_transmit;
};

} /* namespace mihf */ } /* namespace odtone */

#endif
