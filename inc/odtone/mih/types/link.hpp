//=============================================================================
// Brief   : MIH Link Types
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

#ifndef ODTONE_MIH_TYPES_LINK__HPP_
#define ODTONE_MIH_TYPES_LINK__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/mih/types/base.hpp>
#include <odtone/mih/types/address.hpp>
#include <odtone/mih/types/qos.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
typedef uint8        batt_level;
typedef uint8        num_cos;
typedef uint8        num_queue;
typedef uint16       channel_id;
typedef bool         config_status;
typedef octet_string device_info;
typedef uint16       link_ac_ex_time;
typedef boost::variant<uint8, percentage>   sig_strength;

///////////////////////////////////////////////////////////////////////////////
enum op_mode_enum {
	op_mode_normal = 0,
	op_mode_power_saving = 1,
	op_mode_powered_down = 2,
};

typedef enumeration<op_mode_enum> op_mode;

///////////////////////////////////////////////////////////////////////////////
typedef boost::variant<op_mode, channel_id> link_states_rsp;
typedef std::vector<link_states_rsp>        link_states_rsp_list;
typedef boost::variant<num_cos, num_queue>  link_desc_rsp;
typedef std::vector<link_desc_rsp>          link_desc_rsp_list;

///////////////////////////////////////////////////////////////////////////////
enum dev_states_req_enum {
	dev_state_device_info = 0,
	dev_state_batt_level  = 1,
};

typedef bitmap<16, dev_states_req_enum> dev_states_req;

///////////////////////////////////////////////////////////////////////////////
typedef boost::variant<device_info, batt_level> dev_states_rsp;
typedef std::vector<dev_states_rsp>             dev_states_rsp_list;

///////////////////////////////////////////////////////////////////////////////
enum link_states_req_enum {
	link_states_req_op_channel = 0,
	link_states_req_channel_id = 1,
};

typedef bitmap<16, link_states_req_enum> link_states_req;
typedef std::vector<link_states_req>     link_states_req_list;

///////////////////////////////////////////////////////////////////////////////
struct threshold {
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & val;
		ar & x_dir;
	}


	uint16 val;
	uint8  x_dir; //0 - above, 1 - below
};

///////////////////////////////////////////////////////////////////////////////
typedef boost::variant<device_info,
					   batt_level> dev_states_rsp;

///////////////////////////////////////////////////////////////////////////////
enum link_ac_result_enum {
	link_ac_success   = 0,
	link_ac_failure   = 1,
	link_ac_refused   = 2,
	link_ac_imcapable = 3,
};

typedef enumeration<link_ac_result_enum> link_ac_result;

///////////////////////////////////////////////////////////////////////////////
enum link_ac_type_enum {
	link_ac_type_none       = 0,
	link_ac_type_disconnect = 1,
	link_ac_type_low_power  = 2,
	link_ac_type_power_down = 3,
	link_ac_type_power_up   = 4,
};

typedef enumeration<link_ac_type_enum> link_ac_type;

///////////////////////////////////////////////////////////////////////////////
enum link_ac_attr_enum {
	link_ac_attr_scan         = 0,
	link_ac_attr_res_retain   = 1,
	link_ac_attr_data_fwd_req = 2,
};

typedef bitmap<8, link_ac_attr_enum> link_ac_attr;

///////////////////////////////////////////////////////////////////////////////
struct link_action {
	link_ac_type type;
	link_ac_attr attr;
};

typedef std::vector<link_action> link_action_list;

///////////////////////////////////////////////////////////////////////////////
enum th_action {
	th_action_normal = 0,
	th_action_one_shot = 1,
	th_action_cancel = 2
};

///////////////////////////////////////////////////////////////////////////////
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

typedef enumeration<link_type_enum> link_type;

///////////////////////////////////////////////////////////////////////////////
enum link_dn_reason_enum {
	link_dn_reason_explicit_disconnect = 0,
	link_dn_reason_packet_timeout = 1,
	link_dn_reason_no_resource = 2,
	link_dn_reason_no_broadcast = 3,
	link_dn_reason_authentication_failure = 4,
	link_dn_reason_billing_failure = 5,
};

typedef enumeration<link_dn_reason_enum> link_dn_reason;

///////////////////////////////////////////////////////////////////////////////
enum link_gd_reason_enum {
	link_gd_reason_explicit_disconnect = 0,
	link_gd_reason_link_parameter_degrading = 1,
	link_gd_reason_low_power = 2,
	link_gd_reason_no_resource = 3,
};

typedef enumeration<link_gd_reason_enum> link_gd_reason;

///////////////////////////////////////////////////////////////////////////////
enum link_mihcap_flag_enum {
	link_mihcap_event_service = 1,
	link_mihcap_command_service = 2,
	link_mihcap_information_service = 3,
};

typedef bitmap<8, link_mihcap_flag_enum> link_mihcap_flag;

///////////////////////////////////////////////////////////////////////////////
enum link_param_gen_enum {
	link_param_gen_data_rate = 0,
	link_param_gen_signal_strengh = 1,
	link_param_gen_sinr = 2,
	link_param_gen_throughput = 3,
	link_param_gen_packet_error_rate = 4,
};

typedef bitmap<8, link_param_gen_enum> link_param_gen;

///////////////////////////////////////////////////////////////////////////////
typedef bitmap<8, qos_param_val> link_param_qos;

///////////////////////////////////////////////////////////////////////////////
enum link_param_gg_enum {
	link_param_gg_rx_qual = 0,
	link_param_gg_rs_lev = 1,
	link_param_gg_mean_bep = 2,
	link_param_gg_st_dev_bep = 3,
};

typedef bitmap<8, link_param_gg_enum> link_param_gg;

///////////////////////////////////////////////////////////////////////////////
typedef uint8 link_param_edge;

///////////////////////////////////////////////////////////////////////////////
typedef uint8 link_param_eth;

///////////////////////////////////////////////////////////////////////////////
enum link_param_802_11_enum {
	link_param_802_11_rssi = 0,
	link_param_802_11_no_qos = 1,
	link_param_802_11_multicast_packet_loss_rate = 2,
};

typedef bitmap<8, link_param_802_11_enum> link_param_802_11;

///////////////////////////////////////////////////////////////////////////////
enum link_param_c2k_enum {
	link_param_c2k_pilot_strength = 0,
};

typedef bitmap<8, link_param_c2k_enum> link_param_c2k;

///////////////////////////////////////////////////////////////////////////////
enum link_param_ffd_enum {
	link_param_ffd_cpich_rscp = 0,
	link_param_ffd_pccpch_rscp = 0,
	link_param_ffd_ultra_carrie_rssi = 0,
	link_param_ffd_gsm_carrie_rssi = 0,
	link_param_ffd_cpich_ec_no = 0,
	link_param_ffd_transport_channel_bler = 0,
	link_param_ffd_ue = 0,
};

typedef bitmap<8, link_param_ffd_enum> link_param_ffd;

///////////////////////////////////////////////////////////////////////////////
enum link_param_hrpd_enum {
	link_param_hrpd_pilot_strength = 0,
};

typedef bitmap<8, link_param_hrpd_enum> link_param_hrpd;

///////////////////////////////////////////////////////////////////////////////
typedef uint8 link_param_802_16;

///////////////////////////////////////////////////////////////////////////////
typedef uint8 link_param_802_20;

///////////////////////////////////////////////////////////////////////////////
typedef uint8 link_param_802_22;

///////////////////////////////////////////////////////////////////////////////
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

typedef std::vector<link_id> link_id_list;

///////////////////////////////////////////////////////////////////////////////
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
struct link_scan_rsp {
	link_id      id;
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

///////////////////////////////////////////////////////////////////////////////
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

///////////////////////////////////////////////////////////////////////////////
struct link_action_rsp {
	link_id                             id;
	link_ac_result                      result;
	boost::variant<null, link_scan_rsp> scan;

	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & id;
		ar & result;
		ar & scan;
	}
};

typedef std::vector<link_action_rsp> link_action_rsp_list;

///////////////////////////////////////////////////////////////////////////////
enum link_cmd_list_enum {
	link_cmd_event_subscribe      = 1,
	link_cmd_event_unsubscribe    = 2,
	link_cmd_get_parameters       = 3,
	link_cmd_configure_thresholds = 4,
	link_cmd_action               = 5,
};

typedef bitmap<32, link_cmd_list_enum> link_cmd_list;

///////////////////////////////////////////////////////////////////////////////
struct link_det_cfg {
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & network_id;
		ar & signal;
		ar & link_data_rate;
	}


	octet_string                       network_id;
	boost::variant<null, sig_strength> signal;
	uint32                             link_data_rate;
};

///////////////////////////////////////////////////////////////////////////////
struct link_param_type {
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & type;
		ar & value;
	}

	boost::variant<link_param_gen,
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
			link_param_802_22> type;
	uint8 value;
};

typedef std::vector<link_param_type> link_param_type_list;

///////////////////////////////////////////////////////////////////////////////
enum link_desc_req_enum {
	link_desc_req_classes_of_service_supported = 0,
	link_desc_req_queues_supported = 1,
};

typedef bitmap<16, link_desc_req_enum> link_desc_req;

///////////////////////////////////////////////////////////////////////////////
struct link_status_req {
	link_states_req_list _states_req;
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
typedef uint16 link_param_val;

///////////////////////////////////////////////////////////////////////////////
struct link_param {
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & type;
		ar & value;
	}


	link_param_type type;

	boost::variant<link_param_val, qos_param_val> value;
};

typedef std::vector<link_param> link_param_list;

///////////////////////////////////////////////////////////////////////////////
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

typedef std::vector<link_param_report> link_param_rpt_list;

///////////////////////////////////////////////////////////////////////////////
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
	uint16			     timer_interval;
	th_action                    action;
	std::vector<threshold>       threshold_list;
};

typedef std::vector<link_cfg_param> link_cfg_param_list;

///////////////////////////////////////////////////////////////////////////////
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

typedef std::vector<link_cfg_status> link_cfg_status_list;

///////////////////////////////////////////////////////////////////////////////
enum net_caps_enum {
	net_caps_security = 0,
	net_caps_qos_0 = 1,
	net_caps_qos_1 = 2,
	net_caps_qos_2 = 3,
	net_caps_qos_3 = 4,
	net_caps_qos_4 = 5,
	net_caps_qos_5 = 6,
	net_caps_internet = 7,
	net_caps_emergency_services	= 8,
	net_caps_mih = 9,
};

typedef bitmap<32, net_caps_enum> net_caps;

///////////////////////////////////////////////////////////////////////////////
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

typedef std::vector<link_det_info> link_det_info_list;

///////////////////////////////////////////////////////////////////////////////
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

typedef std::vector<link_poa_list> list_of_link_poa_list;

///////////////////////////////////////////////////////////////////////////////
struct link_status_rsp {
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & states_rsp_list;
		ar & param_list;
		ar & desc_rsp;
	}


	link_states_rsp_list states_rsp_list;
	link_param_list      param_list;
	link_desc_rsp_list   desc_rsp;
};

typedef std::vector<link_status_rsp> link_status_rsp_list;

///////////////////////////////////////////////////////////////////////////////
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

typedef std::vector<status_rsp> status_rsp_list;

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /*namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_TYPES_LINK__HPP_ */
