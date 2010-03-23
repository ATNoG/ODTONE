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

#ifndef ODTONE_MIHF_TYPES_HPP
#define ODTONE_MIHF_TYPES_HPP

#include <odtone/base.hpp>
#include <odtone/mih/message.hpp>

#include <boost/function.hpp>

namespace odtone {

typedef boost::function<bool (mih::message_ptr&, mih::message_ptr&)> handler_t;
typedef boost::function<void (mih::message_ptr&)> dispatch_t;

} /* namespace odtone */

#endif
