//=============================================================================
// Brief   : Wireless Network Interface
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

#ifndef LINK_SAP_INTERFACE_802_11__HPP_
#define LINK_SAP_INTERFACE_802_11__HPP_

///////////////////////////////////////////////////////////////////////////////
#include "interface.hpp"

///////////////////////////////////////////////////////////////////////////////
class if_802_11 : public interface {
public:
	if_802_11(uint index, const std::string& name, const odtone::mih::mac_addr& link_addr);

private:
};

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* LINK_SAP_INTERFACE_802_11__HPP_ */
