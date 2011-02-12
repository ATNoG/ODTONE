//==============================================================================
// Brief   : Information Service
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


#ifndef ODTONE_MIHF_INFORMATION_SERVICE_HPP
#define ODTONE_MIHF_INFORMATION_SERVICE_HPP

///////////////////////////////////////////////////////////////////////////////
#include "local_transaction_pool.hpp"
#include "transmit.hpp"
#include "meta_message.hpp"

#include <odtone/base.hpp>
#include <odtone/mih/types.hpp>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

/**
 * This class is responsible for handling the information messages types.
 */
class information_service
	: boost::noncopyable
{
public:
	/**
	 * Information service constructor.
	 *
	 * @param lpool local transction pool.
	 * @param t transmit module.
	 */
	information_service(local_transaction_pool &lpool, transmit &t);

	/**
	 * Get Information Request message handler.
	 *
	 * Currently Information_Service messages are handled by a default local
	 * Information server. If this MIHF is the destination of the message,
	 * forward it to the default server. Add a local transaction indicating
	 * where to send the response.
	 *
	 * @param in input message.
	 * @param out output message.
	 * @return true if the response is sent immediately or false otherwise.
	 */
	bool get_information_request(meta_message_ptr &in,
				     meta_message_ptr &out);

	/**
	 * Get Information Response message handler.
	 *
	 * Currently Information_Service messages are handled by a default local
	 * server. If this MIHF is the destination of the message, check for a
	 * pending transaction and forward the message.
	 *
	 * @param in input message.
	 * @param out output message.
	 * @return true if the response is sent immediately or false otherwise.
	 */
	bool get_information_response(meta_message_ptr &in,
				      meta_message_ptr &out);

	/**
	 * MIH Push Information Request message handler.
	 *
	 * Currently Information_Service messages are handled by a default local
	 * Information server. If this MIHF is the destination of the message,
	 * forward it to the default server. Add a local transaction indicating
	 * where to send the response.
	 *
	 * @param in input message.
	 * @param out output message.
	 * @return true if the response is sent immediately or false otherwise.
	 */
	bool push_information_indication(meta_message_ptr &in,
					 meta_message_ptr &out);

	/**
	 * MIH Push Information Indication message handler.
	 *
	 * Currently Information_Service messages are handled by a default local
	 * server. If this MIHF is the destination of the message, check for a
	 * pending transaction and forward the message.
	 *
	 * @param in input message.
	 * @param out output message.
	 * @return true if the response is sent immediately or false otherwise.
	 */
	bool push_information_request(meta_message_ptr &in,
				      meta_message_ptr &out);

protected:
	local_transaction_pool	&_lpool;
	transmit		&_transmit;
};

} /* namespace mihf */ } /* namespace odtone */

#endif
