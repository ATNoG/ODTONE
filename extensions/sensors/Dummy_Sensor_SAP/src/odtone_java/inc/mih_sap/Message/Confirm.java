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
 * Class designed to construct confirm messages
 *
 */
public class Confirm {
    Serialization srlz = new Serialization();
    /**
     *
     */
    public byte[] Message_out;



    /**
     *
     * Construct a MIH Capability Discover confirm Message
     *
     * @param MIH_Protocol_Header
     * @param Payload
     * @return byte [] - representation of the confirm message in byte form
     */
    public byte[] MIH_Capability_Discover(MIH_Protocol_Header _msgheader, Payload payload) {
        Message_out =
                new byte[srlz.sequence(_msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload()).length];
        Message_out = srlz.sequence(_msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload());

        return Message_out;
    }
    /**
     *
     * Construct a MIH_Register confirm message
     *
     * @param MIH_Protocol_Header
     * @param Payload
     * @return byte [] - representation of the confirm message in byte form
     */
    public byte[] MIH_Register(MIH_Protocol_Header msgheader, Payload payload) {
        Message_out =
                new byte[srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload()).length];
        Message_out = srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload());

        return Message_out;
    }
    /**
     *
     * Construct a MIH_DeRegister confirm message
     *
     * @param MIH_Protocol_Header
     * @param Payload
     * @return byte [] - representation of the confirm message in byte form
     */
    public byte[] MIH_DeRegister(MIH_Protocol_Header msgheader, Payload payload) {
        Message_out =
                new byte[srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload()).length];
        Message_out = srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload());

        return Message_out;
    }

    /**
     *
     * Construct a MIH Event Subscribe confirm message
     *
     * @param MIH_Protocol_Header
     * @param Payload
     * @return byte [] - representation of the confirm message in byte form
     */
    public byte[] MIH_Event_Subscribe(MIH_Protocol_Header msgheader, Payload payload) {
        Message_out =
                new byte[srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload()).length];
        Message_out = srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload());

        return Message_out;
    }

public byte[] Event_Subscribe(MIH_Protocol_Header msgheader, Payload payload) {
        Message_out =
                new byte[srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload()).length];
        Message_out = srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload());

        return Message_out;
    }
    /**
     *
     * Construct a MIH Event Unsubscribe confirm message
     *
     * @param MIH_Protocol_Header
     * @param Payload
     * @return byte [] - representation of the confirm message in byte form
     */
    public byte[] MIH_Event_Unsubscribe(MIH_Protocol_Header msgheader, Payload payload) {
        Message_out =
                new byte[srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload()).length];
        Message_out = srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload());

        return Message_out;
    }

    /**
     *
     * Construct a MIH_Link_Get_Parameters confirm message
     *
     * @param MIH_Protocol_Header
     * @param Payload
     * @return byte [] - representation of the confirm message in byte form
     */
    public byte[] MIH_Link_Get_Parameters(MIH_Protocol_Header msgheader, Payload payload) {
        Message_out =
                new byte[srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload()).length];
        Message_out = srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload());

        return Message_out;
    }

    /**
     *
     * Construct a MIH_Link_Configure_Thresholds confirm message
     *
     * @param MIH_Protocol_Header
     * @param Payload
     * @return byte [] - representation of the confirm message in byte form
     */
    public byte[] MIH_Link_Configure_Thresholds(MIH_Protocol_Header msgheader, Payload payload) {
        Message_out =
                new byte[srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload()).length];
        Message_out = srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload());

        return Message_out;
    }

    public byte[] Link_Configure_Thresholds(MIH_Protocol_Header msgheader, Payload payload) {
        Message_out =
                new byte[srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload()).length];
        Message_out = srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload());

        return Message_out;
    }
    /**
     *
     * Construct a MIH_Link_Actions confirm message
     *
     * @param MIH_Protocol_Header
     * @param Payload
     * @return byte [] - representation of the confirm message in byte form
     */
    public byte[] MIH_Link_Actions(MIH_Protocol_Header msgheader, Payload payload) {
        Message_out =
                new byte[srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload()).length];
        Message_out = srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload());

        return Message_out;
    }
public byte[] Link_Actions(MIH_Protocol_Header msgheader, Payload payload) {
        Message_out =
                new byte[srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload()).length];
        Message_out = srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload());

        return Message_out;
    }
    /**
     *
     * Construct a MIH_Net_HO_Candidate_Query confirm message
     *
     * @param MIH_Protocol_Header
     * @param Payload
     * @return byte [] - representation of the confirm message in byte form
     */
    public byte[] MIH_Net_HO_Candidate_Query(MIH_Protocol_Header msgheader, Payload payload) {
        Message_out =
                new byte[srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload()).length];
        Message_out = srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload());

        return Message_out;
    }

    /**
     *
     * Construct a MIH_MN_HO_Candidate_Query confirm message
     *
     * @param MIH_Protocol_Header
     * @param Payload
     * @return byte [] - representation of the confirm message in byte form
     */
    public byte[] MIH_MN_HO_Candidate_Query(MIH_Protocol_Header msgheader, Payload payload) {
        Message_out =
                new byte[srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload()).length];
        Message_out = srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload());

        return Message_out;
    }

    /**
     *
     * Construct a MIH_N2N_HO_Query_Resources confirm message
     *
     * @param MIH_Protocol_Header
     * @param Payload
     * @return byte [] - representation of the confirm message in byte form
     */
    public byte[] MIH_N2N_HO_Query_Resources(MIH_Protocol_Header msgheader, Payload payload) {
        Message_out =
                new byte[srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload()).length];
        Message_out = srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload());

        return Message_out;
    }

    /**
     *
     * Construct a MIH_MN_HO_Commit confirm message
     *
     * @param MIH_Protocol_Header
     * @param Payload
     * @return byte [] - representation of the confirm message in byte form
     */
    public byte[] MIH_MN_HO_Commit(MIH_Protocol_Header msgheader, Payload payload) {
        Message_out =
                new byte[srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload()).length];
        Message_out = srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload());

        return Message_out;
    }

    /**
     *
     * Construct a MIH_Net_HO_Commit confirm message
     *
     * @param MIH_Protocol_Header
     * @param Payload
     * @return byte [] - representation of the confirm message in byte form
     */
    public byte[] MIH_Net_HO_Commit(MIH_Protocol_Header msgheader, Payload payload) {
        Message_out =
                new byte[srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload()).length];
        Message_out = srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload());

        return Message_out;
    }

    /**
     *
     * Construct a MIH_N2N_HO_Commit confirm message
     *
     * @param MIH_Protocol_Header
     * @param Payload
     * @return byte [] - representation of the confirm message in byte form
     */
    public byte[] MIH_N2N_HO_Commit(MIH_Protocol_Header msgheader, Payload payload) {
        Message_out =
                new byte[srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload()).length];
        Message_out = srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload());

        return Message_out;
    }

    /**
     *
     * Construct a MIH_MN_HO_Complete confirm message
     *
     * @param MIH_Protocol_Header
     * @param Payload
     * @return byte [] - representation of the confirm message in byte form
     */
    public byte[] MIH_MN_HO_Complete(MIH_Protocol_Header msgheader, Payload payload) {
        Message_out =
                new byte[srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload()).length];
        Message_out = srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload());

        return Message_out;
    }

    /**
     *
     * Construct a MIH_N2N_HO_Complete confirm message
     *
     * @param MIH_Protocol_Header
     * @param Payload
     * @return byte [] - representation of the confirm message in byte form
     */
    public byte[] MIH_N2N_HO_Complete(MIH_Protocol_Header msgheader, Payload payload) {
        Message_out =
                new byte[srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload()).length];
        Message_out = srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload());

        return Message_out;
    }

    /**
     *
     * Construct a MIH_Get_Information confirm message
     *
     * @param MIH_Protocol_Header
     * @param Payload
     * @return byte [] - representation of the confirm message in byte form
     */
    public byte[] MIH_Get_Information(MIH_Protocol_Header msgheader, Payload payload) {
        Message_out =
                new byte[srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload()).length];
        Message_out = srlz.sequence(msgheader.get_MIH_Protocol_Header().getValue(), payload.Get_Payload());

        return Message_out;
    }
}

