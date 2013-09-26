//==============================================================================
// Brief   : QOS_LIST Data Type
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
import mih.types.qos.auxiliar.ListAvgPkTxDelay;
import mih.types.qos.auxiliar.ListMaxPkTxDelay;
import mih.types.qos.auxiliar.ListMinPkTxDelay;
import mih.types.qos.auxiliar.ListPkDelayJitter;
import mih.types.qos.auxiliar.ListPkLossRate;

public class QosList
		extends
		Sequence<NumCosTypes, ListMinPkTxDelay, ListAvgPkTxDelay, ListMaxPkTxDelay, ListPkDelayJitter, ListPkLossRate, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public QosList(NumCosTypes numCosTypes, ListMinPkTxDelay listMinPkTxDelay, ListAvgPkTxDelay listAvgPkTxDelay, ListMaxPkTxDelay listMaxPkTxDelay, ListPkDelayJitter listPkDelayJitter, ListPkLossRate listPkLossRate) {
		super(numCosTypes, listMinPkTxDelay, listAvgPkTxDelay, listMaxPkTxDelay, listPkDelayJitter, listPkLossRate);
	}

	public QosList(QosList value) {
		super(value.getNumCosTypes(), value.getListMinPkTxDelay(), value.getListAvgPkTxDelay(), value.getListMaxPkTxDelay(), value.getListPkDelayJitter(), value.getListPkLossRate());
	}

	public QosList() {
		super(new NumCosTypes(), new ListMinPkTxDelay(), new ListAvgPkTxDelay(), new ListMaxPkTxDelay(), new ListPkDelayJitter(), new ListPkLossRate());
	}

	public NumCosTypes getNumCosTypes() {
		return getA();
	}

	public void setNumCosTypes(NumCosTypes type) {
		setA(type);
	}

	public ListMinPkTxDelay getListMinPkTxDelay() {
		return getB();
	}

	public void setListMinPkTxDelay(ListMinPkTxDelay listMinPkTxDelay) {
		setB(listMinPkTxDelay);
	}

	public ListAvgPkTxDelay getListAvgPkTxDelay() {
		return getC();
	}

	public void setListAvgPkTxDelay(ListAvgPkTxDelay listAvgPkTxDelay) {
		setC(listAvgPkTxDelay);
	}

	public ListMaxPkTxDelay getListMaxPkTxDelay() {
		return getD();
	}

	public void setListMaxPkTxDelay(ListMaxPkTxDelay listMaxPkTxDelay) {
		setD(listMaxPkTxDelay);
	}

	public ListPkDelayJitter getListPkDelayJitter() {
		return getE();
	}

	public void setListPkDelayJitter(ListPkDelayJitter listPkDelayJitter) {
		setE(listPkDelayJitter);
	}

	public ListPkLossRate getListPkLossRate() {
		return getF();
	}

	public void setListPkLossRate(ListPkLossRate listPkLossRate) {
		setF(listPkLossRate);
	}
}
