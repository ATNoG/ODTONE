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
#include "comm_handler.hpp"

#include "service_access_controller.hpp"
///////////////////////////////////////////////////////////////////////////////

extern boost::asio::io_service io_service;

namespace odtone { namespace mihf {


comm_handler *comm_handler::ptr_instance = NULL;

comm_handler *comm_handler::instance()
{
	if (ptr_instance == NULL)
        ptr_instance = new comm_handler(io_service);

	return ptr_instance;
}

comm_handler::comm_handler(boost::asio::io_service& io)
	: generic_server(io)
{
}

comm_handler::~comm_handler()
{
	if(ptr_instance)
        delete ptr_instance;
}

void comm_handler::process_message(mih::message_ptr& msg)
{
	sac->dispatch(msg);
}

} /* namespace mihf */ } /* namespace odtone */
