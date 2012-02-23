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
 * Class designed to implement an unsigned integer with 16 bits
 *
 *
 */
public class UInt16 {
    byte bs[] = new byte[2];

    /**
     * Empty Constructor
     */
    public UInt16() {}

    /**
     * Transforms a integer into a unsigned integer 16 datatype
     * @param integer
     */
    public UInt16(int value) {
        bs[1] = (byte) (0x000000FF & value);
        bs[0] = (byte) ((0x0000FF00 & value) >> 8);
    }

    /**
     *
     * Creates another instance of a UINT16
     *
     * @param UINT16
     */
    public UInt16(UInt16 value) {
        bs = value.getValue();
    }

    /**
     *  Sets a UINT16 value from a byte array with 2 positions
     *
     * @param s
     */
    public void setValue(byte[] s) {
        bs[0] = s[0];
        bs[1] = s[1];
    }

    /**
     * Getter -  Returns a UINT16 datatype formed by a byte array with 2 pos.
     * @return byte []
     */
    public byte[] getValue() {
        return bs;
    }

    /**
     *  Transforms a UINT16 into an Integer
     * @param byte []
     * @return integer
     */
    public static final int UInt16ToInt(byte[] b) {
        int out = 0;

        if (b[0] == 0) {
            out = (new UInt8().UInt8ToInt(b[1]));
        }

        if (b[0] != 0) {
            out = (new UInt8().UInt8ToInt(b[0]) * 256) + (new UInt8().UInt8ToInt(b[1]));
        }

        return out;
    }
}
