//==============================================================================
// Brief   : COST Data Type
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

public class Cost
		extends
		Sequence<CostUnit, CostValue, CostCurr, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public Cost(CostUnit costUnit, CostValue costValue, CostCurr costCurr) {
		super(costUnit, costValue, costCurr);
	}

	public Cost(Cost value) {
		super(value.getCostUnit(), value.getCostValue(), value.getCostCurr());
	}

	public Cost() {
		super(new CostUnit(), new CostValue(), new CostCurr());
	}

	public CostUnit getCostUnit() {
		return getA();
	}

	public void setCostUnit(CostUnit unit) {
		setA(unit);
	}

	public CostValue getCostValue() {
		return getB();
	}

	public void setCostValue(CostValue value) {
		setB(value);
	}

	public CostCurr getCostCurr() {
		return getC();
	}

	public void setCostCurr(CostCurr curr) {
		setC(curr);
	}
}
