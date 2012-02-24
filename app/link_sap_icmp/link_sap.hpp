//==============================================================================
// Brief   : ICMP Link SAP
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

#ifndef LINK_SAP__HPP_
#define LINK_SAP__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/debug.hpp>
#include <odtone/mih/types/capabilities.hpp>
#include <odtone/sap/link.hpp>

using namespace odtone;

///////////////////////////////////////////////////////////////////////////////
namespace link_sap {

///////////////////////////////////////////////////////////////////////////////
/**
 * Link SAP
 */
class link_sap : boost::noncopyable {
public:
	/**
	 * Construct a Link SAP module.
	 *
	 * @param cfg Configuration information.
	 * @param io The io_service object that ICMP Link SAP will use to dispatch
	 * handlers for any asynchronous operations performed on the socket.
	 * @param ifname Interface name.
	 * @param link_id Link identifier.
	 * @param capabilities_event_list Supported events.
	 * @param capabilities_command_list Supported commands.
	 */
	link_sap(const mih::config& cfg,
			 boost::asio::io_service& io,
			 mih::octet_string ifname,
			 mih::link_id link_id,
			 mih::link_evt_list capabilities_event_list,
			 mih::link_cmd_list capabilities_command_list);

	/**
	 * Destruct a Link SAP module.
	 */
	~link_sap();

private:

	/**
	 * ICMP message handler.
	 *
	 * @param buff Message byte buffer.
	 * @param rbytes Size of the received message.
	 * @param error Error code.
	 */
	void icmp_handler(buffer<uint8>& buff, size_t rbytes,
					  const boost::system::error_code& ec);

	/**
	 * IEEE 802.21 message handler.
	 *
	 * @param buff Received message.
	 * @param error Error code.
	 */
	void ieee80221_handler(mih::message& msg,
						   const boost::system::error_code& ec);

	/**
	 * Register the Link SAP with the local MIHF.
	 */
	void register_local_mihf();

	/**
	 * Asynchronously receive an ICMP message.
	 */
	void icmp_recv_async();

private:
	sap::link						_mihf;		/**< MIHF interface.*/
	boost::asio::ip::icmp::socket	_icmp_sock;	/**< ICMP socket. 	*/

	mih::octet_string	_ifname;					/**< Interface name.	*/
	mih::link_id		_link_id;					/**< Link identifier.	*/
	mih::link_evt_list	_capabilities_event_list;	/**< Supported events. 	*/
	mih::link_cmd_list	_capabilities_command_list;	/**< Supported commands.*/
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace link_sap */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* LINK_SAP__HPP_ */
