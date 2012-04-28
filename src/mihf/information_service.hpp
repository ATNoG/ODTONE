//==============================================================================
// Brief   : Information Service
// Authors : Simao Reis <sreis@av.it.pt>
//           Carlos Guimarães <cguimaraes@av.it.pt>
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


#ifndef ODTONE_MIHF_INFORMATION_SERVICE_HPP
#define ODTONE_MIHF_INFORMATION_SERVICE_HPP

///////////////////////////////////////////////////////////////////////////////
#include "local_transaction_pool.hpp"
#include "transmit.hpp"
#include "meta_message.hpp"
#include "user_book.hpp"

#include <odtone/base.hpp>
#include <odtone/mih/types.hpp>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

/**
 * This class is responsible for handling the messages associated with
 * the information service.
 */
class information_service
	: boost::noncopyable
{
public:
	/**
	 * Construct the information service.
	 *
	 * @param lpool The local transaction pool module.
	 * @param t The transmit module.
	 * @param user_abook The user book module.
	 */
	information_service(local_transaction_pool &lpool,
						transmit &t,
						user_book &user_abook);

	/**
	 * Get Information Request message handler.
	 *
	 * @param in The input message.
	 * @param out The output message.
	 * @return True if the response is sent immediately or false otherwise.
	 */
	bool get_information_request(meta_message_ptr &in,
				     meta_message_ptr &out);

	/**
	 * Get Information Response message handler.
	 *
	 * @param in The input message.
	 * @param out The output message.
	 * @return True if the response is sent immediately or false otherwise.
	 */
	bool get_information_response(meta_message_ptr &in,
				      meta_message_ptr &out);

	/**
	 * MIH Push Information Request message handler.
	 *
	 * @param in The input message.
	 * @param out The output message.
	 * @return True if the response is sent immediately or false otherwise.
	 */
	bool push_information_indication(meta_message_ptr &in,
					 meta_message_ptr &out);

	/**
	 * MIH Push Information Indication message handler.
	 *
	 * @param in The input message.
	 * @param out The output message.
	 * @return True if the response is sent immediately or false otherwise.
	 */
	bool push_information_request(meta_message_ptr &in,
				      meta_message_ptr &out);

protected:
	local_transaction_pool	&_lpool;		/**< Local transaction pool module.	*/
	transmit				&_transmit;		/**< Transmit module.				*/
	user_book				&_user_abook;	/**< User book module.				*/
};

} /* namespace mihf */ } /* namespace odtone */

#endif
