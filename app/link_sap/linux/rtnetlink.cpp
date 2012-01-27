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

///////////////////////////////////////////////////////////////////////////////
#include "rtnetlink.hpp"
#include <odtone/debug.hpp>
#include <iostream>

//#include <linux/wireless.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>

//
// Including linux headers is painfull
//
#ifndef __user
#define __user
#endif


///////////////////////////////////////////////////////////////////////////////
ODTONE_STATIC_ASSERT(rtnetlink::link          == RTMGRP_LINK, "");
ODTONE_STATIC_ASSERT(rtnetlink::notify        == RTMGRP_NOTIFY, "");
ODTONE_STATIC_ASSERT(rtnetlink::neigh         == RTMGRP_NEIGH, "");
ODTONE_STATIC_ASSERT(rtnetlink::tc            == RTMGRP_TC, "");
ODTONE_STATIC_ASSERT(rtnetlink::ipv4_ifaddr   == RTMGRP_IPV4_IFADDR, "");
ODTONE_STATIC_ASSERT(rtnetlink::ipv4_mroute   == RTMGRP_IPV4_MROUTE, "");
ODTONE_STATIC_ASSERT(rtnetlink::ipv4_route    == RTMGRP_IPV4_ROUTE, "");
ODTONE_STATIC_ASSERT(rtnetlink::ipv4_rule     == RTMGRP_IPV4_RULE, "");
ODTONE_STATIC_ASSERT(rtnetlink::ipv6_ifaddr   == RTMGRP_IPV6_IFADDR, "");
ODTONE_STATIC_ASSERT(rtnetlink::ipv6_mroute   == RTMGRP_IPV6_MROUTE, "");
ODTONE_STATIC_ASSERT(rtnetlink::ipv6_route    == RTMGRP_IPV6_ROUTE, "");
ODTONE_STATIC_ASSERT(rtnetlink::ipv6_ifinfo   == RTMGRP_IPV6_IFINFO, "");
ODTONE_STATIC_ASSERT(rtnetlink::DECnet_ifaddr == RTMGRP_DECnet_IFADDR, "");
ODTONE_STATIC_ASSERT(rtnetlink::DECnet_route  == RTMGRP_DECnet_ROUTE, "");
ODTONE_STATIC_ASSERT(rtnetlink::ipv6_prefix   == RTMGRP_IPV6_PREFIX, "");

ODTONE_STATIC_ASSERT(rtnetlink::if_link::ethernet   == ARPHRD_ETHER, "");
ODTONE_STATIC_ASSERT(rtnetlink::if_link::ieee802_11 == ARPHRD_IEEE80211, "");

ODTONE_STATIC_ASSERT((uint) rtnetlink::if_link::up             == IFF_UP, "");
ODTONE_STATIC_ASSERT((uint) rtnetlink::if_link::broadcast      == IFF_BROADCAST, "");
ODTONE_STATIC_ASSERT((uint) rtnetlink::if_link::debug          == IFF_DEBUG, "");
ODTONE_STATIC_ASSERT((uint) rtnetlink::if_link::loopback       == IFF_LOOPBACK, "");
ODTONE_STATIC_ASSERT((uint) rtnetlink::if_link::point_to_point == IFF_POINTOPOINT, "");
ODTONE_STATIC_ASSERT((uint) rtnetlink::if_link::no_trailers    == IFF_NOTRAILERS, "");
ODTONE_STATIC_ASSERT((uint) rtnetlink::if_link::running        == IFF_RUNNING, "");
ODTONE_STATIC_ASSERT((uint) rtnetlink::if_link::no_arp         == IFF_NOARP, "");
ODTONE_STATIC_ASSERT((uint) rtnetlink::if_link::promiscuous    == IFF_PROMISC, "");
ODTONE_STATIC_ASSERT((uint) rtnetlink::if_link::all_multicast  == IFF_ALLMULTI, "");
ODTONE_STATIC_ASSERT((uint) rtnetlink::if_link::master         == IFF_MASTER, "");
ODTONE_STATIC_ASSERT((uint) rtnetlink::if_link::slave          == IFF_SLAVE, "");
ODTONE_STATIC_ASSERT((uint) rtnetlink::if_link::multicast      == IFF_MULTICAST, "");
ODTONE_STATIC_ASSERT((uint) rtnetlink::if_link::portsel        == IFF_PORTSEL, "");
ODTONE_STATIC_ASSERT((uint) rtnetlink::if_link::automedia      == IFF_AUTOMEDIA, "");
ODTONE_STATIC_ASSERT((uint) rtnetlink::if_link::dynamic        == IFF_DYNAMIC, "");

///////////////////////////////////////////////////////////////////////////////
rtnetlink::if_link::if_link()
	: _type(0), _index(0), _flags(0), _mtu(nullptr), _link_type(nullptr),
	_stats(nullptr)
{
}

rtnetlink::if_link::if_link(message& msg)
	: _type(0), _index(0), _flags(0), _mtu(nullptr), _link_type(nullptr),
	_stats(nullptr)
{
	*this = msg;
}

rtnetlink::if_link& rtnetlink::if_link::operator=(message& msg)
{
	static_cast<data&>(*this) = msg;

	std::pair<const void*, size_t> pl = msg.payload();

	if (msg.type() < 16 || msg.type() > 19 || pl.second < sizeof(::ifinfomsg))
		throw "bad msg type";

	const ::ifinfomsg* ifi = reinterpret_cast<const ifinfomsg*>(pl.first);

	_type = ifi->ifi_type;
	_index = ifi->ifi_index;
	_flags = ifi->ifi_flags;

	const ::rtattr* rta = IFLA_RTA(ifi);
	size_t attrlen = IFLA_PAYLOAD(reinterpret_cast<const ::nlmsghdr*>(_msg->header()));

	for (; RTA_OK(rta, attrlen); rta = RTA_NEXT(rta, attrlen)) {
		switch (rta->rta_type) {
		case IFLA_ADDRESS:
			_address = attr<void>(RTA_DATA(rta), RTA_PAYLOAD(rta));
			break;

		case IFLA_BROADCAST:
			_bcast_addr = attr<void>(RTA_DATA(rta), RTA_PAYLOAD(rta));
			break;

		case IFLA_IFNAME:
			_name = attr<char>(RTA_DATA(rta), RTA_PAYLOAD(rta));
			break;

		case IFLA_MTU:
			ODTONE_ASSERT(sizeof(odtone::uint) == RTA_PAYLOAD(rta));
			_mtu = reinterpret_cast<odtone::uint*>(RTA_DATA(rta));
			break;

		case IFLA_LINK:
			ODTONE_ASSERT(sizeof(odtone::sint) == RTA_PAYLOAD(rta));
			_link_type = reinterpret_cast<odtone::sint*>(RTA_DATA(rta));
			break;

		case IFLA_QDISC:
			_qdisc = attr<char>(RTA_DATA(rta), RTA_PAYLOAD(rta));
			break;

		case IFLA_STATS:
			ODTONE_ASSERT(sizeof(::rtnl_link_stats) == RTA_PAYLOAD(rta));
			_stats = RTA_DATA(rta);
			break;

		case IFLA_WIRELESS:
			std::cout << "IFLA_WIRELESS(" << rta->rta_type << ", " << RTA_PAYLOAD(rta) << ")\n";
			// std::cout	<< "\tcmd: "
			// 			<< reinterpret_cast<iw_event*>(RTA_DATA(rta))->cmd
			// 			<< "  len: "
			// 			<< reinterpret_cast<iw_event*>(RTA_DATA(rta))->len
			// 			<< std::endl;

			_wifi = attr<void>(RTA_DATA(rta), RTA_PAYLOAD(rta));
			break;

		default:
			std::cout << "IFLA_UNSPEC(" << rta->rta_type << ", " << RTA_PAYLOAD(rta) << ")\n";
		}
	}

	return *this;
}

///////////////////////////////////////////////////////////////////////////////
rtnetlink::if_addr::if_addr()
	: _family(0), _prefixlen(0), _flags(0), _scope(0), _index(0)
{
}

rtnetlink::if_addr::if_addr(message& msg)
	: _family(0), _prefixlen(0), _flags(0), _scope(0), _index(0)
{
	*this = msg;
}

rtnetlink::if_addr& rtnetlink::if_addr::operator=(message& msg)
{
	static_cast<data&>(*this) = msg;

	std::pair<const void*, size_t> pl = msg.payload();

	if (msg.type() < 20 || msg.type() > 23 || pl.second < sizeof(::ifaddrmsg))
		throw "bad msg type";

	const ::ifaddrmsg* ifa = reinterpret_cast<const ifaddrmsg*>(pl.first);

	_family = ifa->ifa_family;
	_prefixlen = ifa->ifa_prefixlen;
	_scope = ifa->ifa_scope;
	_flags = ifa->ifa_flags;
	_index = ifa->ifa_index;

	const ::rtattr* rta = IFLA_RTA(ifa);
	size_t attrlen = IFLA_PAYLOAD(reinterpret_cast<const ::nlmsghdr*>(_msg->header()));

	for (; RTA_OK(rta, attrlen); rta = RTA_NEXT(rta, attrlen)) {
		switch (rta->rta_type) {
		case IFA_ADDRESS:
			_address = attr<void>(RTA_DATA(rta), RTA_PAYLOAD(rta));
			break;

		case IFA_LOCAL:
			_local = attr<void>(RTA_DATA(rta), RTA_PAYLOAD(rta));
			break;

		case IFA_LABEL:
			_label = attr<char>(RTA_DATA(rta), RTA_PAYLOAD(rta));
			break;

		case IFA_BROADCAST:
			_broadcast = attr<void>(RTA_DATA(rta), RTA_PAYLOAD(rta));
			break;

		case IFA_ANYCAST:
			_anycast = attr<void>(RTA_DATA(rta), RTA_PAYLOAD(rta));
			break;

		default:
			std::cout << "IFA_UNSPEC(" << rta->rta_type << ", " << RTA_PAYLOAD(rta) << ")\n";
		}
	}

	return *this;
}

// EOF ////////////////////////////////////////////////////////////////////////
