//==============================================================================
// Brief   : 3GPP_3G_CELL_ID Data Type
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

public class ThreeGpp3GCellId
		extends
		Sequence<PlmnId, CellId, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public ThreeGpp3GCellId(PlmnId plmn, CellId cell) {
		super(plmn, cell);
	}

	public ThreeGpp3GCellId(ThreeGpp3GCellId value) {
		super(value.getPlmnID(), value.getCellID());
	}

	public ThreeGpp3GCellId() {
		super(new PlmnId(), new CellId());
	}

	public PlmnId getPlmnID() {
		return getA();
	}

	public void setPlmnID(PlmnId plmn) {
		setA(plmn);
	}

	public CellId getCellID() {
		return getB();
	}

	public void setCellID(CellId cell) {
		setB(cell);
	}
}