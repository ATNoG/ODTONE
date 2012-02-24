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
import odtone_java.inc.Common.Serialization;

/**
 *
 * @author marcelo lebre <marcelolebre@av.it.pt>
 *
 */
/**
 *
 * Class designed to construct a rdf_query related objects
 * This class nests objects related to the MIIS's rdf querys
 *
 */
public class Rdf_Query {
/**
 *
 * Class designed to construct a IQ_Rdf_Data related objects
 *
 */    public class IQ_Rdf_Data {
        byte[] iq_rdf_data;

        /**
         * Constructor
         * @param String
         */
        public IQ_Rdf_Data(String s) {
            Serialization srlz = new Serialization();
            Octet_String  tmp  = new Octet_String(s);

            iq_rdf_data = new byte[srlz.sequence(srlz.choice(null, 0), tmp.getValue()).length];
            iq_rdf_data = srlz.sequence(srlz.choice(null, 0), tmp.getValue());
        }

        /**
         * Constructor
         * @param String
         * @param String
         */
        public IQ_Rdf_Data(String MimeType, String s) {
            Serialization srlz = new Serialization();
            Octet_String  tmp  = new Octet_String(s);
            Octet_String  tmp2 = new Octet_String(MimeType);

            iq_rdf_data = new byte[srlz.sequence(srlz.choice(tmp2.getValue(), 1), tmp.getValue()).length];
            iq_rdf_data = srlz.sequence(srlz.choice(tmp2.getValue(), 1), tmp.getValue());
        }

        /**
         * Getter - Retuns IQ Rdf Data Value in byte [] form
         * @return byte []
         */
        public byte[] get_IQ_Rdf_Data() {
            return iq_rdf_data;
        }
    }


    /**
 *
 * Class designed to construct a IQ_Rdf_Schm related objects
 *
 */
    public class IQ_Rdf_Schm {
        Octet_String iq_rdf_schm;

        /**
         * Constructor
         * @param String
         */
        public IQ_Rdf_Schm(String s) {
            iq_rdf_schm = new Octet_String(s);
        }

        /**
         * Getter - Returns IQ Rdf Schm value in byte [] form
         * @return byte []
         */
        public byte[] Get_IQ_Rdf_Schm() {
            return iq_rdf_schm.getValue();
        }
    }


   /**
 *
 * Class designed to construct a IR_Rdf_Data related objects
 *
 */
    public class IR_Rdf_Data {
        byte[] ir_rdf_data;

        /**
         * Constructor
         * @param String
         */
        public IR_Rdf_Data(String s) {
            Serialization srlz = new Serialization();
            Octet_String  tmp  = new Octet_String(s);

            ir_rdf_data = new byte[srlz.sequence(srlz.choice(null, 0), tmp.getValue()).length];
            ir_rdf_data = srlz.sequence(srlz.choice(null, 0), tmp.getValue());
        }

        /**
         * Constructor
         * @param String
         * @param String
         */
        public IR_Rdf_Data(String MimeType, String s) {
            Serialization srlz = new Serialization();
            Octet_String  tmp  = new Octet_String(s);
            Octet_String  tmp2 = new Octet_String(MimeType);

            ir_rdf_data = new byte[srlz.sequence(srlz.choice(tmp2.getValue(), 1), tmp.getValue()).length];
            ir_rdf_data = srlz.sequence(srlz.choice(tmp2.getValue(), 1), tmp.getValue());
        }

        /**
         * Getter - Returns IR Rdf Data value in byte [] form
         * @return byte []
         */
        public byte[] Get_IR_Rdf_Data() {
            return ir_rdf_data;
        }
    }


    /**
 *
 * Class designed to construct a IR_Rdf_SCHM related objects
 *
 */
    public class IR_Rdf_SCHM {
        byte[] ir_rdf_schm;

        /**
         * Constructor
         * @param String
         */
        public IR_Rdf_SCHM(String s) {
            Serialization srlz = new Serialization();
            Octet_String  tmp  = new Octet_String(s);

            ir_rdf_schm = new byte[srlz.sequence(srlz.choice(null, 0), tmp.getValue()).length];
            ir_rdf_schm = srlz.sequence(srlz.choice(null, 0), tmp.getValue());
        }

        /**
         * Constructor
         * @param String
         * @param String
         */
        public IR_Rdf_SCHM(String MimeType, String s) {
            Serialization srlz = new Serialization();
            Octet_String  tmp  = new Octet_String(s);
            Octet_String  tmp2 = new Octet_String(MimeType);

            ir_rdf_schm = new byte[srlz.sequence(srlz.choice(tmp2.getValue(), 1), tmp.getValue()).length];
            ir_rdf_schm = srlz.sequence(srlz.choice(tmp2.getValue(), 1), tmp.getValue());
        }

        /**
         * Getter - Returns IR Rdf SCHM value in byte [] form
         * @return byte []
         */
        public byte[] Get_IR_Rdf_SCHM() {
            return ir_rdf_schm;
        }
    }


    /**
 *
 * Class designed to construct a IR_Schm_URL related objects
 *
 */
    public class IR_Schm_URL {
        Octet_String ir_schm_url;

        /**
         * Constructor
         * @param String
         */
        public IR_Schm_URL(String s) {
            ir_schm_url = new Octet_String(s);
        }

        /**
         * Getter - Returns IR Schm URL value in byte [] form
         * @return byte []
         */
        public byte[] Get_IR_Schm_URL() {
            return ir_schm_url.getValue();
        }
    }
}