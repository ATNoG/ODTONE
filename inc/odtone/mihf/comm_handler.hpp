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

#ifndef ODTONE_MIH_COMM_HANDLER_HPP
#define ODTONE_MIH_COMM_HANDLER_HPP

#include "generic_server.hpp"

namespace odtone { namespace mihf {

class comm_handler
	: public generic_server
{
public:
	static comm_handler* instance();
	~comm_handler();

private:
	comm_handler(boost::asio::io_service& io);
	comm_handler();

protected:
	void process_message(mih::message_ptr& msg);
	static comm_handler *ptr_instance;
};

#define comhand comm_handler::instance()

  } /* namespace mihf */
} /* namespace odtone */

#endif
