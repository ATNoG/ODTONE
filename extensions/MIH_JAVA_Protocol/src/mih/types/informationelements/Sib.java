//==============================================================================
// Brief   : SIB Data Type
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

package mih.types.informationelements;

import mih.types.Serializeable;
import mih.types.address.CellId;
import mih.types.basic.Sequence;

public class Sib
		extends
		Sequence<CellId, FqCodeNum, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public Sib(CellId cellId, FqCodeNum fqCodeNum) {
		super(cellId, fqCodeNum);
	}

	public Sib(Sib value) {
		super(value.getCellId(), value.getFqCodeNum());
	}

	public Sib() {
		super(new CellId(), new FqCodeNum());
	}

	public CellId getCellId() {
		return getA();
	}

	public void setCellId(CellId cellId) {
		setA(cellId);
	}

	public FqCodeNum getFqCodeNum() {
		return getB();
	}

	public void setFqCodeNum(FqCodeNum fqCodeNum) {
		setB(fqCodeNum);
	}
}
