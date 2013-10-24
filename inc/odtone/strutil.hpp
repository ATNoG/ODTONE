//=============================================================================
// Brief   : String Utilities
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

#ifndef ODTONE_STRUTIL__HPP_
#define ODTONE_STRUTIL__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/debug.hpp>
#include <odtone/string.hpp>
#include <odtone/win32.hpp>
#include <string>

///////////////////////////////////////////////////////////////////////////////
namespace odtone {

///////////////////////////////////////////////////////////////////////////////
/**
 * Convert a value to hexadecimal.
 *
 * @param src Value to convert.
 * @param len Length of the value to convert.
 * @return The converted hexadecimal value string.
 */
std::string to_string_hex(const void* src, size_t len);

/**
 * Convert a value to hexadecimal values.
 *
 * @param v Value to convert.
 * @return The converted hexadecimal value string.
 */
template<class T>
inline std::string to_string_hex(const T& v)
{
	return to_string_hex(&v, sizeof(T));
}

/**
 * Convert a hexadecimal value to an int.
 *
 * @param c Hexadecimal value.
 * @return The converted int value.
 */
inline uchar hex_to_int(uchar c)
{
	if (c >= 'a')
		return c - 'a' + 0xA;

	if (c >= 'A')
		return c - 'A' + 0xA;

	return c - '0';
}

#ifdef _WIN32
/**
 * Convert a UTF-8 string to native UTF representation
 */
inline std::wstring ustr(const_string_ref str)
{
	return win32::utf8_to_utf16(str);
}

/**
 * Convert a native UTF representation string to UTF-8
 */
inline std::string ustr(const_wstring_ref str)
{
	return win32::utf16_to_utf8(str);
}

#else

/**
 * Convert a UTF-8 string to the native UTF representation
 */
inline char const* ustr(char const* str)
{
	return str;
}

/**
 * Convert a UTF-8 string to the native UTF representation
 */
inline std::string const& ustr(std::string const& str)
{
	return str;
}

#endif /* _WIN32 */

///////////////////////////////////////////////////////////////////////////////
} /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_STRUTIL__HPP_ */
