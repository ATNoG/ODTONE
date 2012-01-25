//==============================================================================
// Brief   : Logger
// Authors : Carlos Guimaraes <cguimaraes@av.it.pt>
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
#include "log.hpp"
#include <iostream>
///////////////////////////////////////////////////////////////////////////////

namespace odtone {

logger *log_t::ptr_instance = NULL;

/**
 * Create a instance of the logger.
 */
logger* log_t::instance()
{
	if (ptr_instance == NULL)
		{
			ptr_instance = new logger("DHCP-User", std::cout);
		}

	return ptr_instance;
}

/**
 * Destructor of the logger.
 */
log_t::~log_t()
{
	if(ptr_instance)
		delete ptr_instance;
}


} /* namespace odtone */
