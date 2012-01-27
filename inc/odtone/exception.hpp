//=============================================================================
// Brief   : Exception Base Class
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
 * Base class for all ODTONE exceptions. 
 * This is the base class for all exceptions thrown by the ODTONE library.
 * You are free to derive your own exception classes, or use a different
 * hierarchy, or to throw non-class data (e.g., fundamental types).
 */
class exception
	: virtual public boost::exception, virtual public std::exception {
public:
	/**
	 * Constructor a new exception.
	 *
	 * @param what General cause of the exception error description.
	 */
	exception(char const* what = "<exception>") : _what(what)
	{ }

	/**
	 * Get a string describing the general cause of the current error.
	 *
	 * @return A string describing the general cause of the current error.
	 */
	char const* what() const throw()
	{
		return _what;
	}

private:
	char const* _what; /**< General cause of the exception error description.*/
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_EXCEPTION__HPP_ */
