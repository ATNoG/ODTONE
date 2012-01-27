//==============================================================================
// Brief   : Link SAP
// Authors : Bruno Santos <bsantos@av.it.pt>
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
#include "base.hpp"
#include <odtone/sap/link.hpp>
#include "interface/interface.hpp"
#include <boost/utility.hpp>
#include <memory>

///////////////////////////////////////////////////////////////////////////////
namespace link_sap {

///////////////////////////////////////////////////////////////////////////////
/**
 * This class provides an implementation of an IEEE 802.21 Link SAP.
 */
class link_sap : boost::noncopyable {
public:
	/**
	 * Construct the Link SAP.
	 *
	 * @param cfg Configuration options.
	 * @param io The io_service object that Link SAP will use to
	 * dispatch handlers for any asynchronous operations performed on the socket. 
	 */
	link_sap(const odtone::mih::config& cfg, boost::asio::io_service& io);

	/**
	 * Destruct the Link SAP.
	 */
	~link_sap();

	/**
	 * Update the state of the interface. If the state has been changed
	 * notify its local MIHF
	 *
	 * @param it Interface information.
	 */
	void update(nic::interface* it);

private:
	/**
	 * Default MIH event handler.
	 *
	 * @param msg Received message.
	 * @param ec Error code.
	 */
	void default_handler(odtone::mih::message& msg, const boost::system::error_code& ec);

	/**
	 * Initialization of Link SAP. Responsible for sending Link SAP register message
	 * to the local MIHF.
	 */
	void init();

private:
	odtone::sap::link  _mihf;	/**< Link SAP helper */
	nic::interface_map _ifmap;	/**< Interface map */
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace link_sap */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* LINK_SAP__HPP_ */
