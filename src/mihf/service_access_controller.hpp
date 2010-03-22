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

#ifndef ODTONE_MIHF_SERVICE_ACCESS_CONTROLLER_HPP
#define ODTONE_MIHF_SERVICE_ACCESS_CONTROLLER_HPP

///////////////////////////////////////////////////////////////////////////////
#include "utils.hpp"
#include <odtone/mih/message.hpp>

///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

bool sac_process_message(mih::message_ptr& in, mih::message_ptr& out);
void sac_dispatch_message(mih::message_ptr& in);
void sac_register_callback(uint mid, mihf::handler_t f);

} /* namespace mihf */ } /* namespace odtone */

#endif
