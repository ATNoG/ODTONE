//==============================================================================
// Brief   : Logger
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

#ifndef ODTONE_MIHF_LOG_HPP
#define ODTONE_MIHF_LOG_HPP

///////////////////////////////////////////////////////////////////////////////
#include <odtone/logger.hpp>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

/**
 * This class provides logging capabilities. It is implemented as a singleton.
 */
class log_t
{
public:
	/**
	 * Creates an instance of the logger.
	 */
	static logger* instance();

	/**
	 * Destructor of the logger.
	 */
	~log_t();

private:
	static logger		*ptr_instance;	/**< Logger instance pointer.	*/
};

#define ODTONE_LOG (*log_t::instance())

} /* namespace mihf */ } /* namespace odtone */

#endif
