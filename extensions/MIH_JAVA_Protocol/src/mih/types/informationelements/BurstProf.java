//==============================================================================
// Brief   : BURST_PROF Data Type
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
import mih.types.basic.Sequence;

public class BurstProf
		extends
		Sequence<DownBp, UpBp, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public BurstProf(DownBp downBp, UpBp upBp) {
		super(downBp, upBp);
	}

	public BurstProf(BurstProf value) {
		super(value.getDownBp(), value.getUpBp());
	}

	public BurstProf() {
		super(new DownBp(), new UpBp());
	}

	public DownBp getDownBp() {
		return getA();
	}

	public void setDownBp(DownBp downBp) {
		setA(downBp);
	}

	public UpBp getUpBp() {
		return getB();
	}

	public void setUpBp(UpBp upBp) {
		setB(upBp);
	}
}
