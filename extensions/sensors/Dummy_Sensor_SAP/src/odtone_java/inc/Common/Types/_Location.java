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
import odtone_java.inc.Common.Datatypes.UInt32;
import odtone_java.inc.Common.Types.Information.Civic_Addr;
import odtone_java.inc.Common.Types.Information.Cntry_Code;
import odtone_java.inc.Common.Serialization;

/**
 *
 * @author marcelo lebre <marcelolebre@av.it.pt>
 *
 */
/**
 *
 * Class designed to construct a location related objects
 * This class nests objects that relate to the MIIS location system
 *
 */
public class _Location {

    /**
     *
     * Class designed to construct a Bin_Civic_Loc objects
     *
     */
    public class Bin_Civic_Loc {

        byte[] bin_civic_loc;

        /**
         * Constructor
         * @param Civic_Addr
         */
        public Bin_Civic_Loc(Civic_Addr civicAddr) {
            Serialization srlz = new Serialization();

            bin_civic_loc = new byte[srlz.choice(civicAddr.get_Civic_Addr(), 1).length];
            bin_civic_loc = srlz.choice(civicAddr.get_Civic_Addr(), 1);
        }

        /**
         * Constructor
         * @param Centry_Code
         */
        public Bin_Civic_Loc(Cntry_Code cntryCode) {
            Serialization srlz = new Serialization();

            bin_civic_loc = new byte[srlz.choice(cntryCode.get_Cntry_Code(), 0).length];
            bin_civic_loc = srlz.choice(cntryCode.get_Cntry_Code(), 0);
        }

        /**
         * Getter- Returns the Bin Civic Loc value in byte [] form
         * @return byte []
         */
        public byte[] get_Bin_Civic_Loc() {
            return bin_civic_loc;
        }
    }

    /**
     *
     * Class designed to construct a Cell_ID objects
     *
     */
    public class Cell_ID {

        UInt32 cell_id;

        /**
         * Constructor
         * @param int
         */
        public Cell_ID(int i) {
            cell_id = new UInt32(i);
        }

        /**
         * Getter - Returns the Cell_ID value in byte [] form
         * @return byte []
         */
        public byte[] get_Cell_ID() {
            return cell_id.getValue();
        }
         public UInt32 get_Cell_ID_Value() {
            return cell_id;
        }
         public void set_Cell_ID(byte[] in) {
            cell_id = new UInt32();
            cell_id.setValue(in);
        }
    }

    /**
     *
     * Class designed to construct a Civic_Loc objects
     *
     */
    public class Civic_Loc {

        byte[] civic_loc;

        /**
         * Constructor
         * @param Bin_Civic_Loc
         */
        public Civic_Loc(Bin_Civic_Loc civicLoc) {
            Serialization srlz = new Serialization();

            civic_loc = new byte[srlz.choice(civicLoc.get_Bin_Civic_Loc(), 0).length];
            civic_loc = srlz.choice(civicLoc.get_Bin_Civic_Loc(), 0);
        }

        /**
         * Constructor
         * @param XML_Civic_Loc
         */
        public Civic_Loc(XML_Civic_Loc xmlLoc) {
            Serialization srlz = new Serialization();

            civic_loc = new byte[srlz.choice(xmlLoc.get_XML_Civic_Loc(), 1).length];
            civic_loc = srlz.choice(xmlLoc.get_XML_Civic_Loc(), 1);
        }

        /**
         * Getter - Returns Civic Loc value in byte [] form
         * @return byte []
         */
        public byte[] get_Civic_Loc() {
            return civic_loc;
        }
    }

    /**
     *
     * Class designed to construct a Geo_Loc objects
     *
     */
    public class Geo_Loc {

        byte[] geo_loc;

        /**
         * Constructor
         * @param Civic_Loc
         */
        public Geo_Loc(Bin_Civic_Loc civicLoc) {
            Serialization srlz = new Serialization();

            geo_loc = new byte[srlz.choice(civicLoc.get_Bin_Civic_Loc(), 0).length];
            geo_loc = srlz.choice(civicLoc.get_Bin_Civic_Loc(), 0);
        }

        /**
         * Constructor
         * @param XML_Civic_Loc
         */
        public Geo_Loc(XML_Civic_Loc xmlLoc) {
            Serialization srlz = new Serialization();

            geo_loc = new byte[srlz.choice(xmlLoc.get_XML_Civic_Loc(), 1).length];
            geo_loc = srlz.choice(xmlLoc.get_XML_Civic_Loc(), 1);
        }

        /**
         * Getter - Returns Geo Loc value in byte [] form
         * @return byte []
         */
        public byte[] get_Geo_Loc() {
            return geo_loc;
        }
    }

    /**
     *
     * Class designed to construct a Location objects
     *
     */
    public class Location {

        byte[] location;

        /**
         * Constructor
         * @param Cell_ID
         */
        public Location(Cell_ID cellID) {
            Serialization srlz = new Serialization();

            location = new byte[srlz.choice(cellID.get_Cell_ID(), 2).length];
            location = srlz.choice(cellID.get_Cell_ID(), 2);
        }

        /**
         * Constructor
         * @param Civic_Loc
         */
        public Location(Civic_Loc civicLoc) {
            Serialization srlz = new Serialization();

            location = new byte[srlz.choice(civicLoc.get_Civic_Loc(), 0).length];
            location = srlz.choice(civicLoc.get_Civic_Loc(), 0);
        }

        /**
         * Constructor
         * @param Geo_Loc
         */
        public Location(Geo_Loc geoLoc) {
            Serialization srlz = new Serialization();

            location = new byte[srlz.choice(geoLoc.get_Geo_Loc(), 1).length];
            location = srlz.choice(geoLoc.get_Geo_Loc(), 1);
        }

        /**
         * Getter - Returns Location value in byte [] form
         * @return byte []
         */
        public byte[] get_Location() {
            return location;
        }

        public void set_Location(byte[] in) {
            location = new byte[in.length];
            location = in;
        }
    }

    /**
     *
     * Class designed to construct a XML_Civic_Loc objects
     *
     */
    public class XML_Civic_Loc {

        byte[] xml_civic_loc;

        /**
         * Constructor
         * @param XML_Civic_Loc
         */
        public XML_Civic_Loc(Octet_String os) {
            xml_civic_loc = new byte[os.getValue().length];
            xml_civic_loc = os.getValue();
        }

        /**
         * Getter - Returns XML Civic Loc value in byte [] form
         * @return byte []
         */
        public byte[] get_XML_Civic_Loc() {
            return xml_civic_loc;
        }
    }
}
