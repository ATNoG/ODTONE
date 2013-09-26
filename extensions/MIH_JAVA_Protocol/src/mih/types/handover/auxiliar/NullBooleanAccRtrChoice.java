//==============================================================================
// Brief   : CHOICE(NULL, BOOLEAN, ACC_RTR) Data Type
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

package mih.types.handover.auxiliar;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;

import mih.types.Serializeable;
import mih.types.basic.Null;
import mih.types.basic.UnsignedInteger8;
import mih.types.general.Boolean;
import mih.types.handover.AccRtr;

public class NullBooleanAccRtrChoice implements Serializeable {

	public NullBooleanAccRtrChoice(Null value) {
		selector = new UnsignedInteger8(0);
		object = value;
	}

	public NullBooleanAccRtrChoice(Boolean value) {
		selector = new UnsignedInteger8(1);
		object = value;
	}

	public NullBooleanAccRtrChoice(AccRtr value) {
		selector = new UnsignedInteger8(2);
		object = value;
	}

	public NullBooleanAccRtrChoice(NullBooleanAccRtrChoice value) {
		selector = value.selector;
		object = value.object;
	}

	public NullBooleanAccRtrChoice() {
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
			((Boolean)object).toBytes(stream);
			break;

		case 2:
			((AccRtr)object).toBytes(stream);
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
			object = new Boolean();
			((Boolean)object).fromBytes(stream);
			break;

		case 2:
			object = new AccRtr();
			((AccRtr)object).fromBytes(stream);
			break;
		}
	}

	UnsignedInteger8 selector;
	Object object;
};