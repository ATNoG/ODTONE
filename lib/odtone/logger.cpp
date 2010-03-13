//=============================================================================
// Brief   : Logging Facilities
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

#include <odtone/debug.hpp>
#include <odtone/logger.hpp>
#include <boost/make_shared.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone {

///////////////////////////////////////////////////////////////////////////////
logger::logger(char const* const name, logger& log)
	: _name(name), _lock(log._lock), _sink(log._sink), _level(log._level)
{
	ODTONE_ASSERT_PTR(name);
}

logger::logger(char const* const name, std::ostream& sink)
	: _name(name), _lock(boost::make_shared<boost::mutex>()), _sink(sink), _level(0)
{
	ODTONE_ASSERT_PTR(name);
}

logger::~logger()
{
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
