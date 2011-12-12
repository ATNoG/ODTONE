//==============================================================================
// Brief   : Netsap
// Authors : Simao Reis <sreis@av.it.pt>
//------------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2009-2011 Universidade Aveiro
// Copyright (C) 2009-2011 Instituto de Telecomunicações - Pólo Aveiro
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//==============================================================================

///////////////////////////////////////////////////////////////////////////////
#include "net_sap.hpp"
#include "mihfid.hpp"
#include "address_book.hpp"
#include "log.hpp"
#include "utils.hpp"

#include <boost/bind.hpp>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

/**
 * Construct a netsap module.
 *
 * @param io The io_service object that Link SAP I/O Service will use to
 * dispatch handlers for any asynchronous operations performed on
 * the socket.
 * @param abook The address book module.
 */
net_sap::net_sap(io_service &io, address_book &abook)
	: _io(io),
	  _abook(abook)
{
}

/**
 * Send the message to a peer MIHF.
 *
 * @param msg The output message.
 */
void net_sap::send(meta_message_ptr &msg)
{
	try {
		address_entry src = _abook.get(mihfid_t::instance()->to_string());
		address_entry dst = _abook.get(msg->destination().to_string());

		if(dst.trans.get(mih::transport_tcp) == 1 && src.trans.get(mih::transport_tcp) == 1)
			utils::tcp_send(_io, msg, dst.ip.c_str(), dst.port);
		else
			utils::udp_send(_io, msg, dst.ip.c_str(), dst.port);

		ODTONE_LOG(1, "(net sap) sent message to: ", msg->destination().to_string(), " ", dst.ip, " ", dst.port);
	} catch(...) { // no registration was found

		// try to broadcast message
		if (msg->destination().to_string().size() == 0) {
			utils::udp_send(_io, msg, "ff02::1", 4551);
		// check msg meta data for ip and use it
		} else if (msg->ip().size() != 0) {
			utils::udp_send(_io, msg, msg->ip().c_str(), 4551);
		} else {
			ODTONE_LOG(1, "(net sap) no registration for peer mihf with id: ", msg->destination().to_string());
		}
	}
}

} /* namespace mihf */ } /* namespace odtone */

