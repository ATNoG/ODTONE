//=============================================================================
// Brief   : Link SAP
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

#ifndef LINK_SAP__HPP_
#define LINK_SAP__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/sap/link.hpp>
#include <boost/utility.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include "interface/interface.hpp"

///////////////////////////////////////////////////////////////////////////////
class link_sap : boost::noncopyable {
public:
	link_sap(const odtone::mih::config& cfg, boost::asio::io_service& io);
	~link_sap();

	void update(interface* it);

private:
	void default_handler(odtone::mih::message& msg);
	void cleanup_handler(odtone::mih::message& msg, const boost::system::error_code& ec);

private:
	odtone::sap::link _mihf;
	interface_map     _ifmap;
};

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* LINK_SAP__HPP_ */
