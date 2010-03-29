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
#include "base.hpp"
#include <odtone/sap/link.hpp>
<<<<<<< HEAD:src/link_sap/link_sap.hpp
#include "interface/interface.hpp"
=======
>>>>>>> develop:app/link_sap/link_sap.hpp
#include <boost/utility.hpp>
#include <memory>

#ifdef BOOST_WINDOWS
#include <odtone/sap/nif/interface.hpp>
using odtone::sap::nif::interface;
using odtone::sap::nif::interface_map;
#else
#include "interface/interface.hpp"
#endif

///////////////////////////////////////////////////////////////////////////////
namespace link_sap {

///////////////////////////////////////////////////////////////////////////////
class link_sap : boost::noncopyable {
public:
	link_sap(const odtone::mih::config& cfg, boost::asio::io_service& io);
	~link_sap();

<<<<<<< HEAD:src/link_sap/link_sap.hpp
	void update(nic::interface* it);
=======
	void update(/*odtone::sap::nif::*/interface* it);
>>>>>>> develop:app/link_sap/link_sap.hpp

private:
	void default_handler(odtone::mih::message& msg);

private:
<<<<<<< HEAD:src/link_sap/link_sap.hpp
	odtone::sap::link  _mihf;
	nic::interface_map _ifmap;
=======
	odtone::sap::link               _mihf;
	/*odtone::sap::nif::*/interface_map _ifmap;
>>>>>>> develop:app/link_sap/link_sap.hpp
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace link_sap */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* LINK_SAP__HPP_ */
