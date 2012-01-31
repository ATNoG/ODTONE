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

#ifndef ODTONE_NET_LINK_ADDRESS_MAC__HPP_
#define ODTONE_NET_LINK_ADDRESS_MAC__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <boost/array.hpp>
#include <utility>
#include <string>
#include <ostream>
#include <cctype>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace net { namespace link {

///////////////////////////////////////////////////////////////////////////////
/**
 * This class represents the MAC address.
 */
class address_mac {
public:
	typedef boost::array<uint8, 6> bytes_type;

public:
	/**
	 * Get the MAC address from a string.
	 *
	 * @param str The input string.
	 * @return The extracted MAC address.
	 */
	static address_mac from_string(const char* str);

	/**
	 * Get the MAC address from a string.
	 *
	 * @param str The input string.
	 * @return The extracted MAC address.
	 */
	static address_mac from_string(const std::string& str);

public:
	/**
	 * Construct an empty MAC address.
	 */
	address_mac()
	{
		_address.assign(0);
	}

	/**
	 * Construct a MAC address.
	 *
	 * @param address The MAC address raw bytes.
	 */
	explicit address_mac(const uint8 address[6])
	{
		std::copy(address, address + 6, _address.begin());
	}

	/**
	 * Construct a MAC address.
	 *
	 * @param address The MAC address raw bytes.
	 */
	explicit address_mac(const bytes_type& address)
	{
		std::copy(address.begin(), address.end(), _address.begin());
	}

	/**
	 * Check if the MAC address is smaller than another MAC address.
	 *
	 * @param lhs The MAC address to compare with.
	 * @return True if they are equal or false otherwise.
	 */
	bool operator<(const address_mac& lhs) const
	{
		return _address < lhs._address;
	}

	/**
	 * Convert the MAC address to a string.
	 *
	 * @return A string representation of this object.
	 */
	std::string to_string() const;

	/**
	 * Get the MAC address raw bytes.
	 *
	 * @return The MAC address raw bytes.
	 */
	bytes_type  to_bytes() const;

	/**
	 * MAC address output.
	 *
	 * @param out ostream.
	 * @param mac The IPv6 Prefix.
	 * @return ostream reference.
	 */
	friend std::ostream& operator<<(std::ostream& out, const address_mac& mac)
	{
		return out << mac.to_string();
	}

public:
	bytes_type _address;	/**< The MAC address raw bytes.	*/
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace link */ } /* namespace net */ } /* namespace odtone */

///////////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_NET_LINK_ADDRESS_MAC__HPP_ */
