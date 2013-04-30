//
// Copyright (c) 2009-2013 2013 Universidade Aveiro - Instituto de
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
import odtone_java.inc.Common.Datatypes.Octet_String;
import odtone_java.inc.Common.Datatypes.UInt16;
import odtone_java.inc.Common.Types.Information.Network_type_addr;
import odtone_java.inc.Common.Types.Ipconfig.IP_Addr;
import odtone_java.inc.Common.Serialization;

//~--- JDK imports ------------------------------------------------------------

import java.util.Vector;
import odtone_java.inc.Common.Datatypes.Octet;
import odtone_java.inc.Common.Datatypes.UInt32;

/**
 *
 * @author marcelo lebre <marcelolebre@av.it.pt>
 *
 */
/**
 *
 * Class designed to construct a address object
 * Nested in this class are several objects that relate to
 * address information in the standard
 *
 */
public class Address {

    /**
     *
     */
    public IP_Addr ACC_RTR;
    /**
     *
     */
    public IP_Addr DHCP_Serv;
    /**
     *
     */
    public IP_Addr FN_AGNT;
    /**
     *
     */
    public Transport_address mac_address;

    /**
     *
     * Class designed to construct a link address list object
     *
     */
    public class Link_Addr_List {

        byte[] link_addr_list;
        Vector link_addr_list_ = new Vector();

        public Link_Addr_List(byte[] in) {
            link_addr_list = new byte[in.length];
            link_addr_list = in;
        }

        public Link_Addr_List(Vector linkAddrList) {
            link_addr_list_ = linkAddrList;

            int count = 0, pos = 0;
            Serialization srlz = new Serialization();

            Vector tmp = new Vector();
            for (int i = 0; i < linkAddrList.size(); i++) {
                tmp.addElement(((Network_type_addr)linkAddrList.elementAt(i)).get_Network_type_addr());
            }

            link_addr_list = new byte[srlz.encoding_List(tmp).length];
            link_addr_list = srlz.encoding_List(tmp);
        }

        public byte[] getLinkAddrList() {
            return link_addr_list;
        }

        public Vector getLinkAddrListValues() {
            return link_addr_list_;
        }
    }

    /**
     *
     * Class designed to construct a link address object
     *
     */
    public class Link_Address {

        /**
         *
         */
        public static final int _3GPP2_ADDR = 5;
        /**
         *
         */
        public static final int _3GPP_2G_CELL_ID = 3;
//      Behaviour not implemented
        /**
         *
         */
        public static final int _3GPP_3G_CELL_ID = 2;
        /**
         *
         */
        public static final int _3GPP_ADDR = 4;
        /**
         *
         */
        public static final int _OTHER_L2_ADDR = 6;
        /**
         *
         */
        public static final int mac_add = 1;
//
        byte[] link_address;
        byte[] link_address_out;
        Transport_address macaddr;
        ThreeGPP_ADDR tga;
        ThreeGPP2_ADDR tg2a;
        ThreeGPP_2G_Cell_ID tg2ci;
        ThreeGPP_3G_Cell_ID tg3ci;
        Other_l2_ADDR ola;
        String which_transport = "";

        public String get_which_active_transport() {
            return which_transport;
        }

        public Other_l2_ADDR get_Other_L2_Addr() {
            return ola;
        }

        public ThreeGPP_3G_Cell_ID get_3GPP_3G_Cell_ID() {
            return tg3ci;
        }

        public ThreeGPP_2G_Cell_ID get_3GPP_2G_Cell_ID() {
            return tg2ci;
        }

        public ThreeGPP2_ADDR get_3GPP2_Addr() {
            return tg2a;
        }

        public Transport_address get_Transport_address() {
            return macaddr;
        }

        public ThreeGPP_ADDR get_3GPP_Addr() {
            return tga;
        }

        public Link_Address(Transport_address mac_addr) {
            macaddr = new Transport_address(mac_addr.get_Value_i(), mac_addr.get_Value_Octet_String());
            Serialization srlz = new Serialization();
            which_transport = "mac address";
            link_address_out = new byte[srlz.choice(mac_addr.get_Transport_address(), 0).length];
            link_address_out = srlz.choice(mac_addr.get_Transport_address(), 0);
        }

        public Link_Address(Link_Address la) {
            if (la.get_which_active_transport().equals("mac address")) {
                macaddr = new Transport_address(la.get_Transport_address().get_Value_i(), la.get_Transport_address().get_Value_Octet_String());
                Serialization srlz = new Serialization();
                which_transport = "mac address";
                link_address_out = new byte[la.get_link_address().length];
                link_address_out = la.get_link_address();
            }
            if (la.get_which_active_transport().equals("3GPP 3G Cell ID")) {
                tg3ci = new ThreeGPP_3G_Cell_ID(la.get_3GPP_3G_Cell_ID().get_PLMN_ID(), la.get_3GPP_3G_Cell_ID().get_CELL_ID());
                Serialization srlz = new Serialization();
                which_transport = "3GPP 3G Cell ID";
                link_address_out = new byte[la.get_link_address().length];
                link_address_out = la.get_link_address();
            }
            if (la.get_which_active_transport().equals("3GPP 2G Cell ID")) {
                tg2ci = new ThreeGPP_2G_Cell_ID(la.get_3GPP_2G_Cell_ID().get_PLMN_ID(), la.get_3GPP_2G_Cell_ID().get_LAC(), la.get_3GPP_2G_Cell_ID().get_CI());
                Serialization srlz = new Serialization();
                which_transport = "3GPP 3G Cell ID";
                link_address_out = new byte[la.get_link_address().length];
                link_address_out = la.get_link_address();
            }
            if (la.get_which_active_transport().equals("3GPP Address")) {
                tga = new ThreeGPP_ADDR(la.get_3GPP_Addr().get_3GPP_Addr_Value());
                Serialization srlz = new Serialization();
                which_transport = "3GPP Address";
                link_address_out = new byte[la.get_link_address().length];
                link_address_out = la.get_link_address();
            }
            if (la.get_which_active_transport().equals("3GPP2 Address")) {
                tg2a = new ThreeGPP2_ADDR(la.get_3GPP2_Addr().get_3GPP2_Addr_Value());
                Serialization srlz = new Serialization();
                which_transport = "3GPP2 Address";
                link_address_out = new byte[la.get_link_address().length];
                link_address_out = la.get_link_address();
            }
            if (la.get_which_active_transport().equals("Other L2 Address")) {
                ola = new Other_l2_ADDR(la.get_Other_L2_Addr().get_Other_L2_Addr_Value());
                Serialization srlz = new Serialization();
                which_transport = "Other L2 Address";
                link_address_out = new byte[la.get_link_address().length];
                link_address_out = la.get_link_address();
            }

        }

        /**
         *
         * Constructor
         *
         */
        public Link_Address(byte[] in) {
            int selector = -1;
            link_address_out = new byte[in.length];
            link_address_out = in;
            selector = in[0];
            byte[] tmp = new byte[in.length - 1];

            for (int i = 0; i < in.length - 1; i++) {
                tmp[0] = in[i + 1];
            }

            if (selector == 0) {

                macaddr = new Transport_address(tmp);
                Serialization srlz = new Serialization();
                which_transport = "mac address";
                link_address_out = new byte[in.length];
                link_address_out = in;
            }
            if (selector == 1) {
                tg3ci = new ThreeGPP_3G_Cell_ID(tmp);
                Serialization srlz = new Serialization();
                which_transport = "3GPP 3G Cell ID";
                link_address_out = new byte[in.length];
                link_address_out = in;
            }
            if (selector == 2) {
                tg2ci = new ThreeGPP_2G_Cell_ID(tmp);
                Serialization srlz = new Serialization();
                which_transport = "3GPP 3G Cell ID";
                link_address_out = new byte[in.length];
                link_address_out = in;
            }
            if (selector == 3) {
                tga = new ThreeGPP_ADDR(tmp);
                Serialization srlz = new Serialization();
                which_transport = "3GPP Address";
                link_address_out = new byte[in.length];
                link_address_out = in;
            }
            if (selector == 4) {
                tg2a = new ThreeGPP2_ADDR(tmp);
                Serialization srlz = new Serialization();
                which_transport = "3GPP2 Address";
                link_address_out = new byte[in.length];
                link_address_out = in;
            }
            if (selector == 5) {
                ola = new Other_l2_ADDR(tmp);
                Serialization srlz = new Serialization();
                which_transport = "Other L2 Address";
                link_address_out = new byte[in.length];
                link_address_out = in;
            }

        }

        public Link_Address(ThreeGPP_3G_Cell_ID t3c) {
            tg3ci = new ThreeGPP_3G_Cell_ID(null, null);
            Serialization srlz = new Serialization();
            link_address_out = new byte[srlz.choice(t3c.get_ThreeGPP_3G_Cell_ID(), 1).length];
            link_address_out = srlz.choice(t3c.get_ThreeGPP_3G_Cell_ID(), 1);
            which_transport = "3GPP 3G Cell ID";
        }

        /**
         *
         * Constructor
         *
         */
        public Link_Address(ThreeGPP_2G_Cell_ID t2c) {
            Serialization srlz = new Serialization();
            link_address_out = new byte[srlz.choice(t2c.get_ThreeGPP_2G_Cell_ID(), 2).length];
            link_address_out = srlz.choice(t2c.get_ThreeGPP_2G_Cell_ID(), 2);
            which_transport = "3GPP 2G Cell ID";
        }

        /**
         *
         * Constructor
         *
         */
        public Link_Address(ThreeGPP_ADDR tga) {
            Serialization srlz = new Serialization();
            link_address_out = new byte[srlz.choice(tga.get_3GPP_ADDR(), 3).length];
            link_address_out = srlz.choice(tga.get_3GPP_ADDR(), 3);
            which_transport = "3GPP Address";
        }

        /**
         *
         * Constructor
         *
         */
        public Link_Address() {
        }

        /**
         *
         * Constructor
         *
         */
        public Link_Address(ThreeGPP2_ADDR tga) {
            Serialization srlz = new Serialization();
            link_address_out = new byte[srlz.choice(tga.get_3GPP2_ADDR(), 4).length];
            link_address_out = srlz.choice(tga.get_3GPP2_ADDR(), 4);
            which_transport = "3GPP2 Address";
        }

        /**
         *
         * Constructor
         *
         */
        public Link_Address(Other_l2_ADDR ola) {
            Serialization srlz = new Serialization();
            link_address_out = new byte[srlz.choice(ola.get_Other_l2_ADDR(), 4).length];
            link_address_out = srlz.choice(ola.get_Other_l2_ADDR(), 4);
            which_transport = "Other L2 Address";
        }

        /**
         * Getter - Returns the link address in byte[] form
         * @return byte []
         */
        public byte[] get_link_address() {
            return link_address_out;
        }
    }

    /**
     *
     * Class designed to construct a transport address object
     *
     */
    public class Transport_address {

        public byte[] transportaddress;
        public int value_i;
        public Octet_String value_os;

        public Transport_address(byte[] in) {

            transportaddress = new byte[in.length];
            transportaddress = in;

            byte[] tmpUint2 = new byte[2];
            tmpUint2[0] = in[0];
            tmpUint2[1] = in[1];
            UInt32 family = new UInt32();
            value_i = family.UInt32ToInt(tmpUint2);

            byte[] add = new byte[in.length - 2];
            for (int i = 0, j = 2; j < in.length; i++) {
                add[i] = in[j];
            }
            value_os = new Octet_String(add);

        }

        /**
         * Constructor
         * @param int
         * @param Octet_String
         */
        public Transport_address(int i, Octet_String os) {
            value_i = i;
            value_os = new Octet_String(os);

            // The maximum value of i according to IANA
            // http://www.iana.org/assignments/address-family-numbers/


            // Sequencing
            Serialization srlz = new Serialization();
            transportaddress = new byte[srlz.sequence((new UInt16(i)).getValue(), os.getValue()).length];
            transportaddress = srlz.sequence((new UInt16(i)).getValue(), os.getValue());

        }

        /**
         * Getter - returns the transport address value in byte []
         * @return byte[]
         */
        public byte[] get_Transport_address() {
            return transportaddress;
        }

        public int get_Value_i() {
            return value_i;
        }

        public Octet_String get_Value_Octet_String() {
            return value_os;
        }
    }

    /**
     *
     * Class designed to construct a 3GPP_3G_Cell_ID object
     *
     */
    public class ThreeGPP_3G_Cell_ID {

        byte[] threegpp_3g_cell_id;
        PLMN_ID plmn_ID;
        CELL_ID cell_ID;

        public ThreeGPP_3G_Cell_ID(PLMN_ID plmnID, CELL_ID cellID) {
            plmn_ID = new PLMN_ID(plmnID);
            cell_ID = new CELL_ID(cellID);
            Serialization srlz = new Serialization();
            threegpp_3g_cell_id = new byte[srlz.sequence(plmnID.get_PLMN_ID(), cellID.get_CELL_ID()).length];
            threegpp_3g_cell_id = srlz.sequence(plmnID.get_PLMN_ID(), cellID.get_CELL_ID());
        }

        public ThreeGPP_3G_Cell_ID(byte[] in) {
            threegpp_3g_cell_id = new byte[in.length];
            threegpp_3g_cell_id = in;

            byte[] tmp1 = new byte[3];
            byte[] tmp2 = new byte[4];

            for (int i = 0; i < 3; i++) {
                tmp1[i] = in[i];
            }
            for (int i = 3, j = 0; i < in.length; i++, j++) {
                tmp2[j] = in[i];
            }

            Octet os = new Octet(tmp1);
            plmn_ID = new PLMN_ID(os);
            UInt32 val = new UInt32();
            val.setValue(tmp2);
            cell_ID = new CELL_ID(val);

        }

        public PLMN_ID get_PLMN_ID() {
            return plmn_ID;
        }

        public CELL_ID get_CELL_ID() {
            return cell_ID;
        }

        public byte[] get_ThreeGPP_3G_Cell_ID() {
            return threegpp_3g_cell_id;
        }
    }

    public class PLMN_ID {

        byte[] plmnID;
        Octet value;

        public PLMN_ID(Octet os) {
            value = new Octet(os);
            if (os.getValue().length == 3) {
                plmnID = new byte[os.getValue().length];
                plmnID = os.getValue();
            }
        }

        public PLMN_ID(PLMN_ID plmnID) {
            value = plmnID.get_PLMN_ID_Value();
            this.plmnID = new byte[plmnID.get_PLMN_ID().length];
            this.plmnID = plmnID.get_PLMN_ID();
        }

        public byte[] get_PLMN_ID() {
            return plmnID;
        }

        public Octet get_PLMN_ID_Value() {
            return value;
        }
    }

    public class CELL_ID {

        byte[] cellID;
        int value;

        public CELL_ID(CELL_ID cellID) {
            value = cellID.get_CELL_ID_Value();
            this.cellID = new byte[cellID.get_CELL_ID().length];
            this.cellID = cellID.get_CELL_ID();
        }

        public CELL_ID(UInt32 uint) {
            value = uint.UInt32ToInt(uint.getValue());
            cellID = new byte[uint.getValue().length];
            cellID = uint.getValue();

        }

        public int get_CELL_ID_Value() {
            return value;
        }

        public byte[] get_CELL_ID() {
            return cellID;
        }
    }

    public class ThreeGPP_2G_Cell_ID {

        byte[] threegpp_2g_cell_id;
        PLMN_ID plmnID;
        LAC lac;
        CI ci;

        public ThreeGPP_2G_Cell_ID(byte[] in) {
            threegpp_2g_cell_id = new byte[in.length];
            threegpp_2g_cell_id = in;

            byte[] tmp1 = new byte[3];
            byte[] tmp2 = new byte[2];
            byte[] tmp3 = new byte[2];
            for (int i = 0; i < 3; i++) {
                tmp1[i] = in[i];
            }
            tmp2[0] = in[3];
            tmp2[1] = in[4];

            tmp3[0] = in[5];
            tmp3[1] = in[6];

            lac = new LAC(new Octet(tmp2));
            ci = new CI(new Octet(tmp3));

        }

        public PLMN_ID get_PLMN_ID() {
            return this.plmnID;
        }

        public LAC get_LAC() {
            return this.lac;
        }

        public CI get_CI() {
            return this.ci;
        }

        public ThreeGPP_2G_Cell_ID(PLMN_ID plmnID, LAC lac, CI ci) {
            Serialization srlz = new Serialization();
            this.plmnID = plmnID;
            this.lac = lac;
            this.ci = ci;

            threegpp_2g_cell_id = new byte[srlz.sequence(plmnID.get_PLMN_ID(), lac.get_LAC(), ci.get_CI()).length];
            threegpp_2g_cell_id = srlz.sequence(plmnID.get_PLMN_ID(), lac.get_LAC(), ci.get_CI());
        }

        public byte[] get_ThreeGPP_2G_Cell_ID() {
            return threegpp_2g_cell_id;
        }
    }

    public class LAC {

        byte[] lac;
        Octet os;

        public LAC(Octet os) {
            this.os = os;
            if (os.getValue().length == 2) {
                lac = new byte[os.getValue().length];
                lac = os.getValue();
            }
        }

        public byte[] get_LAC() {
            return lac;
        }

        public Octet get_LAC_Value() {
            return os;
        }
    }

    public class CI {

        byte[] ci;
        Octet os;

        public CI(Octet os) {
            this.os = os;
            if (os.getValue().length == 2) {
                ci = new byte[os.getValue().length];
                ci = os.getValue();
            }
        }

        public Octet get_CI_Value() {
            return this.os;
        }

        public byte[] get_CI() {
            return ci;
        }
    }

    public class ThreeGPP_ADDR {

        byte[] threeGppAddr;
        Octet_String os;
        public ThreeGPP_ADDR(byte [] in){
        threeGppAddr = new byte[in.length];
        threeGppAddr = in;
        os = new Octet_String(in);
        }

        public ThreeGPP_ADDR(Octet_String os) {
            this.os = new Octet_String(os);
            threeGppAddr = new byte[os.getValue().length];
            threeGppAddr = os.getValue();
        }

        public Octet_String get_3GPP_Addr_Value() {
            return this.os;
        }

        public byte[] get_3GPP_ADDR() {
            return threeGppAddr;
        }
    }

    public class ThreeGPP2_ADDR {

        byte[] threeGpp2Addr;
        Octet_String os;

        public ThreeGPP2_ADDR(byte [] in){
        threeGpp2Addr = new byte[in.length];
        threeGpp2Addr = in;
        os = new Octet_String(in);

        }
        public ThreeGPP2_ADDR(Octet_String os) {
            this.os = new Octet_String(os);
            threeGpp2Addr = new byte[os.getValue().length];
            threeGpp2Addr = os.getValue();
        }

        public byte[] get_3GPP2_ADDR() {
            return threeGpp2Addr;
        }

        public Octet_String get_3GPP2_Addr_Value() {
            return this.os;
        }
    }

    public class Other_l2_ADDR {

        byte[] other_l2_ADDR;
        Octet_String os;

        public Other_l2_ADDR(byte [] in){
        other_l2_ADDR = new byte[in.length];
        other_l2_ADDR = in;

        os = new Octet_String(in);

        }
        public Other_l2_ADDR(Octet_String os) {
            this.os = new Octet_String(os);
            other_l2_ADDR = new byte[os.getValue().length];
            other_l2_ADDR = os.getValue();

        }

        public Octet_String get_Other_L2_Addr_Value() {
            return this.os;
        }

        public byte[] get_Other_l2_ADDR() {
            return other_l2_ADDR;
        }
    }
}
