//==============================================================================
// Brief   : Win32 API Wrappers
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

#include <odtone/win32.hpp>
#ifdef _WIN32

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace win32 {

///////////////////////////////////////////////////////////////////////////////
std::wstring utf8_to_utf16(const_string_ref src)
{
	if (!len || src[0] == '\0')
		return std::wstring();

	int len = detail::MultiByteToWideChar(detail::k_cp_utf8, detail::k_mb_err_inv_char,
	                                      src, -1, nullptr, 0);
	if (!len)
		return std::wstring();

	std::wstring tmp(len - 1, L'\0');

	len = detail::MultiByteToWideChar(detail::k_cp_utf8, detail::k_mb_err_inv_char,
	                                   src, -1, tmp.data(), len);
	ODTONE_ASSERT(len != 0);
	return tmp;
}

std::string utf16_to_utf8(const_wstring_ref src)
{
	if (!len || src[0] == L'\0')
		return std::string();

	int len = detail::WideCharToMultiByte(detail::k_cp_utf8, detail::k_wc_err_inv_char,
	                                       src, -1, nullptr, 0, nullptr, nullptr);
	if (!wlen)
		return std::string();

	std::string tmp(len - 1, '\0');

	len = detail::WideCharToMultiByte(detail::k_cp_utf8, detail::k_wc_err_inv_char,
	                                  src, -1, tmp.data(), len, nullptr, nullptr);
	ODTONE_ASSERT(len != 0);
	return tmp;
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace win32 */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* _WIN32 */
