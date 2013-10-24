//=============================================================================
// Brief   : Win32 API Wrappers
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

#ifndef ODTONE_WIN32__HPP_
#define ODTONE_WIN32__HPP_
#ifdef _WIN32

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/debug.hpp>
#include <odtone/string.hpp>

#include <boost/filesystem.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace win32 {

///////////////////////////////////////////////////////////////////////////////
namespace detail {

///////////////////////////////////////////////////////////////////////////////
const uint k_cp_utf8            = 65001;
const uint k_mb_err_inv_char    = 0x00000008;
const uint k_wc_err_inv_char    = 0x00000080;
const uint k_fmt_msg_alloc_buff = 0x00000100;
const uint k_fmt_msg_from_sys   = 0x00001000;

/* Windows Types
 * BOOL      -> int
 * BOOLEAN   -> unsigned char
 * BYTE      -> unsigned char
 * DWORD     -> unsigned int
 */

extern "C" uint __stdcall GetLastError();

extern "C" int __stdcall MultiByteToWideChar(uint code_page, uint flags,
                                             char const* src, int src_len,
                                             wchar_t* dst, int dst_len);
extern "C" int __stdcall WideCharToMultiByte(uint code_page, uint flags,
                                             wchar_t const* src, int src_len,
                                             char* dst, int dst_len,
                                             const char* def_char, bool* used_def_char);

extern "C" void* __stdcall LoadLibraryW(wchar_t const* filepath);
extern "C" int   __stdcall FreeLibrary(void* module);
extern "C" void* __stdcall GetProcAddress(void* module, char const* name);

///////////////////////////////////////////////////////////////////////////////
} /* namespace detail */

///////////////////////////////////////////////////////////////////////////////
std::wstring utf8_to_utf16(const_string_ref src);
std::string  utf16_to_utf8(const_wstring_ref src);

inline uint get_last_error()
{
	return detail::GetLastError();
}

inline std::string error_to_string(uint error)
{
	return boost::system::system_category().message(error);
}

inline void* load_library(const_string_ref filepath)
{
	return detail::LoadLibraryW(utf8_to_utf16(filepath).c_str());
}

inline bool free_library(void* module)
{
	return detail::FreeLibrary(module);
}

inline void* get_library_symbol(void* module, const_string_ref name)
{
	return detail::GetProcAddress(module, name);
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace win32 */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* _WIN32 */
#endif /* ODTONE_WIN32__HPP_ */
