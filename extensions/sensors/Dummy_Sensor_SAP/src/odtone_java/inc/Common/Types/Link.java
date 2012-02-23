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
package odtone_java.inc.Common.Types;

import java.util.Vector;
import lightMIHF.Bitmap16;
import lightMIHF.Bitmap32;
import lightMIHF.Bitmap64;
import odtone_java.inc.Common.Datatypes.Bitmap8;
import odtone_java.inc.Common.Datatypes.Octet_String;
import odtone_java.inc.Common.Datatypes.UInt16;
import odtone_java.inc.Common.Datatypes.UInt32;
import odtone_java.inc.Common.Datatypes.UInt8;
import odtone_java.inc.Common.Types.Address.Link_Address;
import odtone_java.inc.Common.Types.Base.Percentage;
import odtone_java.inc.Common.Serialization;

/**
 *
 * @author marcelo lebre <marcelolebre@av.it.pt>
 *
 */
/**
 *
 * Class designed to construct a link object
 * This class nests objects related to the link between the entities
 *
 */
public class Link {

    /**
     *
     * Class designed to construct a Link_Res_Status object
     *
     */
    public class Link_Res_Status {

        byte[] link_res_status;

        /**
         * Constructor
         * @param boolean
         */
        public Link_Res_Status(boolean bool) {
            link_res_status = new byte[1];
            if (bool) {
                link_res_status[0] = 0x01;
            } else {
                link_res_status[0] = 0x00;
            }

        }

        /**
         * Getter - Returns the Link Res Status
         * @return byte []
         */
        public byte[] Get_Link_Res_Status() {
            return link_res_status;
        }
    }

    /**
     *
     * Class designed to construct a Link_PoA_List object
     *
     */
    public class Link_PoA_List {

        byte[] link_poa_list;

        /**
         * Constructor
         * @param linkid
         * @param linkAddressList
         */
        public Link_PoA_List(Link_ID linkid, Vector linkAddressList) {
            Serialization srlz = new Serialization();
            Vector tmp1 = new Vector();

            for (int i = 0; i < linkAddressList.size(); i++) {
                tmp1.addElement(((Link_Address) linkAddressList.elementAt(i)).get_link_address());
            }
            byte[] tmp;
            tmp = new byte[srlz.encoding_List(tmp1).length];
            tmp = srlz.encoding_List(tmp1);

            link_poa_list = new byte[srlz.sequence(linkid.get_Value(), tmp).length];
            link_poa_list = srlz.sequence(linkid.get_Value(), tmp);
        }

        /**
         * Getter - Returns the Link PoA List in byte[] form
         * @return byte[]
         */
        public byte[] get_Link_PoA_List() {
            return link_poa_list;
        }
    }

    /**
     *
     * Class designed to construct a Link_Action_Rsp object
     *
     */
    public class Link_Action_Rsp {

        byte[] link_action_rsp;

        /**
         * Constructor
         * @param linkid
         * @param linkacResult
         */
        public Link_Action_Rsp(Link_ID linkid, Link_AC_Result linkacResult) {
            Serialization srlz = new Serialization();
            byte[] tmp = new byte[srlz.choice(null, 0).length];
            tmp = srlz.choice(null, 0);

            link_action_rsp = new byte[srlz.sequence(linkid.get_Value(), linkacResult.get_Link_AC_Result(), tmp).length];
            link_action_rsp = srlz.sequence(linkid.get_Value(), linkacResult.get_Link_AC_Result(), tmp);
        }

        /**
         * Constructor
         * @param Link_ID
         * @param Link_AC_Result
         * @param List<Link_Scan_Rsp>
         */
        /**
         * Getter - Return Link Action Rsp in byte[] form
         * @return byte []
         */
        public byte[] get_Link_Action_Rsp() {
            return link_action_rsp;
        }
    }

    /**
     *
     * Class designed to construct a Link_AC_Result object
     *
     */
    public class Link_AC_Result {

        /**
         *
         */
        public static final int SUCCESS = 0;
        /**
         *
         */
        public static final int FAILURE = 1;
        /**
         *
         */
        public static final int REFUSED = 2;
        /**
         *
         */
        public static final int INCAPABLE = 3;
        UInt8 link_ac_result;

        /**
         * Constructor
         * @param int
         */
        public Link_AC_Result(int linkresult) {
            link_ac_result = new UInt8(linkresult);
        }

        /**
         * Getter - Return Link AC Result in byte[] form
         * @return byte[]
         */
        public byte[] get_Link_AC_Result() {
            return link_ac_result.getValue();
        }
    }

    /**
     *
     * Class designed to construct a Link_Scan_Rsp object
     *
     */
    public class Link_Scan_Rsp {

        byte[] link_scan_rsp;

        /**
         * Constructor
         * @param Link_address
         * @param Network_ID
         * @param Sig_Strength
         */
        public Link_Scan_Rsp(Link_Address linkaddr, Network_ID netID, Sig_Strength sigstrength) {
            Serialization srlz = new Serialization();
            link_scan_rsp = new byte[srlz.sequence(linkaddr.get_link_address(), netID.get_Network_ID(), sigstrength.get_Sig_Strength()).length];
            link_scan_rsp = srlz.sequence(linkaddr.get_link_address(), netID.get_Network_ID(), sigstrength.get_Sig_Strength());
        }

        /**
         * Getter - Return Link Scan Rsp value in byte []
         * @return byte[]
         */
        public byte[] get_Link_Scan_Rsp() {
            return link_scan_rsp;
        }
    }

    /**
     *
     * Class designed to construct a Link_Action_Req object
     *
     */
    /**
     *
     * Class designed to construct a Link_Action object
     *
     */
    /**
     *
     * Class designed to construct a Link_AC_Attr object
     *
     */
    /**
     *
     * Class designed to construct a Link_AC_Type object
     *
     */
    public class Link_AC_Type {

        /**
         *
         */
        public static final int NONE = 0;
        /**
         *
         */
        public static final int LINK_DISCONNECT = 1;
        /**
         *
         */
        public static final int LINK_LOW_POWER = 2;
        /**
         *
         */
        public static final int LINK_POWER_DOWN = 3;
        /**
         *
         */
        public static final int LINK_POWER_UP = 4;
        UInt8 link_ac_type;

        /**
         * Constructor
         * @param int
         */
        public Link_AC_Type(int linkACType) {
            link_ac_type = new UInt8(linkACType);
        }

        /**
         * Getter - Return the Link AC TYpe value in byte [] form
         * @return byte[]
         */
        public byte[] get_Link_AC_Type() {
            return link_ac_type.getValue();
        }
    }

    /**
     *
     * Class designed to construct a Link_AC_EX_Time object
     *
     */
    public class Link_AC_EX_Time {

        UInt16 link_ac_ex_time;

        /**
         *Constructor
         * @param int
         */
        public Link_AC_EX_Time(int laet) {
            link_ac_ex_time = new UInt16(laet);
        }

        /**
         * Getter - Returns the Link AC EX Time value in byte[] form
         * @return byte []
         */
        public byte[] get_Link_AC_EX_Time() {
            return link_ac_ex_time.getValue();
        }
    }

    /**
     *
     * Class designed to construct a Link_CFG_Status object
     *
     */
    public class Link_CFG_Status {

        byte[] link_cfg_status;

        /**
         * Constructor
         * @param Link_Param_Type
         * @param Threshold
         * @param Config_Status
         */
        public Link_CFG_Status(Link_Param_Type lnkParamType, Threshold threshold, Config_Status cfgStatus) {
            Serialization srlz = new Serialization();

            link_cfg_status = new byte[srlz.sequence(lnkParamType.get_Link_Param_Type(), threshold.get_Threshold(), cfgStatus.get_Config_Status()).length];
            link_cfg_status = srlz.sequence(lnkParamType.get_Link_Param_Type(), threshold.get_Threshold(), cfgStatus.get_Config_Status());
        }

        /**
         * Getter - Return the Link CFG Status in byte[] form
         * @return byte[]
         */
        public byte[] Get_Link_CFG_Status() {
            return link_cfg_status;
        }
    }

    /**
     *
     * Class designed to construct a Config_Status object
     *
     */
    public class Config_Status {

        byte[] config_status;

        /**
         * Constructor
         * @param boolean
         */
        public Config_Status(boolean bool) {
            config_status = new byte[1];
            if (bool) {
                config_status[0] = (byte) 0x01;
            } else {
                config_status[0] = (byte) 0x00;
            }
        }

        /**
         * Getter - Return the Config Status in byte [] form
         * @return byte[]
         */
        public byte[] get_Config_Status() {
            return config_status;
        }
    }

    /**
     *
     * Class designed to construct a GetStatusResponseList object
     *
     */
    public class Get_Status_Response_List {

        public byte[] getstatusresponselist;
        Serialization srlz = new Serialization();

        public Get_Status_Response_List() {
        }

        public Get_Status_Response_List(Vector status_response_sequence) {
            getstatusresponselist = new byte[srlz.encoding_List(status_response_sequence).length];
            getstatusresponselist = srlz.encoding_List(status_response_sequence);
        }

        public byte[] get_Status_Response_List() {
            return getstatusresponselist;
        }
    }

    /**
     *
     * Class designed to construct a GetStatusResponseSequence object
     *
     */
    public class Status_Response_Sequence {

        byte[] status_response_sequence;
        Serialization srlz = new Serialization();

        public Status_Response_Sequence() {
        }

        public Status_Response_Sequence(Link_ID link_id, Link_Status_RSP link_status_rsp) {
            status_response_sequence = new byte[srlz.sequence(link_id.get_Value(), link_status_rsp.get_Link_Status_Rsp()).length];
            status_response_sequence = srlz.sequence(link_id.get_Value(), link_status_rsp.get_Link_Status_Rsp());
        }

        public byte[] get_status_response_sequence() {
            return status_response_sequence;
        }
    }

    /**
     *
     * Class designed to construct a Link_Status_RSP object
     *
     */
    public class Link_Status_RSP {

        byte[] link_status_rsp;
        Serialization srlz = new Serialization();

        public Link_Status_RSP() {
        }

        public Link_Status_RSP(Vector link_States_Rsp_List, Vector link_Param_List, Vector link_Desc_Rsp_List) {

            link_status_rsp = new byte[
                    srlz.sequence(srlz.encoding_List(link_States_Rsp_List),
                                    srlz.encoding_List(link_Param_List),
                                    srlz.encoding_List(link_States_Rsp_List))
                                 .length];
            link_status_rsp = srlz.sequence(srlz.encoding_List(link_States_Rsp_List), srlz.encoding_List(link_Param_List), srlz.encoding_List(link_States_Rsp_List));
        }

        public byte[] get_Link_Status_Rsp() {
            return link_status_rsp;
        }
    }

    /**
     *
     * Class designed to construct a Link_Desc_RSP object
     *
     */
    public class Link_Desc_RSP {

        byte[] link_desc_rsp;

        /**
         * Constructor
         * @param Num_Cos
         */
        public Link_Desc_RSP(Num_Cos numcos) {
            Serialization srlz = new Serialization();
            link_desc_rsp = new byte[srlz.choice(numcos.get_Num_Cos(), -1).length];
            link_desc_rsp = srlz.choice(numcos.get_Num_Cos(), 0);
        }

        /**
         * Constructor
         * @param Num_Queue
         */
        public Link_Desc_RSP(Num_Queue numqueue) {
            Serialization srlz = new Serialization();
            link_desc_rsp = new byte[srlz.choice(numqueue.get_Num_Queue(), 0).length];
            link_desc_rsp = srlz.choice(numqueue.get_Num_Queue(), 1);
        }

        /**
         * Getter- Returns Link Desc RSPP in byte[] form
         * @return byte []
         */
        public byte[] get_Link_Desc_RSPP() {
            return link_desc_rsp;
        }
    }

    /**
     *
     * Class designed to construct a Link_States_RSP object
     *
     */
    public class Link_States_RSP {

        byte[] link_states_rsp;

        /**
         * Constructor
         * @param OP_MODE
         */
        public Link_States_RSP(OP_MODE opmode) {
            Serialization srlz = new Serialization();
            link_states_rsp = new byte[srlz.choice(opmode.get_OP_MODE(), -1).length];
            link_states_rsp = srlz.choice(opmode.get_OP_MODE(), -1);
        }

        /**
         * Constructor
         * @param CHANNEL_ID
         */
        public Link_States_RSP(CHANNEL_ID channelid) {
            Serialization srlz = new Serialization();
            link_states_rsp = new byte[srlz.choice(channelid.get_CHANNEL_ID(), 0).length];
            link_states_rsp = srlz.choice(channelid.get_CHANNEL_ID(), 0);
        }

        /**
         * Getter - Return the link states rsp in byte[] form
         * @return byte []
         */
        public byte[] get_Link_States_RSP() {
            return link_states_rsp;
        }
    }

    /**
     *
     * Class designed to construct a OP_MODE object
     *
     */
    public class OP_MODE {

        /**
         *
         */
        public static final int NORMAL_MODE = 0;
        /**
         *
         */
        public static final int POWER_SAVING_MODE = 1;
        /**
         *
         */
        public static final int POWERED_DOWN = 2;
        UInt8 opmode;

        /**
         * Construct
         * @param int
         */
        public OP_MODE(int mode) {
            opmode = new UInt8(mode);
        }

        /**
         * Getter - Return OP_MODE in byte[] form
         * @return byte[]
         */
        public byte[] get_OP_MODE() {
            return opmode.getValue();
        }
    }

    /**
     *
     * Class designed to construct a CHANNEL_ID object
     *
     */
    public class CHANNEL_ID {

        UInt16 channelID;

        /**
         * COnstructor
         * @param int
         */
        public CHANNEL_ID(int id) {
            channelID = new UInt16(id);
        }

        /**
         * Getter - Return CHANNEL_ID in byte[] form
         * @return byte[]
         */
        public byte[] get_CHANNEL_ID() {
            return channelID.getValue();
        }
    }

    /**
     *
     * Class designed to construct a Num_Cos object
     *
     */
    public class Num_Cos {

        UInt8 numcos;

        /**
         * Constructor
         * @param int
         */
        public Num_Cos(int num) {
            numcos = new UInt8(num);
        }

        /**
         * Getter - Returns Num Cos in byte[] form
         * @return byte[]
         */
        public byte[] get_Num_Cos() {
            return numcos.getValue();
        }
    }

    /**
     *
     * Class designed to construct a Num_Queue object
     *
     */
    public class Num_Queue {

        UInt8 numqueue;

        /**
         * Constructor
         * @param int
         */
        public Num_Queue(int num) {
            numqueue = new UInt8(num);
        }

        /**
         * Getter - Returns Num Queue value in byte[] form
         * @return byte[]
         */
        public byte[] get_Num_Queue() {
            return numqueue.getValue();
        }
    }

    /**
     *
     * Class designed to construct a Dev_States_RSP object
     *
     */
    public class Dev_States_RSP {

        byte[] dev_states_rsp;

        /**
         * Constructor
         * @param Device_Info
         */
        public Dev_States_RSP(Device_Info deviceinfo) {
            Serialization srlz = new Serialization();
            dev_states_rsp = new byte[srlz.choice(deviceinfo.get_Device_Info().getValue(), 0).length];
            dev_states_rsp = srlz.choice(deviceinfo.get_Device_Info().getValue(), 0);
        }

        public Dev_States_RSP(byte[] in) {
            dev_states_rsp = new byte[in.length];
            dev_states_rsp = in;

        }

        /**
         * Constructor
         * @param Batt_Level
         */
        public Dev_States_RSP(Batt_Level level) {
            Serialization srlz = new Serialization();
            byte[] tmp = new byte[1];
            tmp[0] = (byte) level.get_Batt_Level();
            dev_states_rsp = new byte[srlz.choice(tmp, 1).length];
            dev_states_rsp = srlz.choice(tmp, 1);
        }

        /**
         * Getter - Returns Dev States Rsp valuein byte[] form
         * @return byte[]
         */
        public byte[] get_Dev_States_Rsp() {
            return dev_states_rsp;
        }
    }

    /**
     *
     * Class designed to construct a Device_Info object
     *
     */
    public class Device_Info {

        Octet_String device_info;

        /**
         * Constructor Device_Info
         * @param Octet_String
         */
        public Device_Info(Octet_String os) {
            device_info = new Octet_String(os);

        }

        /**
         * Getter -  Returns Device Info value in byte[] value
         * @return byte []
         */
        public Octet_String get_Device_Info() {
            return device_info;
        }
    }

    /**
     *
     * Class designed to construct a Batt_Level object
     *
     */
    public class Batt_Level {

        int batt_level;

        /**
         * Constructor
         * @param int
         */
        public Batt_Level(int level) {
            if (level < -1 | level > 100) {
                throw new IllegalArgumentException("Battery level out of bounds [-1;100]");
            } else {
                batt_level = level;
            }

        }

        /**
         *Getter - Returns Batt Level value in byte[] form
         * @return byte[]
         */
        public int get_Batt_Level() {
            return batt_level;
        }
    }

    /**
     *
     * Class designed to construct a Link_Status_Req object
     *
     */
    /**
     *
     * Class designed to construct a Link_Desc_Req object
     *
     */
    /**
     *
     * Class designed to construct a Link_States_Req object
     *
     */
    /**
     *
     * Class designed to construct a DEV_STATES_REQ object
     *
     */
    public class DEV_STATES_REQ {

        /**
         *
         */
        public static final int DEVICE_INFO = 0;
        /**
         *
         */
        public static final int BATT_LEVEl = 1;
        Bitmap16 dev_states_req;

        /**
         * Constructor
         * @param List<Integer>
         */
        /**
         * Getter - Returns DEV States Req value in byte [] form
         * @return byte []
         */
        public byte[] get_DEV_STATES_REQ() {
            return dev_states_req.getValue();
        }
    }

    /**
     *
     * Class designed to construct a Link_GD_Reason object
     *
     */
    public class Link_GD_Reason {

        /**
         *
         */
        public static final int EXPLICIT_DISCONNECT = 0;
        /**
         *
         */
        public static final int LINK_PARAMETER_DEGRADING = 1;
        /**
         *
         */
        public static final int LOW_POWER = 2;
        /**
         *
         */
        public static final int NO_RESOURCE = 3;
        UInt8 link_gd_reason;

        /**
         * Constructor
         * @param int
         */
        public Link_GD_Reason(int value) {
            link_gd_reason = new UInt8(value);

        }

        /**
         * Getter - Returns Link GD Reason value in byte[] form
         * @return byte []
         */
        public byte[] get_Link_GD_Reason() {
            return link_gd_reason.getValue();
        }
    }

    /**
     *
     * Class designed to construct a Link_Param_RPT object
     *
     */
    public class Link_Param_RPT {

        byte[] link_param_rpt;
        Serialization srlz = new Serialization();

        public Link_Param_RPT() {
        }

        public Link_Param_RPT(Link_Param lp, Threshold thr) {
            if (thr == null) {
                link_param_rpt = new byte[srlz.sequence(lp.get_Link_Param(), srlz.choice(null, -1)).length];
                link_param_rpt = srlz.sequence(lp.get_Link_Param(), srlz.choice(null, -1));
            } else {
                link_param_rpt = new byte[srlz.sequence(lp.get_Link_Param(), srlz.choice(thr.get_Threshold(), 0)).length];
                link_param_rpt = srlz.sequence(lp.get_Link_Param(), srlz.choice(thr.get_Threshold(), 0));
            }
        }

        public byte[] get_link_param_rpt() {
            return link_param_rpt;
        }
    }

    /**
     *
     * Class designed to construct a Link_Param object
     *
     */
    public class Link_Param {

        byte[] link_param;
        Serialization srlz = new Serialization();

        public Link_Param() {
        }

        public Link_Param(Link_Param_Type lpt, Link_Param_Val lpv) {

            link_param = new byte[srlz.sequence(lpt.get_Link_Param_Type(), srlz.choice(lpv.get_Link_Param_Val(),-1)).length];
            link_param = srlz.sequence(lpt.get_Link_Param_Type(), srlz.choice(lpv.get_Link_Param_Val(), -1));
        }

        public byte[] get_Link_Param() {
            return link_param;
        }
    }

    /**
     *
     * Class designed to construct a Link_Param_Val object
     *
     */
    public class Link_Param_Val {

        UInt16 link_param_val;

        /**
         * Constructor
         * @param int
         */
        public Link_Param_Val(int val) {
            link_param_val = new UInt16(val);
        }

        /**
         * Getter - Returns Link Param Val value in byte[] form
         * @return byte[]
         */
        public byte[] get_Link_Param_Val() {
            return link_param_val.getValue();
        }
    }

    /**
     *
     * Class designed to construct a Link_DN_REASON object
     *
     */
    public class Link_DN_REASON {

        UInt8 link_dn_reason;
        /**
         *
         */
        public static final int EXPLICIT_DISCONNECT = 0;
        /**
         *
         */
        public static final int PACKET_TIMEOUT = 1;
        /**
         *
         */
        public static final int NO_RESOURCE = 2;
        /**
         *
         */
        public static final int NO_BROADCAST = 3;
        /**
         *
         */
        public static final int AUTHENTICATION_FAILURE = 4;
        /**
         *
         */
        public static final int BILLING_FAILURE = 5;

        /**
         * Constructor
         * @param int
         */
        public Link_DN_REASON(int reason) {
            link_dn_reason = new UInt8(reason);
        }

        /**
         * Getter - Returns Link_DN_REASON value in UInt8 form
         * @return UInt8
         */
        public UInt8 Link_DN_REASON() {
            return link_dn_reason;
        }
    }

    /**
     *
     * Class designed to construct a LinkDetectedInfoList object
     *
     */
    /**
     *
     * Class designed to construct a Link_DET_INFO object
     *
     */
    /**
     *
     * Class designed to construct a Net_Caps object
     *
     */
    /**
     *
     * Class designed to construct a Link_MIHCAP_Flag object
     *
     */
    public class Link_MIHCAP_Flag {

        /**
         *
         */
        public static final int Link_MIHCAP_Flag_Event_Service_Supported = 1;
        /**
         *
         */
        public static final int Link_MIHCAP_Flag_Command_Service_Supported = 2;
        /**
         *
         */
        public static final int Link_MIHCAP_Flag_Information_Service_Supported = 3;
        Bitmap8 link_mihcap_flag;

        /**
         * Constructor
         * @param List<Integer>
         */
        /**
         * Getter- Returns Link MIHCAP flag value in byte[] form
         * @return byte []
         */
        public Bitmap8 get_Link_MIHCAP_Flag() {
            return link_mihcap_flag;
        }
    }

    /**
     *
     * Class designed to construct a SINR object
     *
     */
    public class SINR {

        UInt16 sinr;

        /**
         * Constructor
         * @param UInt16
         */
        public SINR(UInt16 s) {
            sinr = new UInt16(s);

        }

        /**
         * Getter - Returns SINR value in byte[] form
         * @return
         */
        public byte[] get_SINR() {
            return sinr.getValue();
        }
    }

    /**
     *
     * Class designed to construct a Net_aux_id object
     *
     */
    public class Net_aux_id {

        byte[] net_aux_id;

        /**
         * Constructor
         * @param Octet_String
         */
        public Net_aux_id(Octet_String os) {
            net_aux_id = new byte[os.getValue().length];
            net_aux_id = os.getValue();

        }

        /**
         * Getter - Return Net aux id value in byte[] form
         * @return byte []
         */
        public byte[] get_Net_Aux_Id() {
            return net_aux_id;
        }

        public String get_Net_Aux_ID() {
            return (new String(net_aux_id));
        }

        public void set_Net_Aux_ID(byte[] in) {
            net_aux_id = new byte[in.length];
            net_aux_id = in;
        }
    }

    /**
     *
     * Class designed to construct a EventConfigurationInfoList object
     *
     */
    public class EventConfigurationInfoList {

        /**
         *
         */
        public byte[] eventconfigurationinfolist;
        /**
         *
         */
        public Vector _eventconfigurationinfolist;

        /**
         * Constructor
         * @param List<Evt_CFG_INFO>
         */
        public EventConfigurationInfoList(Vector lst) {
            _eventconfigurationinfolist = lst;
            byte[] tmp;
            Vector tmp1 = new Vector();
            Serialization srlz = new Serialization();
            for (int i = 0; i < lst.size(); i++) {
                tmp1.addElement(((Evt_CFG_INFO) lst.elementAt(i)).get_Evt_CFG_INFO());
            }

            tmp = new byte[srlz.encoding_List(tmp1).length];
            tmp = srlz.encoding_List(tmp1);
            eventconfigurationinfolist = new byte[tmp.length];
            eventconfigurationinfolist = tmp;
        }

        /**
         * Getter - Returns EVENT CONFIGURATIONINFOLIST value in byte[] form
         * @return byte[]
         */
        public Vector get_EventConfigurationInfoList() {
            return _eventconfigurationinfolist;
        }
    }

    /**
     *
     * Class designed to construct a Evt_CFG_INFO object
     *
     */
    public class Evt_CFG_INFO {

        /**
         *
         */
        public byte[] evt_cfg_info;
        /**
         *
         */
        public static final int Link_DET_CFG_CHOICE = 0;
        /**
         *
         */
        public static final int Link_CFG_PARAM_CHOICE = 1;

        /**
         * Constructor
         * @param List
         * @param int
         */
        /**
         * Getter - Returns EVT_CFG_INFO value in byte[]
         * @return byte[]
         */
        public byte[] get_Evt_CFG_INFO() {
            return evt_cfg_info;
        }
    }

    /**
     *
     * Class designed to construct a Link_CFG_PARAM object
     *
     */
    public class Link_CFG_PARAM {

        /**
         *
         */
        public byte[] link_cfg_param;

        /**
         * Constructor
         * @param Link_Param_Type
         * @param Timer_Interval
         * @param Th_action
         * @param List<Threshold>
         */
        /**
         * Getter - Returns Link_CFG__Param value in byte[] form
         * @return byte[]
         */
        public byte[] get_Link_CFG_PARAM() {
            return link_cfg_param;
        }
    }

    /**
     *
     * Class designed to construct a Link_CFG_PARAM object
     *
     */
    public class Link_Det_CFG {

        /**
         *
         */
        public byte[] link_det_cfg;

        /**
         * Constructor
         * @param Network_ID
         * @param Sig_Strength
         * @param Link_Data_Rate
         */
        public Link_Det_CFG(Network_ID netID, Sig_Strength sigstrength, Link_Data_Rate linkdatarate) {
            Serialization srlz = new Serialization();
            byte[] tmp, tmp1, tmp2;
            if (netID != null) {
                tmp = srlz.choice(netID.get_Network_ID(), 1);
            } else {
                tmp = srlz.choice(null, 0);
            }
            if (sigstrength != null) {
                tmp1 = srlz.choice(sigstrength.get_Sig_Strength(), 1);
            } else {
                tmp1 = srlz.choice(null, 0);
            }
            if (linkdatarate != null) {
                tmp2 = srlz.choice(linkdatarate.get_Link_Data_Rate(), 1);
            } else {
                tmp2 = srlz.choice(null, 0);
            }
            link_det_cfg = srlz.sequence(tmp, tmp1, tmp2);
        }

        /**
         * Getter - Returns Link Det CFG value in byte[] form
         * @return byte[]
         */
        public byte[] Get_Link_Det_CFG() {
            return link_det_cfg;
        }
    }

    /**
     *
     * Class designed to construct a Network_ID object
     *
     */
    public class Network_ID {

        /**
         *
         */
        public byte[] network_id;

        /**
         * Constructor
         * @param Octet_String
         */
        public Network_ID(Octet_String s) {
            network_id = s.getValue();
        }

        /**
         * Getter - Returns Network ID valu  in byte [] form
         * @return form
         */
        public byte[] get_Network_ID() {
            return network_id;
        }

        public void set_Network_ID(byte[] in) {
            network_id = new byte[in.length];
            network_id = in;
        }

        public String get_Network_ID_Value() {
            return (new String(network_id));
        }
    }

    /**
     *
     * Class designed to construct a Sig_Strength object
     *
     */
    public class Sig_Strength {

        /**
         *
         */
        public byte[] sig_strength;

        /**
         * Constructor
         * @param UInt8
         */
        public Sig_Strength(UInt8 value) {
            Serialization srlz = new Serialization();
            sig_strength = srlz.choice(value.getValue(), 0);
        }

        /**
         * Constructor
         * @param Percentage
         */
        public Sig_Strength(Percentage p) {
            Serialization srlz = new Serialization();
            sig_strength = srlz.choice(p.get_Percentage(), 0);
        }

        /**
         * Getter - Returns Sig_Strength value in byte [] form
         * @return byte[]
         */
        public byte[] get_Sig_Strength() {
            return sig_strength;
        }
    }

    /**
     *
     * Class designed to construct a Link_Param_Eth object
     *
     */
    public class Link_Param_Eth {

        /**
         *
         */
        public UInt8 linkparamEth;

        /**
         * Constructor
         * @param int
         */
        public Link_Param_Eth(int i) {
            linkparamEth = new UInt8(i);
        }

        /**
         * Getter - Returns Link Param ETh value in byte[]
         * @return byte []
         */
        public byte[] get_Link_Param_Eth() {
            return linkparamEth.getValue();
        }
    }

    /**
     *
     * Class designed to construct a Link_Param_802_11 object
     *
     */
    public class Link_Param_802_11 {

        /**
         *
         */
        public UInt8 linkparam80211;

        /**
         * Constructor
         * @param int
         */
        public Link_Param_802_11(int i) {
            linkparam80211 = new UInt8(i);
        }

        /**
         * Getter - Returns Link Param 80211 valuye in byte[] form
         * @return byte[]
         */
        public byte[] get_Link_Param_802_11() {
            return linkparam80211.getValue();
        }
    }

    /**
     *
     * Class designed to construct a Link_Param_Sensor object
     *
     */
public class Link_Param_Sensor {

        /**
         *
         */
        public UInt8 linkparamsensor;

        /**
         * Constructor
         * @param int
         */
        public Link_Param_Sensor(int i) {
            linkparamsensor = new UInt8(i);
        }

        /**
         * Getter - Returns Link Param 80211 valuye in byte[] form
         * @return byte[]
         */
        public byte[] get_Link_Param_Sensor() {
            return linkparamsensor.getValue();
        }
    }





    /**
     *
     * Class designed to construct a Link_Param_Type object
     *
     */
    public class Link_Param_Type {

        /**
         *
         * Class designed to construct a link_param_type_choice object
         *
         */
        public class link_param_type_choice {

            /**
             *
             */
            public static final int LINK_PARAM_ETH = 4;
            /**
             *
             */
            public static final int LINK_PARAM_802_11 = 5;
            public static final int LINK_PARAM_SENSOR = 12;
        }
        /**
         *
         */
        public byte[] linkparamtype;

        /**
         * Constructor
         */
        public Link_Param_Type() {
        }

        /**
         * Constructor
         * @param Link_Param_Eth
         */
        public Link_Param_Type(Link_Param_Eth lpEth) {
            Serialization srlz = new Serialization();
            linkparamtype = new byte [srlz.choice(lpEth.get_Link_Param_Eth(), Link_Param_Type.link_param_type_choice.LINK_PARAM_ETH).length];
            linkparamtype = srlz.choice(lpEth.get_Link_Param_Eth(), Link_Param_Type.link_param_type_choice.LINK_PARAM_ETH);
        }

        /**
         * Constructor
         * @param Link_Param_802_11
         */
        public Link_Param_Type(Link_Param_802_11 lp80211) {
            Serialization srlz = new Serialization();
            linkparamtype = new byte [srlz.choice(lp80211.get_Link_Param_802_11(), Link_Param_Type.link_param_type_choice.LINK_PARAM_802_11).length];
            linkparamtype = srlz.choice(lp80211.get_Link_Param_802_11(), Link_Param_Type.link_param_type_choice.LINK_PARAM_802_11);
        }

        public Link_Param_Type(Link_Param_Sensor lps) {
            Serialization srlz = new Serialization();
            linkparamtype = new byte [srlz.choice(lps.get_Link_Param_Sensor(), 11).length];
            linkparamtype = srlz.choice(lps.get_Link_Param_Sensor(), 11);
        }


        /**
         * Getter - Returns Link Param Typ value in byte [] form
         * @return byte[]
         */
        public byte[] get_Link_Param_Type() {
            return linkparamtype;
        }
    }

    /**
     *
     * Class designed to construct a Timer_Interval object
     *
     */
    public class Timer_Interval {

        /**
         *
         */
        public UInt16 Timer_Interval;

        /**
         * Constructor
         * @param int
         */
        public Timer_Interval(int i) {
            Timer_Interval = new UInt16(i);
        }

        /**
         * Constructor
         * @param UInt16
         */
        public Timer_Interval(UInt16 i) {
            Timer_Interval = new UInt16();
            Timer_Interval = i;
        }

        /**
         * Getter - Returns Timer Interval value in byte[] form
         * @return byte[]
         */
        public byte[] get_Timer_Interval() {
            return Timer_Interval.getValue();
        }
    }

    /**
     *
     * Class designed to construct a Timer_Interval object
     *
     */
    public class Link_Data_Rate {

        /**
         *
         */
        public UInt32 Link_Data_Rate;

        /**
         * Constructor
         * @param Link_Data_Rate
         */
        public Link_Data_Rate(int i) {
            Link_Data_Rate = new UInt32(i);
        }

        /**
         * Getter - Returns Link Data Rate value in byte[] form
         * @return byte[]
         */
        public byte[] get_Link_Data_Rate() {
            return Link_Data_Rate.getValue();
        }
    }

    /**
     *
     * Class designed to construct a Th_action object
     *
     */
    public class Th_action {

        /**
         *
         */
        public UInt8 th_action;
        /**
         *
         */
        public static final int normal_threshold = 0;
        /**
         *
         */
        public static final int one_shot_threshold = 1;
        /**
         *
         */
        public static final int cancel_threshold = 2;

        /**
         * Constructor
         * @param int
         */
        public Th_action(int action) {
            th_action = new UInt8(action);
        }

        /**
         * Getter - Returns TH_Action value in byte[] form
         * @return byte[]
         */
        public byte[] get_TH_Action() {
            return th_action.getValue();
        }
    }

    /**
     *
     * Class designed to construct a Threshold object
     *
     */
    public class Threshold {

        /**
         *
         */
        public byte[] threshold;

        /**
         * Constructor
         * @param int
         * @param int
         */
        public Threshold(int threshold_val, int threshold_x_dir) {
            UInt16 thresholdVal = new UInt16(threshold_val);
            UInt8 thresholdXdir = new UInt8(threshold_x_dir);
            Serialization srlz = new Serialization();
            threshold = srlz.sequence(thresholdVal.getValue(), thresholdXdir.getValue());
        }

        /**
         * Getter - Returns the Threshold value in byte[] form
         * @return byte[]
         */
        public byte[] get_Threshold() {
            return threshold;
        }
    }
    /**
     *
     */
    public Vector LinkIdentifierList;

    /**
     *
     * Class designed to construct a Link_Tuple_ID object
     *
     */
    public class Link_Tuple_ID {

        byte[] link_tuple_id;

        public Link_Tuple_ID() {
        }
        //Identifier of a link that is associated with a PoA
        //The lINK_ID contains the MN LINK_ADDR.  The optional  LINK_ADDR contains
        //a link address of the PoA

        /**
         * Constructor
         * @param Link_ID
         * @param Link_address
         */
        public Link_Tuple_ID(Link_ID lnkid, Link_Address lnk) {
            byte[] tmp_choice = new byte[0];
            Serialization srlz = new Serialization();
            if (lnk == null) {
                tmp_choice = new byte[(srlz.choice(null, -1)).length];
                tmp_choice = srlz.choice(null, -1);
                link_tuple_id = new byte[(srlz.sequence(lnkid.get_Value(), tmp_choice)).length];
                link_tuple_id = srlz.sequence(lnkid.get_Value(), tmp_choice);
            }
            if (lnk != null) {
                tmp_choice = new byte[(srlz.choice(lnk.get_link_address(), 0)).length];
                tmp_choice = srlz.choice(lnk.get_link_address(), 0);
                link_tuple_id = new byte[(srlz.sequence(lnkid.get_Value(), tmp_choice)).length];
                link_tuple_id = srlz.sequence(lnkid.get_Value(), tmp_choice);
            }

        }

        /**
         * Getter - Returns Link Tuple ID in byte [] form
         * @return byte []
         */
        public byte[] get_Link_Tuple_ID() {
            return link_tuple_id;
        }

        /**
         * Getter - Returns Link Tuple ID in byte [] form
         * @return byte []
         */
        public void set_Link_Tuple_ID(byte[] in) {
            link_tuple_id = new byte[in.length];
            link_tuple_id = in;
        }
    }

    /**
     *
     * Class designed to construct a Link_ID object
     *
     */
    public class Link_ID {

        byte[] link_id;

        /**
         * Getter - Returns Link ID value in byte[] form
         * @return byte[]
         */
        public byte[] get_Value() {
            return link_id;
        }

        /**
         * Constructor
         */
        public Link_ID(byte[] in) {

            link_id = new byte[in.length];
            link_id = in;
        }

        /**
         * Constructor
         * @param Link_Type
         * @param Link_address
         */
        public Link_ID(Link_Type lnktp, Link_Address lnk_add) {
            Serialization srlz = new Serialization();
            link_id = new byte[srlz.sequence(lnktp.linktype.getValue(), lnk_add.get_link_address()).length];
            link_id = srlz.sequence(lnktp.linktype.getValue(), lnk_add.get_link_address());
        }
    }

    /**
     *
     * Class designed to construct a Link_ID object
     *
     */
    public class Link_Type {

        /**
         *
         */
        public UInt8 linktype;
        /**
         *
         */
        public int lnktp;
        /**
         *
         */
        public static final int link_type_gsm = 1;
        /**
         *
         */
        public static final int link_type_gprs = 2;
        /**
         *
         */
        public static final int link_type_edge = 3;
        /**
         *
         */
        public static final int link_type_ethernet = 15;
        /**
         *
         */
        public static final int link_type_wireless_other = 18;
        /**
         *
         */
        public static final int link_type_802_11 = 19;
        /**
         *
         */
        public static final int link_type_cdma2000 = 22;
        /**
         *
         */
        public static final int link_type_umts = 23;
        /**
         *
         */
        public static final int link_type_cdma2000_hrpd = 24;
        /**
         *
         */
        public static final int link_type_802_16 = 27;
        /**
         *
         */
        public static final int link_type_802_20 = 28;
        /**
         *
         */
        public static final int link_type_802_22 = 29;
        public static final int link_type_sensor = 30;

        public Link_Type(Link_Type lt) {
            linktype = lt.get_Link_Type_Value();

        }

        public UInt8 get_Link_Type_Value() {
            return linktype;
        }

        public Link_Type() {
        }

        /**
         * Constructor
         * @param int
         */
        public Link_Type(int type) {
            linktype = new UInt8(type);
            lnktp = type;
        }

        /**
         * Constructor
         * @param int
         */
        public Link_Type(byte[] in) {
            linktype = new UInt8();
            linktype.setValue(in);
        }

        /**
         * Getter - Returns Link Type value in byte [] form
         * @return byte []
         */
        public byte[] get_Link_Type() {
            return linktype.getValue();
        }
    }

    /**
     *
     * Class designed to construct a Subtype object
     *
     */
    public class Subtype {

        public Subtype() {
        }

        public Subtype(byte[] in) {
            sub_type = new Bitmap64(in);
        }

        public Subtype(Subtype sb) {
            sub_type = new Bitmap64(sb.get_SubType());
            sub_type = sb.get_Subtype_Value();
        }

        public Bitmap64 get_Subtype_Value() {
            return sub_type;
        }
        /**
         *
         */
        public Bitmap64 sub_type;
        /**
         *
         */
        public static final int netsubtype_eth10 = 0;
        /**
         *
         */
        public static final int netsubtype_eth100 = 1;
        /**
         *
         */
        public static final int netsubtype_eth1000 = 2;
        /**
         *
         */
        public static final int netsubtype_iee80211_2_4GHz = 0;
        /**
         *
         */
        public static final int netsubtype_iee80211_5GHz = 1;
        /**
         *
         */
        public static final int netsubtype_iee80211_4_9GHz = 2;
        /**
         *
         */
        public static final int netsubtype_iee80211_3_65GHz = 3;
        /**
         *
         */
        public static final int netsubtype_iee80211_316THz = 4;
        /**
         *
         */
        public static final int netsubtype_umts_rel99 = 0;
        /**
         *
         */
        public static final int netsubtype_umts_rel4 = 1;
        /**
         *
         */
        public static final int netsubtype_umts_rel5_hsdpa = 2;
        /**
         *
         */
        public static final int netsubtype_umts_rel6_hsupa = 3;
        /**
         *
         */
        public static final int netsubtype_umts_rel7_mimo = 4;
        /**
         *
         */
        public static final int netsubtype_umts_rel8 = 5;
        /**
         *
         */
        public static final int netsubtype_cdma2000_hrpd_rev0 = 0;
        /**
         *
         */
        public static final int netsubtype_cdma2000_hrpd_revA = 1;
        /**
         *
         */
        public static final int netsubtype_cdma2000_hrpd_revB = 2;
        /**
         *
         */
        public static final int netsubtype_cdma2000_hrpd_revC = 3;
        /**
         *
         */
        public Vector list_subtype;

        /**
         * Constructor
         * @param List<Integer>
         */
        public void setSubType(Vector lst) {
            sub_type = new Bitmap64(lst);
        }

        public byte[] get_SubType() {
            return sub_type.getValue();
        }
    }

    public class Type_Ext {

        Octet_String os;
        byte[] typeExt;

        public Type_Ext() {
        }

        public Type_Ext(byte[] in) {
            typeExt = new byte[in.length];
            typeExt = in;
        }

        public Type_Ext(Type_Ext te) {
            typeExt = new byte[te.get_TypeExt().length];
            typeExt = te.get_TypeExt();
            os = new Octet_String(te.get_Type_Ext_Value());

        }

        public byte[] get_TypeExt() {
            return typeExt;
        }

        public Octet_String get_Type_Ext_Value() {
            return os;
        }
    }
}
