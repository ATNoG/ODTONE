//==============================================================================
// Brief   : Service Management
// Authors : Simao Reis <sreis@av.it.pt>
//           Carlos Guimarães <cguimaraes@av.it.pt>
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


#ifndef ODTONE_MIHF_SERVICE_MANAGEMENT_HPP
#define ODTONE_MIHF_SERVICE_MANAGEMENT_HPP

///////////////////////////////////////////////////////////////////////////////
#include "link_response_pool.hpp"
#include "local_transaction_pool.hpp"
#include "transmit.hpp"
#include "meta_message.hpp"

#include <boost/date_time/posix_time/posix_time.hpp>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

/**
 * This class is responsible for handling the services managements messages types.
 */
class service_management {
public:
	/**
	 * Service management constructor.
	 *
	 * @param io io_service.
	 * @param lpool local transction pool.
	 * @param link_abook link book.
	 * @param t transmit module.
	 * @param lrpool link response pool.
	 * @param enable_broadcast true if response to broadcast to
	 *                          Capability_Discover.request is enable or false otherwise.
	 */
	service_management(io_service &io,
			   local_transaction_pool &lpool,
			   link_book &link_abook,
			   user_book &user_abook,
			   address_book &address_book,
			   transmit &t,
			   link_response_pool &lrpool,
			   bool enable_broadcast = false);

	/**
	 * Capability Discover Request message handler.
	 *
	 * @param in input message.
	 * @param out output message.
	 * @return true if the response is sent immediately or false otherwise.
	 */
	bool capability_discover_request(meta_message_ptr &in,
	                                 meta_message_ptr &out);

	/**
	 * Capability Discover Response message handler.
	 *
	 * @param in input message.
	 * @param out output message.
	 * @return true if the response is sent immediately or false otherwise.
	 */
	bool capability_discover_response(meta_message_ptr&in,
	                                  meta_message_ptr &out);

	/**
	 * Capability Discover Confirm message handler.
	 *
	 * @param in input message.
	 * @param out output message.
	 * @return true if the response is sent immediately or false otherwise.
	 */
	bool capability_discover_confirm(meta_message_ptr&in,
	                                 meta_message_ptr &out);

	/**
	 * Link Register Indication message handler.
	 *
	 * @param in input message.
	 * @param out output message.
	 * @return true if the response is sent immediately or false otherwise.
	 */
	bool link_register_indication(meta_message_ptr &in,
	                              meta_message_ptr &out);

	/**
	 * User Register Indication message handler.
	 *
	 * @param in input message.
	 * @param out output message.
	 * @return true if the response is sent immediately or false otherwise.
	 */
	bool user_register_indication(meta_message_ptr &in,
	                              meta_message_ptr &out);

private:
	/**
	 * Asks for local Link SAPs capabilities by sending a Capability Request message
	 * to all known Link SAPs. Also responsible for launch the thread that will
	 * respond to the requestor.
	 *
	 * @param in input message.
	 * @param out output message.
	 * @return always false, because it does not send any response directly.
	 */
	bool forward_to_link_capability_discover_request(meta_message_ptr &in,
													 meta_message_ptr &out);

	/**
	 * Handler responsible for asking capabilities to known local Link SAPs,
	 * process those capabilities and answer with a Capability Discover response
	 * message to the requestor.
	 *
	 * @param in input message.
	 */
	void link_capability_discover_response_handler(meta_message_ptr &in);

protected:
	local_transaction_pool	&_lpool;
	link_book				&_link_abook;
	user_book				&_user_abook;
	address_book			&_abook;
	transmit				&_transmit;
	link_response_pool		&_lrpool;

	boost::asio::deadline_timer _timer;

	// set to true if this MIHF responds to broadcast messages
	bool			 _enable_broadcast;
};

} /* namespace mihf */ } /* namespace odtone */

#endif
