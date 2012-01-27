//=============================================================================
// Brief   : ODTONE SAP library namespace documentation
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

#error Documentation only.


namespace odtone {
/**
 * ODTONE SAP library.
 *
 * The SAP library contains a set of I/O service classes, providing the ability
 * to send and receive MIH messages. The implementation is based on the
 * boost::asio and it only supports asynchronous operation.
 * @note It is important to be familiar with the boost::asio library.
 * It is also recommend to be familiar with boost::function and
 * boost::bind.
 *
 * Examples:
 *
 * Receive MIH Messages:
 *
 * Here is presented a very basic running MIH User SAP that only receives
 * MIH messages. To receive messages, callback handler is needed:
 * \code
 * void event_handler(odtone::mih::message& pm, const boost::system::error_code& ec)
 * {
 *		if (ec) {
 * 			//do something with the error
 * 			return;
 * 		}
 *
 * 		switch (pm.mid()) {
 *			case odtone::indication::link_up:
 *			//...
 *			break;
 *			default:
 *			//...
 *			}
 *		}
 * \endcode
 * 
 * And the main function:
 * \code
 * int main()
 * {
 * 		boost::asio::io_service ios;
 * 		odtone::mih::config cfg;
 * 		odtone::sap::user mih_usr(cfg, ios, &event_handler);
 *
 * 		ios.run();
 * }
 * \endcode
 *
 * Send MIH Messages:
 *
 * In this example the ability to send MIH messages is added:
 * To send messages, we need a callback handler:
 * \code
 * void register_response_handler(odtone::mih::message& msg, const boost::system::error_code& ec)
 * {
 * 		if (ec) {
 * 			//do something with the error
 * 			return;
 * 		}
 *
 * 		odtone::mih::status st;
 *
 * 		msg >> odtone::mih::response()
 * 			& odtone::mih::tlv_status(st);
 *
 * 		//...
 * }
 * \endcode
 *
 * And a few modifications in the main function:
 * \code
 * int main()
 * {
 * 		boost::asio::io_service ios;
 * 		odtone::mih::config cfg;
 * 		odtone::sap::user usr(cfg, ios, &event_handler);
 *
 * 		msg << odtone::mih::request(odtone::mih::request::mih_register);
 *
 * 		usr.async_send(msg, &register_response_handler);
 *
 * 		ios.run();
 * }
 * \endcode
 */
namespace sap {

} /* namespace sap */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
