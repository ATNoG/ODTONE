//=============================================================================
// Brief   : Exception Base Class
// Authors : Bruno Santos <bsantos@av.it.pt>
//------------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2009-2013 Universidade Aveiro
// Copyright (C) 2009-2013 Instituto de Telecomunicações - Pólo Aveiro
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
#include <odtone/base.hpp>
#include <boost/exception/exception.hpp>
#include <boost/throw_exception.hpp>
#include <boost/system/error_code.hpp>
#include <exception>

///////////////////////////////////////////////////////////////////////////////
namespace odtone {

///////////////////////////////////////////////////////////////////////////////
using boost::throw_exception;

///////////////////////////////////////////////////////////////////////////////
/**
 * Base class for all ODTONE exceptions.
 * This is the base class that all odtone exceptions derive from.
 * Virtual inheritance must be used when deriving from this class!
 *
 * Example:
 * struct file_error : virtual public odtone::exception { };
 *
 * struct file_read_error : virtual public file_error {
 *     virtual const char* what() throw() { return "read file error"; }
 * };
 *
 * struct file_write_error : virtual public file_error {
 *     virtual const char* what() throw() { return "write file error"; }
 * };
 */
class exception : virtual public boost::exception, virtual public std::exception { };

///////////////////////////////////////////////////////////////////////////////
using boost::system::error_code;

inline error_code system_error_code(int val)
{
	return error_code(val, boost::system::system_category());
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_EXCEPTION__HPP_ */
