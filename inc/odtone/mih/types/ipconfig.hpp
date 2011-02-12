//=============================================================================
// Brief   : MIH IP Configuration Types
// Authors : Bruno Santos <bsantos@av.it.pt>
//------------------------------------------------------------------------------
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
//==============================================================================

#ifndef ODTONE_MIH_TYPES_IPCONFIG__HPP_
#define ODTONE_MIH_TYPES_IPCONFIG__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/mih/types/base.hpp>
#include <odtone/mih/types/address.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
/**
 * The enumeration of IP_CFG_METHODS data type.
 */
enum ip_cfg_methods_enum {
	ip_cfg_ipv4_static = 0,
	ip_cfg_ipv4_dynamic = 1,
	ip_cfg_ipv4_mobile_fa = 2,
	ip_cfg_ipv4_mobile = 3,

	ip_cfg_ipv6_stateless = 11,
	ip_cfg_ipv6_stateful = 12,
	ip_cfg_ipv6_manual = 13,
};

/**
 * Define IP_CFG_METHODS data type.
 */
typedef bitmap<32, ip_cfg_methods_enum> ip_cfg_methods;

///////////////////////////////////////////////////////////////////////////////
enum ip_mob_mgmt_enum {
	ip_mob_ipv4 = 0,
	ip_mob_ipv4_regional_registration = 1,
	ip_mob_ipv6 = 2,
	ip_mob_hierarchical_ipv6 = 3,
	ip_mob_low_latency_handoffs	= 4,
	ip_mob_ipv6_fast_handovers = 5,
	ip_mob_IKEv2 = 6,
};

/**
 * Define IP_MOB_MGMT data type.
 */
typedef bitmap<16, ip_mob_mgmt_enum> ip_mob_mgmt;

///////////////////////////////////////////////////////////////////////////////
/**
 * Define IP4_ADDR data type.
 */
struct ip4_addr
{
	uint8 addr[4];

	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & addr[0];
		ar & addr[1];
		ar & addr[2];
		ar & addr[3];
	}
};

///////////////////////////////////////////////////////////////////////////////
/**
 * Define IP6_ADDR data type.
 */
struct ip6_addr
{
	uint8 addr[16];

	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		uint i;
		for(i = 0; i < 16; i++)
			ar & addr[i];
	}
};

///////////////////////////////////////////////////////////////////////////////
/**
 * Define FQDN data type.
 */
typedef octet_string fqdn;

///////////////////////////////////////////////////////////////////////////////
/**
 * Define IP_CONFIG data type.
 */
struct ip_config
{
	ip_cfg_methods						ipcfgmethods;
	boost::variant<null, dhcp_serv>		dhcpserv;
	boost::variant<null, fn_agent>		fnagent;
	boost::variant<null, acc_rtr>		accrtr;

	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & ipcfgmethods;
		ar & dhcpserv;
		ar & fnagent;
		ar & accrtr;
	}
};

///////////////////////////////////////////////////////////////////////////////
/**
 * Define IP_PREFIX_LEN data type.
 */
typedef uint8 ip_prefix_len;

///////////////////////////////////////////////////////////////////////////////
/**
 * Define IP_RENEWAL_FLAG data type.
 */
typedef bool ip_renewal_flag;

///////////////////////////////////////////////////////////////////////////////
/**
 * Define IP_SUBNET_INFO data type.
 */
struct ip_subnet_info
{
	ip_prefix_len		ipprefixlen;
	ip_addr				ipaddr;

	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & ipprefixlen;
		ar & ipaddr;
	}
};


///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /*namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_TYPES_IPCONFIG__HPP_ */
