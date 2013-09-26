//==============================================================================
// Brief   : RPT_LIMIT Data Type
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
import mih.types.basic.UnsignedInteger16;

public class RptLimit
		extends
		Sequence<UnsignedInteger16, UnsignedInteger16, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public RptLimit(UnsignedInteger16 max, UnsignedInteger16 start) {
		super(max, start);
	}

	public RptLimit(RptLimit value) {
		super(value.getMaxIEs(), value.getStartingIE());
	}

	public RptLimit() {
		super(new UnsignedInteger16(), new UnsignedInteger16());
	}

	public UnsignedInteger16 getMaxIEs() {
		return getA();
	}

	public void setMaxIEs(UnsignedInteger16 max) {
		setA(max);
	}

	public UnsignedInteger16 getStartingIE() {
		return getB();
	}

	public void setStartingIE(UnsignedInteger16 start) {
		setB(start);
	}
}
