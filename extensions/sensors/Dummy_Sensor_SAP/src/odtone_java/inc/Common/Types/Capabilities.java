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

//~--- non-JDK imports --------------------------------------------------------

import odtone_java.inc.Common.Types.Information.Network_type;
import odtone_java.inc.Common.Serialization;

//~--- JDK imports ------------------------------------------------------------

import java.util.Vector;
import lightMIHF.Bitmap16;
import lightMIHF.Bitmap32;
import lightMIHF.Bitmap64;

/**
 *
 * @author marcelo lebre <marcelolebre@av.it.pt>
 *
 */
/**
 *
 * This class nests objects related to the capability mechanism
 *
 */
public class Capabilities {

    /**
     *
     */
    public Mih_IQ_Type_List SupportedISQueryTypeList;
    /**
     *
     */
    public Mih_IQ_Type_List SupportedTransportList;

    /**
     *
     */
    public Capabilities() {
    }

    /**
     *
     * @author marcelo lebre <marcelolebre@av.it.pt>
     *
     */
    /**
     *
     * Class designed to construct a MBBHandorverSupport object
     *
     */
    

    /**
     *
     * Class designed to construct a MBB_HO_SUP object
     *
     */
    public class MBB_HO_SUP {

        byte[] mbb_ho_sup;

        /**
         * Constructor
         * @param Network_Type
         * @param Network_Tyoe
         * @param boolean
         */
        public MBB_HO_SUP(Network_type netType1, Network_type netType2, boolean bool) {
            Serialization srlz = new Serialization();
            byte[] tmp = new byte[1];

            if (bool) {
                tmp[0] = (byte) 0x01;
            } else {
                tmp[0] = (byte) 0x00;
            }

            mbb_ho_sup = new byte[srlz.sequence(netType1.get_network_type(), netType2.get_network_type(), tmp).length];
            mbb_ho_sup = srlz.sequence(netType1.get_network_type(), netType2.get_network_type(), tmp);
        }

        /**
         * Getter - Returns the MBB_HO_SUP value in byte[] form
         * @return byte []
         */
        public byte[] get_MBB_HO_SUP() {
            return mbb_ho_sup;
        }
    }

    /**
     *
     * Class designed to construct a Mih_IQ_Type_List object
     *
     */
    public class Mih_IQ_Type_List {

        /**
         *
         */
        public static final int iq_type_binary_data = 0;
        /**
         *
         */
        public static final int iq_type_ie_cost = 11;
        /**
         *
         */
        public static final int iq_type_ie_country_code = 7;
        /**
         *
         */
        public static final int iq_type_ie_net_capabilities = 17;
        /**
         *
         */
        public static final int iq_type_ie_net_emserv_proxy = 20;
        /**
         *
         */
        public static final int iq_type_ie_net_frequency_bands = 15;
        /**
         *
         */
        public static final int iq_type_ie_net_ims_proxy_cscf = 21;
        /**
         *
         */
        public static final int iq_type_ie_net_ip_cfg_methods = 16;
        /**
         *
         */
        public static final int iq_type_ie_net_mob_mgmt_prot = 19;
        /**
         *
         */
        public static final int iq_type_ie_net_mobile_network = 22;
        /**
         *
         */
        public static final int iq_type_ie_net_regult_domain = 14;
        /**
         *
         */
        public static final int iq_type_ie_net_supported_lcp = 18;
        /**
         *
         */
        public static final int iq_type_ie_network_aux_id = 9;
        /**
         *
         */
        public static final int iq_type_ie_network_data_rate = 13;
        /**
         *
         */
        public static final int iq_type_ie_network_id = 8;
        /**
         *
         */
        public static final int iq_type_ie_network_qos = 12;
        /**
         *
         */
        public static final int iq_type_ie_poa_channel_range = 25;
        /**
         *
         */
        public static final int iq_type_ie_poa_ip_addr = 28;
        /**
         *
         */
        public static final int iq_type_ie_poa_link_addr = 23;
        /**
         *
         */
        public static final int iq_type_ie_poa_location = 24;
        /**
         *
         */
        public static final int iq_type_ie_poa_subnet_info = 27;
        /**
         *
         */
        public static final int iq_type_ie_poa_system_info = 26;
        /**
         *
         */
        public static final int iq_type_ie_roaming_parteners = 10;
        /**
         *
         */
        public static final int iq_type_ir_network_type = 4;
        /**
         *
         */
        public static final int iq_type_operator_id = 5;
        /**
         *
         */
        public static final int iq_type_rdf_data = 1;
        /**
         *
         */
        public static final int iq_type_rdf_schema = 3;
        /**
         *
         */
        public static final int iq_type_rdf_schema_url = 2;
        /**
         *
         */
        public static final int iq_type_service_provider_id = 6;
        Bitmap64 mih_iq_type_list;

        /**
         * Cunstructor
         * @param List<Integer>
         */
        public Mih_IQ_Type_List(Vector lst) {
            mih_iq_type_list = new Bitmap64(lst);
        }

        /**
         * Getter - Returns MIH_IQ_Type_List values in Bitmap64 form
         * @return Bitmap64
         */
        public Bitmap64 get_Mih_IQ_Type_List() {
            return mih_iq_type_list;
        }
    }

     /**
     *
     * Class designed to construct a Mih_Trans_Lst object
     *
     */
    public class Mih_Trans_Lst {

        /**
         *
         */
        public static final int TCP = 1;
        /**
         *
         */
        public static final int UDP = 0;
        Bitmap16 mih_trans_list;

        /**
         * Constructor
         * @param List<Integer>
         */
        public Mih_Trans_Lst(Vector lst) {
            mih_trans_list = new Bitmap16(lst);
        }

        public Mih_Trans_Lst(Bitmap16 b){
            mih_trans_list = new Bitmap16();
            mih_trans_list = b;
        }
        /**
         * Getter- Returns the MIH Trans LST in a BITmap16 form
         * @return Bitmap16
         */
        public Bitmap16 Get_Mih_Trans_Lst() {
            return mih_trans_list;
        }
    }

    /**
     *
     * Class designed to construct a Mih_cmd_lst object
     *
     */
    public class Mih_cmd_lst {

        /**
         *
         */
        public static final int link_actions = 2;
        /**
         *
         */
        public static final int link_configure_thresholds = 1;
        // Supported_MIH_Command_List
        /**
         *
         */
        public static final int link_get_parameters = 0;
        /**
         *
         */
        public static final int mn_ho_candidate_query = 4;
        /**
         *
         */
        public static final int mn_ho_commit = 4;
        /**
         *
         */
        public static final int mn_ho_complete = 4;
        /**
         *
         */
        public static final int n2n_ho_Complete = 3;
        /**
         *
         */
        public static final int n2n_ho_commit = 3;
        /**
         *
         */
        public static final int n2n_ho_query_resources = 3;
        /**
         *
         */
        public static final int net_ho_candidate_query = 3;
        /**
         *
         */
        public static final int net_ho_commit = 3;
        Bitmap32 mih_cmd_list;

        /**
         * Constructor
         * @param List<Integer>
         */
        public Mih_cmd_lst(Vector lst) {
            mih_cmd_list = new Bitmap32(lst);
        }

        /**
         * Getter - Returns the MIH COmmand list in a bitmap32 form
         * @return bitmap32
         */
        public Bitmap32 get_mih_command_list() {
            return mih_cmd_list;
        }
    }

    /**
     *
     * Class designed to construct a Mih_evt_lst object
     *
     */
    public class Mih_evt_lst {

        // MIH_Event_List
        /**
         *
         */
        public static final int link_detected = 0;
        /**
         *
         */
        public static final int link_down = 2;
        /**
         *
         */
        public static final int link_going_down = 4;
        /**
         *
         */
        public static final int link_handover_complete = 6;
        /**
         *
         */
        public static final int link_handover_imminent = 5;
        /**
         *
         */
        public static final int link_parameters_report = 3;
        /**
         *
         */
        public static final int link_pdu_transmit_status = 7;
        /**
         *
         */
        public static final int link_up = 1;
        /**
         *
         */
        public Mih_evt_lst RequestedMIHEventList;
        /**
         *
         */
        public Mih_evt_lst ResponseMIHEventList;
        /**
         *
         */
        public Mih_evt_lst SupportedMIHEventList;
        Bitmap32 mih_evt_list;
        Vector requestedMIHEventList;
        Vector responseMIHEventList;
        Vector supportedMIHEventList;

        /**
         * Constructor
         * @param List<Integer>
         */
        public Mih_evt_lst(Vector lst) {
            supportedMIHEventList = lst;
            requestedMIHEventList = lst;
            responseMIHEventList = lst;
            mih_evt_list = new Bitmap32(lst);
        }

        /**
         * Getter - Return MIH EVENT LIST in bitmap32 form
         * @return bitmap32
         */
        public Bitmap32 get_mih_event_list() {
            return mih_evt_list;
        }
    }
}

