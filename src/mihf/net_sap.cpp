//==============================================================================
// Brief   : Netsap
// Authors : Simao Reis <sreis@av.it.pt>
//------------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2009-2012 Universidade Aveiro
// Copyright (C) 2009-2012 Instituto de Telecomunicações - Pólo Aveiro
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
 * @param io The io_service object that netsap module will use to
 * dispatch handlers for any asynchronous operations performed on
 * the socket.
 * @param abook The address book module.
 * @param port Port used to send the messages.
 */
net_sap::net_sap(io_service &io, address_book &abook, uint16 port)
	: _io(io),
	  _abook(abook)
{
	_port = port;
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

		if(dst.capabilities_trans_list.is_initialized()) {
			if(dst.capabilities_trans_list->get(mih::transport_tcp) == 1
				&& src.capabilities_trans_list->get(mih::transport_tcp) == 1)
				utils::tcp_send(_io, msg, dst.ip.c_str(), dst.port, _port);
			else
				utils::udp_send(_io, msg, dst.ip.c_str(), dst.port, _port);
		} else {
			utils::udp_send(_io, msg, dst.ip.c_str(), dst.port, _port);
		}

		ODTONE_LOG(1, "(net sap) sent message to: ", msg->destination().to_string(), " : ", dst.ip, " : ", dst.port);
	} catch(...) { // no registration was found

		// check msg meta data for ip and use it
		if (msg->ip().size() != 0 && msg->ip().compare("127.0.0.1") != 0) {
			if(msg->port() != 0) {
				utils::udp_send(_io, msg, msg->ip().c_str(), msg->port(), _port);
			} else {
				utils::udp_send(_io, msg, msg->ip().c_str(), 4551, _port);
			}
			ODTONE_LOG(1, "(net sap) sent message using the meta-information");
		// try to broadcast message
		} else if(utils::is_multicast(msg)) {
			utils::udp_send(_io, msg, "ff02::1", 4551, _port);
			ODTONE_LOG(1, "(net sap) sent message in a multicast way");
		} else {
			ODTONE_LOG(1, "(net sap) no registration for peer mihf with id: ", msg->destination().to_string());
		}
	}
}

} /* namespace mihf */ } /* namespace odtone */

