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
 * Class designed to implement a Bitmap of 32 bits
 *
 */
public class Bitmap32 {

    /**
     *
     */
    public byte bmpArray[] = new byte[4];
    /**
     *
     */
    public byte tmp[] = new byte[4];

    /**
     *Empty constructor
     */
    public Bitmap32() {
    }

    /**
     *
     * Transforms a List of Integer into a Bitmap32
     *
     * @param List<Integer>
     */
    public Bitmap32(Vector lst) {
        int value;

        bmpArray[0] = 0x00;
        bmpArray[1] = 0x00;
        bmpArray[2] = 0x00;
        bmpArray[3] = 0x00;
        tmp[0] = 0x00;
        tmp[1] = 0x00;
        tmp[2] = 0x00;
        tmp[3] = 0x00;

        for (int i = 0; i < lst.size(); i++) {
           
            value = (Integer.parseInt(lst.elementAt(i).toString()));

            if (value > 31 | value < 0) {
                throw new IllegalArgumentException();
            }

            if (value > 7 & value < 16) {
                tmp[2] = 0x01;
                tmp[2] = (byte) (tmp[2] << (value - 8));
                bmpArray[2] = (byte) (bmpArray[2] | tmp[2]);
            }

            if (value > 15 & value < 24) {
                tmp[1] = 0x01;
                tmp[1] = (byte) (tmp[1] << value - 16);
                bmpArray[1] = (byte) (bmpArray[1] | tmp[1]);
            }

            if (value > 23) {
                tmp[0] = 0x01;
                tmp[0] = (byte) (tmp[0] << value - 24);
                bmpArray[0] = (byte) (bmpArray[0] | tmp[0]);
            }

            if (value < 8) {
                tmp[3] = 0x01;
                tmp[3] = (byte) (tmp[3] << value);
                bmpArray[3] = (byte) (bmpArray[3] | tmp[3]);
            }

            tmp[0] = 0x00;
            tmp[1] = 0x00;
            tmp[2] = 0x00;
            tmp[3] = 0x00;
        }
    }

    /**
     * Getter - retuns the Bitmap32 in a byte[] form
     * @return byte[]
     */
    public byte[] getValue() {
        return bmpArray;
    }

    /**
     * Setter - returns the Bitmap32 in a byte[] form
     * @param byte[]
     */
    public void setValue(byte[] in) {
        if (in.length == 4) {
            bmpArray = in;
        } else {
            System.out.println("Size Error - Not a Bitmap32 datatype");
        }
    }
}
