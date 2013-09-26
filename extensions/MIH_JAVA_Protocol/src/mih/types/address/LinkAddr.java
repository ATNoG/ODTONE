//==============================================================================
// Brief   : LINK_ADDR Data Type
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

package mih.types.address;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;

import mih.types.Serializeable;
import mih.types.basic.UnsignedInteger8;

public class LinkAddr implements Serializeable {

	public LinkAddr(MacAddr addr) {
		selector = new UnsignedInteger8(0);
		object = addr;
	}

	public LinkAddr(ThreeGpp3GCellId addr) {
		selector = new UnsignedInteger8(1);
		object = addr;
	}

	public LinkAddr(ThreeGpp2GCellId addr) {
		selector = new UnsignedInteger8(2);
		object = addr;
	}

	public LinkAddr(ThreeGppAddr addr) {
		selector = new UnsignedInteger8(3);
		object = addr;
	}

	public LinkAddr(ThreeGpp2Addr addr) {
		selector = new UnsignedInteger8(4);
		object = addr;
	}

	public LinkAddr(OtherL2Addr addr) {
		selector = new UnsignedInteger8(5);
		object = addr;
	}

	public LinkAddr(LinkAddr value) {
		this.selector = value.selector;
		this.object = value.object;
	}

	public LinkAddr() {
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
			((MacAddr)object).toBytes(stream);
			break;

		case 1:
			((ThreeGpp3GCellId)object).toBytes(stream);
			break;

		case 2:
			((ThreeGpp2GCellId)object).toBytes(stream);
			break;

		case 3:
			((ThreeGppAddr)object).toBytes(stream);
			break;

		case 4:
			((ThreeGpp2Addr)object).toBytes(stream);
			break;

		case 5:
			((OtherL2Addr)object).toBytes(stream);
			break;
		}
	}

	public void fromBytes(ByteArrayInputStream stream) throws Exception {
		selector.fromBytes(stream);

		switch(selector.getValue()) {
		case 0:
			object = new MacAddr();
			((MacAddr)object).fromBytes(stream);
			break;

		case 1:
			object = new ThreeGpp3GCellId();
			((ThreeGpp3GCellId)object).fromBytes(stream);
			break;

		case 2:
			object = new ThreeGpp2GCellId();
			((ThreeGpp2GCellId)object).fromBytes(stream);
			break;

		case 3:
			object = new ThreeGppAddr();
			((ThreeGppAddr)object).fromBytes(stream);
			break;

		case 4:
			object = new ThreeGpp2Addr();
			((ThreeGpp2Addr)object).fromBytes(stream);
			break;

		case 5:
			object = new OtherL2Addr();
			((OtherL2Addr)object).fromBytes(stream);
			break;
		}
	}

	UnsignedInteger8 selector;
	Object object;
}