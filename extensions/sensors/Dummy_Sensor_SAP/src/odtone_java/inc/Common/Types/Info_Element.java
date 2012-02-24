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
package odtone_java.inc.Common.Types;

import odtone_java.inc.Common.Serialization;

/**
 *
 * @author marcelo lebre <marcelolebre@av.it.pt>
 *
 */
public class Info_Element {

    byte[] infoElement;
    Serialization srlz = new Serialization();

    public Info_Element() {
    }
    
    public Info_Element(int type, byte[] in) {
        infoElement = new byte[srlz.serializeInfoElements(type, in).length];
        infoElement = srlz.serializeInfoElements(type, in);
    }

    public byte[] get_Info_Element() {
        return infoElement;
    }

    public void set_Info_Element(byte[] in) {
        infoElement = new byte[in.length];
        infoElement = in;
    }
}
