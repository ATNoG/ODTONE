//=============================================================================
// Brief   : IPv6 Options
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

#ifndef ODTONE_IP_ICMP_OPTIONS__HPP_
#define ODTONE_IP_ICMP_OPTIONS__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/net/ip/options.hpp>
#include <odtone/net/ip/address.hpp>
#include <odtone/net/ip/prefix.hpp>
#include <odtone/net/link/address_mac.hpp>
#include <boost/array.hpp>
#include <algorithm>
#include <utility>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace net { namespace ip {

///////////////////////////////////////////////////////////////////////////////
template<uint8 TypeValue>
class opt_link_layer : public option {
	typedef opt_link_layer<TypeValue> self_type;

public:
	static const size_t static_size = 8;
	static const uint8  type_value  = TypeValue;

	static self_type* cast(option* opt)
	{
		return option::cast<self_type>(opt);
	}

public:
	opt_link_layer()
		: option(type_value, static_size)
	{
		_mac.fill(0);
	}

	opt_link_layer& operator=(const link::address_mac& mac)
	{
		_mac = mac.to_bytes();
		return *this;
	}

	link::address_mac to_mac() const
	{
		BOOST_ASSERT(option::size(this) == static_size);
		return link::address_mac(_mac);
	}

private:
	link::address_mac::bytes_type _mac;
};

typedef opt_link_layer<1> opt_source_link_layer;
typedef opt_link_layer<2> opt_target_link_layer;

///////////////////////////////////////////////////////////////////////////////
class opt_prefix_info : public option {
public:
	typedef prefix_v6::bytes_type bytes_type;

	static const uint8  type_value  = 3;
	static const size_t static_size = 16 + 16;

public:
	opt_prefix_info()
		: option(type_value, static_size),
		_plength(0),_flags(0), _valid_lifetime(0),
		_prefered_lifetime(0), _reserved(0)
	{
		_prefix.fill(0);
	}

	prefix_v6 prefix() const  { return prefix_v6(_prefix, _plength); }
	uint8     plength() const { return _plength; }
	bool      L() const       { return _flags & 0x80; }
	bool      A() const       { return _flags & 0x40; }

	void valid_lifetime(uint32 val)    { _valid_lifetime = htonl(val); }
	void prefered_lifetime(uint32 val) { _prefered_lifetime = htonl(val); }

	void prefix(const prefix_v6& val)
	{
		_plength = val.length();
		_prefix = val.bytes();
	}

	void L(bool val)
	{
		if (val)
			_flags |= 0x80;
		else
			_flags &= ~(0x80);
	}

	void A(bool val)
	{
		if (val)
			_flags |= 0x40;
		else
			_flags &= ~(0x40);
	}

private:
	uint8      _plength;
	uint8      _flags;
	uint32     _valid_lifetime;
	uint32     _prefered_lifetime;
	uint32     _reserved;
	bytes_type _prefix;
};

///////////////////////////////////////////////////////////////////////////////
class opt_mtu : public option {
public:
	static const uint8  type_value  = 5;
	static const size_t static_size = 8;

public:
	opt_mtu()
		: option(type_value, static_size), _reserved(0)
	{ }

	void   set(uint32 val) { _mtu = htonl(val); }
	uint32 get() const     { return ntohl(_mtu); }

public:
	uint16 _reserved;
	uint32 _mtu;
};

///////////////////////////////////////////////////////////////////////////////
class opt_rdns : public option { //RFC 5006 (experimental)
public:
	typedef address_v6::bytes_type bytes_type;

	static const uint8  type_value  = 25;
	static const size_t static_size = 8 + 16;

public:
	opt_rdns(uint address_count = 1)
		: option(type_value, static_size + 16 * address_count),
		  reserved(0), lifetime(0)
	{
		BOOST_ASSERT(address_count != 0);
	}

	uint address_count() const { return (option::size(this) - static_size) / 16; }

public:
	uint16     reserved;
	uint32     lifetime;
	bytes_type addresses[1];
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace ip */ } /* namespace net */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_IP_ICMP_OPTIONS__HPP_ */
