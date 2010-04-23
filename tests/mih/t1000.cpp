//=============================================================================
// Brief     : Base Serialization Unit Tests
// Copyright : © 2009 Instituto de Telecomunicações
//=============================================================================

#include <odtone/debug.hpp>
#include <odtone/mih/archive.hpp>
#include <odtone/random.hpp>
#include <algorithm>
#include <cstdlib>
#include <cassert>
#include <string>
#include <list>

///////////////////////////////////////////////////////////////////////////////
using odtone::uint8;
using odtone::uint16;
using odtone::uint32;
using odtone::uint64;
using odtone::sint8;
using odtone::sint16;
using odtone::sint32;
using odtone::sint64;

//
// TODO: use a better random number generator
//

///////////////////////////////////////////////////////////////////////////////
void t1000()
{
	odtone::mih::archive arch;


	std::string       a1("The quick brown fox jumps over the lazy dog");
	const uint8       b1 = odtone::mih::rand8();
	const uint16      c1 = odtone::mih::rand16();
	const uint32      d1 = odtone::mih::rand32();
	const uint64      e1 = odtone::mih::rand64();
	const bool        f1 = (odtone::mih::rand8() % 2);
	std::list<uint32> g1(odtone::mih::rand16() >> 2);

	std::fill(g1.begin(), g1.end(), odtone::mih::rand32());

	odtone::mih::oarchive& out = arch.output();

	out & a1;
	out & b1;
	out & c1;
	out & d1;
	out & e1;
	out & f1;
	out & g1;


	std::string       a2("Junk");
	uint8             b2 = b1 ^ ~0;
	uint16            c2 = c1 ^ ~0;
	uint32            d2 = d1 ^ ~0;
	uint64            e2 = e1 ^ ~0;
	bool              f2 = !f1;
	std::list<uint32> g2(odtone::mih::rand16());

	odtone::mih::iarchive& in = arch.input();

	in.rewind();

	in & a2;
	in & b2;
	in & c2;
	in & d2;
	in & e2;
	in & f2;
	in & g2;

	ODTONE_ASSERT(a1 == a2);
	ODTONE_ASSERT(b1 == b2);
	ODTONE_ASSERT(c1 == c2);
	ODTONE_ASSERT(d1 == d2);
	ODTONE_ASSERT(e1 == e2);
	ODTONE_ASSERT(f1 == f2);
	ODTONE_ASSERT(g1 == g2);
}

// EOF ////////////////////////////////////////////////////////////////////////
