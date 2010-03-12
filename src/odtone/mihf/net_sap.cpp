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

#include <odtone/mihf/net_sap.hpp>
#include <odtone/mihf/transaction_manager.hpp>
#include <odtone/mihf/mihfid.hpp>

extern boost::asio::io_service io_service;

namespace odtone { namespace mihf {


net_sap *net_sap::ptr_instance = NULL;

net_sap *net_sap::instance()
{
      if (ptr_instance == NULL)
        ptr_instance = new net_sap(io_service);

	return ptr_instance;
}

net_sap::net_sap(boost::asio::io_service& io)
	: generic_server(io)
{
}

net_sap::~net_sap()
{
	if(ptr_instance)
        delete ptr_instance;
}

void net_sap::process_message(mih::message_ptr& msg)
{
	tmanager->message_in(msg);
}

} /* namespace mihf */ } /* namespace odtone */
