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


package odtone_java.inc.mih_sap.Message;

//~--- non-JDK imports --------------------------------------------------------

import odtone_java.inc.Common.MessageHandler.Payload;
import odtone_java.inc.Common.MessageHandler.MIH_Protocol_Header;
import odtone_java.inc.Common.Serialization;

/**
 *
 * @author marcelo lebre <marcelolebre@av.it.pt>
 *
 */
/**
 *
 * Class designed to implement a Indication message
 *
 */
public class Indication {
    Serialization srlz = new Serialization();
    /**
     *
     */
    public byte[] Message_out;

    /**
     *
     * Constructs a message indication for the MIH_Link_Detected
     *
     * @param MIH_Protocol_Header
     * @param Payload
     * @return byte[] - Indication message in the form of a byte[]
     *
     */
    public byte[] MIH_Link_Detected(MIH_Protocol_Header msgheader, Payload payload) {
        Message_out =
            new byte[srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload()).length];
        Message_out = srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload());

        return Message_out;
    }

    /**
     * 
     * Constructs a message indication for the MIH_Link_Up
     *
     * @param MIH_Protocol_Header
     * @param Payload
     * @return byte[] - Indication message in the form of a byte[]
     *
     */
    public byte[] MIH_Link_Up(MIH_Protocol_Header msgheader, Payload payload) {
        Message_out =
            new byte[srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload()).length];
        Message_out = srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload());

        return Message_out;
    }

     public byte[] Sensor_Up(MIH_Protocol_Header msgheader, Payload payload) {
        Message_out =
            new byte[srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload()).length];
        Message_out = srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload());

        return Message_out;
    }
     public byte[] Link_Parameters_Report(MIH_Protocol_Header msgheader, Payload payload) {
        Message_out =
            new byte[srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload()).length];
        Message_out = srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload());

        return Message_out;
    }
    /**
     *
     * Constructs a message indication for the MIH_Link_Down
     *
     * @param MIH_Protocol_Header
     * @param Payload
     * @return byte[] - Indication message in the form of a byte[]
     *
     */
    public byte[] MIH_Link_Down(MIH_Protocol_Header msgheader, Payload payload) {
        Message_out =
            new byte[srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload()).length];
        Message_out = srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload());

        return Message_out;
    }

    /**
     *
     * Constructs a message indication for the MIH_Link_Parameters_Report
     *
     * @param MIH_Protocol_Header
     * @param Payload
     * @return byte[] - Indication message in the form of a byte[]
     *
     */
    public byte[] MIH_Link_Parameters_Report(MIH_Protocol_Header msgheader, Payload payload) {
        Message_out =
            new byte[srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload()).length];
        Message_out = srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload());

        return Message_out;
    }

    /**
     *
     * Constructs a message indication for the MIH_Link_Going_Down
     *
     * @param MIH_Protocol_Header
     * @param Payload
     * @return byte[] - Indication message in the form of a byte[]
     *
     */
    public byte[] MIH_Link_Going_Down(MIH_Protocol_Header msgheader, Payload payload) {
        Message_out =
            new byte[srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload()).length];
        Message_out = srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload());

        return Message_out;
    }

    /**
     *
     * Constructs a message indication for the MIH_Link_Handover_Imminent
     *
     * @param MIH_Protocol_Header
     * @param Payload
     * @return byte[] - Indication message in the form of a byte[]
     *
     */
    public byte[] MIH_Link_Handover_Imminent(MIH_Protocol_Header msgheader, Payload payload) {
        Message_out =
            new byte[srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload()).length];
        Message_out = srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload());

        return Message_out;
    }

    /**
     *
     * Constructs a message indication for the MIH_Link_Handover_Complete
     *
     * @param MIH_Protocol_Header
     * @param Payload
     * @return byte[] - Indication message in the form of a byte[]
     *
     */
    public byte[] MIH_Link_Handover_Complete(MIH_Protocol_Header msgheader, Payload payload) {
        Message_out =
            new byte[srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload()).length];
        Message_out = srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload());

        return Message_out;
    }

    /**
     *
     * Constructs a message indication for the MIH_Push_Information
     *
     * @param MIH_Protocol_Header
     * @param Payload
     * @return byte[] - Indication message in the form of a byte[]
     *
     */
    public byte[] MIH_Push_Information(MIH_Protocol_Header msgheader, Payload payload) {
        Message_out =
            new byte[srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload()).length];
        Message_out = srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload());

        return Message_out;
    }
}