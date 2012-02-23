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


import java.util.Vector;
import lightMIHF.Bitmap16;
import lightMIHF.Bitmap32;
import lightMIHF.Bitmap64;
import odtone_java.inc.Common.Datatypes.UInt32;
import odtone_java.inc.Common.Datatypes.UInt8;
import odtone_java.inc.Common.Types.ID;
import odtone_java.inc.Common.Types.Information.Network_type;
import odtone_java.inc.Common.Types.Information.Network_type_addr;
import odtone_java.inc.Common.Types.Address.Link_Address;
import odtone_java.inc.Common.Types.Ipconfig.IP_Addr;
import odtone_java.inc.Common.Types.Link.Dev_States_RSP;
import odtone_java.inc.Common.Types.Link.Link_ID;
import odtone_java.inc.Common.Types.Link.Link_Res_Status;
import odtone_java.inc.Common.Types.Link.Link_Tuple_ID;
import odtone_java.inc.Common.Types.Link.Link_Type;
import odtone_java.inc.Common.Types.Link.Timer_Interval;
import odtone_java.inc.Common.Serialization;


/**
 *
 * @author marcelo lebre <marcelolebre@av.it.pt>
 *
 */
/**
 *
 * Class designed to serialize objects in TLV form
 *
 */
public class Tlv_Types {

    /**
     *
     * Serialization of source identifier
     *
     * @param ID
     * @return byte[]
     */
    public byte[] tlv_source_identifier(ID id) {

       Serialization srlz = new Serialization();

        return srlz.serialize_to_tlv(Tlv.tlv_source_id, id.get_ID());
    }

    /**
     *
     * Serialization of destination identifier
     *
     * @param ID
     * @return byte[]
     */
    public byte[] tlv_destination_identifier(ID id) {

        Serialization srlz = new Serialization();
        
        return srlz.serialize_to_tlv(Tlv.tlv_destination_id, id.get_ID());
    }

    /**
     *
     * Serialization of tlv link address list
     *
     * @param List<Network_type_addr>
     * @return byte[]
     */
    public byte[] tlv_link_address_list(Vector net_list) {
        Serialization srlz = new Serialization();
        Vector tmp = new Vector();
        //Transforming a List(NetworkTypeAddr) to a List(ByteArray) for encoding
        for (int i = 0; i < net_list.size(); i++) {
            tmp.addElement(((Network_type_addr)(net_list.elementAt(i))).get_Network_type_addr());
        }
        //Now encoding list
        byte[] tmp2 = srlz.encoding_List(tmp);
        //List encoded


        byte[] b_out = new byte[(srlz.serialize_to_tlv(Tlv.tlv_link_addr_list, tmp2)).length];
        b_out = srlz.serialize_to_tlv(Tlv.tlv_link_addr_list, tmp2);
        return b_out;
    }

    /**
     *
     * Serialization of supported mih event list
     *
     * @param Bitmap32
     * @return byte[]
     */
    public byte[] tlv_supported_mih_event_list(Bitmap32 mih_evt_list) {
        Serialization srlz = new Serialization();
        byte[] b_out = new byte[(srlz.serialize_to_tlv(Tlv.tlv_event_list, mih_evt_list.getValue())).length];
        b_out = srlz.serialize_to_tlv(Tlv.tlv_event_list, mih_evt_list.getValue());
        return b_out;
    }

    /**
     *
     * Serialization of supported mih command list
     *
     * @param Bitmap32
     * @return byte[]
     */
    public byte[] tlv_supported_mih_command_list(Bitmap32 mih_cmd_list) {
        Serialization srlz = new Serialization();
        byte[] b_out = new byte[(srlz.serialize_to_tlv(Tlv.tlv_command_list, mih_cmd_list.getValue())).length];
        b_out = srlz.serialize_to_tlv(Tlv.tlv_command_list, mih_cmd_list.getValue());
        return b_out;
    }

    /**
     *
     * Serialization of status tlv
     *
     * @param int
     * @return byte[]
     */
    public byte[] tlv_status(int status) {
        Serialization srlz = new Serialization();
        UInt8 status_array = new UInt8(status);
        byte[] b_out = new byte[(srlz.serialize_to_tlv(Tlv.tlv_status, status_array.getValue())).length];
        b_out = srlz.serialize_to_tlv(Tlv.tlv_status, status_array.getValue());
        return b_out;
    }

    /**
     *
     * Serialization of link identifier list
     *
     * @param List<Link_ID>
     * @return byte[]
     */
  

    /**
     *
     * Serialization of tlv_reg_request_code
     *
     * @param int
     * @return byte[]
     */
    public byte[] tlv_reg_request_code(int regrequestcode) {
        Serialization srlz = new Serialization();
        UInt8 regrequestcode_array = new UInt8(regrequestcode);
        byte[] b_out = new byte[(srlz.serialize_to_tlv(Tlv.tlv_reg_request_code, regrequestcode_array.getValue())).length];
        b_out = srlz.serialize_to_tlv(Tlv.tlv_reg_request_code, regrequestcode_array.getValue());
        return b_out;
    }

    /**
     *
     * Serialization of tlv_link_identifier
     *
     * @param Link_Tuple_ID
     * @return byte[]
     */
    public byte[] tlv_link_identifier(Link_Tuple_ID link_identifier) {
        Serialization srlz = new Serialization();
        byte[] b_out = new byte[(srlz.serialize_to_tlv(Tlv.tlv_link_identifier, link_identifier.get_Link_Tuple_ID())).length];
        b_out = srlz.serialize_to_tlv(Tlv.tlv_link_identifier, link_identifier.get_Link_Tuple_ID());
        return b_out;
    }

    /**
     *
     * Serialization of tlv_valid_time_interval
     *
     * @param UInt32
     * @return byte[]
     */
    public byte[] tlv_valid_time_interval(UInt32 time) {
        Serialization srlz = new Serialization();
        byte[] b_out = new byte[(srlz.serialize_to_tlv(Tlv.tlv_valid_time_interval, time.getValue())).length];
        b_out = srlz.serialize_to_tlv(Tlv.tlv_valid_time_interval, time.getValue());
        return b_out;
    }

    /**
     *
     * Serialization of tlv_requested_mih_event_list
     *
     * @param Bitmap32
     * @return byte[]
     */
    public byte[] tlv_requested_mih_event_list(Bitmap32 req_mih_evt_list) {
        Serialization srlz = new Serialization();
        byte[] b_out = new byte[(srlz.serialize_to_tlv(Tlv.tlv_event_list, req_mih_evt_list.getValue())).length];
        b_out = srlz.serialize_to_tlv(Tlv.tlv_event_list, req_mih_evt_list.getValue());
        return b_out;
    }
//    public byte [] tlv_event_configuration_info_list(byte [] evt_cfg_info_list){
//        serialization srlz = new serialization();
//        byte[] b_out = new byte[(srlz.serialize_to_tlv(tlv.tlv_evt_cfg_info_list, evt_cfg_info_list)).length];
//        b_out = srlz.serialize_to_tlv(tlv.tlv_evt_cfg_info_list, evt_cfg_info_list);
//        return b_out;
//    }

    /**
     *
     * Serialization of tlv_event_configuration_info_list
     *
     * @param EventConfigurationInfoList
     * @return byte[]
     */
    

    /**
     *
     * Serialization of tlv_response_mih_event_list
     *
     * @param Bitmap32
     * @return byte[]
     */
    public byte[] tlv_response_mih_event_list(Bitmap32 response_mih_evt_list) {
        Serialization srlz = new Serialization();
        byte[] b_out = new byte[(srlz.serialize_to_tlv(Tlv.tlv_event_list, response_mih_evt_list.getValue())).length];
        b_out = srlz.serialize_to_tlv(Tlv.tlv_event_list, response_mih_evt_list.getValue());
        return b_out;
    }

    /**
     *
     * Serialization of tlv_link_detected_info_list
     *
     * @param LinkDetectedInfoList
     * @return byte[]
     */
   

    /**
     *
     * Serialization of tlv_old_access_router
     *
     * @param Link_address
     * @return byte[]
     */
    public byte[] tlv_old_access_router(Link_Address lnkaddr) {

        Serialization srlz = new Serialization();
        byte[] b_out = new byte[(srlz.serialize_to_tlv(Tlv.tlv_old_access_router, lnkaddr.get_link_address())).length];
        b_out = srlz.serialize_to_tlv(Tlv.tlv_old_access_router, lnkaddr.get_link_address());
        return b_out;
    }

    /**
     *
     * Serialization of tlv_new_access_router
     *
     * @param Link_address
     * @return byte[]
     */
    public byte[] tlv_new_access_router(Link_Address lnkaddr) {

        Serialization srlz = new Serialization();
        byte[] b_out = new byte[(srlz.serialize_to_tlv(Tlv.tlv_new_access_router, lnkaddr.get_link_address())).length];
        b_out = srlz.serialize_to_tlv(Tlv.tlv_new_access_router, lnkaddr.get_link_address());
        return b_out;
    }

    /**
     *
     * Serialization of tlv_ip_renewal_flagr
     *
     * @param byte[]
     * @return byte[]
     */
    public byte[] tlv_ip_renewal_flagr(byte[] bool) {

        Serialization srlz = new Serialization();
        byte[] b_out = new byte[(srlz.serialize_to_tlv(Tlv.tlv_ip_renewal_flag, bool)).length];
        b_out = srlz.serialize_to_tlv(Tlv.tlv_ip_renewal_flag, bool);
        return b_out;
    }

    /**
     *
     * Serialization of tlv_ip_mob_mgmt
     *
     * @param Bitmap32
     * @return byte[]
     */
    public byte[] tlv_ip_mob_mgmt(Bitmap32 ipmobmgmt) {

        Serialization srlz = new Serialization();
        byte[] b_out = new byte[(srlz.serialize_to_tlv(Tlv.tlv_ip_mob_mgmt, ipmobmgmt.getValue())).length];
        b_out = srlz.serialize_to_tlv(Tlv.tlv_ip_mob_mgmt, ipmobmgmt.getValue());
        return b_out;
    }

    /**
     *
     * Serialization of tlv_link_parameter_report_list
     *
     * @param LinkParameterReportList
     * @return byte[]
     */
   

    /**
     *
     * Serialization of tlv_iq_type_lst
     *
     * @param Bitmap64
     * @return byte[]
     */
    public byte[] tlv_iq_type_lst(Bitmap64 iqTypeLst) {
        Serialization srlz = new Serialization();
        byte[] b_out = new byte[(srlz.serialize_to_tlv(Tlv.tlv_query_type_list, iqTypeLst.getValue())).length];
        b_out = srlz.serialize_to_tlv(Tlv.tlv_query_type_list, iqTypeLst.getValue());
        return b_out;
    }

    /**
     *
     * Serialization of tlv_trans_lst
     *
     * @param Bitmap16
     * @return byte[]
     */
    public byte[] tlv_trans_lst(Bitmap16 transpLst) {
        Serialization srlz = new Serialization();
        byte[] b_out = new byte[(srlz.serialize_to_tlv(Tlv.tlv_transport_option_list, transpLst.getValue())).length];
        b_out = srlz.serialize_to_tlv(Tlv.tlv_transport_option_list, transpLst.getValue());
        return b_out;
    }

    /**
     *
     * Serialization of tlv_mbb_handover_support
     *
     * @param MBBHandorverSupport
     * @return byte[]
     */
   

    /**
     *
     * Serialization of tlv_timer_interval
     *
     * @param Timer_Interval
     * @return byte[]
     */
    public byte[] tlv_timer_interval(Timer_Interval time) {

        Serialization srlz = new Serialization();
        byte[] b_out = new byte[(srlz.serialize_to_tlv(Tlv.tlv_time_interval, time.Timer_Interval.getValue())).length];
        b_out = srlz.serialize_to_tlv(Tlv.tlv_time_interval, time.Timer_Interval.getValue());
        return b_out;
    }

    /**
     *
     * Serialization of tlv_old_link_identifier
     *
     * @param Link_Tuple_ID
     * @return byte[]
     */
    public byte[] tlv_old_link_identifier(Link_Tuple_ID lnktplID) {
        Serialization srlz = new Serialization();
        byte[] b_out = new byte[(srlz.serialize_to_tlv(Tlv.tlv_link_identifier, lnktplID.get_Link_Tuple_ID())).length];
        b_out = srlz.serialize_to_tlv(Tlv.tlv_link_identifier, lnktplID.get_Link_Tuple_ID());
        return b_out;
    }

    /**
     *
     * Serialization of tlv_new_link_identifier
     *
     * @param Link_Tuple_ID
     * @return byte[]
     */
    public byte[] tlv_new_link_identifier(Link_Tuple_ID lnktplID) {
        Serialization srlz = new Serialization();
        byte[] b_out = new byte[(srlz.serialize_to_tlv(Tlv.tlv_new_link_identifier, lnktplID.get_Link_Tuple_ID())).length];
        b_out = srlz.serialize_to_tlv(Tlv.tlv_new_link_identifier, lnktplID.get_Link_Tuple_ID());
        return b_out;
    }

    /**
     *
     * Serialization of tlv_link_handover_status
     *
     * @param int
     * @return byte[]
     */
    public byte[] tlv_link_handover_status(int status) {
        Serialization srlz = new Serialization();
        UInt8 status_array = new UInt8(status);
        byte[] b_out = new byte[(srlz.serialize_to_tlv(Tlv.tlv_status, status_array.getValue())).length];
        b_out = srlz.serialize_to_tlv(Tlv.tlv_status, status_array.getValue());
        return b_out;
    }

    /**
     *
     * Serialization of tlv_device_states_request
     *
     * @param Bitmap16
     * @return byte[]
     */
    public byte[] tlv_device_states_request(Bitmap16 devstReq) {
        Serialization srlz = new Serialization();
        byte[] b_out = new byte[(srlz.serialize_to_tlv(Tlv.tlv_dev_states_req, devstReq.getValue())).length];
        b_out = srlz.serialize_to_tlv(Tlv.tlv_dev_states_req, devstReq.getValue());
        return b_out;
    }

    /**
     *
     * Serialization of tlv_link_status_request
     *
     * @param Link_Status_Req
     * @return byte[]
     */
    

    /**
     *
     * Serialization of tlv_device_states_rsp
     *
     * @param Dev_States_RSP
     * @return byte[]
     */
    public byte[] tlv_device_states_rsp(Dev_States_RSP devStatesRsp) {
        Serialization srlz = new Serialization();
        byte[] b_out = new byte[(srlz.serialize_to_tlv(Tlv.tlv_dev_states_rsp_list, devStatesRsp.get_Dev_States_Rsp())).length];
        b_out = srlz.serialize_to_tlv(Tlv.tlv_dev_states_rsp_list, devStatesRsp.get_Dev_States_Rsp());
        return b_out;
    }

    /**
     *
     * Serialization of tlv_get_status_response_list
     *
     * @param GetStatusResponseList
     * @return byte[]
     */
   

   /**
     *
     * Serialization of tlv_get_status_response_list
     *
     * @param GetStatusResponseList
     * @return byte[]
     */
    

    /**
     *
     * Serialization of tlv_configure_response_list
     *
     * @param List<Link_CFG_Status>
     * @return byte[]
     */
   
    /**
     *
     * Serialization of tlv_link_actions_list
     *
     * @param List<Link_Action_Req>
     * @return byte[]
     */
    

    /**
     *
     * Serialization of tlv_link_actions_result_list
     *
     * @param List<Link_Action_Rsp>
     * @return byte[]
     */
   

    /**
     *
     * Serialization of tlv_list_of_link_poa_list
     *
     * @param List<Link_PoA_List>
     * @return byte[]
     */
   

    /**
     *
     * Serialization of tlv_query_resource_report_flag
     *
     * @param boolean
     * @return byte[]
     */
    public byte[] tlv_query_resource_report_flag(boolean bool) {
        Serialization srlz = new Serialization();
        byte[] tmp;
        if (bool) {
            tmp = new byte[1];
            tmp[0] = 0x01;
        } else {
            tmp = new byte[1];
            tmp[0] = 0x00;
        }
        byte[] b_out = new byte[(srlz.serialize_to_tlv(Tlv.tlv_dev_states_rsp_list, tmp)).length];
        b_out = srlz.serialize_to_tlv(Tlv.tlv_dev_states_rsp_list, tmp);
        return b_out;
    }

    /**
     *
     * Serialization of tlv_handover_status
     *
     * @param HO_Status
     * @return byte[]
     */
    

    /**
     *
     * Serialization of tlv_preferred_link_list
     *
     * @param List<RQ_Result>
     * @return byte[]
     */
   

    /**
     *
     * Serialization of tlv_handover_resource_query_list
     *
     * @param QoS_List
     * @return byte[]
     */
   

    /**
     *
     * Serialization of tlv_ip_address_configuration_methods
     *
     * @param IP_Cfg_Mthds
     * @return byte[]
     */
    

    /**
     *
     * Serialization of tlv_dhcp_server_address
     *
     * @param IP_Addr
     * @return byte[]
     */
    public byte[] tlv_dhcp_server_address(IP_Addr ipaddr) {
        Serialization srlz = new Serialization();
        byte[] b_out = new byte[(srlz.serialize_to_tlv(Tlv.tlv_dhcp_server_addr, ipaddr.get_IP_Addr())).length];
        b_out = srlz.serialize_to_tlv(Tlv.tlv_dhcp_server_addr, ipaddr.get_IP_Addr());
        return b_out;
    }

    /**
     *
     * Serialization of tlv_fa_address
     *
     * @param IP_Addr
     * @return byte[]
     */
    public byte[] tlv_fa_address(IP_Addr ipaddr) {
        Serialization srlz = new Serialization();
        byte[] b_out = new byte[(srlz.serialize_to_tlv(Tlv.tlv_fa_addr, ipaddr.get_IP_Addr())).length];
        b_out = srlz.serialize_to_tlv(Tlv.tlv_fa_addr, ipaddr.get_IP_Addr());
        return b_out;
    }

    /**
     *
     * Serialization of tlv_access_router_address
     *
     * @param IP_Addr
     * @return byte[]
     */
    public byte[] tlv_access_router_address(IP_Addr ipaddr) {
        Serialization srlz = new Serialization();
        byte[] b_out = new byte[(srlz.serialize_to_tlv(Tlv.tlv_access_router_addr, ipaddr.get_IP_Addr())).length];
        b_out = srlz.serialize_to_tlv(Tlv.tlv_access_router_addr, ipaddr.get_IP_Addr());
        return b_out;
    }

    /**
     *
     * Serialization of tlv_resource_status
     *
     * @param Link_Res_Status
     * @return byte[]
     */
    public byte[] tlv_resource_status(Link_Res_Status linkRes) {
        Serialization srlz = new Serialization();
        byte[] b_out = new byte[(srlz.serialize_to_tlv(Tlv.tlv_resource_status, linkRes.Get_Link_Res_Status())).length];
        b_out = srlz.serialize_to_tlv(Tlv.tlv_resource_status, linkRes.Get_Link_Res_Status());
        return b_out;
    }

    /**
     *
     * Serialization of tlv_resource_status
     *
     * @param Link_Type
     * @return byte[]
     */
    public byte[] tlv_link_type(Link_Type type) {
        Serialization srlz = new Serialization();
        byte[] b_out = new byte[(srlz.serialize_to_tlv(Tlv.tlv_link_type, type.get_Link_Type())).length];
        b_out = srlz.serialize_to_tlv(Tlv.tlv_link_type, type.get_Link_Type());
        return b_out;
    }

    /**
     *
     * Serialization of tlv_target_network_info
     *
     * @param TGT_Net_Info
     * @return byte[]
     */
    

    /**
     *
     * Serialization of tlv_list_of_target_network_info
     *
     * @param List<TGT_Net_Info>
     * @return byte[]
     */
   

    /**
     *
     * Serialization of tlv_list_of_target_network_info
     *
     * @param Asgn_Res_Set
     * @return byte[]
     */
    

    /**
     *
     * Serialization of tlv_mobile_node_mihf_id
     *
     * @param ID
     * @return byte[]
     */
    public byte[] tlv_mobile_node_mihf_id(ID id) {
        Serialization srlz = new Serialization();
        byte[] b_out = new byte[(srlz.serialize_to_tlv(Tlv.tlv_mobile_node_mihf_id, id.get_ID())).length];
        b_out = srlz.serialize_to_tlv(Tlv.tlv_mobile_node_mihf_id, id.get_ID());
        return b_out;
    }

    /**
     *
     * Serialization of tlv_mn_link_id
     *
     * @param Link_ID
     * @return byte[]
     */

    public byte[] tlv_mn_link_id(Link_ID linkid) {
        Serialization srlz = new Serialization();
        byte[] b_out = new byte[(srlz.serialize_to_tlv(Tlv.tlv_mn_link_id, linkid.get_Value())).length];
        b_out = srlz.serialize_to_tlv(Tlv.tlv_mn_link_id, linkid.get_Value());
        return b_out;
    }

   /**
     *
     * Serialization of tlv_poa
     *
     * @param Link_address
     * @return byte[]
     */
    public byte[] tlv_poa(Link_Address linkadd) {
        Serialization srlz = new Serialization();
        byte[] b_out = new byte[(srlz.serialize_to_tlv(Tlv.tlv_poa, linkadd.get_link_address())).length];
        b_out = srlz.serialize_to_tlv(Tlv.tlv_poa, linkadd.get_link_address());
        return b_out;
    }

    /**
     *
     * Serialization of tlv_requested_resource_set
     *
     * @param Req_Res_Set
     * @return byte[]
     */
    

    /**
     *
     * Serialization of tlv_requested_resource_set
     *
     * @param HO_Result
     * @return byte[]
     */
    
    /**
     *
     * Serialization of tlv_resource_retention_status
     *
     * @param boolean
     * @return byte[]
     */
    public byte[] tlv_resource_retention_status(boolean bool) {
        Serialization srlz = new Serialization();
        byte[] tmp;
        if (bool) {
            tmp = new byte[1];
            tmp[0] = 0x01;
        } else {
            tmp = new byte[1];
            tmp[0] = 0x00;
        }
        byte[] b_out = new byte[(srlz.serialize_to_tlv(Tlv.tlv_resource_ret_status, tmp)).length];
        b_out = srlz.serialize_to_tlv(Tlv.tlv_resource_ret_status, tmp);
        return b_out;
    }

    /**
     *
     * Serialization of tlv_info_query_binary_data_list
     *
     * @param List<IQ_Bin_Data>
     * @return byte[]
     */
    
    /**
     *
     * Serialization of tlv_networ_type
     *
     * @param Network_type
     * @return byte[]
     */
    public byte[] tlv_networ_type(Network_type netType) {
        Serialization srlz = new Serialization();
        byte[] b_out = new byte[(srlz.serialize_to_tlv(Tlv.tlv_network_type, netType.get_network_type())).length];
        b_out = srlz.serialize_to_tlv(Tlv.tlv_network_type, netType.get_network_type());
        return b_out;
    }

    /**
     *
     * Serialization of tlv_unauthenticated_information_request
     *
     * @param boolean
     * @return byte[]
     */
    public byte[] tlv_unauthenticated_information_request(boolean bool) {
        Serialization srlz = new Serialization();
        byte[] tmp;
        if (bool) {
            tmp = new byte[1];
            tmp[0] = 0x01;
        } else {
            tmp = new byte[1];
            tmp[0] = 0x00;
        }
        byte[] b_out = new byte[(srlz.serialize_to_tlv(Tlv.tlv_unauthenticated_info_req, tmp)).length];
        b_out = srlz.serialize_to_tlv(Tlv.tlv_unauthenticated_info_req, tmp);
        return b_out;
    }

    /**
     *
     * Serialization of tlv_info_response_rdf_data_list
     *
     * @param List<IR_Rdf_Data>
     * @return byte[]
     */
   

    /**
     *
     * Serialization of tlv_info_response_RDF_schema_url_list
     *
     * @param List<IR_Schm_URL>
     * @return byte[]
     */
    

   /**
     *
     * Serialization of tlv_info_response_RDF_schema_list
     *
     * @param List<IR_Rdf_SCHM>
     * @return byte[]
     */
   

}
