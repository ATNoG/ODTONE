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

#ifndef ODTONE_MIHF_LOG_HPP
#define ODTONE_MIHF_LOG_HPP

///////////////////////////////////////////////////////////////////////////////
#include <odtone/logger.hpp>
///////////////////////////////////////////////////////////////////////////////

namespace odtone {

/**
 * This class represents the logger.
 */
class log_t
{
public:
	/**
	 * Create a instance of the logger.
	 */
	static logger* instance();

	/**
	 * Destructor of the logger.
	 */
	~log_t();

private:
	static logger		*ptr_instance;
};

#define ODTONE_LOG (*log_t::instance())

} /* namespace odtone */

#endif
