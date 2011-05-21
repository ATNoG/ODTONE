//=============================================================================
// Brief   : Logging Facilities
// Authors : Bruno Santos <bsantos@av.it.pt>
//------------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2009-2011 Universidade Aveiro
// Copyright (C) 2009-2011 Instituto de Telecomunicações - Pólo Aveiro
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//==============================================================================

#include <odtone/debug.hpp>
#include <odtone/logger.hpp>
#include <boost/make_shared.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone {

///////////////////////////////////////////////////////////////////////////////
/**
 * Construct a Logger.
 *
 * @param name logger's name.
 * @param log logger from where extract the configurations for the new logger.
 */
logger::logger(char const* const name, logger& log)
	: _name(name), _lock(log._lock), _sink(log._sink), _level(log._level)
{
	ODTONE_ASSERT(name);
}

/**
 * Construct a Logger.
 *
 * @param name logger's name.
 * @param sink std::ostream that defines how the logger will write and format output as sequences of characters.
 */
logger::logger(char const* const name, std::ostream& sink)
	: _name(name), _lock(boost::make_shared<boost::mutex>()), _sink(sink), _level(0)
{
	ODTONE_ASSERT(name);
}

/**
 * Destruct for Logger.
 */
logger::~logger()
{
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
