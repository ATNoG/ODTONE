//==============================================================================
// Brief   : QUERIER_LOC Data Type
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

package mih.types.informationservicequery;

import mih.types.Serializeable;
import mih.types.basic.Sequence;
import mih.types.informationservicequery.auxiliar.NullLinkAddrChoice;
import mih.types.informationservicequery.auxiliar.NullLocationChoice;
import mih.types.informationservicequery.auxiliar.NullNghbRadiusChoice;

public class QuerierLoc
		extends
		Sequence<NullLocationChoice, NullLinkAddrChoice, NullNghbRadiusChoice, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public QuerierLoc(NullLocationChoice location, NullLinkAddrChoice linkAddr, NullNghbRadiusChoice nghbRadius) {
		super(location, linkAddr, nghbRadius);
	}

	public QuerierLoc(QuerierLoc value) {
		super(value.getLocation(), value.getLinkAddr(), value.getNghbRadius());
	}

	public QuerierLoc() {
		super(new NullLocationChoice(), new NullLinkAddrChoice(), new NullNghbRadiusChoice());
	}

	public NullLocationChoice getLocation() {
		return getA();
	}

	public void setLocation(NullLocationChoice location) {
		setA(location);
	}

	public NullLinkAddrChoice getLinkAddr() {
		return getB();
	}

	public void setLinkAddr(NullLinkAddrChoice linkAddr) {
		setB(linkAddr);
	}

	public NullNghbRadiusChoice getNghbRadius() {
		return getC();
	}

	public void setNghbRadius(NullNghbRadiusChoice nghbRadius) {
		setC(nghbRadius);
	}
}
