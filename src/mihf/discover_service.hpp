//==============================================================================
// Brief   : Discover Service
// Authors : Carlos Guimarães <cguimaraes@av.it.pt>
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

#ifndef ODTONE_MIHF_DISCOVER_SERVICE_HPP
#define ODTONE_MIHF_DISCOVER_SERVICE_HPP

///////////////////////////////////////////////////////////////////////////////
#include "meta_message.hpp"
#include "local_transaction_pool.hpp"
#include "transmit.hpp"
#include "address_book.hpp"
#include "user_book.hpp"

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

class discover_service {
public:
	/**
	 * Construct the discovery service.
	 *
	 * @param io The io_service object that discovery module module will
	 * use to dispatch handlers for any asynchronous operations performed on
	 * the socket.
	 * @param lpool The local transaction pool module.
	 * @param address_abook The address book module.
	 * @param user_abook The user book module.
	 * @param t The transmit module.
	 * @param dscv_order Ordered list of entities that will manage the
	 * discovery of new PoS.
	 * @param enable_unsolicited Allows unsolicited discovery.
	 */
	discover_service(io_service &io,
					 local_transaction_pool &lpool,
					 address_book &abook,
					 user_book &user_abook,
					 transmit &t,
					 std::vector<mih::octet_string> &dscv_order,
					 bool enable_unsolicited);

	/**
	 * Discovery request handler.
	 *
	 * @param in The input message.
	 * @param out The output message.
	 */
	void request(meta_message_ptr& in, meta_message_ptr& out);

	/**
	 * Discovery response handler.
	 *
	 * @param in The input message.
	 * @param out The output message.
	 */
	void response(meta_message_ptr& in, meta_message_ptr& out);

protected:
	/**
	 * Request PoS capabilities using MIH Capability Discover procedure.
	 *
	 * @param out The output message.
	 * @param pos The PoS information.
	 * @param unsolicited Allows unsolicited discovery.
	 */
	void request_pos_capabilities(meta_message_ptr& out, mih::mos_info &pos, bool unsolicited);

private:
	io_service				&_io;				/**< IO service module.				*/
	local_transaction_pool	&_lpool;			/**< Local transaction pool module.	*/
	address_book			&_abook;			/**< Address book module.			*/
	user_book				&_user_abook;		/**< User book module.				*/
	transmit				&_transmit;			/**< Transmit book module.			*/
	std::vector<mih::octet_string> _dscv_order;	/**< Ordered list of discovery entities.*/
	bool					_enable_unsolicited;/**< Allows unsolicited discovery.	*/
};

} /* namespace mihf */ } /* namespace odtone */

#endif
