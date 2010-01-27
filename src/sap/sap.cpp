//=============================================================================
// Brief   : SAP IO Service
// Authors : Bruno Santos <bsantos@av.it.pt>
//
//
// Copyright (C) 2009 Universidade Aveiro - Instituto de Telecomunicacoes Polo Aveiro
//
// This file is part of ODTONE - Open Dot Twenty One.
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//=============================================================================

#include <odtone/sap/sap.hpp>

///////////////////////////////////////////////////////////////////////////////
 /**
 * \defgroup SAP
 *
 * <b> Overview </b>
 *
 * The SAP API contains a set of IO service classes to send/receive MIH
 * messages. The implementation is modeled after \a boost::asio and only
 * supports asynchronous operation. IO services (odtone::sap::user and
 * odtone::sap::link) are provided to implement User SAP's and Link SAP's.
 *
 * It's important to be familiar with the \a boost::asio library. It's also
 * recommend to be familiar with \a boost::function and \a boost::bind.
 *
 * <b> Tutorial </b>
 *
 * In this example we have very basic running MIH User. In this example
 * it only receives MIH messages:
 * \code
 * void event_handler(odtone::mih::message& pm, const boost::system::error_code& ec)
 * {
 *     if (ec) {
 *         //do something with the error
 *         return;
 *     }
 *
 *     switch (pm.mid()) {
 *     case odtone::indication::link_up:
 *         //...
 *         break;
 *
 *     default:
 *         //...
 * }
 *
 * int main()
 * {
 *     boost::asio::io_service ios;
 *     odtone::mih::config cfg;
 *     odtone::sap::user mih_usr(cfg, ios, &event_handler);
 *
 *     ios.run();
 * }
 * \endcode
 *
 * To send messages, we need a callback handler:
 * \code
 * void register_response_handler(odtone::mih::message& msg, const boost::system::error_code& ec)
 * {
 *     if (ec) {
 *         //do something with the error
 *         return;
 *     }
 *
 *     odtone::mih::status st;
 *
 *     msg >> odtone::mih::response()
 *          & odtone::mih::tlv_status(st);
 *
 *     //...
 * }
 * \endcode
 *
 * And a few modifications in main to send the message:
 * \code
 * int main()
 * {
 *     boost::asio::io_service ios;
 *     odtone::mih::config cfg;
 *     odtone::sap::user usr(cfg, ios, &event_handler);
 *
 *     msg << odtone::mih::request(odtone::mih::request::mih_register);
 *
 *     usr.async_send(msg, &register_response_handler);
 *
 *     ios.run();
 * }
 * \endcode
 *
 * User and Link SAP example implementations are provided in the source code
 * distribution.
 */
// EOF ////////////////////////////////////////////////////////////////////////
