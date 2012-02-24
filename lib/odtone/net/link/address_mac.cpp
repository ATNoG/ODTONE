//=============================================================================
// Brief   : Link Layer MAC Address
// Authors : Bruno Santos <bsantos@av.it.pt>
// ----------------------------------------------------------------------------
// ODTOne - Open Dot Twenty One
//
// Copyright (C) 2009-2012 Universidade de Aveiro
// Copyrigth (C) 2009-2012 Instituto de Telecomunicações - Pólo de Aveiro
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//=============================================================================

#include <odtone/net/link/address_mac.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace net { namespace link {

///////////////////////////////////////////////////////////////////////////////
//FIXME: move this somewhere else
static uchar hex_to_int(uchar c)
{
	if (c >= 'a')
		return c - 'a' + 0xA;

	if (c >= 'A')
		return c - 'A' + 0xA;

	return c - '0';
}

///////////////////////////////////////////////////////////////////////////////
address_mac address_mac::from_string(const char* str)
{
	address_mac mac;
	uint i;

	for (i = 0; i < bytes_type::static_size; ++i) {
		uint8 tmp[2];

		if (!std::isxdigit(*str))
			break;
		tmp[0] = hex_to_int(*(str++));

		if (!std::isxdigit(*str))
			break;
		tmp[1] = hex_to_int(*(str++));

		mac._address[i] = (tmp[0] << 4) | tmp[1];

		if (*str != ':')
			break;
		++str;
	}

	if (((i + 1) != bytes_type::static_size) || *str != '\0')
		return address_mac();

	return mac;
}

address_mac address_mac::from_string(const std::string& str)
{
	return from_string(str.c_str());
}

address_mac::bytes_type address_mac::to_bytes() const
{
	return _address;
}

std::string address_mac::to_string() const
{
	std::string str;

	for (uint i = 0; i < bytes_type::static_size; ++i) {
		char tmp[4];

		tmp[0] = _address[i] >> 4;
		tmp[1] = _address[i] & 0x0f;
		tmp[2] = ':';
		tmp[3] = '\0';

		BOOST_ASSERT(!(tmp[0] & 0xf0) && !(tmp[1] & 0xf0));

		if (tmp[0] < 10)
			tmp[0] += '0';
		else
			tmp[0] += 'a' - 10;

		if (tmp[1] < 10)
			tmp[1] += '0';
		else
			tmp[1] += 'a' - 10;

		str.append(tmp);
	}
	str.resize(str.length() - 1);

	return str;
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace link */ } /* namespace net */ } /* namespace odtone */

///////////////////////////////////////////////////////////////////////////////
