//==============================================================================
// Brief   : QOS_PARAM_VAL Data Type
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

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;

import mih.types.Serializeable;
import mih.types.basic.UnsignedInteger8;
import mih.types.qos.auxiliar.ListAvgPkTxDelay;
import mih.types.qos.auxiliar.ListMaxPkTxDelay;
import mih.types.qos.auxiliar.ListMinPkTxDelay;
import mih.types.qos.auxiliar.ListPkDelayJitter;
import mih.types.qos.auxiliar.ListPkLossRate;

public class QosParamVal implements Serializeable {

	public QosParamVal(NumCosTypes numCosTypes) {
		selector = new UnsignedInteger8(0);
		object = numCosTypes;
	}

	public QosParamVal(ListMinPkTxDelay listMinPkTxDelay) {
		selector = new UnsignedInteger8(1);
		object = listMinPkTxDelay;
	}

	public QosParamVal(ListAvgPkTxDelay listAvgPkTxDelay) {
		selector = new UnsignedInteger8(2);
		object = listAvgPkTxDelay;
	}

	public QosParamVal(ListMaxPkTxDelay linkMaxPkTxDelay) {
		selector = new UnsignedInteger8(3);
		object = linkMaxPkTxDelay;
	}

	public QosParamVal(ListPkDelayJitter listPkDelayJitter) {
		selector = new UnsignedInteger8(4);
		object = listPkDelayJitter;
	}

	public QosParamVal(ListPkLossRate listPkLossRate) {
		selector = new UnsignedInteger8(5);
		object = listPkLossRate;
	}

	public QosParamVal(QosParamVal value) {
		this.selector = value.selector;
		this.object = value.object;
	}

	public QosParamVal() {
		selector = new UnsignedInteger8(0);
		object = new Object();
	}

	public UnsignedInteger8 getSelector() {
		return selector;
	}

	public void setSelector(UnsignedInteger8 selector) {
		this.selector = selector;
	}

	public Object getObject() {
		return object;
	}

	public void setObject(Object object) {
		this.object = object;
	}

	public void toBytes(ByteArrayOutputStream stream) throws Exception {
		selector.toBytes(stream);

		switch(selector.getValue()) {
		case 0:
			((NumCosTypes)object).toBytes(stream);
			break;

		case 1:
			((ListMinPkTxDelay)object).toBytes(stream);
			break;

		case 2:
			((ListAvgPkTxDelay)object).toBytes(stream);
			break;

		case 3:
			((ListMaxPkTxDelay)object).toBytes(stream);
			break;

		case 4:
			((ListPkDelayJitter)object).toBytes(stream);
			break;

		case 5:
			((ListPkLossRate)object).toBytes(stream);
			break;
		}
	}

	public void fromBytes(ByteArrayInputStream stream) throws Exception {
		selector.fromBytes(stream);

		switch(selector.getValue()) {
		case 0:
			object = new NumCosTypes();
			((NumCosTypes)object).fromBytes(stream);
			break;

		case 1:
			object = new ListMinPkTxDelay();
			((ListMinPkTxDelay)object).fromBytes(stream);
			break;

		case 2:
			object = new ListAvgPkTxDelay();
			((ListAvgPkTxDelay)object).fromBytes(stream);
			break;

		case 3:
			object = new ListMaxPkTxDelay();
			((ListMaxPkTxDelay)object).fromBytes(stream);
			break;

		case 4:
			object = new ListPkDelayJitter();
			((ListPkDelayJitter)object).fromBytes(stream);
			break;

		case 5:
			object = new ListPkLossRate();
			((ListPkLossRate)object).fromBytes(stream);
			break;
		}
	}

	UnsignedInteger8 selector;
	Object object;
}