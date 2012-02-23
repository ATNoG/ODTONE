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


package odtone_java.inc.Common.MessageHandler;

//~--- non-JDK imports --------------------------------------------------------

import odtone_java.inc.Common.Datatypes.UInt8;
import odtone_java.inc.Common.Datatypes.UInt64;
import odtone_java.inc.Common.Datatypes.UInt16;

/**
 *
 * @author marcelo lebre <marcelolebre@av.it.pt>
 *
 */
/**
 *
 * Class designed to implement a MIH Protocol Header
 *
 */
public class MIH_Protocol_Header {
    /**
     *
     */
    public UInt8   Rsvd2                 = new UInt8(0x00);
    /**
     *
     */
    public UInt16  VariablePayloadLength = new UInt16();
    /**
     *
     */
    public boolean ACKREQ;
    /**
     *
     */
    public boolean ACKRSP;
    /**
     *
     */
    public UInt8   FN;
    /**
     *
     */
    public boolean M;
    /**
     *
     */
    public UInt16  MID;
    /**
     *
     */
    public boolean Rsvd1;
    /**
     *
     */
    public UInt16  TransactionID;
    /**
     *
     */
    public boolean UIR;
    /**
     *
     */
    public UInt8   Version;

    /**
     *
     * Getter - returns the Mih protocol header in UINT64 format
     *
     * @return UINT64
     */
    public UInt64 get_MIH_Protocol_Header() {
        UInt64 Header = new UInt64();

        Header.getValue()[0] = 0x00;

        try {

            // POPULATING MESSAGE HEADER
            Header.getValue()[0] = (byte) ((Header.getValue()[0] | Version.getValue()[0]) << 4);

            if (ACKREQ) {
                Header.getValue()[0] = (byte) (Header.getValue()[0] | 0x08);
            } else {
                Header.getValue()[0] = (byte) (Header.getValue()[0] | 0x00);
            }

            if (ACKRSP) {
                Header.getValue()[0] = (byte) (Header.getValue()[0] | 0x04);
            } else {
                Header.getValue()[0] = (byte) (Header.getValue()[0] | 0x00);
            }

            if (UIR) {
                Header.getValue()[0] = (byte) (Header.getValue()[0] | 0x02);
            } else {
                Header.getValue()[0] = (byte) (Header.getValue()[0] | 0x00);
            }

            if (M) {
                Header.getValue()[0] = (byte) (Header.getValue()[0] | 0x01);
            } else {
                Header.getValue()[0] = (byte) (Header.getValue()[0] | 0x00);
            }

            // /FIRST OCTET COMPLETE
            // PROCEDING TO SECOND OCTET

            Header.getValue()[1] = 0x00;
            Header.getValue()[1] = (byte) ((Header.getValue()[1] | FN.getValue()[0]) << 1);

            if (Rsvd1) {
                Header.getValue()[1] = (byte) (Header.getValue()[1] | 0x01);
            } else {
                Header.getValue()[1] = (byte) (Header.getValue()[1] | 0x00);
            }

            // /SECOND OCTET COMPLETE
            // PROCEDING TO THIRD OCTET
            Header.getValue()[2] = 0x00;
            Header.getValue()[2] = (byte) (Header.getValue()[2] | MID.getValue()[0]);

            // /THIRD OCTET COMPLETE
            // PROCEDING TO FOURTH OCTET
            Header.getValue()[3] = 0x00;
            Header.getValue()[3] = (byte) (Header.getValue()[3] | MID.getValue()[1]);

            // /FOURTH OCTET COMPLETE
            // PROCEDING TO FIFTH OCTET
            Header.getValue()[4] = 0x00;
            Header.getValue()[4] = (byte) ((Header.getValue()[4] | Rsvd2.getValue()[0]) << 4);
            Header.getValue()[4] = (byte) ((Header.getValue()[4] | (TransactionID.getValue()[0] & 0x0F)));

            // /FIFTH OCTET COMPLETE
            // PROCEDING TO SIXTH OCTET
            Header.getValue()[5] = (byte) (Header.getValue()[5] | TransactionID.getValue()[1]);

            // /SIXTH OCTET COMPLETE
            // PROCEDING TO SEVENTH OCTET
            Header.getValue()[6] = (byte) (Header.getValue()[6] | VariablePayloadLength.getValue()[0]);

            // /SIXTH OCTET COMPLETE
            // PROCEDING TO SEVENTH OCTET
            Header.getValue()[7] = (byte) (Header.getValue()[7] | VariablePayloadLength.getValue()[1]);
        } catch (Exception e) {
            System.out.println(e);
        }
        return Header;
    }

    /**
     *
     * Setter - Constructs the MIH Protocol Header
     *
     *
     * @param version
     * @param ackreq
     * @param ackrsp
     * @param uir
     * @param m
     * @param fn
     * @param rsvd1
     * @param mid
     * @param rsvd2
     * @param tid
     * @param vpl
     * @return boolean - true if success
     */
    public boolean Set_MIH_Protocol_Header(int version, boolean ackreq, boolean ackrsp, boolean uir, boolean m, int fn,
            boolean rsvd1, UInt16 mid, int rsvd2, int tid, int vpl) {
        try {
            this.Version(new UInt8(version));
            ACKREQ = ackreq;
            ACKRSP = ackrsp;
            UIR    = uir;
            M      = m;
            FN(new UInt8(fn));
            Rsvd1 = rsvd1;
            MID   = mid;
            Rsvd2(rsvd2);
            TransactionID(tid);
            VariablePayloadLength(vpl);

            return true;
        } catch (Exception e) {
            return false;
        }
    }

    /**
     *
     * Sets the Version
     *
     * @param UINT8
     */
    public void Version(UInt8 value) {
        byte[] b;
        byte   rb,
               mask = 0x0F;

        b  = value.getValue();
        rb = (byte) (b[0] & mask);

        UInt8 r = new UInt8(rb);

        Version = new UInt8();
        Version.setValue(r.getValue());
    }

    /**
     *
     * Sets the FN value
     * @param UINT8
     */
    public void FN(UInt8 value) {
        FN = new UInt8();

        byte[] b;
        byte   rb,
               mask = 0x03;

        b  = value.getValue();
        rb = (byte) (b[0] & mask);

        UInt8 r = new UInt8(rb);

        FN.setValue(r.getValue());
    }

    /**
     *
     * Constructs the MID
     *
     * @param SID_VAL
     * @param OPCODE_VAL
     * @param AID_VAL
     */
    public void MID(int SID_VAL, int OPCODE_VAL, int AID_VAL) {
        byte   bSID, bOPCODE, bAID1, bAID2;
        byte[] _MID    = new byte[2];
        UInt8  _SID    = new UInt8(SID_VAL);
        UInt8  _OPCODE = new UInt8(OPCODE_VAL);
        UInt16 _AID    = new UInt16(AID_VAL);

        bSID    = _SID.getValue()[0];
        bOPCODE = _OPCODE.getValue()[0];
        bAID1   = _AID.getValue()[0];
        bAID2   = _AID.getValue()[1];
        _MID[0] = 0x00;
        _MID[0] = (byte) (_MID[0] | ((((byte) SID_VAL) & 0x0F) << 4));
        _MID[0] = (byte) (_MID[0] | ((((byte) OPCODE_VAL) & 0x03) << 2));
        _MID[1] = (byte) (_MID[1] | (byte) AID_VAL);
        MID     = new UInt16();
        MID.setValue(_MID);
    }

    /**
     *
     * Constructs the RSV2
     *
     * @param value
     */
    public void Rsvd2(int value) {
        Rsvd2 = new UInt8();

        byte[] bs  = Rsvd2.getValue();
        UInt8  rsv = new UInt8(value);
        byte[] ba  = rsv.getValue();

        bs[0] = (byte) (bs[0] | (ba[0] & 0x0F));
        Rsvd2.setValue(bs);
    }

    /**
     *Consctructs the TRANSACTTION ID
     * @param value
     */
    public void TransactionID(int value) {
        TransactionID = new UInt16();

        TransactionID.setValue(new UInt16(value).getValue());
    }

    /**
     *
     * Constructs the variable payload length
     *
     * @param value
     */
    public void VariablePayloadLength(int value) {
        VariablePayloadLength.setValue((new UInt16(value).getValue()));
    }

    /**
     *
     * List of available AIDs
     *
     */
    public class AID {

        // /////////// SERVICE MANAGEMENT //////////////
        /**
         *
         */
        public static final int MIH_Capability_Discover = 1;
        /**
         *
         */
        public static final int MIH_DeRegister          = 3;
        /**
         *
         */
        public static final int MIH_Event_Subscribe     = 4;
        /**
         *
         */
        public static final int MIH_Event_UnSubscribe   = 5;

        // /////////// INFORMATION SERVICE //////////////
        /**
         *
         */
        public static final int MIH_Get_Information           = 1;
        /**
         *
         */
        public static final int MIH_Link_Actions              = 3;
        /**
         *
         */
        public static final int MIH_Link_Configure_Thresholds = 2;

        // /////////// EVENT SERVICE //////////////
        /**
         *
         */
        public static final int MIH_Link_Detected = 1;
        /**
         *
         */
        public static final int MIH_Link_Down     = 3;

        // /////////// COMMAND SERVICE //////////////
        /**
         *
         */
        public static final int MIH_Link_Get_Parameters         = 1;
        /**
         *
         */
        public static final int MIH_Link_Going_Down             = 6;
        /**
         *
         */
        public static final int MIH_Link_Handover_Complete      = 8;
        /**
         *
         */
        public static final int MIH_Link_Handover_Imminent      = 7;
        /**
         *
         */
        public static final int MIH_Link_Parameters_Report      = 5;
        /**
         *
         */
        public static final int MIH_Link_Up                     = 2;
        /**
         *
         */
        public static final int MIH_MN_HO_Candidate_Query       = 5;
        /**
         *
         */
        public static final int MIH_MN_HO_Commit                = 7;
        /**
         *
         */
        public static final int MIH_MN_HO_Complete              = 10;
        /**
         *
         */
        public static final int MIH_N2N_HO_Commit               = 9;
        /**
         *
         */
        public static final int MIH_N2N_HO_Complete             = 11;
        /**
         *
         */
        public static final int MIH_N2N_HO_Query_Resources      = 6;
        /**
         *
         */
        public static final int MIH_Net_HO_Candidate_Query      = 4;
        /**
         *
         */
        public static final int MIH_Net_HO_Commit               = 8;
        /**
         *
         */
        public static final int MIH_Push_Information            = 2;
        /**
         *
         */
        public static final int MIH_Register                    = 2;
        /**
         *
         */
          public static final int MIH_Sensor_UP                    = 9;
        /**
         *
         */
    }


    /**
     *
     * List of available OPCODEs
     *
     */
    public class Opcode {
        /**
         *
         */
        public static final int Confirm    = 0;
        /**
         *
         */
        public static final int Indication = 3;
        /**
         *
         */
        public static final int Request    = 1;
        /**
         *
         */
        public static final int Response   = 2;
    }


    /**
     *
     * List of available SIDs
     *
     */
    public class SID {
        /**
         *
         */
        public static final int CommandService     = 3;
        /**
         *
         */
        public static final int EventService       = 2;
        /**
         *
         */
        public static final int InformationService = 4;
        /**
         *
         */
        public static final int ServiceManagement  = 1;
    }
}
