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

#ifndef ODTONE_MIHF_HPP
#define ODTONE_MIHF_HPP

#include <odtone/base.hpp>
#include <odtone/debug.hpp>
#include <odtone/mih/config.hpp>
#include <odtone/mih/types.hpp>
#include <odtone/mih/tlv.hpp>

#include <odtone/mihf/mihfid.hpp>
#include <odtone/mihf/log.hpp>
#include <odtone/mihf/transaction_ack_service.hpp>
#include <odtone/mihf/net_sap.hpp>
#include <odtone/mihf/comm_handler.hpp>
#include <odtone/mihf/sqlite_handler.hpp>
#include <odtone/mihf/transaction_manager.hpp>
#include <odtone/mihf/service_access_controller.hpp>

#include <iostream>
#include <map>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>

namespace odtone { namespace mihf {

class mihf
{
public:
	mihf();
	~mihf(){}

	void init(const mih::config &cfg);
	void run();
};

} /* namespace mihf */ } /* namespace odtone */

#endif
