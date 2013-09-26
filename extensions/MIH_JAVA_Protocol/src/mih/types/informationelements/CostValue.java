//==============================================================================
// Brief   : COST_VALUE Data Type
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
import mih.types.basic.UnsignedInteger16;
import mih.types.basic.UnsignedInteger32;

public class CostValue
		extends
		Sequence<UnsignedInteger32, UnsignedInteger16, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public CostValue(UnsignedInteger32 integer, UnsignedInteger16 fraction) {
		super(integer, fraction);
	}

	public CostValue(CostValue value) {
		super(value.getIntegerPart(), value.getFractionPart());
	}

	public CostValue() {
		super(new UnsignedInteger32(), new UnsignedInteger16());
	}

	public UnsignedInteger32 getIntegerPart() {
		return getA();
	}

	public void setIntegerPart(UnsignedInteger32 integer) {
		setA(integer);
	}

	public UnsignedInteger16 getFractionPart() {
		return getB();
	}

	public void setFractionPart(UnsignedInteger16 fraction) {
		setB(fraction);
	}
}
