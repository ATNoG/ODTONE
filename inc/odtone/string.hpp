//=============================================================================
// Brief   : STL Platform Specific Unicode String
// Authors : Bruno Santos <bsantos@av.it.pt>
//
//
// Copyright (C) 2010 Universidade Aveiro - Instituto de Telecomunicacoes Polo Aveiro
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

#ifndef ODTONE_STRING__HPP_
#define ODTONE_STRING__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <string>

///////////////////////////////////////////////////////////////////////////////
namespace odtone {

///////////////////////////////////////////////////////////////////////////////
#ifdef BOOST_WINDOWS

#define ODTONE_L     L
typedef wchar_t      char_t;
typedef std::wstring string;

#else

#define ODTONE_L
typedef char        char_t;
typedef std::string string;

#endif

///////////////////////////////////////////////////////////////////////////////
} /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_STRING__HPP_ */
