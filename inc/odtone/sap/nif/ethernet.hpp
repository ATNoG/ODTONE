//=============================================================================
// Brief   : Ethernet Network Interface
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

#ifndef ODTONE_SAP_NIF_ETHERNET__HPP_
#define ODTONE_SAP_NIF_ETHERNET__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/sap/nif/interface.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace sap { namespace nif {

///////////////////////////////////////////////////////////////////////////////
class interface_ethernet : public interface {
public:
	interface_ethernet(uint index, const std::string& name, const odtone::mih::mac_addr& mac_addr);
	~interface_ethernet();
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace nif */ } /* namespace sap */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_SAP_NIF_ETHERNET__HPP_ */
