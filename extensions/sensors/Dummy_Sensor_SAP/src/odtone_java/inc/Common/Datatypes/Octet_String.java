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
/**
 *
 * @author marcelo lebre <marcelolebre@av.it.pt>
 *
 */
/**
 *
 * Class designed to implement an Octet_String
 *
 */
public class Octet_String {

    byte[] string_list_byte;
    String str;

    /**
     *
     * Create another Octet_String
     *
     * @param Octet_String
     */
    public Octet_String(Octet_String os) {
        string_list_byte = new byte[os.getValue().length];
        string_list_byte = os.getValue();
        str = os.get_String();
    }

    /**
     *
     * Transform a string into an Octet_String datatype
     *
     * @param Stromg
     */
    public Octet_String(String value) {
        str = value;
        string_list_byte = new byte[(value.length() + 1)];
        string_list_byte[0] = new UInt8((byte) value.length()).getValue()[0];

        for (int i = 1, j = 0; j < value.length(); i++, j++) {
            string_list_byte[i] = new UInt8(value.charAt(j)).getValue()[0];
        }
    }

    public String get_String() {
        return str;
    }

    /**
     *
     * Getter - Returns a Octet_String Datatype in a form of byte array
     *
     * @return byte[]
     */
    public byte[] getValue() {
        return string_list_byte;
    }

    public Octet_String() {
    }

    public Octet_String(byte[] in) {
        string_list_byte = new byte[in.length];
        string_list_byte = in;
        byte[] tmp = new byte[in.length - 1];
        for (int i = 0; i < in.length - 1; i++) {
            tmp[i] = in[i + 1];
        }
        str = new String(tmp);
    }

    /**
     *
     * Setter - Sets a Octet_String  in a form of byte array
     *
     * @return byte[]
     */
    public void setValue(byte[] in) {
        string_list_byte = new byte[in.length + 1];
        string_list_byte[0] = (byte) in.length;
        for (int i = 1, j = 0; j < in.length; j++, i++) {
            string_list_byte[i] = in[j];
        }
    }
}
