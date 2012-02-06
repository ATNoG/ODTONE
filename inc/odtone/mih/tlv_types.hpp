//=============================================================================
// Brief   : MIH TLV Types
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

#ifndef ODTONE_MIH_TLV_TYPES__HPP_
#define ODTONE_MIH_TLV_TYPES__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/mih/tlv.hpp>
#include <odtone/mih/types.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
static const tlv_cast_<id,                    tlv_< 1> > tlv_source_id = {};
static const tlv_cast_<id,                    tlv_< 2> > tlv_destination_id = {};
static const tlv_cast_<status,                tlv_< 3> > tlv_status = {};
static const tlv_cast_<link_type,             tlv_< 4> > tlv_link_type = {};
static const tlv_cast_<mih_evt_list,          tlv_< 5> > tlv_event_list = {};
static const tlv_cast_<mih_cmd_list,          tlv_< 6> > tlv_command_list = {};
static const tlv_cast_<iq_type_list,          tlv_< 7> > tlv_query_type_list = {};
static const tlv_cast_<transport_list,        tlv_< 8> > tlv_transport_option_list = {};
static const tlv_cast_<net_type_addr_list,    tlv_< 9> > tlv_net_type_addr_list = {};
static const tlv_cast_<mbb_ho_supp_list,      tlv_<10> > tlv_mbb_ho_supp_list = {};
static const tlv_cast_<reg_request_code,      tlv_<11> > tlv_reg_request_code = {};
static const tlv_cast_<uint32,                tlv_<12> > tlv_valid_time_interval = {};
static const tlv_cast_<link_tuple_id,         tlv_<13> > tlv_link_identifier = {};
static const tlv_cast_<link_tuple_id,         tlv_<14> > tlv_new_link_identifier = {};
static const tlv_cast_<link_addr,             tlv_<15> > tlv_old_access_router = {};
static const tlv_cast_<link_addr,             tlv_<16> > tlv_new_access_router = {};
static const tlv_cast_<bool,                  tlv_<17> > tlv_ip_renewal_flag = {};
static const tlv_cast_<ip_mob_mgmt,           tlv_<18> > tlv_ip_mob_mgmt = {};
static const tlv_cast_<ip_cfg_methods,        tlv_<19> > tlv_ip_cfg_methods = {};
static const tlv_cast_<link_dn_reason,        tlv_<20> > tlv_link_dn_reason = {};
static const tlv_cast_<uint16,                tlv_<21> > tlv_time_interval = {};
static const tlv_cast_<link_gd_reason,        tlv_<22> > tlv_link_gd_reason = {};
static const tlv_cast_<link_param_rpt_list,   tlv_<23> > tlv_link_param_rpt_list = {};
static const tlv_cast_<dev_states_req,        tlv_<24> > tlv_dev_states_req = {};
static const tlv_cast_<link_id_list,          tlv_<25> > tlv_link_id_list = {};
static const tlv_cast_<dev_states_rsp_list,   tlv_<26> > tlv_dev_states_rsp_list = {};
static const tlv_cast_<link_status_req,       tlv_<27> > tlv_get_status_req_set = {};
static const tlv_cast_<status_rsp_list,       tlv_<28> > tlv_get_status_rsp_list = {};
static const tlv_cast_<link_cfg_param_list,   tlv_<29> > tlv_link_cfg_param_list = {};
static const tlv_cast_<link_cfg_status_list,  tlv_<30> > tlv_link_cfg_status_list = {};
static const tlv_cast_<list_of_link_poa_list, tlv_<31> > tlv_list_of_link_poa_list = {};
static const tlv_cast_<rq_result_list,        tlv_<32> > tlv_preferred_link_list = {};
static const tlv_cast_<qos_list,              tlv_<33> > tlv_ho_resource_query_list = {};
static const tlv_cast_<ho_status,             tlv_<34> > tlv_ho_status = {};
static const tlv_cast_<ip_addr,               tlv_<35> > tlv_access_router_addr = {};
static const tlv_cast_<ip_addr,               tlv_<36> > tlv_dhcp_server_addr = {};
static const tlv_cast_<ip_addr,               tlv_<37> > tlv_fa_addr = {};
static const tlv_cast_<link_action_list,      tlv_<38> > tlv_link_action_list = {};
static const tlv_cast_<link_action_rsp_list,  tlv_<39> > tlv_link_action_rsp_list = {};
static const tlv_cast_<ho_result,             tlv_<40> > tlv_ho_result = {};
static const tlv_cast_<bool,                  tlv_<41> > tlv_resource_status = {};
static const tlv_cast_<bool,                  tlv_<42> > tlv_resource_ret_status = {};
static const tlv_cast_<iq_bin_data_list,      tlv_<43> > tlv_info_query_bin_data_list = {};
static const tlv_cast_<iq_rdf_data_list,      tlv_<44> > tlv_info_query_rdf_data_list = {};
static const tlv_cast_<bool,                  tlv_<45> > tlv_iq_rdf_schema_url = {};
static const tlv_cast_<iq_rdf_schema_list,    tlv_<46> > tlv_iq_rdf_schema_list = {};
static const tlv_cast_<uint16,                tlv_<47> > tlv_max_response_size = {};
static const tlv_cast_<ir_bin_data_list,      tlv_<48> > tlv_info_resp_bin_data_list = {};
static const tlv_cast_<ir_rdf_data_list,      tlv_<49> > tlv_info_resp_rdf_data_list = {};
static const tlv_cast_<ir_rdf_schem_url_list, tlv_<50> > tlv_info_resp_rdf_schem_url_list = {};
static const tlv_cast_<ir_rdf_schem_list,     tlv_<51> > tlv_info_resp_rdf_schem_list = {};
static const tlv_cast_<id,                    tlv_<52> > tlv_mobile_node_mihf_id = {};
static const tlv_cast_<bool,                  tlv_<53> > tlv_query_res_report_flag = {};
static const tlv_cast_<evt_cfg_info_list,     tlv_<54> > tlv_evt_cfg_info_list = {};
static const tlv_cast_<tgt_net_info,          tlv_<55> > tlv_target_network_info = {};
static const tlv_cast_<tgt_net_info_list,     tlv_<56> > tlv_target_network_info_list = {};
static const tlv_cast_<asgn_res_set,          tlv_<57> > tlv_assigned_resource_set = {};
static const tlv_cast_<link_det_info_list,    tlv_<58> > tlv_link_det_info_list = {};
static const tlv_cast_<link_id,               tlv_<59> > tlv_mn_link_id = {};
static const tlv_cast_<link_addr,             tlv_<60> > tlv_poa = {};
static const tlv_cast_<bool,                  tlv_<61> > tlv_unauthenticated_info_req = {};
static const tlv_cast_<network_type,          tlv_<62> > tlv_network_type = {};
static const tlv_cast_<rq_res_set,            tlv_<63> > tlv_request_resource_set = {};

// ODTONE specific TLVs
static const tlv_cast_<link_evt_list,         tlv_<101> > tlv_link_evt_list = {};
static const tlv_cast_<link_cmd_list,         tlv_<102> > tlv_link_cmd_list = {};
static const tlv_cast_<link_param_type_list,  tlv_<103> > tlv_link_parameters_req = {};
static const tlv_cast_<link_param_list,       tlv_<104> > tlv_link_parameters_status_list = {};
static const tlv_cast_<link_states_req,       tlv_<105> > tlv_link_states_req = {};
static const tlv_cast_<link_states_rsp_list,  tlv_<106> > tlv_link_states_rsp = {};
static const tlv_cast_<link_desc_req,         tlv_<107> > tlv_link_descriptor_req = {};
static const tlv_cast_<link_desc_rsp_list,    tlv_<108> > tlv_link_descriptor_rsp = {};
static const tlv_cast_<link_action,           tlv_<109> > tlv_link_action = {};
static const tlv_cast_<link_ac_result,        tlv_<110> > tlv_link_ac_result = {};
static const tlv_cast_<link_scan_rsp_list,    tlv_<111> > tlv_link_scan_rsp_list = {};
static const tlv_cast_<link_det_info,         tlv_<112> > tlv_link_det_info = {};
static const tlv_cast_<link_id,               tlv_<113> > tlv_interface_type_addr = {};
static const tlv_cast_<mos_dscv,              tlv_<114> > tlv_mos_dscv = {};


///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_TLV_TYPES__HPP_ */
