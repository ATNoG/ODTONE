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

//~--- non-JDK imports --------------------------------------------------------
import odtone_java.inc.Common.Datatypes.Octet_String;

/**
 *
 * @author marcelo lebre <marcelolebre@av.it.pt>
 *
 */
/**
 *
 * Class designed to construct a ID object
 *
 */
public class ID {

    /**
     *
     */
    public Octet_String _id;

    // MIHFID for example
    /**
     * Empty Constructor
     *
     *
     */
     public ID() {
    }

    /**
     * Constructor
     *
     * @param Octet_String
     */
    public ID(Octet_String id) {
        _id = id;
    }

    /**
     * Getter - Returns the ID in byte [] form
     * @return byte[]
     */
    public byte[] get_ID() {
        return _id.getValue();
    }

    /**
     * Setter - Sets the ID in byte [] form
     * 
     */
    public void Set_ID(byte[] in) {
        _id.setValue(in);
    }

    public String getIDValue() {
        return _id.toString();
    }
}
