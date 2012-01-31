//=============================================================================
// Brief   : IPv6 ICMP Data Structures
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

#ifndef ODTONE_NET_IP_ICMP__HPP_
#define ODTONE_NET_IP_ICMP__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/net/ip/address.hpp>
#include <boost/asio/ip/icmp.hpp>
#include <boost/type_traits/is_base_of.hpp>

#ifndef _WIN32
	#include <netinet/icmp6.h>
#endif

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
/**
 * This class represents the header of an ICMP packet.
 */
class icmp::header {
public:
	/**
	 * Convert a byte buffer ICMP packet.
	 *
	 * @param data The byte buffer.
	 * @param len The size of the byte buffer.
	 * @return The pointer of the returning ICMP packet.
	 */
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
	/**
	 * Construct an ICMP packet header.
	 *
	 * @param type The ICMP packet header type.
	 * @param length The ICMP packet header code.
	 */
	header(uint8 type, uint8 code)
		: _type(type), _code(code), _checksum(0)
	{ }

	/**
	 * Get the ICMP packet header type.
	 *
	 * @return The ICMP packet header type.
	 */
	uint8 type() const
	{
		return _type;
	}

	/**
	 * Get the ICMP packet header code.
	 *
	 * @return The ICMP packet header code.
	 */
	uint8 code() const
	{
		return _code;
	}

	/**
	 * Set the ICMP packet checksum field.
	 *
	 * @param csum The ICMP packet checksum field.
	 */
	void checksum(uint16 csum)
	{
		_checksum = csum;
	}

protected:
	uint8  _type;		/**< ICMP packet header type.		*/
	uint8  _code;		/**< ICMP packet header code.		*/
	uint16 _checksum;	/**< ICMP packet checksum field.	*/
};

///////////////////////////////////////////////////////////////////////////////
/**
 * This class represents an ICMP Router Solicitation packet.
 */
class icmp::router_solicitation : public icmp::header {
public:
	static const uint8 type_value = 133;/**< ICMP Router Solicitation type.*/
	static const uint8 code_value = 0;	/**< ICMP Router Solicitation type.*/

public:
	/**
	 * Construct an empty ICMP Router Solicitation packet.
	 */
	router_solicitation()
		: header(type_value, code_value), _reserved(0)
	{ }

private:
	uint32 _reserved;	/**< Reserved.	*/
};

///////////////////////////////////////////////////////////////////////////////
/**
 * This class represents an ICMP Router Advertisement packet.
 */
class icmp::router_advertisement : public icmp::header {
public:
	static const uint8 type_value = 134;/**< ICMP Router Advertisement type.*/
	static const uint8 code_value = 0;	/**< ICMP Router Advertisement code.*/

public:
	/**
	 * Construct an empty ICMP Router Advertisement packet.
	 */
	router_advertisement()
		: header(type_value, code_value), _current_hop_limit(0),
		_flags(0), _lifetime(0), _reachable_time(0), _retrans_timer(0)
	{ }

	/**
	 * Get the Current Hop Limit field value.
	 *
	 * @return The Current Hop Limit field value.
	 */
	uint8 current_hop_limit() const
	{
		return _current_hop_limit;
	}

	/**
	 * Get the Managed Address Configuration flag value.
	 *
	 * @return The Managed Address Configuration flag value.
	 */
	bool M() const
	{
		return _flags & 0x80;
	}

	/**
	 * Get the Other Configuration flag value.
	 *
	 * @return The Other Configuration flag value.
	 */
	bool O() const
	{
		return _flags & 0x40;
	}

	/**
	 * Get the Lifetime field value.
	 *
	 * @return The Lifetime field value.
	 */
	uint16 lifetime() const
	{
		return ntohs(_lifetime);
	}

	/**
	 * Get the Reachable Time field value.
	 *
	 * @return The Reachable Time field value.
	 */
	uint32 reachable_time() const
	{
		return ntohl(_reachable_time);
	}

	/**
	 * Get the Retransmission Timer field value.
	 *
	 * @return The Retransmission Timer field value.
	 */
	uint32 retrans_timer() const
	{
		return ntohl(_retrans_timer);
	}

	/**
	 * Set the Current Hop Limit field value.
	 *
	 * @param val The Current Hop Limit field value.
	 */
	void current_hop_limit(uint8 val)
	{
		_current_hop_limit = val;
	}

	/**
	 * Set the Managed Address Configuration flag value.
	 *
	 * @param val The Managed Address Configuration flag value.
	 */
	void M(bool val)
    {
		if (val)
			_flags |= 0x80;
		else
			_flags &= ~(0x80);
	}

	/**
	 * Set the Other Configuration flag value.
	 *
	 * @param val The Other Configuration flag value.
	 */
	void O(bool val)
	{
		if (val)
			_flags |= 0x40;
		else
			_flags &= ~(0x40);
	}

	/**
	 * Set the Lifetime field value.
	 *
	 * @param val The Lifetime field value.
	 */
	void lifetime(uint16 val)
	{
		_lifetime = htons(val);
	}

	/**
	 * Set the Reachable Time field value.
	 *
	 * @param val The Reachable Time field value.
	 */
	void reachable_time(uint32 val)
	{
		_reachable_time = htonl(val);
	}

	/**
	 * Set the Retransmission Timer field value.
	 *
	 * @param val The Retransmission Timer field value.
	 */
	void retrans_timer(uint32 val)
	{
		_retrans_timer = htonl(val);
	}

private:
	uint8  _current_hop_limit;	/**< Current hop limit.		*/
	uint8  _flags;				/**< Flags.					*/
	uint16 _lifetime;			/**< Lifetime.				*/
	uint32 _reachable_time;		/**< Reachable time.		*/
	uint32 _retrans_timer;		/**< Retransmission timer.	*/
};

///////////////////////////////////////////////////////////////////////////////
/**
 * This class represents an ICMP Neighbor Solicitation packet.
 */
class icmp::neighbor_solicitation : public icmp::header {
public:
	static const uint8 type_value = 135;/**< ICMP Neighbor Solicitation type.*/
	static const uint8 code_value = 0;	/**< ICMP Neighbor Solicitation type.*/

public:
	/**
	 * Construct an empty ICMP Neighbor Solicitation packet.
	 */
	neighbor_solicitation()
		: header(type_value, code_value), _reserved(0)
	{
		_target_addr.fill(0);
	}

	/**
	 * Set the Target address field value.
	 *
	 * @param addr The Target Address field value.
	 */
	void target(const address_v6::bytes_type& addr)
	{
		_target_addr = addr;
	}

	/**
	 * Get the Target address field value.
	 *
	 * @return The Target Address field value.
	 */
	const address_v6::bytes_type& target() const
	{
		return _target_addr;
	}

private:
	uint32                 _reserved;		/**< Reserved.			*/
	address_v6::bytes_type _target_addr;	/**< Target address.	*/
};

///////////////////////////////////////////////////////////////////////////////
/**
 * This class represents an ICMP Neighbor Advertisement packet.
 */
class icmp::neighbor_advertisement : public icmp::header {
public:
	static const uint8 type_value = 136;/**< ICMP Neighbor Advertisement type.*/
	static const uint8 code_value = 0;	/**< ICMP Neighbor Advertisement type.*/

public:
	/**
	 * Construct an empty ICMP Neighbor Advertisement packet.
	 */
	neighbor_advertisement()
		: header(type_value, code_value), _flags(0), _reserved1(0),
		_reserved2(0)
	{
		_target_addr.fill(0);
	}

	/**
	 * Set the Target address field value.
	 *
	 * @param addr The Target Address field value.
	 */
	void target(const address_v6::bytes_type& addr)
	{
		_target_addr = addr;
	}

	/**
	 * Get the Router flag value.
	 *
	 * @return The Router flag value.
	 */
	bool R() const
	{
		return _flags & 0x80;
	}

	/**
	 * Get the Solicited flag value.
	 *
	 * @return The Solicited flag value.
	 */
	bool S() const
	{
		return _flags & 0x40;
	}

	/**
	 * Get the Override flag value.
	 *
	 * @return The Override flag value.
	 */
	bool O() const
	{
		return _flags & 0x20;
	}

	/**
	 * Get the Target address field value.
	 *
	 * @return The Target Address field value.
	 */
	const address_v6::bytes_type& target() const
	{
		return _target_addr;
	}

	/**
	 * Set the Router flag value.
	 *
	 * @param val The Router flag value.
	 */
	void R(bool val)
    {
		if (val)
			_flags |= 0x80;
		else
			_flags &= ~(0x80);
	}

	/**
	 * Set the Solicited flag value.
	 *
	 * @param val The Solicited flag value.
	 */
	void S(bool val)
	{
		if (val)
			_flags |= 0x40;
		else
			_flags &= ~(0x40);
	}

	/**
	 * Set the Override flag value.
	 *
	 * @param val The Override flag value.
	 */
	void O(bool val)
	{
		if (val)
			_flags |= 0x20;
		else
			_flags &= ~(0x20);
	}

private:
	uint8                  _flags;			/**< Flags.				*/
	uint8                  _reserved1;		/**< Reserved.			*/
	uint16                 _reserved2;		/**< Reserved.			*/
	address_v6::bytes_type _target_addr;	/**< Target address.	*/
};

///////////////////////////////////////////////////////////////////////////////
#ifndef _WIN32
/**
 * This class represents an ICMP filter.
 */
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
	::icmp6_filter _filter;	/**< Filter.	*/
};
#endif WIN32

///////////////////////////////////////////////////////////////////////////////
} /* namespace ip */ } /* namespace net */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_NET_IP_ICMP__HPP_ */
