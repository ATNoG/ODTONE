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
 * Class designed to implement a Bitmap of 8 bits
 *
 */
public class UInt8 {
    byte bs[] = new byte[1];

    /**
     *
     * Empty Constructor
     *
     */
    public UInt8() {}

    /**
     * Creates a UINT8 datatype from an integer
     *
     * @param int
     */
    public UInt8(int value) {
        bs[0] = (byte) (0x000000FF & value);
    }

    /**
     *
     * Gets the byte[] value of the UINT8 datatype
     *
     * @return byte []
     */
    public byte[] getValue() {
        return bs;
    }

    /**
     *
     * Sets the UINT8 value
     *
     * @param byte[]
     */
    public void setValue(byte[] s) {
        bs[0] = s[0];
    }

    /**
     *
     * Transforms an UINT8 into an Integer
     * @param byte
     * @return int
     */
    public int UInt8ToInt(byte value) {
        int out;

        if ((int) value < 0) {
            out = value + 256;
        } else {
            return value;
        }

        return out;
    }
}
