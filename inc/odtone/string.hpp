//=============================================================================
// Brief   : STL Platform Specific Unicode String
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

#ifndef ODTONE_STRING__HPP_
#define ODTONE_STRING__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <string>
#include <cstring>

///////////////////////////////////////////////////////////////////////////////
namespace odtone {

///////////////////////////////////////////////////////////////////////////////
template<class CharT>
class basic_const_string_ref {
public:
	typedef CharT const* type;

	basic_const_string_ref(type str)
		: _str(str), _len(std::strlen(str))
	{ }
	basic_const_string_ref(std::basic_string<CharT> const& str)
		: _str(str.c_str()), _len(str.length())
	{ }

	char const* data() const { return _str; }
	size_t length() const    { return _len; }

	CharT operator[](ptrdiff_t idx) const { return _str[idx]; }

private:
	type   _str;
	size_t _len;
};

typedef basic_const_string_ref<char>    const_string_ref;
typedef basic_const_string_ref<wchar_t> const_wstring_ref;

///////////////////////////////////////////////////////////////////////////////
} /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_STRING__HPP_ */
