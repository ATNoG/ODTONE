//=============================================================================
// Brief   : MIH Information Types
// Authors : Bruno Santos <bsantos@av.it.pt>
//           Simao Reis   <sreis@av.it.pt>
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
/**
 * Define NET_AUX_ID data type.
 */
typedef octet_string	net_aux_id;

/**
 * Define NETWORK_ID data type.
 */
typedef octet_string	network_id;

/**
 * Define BAND_CLASS data type.
 */
typedef uint8			band_class;

/**
 * Define BANDWIDTH data type.
 */
typedef uint16			bandwidth;

/**
 * Define BASE_ID data type.
 */
typedef uint16			base_id;

/**
 * Define CNTRY_CODE data type.
 */
typedef uint16			cntry_code;

/**
 * Define DU_CTR_FREQ data type.
 */
typedef sint64			du_ctr_freq;

/**
 * Define EIRP data type.
 */
typedef sint8			eirp;

/**
 * Define INIT_CODE data type.
 */
typedef sint8			init_code;

/**
 * Define HO_CODE data type.
 */
typedef sint8			ho_code;

/**
 * Define FQ_CODE_NUM data type.
 */
typedef sint16			fq_code_num;

/**
 * Define PILOT_PN data type.
 */
typedef sint16			pilot_pn;

/**
 * Define FREQ_ID data type.
 */
typedef sint16			freq_id;

/**
 * Define DOWN_BP data type.
 */
typedef bitmap<256, uint8>		down_bp;

/**
 * Define UP_BP data type.
 */
typedef bitmap<256, uint8>		up_bp;

///////////////////////////////////////////////////////////////////////////////
/**
 * Define COST_CURR data type.
 */
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
/**
 * The enumeration of COST_UNIT data type.
 */
enum cost_unit_enum {
	cost_unit_second = 0,
	cost_unit_minute = 1,
	cost_unit_hours = 2,
	cost_unit_day = 3,
	cost_unit_week = 4,
	cost_unit_month = 5,
	cost_unit_year = 6,
	cost_unit_free = 7,
	cost_unit_flat_rate = 8
};

/**
 * Define COST_UNIT data type.
 */
typedef enumeration<cost_unit_enum> cost_unit;

///////////////////////////////////////////////////////////////////////////////
/**
 * Define COST_VALUE data type.
 */
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
/**
 * Define COST data type.
 */
struct cost {
	cost_unit	unit;
	cost_value	value;
	cost_curr	curr;


	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & unit;
		ar & value;
		ar & curr;
	}
};

///////////////////////////////////////////////////////////////////////////////
/**
 * Define DATA_RATE data type.
 */
typedef uint32 data_rate;

///////////////////////////////////////////////////////////////////////////////
/**
 * Define REGU_DOMAIN data type.
 */
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
/**
 * Define FREQ_BANDS data type.
 */
typedef std::vector<uint32> freq_bands;

///////////////////////////////////////////////////////////////////////////////
/**
 * Define CH_RANGE data type.
 */
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
/**
 * Define GAP data type.
 */
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
/**
 * Define BURST_PROF data type.
 */
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
/**
 * Define CDMA_CODES data type.
 */
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
/**
 * Define DCD_UDC data type.
 */
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
/**
 * Define SIB data type.
 */
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
/**
 * Define SYS_PARAMS data type.
 */
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
/**
 * Define PARAMETERS data type.
 */
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

	netsubtype_iee80216_2_5GHz = 0,
	netsubtype_iee80216_3_5GHz = 1,
};

/**
 * Define SUBTYPE data type.
 */
typedef bitmap<64, netsubtype_enum> netsubtype;

///////////////////////////////////////////////////////////////////////////////
/**
 * Define TYPE_EXT data type.
 */
typedef octet_string type_ext;

///////////////////////////////////////////////////////////////////////////////
/**
 * Define NETWORK_TYPE data type.
 */
struct network_type {
	boost::variant<null, link_type>  link;
	boost::variant<null, netsubtype> subtype;
	boost::variant<null, type_ext>   typeext;


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
/**
 * Define SYSTEM_INFO data type.
 */
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
/**
 * Define OP_NAME data type.
 */
typedef octet_string op_name;

/**
 * Define SP_ID data type.
 */
typedef octet_string sp_id;

enum op_namespace_enum {
	op_namespace_gsm_umts = 0,
	op_namespace_cdma = 1,
	op_namespace_realm = 2,
	op_namespace_itu_t_tsb = 3,
	op_namespace_general = 4
};

/**
 * Define OP_NAMESPACE data type.
 */
typedef enumeration<op_namespace_enum> op_namespace;

///////////////////////////////////////////////////////////////////////////////
/**
 * Define OPERATOR_ID data type.
 */
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

/**
 * Define ROAMING_PTNS data type.
 */
typedef std::vector<operator_id> roaming_ptns;

///////////////////////////////////////////////////////////////////////////////
enum supported_lcp_enum {
	supported_lcp_null = 0,
	supported_lcp_lldp = 1,
	supported_lcp_lbyr_with_lldp = 2,
	supported_lcp_lldp_med = 11,
	supported_lcp_lbyr_with_lld_med = 12,
	supported_lcp_u_tdoa = 21,
	supported_lcp_d_tdoa = 22,
	supported_lcp_dhcp = 31,
	supported_lcp_lbyr_with_dhcp = 32,
	supported_lcp_oma_supl = 41,
	supported_lcp_ieee_802_11 = 42,
	supported_lcp_lbyr_with_ieee_802_11 = 43,
	supported_lcp_held = 51,
	supported_lcp_lbyr_with_held = 52
};

/**
 * Define SUPPORTED_LCP data type.
 */
typedef enumeration<supported_lcp_enum> supported_lcp;

///////////////////////////////////////////////////////////////////////////////
/**
 * Define PROXY_ADDR data type.
 */
typedef boost::variant<ip4_addr, ip6_addr, fqdn> proxy_addr;

///////////////////////////////////////////////////////////////////////////////
/**
 * Define NET_TYPE_ADDR data type.
 */
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

/**
 * Define LIST(NET_TYPE_ADDR) data type.
 */
typedef std::vector<net_type_addr> net_type_addr_list;

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_TYPES_INFORMATION__HPP_ */
