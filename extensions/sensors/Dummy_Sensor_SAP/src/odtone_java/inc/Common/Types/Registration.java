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
import odtone_java.inc.Common.Datatypes.UInt32;

/**
 *
 * @author marcelo lebre <marcelolebre@av.it.pt>
 *
 */
/**
 *
 * Class designed to construct a registration object
 *
 */
public class Registration {

    /**
     *
     * Class designed to construct a Reg_request_code object
     *
     */
    public class Reg_request_code {

        /**
         *
         */
        public static final int reg_request_re_registration = 1;
        /**
         *
         */
        public static final int reg_request_registration = 0;
        /**
         *
         */
        public int regrequestcode;

        /**
         * Getter - Returns Reg Request Code in byte [] form
         * @return byte []
         */
        public int get_Reg_Request_Code() {
            return regrequestcode;
        }

        /**
         * Getter- Returns Reg Request Code in byte[] form
         * @param int
         */
        public void set_Reg_Request_Code(int reg_req_code) {
            regrequestcode = reg_req_code;
        }
    }

    /**
     *
     * Class designed to construct a ValidTimeInterval object
     *
     */
    public class ValidTimeInterval {

        /**
         *
         */
        public UInt32 ValidTimeInterval;

        /**
         * Constructor
         * @param int
         */
        public ValidTimeInterval(int time) {
            ValidTimeInterval = new UInt32(time);
        }

        /**
         * Getter - Returns Valid Time Interval value in byte[] form
         * @return byte []
         */
        public byte[] get_ValidTimeInterval() {
            return ValidTimeInterval.getValue();
        }

        public int getValidTimeIntervalValue() {
            return new UInt32().UInt32ToInt(ValidTimeInterval.getValue());
        }
    }
}
