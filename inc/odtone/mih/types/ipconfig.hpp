//=============================================================================
// Brief   : MIH IP Configuration Types
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
 * IP_CFG_METHODS data type enumeration.
 */
enum ip_cfg_methods_enum {
	ip_cfg_ipv4_static = 0,		/**< IPv4 static configuration.						*/
	ip_cfg_ipv4_dynamic = 1,	/**< IPv4 dynamic configuration (DHCPv4).			*/
	ip_cfg_ipv4_mobile_fa = 2,	/**< Mobile IPv4 with FA-CoA.						*/
	ip_cfg_ipv4_mobile = 3,		/**< Mobile IPv4 without FA (Co-located CoA).		*/

	ip_cfg_ipv6_stateless = 11,	/**< IPv6 stateless address configuration.			*/
	ip_cfg_ipv6_stateful = 12,	/**< IPv6 stateful address configuration (DHCPv6).	*/
	ip_cfg_ipv6_manual = 13,	/**< IPv6 manual configuration.						*/
};

/**
 * IP_CFG_METHODS data type.
 */
typedef bitmap<32, ip_cfg_methods_enum> ip_cfg_methods;

///////////////////////////////////////////////////////////////////////////////
/**
 * IP_MOB_MGMT data type enumeration.
 */
enum ip_mob_mgmt_enum {
	ip_mob_ipv4 = 0,						/**< Mobile IPv4				*/
	ip_mob_ipv4_regional_registration = 1,	/**< Mobile IPv4 Regional Registration*/
	ip_mob_ipv6 = 2,						/**< Mobile IPv6				*/
	ip_mob_hierarchical_ipv6 = 3,			/**< Hiearchical Mobile IPv6	*/
	ip_mob_low_latency_handoffs	= 4,		/**< Low Latency Handoffs 		*/
	ip_mob_ipv6_fast_handovers = 5,			/**< Mobile IPv6 Fast Handovers	*/
	ip_mob_IKEv2 = 6,						/**< IKEv2 Mobility and Multihoming Protocol*/
};

/**
 * IP_MOB_MGMT data type.
 */
typedef bitmap<16, ip_mob_mgmt_enum> ip_mob_mgmt;

///////////////////////////////////////////////////////////////////////////////
/**
 * IP4_ADDR data type.
 */
struct ip4_addr
{
	uint8 addr[4];	/**< IPv4 byte values */

	/**
	 * Serialize/deserialize the IP4_ADDR data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
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
 * IP6_ADDR data type.
 */
struct ip6_addr
{
	uint8 addr[16];	/**< IPv6 byte values */

	/**
	 * Serialize/deserialize the IP6_ADDR data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
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
 * FQDN data type.
 */
typedef octet_string fqdn;

///////////////////////////////////////////////////////////////////////////////
/**
 * IP_CONFIG data type.
 */
struct ip_config
{
	ip_cfg_methods					ipcfgmethods;	/**< IP configuration methods 			*/
	boost::variant<null, dhcp_serv>	dhcpserv;		/**< DHCP IP address 					*/
	boost::variant<null, fn_agent>	fnagent;		/**< Foreign Agent IP Address 			*/
	boost::variant<null, acc_rtr>	accrtr;			/**< Candidate access router IP address.*/

	/**
	 * Serialize/deserialize the IP_CONFIG data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
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
 * IP_PREFIX_LEN data type.
 */
typedef uint8 ip_prefix_len;

///////////////////////////////////////////////////////////////////////////////
/**
 * IP_RENEWAL_FLAG data type.
 */
typedef bool ip_renewal_flag;

///////////////////////////////////////////////////////////////////////////////
/**
 * IP_SUBNET_INFO data type.
 */
struct ip_subnet_info
{
	ip_prefix_len	ipprefixlen;	/**< Network prefix IP Address lenght	*/
	ip_addr			ipaddr;			/**< Network prefix IP address 			*/

	/**
	 * Serialize/deserialize the IP_SUBNET_INFO data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
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
