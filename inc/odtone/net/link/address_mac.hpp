//=============================================================================
// Brief   : Link Layer MAC Address
// Authors : Bruno Santos <bsantos@av.it.pt>
// ----------------------------------------------------------------------------
// ODTOne - Open Dot Twenty One
//
// Copyright (C) 2010-2011 Universidade de Aveiro
// Copyrigth (C) 2010-2011 Instituto de Telecomunicações - Pólo de Aveiro
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//=============================================================================

#ifndef ODTONE_NET_LINK_ADDRESS_MAC__HPP_
#define ODTONE_NET_LINK_ADDRESS_MAC__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <boost/array.hpp>
#include <utility>
#include <string>
#include <ostream>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace net { namespace link {

///////////////////////////////////////////////////////////////////////////////
class address_mac {
public:
	typedef boost::array<uint8, 6> bytes_type;

public:
	static address_mac from_string(const char* str);
	static address_mac from_string(const std::string& str);

public:
	address_mac()
	{
		_address.assign(0);
	}

	explicit address_mac(const uint8 address[6])
	{
		std::copy(address, address + 6, _address.begin());
	}

	explicit address_mac(const bytes_type& address)
	{
		std::copy(address.begin(), address.end(), _address.begin());
	}

	bool operator<(const address_mac& lhs) const
	{
		return _address < lhs._address;
	}

	std::string to_string() const;
	bytes_type  to_bytes() const;

	friend std::ostream& operator<<(std::ostream& out, const address_mac& mac)
	{
		return out << mac.to_string();
	}

public:
	bytes_type _address;
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace link */ } /* namespace net */ } /* namespace odtone */

///////////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_NET_LINK_ADDRESS_MAC__HPP_ */
