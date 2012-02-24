//=============================================================================
// Brief   : IP Address Prefix
// Authors : Bruno Santos <bsantos@av.it.pt>
// ----------------------------------------------------------------------------
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
//=============================================================================

#ifndef ODTONE_NET_IP_PREFIX__HPP_
#define ODTONE_NET_IP_PREFIX__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/net/ip/address.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace net { namespace ip {

///////////////////////////////////////////////////////////////////////////////
/**
 * This class represents the base IPv6 Prefix.
 */
class prefix_v6 {
	ODTONE_UNDEFINED_BOOL;

public:
	typedef address_v6::bytes_type bytes_type;

public:
	/**
	 * Get the IPv6 Prefix from a string.
	 *
	 * @param str The input string.
	 * @return The extracted IPv6 Prefix.
	 */
	static prefix_v6 from_string(const std::string& str);

public:
	/**
	 * Construct an empty IPv6 Prefix.
	 */
	prefix_v6();

	/**
	 * Construct an IPv6 Prefix.
	 *
	 * @param addr The IPv6 Prefix raw bytes.
	 * @param length The IPv6 Prefix byte length.
	 */
	prefix_v6(const bytes_type& addr, uint length);

	/**
	 * Construct an IPv6 Prefix.
	 *
	 * @param addr The IPv6 Prefix.
	 * @param length The IPv6 Prefix byte length.
	 */
	prefix_v6(const address_v6& addr, uint length);

	/**
	 * Get the IPv6 Prefix raw bytes.
	 *
	 * @return The IPv6 Prefix raw bytes.
	 */
	const bytes_type& bytes() const
	{
		return _prefix;
	}

	/**
	 * Get the IPv6 Prefix length.
	 *
	 * @return The IPv6 Prefix length.
	 */
	uint length() const
	{
		return _length;
	}

	operator undefined_bool() const
	{
		return _length ? ODTONE_UNDEFINED_BOOL_TRUE
		               : ODTONE_UNDEFINED_BOOL_FALSE;
	}

	bool operator!() const
	{
		return !_length;
	}

	friend bool operator!=(const prefix_v6& rhr, const prefix_v6& lhr);
	friend bool operator<(const prefix_v6& rhr, const prefix_v6& lhr);
	friend bool operator<=(const prefix_v6& rhr, const prefix_v6& lhr);
	friend bool operator==(const prefix_v6& rhr, const prefix_v6& lhr);
	friend bool operator>(const prefix_v6& rhr, const prefix_v6& lhr);
	friend bool operator>=(const prefix_v6& rhr, const prefix_v6& lhr);

	/**
	 * IPv6 Prefix output.
	 *
	 * @param out ostream.
	 * @param lhr The IPv6 Prefix.
	 * @return ostream reference.
	 */
	friend std::ostream& operator<<(std::ostream& out, const prefix_v6& lhr);

	/**
	 * Check if the IPv6 Prefix is equal to another IPv6 Prefix.
	 *
	 * @param addr The IPv6 Prefix to compare with.
	 * @return True if they are equal or false otherwise.
	 */
	bool match(const address_v6& addr) const;

private:
	uchar      _length;	/**< IPv6 Prefix length.	*/
	bytes_type _prefix;	/**< IPv6 Prefix raw bytes.	*/
};

inline bool operator!=(const prefix_v6& rhr, const prefix_v6& lhr)
{
	return (rhr._length != lhr._length) && (rhr._prefix != lhr._prefix);
}

inline bool operator<(const prefix_v6& rhr, const prefix_v6& lhr)
{
	return (rhr._length < lhr._length)
	       | ((rhr._length == lhr._length) && (rhr._prefix < lhr._prefix));
}

inline bool operator<=(const prefix_v6& rhr, const prefix_v6& lhr)
{
	return (rhr._length < lhr._length)
	       | ((rhr._length == lhr._length) && (rhr._prefix <= lhr._prefix));
}

inline bool operator==(const prefix_v6& rhr, const prefix_v6& lhr)
{
	return (rhr._length == lhr._length) && (rhr._prefix == lhr._prefix);
}

inline bool operator>(const prefix_v6& rhr, const prefix_v6& lhr)
{
	return (rhr._length > lhr._length)
	       | ((rhr._length == lhr._length) && (rhr._prefix > lhr._prefix));
}

inline bool operator>=(const prefix_v6& rhr, const prefix_v6& lhr)
{
	return (rhr._length > lhr._length)
	       | ((rhr._length == lhr._length) && (rhr._prefix >= lhr._prefix));
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace net */ } /* namespace ip */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_NET_IP_PREFIX__HPP_ */
