//=============================================================================
// Brief   : MIH IP Configuration Types
// Authors : Bruno Santos <bsantos@av.it.pt>
//
//
// Copyright (C) 2009 Universidade Aveiro - Instituto de Telecomunicacoes Polo Aveiro
//
// This file is part of ODTONE - Open Dot Twenty One.
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//=============================================================================

#ifndef ODTONE_MIH_TYPES_IPCONFIG__HPP_
#define ODTONE_MIH_TYPES_IPCONFIG__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/mih/types/base.hpp>
#include <odtone/mih/types/address.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
enum ip_cfg_methods_enum {
	ip_cfg_ipv4_static = 0,
	ip_cfg_ipv4_dynamic = 1,
	ip_cfg_ipv4_mobile_fa = 2,
	ip_cfg_ipv4_mobile = 3,

	ip_cfg_ipv6_stateless = 11,
	ip_cfg_ipv6_stateful = 12,
	ip_cfg_ipv6_manual = 13,
};

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

typedef bitmap<16, ip_mob_mgmt_enum> ip_mob_mgmt;

///////////////////////////////////////////////////////////////////////////////
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
typedef octet_string fqdn;

///////////////////////////////////////////////////////////////////////////////
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
typedef sint8 ip_prefix_len;

///////////////////////////////////////////////////////////////////////////////
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
