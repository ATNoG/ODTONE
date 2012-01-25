//==============================================================================
// Brief   : MIHF ID
// Authors : Simao Reis <sreis@av.it.pt>
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

///////////////////////////////////////////////////////////////////////////////
#include "mihfid.hpp"
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

mih::id *mihfid_t::ptr_instance = NULL;

/**
 * Constructor of the MIHF MIH Identifier.
 */
mihfid_t::mihfid_t()
{
}

/**
 * Destructor of the MIHF MIH Identifier.
 */
mihfid_t::~mihfid_t()
{
	if (ptr_instance)
		delete ptr_instance;
}

/**
 * Create a instance of the MIHF MIH Identifier.
 */
mih::id* mihfid_t::instance()
{
	if (ptr_instance == NULL)
		ptr_instance = new mih::id();

	return ptr_instance;
}

} /* namespace mihf */ } /* namespace odtone */
