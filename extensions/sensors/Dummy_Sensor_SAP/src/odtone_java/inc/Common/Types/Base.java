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
import odtone_java.inc.Common.Datatypes.UInt8;

/**
 *
 * @author marcelo lebre <marcelolebre@av.it.pt>
 *
 */
/**
 *
 * Class designed to construct a some basic objects
 *
 */
public class Base {

    /**
     *
     * Class designed to construct IPRenewalFlag object
     *
     */
    public class IP_Renewal_Flag {

        byte[] iprenewallflag = new byte[1];

        /**
         *  Constructor
         * @param boolean
         */
        public IP_Renewal_Flag(boolean bool) {
            if (bool) {
                iprenewallflag[0] = (byte) 1;
            } else {
                iprenewallflag[0] = (byte) 0;
            }
        }
        public IP_Renewal_Flag(byte  in) {
            if (in == 1) {
                iprenewallflag[0] = (byte) 1;
            } else {
                iprenewallflag[0] = (byte) 0;
            }
        }
        /**
         * Getter - returns iprenewellflag value in byte[] form
         * @return byte []
         */
        public byte[] get_IP_Renewal_Flag() {
            return iprenewallflag;
        }
    }

    /**
     *
     * Class designed to construct Percentage object
     *
     */
    public class Percentage {

        UInt8 percentage;

        /**
         * Constructor
         * 
         * @param int
         */
        public Percentage(int value) {
            if ((value <= 100) & (value >= 0)) {
                percentage = new UInt8(value);
            } else {
                throw new IndexOutOfBoundsException();
            }
        }

        /**
         * Getter - Returns the percentage value in byte [] form
         *
         * @return byte[]
         */
        public byte[] get_Percentage() {
            return percentage.getValue();
        }
    }

     /**
     *
     * Class designed to construct Status object
     *
     */
    public class Status {

        /**
         *
         */
        public static final int authorization_failure = 3;
        /**
         *
         */
        public static final int network_error = 4;
        /**
         *
         */
        public static final int rejected = 2;
        /**
         *
         */
        public static final int success = 0;
        /**
         *
         */
        public static final int unspecified_failure = 1;
        /**
         *
         */
        public UInt8 status;

        /**
         * Constructor
         * @param int
         */
        public Status(int i) {
            status = new UInt8();

            if (i < 5 & i >= 0) {
                status = new UInt8(i);
            } else {
                throw new IndexOutOfBoundsException();
            }
        }

        /**
         * Getter - Returns the status value in byte[] form
         * @return
         */
        public byte[] get_Status() {
            return status.getValue();
        }
    }
}
