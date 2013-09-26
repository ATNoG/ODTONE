//==============================================================================
// Brief   : CHOICE(NULL, QUERIER_LOC) Data Type
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

package mih.types.informationservicequery.auxiliar;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;

import mih.types.Serializeable;
import mih.types.basic.Null;
import mih.types.basic.UnsignedInteger8;
import mih.types.informationservicequery.QuerierLoc;

public class NullQuerierLocChoice implements Serializeable {

	public NullQuerierLocChoice(Null value) {
		selector = new UnsignedInteger8(0);
		object = value;
	}

	public NullQuerierLocChoice(QuerierLoc value) {
		selector = new UnsignedInteger8(1);
		object = value;
	}

	public NullQuerierLocChoice(NullQuerierLocChoice value) {
		selector = value.selector;
		object = value.object;
	}

	public NullQuerierLocChoice() {
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
			((Null)object).toBytes(stream);
			break;

		case 1:
			((QuerierLoc)object).toBytes(stream);
			break;
		}
	}

	public void fromBytes(ByteArrayInputStream stream) throws Exception {
		selector.fromBytes(stream);

		switch(selector.getValue()) {
		case 0:
			object = new Null();
			((Null)object).fromBytes(stream);
			break;

		case 1:
			object = new QuerierLoc();
			((QuerierLoc)object).fromBytes(stream);
			break;
		}
	}

	UnsignedInteger8 selector;
	Object object;
};