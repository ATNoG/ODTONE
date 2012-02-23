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
package odtone_java.inc.Common;

import java.util.Vector;
import odtone_java.inc.Common.Datatypes.UInt32;
import odtone_java.inc.Common.Datatypes.UInt8;

/**
 *
 * @author marcelo lebre <marcelolebre@av.it.pt>
 *
 */
/**
 *
 * Class designed to handle serialization for message construction
 * Transforms MIH datatypes into byte []s
 */
public class Serialization {

    byte[] out;

    /**
     * Function with 8 parameters to sequence them in MIH protocol order
     *
     * @param first
     * @param second
     * @param third
     * @param fourth
     * @param fifth
     * @param sixth
     * @param seventh
     * @param eigth
     * @return byte[] - returns a sequenced byte array
     */
    public byte[] sequence(byte[] first, byte[] second, byte[] third, byte[] fourth, byte[] fifth, byte[] sixth, byte[] seventh, byte[] eigth) {


        int size = first.length + second.length + third.length + fourth.length + fifth.length + sixth.length + seventh.length + eigth.length;
        out = new byte[size];

        int i, pos;
        for (i = 0, pos = 0; i < first.length; i++, pos++) {

            out[i] = first[i];
        }
        for (i = 0; i < second.length; i++, pos++) {

            out[pos] = second[i];
        }
        for (i = 0; i < third.length; i++, pos++) {

            out[pos] = third[i];
        }
        for (i = 0; i < fourth.length; i++, pos++) {

            out[pos] = fourth[i];
        }
        for (i = 0; i < fifth.length; i++, pos++) {

            out[pos] = fifth[i];
        }
        for (i = 0; i < sixth.length; i++, pos++) {

            out[pos] = sixth[i];
        }
        for (i = 0; i < seventh.length; i++, pos++) {

            out[pos] = seventh[i];
        }
        for (i = 0; i < eigth.length; i++, pos++) {

            out[pos] = eigth[i];
        }

        return out;

    }

    /**
     * Function with 9 parameters to sequence them in MIH protocol order
     *
     * @param first
     * @param second
     * @param third
     * @param fourth
     * @param fifth
     * @param sixth
     * @param seventh
     * @param eigth
     * @param nineth
     * @return byte[] - returns a sequenced byte array
     */
    public byte[] sequence(byte[] first, byte[] second, byte[] third, byte[] fourth, byte[] fifth, byte[] sixth, byte[] seventh, byte[] eigth, byte[] nineth) {

        //Sequencing
        int size = first.length + second.length + third.length + fourth.length + fifth.length + sixth.length + seventh.length + eigth.length + nineth.length;
        out = new byte[size];
        //Sequencing first object
        int i, pos;
        for (i = 0, pos = 0; i < first.length; i++, pos++) {

            out[i] = first[i];
        }
        for (i = 0; i < second.length; i++, pos++) {

            out[pos] = second[i];
        }
        for (i = 0; i < third.length; i++, pos++) {

            out[pos] = third[i];
        }
        for (i = 0; i < fourth.length; i++, pos++) {

            out[pos] = fourth[i];
        }
        for (i = 0; i < fifth.length; i++, pos++) {

            out[pos] = fifth[i];
        }
        for (i = 0; i < sixth.length; i++, pos++) {

            out[pos] = sixth[i];
        }
        for (i = 0; i < seventh.length; i++, pos++) {

            out[pos] = seventh[i];
        }
        for (i = 0; i < eigth.length; i++, pos++) {

            out[pos] = eigth[i];
        }
        for (i = 0; i < nineth.length; i++, pos++) {

            out[pos] = nineth[i];
        }


        return out;

    }

    /**
     * Function with 7 parameters to sequence them in MIH protocol order
     *
     * @param first
     * @param second
     * @param third
     * @param fourthIP4_ADD
     * @param fifth
     * @param sixth
     * @param seventh
     * @return byte[] - returns a sequenced byte array
     */
    public byte[] sequence(byte[] first, byte[] second, byte[] third, byte[] fourth, byte[] fifth, byte[] sixth, byte[] seventh) {

        //Sequencing
        int size = first.length + second.length + third.length + fourth.length + fifth.length + sixth.length + seventh.length;
        out = new byte[size];
        //Sequencing first object
        int i, pos;
        for (i = 0, pos = 0; i < first.length; i++, pos++) {

            out[i] = first[i];
        }
        for (i = 0; i < second.length; i++, pos++) {

            out[pos] = second[i];
        }
        for (i = 0; i < third.length; i++, pos++) {

            out[pos] = third[i];
        }
        for (i = 0; i < fourth.length; i++, pos++) {

            out[pos] = fourth[i];
        }
        for (i = 0; i < fifth.length; i++, pos++) {

            out[pos] = fifth[i];
        }
        for (i = 0; i < sixth.length; i++, pos++) {

            out[pos] = sixth[i];
        }
        for (i = 0; i < seventh.length; i++, pos++) {

            out[pos] = seventh[i];
        }


        return out;

    }

    /**
     * Function with 6 parameters to sequence them in MIH protocol order
     *
     * @param first
     * @param second
     * @param third
     * @param fourth
     * @param fifth
     * @param sixth
     * @return byte[] - returns a sequenced byte array
     */
    public byte[] sequence(byte[] first, byte[] second, byte[] third, byte[] fourth, byte[] fifth, byte[] sixth) {

        //Sequencing
        int size = first.length + second.length + third.length + fourth.length + fifth.length + sixth.length;
        out = new byte[size];
        //Sequencing first object
        int i, pos;
        for (i = 0, pos = 0; i < first.length; i++, pos++) {

            out[i] = first[i];
        }
        for (i = 0; i < second.length; i++, pos++) {

            out[pos] = second[i];
        }
        for (i = 0; i < third.length; i++, pos++) {

            out[pos] = third[i];
        }
        for (i = 0; i < fourth.length; i++, pos++) {

            out[pos] = fourth[i];
        }
        for (i = 0; i < fifth.length; i++, pos++) {

            out[pos] = fifth[i];
        }
        for (i = 0; i < sixth.length; i++, pos++) {

            out[pos] = sixth[i];
        }


        return out;

    }

    /**
     * Function with 5 parameters to sequence them in MIH protocol order
     *
     * @param first
     * @param second
     * @param third
     * @param fourth
     * @param fifth
     * @return byte[] - returns a sequenced byte array
     */
    public byte[] sequence(byte[] first, byte[] second, byte[] third, byte[] fourth, byte[] fifth) {

        //Sequencing
        int size = first.length + second.length + third.length + fourth.length + fifth.length;
        out = new byte[size];
        //Sequencing first object
        int i, pos;
        for (i = 0, pos = 0; i < first.length; i++, pos++) {

            out[i] = first[i];
        }
        for (i = 0; i < second.length; i++, pos++) {

            out[pos] = second[i];
        }
        for (i = 0; i < third.length; i++, pos++) {

            out[pos] = third[i];
        }
        for (i = 0; i < fourth.length; i++, pos++) {

            out[pos] = fourth[i];
        }
        for (i = 0; i < fifth.length; i++, pos++) {

            out[pos] = fifth[i];
        }

        return out;

    }

    /**
     * Function with 4 parameters to sequence them in MIH protocol order
     *
     * @param first
     * @param second
     * @param third
     * @param fourth
     * @return byte[] - returns a sequenced byte array
     */
    public byte[] sequence(byte[] first, byte[] second, byte[] third, byte[] fourth) {

        //Sequencing
        int size = first.length + second.length + third.length + fourth.length;
        out = new byte[size];
        //Sequencing first object
        int i, pos;
        for (i = 0, pos = 0; i < first.length; i++, pos++) {

            out[i] = first[i];
        }
        for (i = 0; i < second.length; i++, pos++) {

            out[pos] = second[i];
        }
        for (i = 0; i < third.length; i++, pos++) {

            out[pos] = third[i];
        }
        for (i = 0; i < fourth.length; i++, pos++) {

            out[pos] = fourth[i];
        }

        return out;

    }

    /**
     * Function with 3 parameters to sequence them in MIH protocol order
     *
     * @param first
     * @param second
     * @param third
     * @return byte[] - returns a sequenced byte array
     */
    public byte[] sequence(byte[] first, byte[] second, byte[] third) {

        //Sequencing
        int size = first.length + second.length + third.length;
        out = new byte[size];
        //Sequencing first object
        int i, pos;
        for (i = 0, pos = 0; i < first.length; i++, pos++) {

            out[i] = first[i];
        }
        for (i = 0; i < second.length; i++, pos++) {

            out[pos] = second[i];
        }
        for (i = 0; i < third.length; i++, pos++) {

            out[pos] = third[i];
        }

        return out;

    }

    /**
     * Function with 2 parameters to sequence them in MIH protocol order
     * @param first
     * @param second
     * @return
     */
    public byte[] sequence(byte[] first, byte[] second) {

        //Sequencing
        int size = first.length + second.length;
        out = new byte[size];
        //Sequencing first object
        int i, pos;

        for (i = 0, pos = 0; i < first.length; i++, pos++) {

            out[i] = first[i];
        }
        for (i = 0; i < second.length; i++, pos++) {

            out[pos] = second[i];
        }

        return out;

    }

    /**
     * Encodes a 1 parameter Choice MIH object
     *
     * @param data
     * @param choice
     * @return byte[] - returns a choice MIH object in byte array
     */
    public byte[] choice(byte[] data, int choice) {
        byte selector;
        byte[] value;
        byte[] out_choice = new byte[0];
        int tmp, i;
        choice = choice + 1;

        if (data != null) {
            Serialization srlz = new Serialization();
            byte[] selectorX = new byte[1];

            out_choice = new byte[1 + data.length];

            selectorX = new byte[1];
            selectorX[0] = (byte) choice;


            out_choice = srlz.sequence(selectorX, data);

        } else {
            //Encoding Null chooice
            selector = 0;

            out_choice = new byte[1];
            //Encoding Choice

            out_choice[0] = selector;
            // | 0 | 0 | 0 |
        }

        return out_choice;

    }

    /**
     * Encodes a List<Byte[]> into a MIH List object
     *
     * @param List<byte[]>
     * @return byte[] - MIH List object
     * 
     */
    public byte[] encoding_List(Vector lst) {
        int size = 0;
        int valueSize = 0;


        byte[] out_list = new byte[0];
        for (int i = 0; i < lst.size(); i++) {
            valueSize = valueSize + ((byte[])lst.elementAt(i)).length;
        }
        size = lst.size();
        if (size < 128) {
            //Instantiates the out_list array
            out_list = new byte[1 + valueSize];
            //Sets the list size
            out_list[0] = (byte) lst.size();
            int pos = 1;
            for (int i = 1; i <= lst.size(); i++) {
                for (int j = 0; j < ((byte[])lst.elementAt(i-1)).length; j++) {
                    out_list[pos] = ((byte[])lst.elementAt(i-1))[j];
                    pos++;
                }
            }
        } else {
            try {
                int appendedSize = size - 128;

                //Calculates the number of octets to be appended to the length field

                int nOctetsLength = (int) Math.ceil(((double) appendedSize / 255));
                if (nOctetsLength > 0xFF) {
                    throw new Exception("Error: message size not supported");
                }
                //Instantiates the out_list array
                out_list = new byte[1 + nOctetsLength + valueSize];
                out_list[0] = (byte) 0x80;
                out_list[0] = (byte) (out_list[0] | nOctetsLength);
                //Append the number of octets of the length field
                for (int i = 1; i < nOctetsLength - 1; i++) {
                    out_list[i] = (byte) 0xFF;
                }

                if (nOctetsLength > 1) {
                    out_list[nOctetsLength] = (byte) ((new UInt8(nOctetsLength * 255 - appendedSize)).getValue()[0]);
                } else {
                    out_list[nOctetsLength] = (byte) appendedSize;
                }

                //
                int pos = nOctetsLength + 1;
                for (int i = 1; i <= lst.size(); i++) {
                    for (int j = 0; j < ((byte[])lst.elementAt(i-1)).length; j++) {
                        out_list[pos] = ((byte[])lst.elementAt(i-1))[j];
                        pos++;
                    }
                }
            } catch (Exception e) {
                System.out.println(e.getMessage());
                return new byte[0];
            }
        }
        return out_list;
    }
    //this function takes as parameters the tlv value and the data to be inserted
    //in the value field, take notice that this parameter is already in the proper
    //format to be inserted ( encoded byte array)

    /**
     *
     * Encodes a MIH object in byte[] form into a TLV object
     *
     * @param int (TLV)
     * @param byte [] (ValueField)
     * @return
     */
    public byte[] serialize_to_tlv(int TLV, byte[] ValueField) {

        int i, j;

        if (ValueField.length <= 128) {

            out = new byte[ValueField.length + 2];
            //Inserting Type field
            out[0] = (new UInt8(TLV)).getValue()[0];
            //Inserting Length Field
            out[1] = (new UInt8(ValueField.length)).getValue()[0];
            //Inserting Value Field
            for (i = 2, j = 0; j < ValueField.length; i++, j++) {
                out[i] = ValueField[j];
            }
        } else {
            double nOctets=0;
            //Calculate the amount of octets needed to represent the value size

                nOctets = Math.ceil((double) (ValueField.length-128) / 255);


            
            try {
                if (nOctets > 0x7F) {
                    throw new Exception("Error: Message size not supported");
                }
            } catch (Exception e) {
                System.out.println(e.getMessage());
                return new byte[0];
            }
            //Instantiating the out array
            System.out.println("Valuefield Size: " + ValueField.length);

            System.out.println("Total size of frame: " + (ValueField.length + 1 + (int) nOctets));

            out = new byte[ValueField.length + 1 + (int) nOctets+1];

            //Inserting Type field
            out[0] = (new UInt8(TLV)).getValue()[0];

            //Insert the Length Field
            //First octet, when >128:
            out[1] = (byte) 0x80;
            out[1] = (byte) (out[1] | (byte) (nOctets));

            //The rest of the Length field octets
            for (i = 0, j = 2; i < nOctets - 1; j++, i++) {
                //Fill with 0xFF
                out[j] = (byte) 0xFF;

            }


            out[j] = (byte) (ValueField.length - (255 * (nOctets - 2) + 128));

            j++;
            int offset = j;
            //Insert the Value Field
            for (i = 0; i < ValueField.length; j++, i++) {
                out[j] = ValueField[i];
            }
        }
        return out;
    }

    public byte[] serializeInfoElements(int type, byte[] ValueField) {
        int i, j;
        byte[] tp;
        if (ValueField.length <= 128) {

            out = new byte[ValueField.length + 1 + 4];
            tp = new UInt32(type).getValue();
            //Inserting Type field
            for (i = 0; i < 4; i++) {
                out[i] = tp[i];
            }
            //Inserting Length Field
            out[4] = (byte) ValueField.length;

            //Inserting Value Field
            for (i = 5, j = 0; j < ValueField.length; i++, j++) {
                out[i] = ValueField[j];
            }
        } else {
            //Calculate the amount of octets needed to represent the value size
            double nOctets = Math.ceil((double) (ValueField.length-128) / 255);
            //Instantiating the out array

            out = new byte[ValueField.length + 4 + ((int) nOctets)+1];
            //Inserting Type field
            tp = new UInt32(type).getValue();
            //Inserting Type field
            for (i = 0; i < 4; i++) {
                out[i] = tp[i];
            }

            //Insert the Length Field
            //First octet, when >128:
            out[4] = (byte) 0x80;
            out[4] = (byte) (out[4] | (byte) (nOctets));
            //The rest of the Length field octets
            for (i = 5, j = 0; j < nOctets - 1; i++, j++) {
                //Fill with 0xFF
                out[i] = (byte) 0xFF;

            }

            out[i] = (byte) (ValueField.length - (255 * (nOctets - 1) + 128));
            i++;
            //Insert the Value Field
            int offset = i;
            //Insert the Value Field

            for (j = 0; j < ValueField.length; j++, i++) {
                out[i] = ValueField[j];
            }
        }
        return out;
    }
}
