//==============================================================================
// Brief   : String Utilities
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

#include <odtone/strutil.hpp>
#include <odtone/debug.hpp>

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
std::string to_string_hex(const void* src, size_t len)
{
	std::string str;

	if (len) {
		size_t l = 2 * len;

		ODTONE_ASSERT(l > len);

		str.resize(l);

		for (size_t i = 0, j = 0; i < len; ++i, j += 2) {
			uint v1 = uint(reinterpret_cast<const uchar*>(src)[i] & 0xF0) >> 4;
			uint v2 = uint(reinterpret_cast<const uchar*>(src)[i] & 0x0F);

			str[j    ] = (v1 < 10) ? '0' + v1 : 'a' + v1 - 10;
			str[j + 1] = (v2 < 10) ? '0' + v2 : 'a' + v2 - 10;
		}
	}

	return str;
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
