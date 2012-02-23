//
// Copyright (c) 2009-2012 2012 Universidade Aveiro - Instituto de
// Telecomunicacoes Polo Aveiro
// This file is part of ODTONE - Open Dot Twenty One.
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//
// Author:     Marcelo Lebre <marcelolebre@av.it.pt>
//

package odtone_java.inc.Common.TLVHandler;

/**
 *
 * @author marcelo lebre <marcelolebre@av.it.pt>
 *
 */
/**
 *
 * Class represents TLV values
 *
 */
public class Tlv {
    /**
     *
     */
    public static final int tlv_access_router_addr                   = 35;
    /**
     *
     */
    public static final int tlv_assigned_resource_set                = 57;
    /**
     *
     */
    public static final int tlv_command_list                         = 6;
    /**
     *
     */
    public static final int tlv_destination_id                       = 2;
    /**
     *
     */
    public static final int tlv_dev_states_req                       = 24;
    /**
     *
     */
    public static final int tlv_dev_states_rsp_list                  = 26;
    /**
     *
     */
    public static final int tlv_dhcp_server_addr                     = 36;
    /**
     *
     */
    public static final int tlv_event_list                           = 5;
    /**
     *
     */
    public static final int tlv_evt_cfg_info_list                    = 54;
    /**
     *
     */
    public static final int tlv_execution_delay                      = 75;
    /**
     *
     */
    public static final int tlv_fa_addr                              = 37;
    /**
     *
     */
    public static final int tlv_get_sensor_states_request_set        = 70;
    /**
     *
     */
    public static final int tlv_get_sensor_status_response_list      = 71;
    /**
     *
     */
    public static final int tlv_get_status_req_set                   = 27;
    /**
     *
     */
    public static final int tlv_get_status_rsp_list                  = 28;
    /**
     *
     */
    public static final int tlv_ho_resource_query_list               = 33;
    /**
     *
     */
    public static final int tlv_ho_result                            = 40;
    /**
     *
     */
    public static final int tlv_ho_status                            = 34;
    /**
     *
     */
    public static final int tlv_info_query_bin_data_list             = 43;
    /**
     *
     */
    public static final int tlv_info_query_rdf_data_list             = 44;
    /**
     *
     */
    public static final int tlv_info_resp_bin_data_list              = 48;
    /**
     *
     */
    public static final int tlv_info_resp_rdf_data_list              = 49;
    /**
     *
     */
    public static final int tlv_info_resp_rdf_schem_list             = 51;
    /**
     *
     */
    public static final int tlv_info_resp_rdf_schem_url_list         = 50;
    /**
     *
     */
    public static final int tlv_ip_cfg_methods                       = 19;
    /**
     *
     */
    public static final int tlv_ip_mob_mgmt                          = 18;
    /**
     *
     */
    public static final int tlv_ip_renewal_flag                      = 17;
    /**
     *
     */
    public static final int tlv_iq_rdf_schema_list                   = 46;
    /**
     *
     */
    public static final int tlv_iq_rdf_schema_url                    = 45;
    /**
     *
     */
    public static final int tlv_link_action_list                     = 38;
    /**
     *ublic byte [] type(){}
//    public byte [] length(){}
//
//    public Info_Element() {
//    }
//
//    public Info_Element(InformationElement_ID ieID, L) {
//    }
     */
    public static final int tlv_link_action_rsp_list                 = 39;
    /**
     *
     */
    public static final int tlv_link_addr_list                       = 9;
    /**
     *
     */
    public static final int tlv_link_cfg_param_list                  = 29;
    /**
     *
     */
    public static final int tlv_link_cfg_status_list                 = 30;
    /**
     *
     */
    public static final int tlv_link_det_info_list                   = 58;
    /**
     *
     */
    public static final int tlv_link_dn_reason                       = 20;
    /**
     *
     */
    public static final int tlv_link_gd_reason                       = 22;
    /**
     *
     */
    public static final int tlv_link_id_list                         = 25;
    /**
     *
     */
    public static final int tlv_link_identifier                      = 13;
    /**
     *
     */
    public static final int tlv_link_param_rpt_list                  = 23;
    /**
     *
     */
    public static final int tlv_link_type                            = 4;
    /**
     *
     */
    public static final int tlv_list_of_link_poa_list                = 31;
    /**
     *
     */
    public static final int tlv_max_response_size                    = 47;
    /**
     *
     */
    public static final int tlv_mbb_ho_supp_list                     = 10;
    /**
     *
     */
    public static final int tlv_mn_link_id                           = 59;
    /**
     *
     */
    public static final int tlv_mobile_node_mihf_id                  = 52;
    /**
     *
     */
    public static final int tlv_network_type                         = 62;
    /**
     *
     */
    public static final int tlv_new_access_router                    = 16;
    /**
     *
     */
    public static final int tlv_new_link_identifier                  = 14;
    /**
     *
     */
    public static final int tlv_old_access_router                    = 15;
    /**
     *
     */
    public static final int tlv_poa                                  = 60;
    /**
     *
     */
    public static final int tlv_preferred_link_list                  = 32;
    /**
     *
     */
    public static final int tlv_query_res_report_flag                = 53;
    /**
     *
     */
    public static final int tlv_query_type_list                      = 7;
    /**
     *
     */
    public static final int tlv_reg_request_code                     = 11;
    /**
     *
     */
    public static final int tlv_request_resource_set                 = 63;

//  SENSOR TLV FROM HEREf

    /**
     *
     */
    public static final int tlv_requested_mih_sensor_event_list      = 65;
    /**
     *
     */
    public static final int tlv_resource_ret_status                  = 42;
    /**
     *
     */
    public static final int tlv_resource_status                      = 41;
    /**
     *
     */
    public static final int tlv_sensor_action                        = 74;
    /**
     *
     */
    public static final int tlv_sensor_configure_request_list        = 72;
    /**
     *
     */
    public static final int tlv_sensor_configure_response_list       = 73;
    /**
     *
     */
    public static final int tlv_sensor_device_states_request         = 69;
    /**
     *
     */
    public static final int tlv_sensor_event_configuration_info_list = 66;
    /**
     *
     */
    public static final int tlv_sensor_identifier                    = 64;
    /**
     *
     */
    public static final int tlv_sensor_identifier_list               = 68;
    /**
     *
     */
    public static final int tlv_sensor_parameter_report_list         = 67;
    /**
     *
     */
    public static final int tlv_source_id                            = 1;
    /**
     *
     */
    public static final int tlv_status                               = 3;
    /**
     *
     */
    public static final int tlv_target_network_info                  = 55;
    /**
     *
     */
    public static final int tlv_target_network_info_list             = 56;
    /**
     *
     */
    public static final int tlv_time_interval                        = 21;
    /**
     *
     */
    public static final int tlv_transport_option_list                = 8;
    /**
     *
     */
    public static final int tlv_unauthenticated_info_req             = 61;
    /**
     *
     */
    public static final int tlv_valid_time_interval                  = 12;

    public static final int link_param_type_list = 101;
    public static final int link_states_rsp_list = 104;
    public static final int link_desc_rsp_list = 106;
    public static final int link_param_list = 102;
    public static final int link_ac_result = 108;
}