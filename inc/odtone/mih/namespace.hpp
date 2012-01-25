//=============================================================================
// Brief   : ODTONE MIH library namespace documentation
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
 * ODTONE MIH library.
 *
 * The ODTONE MIH library defines all MIH data types presented in the 802.21
 * standard. In addition, it provides a set of classes which facilitates
 * the creation and parsing of MIH messages.
 *
 * Examples:
 *
 * To generate and send a MIH message:
 * \code
 * odtone::mih::message msg;
 * odtone::mih::link_tuple_id li;
 * odtone::mih::event_list evts;
 *
 * //...
 *
 * msg << odtone::mih::request(odtone::mih::request::event_subscribe)
 *     & odtone::mih::tlv_link_identifier(li)
 *     & odtone::mih::tlv_event_list(evts);
 *
 * io_service.async_send(msg, &event_subscribe_response_handler);
 * \endcode
 *
 * Notice that we start with the message and then we use the operator << to
 * begin the generation of the message, followed by the message_helper
 * classes (odtone::mih::request, odtone::mih::response,
 * odtone::mih::indication or odtone::mih::confirm). To insert an TLV in the
 * message, the operator & is used followed by the tlv_fwd helper classes.
 *
 * To receive and parse a MIH message:
 * \code
 *     //...
 *
 *     msg << odtone::mih::request(odtone::mih::request::capability_discover);
 *
 *     user_sap_ios.async_send(msg, &capability_discover_response);
 *
 *     //...
 *
 * void capability_discovery_response(odtone::mih::message& msg, const boost::system::error_code& ec)
 * {
 *     if (ec) {
 *         // do something with the error and don't parse the msg or else,
 *         // an iarchive_eof_error exception is thrown
 *
 *         return;
 *     }
 *
 *     odtone::mih::status st;
 *     boost::optional<odtone::mih::net_type_addr_list> ntal;
 *     boost::optional<odtone::mih::event_list> evt;
 *
 *     msg >> odtone::mih::response()
 *         & odtone::mih::tlv_status(st)
 *         & odtone::mih::tlv_net_type_addr_list(ntal)
 *         & odtone::mih::tlv_event_list(evt);
 *
 *     //...
 * }
 * \endcode
 *
 * Here, to parse the message the operator >> is used. Everything else is
 * similar to previous example.
 *
 * Notice that for the optional parameters the correspondent MIH data type
 * is wrapped in a boost::optional.
 */
namespace mih {

} /* namespace mih */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
