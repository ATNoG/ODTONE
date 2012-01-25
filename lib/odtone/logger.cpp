//==============================================================================
// Brief   : Logging Facilities
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

#include <odtone/debug.hpp>
#include <odtone/logger.hpp>
#include <boost/make_shared.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone {

///////////////////////////////////////////////////////////////////////////////
/**
 * Construct a logger by copying it from another logger.
 *
 * @param name Logger's name.
 * @param log Logger to copy.
 */
logger::logger(char const* const name, logger& log)
	: _lock(log._lock), _name(name), _sink(log._sink), _level(log._level)
{
	ODTONE_ASSERT(name);
}

/**
 * Construct a logger.
 *
 * @param name Logger's name.
 * @param sink std::ostream which defines how the logger will write and
 *             format output.
 */
logger::logger(char const* const name, std::ostream& sink)
	: _lock(boost::make_shared<boost::mutex>()), _name(name), _sink(sink), _level(0)
{
	ODTONE_ASSERT(name);
}

/**
 * Destruct a logger.
 */
logger::~logger()
{
}

/**
 * Set the output level. Each logger has a level associated with it.
 * This reflects the maximum level that the logger cares about. So, if the
 * logger level is set to 2 it only cares about log messages belonging
 * to level 0, 1 and 2.
 *
 * @param n Logger level.
 */
void logger::level(uint n)
{
	_level = n;
}

/**
 * Get the level configuration. Each logger has a level associated with it.
 * This reflects the maximum level that the logger cares about. So, if the
 * logger level is set to 2 it only cares about log messages belonging
 * to level 0, 1 and 2.
 *
 * @return The logger level.
 */
uint logger::level() const
{
	return _level;
}

/**
 * Get the std::ostream associated with the logger.
 *
 * @return The std::ostream associated with the logger.
 */
std::ostream& logger::sink() const
{
	return _sink;
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
