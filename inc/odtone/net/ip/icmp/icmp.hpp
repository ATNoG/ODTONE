//=============================================================================
// Brief   : IPv6 ICMP Data Structures
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

#ifndef ODTONE_NET_IP_ICMP__HPP_
#define ODTONE_NET_IP_ICMP__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/net/ip/address.hpp>
#include <boost/asio/ip/icmp.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <netinet/icmp6.h>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace net { namespace ip {

///////////////////////////////////////////////////////////////////////////////
struct icmp {
	class header;
	class router_solicitation;
	class router_advertisement;
	class neighbor_solicitation;
	class neighbor_advertisement;
	class filter;
};

///////////////////////////////////////////////////////////////////////////////
class icmp::header {
public:
	template<class T>
	static T* cast(void* buffer, size_t length)
	{
		ODTONE_STATIC_ASSERT((boost::is_base_of<header, T>::value), "T must be a base of odtone::net::ip::icmp::header");
		header* hdr = static_cast<header*>(buffer);

		if (length >= sizeof(T) && hdr->type() == T::type_value)
			return static_cast<T*>(hdr);

		return nullptr;
	}

public:
	header(uint8 type, uint8 code)
		: _type(type), _code(code), _checksum(0)
	{ }

	uint8 type() const { return _type; }
	uint8 code() const { return _code; }

	void checksum(uint16 csum) { _checksum = csum; }

protected:
	uint8  _type;
	uint8  _code;
	uint16 _checksum;
};

///////////////////////////////////////////////////////////////////////////////
class icmp::router_solicitation : public icmp::header {
public:
	static const uint8 type_value = 133;
	static const uint8 code_value = 0;

public:
	router_solicitation()
		: header(type_value, code_value), _reserved(0)
	{ }

private:
	uint32 _reserved;
};

///////////////////////////////////////////////////////////////////////////////
class icmp::router_advertisement : public icmp::header {
public:
	static const uint8 type_value = 134;
	static const uint8 code_value = 0;

public:
	router_advertisement()
		: header(type_value, code_value), _current_hop_limit(0),
		_flags(0), _lifetime(0), _reachable_time(0), _retrans_timer(0)
	{ }

	uint8  current_hop_limit() const { return _current_hop_limit; }
	bool   M() const                 { return _flags & 0x80; }
	bool   O() const                 { return _flags & 0x40; }
	uint16 lifetime() const          { return ntohs(_lifetime); }
	uint32 reachable_time() const    { return ntohl(_reachable_time); }
	uint32 retrans_timer() const     { return ntohl(_retrans_timer); }

	void current_hop_limit(uint8 val) { _current_hop_limit = val; }

	void M(bool val)
    {
		if (val)
			_flags |= 0x80;
		else
			_flags &= ~(0x80);
	}

	void O(bool val)
	{
		if (val)
			_flags |= 0x40;
		else
			_flags &= ~(0x40);
	}

	void lifetime(uint16 val)       { _lifetime = htons(val); }
	void reachable_time(uint32 val) { _reachable_time = htonl(val); }
	void retrans_timer(uint32 val)  { _retrans_timer = htonl(val); }

private:
	uint8  _current_hop_limit;
	uint8  _flags;
	uint16 _lifetime;
	uint32 _reachable_time;
	uint32 _retrans_timer;
};

///////////////////////////////////////////////////////////////////////////////
class icmp::neighbor_solicitation : public icmp::header {
public:
	static const uint8 type_value = 135;
	static const uint8 code_value = 0;

public:
	neighbor_solicitation()
		: header(type_value, code_value), _reserved(0)
	{
		_target_addr.fill(0);
	}

	void target(const address_v6::bytes_type& addr) { _target_addr = addr; }

	const address_v6::bytes_type& target() const { return _target_addr; }

private:
	uint32                 _reserved;
	address_v6::bytes_type _target_addr;
};

///////////////////////////////////////////////////////////////////////////////
class icmp::neighbor_advertisement : public icmp::header {
public:
	static const uint8 type_value = 136;
	static const uint8 code_value = 0;

public:
	neighbor_advertisement()
		: header(type_value, code_value), _flags(0), _reserved1(0),
		_reserved2(0)
	{
		_target_addr.fill(0);
	}

	void target(const address_v6::bytes_type& addr) { _target_addr = addr; }
	bool R() const                                  { return _flags & 0x80; }
	bool S() const                                  { return _flags & 0x40; }
	bool O() const                                  { return _flags & 0x20; }

	const address_v6::bytes_type& target() const { return _target_addr; }

	void R(bool val)
    {
		if (val)
			_flags |= 0x80;
		else
			_flags &= ~(0x80);
	}

	void S(bool val)
	{
		if (val)
			_flags |= 0x40;
		else
			_flags &= ~(0x40);
	}

	void O(bool val)
	{
		if (val)
			_flags |= 0x20;
		else
			_flags &= ~(0x20);
	}

private:
	uint8                  _flags;
	uint8                  _reserved1;
	uint16                 _reserved2;
	address_v6::bytes_type _target_addr;
};

///////////////////////////////////////////////////////////////////////////////
class icmp::filter {
public:
	filter(bool block)
	{
		if (block) {
			ICMP6_FILTER_SETBLOCKALL(&_filter);
		} else {
			ICMP6_FILTER_SETPASSALL(&_filter);
		}
	}

	filter(bool block, uint except_value_type)
	{
		if (block) {
			ICMP6_FILTER_SETBLOCKALL(&_filter);
			ICMP6_FILTER_SETPASS(except_value_type, &_filter);
		} else {
			ICMP6_FILTER_SETPASSALL(&_filter);
			ICMP6_FILTER_SETBLOCK(except_value_type, &_filter);
		}
	}

	void pass()
	{
		ICMP6_FILTER_SETPASSALL(&_filter);
	}

	void pass(uint type_value)
	{
		ICMP6_FILTER_SETPASS(type_value, &_filter);
	}

	void block()
	{
		ICMP6_FILTER_SETBLOCKALL(&_filter);
	}

	void block(uint type_value)
	{
		ICMP6_FILTER_SETBLOCK(type_value, &_filter);
	}

	int level(const boost::asio::ip::icmp&) const        { return IPPROTO_ICMPV6; }
	int name(const boost::asio::ip::icmp&) const         { return ICMP6_FILTER; }
	const void* data(const boost::asio::ip::icmp&) const { return &_filter; }
	size_t size(const boost::asio::ip::icmp&) const      { return sizeof(_filter); }

private:
	::icmp6_filter _filter;
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace ip */ } /* namespace net */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_NET_IP_ICMP__HPP_ */
