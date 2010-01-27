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

#ifndef ODTONE_MIHF_UTILS_HPP
#define ODTONE_MIHF_UTILS_HPP

#include <odtone/base.hpp>
#include <odtone/mih/message.hpp>
#include <odtone/mih/types.hpp>


namespace odtone { namespace mihf { namespace utils {

bool forward_to_user(uint16 mid, mih::message& in, mih::message& out);

bool is_local_request(mih::message_ptr &in);

// A user sent a MIH request message, set the MIH source field and
// forward the message to the required destination.
bool forward_request(mih::message_ptr &in);


void register_interface(mih::link_tuple_id &li);

} } }

#endif
