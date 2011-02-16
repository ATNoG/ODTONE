//=============================================================================
// Brief   : MIH Link Types
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

#ifndef ODTONE_MIH_TYPES_LINK__HPP_
#define ODTONE_MIH_TYPES_LINK__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/mih/types/base.hpp>
#include <odtone/mih/types/address.hpp>
#include <odtone/mih/types/qos.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
/**
 * Define BATT_LEVEL data type.
 */
typedef uint8        batt_level;

/**
 * Define NUM_COS data type.
 */
typedef uint8        num_cos;

/**
 * Define NUM_QUEUE data type.
 */
typedef uint8        num_queue;

/**
 * Define CHANNEL_ID data type.
 */
typedef uint16       channel_id;

/**
 * Define CONFIG_STATUS data type.
 */
typedef bool config_status;

/**
 * Define DEVICE_INFO data type.
 */
typedef octet_string device_info;

/**
 * Define LINK_AC_EX_TIME data type.
 */
typedef uint16 link_ac_ex_time;

/**
 * Define SIG_STRENGTH data type.
 */
typedef boost::variant<uint8, percentage> sig_strength;

/**
 * Define LINK_RES_STATUS data type.
 */
typedef bool link_res_status;

///////////////////////////////////////////////////////////////////////////////
/**
 * The enumeration of OP_MODE data type.
 */
enum op_mode_enum {
	op_mode_normal = 0,
	op_mode_power_saving = 1,
	op_mode_powered_down = 2,
};

/**
 * Define OP_MODE data type.
 */
typedef enumeration<op_mode_enum> op_mode;

///////////////////////////////////////////////////////////////////////////////
/**
 * Define LINK_STATES_RSP data type.
 */
typedef boost::variant<op_mode, channel_id> link_states_rsp;

/**
 * Define LIST(LINK_STATES_RSP) data type.
 */
typedef std::vector<link_states_rsp>        link_states_rsp_list;

/**
 * Define LINK_DESC_RSP data type.
 */
typedef boost::variant<num_cos, num_queue>  link_desc_rsp;

/**
 * Define LIST(LINK_DESC_RSP) data type.
 */
typedef std::vector<link_desc_rsp>          link_desc_rsp_list;

///////////////////////////////////////////////////////////////////////////////
/**
 * The enumeration of DEV_STATES_REQ data type.
 */
enum dev_states_req_enum {
	dev_state_device_info = 0,
	dev_state_batt_level  = 1,
};

/**
 * Define DEV_STATES_REQ data type.
 */
typedef bitmap<16, dev_states_req_enum> dev_states_req;

///////////////////////////////////////////////////////////////////////////////
/**
 * Define DEV_STATES_RSP data type.
 */
typedef boost::variant<device_info, batt_level> dev_states_rsp;

/**
 * Define LIST(DEV_STATES_RSP) data type.
 */
typedef std::vector<dev_states_rsp>             dev_states_rsp_list;

///////////////////////////////////////////////////////////////////////////////
/**
 * The enumeration of LINK_STATES_REQ data type.
 */
enum link_states_req_enum {
	link_states_req_op_mode = 0,
	link_states_req_channel_id = 1,
};

/**
 * Define LINK_STATES_REQ data type.
 */
typedef bitmap<16, link_states_req_enum> link_states_req;

/**
 * Define LIST(LINK_STATES_REQ) data type.
 */
typedef std::vector<link_states_req>     link_states_req_list;

///////////////////////////////////////////////////////////////////////////////
/**
 * Define THRESHOLD data type.
 */
struct threshold {
	enum type_ip_enum {
		above_threshold = 0,
		below_threshold = 1,
	};

	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & threshold_val;
		ar & threshold_x_dir;
	}

	uint16                     threshold_val;
	enumeration<type_ip_enum>  threshold_x_dir;
};

///////////////////////////////////////////////////////////////////////////////
/**
 * The enumeration of LINK_AC_RESULT data type.
 */
enum link_ac_result_enum {
	link_ac_success   = 0,
	link_ac_failure   = 1,
	link_ac_refused   = 2,
	link_ac_incapable = 3,
};

/**
 * Define LINK_AC_RESULT data type.
 */
typedef enumeration<link_ac_result_enum> link_ac_result;

///////////////////////////////////////////////////////////////////////////////
/**
 * The enumeration of LINK_AC_TYPE data type.
 */
enum link_ac_type_enum {
	link_ac_type_none       = 0,
	link_ac_type_disconnect = 1,
	link_ac_type_low_power  = 2,
	link_ac_type_power_down = 3,
	link_ac_type_power_up   = 4,
};

/**
 * Define LINK_AC_TYPE data type.
 */
typedef enumeration<link_ac_type_enum> link_ac_type;

///////////////////////////////////////////////////////////////////////////////
/**
 * The enumeration of LINK_AC_ATTR data type.
 */
enum link_ac_attr_enum {
	link_ac_attr_scan         = 0,
	link_ac_attr_res_retain   = 1,
	link_ac_attr_data_fwd_req = 2,
};

/**
 * Define LINK_AC_ATTR data type.
 */
typedef bitmap<8, link_ac_attr_enum> link_ac_attr;

///////////////////////////////////////////////////////////////////////////////
/**
 * Define LINK_ACTION data type.
 */
struct link_action {
	link_ac_type type;
	link_ac_attr attr;

	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{;
		ar & type;
		ar & attr;
	}
};

///////////////////////////////////////////////////////////////////////////////
/**
 * The enumeration of TH_ACTION data type.
 */
enum th_action_enum {
	th_action_normal = 0,
	th_action_one_shot = 1,
	th_action_cancel = 2
};

/**
 * Define TH_ACTION data type.
 */
typedef enumeration<th_action_enum> th_action;

///////////////////////////////////////////////////////////////////////////////
/**
 * The enumeration of LINK_TYPE data type.
 */
enum link_type_enum {
	link_type_gsm = 1,
	link_type_gprs = 2,
	link_type_edge = 3,

	link_type_ethernet = 15,

	link_type_wireless_other = 18,
	link_type_802_11 = 19,

	link_type_cdma2000 = 22,
	link_type_umts = 23,
	link_type_cdma2000_hrpd = 24,

	link_type_802_16 = 27,
	link_type_802_20 = 28,
	link_type_802_22 = 29
};

/**
 * Define LINK_TYPE data type.
 */
typedef enumeration<link_type_enum> link_type;

///////////////////////////////////////////////////////////////////////////////
/**
 * The enumeration of LINK_DN_REASON data type.
 */
enum link_dn_reason_enum {
	link_dn_reason_explicit_disconnect = 0,
	link_dn_reason_packet_timeout = 1,
	link_dn_reason_no_resource = 2,
	link_dn_reason_no_broadcast = 3,
	link_dn_reason_authentication_failure = 4,
	link_dn_reason_billing_failure = 5,
};

/**
 * Define LINK_DN_REASON data type.
 */
typedef enumeration<link_dn_reason_enum> link_dn_reason;

///////////////////////////////////////////////////////////////////////////////
/**
 * The enumeration of LINK_GD_REASON data type.
 */
enum link_gd_reason_enum {
	link_gd_reason_explicit_disconnect = 0,
	link_gd_reason_link_parameter_degrading = 1,
	link_gd_reason_low_power = 2,
	link_gd_reason_no_resource = 3,
};

/**
 * Define LINK_GD_REASON data type.
 */
typedef enumeration<link_gd_reason_enum> link_gd_reason;

///////////////////////////////////////////////////////////////////////////////
/**
 * The enumeration of LINK_MIHCAP_FLAG data type.
 */
enum link_mihcap_flag_enum {
	link_mihcap_event_service = 1,
	link_mihcap_command_service = 2,
	link_mihcap_information_service = 3,
};

/**
 * Define LINK_MIHCAP_FLAG data type.
 */
typedef bitmap<8, link_mihcap_flag_enum> link_mihcap_flag;

///////////////////////////////////////////////////////////////////////////////
/**
 * The enumeration of LINK_PARAM_GEN data type.
 */
enum link_param_gen_enum {
	link_param_gen_data_rate = 0,
	link_param_gen_signal_strength = 1,
	link_param_gen_sinr = 2,
	link_param_gen_throughput = 3,
	link_param_gen_packet_error_rate = 4,
};

/**
 * Define LINK_PARAM_GEM data type.
 */
typedef enumeration<link_param_gen_enum> link_param_gen;

///////////////////////////////////////////////////////////////////////////////
/**
 * Define LINK_PARAM_QOS data type.
 */
typedef uint8 link_param_qos;

///////////////////////////////////////////////////////////////////////////////
/**
 * The enumeration of LINK_PARAM_GG data type.
 */
enum link_param_gg_enum {
	link_param_gg_rx_qual = 0,
	link_param_gg_rs_lev = 1,
	link_param_gg_mean_bep = 2,
	link_param_gg_st_dev_bep = 3,
};

/**
 * Define LINK_PARAM_GG data type.
 */
typedef enumeration<link_param_gg_enum> link_param_gg;

///////////////////////////////////////////////////////////////////////////////
/**
 * The enumeration of LINK_PARAM_EDGE data type.
 */
enum link_param_edge_enum {
};

/**
 * Define LINK_PARAM_EDGE data type.
 */
typedef enumeration<link_param_edge_enum> link_param_edge;

///////////////////////////////////////////////////////////////////////////////
/**
 * The enumeration of LINK_PARAM_ETH data type.
 */
enum link_param_eth_enum {
};

/**
 * Define LINK_PARAM_ETH data type.
 */
typedef enumeration<link_param_eth_enum> link_param_eth;

///////////////////////////////////////////////////////////////////////////////
/**
 * The enumeration of LINK_PARAM_802_11 data type.
 */
enum link_param_802_11_enum {
	link_param_802_11_rssi = 0,
	link_param_802_11_no_qos = 1,
	link_param_802_11_multicast_packet_loss_rate = 2,
};

/**
 * Define LINK_PARAM_802_11 data type.
 */
typedef enumeration<link_param_802_11_enum> link_param_802_11;

///////////////////////////////////////////////////////////////////////////////
/**
 * The enumeration of LINK_PARAM_C2K data type.
 */
enum link_param_c2k_enum {
	link_param_c2k_pilot_strength = 0,
};

/**
 * Define LINK_PARAM_C2K data type.
 */
typedef enumeration<link_param_c2k_enum> link_param_c2k;

///////////////////////////////////////////////////////////////////////////////
/**
 * The enumeration of LINK_PARAM_FFD data type.
 */
enum link_param_ffd_enum {
	link_param_ffd_cpich_rscp = 0,
	link_param_ffd_pccpch_rscp = 1,
	link_param_ffd_ultra_carrie_rssi = 2,
	link_param_ffd_gsm_carrie_rssi = 3,
	link_param_ffd_cpich_ec_no = 4,
	link_param_ffd_transport_channel_bler = 5,
	link_param_ffd_ue = 6,
};

/**
 * Define LINK_PARAM_FFD data type.
 */
typedef enumeration<link_param_ffd_enum> link_param_ffd;

///////////////////////////////////////////////////////////////////////////////
/**
 * The enumeration of LINK_PARAM_HRPD data type.
 */
enum link_param_hrpd_enum {
	link_param_hrpd_pilot_strength = 0,
};

/**
 * Define LINK_PARAM_HRPD data type.
 */
typedef enumeration<link_param_hrpd_enum> link_param_hrpd;

///////////////////////////////////////////////////////////////////////////////
/**
 * The enumeration of LINK_PARAM_802_16 data type.
 */
enum link_param_802_16_enum {
};

/**
 * Define LINK_PARAM_802_16 data type.
 */
typedef enumeration<link_param_802_16_enum> link_param_802_16;

///////////////////////////////////////////////////////////////////////////////
/**
 * The enumeration of LINK_PARAM_802_20 data type.
 */
enum link_param_802_20_enum {
};

/**
 * Define LINK_PARAM_802_20 data type.
 */
typedef enumeration<link_param_802_20_enum> link_param_802_20;

///////////////////////////////////////////////////////////////////////////////
/**
 * The enumeration of LINK_PARAM_802_22 data type.
 */
enum link_param_802_22_enum {
};

/**
 * Define LINK_PARAM_802_22 data type.
 */
typedef enumeration<link_param_802_22_enum> link_param_802_22;


///////////////////////////////////////////////////////////////////////////////
/**
 * Define LINK_ID data type.
 */
struct link_id {
	link_id() : type(link_type_enum(0))
	{ }

	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & type;
		ar & addr;
	}

	bool operator==(const link_id& other) const
	{
		return ((type == other.type) && (addr == other.addr));
	}

	link_type type;
	link_addr addr;
};

/**
 * Define LIST(LINK_ID) data type.
 */
typedef std::vector<link_id> link_id_list;

///////////////////////////////////////////////////////////////////////////////
/**
 * Define LINK_TUPLE_ID data type.
 */
class link_tuple_id : public link_id {
public:
	link_tuple_id() : poa_addr(null())
	{ }

	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		link_id::serialize(ar);
		ar & poa_addr;
	}

	bool operator==(const link_tuple_id& other) const
	{
		return ((static_cast<const link_id&>(*this) == static_cast<const link_id&>(other))
				&& (addr == other.addr));
	}

	boost::variant<null, link_addr> poa_addr;
};

///////////////////////////////////////////////////////////////////////////////
/**
 * Define LINK_SCAN_RSP data type.
 */
struct link_scan_rsp {
	link_addr    id;
	octet_string net_id;
	sig_strength signal;

	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & id;
		ar & net_id;
		ar & signal;
	}
};

/**
 * Define LIST(LINK_SCAN_RSP) data type.
 */
typedef std::vector<link_scan_rsp> link_scan_rsp_list;

///////////////////////////////////////////////////////////////////////////////
/**
 * Define LINK_ACTION_REQ data type.
 */
struct link_action_req {
	link_id                         id;
	boost::variant<null, link_addr> addr;
	link_action                     action;
	link_ac_ex_time                 ex_time;

	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & id;
		ar & addr;
		ar & action;
		ar & ex_time;
	}
};

/**
 * Define LIST(LINK_ACTION_REQ) data type.
 */
typedef std::vector<link_action_req> link_action_list;

///////////////////////////////////////////////////////////////////////////////
/**
 * Define LINK_ACTION_RSP data type.
 */
struct link_action_rsp {
	link_id                                  id;
	link_ac_result                           result;
	boost::variant<null, link_scan_rsp_list> scan_list;

	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & id;
		ar & result;
		ar & scan_list;
	}
};

/**
 * Define LIST(LINK_ACTION_RSP) data type.
 */
typedef std::vector<link_action_rsp> link_action_rsp_list;

///////////////////////////////////////////////////////////////////////////////
/**
 * The enumeration of LINK_CMD_LIST data type.
 */
enum link_cmd_list_enum {
	link_cmd_event_subscribe      = 1,
	link_cmd_event_unsubscribe    = 2,
	link_cmd_get_parameters       = 3,
	link_cmd_configure_thresholds = 4,
	link_cmd_action               = 5,
};

/**
 * Define LINK_CMD_LIST data type.
 */
typedef bitmap<32, link_cmd_list_enum> link_cmd_list;

///////////////////////////////////////////////////////////////////////////////
/**
 * Define LINK_DET_CFG data type.
 */
struct link_det_cfg {
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & network_id;
		ar & signal;
		ar & link_data_rate;
	}


	boost::variant<null, octet_string> network_id;
	boost::variant<null, sig_strength> signal;
	boost::variant<null, uint32>       link_data_rate;
};

///////////////////////////////////////////////////////////////////////////////
/**
 * Define LINK_PARAM_TYPE data type.
 */
typedef boost::variant<link_param_gen,
			link_param_qos,
			link_param_gg,
			link_param_edge,
			link_param_eth,
			link_param_802_11,
			link_param_c2k,
			link_param_ffd,
			link_param_hrpd,
			link_param_802_16,
			link_param_802_20,
			link_param_802_22> link_param_type;

/**
 * Define LIST(LINK_PARAM_TYPE) data type.
 */
typedef std::vector<link_param_type> link_param_type_list;

///////////////////////////////////////////////////////////////////////////////
/**
 * The enumeration of LINK_DESC_REQ_LIST data type.
 */
enum link_desc_req_enum {
	link_desc_req_classes_of_service_supported = 0,
	link_desc_req_queues_supported = 1,
};

/**
 * Define LINK_DESC_REQ data type.
 */
typedef bitmap<16, link_desc_req_enum> link_desc_req;

///////////////////////////////////////////////////////////////////////////////
/**
 * Define LINK_STATUS_REQ data type.
 */
struct link_status_req {
	link_states_req      _states_req;
	link_param_type_list _param_type_list;
	link_desc_req        _desc_req;


	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & _states_req;
		ar & _param_type_list;
		ar & _desc_req;
	}
};

///////////////////////////////////////////////////////////////////////////////
/**
 * Define LINK_PARAM_VAL data type.
 */
typedef uint16 link_param_val;

///////////////////////////////////////////////////////////////////////////////
/**
 * Define LINK_PARAM data type.
 */
struct link_param {
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & type;
		ar & value;
	}

	link_param_type type;
	boost::variant<link_param_val,
	               qos_param_val> value;
};

/**
 * Define LINK_PARAM_LIST data type.
 */
typedef std::vector<link_param> link_param_list;

///////////////////////////////////////////////////////////////////////////////
/**
 * Define LINK_PARAM_RPT data type.
 */
struct link_param_report {
	link_param_report() : thold(null())
	{ }

	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & param;
		ar & thold;
	}


	link_param                      param;
	boost::variant<null, threshold> thold;
};

/**
 * Define LIST(LINK_PARAM_RPT) data type.
 */
typedef std::vector<link_param_report> link_param_rpt_list;

///////////////////////////////////////////////////////////////////////////////
/**
 * Define LINK_CFG_PARAM data type.
 */
struct link_cfg_param {
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & type;
		ar & timer_interval;
		ar & action;
		ar & threshold_list;
	}


	link_param_type              type;
	boost::variant<null, uint16> timer_interval;
	th_action                    action;
	std::vector<threshold>       threshold_list;
};

/**
 * Define LIST(LINK_CFG_PARAM) data type.
 */
typedef std::vector<link_cfg_param> link_cfg_param_list;

///////////////////////////////////////////////////////////////////////////////
/**
 * Define LINK_CFG_STATUS data type.
 */
struct link_cfg_status {
	link_param_type type;
	threshold       thold;
	config_status   status;

	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & type;
		ar & thold;
		ar & status;
	}
};

/**
 * Define LIST(LINK_CFG_STATUS) data type.
 */
typedef std::vector<link_cfg_status> link_cfg_status_list;

///////////////////////////////////////////////////////////////////////////////
/**
 * The enumeration of NET_CAPS data type.
 */
enum net_caps_enum {
	net_caps_security = 0,
	net_caps_qos_0 = 1,
	net_caps_qos_1 = 2,
	net_caps_qos_2 = 3,
	net_caps_qos_3 = 4,
	net_caps_qos_4 = 5,
	net_caps_qos_5 = 6,
	net_caps_internet = 7,
	net_caps_emergency_services = 8,
	net_caps_mih = 9,
};

/**
 * Define NET_CAPS data type.
 */
typedef bitmap<32, net_caps_enum> net_caps;

///////////////////////////////////////////////////////////////////////////////
/**
 * Define LINK_DET_INFO data type.
 */
struct link_det_info {
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & id;
		ar & network_id;
		ar & net_aux_id;
		ar & signal;
		ar & sinr;
		ar & data_rate;
		ar & mih_capabilities;
		ar & net_capabilities;
	}


	link_tuple_id    id;
	octet_string     network_id;
	octet_string     net_aux_id;
	sig_strength     signal;
	uint16           sinr;
	uint32           data_rate;
	link_mihcap_flag mih_capabilities;
	net_caps         net_capabilities;
};

/**
 * Define LIST(LINK_DET_INFO) data type.
 */
typedef std::vector<link_det_info> link_det_info_list;

///////////////////////////////////////////////////////////////////////////////
/**
 * Define LINK_POA_LIST data type.
 */
struct link_poa_list {
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & id;
		ar & addr_list;
	}


	link_id        id;
	link_addr_list addr_list;
};

/**
 * Define LIST(LINK_POA_LIST) data type.
 */
typedef std::vector<link_poa_list> list_of_link_poa_list;

///////////////////////////////////////////////////////////////////////////////
/**
 * Define LINK_STATUS_RSP data type.
 */
struct link_status_rsp {
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & states_rsp_list;
		ar & param_list;
		ar & desc_rsp_list;
	}


	link_states_rsp_list states_rsp_list;
	link_param_list      param_list;
	link_desc_rsp_list   desc_rsp_list;
};

/**
 * Define LIST(LINK_STATUS_RSP) data type.
 */
typedef std::vector<link_status_rsp> link_status_rsp_list;

///////////////////////////////////////////////////////////////////////////////
/**
 * Define SEQUENCE(LINK_ID,LINK_STATUS_RSP) data type.
 */
struct status_rsp {
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & id;
		ar & rsp;
	}


	link_id         id;
	link_status_rsp rsp;
};

/**
 * Define LIST(SEQUENCE(LINK_ID,LINK_STATUS_RSP)) data type.
 */
typedef std::vector<status_rsp> status_rsp_list;

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /*namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_TYPES_LINK__HPP_ */
