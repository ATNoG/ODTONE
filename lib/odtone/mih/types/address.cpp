//==============================================================================
// Brief   : MIH Address Types
// Authors : Bruno Santos <bsantos@av.it.pt>
//           Carlos Guimaraes <cguimaraes@av.it.pt>
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
#include <odtone/mih/types/address.hpp>

#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>

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
		std::vector<int> tmp(_addr.size());

		for (size_t i = 0; i < _addr.size(); ++i) {
			if(i != 0)
				str += '.';
			tmp[i] = _addr[i] & 0x000000FF;
			std::stringstream temp;
			temp << tmp[i];
			str += temp.str();
		}
	} else if(_type == ip_addr::ipv6) {
		for (size_t i = 0; i < _addr.size(); i += 2) {
			str += to_string_hex(&_addr[i], 1);
			str += to_string_hex(&_addr[i + 1], 1);
			str += ':';
		}
		if (str.length())
			str.erase(str.length() - 1);
	}

	return str;
}

void ip_addr::address(const octet_string& addr)
{
	using namespace boost;

	if(_type == ip_addr::ipv4) {
		char_separator<char> sep(".");
		tokenizer< char_separator<char> > list_tokens(addr, sep);

		_addr.clear();

		BOOST_FOREACH(mih::octet_string str, list_tokens)
		{
			std::istringstream buffer(str);
			unsigned int value;
			buffer >> value;
			_addr += value;
		}
	} else if(_type == ip_addr::ipv6) {
		char_separator<char> sep(":");
		tokenizer< char_separator<char> > list_tokens(addr, sep);

		_addr.clear();

		BOOST_FOREACH(mih::octet_string str, list_tokens)
		{
			uchar tmp[4];
			tmp[0] = 0;
			tmp[1] = 0;
			tmp[2] = 0;
			tmp[3] = 0;

			for (size_t j = 0; j < str.length(); ++j)
				tmp[j] = hex_to_int(str[j]);

			_addr += char((tmp[0] << 4) | tmp[1]);
			_addr += char((tmp[2] << 4) | tmp[3]);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /*namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
