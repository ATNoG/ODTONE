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
 * Class designed to implement a Bitmap of 16 bits
 *
 */
public class Bitmap16 {

    /**
     *
     */
    public byte bmpArray[] = new byte[2];
    /**
     *
     */
    public byte tmp[] = new byte[2];

    /**
     *
     */
    public Bitmap16() {
    }

    /**
     *
     * Transforms a List of Integer into a Bitmap16
     *
     * @param List<Integer>
     */
    public Bitmap16(Vector lst) {
        int value;

        bmpArray[0] = 0x00;
        bmpArray[1] = 0x00;
        tmp[0] = 0x00;
        tmp[1] = 0x00;

        for (int i = 0; i < lst.size(); i++) {
            value = (Integer.parseInt(lst.elementAt(i).toString()));

            if (value > 15 | value < 0) {
                throw new IllegalArgumentException();
            }

            if (value > 7) {
                tmp[0] = 0x01;
                tmp[0] = (byte) (tmp[0] << (value - 8));
                bmpArray[0] = (byte) (bmpArray[0] | tmp[0]);
            }

            if (value < 8) {
                tmp[1] = 0x01;
                tmp[1] = (byte) (tmp[1] << value);
                bmpArray[1] = (byte) (bmpArray[1] | tmp[1]);
            }

            tmp[0] = 0x00;
            tmp[1] = 0x00;
        }
    }

    public Bitmap16(byte[] in) {
        bmpArray = new byte[in.length];
        bmpArray = in;
    }

    /**
     * Getter - retuns the Bitmap16 in a byte[] form
     * @return byte[]
     */
    public byte[] getValue() {
        return bmpArray;
    }

    /**
     * Setter - returns the Bitmap16 in a byte[] form
     * @return byte[]
     */
    public void setValue(byte[] in) {
        bmpArray = new byte[in.length];
        bmpArray = in;
    }
}
