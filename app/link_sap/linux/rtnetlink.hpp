//=============================================================================
// Brief   : RTNetlink
// Authors : Bruno Santos <bsantos@av.it.pt>
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

#ifndef LINK_SAP_LINUX_RTNETLINK__HPP
#define LINK_SAP_LINUX_RTNETLINK__HPP

///////////////////////////////////////////////////////////////////////////////
//#include "../base.hpp"
#include "netlink.hpp"
#include <ostream>

///////////////////////////////////////////////////////////////////////////////
class rtnetlink : public netlink {
public:
	template<class T>
	class attr {
		struct safe_bool_t {
			void true_() {}
		};
		typedef void (safe_bool_t::*safe_bool)();

	public:
		attr() : _data(nullptr), _len(0)
		{ }
		attr(const void* data, size_t len) : _data((const T*) data), _len(len)
		{ }

		const T* get() const  { return _data; }
		size_t   size() const { return _len; }

		operator safe_bool() const { return _data ? &safe_bool_t::true_ : 0; }
		bool operator!() const     { return !_data; }

	private:
		const T* _data;
		size_t   _len;
	};

	class if_link : data {
	public:
		enum type {
			ethernet   = 1,
			ieee802_11 = 801,
		};

		enum flags {
			up             = 0x00001,
			broadcast      = 0x00002,
			debug          = 0x00004,
			loopback       = 0x00008,
			point_to_point = 0x00010,
			no_trailers    = 0x00020,
			running        = 0x00040,
			no_arp         = 0x00080,
			promiscuous    = 0x00100,
			all_multicast  = 0x00200,
			master         = 0x00400,
			slave          = 0x00800,
			multicast      = 0x01000,
			portsel        = 0x02000,
			automedia      = 0x04000,
			dynamic        = 0x08000,
			lower_up       = 0x10000,
			dormant        = 0x20000,
			echo           = 0x40000,
		};

		static inline bool is(const message& msg)
		{
			odtone::uint m = msg.type();

			return m >= 16 && m <= 19;
		}

		if_link();
		if_link(message& msg);

		if_link& operator=(message& msg);

		odtone::ushort type() const  { return _type; }
		odtone::sint   index() const { return _index; }
		odtone::uint   flags() const { return _flags; }

		bool has_address() const    { return _address; }
		bool has_bcast_addr() const { return _bcast_addr; }
		bool has_name() const       { return _name; }
		bool has_mtu() const        { return _mtu; }
		bool has_lnk_type() const   { return _link_type; }
		bool has_qdisc() const      { return _qdisc; }

		const attr<void>& address() const    { return _address; }
		const attr<void>& bcast_addr() const { return _bcast_addr; }
		std::string       name() const       { return std::string(_name.get(), _name.size()); }
		odtone::uint      mtu() const        { return *_mtu; }
		odtone::sint      link_type() const  { return *_link_type; }
		std::string       qdisc() const      { return std::string(_qdisc.get(), _qdisc.size()); }

	private:
		odtone::ushort _type;
		odtone::sint   _index;
		odtone::uint   _flags;
		attr<void>     _address;
		attr<void>     _bcast_addr;
		attr<char>     _name;
		odtone::uint*  _mtu;
		odtone::sint*  _link_type;
		attr<char>     _qdisc;
		void*          _stats;
		attr<void>     _wifi;
	};

	class if_addr : data {
	public:
		static inline bool is(const message& msg)
		{
			odtone::uint m = msg.type();

			return m >= 20 && m <= 23;
		}

		if_addr();
		if_addr(message& msg);

		if_addr& operator=(message& msg);

		odtone::uchar family() const    { return _family; }
		odtone::uchar prefixlen() const { return _prefixlen; }
		odtone::uchar flags() const     { return _flags; }
		odtone::uchar scope() const     { return _scope; }
		odtone::sint  index() const     { return _index; }

		bool has_address() const   { return _address; }
		bool has_local() const     { return _local; }
		bool has_label() const     { return _label; }
		bool has_broadcast() const { return _broadcast; }
		bool has_anycast() const   { return _anycast; }

		const attr<void>& address() const   { return _address; }
		const attr<void>& local() const     { return _local; }
		std::string       label() const     { return std::string(_label.get(), _label.size()); }
		const attr<void>& broadcast() const { return _broadcast; }
		const attr<void>& anycast() const   { return _anycast; }

	private:
		odtone::uchar  _family;
		odtone::uchar  _prefixlen;
		odtone::uchar  _flags;
		odtone::uchar  _scope;
		odtone::sint   _index;
		attr<void>     _address;
		attr<void>     _local;
		attr<char>     _label;
		attr<void>     _broadcast;
		attr<void>     _anycast;
	};

	enum subscription {
		link   = 1,
		notify = 2,
		neigh  = 4,
		tc     = 8,

		ipv4_ifaddr = 0x10,
		ipv4_mroute = 0x20,
		ipv4_route  = 0x40,
		ipv4_rule   = 0x80,

		ipv6_ifaddr = 0x100,
		ipv6_mroute = 0x200,
		ipv6_route  = 0x400,
		ipv6_ifinfo = 0x800,

		DECnet_ifaddr = 0x1000,
		DECnet_route  = 0x4000,

		ipv6_prefix = 0x20000,
	};

	rtnetlink(odtone::uint subscriptions = 0) : netlink(netlink::route, subscriptions)
	{ }

};

template<class T>
inline std::ostream& operator<<(std::ostream& os, const rtnetlink::attr<T>& a)
{
	const odtone::uchar* c = reinterpret_cast<const odtone::uchar*>(a.get());

	os << std::hex;
	for (size_t i = 0; i < a.size(); ++i)
		os << odtone::uint(c[i]);
	os << std::dec;

	return os;
}

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* LINK_SAP_LINUX_RTNETLINK__HPP */
