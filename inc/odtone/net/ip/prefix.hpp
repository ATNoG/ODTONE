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

#ifndef ODTONE_NET_IP_PREFIX__HPP_
#define ODTONE_NET_IP_PREFIX__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/net/ip/address.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace net { namespace ip {

///////////////////////////////////////////////////////////////////////////////
class prefix_v6 {
	ODTONE_UNDEFINED_BOOL;

public:
	typedef address_v6::bytes_type bytes_type;

public:
	static prefix_v6 from_string(const std::string& str);

public:
	prefix_v6();
	prefix_v6(const bytes_type& addr, uint length);
	prefix_v6(const address_v6& addr, uint length);


	const bytes_type& bytes() const  { return _prefix; }
	uint              length() const { return _length; }

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
	friend std::ostream& operator<<(std::ostream& out, const prefix_v6& lhr);

	bool match(const address_v6& addr) const;

private:
	uchar      _length;
	bytes_type _prefix;
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
