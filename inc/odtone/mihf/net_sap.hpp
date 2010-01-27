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

#ifndef NET_SAP_HPP
#define NET_SAP_HPP

#include "generic_server.hpp"

namespace odtone { namespace mihf {

class net_sap
	: public generic_server
{
public:
	static net_sap* instance();
	net_sap(boost::asio::io_service& io);
	~net_sap();

protected:
	net_sap();

private:
	void process_message(mih::message_ptr& msg);

	static net_sap *ptr_instance;
};

#define netsap net_sap::instance()

  } /* namespace mihf */
} /* namespace odtone */

#endif
