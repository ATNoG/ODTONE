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
import odtone_java.inc.Common.Datatypes.Octet_String;
import odtone_java.inc.Common.Types.Address.Transport_address;

//~--- JDK imports ------------------------------------------------------------


/**
 *
 * @author marcelo lebre <marcelolebre@av.it.pt>
 *
 */
/**
 *
 * Class designed to construct a ipconfig object
 * This class nests objects related to IP settings
 *
 */
public class Ipconfig {

    /**
     *
     */
    public class IP_Addr {

        /**
         *
         */
        public static final int IPv4 = 1;
        /**
         *
         */
        public static final int IPv6 = 2;
        byte[] ip_addr;

        public IP_Addr(byte[] in) {
            ip_addr = new byte[in.length];
            ip_addr = in;
        }

        /**
         * Constructor
         * @param Octet_String
         * @param int
         */
        public IP_Addr(Octet_String os, int IPType) {

            Address addr = new Address();
            Transport_address trnsp = addr.new Transport_address(IPType, os);

            ip_addr = new byte[trnsp.get_Transport_address().length];
            ip_addr = trnsp.get_Transport_address();
        }

        /**
         * Getter - Returns IP Addr value in byte [] form
         * @return byte[]
         */
        public byte[] get_IP_Addr() {
            return ip_addr;
        }
    }

    /**
     *
     * Class designed to construct a IP_Cfg_Mthds object
     *
     */
  

    /**
     *
     * Class designed to construct a IP_MOB_MGMT object
     *
     */
   
    public class IP4_Addr {

        byte[] ip4Addr;

        public IP4_Addr(byte[] in) {
            try {
                if (in.length != 4) {
                    throw new Exception("Error: IP4_Addr Requires an Octet(4)");
                } else {
                    ip4Addr = new byte[4];
                    ip4Addr = in;
                }
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }
        }
        public byte [] get_IP4_Addr(){
            return ip4Addr;
        }
        public void set_IP4_Addr(byte [] in){
            ip4Addr = new byte[in.length];
            ip4Addr = in;
        }
    }
    public class IP6_Addr {

        byte[] ip6Addr;

        public IP6_Addr(byte[] in) {
            try {
                if (in.length != 16) {
                    throw new Exception("Error: IP6_Addr Requires an Octet(16)");
                } else {
                    ip6Addr = new byte[16];
                    ip6Addr = in;
                }
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }
        }
        public byte [] get_IP6_Addr(){
            return ip6Addr;
        }
        public void set_IP6_Addr(byte [] in){
            ip6Addr = new byte[in.length];
            ip6Addr = in;
        }
    }
}
