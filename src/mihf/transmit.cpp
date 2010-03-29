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
#include "transmit.hpp"
#include "utils.hpp"
#include "log.hpp"
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

transmit::transmit(io_service &io, address_book &abook, message_out &msg_out)
	: _io(io),
	  _abook(abook),
	  _msg_out(msg_out)
{
}

void transmit::operator()(meta_message_ptr& msg)
{
	// TODO: remove try catch
	try{
		address_entry a = _abook.get(msg->destination().to_string());
		log(1, "(transmit) sending local message to: ",
		    msg->destination().to_string(), " ", a.ip, " ", a.port);
		utils::udp_send(_io, msg, a.ip.c_str(), a.port);
	} catch (...) {
		log(1, "(transmit) forwarding to message_out");
		_msg_out(msg);
	}
}

} /* namespace mihf */ } /* namespace odtone */
