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
package lightMIHF;

//~--- JDK imports ------------------------------------------------------------
import java.util.Vector;

/**
 *
 * @author marcelo lebre <marcelolebre@av.it.pt>
 *
 */
/**
 *
 * Class designed to implement a Bitmap of 64 bits
 *
 */
public class Bitmap64 {

    /**
     *
     */
    public byte bmpArray[] = new byte[8];
    /**
     *
     */
    public byte tmp[] = new byte[8];

    /**
     *
     * Transforms a List of Integer into a Bitmap64
     *
     * @param List<Integer>
     */
    public Bitmap64(Vector lst) {
        int value;

        bmpArray[0] = 0x00;
        bmpArray[1] = 0x00;
        bmpArray[2] = 0x00;
        bmpArray[3] = 0x00;
        bmpArray[4] = 0x00;
        bmpArray[5] = 0x00;
        bmpArray[6] = 0x00;
        bmpArray[7] = 0x00;
        tmp[0] = 0x00;
        tmp[1] = 0x00;
        tmp[2] = 0x00;
        tmp[3] = 0x00;
        tmp[4] = 0x00;
        tmp[5] = 0x00;
        tmp[6] = 0x00;
        tmp[7] = 0x00;

        for (int i = 0; i < lst.size(); i++) {
            value = (Integer.parseInt(lst.elementAt(i).toString()));

            if (value > 63 | value < 0) {
                throw new IllegalArgumentException();
            }

            if (value < 8) {
                tmp[7] = 0x01;
                tmp[7] = (byte) (tmp[7] << value);
                bmpArray[7] = (byte) (bmpArray[7] | tmp[7]);
            }

            if (value > 7 & value < 16) {
                tmp[6] = 0x01;
                tmp[6] = (byte) (tmp[6] << (value - 8));
                bmpArray[6] = (byte) (bmpArray[6] | tmp[6]);
            }

            if (value > 15 & value < 24) {
                tmp[5] = 0x01;
                tmp[5] = (byte) (tmp[5] << value - 16);
                bmpArray[5] = (byte) (bmpArray[5] | tmp[5]);
            }

            if (value > 23 & value < 32) {
                tmp[4] = 0x01;
                tmp[4] = (byte) (tmp[4] << value - 24);
                bmpArray[4] = (byte) (bmpArray[4] | tmp[4]);
            }

            if (value > 31 & value < 40) {
                tmp[3] = 0x01;
                tmp[3] = (byte) (tmp[3] << (value - 32));
                bmpArray[3] = (byte) (bmpArray[3] | tmp[3]);
            }

            if (value > 39 & value < 48) {
                tmp[2] = 0x01;
                tmp[2] = (byte) (tmp[2] << value - 40);
                bmpArray[2] = (byte) (bmpArray[2] | tmp[2]);
            }

            if (value > 47 & value < 56) {
                tmp[1] = 0x01;
                tmp[1] = (byte) (tmp[1] << value - 48);
                bmpArray[1] = (byte) (bmpArray[1] | tmp[1]);
            }

          

            tmp[0] = 0x00;
            tmp[1] = 0x00;
            tmp[2] = 0x00;
            tmp[3] = 0x00;
            tmp[4] = 0x00;
            tmp[5] = 0x00;
            tmp[6] = 0x00;
            tmp[7] = 0x00;
        }
    }

    public Bitmap64(byte[] in) {
        bmpArray = new byte[in.length];
        bmpArray = in;
    }

    /**
     * Getter - retuns the Bitmap64 Datatype in a byte[] form
     * @return byte[]
     */
    public byte[] getValue() {
        return bmpArray;
    }
}
