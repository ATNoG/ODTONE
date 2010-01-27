//=============================================================================
// Brief   : MIH Address Types
// Authors : Bruno Santos <bsantos@av.it.pt>
//
//
// Copyright (C) 2009 Universidade Aveiro - Instituto de Telecomunicacoes Polo Aveiro
//
// This file is part of ODTONE - Open Dot Twenty One.
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//=============================================================================

#include <odtone/strutil.hpp>
#include <odtone/mih/types/address.hpp>

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

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /*namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
