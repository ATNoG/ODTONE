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
 * Class designed to implement an Unsigned Integer with 32 bits
 *
 */
public class UInt32 {
    byte bs[] = new byte[4];

    /**
     * Empty constructor
     */
    public UInt32() {}

    /**
     * Creates an Unsigned integer 32 from an integer
     * @param integer
     */
    public UInt32(int value) {
        bs[3] = (byte) (0x000000FF & value);
        bs[2] = (byte) ((0x0000FF00 & value) >> 8);
        bs[1] = (byte) ((0x00FF0000 & value) >> 16);
        bs[0] = (byte) ((0xFF000000 & value) >> 24);
    }

    /**
     * Sets the UINT32 value
     *
     * @param byte []
     */
    public void setValue(byte[] s) {
        bs[0] = s[0];
        bs[1] = s[1];
        bs[2] = s[2];
        bs[3] = s[3];
    }

    /**
     * Gets the byte [] value of the UInt32 datatype
     * @return byte []
     */
    public byte[] getValue() {
        return bs;
    }
    public static final int UInt32ToInt(byte[] b) {
        int out = 0;


            out = (new UInt8().UInt8ToInt(b[0]) * 1024) +
                    (new UInt8().UInt8ToInt(b[1])*512)+
                    (new UInt8().UInt8ToInt(b[2])*256)+
                    (new UInt8().UInt8ToInt(b[3]));


        return out;
    }
}