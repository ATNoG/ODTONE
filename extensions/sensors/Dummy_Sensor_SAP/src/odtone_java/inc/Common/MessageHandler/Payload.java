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
import odtone_java.inc.Common.Types.ID;
import odtone_java.inc.Common.Serialization;
import odtone_java.inc.Common.TLVHandler.Tlv;

/**
 *
 * @author marcelo lebre <marcelolebre@av.it.pt>
 *
 */
/**
 *
 * Class designed to construct the message Payload
 *
 */
public class Payload {

    Serialization srlz = new Serialization();
    byte[] payload;

    /**
     *
     * Constructs a message with only the source and destination's ID
     *
     * @param ID - source ID
     * @param ID - destination ID
     */
    public Payload(ID source, ID destination) {
        payload =
                new byte[srlz.sequence(srlz.serialize_to_tlv(Tlv.tlv_source_id, source.get_ID()), srlz.serialize_to_tlv(Tlv.tlv_destination_id, destination.get_ID())).length];
        payload = srlz.sequence(srlz.serialize_to_tlv(Tlv.tlv_source_id, source.get_ID()),
                srlz.serialize_to_tlv(Tlv.tlv_destination_id, destination.get_ID()));
    }

    /**
     *
     * Constructs a message with the source ID, destination ID and one parameter
     *
     * @param ID - source ID
     * @param ID - destination ID
     * @param byte [] - parameter
     */
    public Payload(ID source, ID destination, byte[] param1) {
        payload =
                new byte[srlz.sequence(srlz.serialize_to_tlv(Tlv.tlv_source_id, source.get_ID()), srlz.serialize_to_tlv(Tlv.tlv_destination_id, destination.get_ID()), param1).length];
        payload = srlz.sequence(srlz.serialize_to_tlv(Tlv.tlv_source_id, source.get_ID()),
                srlz.serialize_to_tlv(Tlv.tlv_destination_id, destination.get_ID()), param1);
    }

    /**
     *
     * Constructs a message with the source ID, destination ID and two paramters
     * 
     * @param ID - source ID
     * @param ID - destination ID
     * @param byte[] - parameter 1
     * @param byte[] - parameter 2
     */
    public Payload(ID source, ID destination, byte[] param1, byte[] param2) {
        payload =
                new byte[srlz.sequence(srlz.serialize_to_tlv(Tlv.tlv_source_id, source.get_ID()), srlz.serialize_to_tlv(Tlv.tlv_destination_id, destination.get_ID()), param1, param2).length];
        payload = srlz.sequence(srlz.serialize_to_tlv(Tlv.tlv_source_id, source.get_ID()),
                srlz.serialize_to_tlv(Tlv.tlv_destination_id, destination.get_ID()), param1, param2);
    }

    /**
     *
     * Constructs a message with the source ID, destination ID and three paramters
     *
     * @param ID - source ID
     * @param ID - destination ID
     * @param byte[] - parameter 1
     * @param byte[] - parameter 2
     * @param byte[] - parameter 3
     */
    public Payload(ID source, ID destination, byte[] param1, byte[] param2, byte[] param3) {
        payload =
                new byte[srlz.sequence(srlz.serialize_to_tlv(Tlv.tlv_source_id, source.get_ID()), srlz.serialize_to_tlv(Tlv.tlv_destination_id, destination.get_ID()), param1, param2, param3).length];
        payload = srlz.sequence(srlz.serialize_to_tlv(Tlv.tlv_source_id, source.get_ID()),
                srlz.serialize_to_tlv(Tlv.tlv_destination_id, destination.get_ID()), param1, param2,
                param3);
    }

    /**
     *
     * Constructs a message with the source ID, destination ID and four paramters
     *
     * @param ID - source ID
     * @param ID - destination ID
     * @param byte[] - parameter 1
     * @param byte[] - parameter 2
     * @param byte[] - parameter 3
     * @param byte[] - parameter 4
     */
    public Payload(ID source, ID destination, byte[] param1, byte[] param2, byte[] param3, byte[] param4) {
        payload =
                new byte[srlz.sequence(srlz.serialize_to_tlv(Tlv.tlv_source_id, source.get_ID()), srlz.serialize_to_tlv(Tlv.tlv_destination_id, destination.get_ID()), param1, param2, param3, param4).length];

        payload = srlz.sequence(srlz.serialize_to_tlv(Tlv.tlv_source_id, source.get_ID()),
                srlz.serialize_to_tlv(Tlv.tlv_destination_id, destination.get_ID()), param1, param2,
                param3, param4);
    }

    /**
     *
     * Constructs a message with the source ID, destination ID and five paramters
     *
     * @param ID - source ID
     * @param ID - destination ID
     * @param byte[] - parameter 1
     * @param byte[] - parameter 2
     * @param byte[] - parameter 3
     * @param byte[] - parameter 4
     * @param byte[] - parameter 5
     */
    public Payload(ID source, ID destination, byte[] param1, byte[] param2, byte[] param3, byte[] param4,
            byte[] param5) {
        payload =
                new byte[srlz.sequence(srlz.serialize_to_tlv(Tlv.tlv_source_id, source.get_ID()), srlz.serialize_to_tlv(Tlv.tlv_destination_id, destination.get_ID()), param1, param2, param3, param4, param5).length];
        payload = srlz.sequence(srlz.serialize_to_tlv(Tlv.tlv_source_id, source.get_ID()),
                srlz.serialize_to_tlv(Tlv.tlv_destination_id, destination.get_ID()), param1, param2,
                param3, param4, param5);
    }

    /**
     *
     * Constructs a message with the source ID, destination ID and six paramters
     * 
     * @param ID - source ID
     * @param ID - destination ID
     * @param byte[] - parameter 1
     * @param byte[] - parameter 2
     * @param byte[] - parameter 3
     * @param byte[] - parameter 4
     * @param byte[] - parameter 5
     * @param byte[] - parameter 6
     */
    public Payload(ID source, ID destination, byte[] param1, byte[] param2, byte[] param3, byte[] param4,
            byte[] param5, byte[] param6) {
        payload =
                new byte[srlz.sequence(srlz.serialize_to_tlv(Tlv.tlv_source_id, source.get_ID()), srlz.serialize_to_tlv(Tlv.tlv_destination_id, destination.get_ID()), param1, param2, param3, param4, param5, param6).length];
        payload = srlz.sequence(srlz.serialize_to_tlv(Tlv.tlv_source_id, source.get_ID()),
                srlz.serialize_to_tlv(Tlv.tlv_destination_id, destination.get_ID()), param1, param2,
                param3, param4, param5, param6);
    }

    /**
     *
     * Constructs a message with the source ID, destination ID and seven paramters
     *
     * @param ID - source ID
     * @param ID - destination ID
     * @param byte[] - parameter 1
     * @param byte[] - parameter 2
     * @param byte[] - parameter 3
     * @param byte[] - parameter 4
     * @param byte[] - parameter 5
     * @param byte[] - parameter 6
     * @param byte[] - parameter 7
     */
    public Payload(ID source, ID destination, byte[] param1, byte[] param2, byte[] param3, byte[] param4,
            byte[] param5, byte[] param6, byte[] param7) {
        payload =
                new byte[srlz.sequence(srlz.serialize_to_tlv(Tlv.tlv_source_id, source.get_ID()), srlz.serialize_to_tlv(Tlv.tlv_destination_id, destination.get_ID()), param1, param2, param3, param4, param5, param6, param7).length];
        payload = srlz.sequence(srlz.serialize_to_tlv(Tlv.tlv_source_id, source.get_ID()),
                srlz.serialize_to_tlv(Tlv.tlv_destination_id, destination.get_ID()), param1, param2,
                param3, param4, param5, param6, param7);
    }

    /**
     *  Getter - Returns the payload in byte [] form
     * @return byte[]
     */
    public byte[] Get_Payload() {
        return payload;
    }
}
