//=============================================================================
// Brief   : IP Address Prefix
// Authors : Bruno Santos <bsantos@av.it.pt>
// ----------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2009-2011 Universidade Aveiro
// Copyright (C) 2009-2011 Instituto de Telecomunicações - Pólo Aveiro
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//=============================================================================

#include <odtone/net/ip/prefix.hpp>
#include <boost/lexical_cast.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace net { namespace ip {

///////////////////////////////////////////////////////////////////////////////
prefix_v6 prefix_v6::from_string(const std::string& str)
{
	size_t pos = str.rfind('/');

	if (pos == std::string::npos)
		return prefix_v6(); //FIXME: throw_exception

	address_v6 addr = address_v6::from_string(str.substr(0, pos));
	uint       plen = boost::lexical_cast<uint>(str.substr(pos + 1));

	return prefix_v6(addr, plen);
}

prefix_v6::prefix_v6()
{
	_prefix.fill(0);
	_length = 0;
}

prefix_v6::prefix_v6(const bytes_type& addr, uint length)
{
	if (length > 128) {
		_prefix.fill(0);
		_length = 0;

	} else {
		_prefix = addr;
		_length = static_cast<uchar>(length);
	}
}

prefix_v6::prefix_v6(const address_v6& addr, uint length)
{
	if (length > 128) {
		_prefix.fill(0);
		_length = 0;

	} else {
		_prefix = addr.to_bytes();
		_length = static_cast<uchar>(length);
	}
}

bool prefix_v6::match(const address_v6& addr) const
{
	address_v6::bytes_type a(addr.to_bytes());
	uint byte_offset = _length / 8;
	uint bit_offset = _length % 8;

	if (!std::equal(_prefix.begin(), _prefix.begin() + byte_offset, a.begin()))
		return false;

	if (bit_offset) {
		uchar mask = 0xff << (8 - bit_offset);

		if ((_prefix[byte_offset] & mask) != (a[byte_offset] & mask))
			return false;
	}

	return true;
}

std::ostream& operator<<(std::ostream& out, const prefix_v6& lhr)
{
	return out << address_v6(lhr._prefix)
	           << '/' << static_cast<uint>(lhr._length);
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace net */ } /* namespace ip */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
