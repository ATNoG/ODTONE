//=============================================================================
// Brief   : Ethtool interface for fetching data rate.
// Authors : André Prata <andreprata@av.it.pt>
//-----------------------------------------------------------------------------
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

#ifndef ETHTOOL__HPP_
#define ETHTOOL__HPP_

#include <string>

namespace odtone {

/**
 * Get the current interface speed, in Mbit/s
 */
unsigned int get_interface_speed(const std::string &name);

}; // namespace odtone

// EOF ////////////////////////////////////////////////////////////////////////

#endif /* ETHTOOL__HPP_ */
