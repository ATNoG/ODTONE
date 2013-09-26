//==============================================================================
// Brief   : OPERATOR_ID Data Type
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

public class OperatorId
		extends
		Sequence<OpName, OpNamespace, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public OperatorId(OpName opName, OpNamespace opNamespace) {
		super(opName, opNamespace);
	}

	public OperatorId(OperatorId value) {
		super(value.getOpName(), value.getOpNamespace());
	}

	public OperatorId() {
		super(new OpName(), new OpNamespace());
	}

	public OpName getOpName() {
		return getA();
	}

	public void setOpName(OpName opName) {
		setA(opName);
	}

	public OpNamespace getOpNamespace() {
		return getB();
	}

	public void setOpNamespace(OpNamespace opNamespace) {
		setB(opNamespace);
	}
}
