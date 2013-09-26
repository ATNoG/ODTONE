//==============================================================================
// Brief   : BIN_CIVIC_LOC Data Type
// Authors : Carlos Guimarães <cguimaraes@av.it.pt>
//------------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2009-2013 Universidade Aveiro
// Copyright (C) 2009-2013 Instituto de Telecomunicações - Pólo Aveiro
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//==============================================================================

package mih.types.location;

import mih.types.Serializeable;
import mih.types.basic.Sequence;

public class BinCivicLoc
		extends
		Sequence<BinGeoLoc, XmlGeoLoc, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public BinCivicLoc(BinGeoLoc binGeoLoc, XmlGeoLoc xmlGeoLoc) {
		super(binGeoLoc, xmlGeoLoc);
	}

	public BinCivicLoc(BinCivicLoc value) {
		super(value.getBinGeoLoc(), value.getXmlGeoLoc());
	}

	public BinCivicLoc() {
		super(new BinGeoLoc(), new XmlGeoLoc());
	}

	public BinGeoLoc getBinGeoLoc() {
		return getA();
	}

	public void setBinGeoLoc(BinGeoLoc binGeoLoc) {
		setA(binGeoLoc);
	}

	public XmlGeoLoc getXmlGeoLoc() {
		return getB();
	}

	public void setXmlGeoLoc(XmlGeoLoc xmlGeoLoc) {
		setB(xmlGeoLoc);
	}
}
