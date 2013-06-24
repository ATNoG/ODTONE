//==============================================================================
// Brief   : MIH Address Types
// Authors : Bruno Santos <bsantos@av.it.pt>
//           Carlos Guimaraes <cguimaraes@av.it.pt>
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

#include <odtone/strutil.hpp>
#include <odtone/mih/types/address.hpp>

#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>
#include <boost/asio.hpp>

#include <sstream>
#include <string>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
octet_string mac_addr::address() const
{
	octet_string str;

	for (size_t i = 0; i < _addr.size(); ++i) {
		str += to_string_hex(&_addr[i], 1);
		str += ':';
	}
	if (str.length())
		str.erase(str.length() - 1);

	return str;
}

void mac_addr::address(const octet_string& addr)
{
	octet_string::const_iterator i = addr.begin();
	octet_string::const_iterator end = addr.end();

	_addr.clear();

	while (i != end) {
		uchar tmp[2];

		tmp[0] = 0;
		tmp[1] = 0;
		for (size_t j = 0; (j < 2) && (i != end); ++j, ++i)
			tmp[j] = hex_to_int(*i);

		_addr += char((tmp[0] << 4) | tmp[1]);

		if (i != end && *i == ':')
			++i;
	}
}

octet_string ip_addr::address() const
{
	octet_string str;

	if(_type == ip_addr::ipv4) {
		boost::asio::ip::address_v4::bytes_type bytes;
		for(size_t i = 0; i < bytes.size(); ++i)
			bytes[i] = _addr[i];

		boost::asio::ip::address_v4 addrv4(bytes);
		str = addrv4.to_string();

	} else if(_type == ip_addr::ipv6) {
		boost::asio::ip::address_v6::bytes_type bytes;
		for(size_t i = 0; i < bytes.size(); ++i)
			bytes[i] = _addr[i];

		boost::asio::ip::address_v6 addrv6(bytes);
		str = addrv6.to_string();
	}

	return str;
}

void ip_addr::address(const octet_string& addr)
{
	boost::asio::ip::address address = boost::asio::ip::address::from_string(addr);

	if(address.is_v4()) {
		_type = ip_addr::ipv4;

		boost::asio::ip::address_v4 addrv4 = address.to_v4();
		boost::asio::ip::address_v4::bytes_type bytes = addrv4.to_bytes();
		for (size_t i = 0; i < bytes.size(); ++i)
			_addr += bytes[i];


	} else if(address.is_v6()) {
		_type = ip_addr::ipv6;

		boost::asio::ip::address_v6 addrv6 = address.to_v6();
		boost::asio::ip::address_v6::bytes_type bytes = addrv6.to_bytes();
		for (size_t i = 0; i < bytes.size(); ++i)
			_addr += bytes[i];

	}
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /*namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
