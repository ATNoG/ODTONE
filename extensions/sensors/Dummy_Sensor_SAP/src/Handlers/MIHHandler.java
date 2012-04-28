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
package Handlers;

import java.util.Vector;
import java.util.logging.Level;
import java.util.logging.Logger;
import lightMIHF.Bitmap32;
import odtone_java.inc.Common.Datatypes.Octet_String;
import odtone_java.inc.Common.MessageHandler.MIH_Protocol_Header;
import odtone_java.inc.Common.MessageHandler.MIH_Protocol_Header.AID;
import odtone_java.inc.Common.MessageHandler.MIH_Protocol_Header.Opcode;
import odtone_java.inc.Common.MessageHandler.MIH_Protocol_Header.SID;
import odtone_java.inc.Common.MessageHandler.Payload;
import odtone_java.inc.Common.Serialization;
import odtone_java.inc.Common.TLVHandler.Tlv;
import odtone_java.inc.Common.Types.Address;
import odtone_java.inc.Common.Types.Address.Link_Address;
import odtone_java.inc.Common.Types.Address.Other_l2_ADDR;
import odtone_java.inc.Common.Types.Base;
import odtone_java.inc.Common.Types.Base.Status;
import odtone_java.inc.Common.Types.ID;
import odtone_java.inc.Common.Types.Link;
import odtone_java.inc.Common.Types.Link.Dev_States_RSP;
import odtone_java.inc.Common.Types.Link.Device_Info;
import odtone_java.inc.Common.Types.Link.Get_Status_Response_List;
import odtone_java.inc.Common.Types.Link.Link_AC_Result;
import odtone_java.inc.Common.Types.Link.Link_Desc_RSP;
import odtone_java.inc.Common.Types.Link.Link_ID;
import odtone_java.inc.Common.Types.Link.Link_Param;
import odtone_java.inc.Common.Types.Link.Link_Param_RPT;
import odtone_java.inc.Common.Types.Link.Link_Param_Sensor;
import odtone_java.inc.Common.Types.Link.Link_Param_Type;
import odtone_java.inc.Common.Types.Link.Link_Param_Val;
import odtone_java.inc.Common.Types.Link.Link_States_RSP;
import odtone_java.inc.Common.Types.Link.Link_Status_RSP;
import odtone_java.inc.Common.Types.Link.Link_Tuple_ID;
import odtone_java.inc.Common.Types.Link.Link_Type;
import odtone_java.inc.Common.Types.Link.Num_Queue;
import odtone_java.inc.Common.Types.Link.OP_MODE;
import odtone_java.inc.Common.Types.Link.Status_Response_Sequence;
import odtone_java.inc.mih_sap.Message.Confirm;
import odtone_java.inc.mih_sap.Message.Indication;
import odtone_java.inc.mih_sap.Message.Response;
import org.sunspotworld.Message;
import org.sunspotworld.Utils;

/**
 *
 * @author marcelo lebre <marcelolebre@av.it.pt>
 *
 */
public class MIHHandler extends Thread {

    String ipAddress;

    public MIHHandler(String ipAddress) {
        this.ipAddress = ipAddress;
    }
    public static int tid_subs = 0, tid_conf = 0;
    public Serialization srlz = new Serialization();
    public Octet_String source = new Octet_String("sensor_sap");
    public Octet_String destination = new Octet_String("mihf1");
    public ID sourceMIHID = new ID(source), destinationMIHID = new ID(destination);
    Tlv tlv = new Tlv();
    Response response = new Response();
    Confirm confirm = new Confirm();
    Indication indication = new Indication();
    byte[] message_21, msg;
    Message m = new Message();
    MIH_Protocol_Header mph = new MIH_Protocol_Header();
    AID aid = mph.new AID();
    SID sid = mph.new SID();
    int aid_case = 0, variable_payload_length;
    Base base = new Base();
    Status status_ = base.new Status(0);
    Integer sensor_up = new Integer(8);
    Integer paramReport = new Integer(3);
    Vector listforEventlist = new Vector(),
            linkParamRPTList = new Vector(),
            deviceStatesResponseList = new Vector(),
            linkStatesRspList = new Vector(),
            linkParamList = new Vector(),
            linkDescRsp = new Vector(),
            statusResponseSequenceList = new Vector();
    Bitmap32 linkEventList;
    Address address = new Address();
    Link link = new Link();
    Other_l2_ADDR ola = address.new Other_l2_ADDR(new Octet_String("sensoraddress"));
    Link_Address la = address.new Link_Address(ola);
    Link_Type lt = link.new Link_Type(30);
    Link_ID linkid = link.new Link_ID(lt, la);
    Link_Tuple_ID lti = link.new Link_Tuple_ID(linkid, null);
    Payload payload;
    Device_Info di = link.new Device_Info(new Octet_String("Full Spread"));
    Dev_States_RSP dsr = link.new Dev_States_RSP(di);
    Num_Queue nq = link.new Num_Queue(3);
    Link_Desc_RSP ldr = link.new Link_Desc_RSP(nq);
    Link_Status_RSP lsr;
    Status_Response_Sequence srs;
    Get_Status_Response_List gsrl;

    @Override
    public void run() {
        listforEventlist.add(paramReport);
        listforEventlist.add(sensor_up);
        linkEventList = new Bitmap32(listforEventlist);

        System.out.println("############################################");
        System.out.println("############ Dummy Sensor SAP ###############");
        System.out.println("############################################");


        while (true) {
            msg = m.receive(1235, this.ipAddress);
            int TID = new Utils(msg).getTID();
            System.out.println("Recebido:"+TID);


            switch (new Utils(msg).getAid()) {


                case AID.MIH_Event_Subscribe:

                    System.out.println("Sensor SAP received Event Subscribe.request");

                    payload = new Payload(sourceMIHID, destinationMIHID,
                            srlz.serialize_to_tlv(Tlv.tlv_status, status_.get_Status()),
                            srlz.serialize_to_tlv(Tlv.tlv_event_list, linkEventList.getValue()));

                    variable_payload_length = payload.Get_Payload().length;

                    mph.MID(SID.ServiceManagement, Opcode.Confirm, AID.MIH_Event_Subscribe);
                    mph.Set_MIH_Protocol_Header(1, false, false, false, false, 0, false, mph.MID, 0, TID, variable_payload_length);

                    message_21 = confirm.Event_Subscribe(mph, payload);

                    m.send(message_21, ipAddress, 1025);
                    System.out.println("Enviado:"+TID);
                    System.out.println("Sensor SAP sent Event Subscribe.confirm");
                    break;
                case AID.MIH_Link_Configure_Thresholds:
                    System.out.println("Sensor SAP received Configure Thresholds.request");

                    payload = new Payload(
                            sourceMIHID,
                            destinationMIHID,
                            srlz.serialize_to_tlv(Tlv.tlv_status, status_.get_Status()));

                    variable_payload_length = payload.Get_Payload().length;

                    mph.MID(SID.CommandService, Opcode.Confirm, AID.MIH_Link_Configure_Thresholds);
                    mph.Set_MIH_Protocol_Header(1, false, false, false, false, 0, false, mph.MID, 0, TID, variable_payload_length);

                    message_21 = confirm.Link_Configure_Thresholds(mph, payload);

                    m.send(message_21, ipAddress, 1025);
                    System.out.println("Enviado:"+TID);
                    System.out.println("Sensor SAP sent Configure Thresholds.confirm");
                    break;

                case AID.MIH_Link_Actions:
                    System.out.println("Sensor SAP received Link Actions.request");
                    if (new Utils(msg).getLinkAction() == 6) {
                        System.out.println("Performing Action: Doing something");
                        for (int i = 0; i < 1; i++) {
                            //Doing Something
                        }
                    } else {
                        System.out.println("Performing Action: Bad Action");
                    }
                    Link_AC_Result lacr = link.new Link_AC_Result(0);
                    payload = new Payload(sourceMIHID, destinationMIHID,
                            srlz.serialize_to_tlv(Tlv.tlv_status, status_.get_Status()),
                            srlz.serialize_to_tlv(Tlv.link_ac_result, lacr.get_Link_AC_Result()));

                    variable_payload_length = payload.Get_Payload().length;

                    mph.MID(SID.CommandService, Opcode.Confirm, AID.MIH_Link_Actions);
                    mph.Set_MIH_Protocol_Header(1, false, false, false, false, 0, false, mph.MID, 0, TID, variable_payload_length);

                    message_21 = confirm.Link_Actions(mph, payload);

                    m.send(message_21, ipAddress, 1025);
                    System.out.println("Enviado:"+TID);
                    System.out.println("Sensor SAP sent Link Actions.confirm");
                    try {
                        this.sleep(2000);
                    } catch (InterruptedException ex) {
                        Logger.getLogger(MIHHandler.class.getName()).log(Level.SEVERE, null, ex);
                    }

                    payload = new Payload(
                            sourceMIHID,
                            destinationMIHID,
                            srlz.serialize_to_tlv(Tlv.tlv_link_identifier, lti.get_Link_Tuple_ID()));

                    variable_payload_length = payload.Get_Payload().length;

                    mph.MID(
                            SID.EventService,
                            Opcode.Indication,
                            AID.MIH_Sensor_UP);

                    mph.Set_MIH_Protocol_Header(
                            1, false, false, false,
                            false, 0, false, mph.MID, 0, tid_subs,
                            variable_payload_length);

                    message_21 = indication.Sensor_Up(mph, payload);

                    m.send(message_21, ipAddress, 1025);
                    System.out.println("Enviado:"+TID);
                    System.out.println("Sensor SAP sent MIH Sensor UP.Indication");

                    Link_Param_Sensor lps = link.new Link_Param_Sensor(30);
                    Link_Param_Type lptype = link.new Link_Param_Type(lps);
                    Link_Param_Val lpv = link.new Link_Param_Val(123);
                    Link_Param lp = link.new Link_Param(lptype, lpv);
                    Link_Param_RPT lprt = link.new Link_Param_RPT(lp, null);

                    linkParamRPTList.add(lprt.get_link_param_rpt());

                    payload = new Payload(
                            sourceMIHID,
                            destinationMIHID,
                            srlz.serialize_to_tlv(Tlv.tlv_link_identifier, lti.get_Link_Tuple_ID()),
                            srlz.serialize_to_tlv(Tlv.tlv_link_param_rpt_list, srlz.encoding_List(linkParamRPTList)));
//                  
                    variable_payload_length = payload.Get_Payload().length;

                    mph.MID(
                            SID.EventService,
                            Opcode.Indication,
                            AID.MIH_Link_Parameters_Report);

                    mph.Set_MIH_Protocol_Header(
                            1, false, false, false,
                            false, 0, false, mph.MID,
                            0, tid_conf, variable_payload_length);

                    message_21 = new byte[response.MIH_Event_Subscribe(mph, payload).length];
                    message_21 = indication.Link_Parameters_Report(mph, payload);


                    new Message().send(message_21, ipAddress, 1025);
                    System.out.println("Enviado:"+TID);
                    System.out.println("Sensor SAP sent MIH Link Parameters Report.Indication");
                    break;

                case AID.MIH_Link_Get_Parameters:
                    if (new Utils(msg).getSid() == SID.CommandService) {
                        System.out.println("Sensor SAP received Link Get Parameters.request");

                        Link_Param_Sensor lps1 = link.new Link_Param_Sensor(0);


                        Link_Param_Type lptype1 = link.new Link_Param_Type(lps1);
                        Link_Param_Val lpv1 = link.new Link_Param_Val(77);
                        Link_Param lp1 = link.new Link_Param(lptype1, lpv1);

                        OP_MODE om = link.new OP_MODE(0);
                        Link_States_RSP lstatesr = link.new Link_States_RSP(om);
                        linkStatesRspList.add(lstatesr.get_Link_States_RSP());

                        linkParamList.add(lp1.get_Link_Param());
                        linkDescRsp.add(ldr.get_Link_Desc_RSPP());

                        payload = new Payload(
                                sourceMIHID,
                                destinationMIHID,
                                srlz.serialize_to_tlv(Tlv.tlv_status, status_.get_Status()),
                                srlz.serialize_to_tlv(Tlv.link_param_list, srlz.encoding_List(linkParamList)),
                                srlz.serialize_to_tlv(Tlv.link_states_rsp_list, srlz.encoding_List(linkStatesRspList)),
                                srlz.serialize_to_tlv(Tlv.link_desc_rsp_list, srlz.encoding_List(linkDescRsp)));

                        variable_payload_length = payload.Get_Payload().length;

                        mph.MID(
                                SID.CommandService,
                                Opcode.Confirm,
                                AID.MIH_Link_Get_Parameters);

                        mph.Set_MIH_Protocol_Header(
                                1, false, false, false, false, 0,
                                false, mph.MID, 0, TID,
                                variable_payload_length);

                        message_21 = confirm.MIH_Link_Get_Parameters(mph, payload);
                        System.out.println("Enviado:"+TID);
                        m.send(message_21, ipAddress, 1025);
                        System.out.println("Sensor SAP sent Link Get Parameters.confirm");
                    }
                    break;
                default:
                    break;

            }
        }
    }
}
