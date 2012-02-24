//=============================================================================
// Brief   : Random Utilities
// Authors : Bruno Santos <bsantos@av.it.pt>
//           Simao Reis <sreis@av.it.pt>
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

#ifndef ODTONE_MIH_RANDOM__HPP
#define ODTONE_MIH_RANDOM__HPP

#include <cstdlib>
#include <odtone/base.hpp>

namespace odtone { namespace mih {

/**
 * Generate a random 8-bit signed integer value.
 *
 * @return A random 8-bit signed integer value.
 */
inline sint8 srand8()
{
	srand(time(0));
	int n = std::rand();

	return sint8(n << 8) ^ sint8(n);
}

/**
 * Generate a random 16-bit signed integer value.
 *
 * @return A random 16-bit signed integer value.
 */
inline sint16 srand16()
{
	return (sint16(srand8()) << 8) | srand8();
}

/**
 * Generate a random 32-bit signed integer value.
 *
 * @return A random 32-bit signed integer value.
 */
inline sint32 srand32()
{
	return (sint32(srand16()) << 16) | srand16();
}

/**
 * Generate a random 64-bit signed integer value.
 *
 * @return A random 64-bit signed integer value.
 */
inline sint64 srand64()
{
	return (sint64(srand32()) << 32) | srand32();
}

/**
 * Generate a random 8-bit unsigned integer value.
 *
 * @return A random 8-bit unsigned integer value.
 */
inline uint8 rand8()
{
	return uint8(srand8());
}

/**
 * Generate a random 16-bit unsigned integer value.
 *
 * @return A random 16-bit unsigned integer value.
 */
inline uint16 rand16()
{
	return uint16(srand16());
}

/**
 * Generate a random 32-bit unsigned integer value.
 *
 * @return A random 32-bit unsigned integer value.
 */
inline uint32 rand32()
{
	return uint32(srand32());
}

/**
 * Generate a random 64-bit unsigned integer value.
 *
 * @return A random 64-bit unsigned integer value.
 */
inline uint64 rand64()
{
	return uint64(srand64());
}

} /* namespace mihf */ } /* namespace odtone */

#endif
