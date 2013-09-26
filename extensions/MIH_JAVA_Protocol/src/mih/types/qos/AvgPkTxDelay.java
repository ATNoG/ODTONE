//==============================================================================
// Brief   : AVG_PK_TX_DELAY Data Type
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

package mih.types.qos;

import mih.types.Serializeable;
import mih.types.basic.Sequence;
import mih.types.basic.UnsignedInteger16;

public class AvgPkTxDelay
		extends
		Sequence<CosId, UnsignedInteger16, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public AvgPkTxDelay(CosId cos, UnsignedInteger16 value) {
		super(cos, value);
	}

	public AvgPkTxDelay(AvgPkTxDelay value) {
		super(value.getCosId(), value.getValue());
	}

	public AvgPkTxDelay() {
		super(new CosId(), new UnsignedInteger16());
	}

	public CosId getCosId() {
		return getA();
	}

	public void setType(CosId cos) {
		setA(cos);
	}

	public UnsignedInteger16 getValue() {
		return getB();
	}

	public void setValue(UnsignedInteger16 attr) {
		setB(attr);
	}
}
