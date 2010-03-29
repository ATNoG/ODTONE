//
// Copyright (c) 2007-2009 2009 Universidade Aveiro - Instituto de
// Telecomunicacoes Polo Aveiro
// This file is part of ODTONE - Open Dot Twenty One.
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//
// Author:     Bruno Santos <bsantos@av.it.pt>
// Author:     Simao Reis <sreis@av.it.pt>
//

#ifndef ODTONE_MIH_RANDOM__HPP
#define ODTONE_MIH_RANDOM__HPP

#include <cstdlib>
#include <odtone/base.hpp>

namespace odtone { namespace mih {

inline sint8 srand8()
{
	srand(time(0));
	int n = std::rand();

	return sint8(n << 8) ^ sint8(n);
}

inline sint16 srand16() { return (sint16(srand8()) << 8) | srand8(); }
inline sint32 srand32() { return (sint32(srand16()) << 16) | srand16(); }
inline sint64 srand64() { return (sint64(srand32()) << 32) | srand32(); }
inline uint8  rand8()   { return uint8(srand8()); }
inline uint16 rand16()  { return uint16(srand16()); }
inline uint32 rand32()  { return uint32(srand32()); }
inline uint64 rand64()  { return uint64(srand64()); }

} /* namespace mihf */ } /* namespace odtone */

#endif
