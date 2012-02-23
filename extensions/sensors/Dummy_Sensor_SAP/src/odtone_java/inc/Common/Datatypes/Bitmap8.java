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

//~--- JDK imports ------------------------------------------------------------
import java.util.Vector;

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
public class Bitmap8 {

    /**
     *
     */
    public byte bmpArray[] = new byte[1];
    /**
     *
     */
    public byte tmp[] = new byte[1];

    /**
     *
     */
    public Bitmap8() {
    }

    /**
     *
     * Transforms a List of Integer into a Bitmap8
     *
     * @param List<Integer>
     */
    public Bitmap8(Vector lst) {
        int value;

        bmpArray[0] = 0x00;
        tmp[0] = 0x00;

        for (int i = 0; i < lst.size(); i++) {
            value = (Integer.parseInt(lst.elementAt(i).toString()));

            if (value > 7 | value < 0) {
                throw new IllegalArgumentException();
            }

            tmp[0] = 0x01;
            tmp[0] = (byte) (tmp[0] << value);
            bmpArray[0] = (byte) (bmpArray[0] | tmp[0]);
        }
    }

    /**
     * Getter - retuns the Bitmap16 in a byte[] form
     * @return byte[]
     */
    public byte[] getValue() {
        return bmpArray;
    }
}

