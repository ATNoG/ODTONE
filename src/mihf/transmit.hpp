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

#ifndef ODTONE_MIHF_TRANSMIT_HPP
#define ODTONE_MIHF_TRANSMIT_HPP

///////////////////////////////////////////////////////////////////////////////
#include "address_book.hpp"
#include "message_out.hpp"
#include "meta_message.hpp"

#include <odtone/base.hpp>
#include <odtone/debug.hpp>

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
///////////////////////////////////////////////////////////////////////////////

using namespace boost::asio;

namespace odtone { namespace mihf {

class transmit
	: private boost::noncopyable
{
public:
	transmit(io_service &io, address_book &abook, message_out &msg_out);

	void operator()(meta_message_ptr& msg);

private:
	io_service &_io;
	address_book &_abook;
	message_out &_msg_out;

};

} /* namespace mihf */ } /* namespace odtone */

#endif
