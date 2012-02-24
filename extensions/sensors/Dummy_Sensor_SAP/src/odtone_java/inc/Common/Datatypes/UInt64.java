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
public class UInt64 {
    byte bs[] = new byte[8];

    /**
     * Creates a UInt64 datatype from a long
     *
     * @param long
     * @return byte[]
     */
    public byte[] UInt64(long value) {
        bs[7] = (byte) (0x00000000000000FFL & value);
        bs[6] = (byte) ((0x000000000000FF00L & value) >> 8);
        bs[5] = (byte) ((0x0000000000FF0000L & value) >> 16);
        bs[4] = (byte) ((0x00000000FF000000L & value) >> 24);
        bs[3] = (byte) ((0x000000FF00000000L & value) >> 32);
        bs[2] = (byte) ((0x0000FF0000000000L & value) >> 40);
        bs[1] = (byte) ((0x00FF000000000000L & value) >> 48);
        bs[0] = (byte) ((0xFF00000000000000L & value) >> 56);

        return bs;
    }

    /**
     *  Gets the byte [] value of the UInt64 datatype
     * @return byte[]
     */
    public byte[] getValue() {
        return bs;
    }
}
