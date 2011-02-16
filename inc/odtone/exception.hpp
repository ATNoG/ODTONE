//=============================================================================
// Brief   : Exception Base Class
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

#ifndef ODTONE_EXCEPTION__HPP_
#define ODTONE_EXCEPTION__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <boost/exception/exception.hpp>
#include <boost/throw_exception.hpp>
#include <exception>

///////////////////////////////////////////////////////////////////////////////
namespace odtone {

///////////////////////////////////////////////////////////////////////////////
/**
 * The BASE API offers support mechanisms for exceptions support. The odtone::exception
 * class serves as a base from which derive all exceptions in ODTONE.
 */
class exception
	: virtual public boost::exception, virtual public std::exception {
public:
	/**
	 * Constructor a new exception
	 *
	 * @param what textual value of the exception.
	 */
	exception(char const* what = "<exception>") : _what(what)
	{ }

	/**
	 * Get textual value of the exception.
	 *
	 * @return The textual value of the exception.
	 */
	char const* what() const throw() { return _what; }

private:
	char const* _what;
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_EXCEPTION__HPP_ */
