//==============================================================================
// Brief   : 3GPP_2G_CELL_ID Data Type
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

package mih.types.address;

import mih.types.Serializeable;
import mih.types.basic.Sequence;

public class ThreeGpp2GCellId
		extends
		Sequence<PlmnId, Lac , Ci, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public ThreeGpp2GCellId(PlmnId plmn, Lac lac, Ci ci) {
		super(plmn, lac, ci);
	}

	public ThreeGpp2GCellId(ThreeGpp2GCellId value) {
		super(value.getPlmnID(), value.getLac(), value.getCi());
	}

	public ThreeGpp2GCellId() {
		super(new PlmnId(), new Lac(), new Ci());
	}

	public PlmnId getPlmnID() {
		return getA();
	}

	public void setPlmnID(PlmnId plmn) {
		setA(plmn);
	}

	public Lac getLac() {
		return getB();
	}

	public void setLac(Lac lac) {
		setB(lac);
	}

	public Ci getCi() {
		return getC();
	}

	public void setCi(Ci ci) {
		setC(ci);
	}
}