//==============================================================================
// Brief   : IEEE 802 Interface
// Authors : Bruno Santos <bsantos@av.it.pt>
//------------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2009-2013 Universidade Aveiro
// Copyright (C) 2009-2013 Instituto de Telecomunicações - Pólo Aveiro
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//==============================================================================

#ifndef LINK_SAP_NIC_IF_802__HPP_
#define LINK_SAP_NIC_IF_802__HPP_

///////////////////////////////////////////////////////////////////////////////
#include "interface.hpp"

///////////////////////////////////////////////////////////////////////////////
namespace link_sap { namespace nic {

///////////////////////////////////////////////////////////////////////////////
/**
 * This class provides represents and stores information about an
 * IEEE 802 interface.
 */
class if_802 : public interface {
public:
	/**
	 * Construct an IEEE 802 interface representation.
	 *
	 * @param id IEEE 802 interface identifier.
	 */
	if_802(if_id const& id, odtone::mih::link_type lt);
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace nic */ } /* namespace link_sap */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* LINK_SAP_NIC_IF_802__HPP_ */
