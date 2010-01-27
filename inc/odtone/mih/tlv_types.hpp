//=============================================================================
// Brief   : MIH TLV Types
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

#ifndef ODTONE_MIH_TLV_TYPES__HPP_
#define ODTONE_MIH_TLV_TYPES__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/mih/tlv.hpp>
#include <odtone/mih/types.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
typedef tlv_fwd<id,                    tlv_< 1> > tlv_source_id;
typedef tlv_fwd<id,                    tlv_< 2> > tlv_destination_id;
typedef tlv_fwd<status,                tlv_< 3> > tlv_status;
typedef tlv_fwd<link_type,             tlv_< 4> > tlv_link_type;
typedef tlv_fwd<event_list,            tlv_< 5> > tlv_event_list;
typedef tlv_fwd<command_list,          tlv_< 6> > tlv_command_list;
typedef tlv_fwd<iq_type_list,          tlv_< 7> > tlv_query_type_list;
typedef tlv_fwd<transport_list,        tlv_< 8> > tlv_transport_option_list;
typedef tlv_fwd<net_type_addr_list,    tlv_< 9> > tlv_net_type_addr_list;
typedef tlv_fwd<mbb_ho_supp_list,      tlv_<10> > tlv_mbb_ho_supp_list;
typedef tlv_fwd<reg_request_code,      tlv_<11> > tlv_reg_request_code;
typedef tlv_fwd<uint32,                tlv_<12> > tlv_valid_time_interval;
typedef tlv_fwd<link_tuple_id,         tlv_<13> > tlv_link_identifier;
typedef tlv_fwd<link_tuple_id,         tlv_<14> > tlv_new_link_identifier;
typedef tlv_fwd<link_addr,             tlv_<15> > tlv_old_access_router;
typedef tlv_fwd<link_addr,             tlv_<16> > tlv_new_access_router;
typedef tlv_fwd<bool,                  tlv_<17> > tlv_ip_renewal_flag;
typedef tlv_fwd<ip_mob_mgmt,           tlv_<18> > tlv_ip_mob_mgmt;
typedef tlv_fwd<ip_cfg_methods,        tlv_<19> > tlv_ip_cfg_methods;
typedef tlv_fwd<link_dn_reason,        tlv_<20> > tlv_link_dn_reason;
typedef tlv_fwd<uint16,                tlv_<21> > tlv_time_interval;
typedef tlv_fwd<link_gd_reason,        tlv_<22> > tlv_link_gd_reason;
typedef tlv_fwd<link_param_rpt_list,   tlv_<23> > tlv_link_param_rpt_list;
typedef tlv_fwd<dev_states_req,        tlv_<24> > tlv_dev_states_req;
typedef tlv_fwd<link_id_list,          tlv_<25> > tlv_link_id_list;
typedef tlv_fwd<dev_states_rsp_list,   tlv_<26> > tlv_dev_states_rsp_list;
typedef tlv_fwd<link_status_req,       tlv_<27> > tlv_get_status_req_set;
typedef tlv_fwd<status_rsp_list,       tlv_<28> > tlv_get_status_rsp_list;
typedef tlv_fwd<link_cfg_param_list,   tlv_<29> > tlv_link_cfg_param_list;
typedef tlv_fwd<link_cfg_status_list,  tlv_<30> > tlv_link_cfg_status_list;
typedef tlv_fwd<list_of_link_poa_list, tlv_<31> > tlv_list_of_link_poa_list;
typedef tlv_fwd<rq_result_list,        tlv_<32> > tlv_preferred_link_list;
typedef tlv_fwd<qos_list,              tlv_<33> > tlv_ho_resource_query_list;
typedef tlv_fwd<ho_status,             tlv_<34> > tlv_ho_status;
typedef tlv_fwd<ip_addr,               tlv_<35> > tlv_access_router_addr;
typedef tlv_fwd<ip_addr,               tlv_<36> > tlv_dhcp_server_addr;
typedef tlv_fwd<ip_addr,               tlv_<37> > tlv_fa_addr;
typedef tlv_fwd<link_action_list,      tlv_<38> > tlv_link_action_list;
typedef tlv_fwd<link_action_rsp_list,  tlv_<39> > tlv_link_action_rsp_list;
typedef tlv_fwd<ho_result,             tlv_<40> > tlv_ho_result;
typedef tlv_fwd<bool,                  tlv_<41> > tlv_resource_status;
typedef tlv_fwd<bool,                  tlv_<42> > tlv_resource_ret_status;
typedef tlv_fwd<iq_bin_data_list,      tlv_<43> > tlv_info_query_bin_data_list;
typedef tlv_fwd<iq_rdf_data_list,      tlv_<44> > tlv_info_query_rdf_data_list;
typedef tlv_fwd<bool,                  tlv_<45> > tlv_iq_rdf_schema_url;
typedef tlv_fwd<iq_rdf_schema_list,    tlv_<46> > tlv_iq_rdf_schema_list;
typedef tlv_fwd<uint16,                tlv_<47> > tlv_max_response_size;
typedef tlv_fwd<ir_bin_data_list,      tlv_<48> > tlv_info_resp_bin_data_list;
typedef tlv_fwd<ir_rdf_data_list,      tlv_<49> > tlv_info_resp_rdf_data_list;
typedef tlv_fwd<ir_rdf_schem_url_list, tlv_<50> > tlv_info_resp_rdf_schem_url_list;
typedef tlv_fwd<ir_rdf_schem_list,     tlv_<51> > tlv_info_resp_rdf_schem_list;
typedef tlv_fwd<id,                    tlv_<52> > tlv_mobile_node_mihf_id;
typedef tlv_fwd<bool,                  tlv_<53> > tlv_query_res_report_flag;
typedef tlv_fwd<evt_cfg_info_list,     tlv_<54> > tlv_evt_cfg_info_list;
typedef tlv_fwd<tgt_net_info,          tlv_<55> > tlv_target_network_info;
typedef tlv_fwd<tgt_net_info_list,     tlv_<56> > tlv_target_network_info_list;
typedef tlv_fwd<asgn_res_set,          tlv_<57> > tlv_assigned_resource_set;
typedef tlv_fwd<link_det_info_list,    tlv_<58> > tlv_link_det_info_list;
typedef tlv_fwd<link_id,               tlv_<59> > tlv_mn_link_id;
typedef tlv_fwd<link_addr,             tlv_<60> > tlv_poa;
typedef tlv_fwd<bool,                  tlv_<61> > tlv_unauthenticated_info_req;
typedef tlv_fwd<network_type,          tlv_<62> > tlv_network_type;
typedef tlv_fwd<rq_res_set,            tlv_<63> > tlv_request_resource_set;

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_TLV_TYPES__HPP_ */
