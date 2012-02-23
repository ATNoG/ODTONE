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
package odtone_java.inc.Common.Datatypes;

/**
 *
 * @author marcelo lebre <marcelolebre@av.it.pt>
 *
 */
/**
 *
 * Class designed to construct a octet object
 *
 */
public class Octet {

    byte bs[];

    /**
     *
     * Empty Constructor
     *
     */
    public Octet() {
    }

    public Octet(Octet os) {
        this.value = os.get_Octet_Value();
        bs = new byte[os.getValue().length];
        bs = os.getValue();
    }
    int value;

    /**
     * Creates a Octet datatype from an integer
     *
     * @param int
     */
    public int get_Octet_Value(){
    return value;
    }
    public Octet(int value, int size) {
        this.value = value;
        bs = new byte[size];
        switch (size) {
            case 1:
                bs[0] = (byte) (0x000000FF & value);
            case 2:
                bs[1] = (byte) (0x000000FF & value);
                bs[0] = (byte) ((0x0000FF00 & value) >> 8);
            case 3:
                bs[2] = (byte) (0x000000FF & value);
                bs[1] = (byte) ((0x0000FF00 & value) >> 8);
                bs[0] = (byte) ((0x00FF0000 & value) >> 16);
            case 4:
                bs[3] = (byte) (0x000000FF & value);
                bs[2] = (byte) ((0x0000FF00 & value) >> 8);
                bs[1] = (byte) ((0x00FF0000 & value) >> 16);
                bs[0] = (byte) ((0xFF000000 & value) >> 24);
            default:
        }
    }

    /**
     *
     * Gets the byte[] value of the Octet datatype
     *
     * @return byte []
     */
    public byte[] getValue() {
        return bs;
    }

    public void setValue(byte[] in) {
        bs = in;
    }

    public Octet(byte[] in) {
        bs = new byte[in.length];
        bs = in;
    }

    /**
     *
     * Transforms an Octet into an Integer
     * @param byte
     * @return int
     */
    public int OctetToInt(byte value) {
        int out;

        if ((int) value < 0) {
            out = value + 256;
        } else {
            return value;
        }

        return out;
    }
}
