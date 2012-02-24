//==============================================================================
// Brief   : Service Management
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


#ifndef ODTONE_MIHF_SERVICE_MANAGEMENT_HPP
#define ODTONE_MIHF_SERVICE_MANAGEMENT_HPP

///////////////////////////////////////////////////////////////////////////////
#include "link_response_pool.hpp"
#include "local_transaction_pool.hpp"
#include "transmit.hpp"
#include "meta_message.hpp"
#include "discover_service.hpp"

#include <boost/date_time/posix_time/posix_time.hpp>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

/**
 * This class is responsible for handling the messages associated with
 * the service management.
 */
class service_management {
public:
	/**
	 * Construct the service management.
	 *
	 * @param io The io_service object that service management module will
	 * use to dispatch handlers for any asynchronous operations performed on
	 * the socket.
	 * @param lpool The local transaction pool module.
	 * @param link_abook The link book module.
	 * @param user_abook The user book module.
	 * @param address_abook The address book module.
	 * @param t The transmit module.
	 * @param lrpool The link response pool module.
	 * @param dscv_order Ordered list of entities that will manage the
	 * discovery of new PoS.
	 * @param enable_unsolicited Allows unsolicited discovery.
	 */
	service_management(io_service &io,
			   local_transaction_pool &lpool,
			   link_book &link_abook,
			   user_book &user_abook,
			   address_book &address_book,
			   transmit &t,
			   link_response_pool &lrpool,
			   std::vector<mih::octet_string> &dscv_order,
			   bool enable_unsolicited);

	/**
	 * Capability Discover Request message handler.
	 *
	 * @param in The input message.
	 * @param out The output message.
	 * @return True if the response is sent immediately or false otherwise.
	 */
	bool capability_discover_request(meta_message_ptr &in,
	                                 meta_message_ptr &out);

	/**
	 * Capability Discover Response message handler.
	 *
	 * @param in The input message.
	 * @param out The output message.
	 * @return True if the response is sent immediately or false otherwise.
	 */
	bool capability_discover_response(meta_message_ptr&in,
	                                  meta_message_ptr &out);

	/**
	 * Capability Discover Confirm message handler.
	 *
	 * @param in The input message.
	 * @param out The output message.
	 * @return True if the response is sent immediately or false otherwise.
	 */
	bool capability_discover_confirm(meta_message_ptr&in,
	                                 meta_message_ptr &out);

	/**
	 * Link Register Indication message handler.
	 *
	 * @param in The input message.
	 * @param out The output message.
	 * @return True if the response is sent immediately or false otherwise.
	 */
	bool link_register_indication(meta_message_ptr &in,
	                              meta_message_ptr &out);

	/**
	 * User Register Indication message handler.
	 *
	 * @param in The input message.
	 * @param out The output message.
	 * @return True if the response is sent immediately or false otherwise.
	 */
	bool user_register_indication(meta_message_ptr &in,
	                              meta_message_ptr &out);

protected:
	/**
	 * Asks for the capabilities of all local Link SAPs.
	 *
	 * @param in The input message.
	 * @param out The output message.
	 * @return Always false, because it does not send any response directly.
	 */
	bool link_capability_discover_request(meta_message_ptr &in,
										  meta_message_ptr &out);

	/**
	 * Piggyback local MIHF Capabilities in request message.
	 *
	 * @param in input message.
	 * @param out output message.
	 */
	void piggyback_capabilities(meta_message_ptr& in, meta_message_ptr& out);

	/**
	 * Parse all capabilities from MIH Capability Discover message and stores
	 * them.
	 *
	 * @param in input message.
	 * @param out output message.
	 */
	void get_capabilities(meta_message_ptr& in, meta_message_ptr& out);

	/**
	 * Set response to MIH Capability Discover message.
	 *
	 * @param in input message.
	 * @param out output message.
	 */
	void set_capability_discover_response(meta_message_ptr& in,
										  meta_message_ptr& out);

	/**
	 * Send Capability Discover Indication message to all MIH Users.
	 *
	 * @param in input message.
	 * @param out output message.
	 */
	void send_indication(meta_message_ptr& in, meta_message_ptr& out);

private:
	local_transaction_pool	&_lpool;		/**< Local transaction pool module.	*/
	link_book				&_link_abook;	/**< Link book module.				*/
	user_book				&_user_abook;	/**< User book module.				*/
	address_book			&_abook;		/**< Address book module.			*/
	transmit				&_transmit;		/**< Transmit book module.			*/
	link_response_pool		&_lrpool;		/**< Link response pool module.		*/

	bool				_enable_unsolicited;/**< Allows unsolicited discovery.	*/
	discover_service	_discover;			/**< Discovery service module.		*/
	std::vector<mih::octet_string> _dscv_order; /**< Ordered list of discovery entities.*/
};

} /* namespace mihf */ } /* namespace odtone */

#endif
