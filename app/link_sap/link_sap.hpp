//=============================================================================
// Brief   : Link SAP
// Authors : Bruno Santos <bsantos@av.it.pt>
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
class link_sap : boost::noncopyable {
public:
	link_sap(const odtone::mih::config& cfg, boost::asio::io_service& io);
	~link_sap();

	void update(nic::interface* it);

private:
	void default_handler(odtone::mih::message& msg);

	/**
	 * Initialization of Link SAP. Responsible for sending Link SAP register message
	 * to the local MIHF.
	 */
	void init();

private:
	odtone::sap::link  _mihf;
	nic::interface_map _ifmap;
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace link_sap */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* LINK_SAP__HPP_ */
