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
import odtone_java.inc.Common.Datatypes.Octet;
import odtone_java.inc.Common.Datatypes.Octet_String;
import odtone_java.inc.Common.Datatypes.UInt16;
import odtone_java.inc.Common.Datatypes.UInt32;
import odtone_java.inc.Common.Datatypes.UInt8;
import odtone_java.inc.Common.Serialization;
import odtone_java.inc.Common.Types.Address.Link_Address;
import odtone_java.inc.Common.Types.Ipconfig.IP4_Addr;
import odtone_java.inc.Common.Types.Ipconfig.IP6_Addr;
import odtone_java.inc.Common.Types.Ipconfig.IP_Addr;
import odtone_java.inc.Common.Types.Link.Link_Type;
import odtone_java.inc.Common.Types.Link.Subtype;
import odtone_java.inc.Common.Types.Link.Type_Ext;
import odtone_java.inc.Common.Types._Location.Cell_ID;

/**
 *
 * @author marcelo lebre <marcelolebre@av.it.pt>
 *
 */
/**
 *
 * Class designed to construct a Information object
 * In this class several nested objects are defined and can be constructed
 * mainly to support the Information System
 *
 */
public class Information {

    /**
     *
     */
    public class Civic_Addr {

        byte[] civic_addr;

        /**
         * Constructor
         * @param String
         */
        public Civic_Addr(String s) {
            Octet_String os = new Octet_String(s);

            civic_addr = os.getValue();
        }

        /**
         * Getter  - returns civic addr in byte[] form
         * @return byte []
         */
        public byte[] get_Civic_Addr() {
            return civic_addr;
        }
    }

    /**
     *
     */
    public class Cntry_Code {

        byte[] cntry_code;

        /**
         *
         * @param s
         */
        public Cntry_Code(String s) {
            cntry_code = new byte[2];

            cntry_code = new Octet(s.getBytes()).getValue();

        }

        /**
         *
         * @return
         */
        public byte[] get_Cntry_Code() {
            return cntry_code;
        }

        public void set_Cntry_Code(byte[] in) {
            cntry_code = new byte[in.length];
            cntry_code = in;
        }
    }

    /**
     *
     */
    public class Cost_Curr {

        byte[] cost_curr;

        /**
         *
         * @param s
         */
        public Cost_Curr(byte[] in) {
            try {
                if (in.length == 3) {
                    cost_curr = new byte[3];

                    cost_curr = in;
                } else {
                    throw new Exception("Error, Cost_Curr is an Octet(3)");
                }
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }
        }

        /**
         *
         * @return
         */
        public byte[] get_Cost_Curr() {
            return cost_curr;
        }

        public void set_Cost_Curr(byte[] in) {
            cost_curr = new byte[3];
            cost_curr = in;
        }
    }

    /**
     *
     */
    public class Max_Response_Size {

        UInt16 max_response_size;

        /**
         *
         * @param size
         */
        public Max_Response_Size(int size) {
            max_response_size = new UInt16(size);
        }

        /**
         *
         * @return
         */
        public byte[] get_Max_Response_Size() {
            return max_response_size.getValue();
        }
    }

    /**
     *
     */
    public class Network_type {

        byte[] net_type_out, link_type_out, subtype_out, typeext_out;
        Link_Type lt;
        Subtype st;
        Type_Ext te;
        /**
         *
         */
        public byte[] network_type;
        /**Network_type
         *
         */
        public Octet_String type_ext;

        public Network_type(byte[] in) {
            net_type_out = new byte[in.length];
            net_type_out = in;
        }

        public Network_type(Network_type nt) {
        }

        public Link_Type get_Link_Type() {
            return lt;
        }

        public Subtype get_Sub_Type() {
            return st;
        }

        public Type_Ext get_Type_Ext() {
            return te;
        }

        /**
         *
         * @param lnktp
         * @param sbtp
         * @param typeext
         */
        public Network_type(Link_Type lnktp, Subtype sbtp, Type_Ext typeext) {
            Link link = new Link();
            lt = link.new Link_Type(lnktp);
            st = link.new Subtype(sbtp);
            type_ext = typeext.get_Type_Ext_Value();


            Serialization srlz = new Serialization();
            // Processing Choice(null,link_type)
            if (lnktp == null) {
                link_type_out = new byte[srlz.choice(null, 0).length];
                link_type_out = srlz.choice(null, 0);
            } else {
                link_type_out = new byte[srlz.choice(lnktp.get_Link_Type(), 1).length];
                link_type_out = srlz.choice(lnktp.get_Link_Type(), 1);
            }

            // Processing Choice(null,subtype)
            if (sbtp == null) {
                subtype_out = new byte[srlz.choice(null, 0).length];
                subtype_out = srlz.choice(null, 0);
            } else {
                subtype_out = new byte[srlz.choice(sbtp.get_SubType(), 1).length];
                subtype_out = srlz.choice(sbtp.get_SubType(), 1);
            }

            // Processing Choice(null,typeext)
            if (typeext == null) {
                typeext_out = new byte[srlz.choice(null, 0).length];
                typeext_out = srlz.choice(null, 0);
            } else {
                typeext_out = new byte[srlz.choice(typeext.get_TypeExt(), 1).length];
                typeext_out = srlz.choice(typeext.get_TypeExt(), 1);
            }

            // Now sequencing the previous choices
            int sz = link_type_out.length + subtype_out.length + typeext_out.length;

            network_type = new byte[sz];

            int i, pos = 0;

            for (i = 0; i < link_type_out.length; i++) {
                network_type[i] = link_type_out[i];
                pos++;
            }

            // Encoding Value
            for (i = 0; i < subtype_out.length; i++) {
                network_type[pos] = subtype_out[i];
                pos++;
            }

            for (i = 0; i < typeext_out.length; i++, pos++) {
                network_type[pos] = typeext_out[i];
            }
        }

        /**
         *
         * @return
         */
        public byte[] get_network_type() {
            return network_type;
        }
    }

    /**
     *
     */
    public class Network_type_addr {

        // Sequence(NetworkType, Link_Addr
        byte[] network_type_addr;
        Network_type nt;
        Link_Address la;

        /**
         *Empty constructor
         */
        public Network_type_addr() {
        }

        /**
         * Constructor
         * @param Network_type
         * @param Link_address
         */
        public Network_type_addr(Network_type netType, Link_Address lnkadd) {
            Address add = new Address();
            nt = new Network_type(netType.get_Link_Type(), netType.get_Sub_Type(), netType.get_Type_Ext());
            la = add.new Link_Address(lnkadd);

            network_type_addr = new byte[netType.get_network_type().length + lnkadd.get_link_address().length];

            // Encoding link_address //
            int i, pos;

            for (i = 0, pos = 0; i < lnkadd.get_link_address().length; i++, pos++) {
                network_type_addr[i] = lnkadd.get_link_address()[i];
            }

            // Encoding network_type
            for (i = 0; i < lnkadd.get_link_address().length; i++, pos++) {
                network_type_addr[pos] = lnkadd.get_link_address()[i];
            }

            // sequence for network_type_addr encoded
        }

        /**
         * Getter - returns the network type address in byte [] form
         * @return byte []
         */
        public byte[] get_Network_type_addr() {
            return network_type_addr;
        }

        public Network_type get_Network_type() {
            return nt;
        }

        public Link_Address get_Link_Address() {
            return la;
        }

        /**
         * Setter - Sets the network type address value
         * @return void
         */
        public void set_Value(byte[] in) {
            network_type_addr = new byte[in.length];
            network_type_addr = in;
        }
    }

    public class OP_Name {

        byte[] opName;

        public OP_Name(String in) {
            try {
                if (in.length() > 253) {
                    throw new Exception("Error : The octet strings length shall not exceed 253 octets");
                } else {
                    opName = new byte[in.length()];
                    opName = (new Octet_String(in)).getValue();
                }
            } catch (Exception e) {
                e.getMessage();
            }
        }

        public byte[] get_opName() {
            return opName;
        }

        public String get_opName_Value() {
            return (new String(opName));
        }

        public void set_opName(byte[] in) {
            opName = new byte[in.length];
            opName = in;
        }
    }

    public class OP_Namespace {

        byte[] opNamespace;
        //Types that represent an operator name
        int GSM_UMTS = 0;
        int CDMA = 1;
        int REALM = 2;
        int ITU_T_TSB = 3;
        int GENERAL = 4;

        public OP_Namespace(int in) {
            try {
                if (in > 255 | in < 0) {
                    throw new Exception("Error : not an Unsigned Int(1)");
                } else {
                    opNamespace = new byte[1];
                    opNamespace = (new UInt8(in)).getValue();
                }
            } catch (Exception e) {
                e.getMessage();
            }
        }

        public byte[] get_op_Namespace() {
            return opNamespace;
        }

        public int get_op_Namespace_Value() {
            return (new UInt8().UInt8ToInt(opNamespace[0]));
        }

        public void get_op_Namespace(byte[] in) {
            opNamespace = new byte[in.length];
            opNamespace = in;
        }
    }

    public class Operator_ID {

        byte[] operatorID;
        Serialization srlz = new Serialization();

        public Operator_ID() {
        }

        public Operator_ID(OP_Name opName, OP_Namespace opNamespace) {
            operatorID = new byte[srlz.sequence(opName.get_opName(), opNamespace.get_op_Namespace()).length];
            operatorID = srlz.sequence(opName.get_opName(), opNamespace.get_op_Namespace());
        }

        public byte[] get_Operator_ID() {
            return operatorID;
        }

        public void set_Operator_ID(byte[] in) {
            operatorID = new byte[in.length];
            operatorID = in;
        }
    }

    public class SP_ID {

        byte[] spID;

        public SP_ID(String in) {

            spID = new byte[in.length()];
            Octet_String os = new Octet_String();
            os.setValue(in.getBytes());
            spID = os.getValue();
        }

        public byte[] get_SP_ID() {
            return spID;
        }

        public String get_SP_ID_Value() {
            return (new String(spID));
        }

        public void set_SP_ID(byte[] in) {
            spID = new byte[in.length];
            spID = in;
        }
    }

   
    public class Cost_Value {

        byte[] costValue;
        Serialization srlz = new Serialization();

        public Cost_Value(UInt32 in1, UInt16 in2) {
            costValue = new byte[srlz.sequence(in1.getValue(), in2.getValue()).length];
            costValue = srlz.sequence(in1.getValue(), in2.getValue());
        }

        public byte[] get_Cost_Value() {
            return costValue;
        }

        public void set_Cost_Value(byte[] in) {
            costValue = new byte[in.length];
            costValue = in;
        }
    }

    public class Cost_Unit {

        byte[] costUnit;
        Serialization srlz = new Serialization();
        //Type to represent the unit of a cost
        int second = 0;
        int minute = 1;
        int hours = 2;
        int day = 3;
        int week = 4;
        int month = 5;
        int year = 6;
        int free = 7;
        int flat_rate = 8;
        ///////////////////////////////////////////

        public Cost_Unit(UInt8 in) {
            costUnit = new byte[in.getValue().length];
            costUnit = in.getValue();
        }

        public byte[] get_Cost_Unit() {
            return costUnit;
        }

        public int get_Cost_Unit_Value() {
            return (new UInt8().UInt8ToInt(costUnit[0]));
        }

        public void set_Cost_Unit(byte[] in) {
            costUnit = new byte[in.length];
            costUnit = in;
        }
    }

    public class Cost {

        byte[] cost;
        Serialization srlz = new Serialization();

        public Cost(Cost_Unit costUnit, Cost_Value costValue, Cost_Curr costCurr) {
            cost = new byte[srlz.sequence(costUnit.get_Cost_Unit(), costValue.get_Cost_Value(), costCurr.get_Cost_Curr()).length];
            cost = srlz.sequence(costUnit.get_Cost_Unit(), costValue.get_Cost_Value(), costCurr.get_Cost_Curr());
        }

        public byte[] get_Cost() {
            return cost;
        }
    }

    public class Data_Rate {

        byte[] dataRate;

        public Data_Rate(UInt32 in) {
            dataRate = new byte[in.getValue().length];
            dataRate = in.getValue();
        }

        public byte[] get_Data_Rate() {
            return dataRate;
        }

        public void set_Data_Rate(byte[] in) {
            dataRate = new byte[in.length];
            dataRate = in;
        }

        public int get_Data_Rate_Value() {
            return (new UInt32().UInt32ToInt(dataRate));
        }
    }

    public class Regu_Domain {

        byte[] reguDomain;
        Serialization srlz = new Serialization();

        public Regu_Domain(Cntry_Code cntryCode, UInt8 in) {
            reguDomain = new byte[srlz.sequence(cntryCode.get_Cntry_Code(), in.getValue()).length];
            reguDomain = srlz.sequence(cntryCode.get_Cntry_Code(), in.getValue());
        }

        public byte[] get_Regu_Domain() {
            return reguDomain;
        }

        public void set_Regu_Domain(byte[] in) {
            reguDomain = new byte[in.length];
            reguDomain = in;
        }
    }

   

    public class DHCP_Serv {

        byte[] dhcpServ;

        public DHCP_Serv(IP_Addr ip) {
            dhcpServ = new byte[ip.get_IP_Addr().length];
            dhcpServ = ip.get_IP_Addr();
        }

        public byte[] get_DHCP_Serv() {
            return dhcpServ;
        }

        public void set_DHCP_Serv(byte[] in) {
            dhcpServ = new byte[in.length];
            dhcpServ = in;
        }
    }

    public class FN_Agnt {

        byte[] fnAgnt;

        public FN_Agnt(IP_Addr ip) {
            fnAgnt = new byte[ip.get_IP_Addr().length];
            fnAgnt = ip.get_IP_Addr();
        }

        public byte[] get_FN_Agnt() {
            return fnAgnt;
        }

        public void set_FN_Agnt(byte[] in) {
            fnAgnt = new byte[in.length];
            fnAgnt = in;
        }
    }

    public class ACC_Rtr {

        byte[] accRtr;

        public ACC_Rtr(IP_Addr ip) {
            accRtr = new byte[ip.get_IP_Addr().length];
            accRtr = ip.get_IP_Addr();
        }

        public byte[] get_ACC_Rtr() {
            return accRtr;
        }

        public void set_ACC_Rtr(byte[] in) {
            accRtr = new byte[in.length];
            accRtr = in;
        }
    }

   

    public class Supported_LCP {

        byte[] supportedLCP;
        int _NULL = 0;
        int LLDP = 1;
        int LLDP_MED = 11;
        int LbyR_with_LLDPMED = 12;
        int U_TDoA = 21;
        int D_TDoA = 22;
        int DHCP = 31;
        int LbyT_with_DHCP = 32;
        int OMA_SUPL = 41;
        int IEEE_80211 = 41;
        int LbyR_with_IEEE80211 = 43;
        int HELD = 51;
        int LbyR_width_HELD = 52;

        public Supported_LCP(UInt8 in) {
            supportedLCP = new byte[in.getValue().length];
            supportedLCP = in.getValue();
        }

        public byte[] get_Supported_LCP() {
            return supportedLCP;
        }

        public int get_Supported_LCP_Value() {
            return new UInt8().UInt8ToInt(supportedLCP[0]);
        }

        public void set_Supported_LCP(byte[] in) {
            supportedLCP = new byte[in.length];
            supportedLCP = in;
        }
    }

    public class FQDN {

        byte[] fqdn;

        public FQDN(String in) {
            fqdn = new byte[new Octet_String(in).getValue().length];
            fqdn = new Octet_String(in).getValue();
        }

        public String get_FQDN_Value() {
            return new String(fqdn);
        }

        public byte[] get_FQDN() {
            return fqdn;
        }

        public void set_FQDN(byte[] in) {
            fqdn = new byte[in.length];
            fqdn = in;
        }
    }

    public class Proxy_Addr {

        byte[] proxyAddr;
        Serialization srlz = new Serialization();

        public Proxy_Addr(Object o) {

            if (o.getClass() == IP4_Addr.class) {
                proxyAddr = new byte[srlz.choice(((IP4_Addr) o).get_IP4_Addr(), 0).length];
                proxyAddr = srlz.choice(((IP4_Addr) o).get_IP4_Addr(), 0);
            }
            if (o.getClass() == IP6_Addr.class) {
                proxyAddr = new byte[srlz.choice(((IP6_Addr) o).get_IP6_Addr(), 1).length];
                proxyAddr = srlz.choice(((IP6_Addr) o).get_IP6_Addr(), 1);
            }
            if (o.getClass() == FQDN.class) {
                proxyAddr = new byte[srlz.choice(((FQDN) o).get_FQDN(), 2).length];
                proxyAddr = srlz.choice(((FQDN) o).get_FQDN(), 2);
            }

        }

        public byte[] get_Proxy_Addr() {
            return proxyAddr;
        }

        public void set_Proxy_Addr(byte[] in) {
            proxyAddr = new byte[in.length];
            proxyAddr = in;
        }
    }

    public class CH_Range {

        byte[] chRange;
        Serialization srlz = new Serialization();

        public CH_Range(UInt32 in1, UInt32 in2) {
            chRange = new byte[srlz.sequence(in1.getValue(), in2.getValue()).length];
            chRange = srlz.sequence(in1.getValue(), in2.getValue());
        }

        public byte[] get_CH_Range() {
            return chRange;
        }

        public void set_CH_Range(byte[] in) {
            chRange = new byte[in.length];
            chRange = in;
        }
    }

    public class Base_ID {

        byte[] baseID;

        public Base_ID(UInt16 in) {
            baseID = new byte[in.getValue().length];
            baseID = in.getValue();
        }

        public UInt16 get_Base_ID_Value() {
            UInt16 out = new UInt16();
            out.setValue(baseID);
            return out;
        }

        public byte[] get_Base_ID() {
            return baseID;
        }

        public void set_Base_ID(byte[] in) {
            baseID = new byte[in.length];
            baseID = in;
        }
    }

    public class Bandwidth {

        byte[] bandwitdh;

        public Bandwidth(UInt16 in) {
            bandwitdh = new byte[in.getValue().length];
            bandwitdh = in.getValue();
        }

        public UInt16 get_Bandwidth_Value() {
            UInt16 out = new UInt16();
            out.setValue(bandwitdh);
            return out;
        }

        public byte[] get_Bandwidth() {
            return bandwitdh;
        }

        public void set_Bandwidth(byte[] in) {
            bandwitdh = new byte[in.length];
            bandwitdh = in;
        }
    }

    public class Du_Ctr_Freq {

        byte[] duCtrFreq;

        public Du_Ctr_Freq(long in) {
            duCtrFreq = new byte[8];
            for (int i = 0; i < 8; i++) {
                duCtrFreq[i] = (byte) (in >> (56 - i * 8));
            }
        }

        public byte[] get_Du_Ctr_Freq() {
            return duCtrFreq;
        }

        public long get_Du_Ctr_Freq_Value() {
            long l = 0;
            l |= duCtrFreq[0] & 0xFF;
            l <<= 8;
            l |= duCtrFreq[1] & 0xFF;
            l <<= 8;
            l |= duCtrFreq[2] & 0xFF;
            l <<= 8;
            l |= duCtrFreq[3] & 0xFF;
            l <<= 8;
            l |= duCtrFreq[4] & 0xFF;
            l <<= 8;
            l |= duCtrFreq[5] & 0xFF;
            l <<= 8;
            l |= duCtrFreq[6] & 0xFF;
            l <<= 8;
            l |= duCtrFreq[7] & 0xFF;
            l <<= 8;
            l |= duCtrFreq[8] & 0xFF;
            return l;
        }

        public void set_Du_Ctr_Freq(byte[] in) {
            duCtrFreq = new byte[in.length];
            duCtrFreq = in;
        }
    }

    public class EIRP {

        byte[] eirp;

        public EIRP(int in) {

            eirp = new byte[1];
            eirp[0] = (byte) in;

        }

        public byte[] get_EIRP() {
            return eirp;
        }

        public int get_EIRP_Value() {
            return (int) eirp[0];
        }

        public void set_EIRP(byte[] in) {
            eirp = new byte[in.length];
            eirp = in;
        }
    }

    
  

  

    public class Init_Code {

        byte[] initCode;

        public Init_Code(int in) {

            initCode = new byte[1];
            initCode[0] = (byte) in;

        }

        public byte[] get_Init_Code() {
            return initCode;
        }

        public int get_Init_Code_Value() {
            return (int) initCode[0];
        }

        public void set_Init_Code(byte[] in) {
            initCode = new byte[in.length];
            initCode = in;
        }
    }

    public class HO_Code {

        byte[] hoCode;

        public HO_Code(int in) {

            hoCode = new byte[1];
            hoCode[0] = (byte) in;

        }

        public byte[] get_HO_Code() {
            return hoCode;
        }

        public int get_HO_Code_Value() {
            return (int) hoCode[0];
        }

        public void set_HO_Code(byte[] in) {
            hoCode = new byte[in.length];
            hoCode = in;
        }
    }

    public class CDMA_Codes {

        byte[] cdmaCodes;
        Serialization srlz = new Serialization();

        public CDMA_Codes(Init_Code initCode, HO_Code hoCode) {
            cdmaCodes = new byte[srlz.sequence(initCode.get_Init_Code(), hoCode.get_HO_Code()).length];
            cdmaCodes = srlz.sequence(initCode.get_Init_Code(), hoCode.get_HO_Code());
        }

        public byte[] get_CDMA_Codes() {
            return cdmaCodes;
        }

        public void set_CDMA_Codes(byte[] in) {
            cdmaCodes = new byte[in.length];
            cdmaCodes = in;
        }
    }

    public class Gap {

        byte[] gap;
        Serialization srlz = new Serialization();

        public Gap(UInt16 in1, UInt8 in2) {
            gap = new byte[3];
            gap = srlz.sequence(in1.getValue(), in2.getValue());
        }

        public byte[] get_Gap() {
            return gap;
        }

        public void set_Gap(byte[] in) {
            gap = new byte[3];
            gap = in;
        }
    }

   
    public class FQ_Code_Num {

        byte[] fqCodeNum;

        public FQ_Code_Num() {
        }

        public FQ_Code_Num(int in) {
            fqCodeNum = new byte[2];
            fqCodeNum[0] = (byte) (in >> 8);
            fqCodeNum[1] = (byte) (in);
        }

        public byte[] get_FQ_Code_Num() {
            return fqCodeNum;
        }

        public int get_FQ_Code_Num_value() {
            int l = 0;
            l |= fqCodeNum[0] & 0xFF;
            l <<= 8;
            l |= fqCodeNum[1] & 0xFF;
            return l;


        }

        public void set_FQ_Code_Num(byte[] in) {
            fqCodeNum = new byte[in.length];
            fqCodeNum = in;
        }
    }

    public class SIB {

        byte[] sib;
        Serialization srlz = new Serialization();

        public SIB() {
        }

        public SIB(Cell_ID cellID, FQ_Code_Num fqCodeNum) {
            sib = new byte[srlz.sequence(cellID.get_Cell_ID(), fqCodeNum.get_FQ_Code_Num()).length];
            sib = srlz.sequence(cellID.get_Cell_ID(), fqCodeNum.get_FQ_Code_Num());
        }

        public void set_SIB(byte[] sib) {
            this.sib = sib;
        }

        public byte[] get_SIB() {
            return sib;
        }
    }

    public class Pilot_PN {

        byte[] pilotPN;

        public Pilot_PN() {
        }

        public Pilot_PN(int in) {
            pilotPN = new byte[2];
            pilotPN[0] = (byte) (in >> 8);
            pilotPN[1] = (byte) (in);
        }

        public byte[] get_Pilot_PN() {
            return pilotPN;
        }

        public int get_Pilot_PN_Value() {
            int l = 0;
            l |= pilotPN[0] & 0xFF;
            l <<= 8;
            l |= pilotPN[1] & 0xFF;
            return l;


        }

        public void set_Pilot_PN(byte[] in) {
            pilotPN = new byte[in.length];
            pilotPN = in;
        }
    }

    public class Freq_ID {

        byte[] freqID;

        public Freq_ID() {
        }

        public Freq_ID(int in) {
            freqID = new byte[2];
            freqID[0] = (byte) (in >> 8);
            freqID[1] = (byte) (in);
        }

        public byte[] get_Freq_ID() {
            return freqID;
        }

        public int get_Freq_ID_Value() {
            int l = 0;
            l |= freqID[0] & 0xFF;
            l <<= 8;
            l |= freqID[1] & 0xFF;
            return l;


        }

        public void set_Freq_ID(byte[] in) {
            freqID = new byte[in.length];
            freqID = in;
        }
    }

    public class Band_Class {

        byte[] bandClass;

        public Band_Class() {
        }

        public Band_Class(UInt8 i) {
            bandClass = new byte[1];
            bandClass = i.getValue();
        }

        public void set_Band_Class(byte[] bandClass) {
            this.bandClass = bandClass;
        }

        public int get_Band_Class_Value() {
            UInt8 out = new UInt8();
            out.setValue(bandClass);
            return out.UInt8ToInt(bandClass[0]);
        }

        public byte[] get_Band_Class() {
            return bandClass;
        }
    }

    public class SYS_Params {

        byte[] sysParams;
        Serialization srlz = new Serialization();

        public SYS_Params() {
        }

        public SYS_Params(Base_ID baseID, Pilot_PN pilotPN, Freq_ID freqID, Band_Class bandClass) {
            sysParams = new byte[srlz.sequence(baseID.get_Base_ID(), pilotPN.get_Pilot_PN(), freqID.get_Freq_ID(), bandClass.get_Band_Class()).length];
            sysParams = srlz.sequence(baseID.get_Base_ID(), pilotPN.get_Pilot_PN(), freqID.get_Freq_ID(), bandClass.get_Band_Class());
        }

        public void set_SYS_Params(byte[] sysParams) {
            this.sysParams = sysParams;
        }

        public byte[] get_SYS_Params() {
            return sysParams;
        }
    }

    

    
    public class IP_Prefix_Len {

        byte[] ipPrefixLen;

        public IP_Prefix_Len(UInt8 in) {
            ipPrefixLen = new byte[1];
            ipPrefixLen = in.getValue();

        }

        public void set_IP_Prefix_Len(byte[] in) {
            ipPrefixLen = new byte[in.length];
        }

        public byte[] get_IP_Prefix_Len() {
            return ipPrefixLen;
        }
    }

    public class IP_Subnet_Info {

        byte[] ipSubnetInfo;
        Serialization srlz = new Serialization();

        public IP_Subnet_Info(IP_Prefix_Len ipPrefixLen, IP_Addr ipaddr) {
            ipSubnetInfo = new byte[srlz.sequence(ipPrefixLen.get_IP_Prefix_Len(), ipaddr.get_IP_Addr()).length];
            ipSubnetInfo = srlz.sequence(ipPrefixLen.get_IP_Prefix_Len(), ipaddr.get_IP_Addr());
        }

        public byte[] get_IP_Subnet_Info() {
            return ipSubnetInfo;
        }

        public void set_IP_Subnet_Info(byte[] in) {
            ipSubnetInfo = new byte[in.length];
            ipSubnetInfo = in;

        }
    }
}
