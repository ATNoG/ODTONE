//==============================================================================
// Brief   : 802.11 Network Interface
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

#ifndef LINK_SAP_NIC_IF_802_11__HPP_
#define LINK_SAP_NIC_IF_802_11__HPP_

///////////////////////////////////////////////////////////////////////////////
#include "interface.hpp"

///////////////////////////////////////////////////////////////////////////////
namespace link_sap { namespace nic {

///////////////////////////////////////////////////////////////////////////////
/**
 * This class provides represents and stores information about an
 * IEEE 802.11 interface.
 */
class if_802_11 : public interface {
public:
	/**
	 * Construct an IEEE 802.11 interface representation.
	 *
	 * @param id IEEE 802.11 interface identifier.
	 */
	if_802_11(if_id const& id);
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace nic */ } /* namespace link_sap */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* LINK_SAP_NIC_IF_802_11__HPP_ */
