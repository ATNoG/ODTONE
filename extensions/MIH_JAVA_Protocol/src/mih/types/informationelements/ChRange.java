//==============================================================================
// Brief   : CH_RANGE Data Type
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
import mih.types.basic.UnsignedInteger32;

public class ChRange
		extends
		Sequence<UnsignedInteger32, UnsignedInteger32, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public ChRange(UnsignedInteger32 low, UnsignedInteger32 high) {
		super(low, high);
	}

	public ChRange(ChRange value) {
		super(value.getLowRange(), value.getHighRange());
	}

	public ChRange() {
		super(new UnsignedInteger32(), new UnsignedInteger32());
	}

	public UnsignedInteger32 getLowRange() {
		return getA();
	}

	public void setLowRange(UnsignedInteger32 low) {
		setA(low);
	}

	public UnsignedInteger32 getHighRange() {
		return getB();
	}

	public void setHighRange(UnsignedInteger32 high) {
		setB(high);
	}
}
