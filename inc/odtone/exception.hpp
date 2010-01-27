//=============================================================================
// Brief   : Exception Base Class
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

#ifndef ODTONE_EXCEPTION__HPP_
#define ODTONE_EXCEPTION__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <boost/exception/exception.hpp>
#include <boost/throw_exception.hpp>
#include <exception>

///////////////////////////////////////////////////////////////////////////////
namespace odtone {

///////////////////////////////////////////////////////////////////////////////
class exception
	: virtual public boost::exception, virtual public std::exception {
public:
	exception(char const* what = "<exception>") : _what(what)
	{ }

	char const* what() const throw() { return _what; }

private:
	char const* _what;
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_EXCEPTION__HPP_ */
