//==============================================================================
// Brief   : REQ_RES_SET Data Type
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

package mih.types.handover;

import mih.types.Serializeable;
import mih.types.basic.Sequence;
import mih.types.qos.QosList;

public class ReqResSet
		extends
		Sequence<QosList, TspContainer, HoCause, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public ReqResSet(QosList qosList, TspContainer tspContainer, HoCause hoCause) {
		super(qosList, tspContainer, hoCause);
	}

	public ReqResSet(ReqResSet value) {
		super(value.getQosList(), value.getTspContainer(), value.getHoCause());
	}

	public ReqResSet() {
		super(new QosList(), new TspContainer(), new HoCause());
	}

	public QosList getQosList() {
		return getA();
	}

	public void setQosList(QosList qosList) {
		setA(qosList);
	}

	public TspContainer getTspContainer() {
		return getB();
	}

	public void setTspContainer(TspContainer tspContainer) {
		setB(tspContainer);
	}

	public HoCause getHoCause() {
		return getC();
	}

	public void setHoCause(HoCause hoCause) {
		setC(hoCause);
	}
}
