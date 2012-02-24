//=============================================================================
// Brief   : MIH Information Types
// Authors : Bruno Santos <bsantos@av.it.pt>
//           Simao Reis   <sreis@av.it.pt>
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

typedef octet_string	net_aux_id;		/**< NET_AUX_ID data type.	*/
typedef octet_string	network_id;		/**< NETWORK_ID data type.	*/
typedef uint8			band_class;		/**< BAND_CLASS data type.	*/
typedef uint16			bandwidth;		/**< BANDWIDTH data type.	*/
typedef uint16			base_id;		/**< BASE_ID data type.		*/
typedef uint16			cntry_code;		/**< CNTRY_CODE data type.	*/
typedef sint64			du_ctr_freq;	/**< DU_CTR_FREQ data type.	*/
typedef sint8			eirp;			/**< EIRP data type.		*/
typedef sint8			init_code;		/**< INIT_CODE data type.	*/
typedef sint8			ho_code;		/**< HO_CODE data type.		*/
typedef sint16			fq_code_num;	/**< FQ_CODE_NUM data type.	*/
typedef sint16			pilot_pn;		/**< PILOT_PN data type.	*/
typedef sint16			freq_id;		/**< FREQ_ID data type.		*/
typedef bitmap<256, uint8>	down_bp;	/**< DOWN_BP data type.		*/
typedef bitmap<256, uint8>	up_bp;		/**< UP_BP data type.		*/

///////////////////////////////////////////////////////////////////////////////
/**
 * COST_CURR data type.
 */
struct cost_curr {
	/**
	 * Serialize/deserialize the COST_CURR data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
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
 * COST_UNIT data type enumeration.
 */
enum cost_unit_enum {
	cost_unit_second = 0,	/**< Cost unit second		*/
	cost_unit_minute = 1,	/**< Cost unit minute		*/
	cost_unit_hours = 2,	/**< Cost unit hour			*/
	cost_unit_day = 3,		/**< Cost unit day			*/
	cost_unit_week = 4,		/**< Cost unit week			*/
	cost_unit_month = 5,	/**< Cost unit month		*/
	cost_unit_year = 6,		/**< Cost unit year			*/
	cost_unit_free = 7,		/**< Cost unit free			*/
	cost_unit_flat_rate = 8	/**< Cost unit flat rate	*/
};

/**
 * COST_UNIT data type.
 */
typedef enumeration<cost_unit_enum> cost_unit;

///////////////////////////////////////////////////////////////////////////////
/**
 * COST_VALUE data type.
 */
struct cost_value {
	uint32 integer;		/**< Cost value integer part	*/
	uint16 fraction;	/**< Cost value fraction part	*/

	/**
	 * Serialize/deserialize the COST_VALUE data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & integer;
		ar & fraction;
	}
};

///////////////////////////////////////////////////////////////////////////////
/**
 * COST data type.
 */
struct cost {
	cost_unit	unit;	/**< Cost unit		*/
	cost_value	value;	/**< Cost value		*/
	cost_curr	curr;	/**< Cost currency	*/

	/**
	 * Serialize/deserialize the COST data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & unit;
		ar & value;
		ar & curr;
	}
};

///////////////////////////////////////////////////////////////////////////////
typedef uint32 data_rate;	/**< DATA_RATE data type.	*/

///////////////////////////////////////////////////////////////////////////////
/**
 * REGU_DOMAIN data type.
 */
struct regu_domain {
	cntry_code	country_code;		/**< Country code		*/
	uint8		regulatory_class;	/**< Regulatory class	*/

	/**
	 * Serialize/deserialize the REGU_DOMAIN data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & country_code;
		ar & regulatory_class;
	}
};

///////////////////////////////////////////////////////////////////////////////
typedef std::vector<uint32> freq_bands;	/**< FREQ_BANDS data type.*/

///////////////////////////////////////////////////////////////////////////////
/**
 * CH_RANGE data type.
 */
struct ch_range {
	uint32 low;		/**< Channel low range	*/
	uint32 high;	/**< Channel high range */

	/**
	 * Serialize/deserialize the CH_RANGE data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & low;
		ar & high;
	}
};

///////////////////////////////////////////////////////////////////////////////
/**
 * GAP data type.
 */
struct gap {
	uint8 ttg[2];	/**< TTG - transmit/receive transition gap.	*/
	uint8 rtg;		/**< RTG - receive/transmit transition gap.	*/

	/**
	 * Serialize/deserialize the GAP data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
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
 * BURST_PROF data type.
 */
struct burst_prof {
	down_bp 	downbp;	/**< Downlink burst	*/
	up_bp		upbp;	/**< Uplink burst	*/

	/**
	 * Serialize/deserialize the BURST_PROF data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & downbp;
		ar & upbp;
	}
};


///////////////////////////////////////////////////////////////////////////////
/**
 * CDMA_CODES data type.
 */
struct cdma_codes {
	init_code	initcode;	/**< Initial ranging code	*/
	ho_code		hocode;		/**< Handover ranging code	*/

	/**
	 * Serialize/deserialize the CDMA_CODES data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & initcode;
		ar & hocode;
	}
};

///////////////////////////////////////////////////////////////////////////////
/**
 * DCD_UDC data type.
 */
struct dcd_udc {
	base_id		baseid;		/**< Base station identifier.					*/
	bandwidth	bandwidth_;	/**< Channel bandwidth in kb/s.					*/
	du_ctr_freq ductrfreq;	/**< Downlink/Uplink center frequency in kHz.	*/
	eirp		eirp_;		/**< BS effective isotropic radiated power level*/
	gap			gap_;		/**< GAP.										*/
	burst_prof	burstprof;	/**< Burst profile.								*/
	cdma_codes	cdmacodes;	/**< CDMA ranging codes.						*/

	/**
	 * Serialize/deserialize the DCD_UDC data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
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
 * SIB data type.
 */
struct sib {
	cell_id		cellid;		/**< Cell identifier.							*/
	fq_code_num fqcodenum;	/**< UMTS scrambling code, CDMA-2000 Walsh code.*/

	/**
	 * Serialize/deserialize the SIB data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & cellid;
		ar & fqcodenum;
	}
};

///////////////////////////////////////////////////////////////////////////////
/**
 * SYS_PARAMS data type.
 */
struct sys_params {
	base_id		baseid;		/**< Base station identifier.				*/
	pilot_pn	pilotpn;	/**< Pilot PN sequence offset index.		*/
	freq_id		freqid;		/**< Identifier of the carrier frequency.	*/
	band_class	bandclass;	/**< CDMA band class.						*/

	/**
	 * Serialize/deserialize the SYS_PARAMS data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
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
 * PARAMETERS data type.
 */
struct parameters {
	dcd_udc		dcdudc;	/**< Downlink channel descriptor and the
							 uplink channel descriptor.				*/
	sib			sib_;	/**< UMTS system information block.			*/
	sys_params	params;	/**< CDMA-2000 system parameters.			*/

	/**
	 * Serialize/deserialize the PARAMETERS data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & dcdudc ;
		ar & sib_;
		ar & params;
	}
};

///////////////////////////////////////////////////////////////////////////////
/**
 * SUBTYPE data type enumeration.
 */
enum netsubtype_enum {
	netsubtype_eth10   = 0,	/**< Ethernet - IEEE 802.3 - 10 Mb.		*/
	netsubtype_eth100  = 1,	/**< Ethernet - IEEE 802.3 - 100 Mb.	*/
	netsubtype_eth1000 = 2,	/**< Ethernet - IEEE 802.3 - 1000 Mb.	*/

	netsubtype_iee80211_2_4GHz  = 0,	/**< Wireless - IEEE 802.11 - 2.4GHz */
	netsubtype_iee80211_5GHz    = 1,	/**< Wireless - IEEE 802.11 - 5GHz	 */
	netsubtype_iee80211_4_9GHz  = 2,	/**< Wireless - IEEE 802.11 - 4.9GHz */
	netsubtype_iee80211_3_65GHz = 3,	/**< Wireless - IEEE 802.11 - 3.65GHz*/
	netsubtype_iee80211_316THz  = 4,	/**< Wireless - IEEE 802.11 - 316Thz */

	netsubtype_umts_rel99      = 0,		/**< Wireless - UMTS - Rel-99			*/
	netsubtype_umts_rel4       = 1,		/**< Wireless - UMTS - Rel-4			*/
	netsubtype_umts_rel5_hsdpa = 2,		/**< Wireless - UMTS - Rel-5 (w/ HSDPA)	*/
	netsubtype_umts_rel6_hsupa = 3,		/**< Wireless - UMTS - Rel-6 (w/ HSUPA)	*/
	netsubtype_umts_rel7_mimo  = 4,		/**< Wireless - UMTS - Rel-7 (MIMO/OFDM)*/
	netsubtype_umts_rel8       = 5,		/**< Wireless - UMTS - rel-8			*/

	netsubtype_cdma2000_hrpd_rev0 = 0,	/**< Wireless - CDMA-2000-HRPD - Rev-0	*/
	netsubtype_cdma2000_hrpd_revA = 1,	/**< Wireless - CDMA-2000-HRPD - Rev-A	*/
	netsubtype_cdma2000_hrpd_revB = 2,	/**< Wireless - CDMA-2000-HRPD - Rev-B	*/
	netsubtype_cdma2000_hrpd_revC = 3,	/**< Wireless - CDMA-2000-HRPD - Rev-C	*/

	netsubtype_iee80216_2_5GHz = 0,		/**< Wireless - IEEE 802.16	- 2.5GHz	*/
	netsubtype_iee80216_3_5GHz = 1,		/**< Wireless - IEEE 802.16	- 3.5GHz	*/
};

/**
 * SUBTYPE data type.
 */
typedef bitmap<64, netsubtype_enum> netsubtype;

///////////////////////////////////////////////////////////////////////////////
/**
 * TYPE_EXT data type.
 */
typedef octet_string type_ext;

///////////////////////////////////////////////////////////////////////////////
/**
 * NETWORK_TYPE data type.
 */
struct network_type {
	boost::variant<null, link_type>  link;		/**< Link type				*/
	boost::variant<null, netsubtype> subtype;	/**< Link subtype			*/
	boost::variant<null, type_ext>   typeext;	/**< Link type extension	*/

	/**
	 * Construct an empty NETWORK_TYPE data type.
	 */
	network_type() : link(null()), subtype(null()), typeext(null())
	{ }

	/**
	 * Serialize/deserialize the NETWORK_TYPE data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
          ar & link;
          ar & subtype;
          ar & typeext;
	}

	/**
	 * NETWORK_TYPE data type output.
	 *
	 * @param os ostream.
	 * @param nt NETWORK_TYPE data type.
	 * @return ostream reference.
	 */
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
 * SYSTEM_INFO data type.
 */
struct system_info {
	network_type	nettype;					/**< Network type.			*/
	link_addr		linkaddr;					/**< Link address.			*/
	boost::variant<null, parameters> params;	/**< System information.	*/

	/**
	 * Serialize/deserialize the SYSTEM_INFO data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
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
 * OP_NAME data type.
 */
typedef octet_string op_name;

/**
 * SP_ID data type.
 */
typedef octet_string sp_id;

/**
 * OP_NAMESPACE data type enumeration.
 */
enum op_namespace_enum {
	op_namespace_gsm_umts = 0,	/**< GSM/UMTS.	*/
	op_namespace_cdma = 1,		/**< CDMA.		*/
	op_namespace_realm = 2,		/**< REALM.		*/
	op_namespace_itu_t_tsb = 3,	/**< ITU-T/TSB.	*/
	op_namespace_general = 4	/**< General.	*/
};

/**
 * OP_NAMESPACE data type.
 */
typedef enumeration<op_namespace_enum> op_namespace;

///////////////////////////////////////////////////////////////////////////////
/**
 * OPERATOR_ID data type.
 */
struct operator_id {
	op_name				opname;			/**< Operator name.			*/
	op_namespace		opnamespace;	/**< Operator namespace.	*/

	/**
	 * Serialize/deserialize the OPERATOR_ID data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & opname;
		ar & opnamespace;
	}
};

/**
 * ROAMING_PTNS data type.
 */
typedef std::vector<operator_id> roaming_ptns;

///////////////////////////////////////////////////////////////////////////////
/**
 * SUPPORTED_LCP data type enumeration.
 */
enum supported_lcp_enum {
	supported_lcp_null = 0,						/**< NULL.					*/
	supported_lcp_lldp = 1,						/**< LLDP.					*/
	supported_lcp_lbyr_with_lldp = 2,			/**< LbyR with LLDP.		*/
	supported_lcp_lldp_med = 11,				/**< LLDP-MED.				*/
	supported_lcp_lbyr_with_lld_med = 12,		/**< LbyR with LLDP-MED.	*/
	supported_lcp_u_tdoa = 21,					/**< U-TDoA.				*/
	supported_lcp_d_tdoa = 22,					/**< D-TDoA.				*/
	supported_lcp_dhcp = 31,					/**< DHCP.					*/
	supported_lcp_lbyr_with_dhcp = 32,			/**< LbyR with DHCP.		*/
	supported_lcp_oma_supl = 41,				/**< OMA SUPL.				*/
	supported_lcp_ieee_802_11 = 42,				/**< IEEE 802.11.			*/
	supported_lcp_lbyr_with_ieee_802_11 = 43,	/**< LbyR with IEEE 802.11.	*/
	supported_lcp_held = 51,					/**< HELD.					*/
	supported_lcp_lbyr_with_held = 52			/**< LbyR with HELD.		*/
};

/**
 * SUPPORTED_LCP data type.
 */
typedef enumeration<supported_lcp_enum> supported_lcp;

///////////////////////////////////////////////////////////////////////////////
/**
 * PROXY_ADDR data type.
 */
typedef boost::variant<ip4_addr, ip6_addr, fqdn> proxy_addr;

///////////////////////////////////////////////////////////////////////////////
/**
 * NET_TYPE_ADDR data type.
 */
struct net_type_addr {
	network_type nettype;	/**< Network type.	*/
	link_addr    addr;		/**< Link address.	*/

	/**
	 * Serialize/deserialize the NET_TYPE_ADDR data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & nettype;
		ar & addr;
	}

	/**
	 * NET_TYPE_ADDR data type output.
	 *
	 * @param os ostream.
	 * @param nta NET_TYPE_ADDR data type.
	 * @return ostream reference.
	 */
	friend std::ostream& operator<<(std::ostream& os, const net_type_addr& nta)
	{
		os << "\nnettype: " << nta.nettype;
		os << "\naddr: " << nta.addr;

		return os;
	}
};

/**
 * LIST(NET_TYPE_ADDR) data type.
 */
typedef std::vector<net_type_addr> net_type_addr_list;

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_TYPES_INFORMATION__HPP_ */
