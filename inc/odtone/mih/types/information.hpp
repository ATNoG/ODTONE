//=============================================================================
// Brief   : MIH Information Types
// Authors : Bruno Santos <bsantos@av.it.pt>
//           Simao Reis   <sreis@av.it.pt>
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

#ifndef ODTONE_MIH_TYPES_INFORMATION__HPP_
#define ODTONE_MIH_TYPES_INFORMATION__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/mih/types/base.hpp>
#include <odtone/mih/types/link.hpp>
#include <odtone/mih/types/ipconfig.hpp>
#include <boost/variant/get.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
typedef octet_string	net_aux_id;
typedef octet_string	network_id;
typedef uint8			band_class;
typedef uint16			bandwidth;
typedef uint16			base_id;
typedef uint16			cntry_code;
typedef sint64			du_ctr_freq;
typedef sint8			eirp;
typedef sint8			init_code;
typedef sint8			ho_code;
typedef sint16			fq_code_num;
typedef sint16			pilot_pn;
typedef sint16			freq_id;

typedef bitmap<256, uint8>		down_bp;
typedef bitmap<256, uint8>		up_bp;

///////////////////////////////////////////////////////////////////////////////
struct cost_curr {
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
          ar & val[0];
          ar & val[1];
          ar & val[2];
	}


	uint8 val[3];
};

///////////////////////////////////////////////////////////////////////////////
enum cost_unit
	{
		second = 0,
		minute,
		hours,
		day,
		week,
		month,
		year,
		free,
		flat_rate
	};

///////////////////////////////////////////////////////////////////////////////
struct cost_value {
	uint32 integer;
	uint16 fraction;

	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & integer;
		ar & fraction;
	}
};

///////////////////////////////////////////////////////////////////////////////
struct cost {
	cost_unit	unit;
	cost_value	value;
	cost_curr	curr;


	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & (uint8) unit;
		ar & value;
		ar & curr;
	}
};

///////////////////////////////////////////////////////////////////////////////
typedef uint32 data_rate;

///////////////////////////////////////////////////////////////////////////////
struct regu_domain {
	cntry_code	country_code;
	uint8		regulatory_class;

	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & country_code;
		ar & regulatory_class;
	}
};

///////////////////////////////////////////////////////////////////////////////
typedef std::vector<uint32> freq_bands;

///////////////////////////////////////////////////////////////////////////////
struct ch_range {
	uint32 low;
	uint32 high;


	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & low;
		ar & high;
	}
};

///////////////////////////////////////////////////////////////////////////////
struct gap {
	uint8 ttg[2];
	uint8 rtg;


	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & ttg[0];
		ar & ttg[1];
		ar & rtg;
	}
};

///////////////////////////////////////////////////////////////////////////////
struct burst_prof {
	down_bp 	downbp;
	up_bp		upbp;


	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & downbp;
		ar & upbp;
	}
};


///////////////////////////////////////////////////////////////////////////////
struct cdma_codes {
	init_code	initcode;
	ho_code		hocode;


	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & initcode;
		ar & hocode;
	}
};

///////////////////////////////////////////////////////////////////////////////
struct dcd_udc {
	base_id		baseid;
	bandwidth	bandwidth_;
	du_ctr_freq ductrfreq;
	eirp		eirp_;
	gap			gap_;
	burst_prof	burstprof;
	cdma_codes	cdmacodes;


	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & baseid;
		ar & bandwidth_;
		ar & ductrfreq;
		ar & eirp_;
		ar & gap_;
		ar & burstprof;
		ar & cdmacodes;
	}
};

///////////////////////////////////////////////////////////////////////////////
struct sib {
	cell_id		cellid;
	fq_code_num fqcodenum;


	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & cellid;
		ar & fqcodenum;
	}
};

///////////////////////////////////////////////////////////////////////////////
struct sys_params {
	base_id		baseid;
	pilot_pn	pilotpn;
	freq_id		freqid;
	band_class	bandclass;


	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & baseid;
		ar & pilotpn;
		ar & freqid;
		ar & bandclass;
	}
};

///////////////////////////////////////////////////////////////////////////////
struct parameters {
	dcd_udc		dcdudc;
	sib			sib_;
	sys_params	params;


	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & dcdudc ;
		ar & sib_;
		ar & params;
	}
};

///////////////////////////////////////////////////////////////////////////////
enum netsubtype_enum {
	netsubtype_eth10   = 0,
	netsubtype_eth100  = 1,
	netsubtype_eth1000 = 2,

	netsubtype_iee80211_2_4GHz  = 0,
	netsubtype_iee80211_5GHz    = 1,
	netsubtype_iee80211_4_9GHz  = 2,
	netsubtype_iee80211_3_65GHz = 3,
	netsubtype_iee80211_316THz  = 4,

	netsubtype_umts_rel99      = 0,
	netsubtype_umts_rel4       = 1,
	netsubtype_umts_rel5_hsdpa = 2,
	netsubtype_umts_rel6_hsupa = 3,
	netsubtype_umts_rel7_mimo  = 4,
	netsubtype_umts_rel8       = 5,

	netsubtype_cdma2000_hrpd_rev0 = 0,
	netsubtype_cdma2000_hrpd_revA = 1,
	netsubtype_cdma2000_hrpd_revB = 2,
	netsubtype_cdma2000_hrpd_revC = 3,
};

typedef bitmap<64, netsubtype_enum> netsubtype;

///////////////////////////////////////////////////////////////////////////////
struct network_type {
	boost::variant<null, link_type>    link;
	boost::variant<null, netsubtype>   subtype;
	boost::variant<null, octet_string> typeext;


	network_type() : link(null()), subtype(null()), typeext(null())
	{ }

	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
          ar & link;
          ar & subtype;
          ar & typeext;
	}

	friend std::ostream& operator<<(std::ostream& os, const network_type& nt)
	{
		os << "\nlink: " << nt.link;
		if (nt.subtype.which() == 1)
			os << "\nsubtype: " << reinterpret_cast<uint64&>(boost::get<netsubtype&>(nt.subtype));
		os << "\ntypeext: " << nt.typeext;

		return os;
	}
};


///////////////////////////////////////////////////////////////////////////////
struct system_info {
	network_type						nettype;
	link_addr							linkaddr;
	boost::variant<null, parameters>	params;


	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & nettype;
		ar & linkaddr;
		ar & params;
	}
};

///////////////////////////////////////////////////////////////////////////////
typedef octet_string op_name;
typedef octet_string sp_id;

enum op_namespace
	{
		gsm_umts = 0,
		cdma,
		realm,
		itu_t_tsb,
		general
	};

///////////////////////////////////////////////////////////////////////////////
struct operator_id {
	op_name				opname;
	op_namespace		opnamespace;

	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & opname;
		ar & opnamespace;
	}
};

typedef std::vector<operator_id> roaming_ptns;

///////////////////////////////////////////////////////////////////////////////
enum supported_lcp
	{
		lcp_null = 0,
		lldp = 1,
		lbyr_with_lldp = 2,
		lldp_med = 11,
		lbyr_with_lld_med = 12,
		u_tdoa = 21,
		d_tdoa = 22,
		dhcp = 31,
		lbyr_with_dhcp = 32,
		oma_supl = 41,
		ieee_802_11 = 42,
		lbyr_with_ieee_802_11 = 43,
		held = 50,
		lbyr_with_held = 51
	};

///////////////////////////////////////////////////////////////////////////////
typedef boost::variant<ip4_addr, ip6_addr, fqdn> proxy_addr;

///////////////////////////////////////////////////////////////////////////////
struct net_type_addr {
	network_type nettype;
	link_addr    addr;


	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & nettype;
		ar & addr;
	}

	friend std::ostream& operator<<(std::ostream& os, const net_type_addr& nta)
	{
		os << "\nnettype: " << nta.nettype;
		os << "\naddr: " << nta.addr;

		return os;
	}
};

typedef std::vector<net_type_addr> net_type_addr_list;

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_TYPES_INFORMATION__HPP_ */
