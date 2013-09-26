//==============================================================================
// Brief   : PROXY_ADDR Data Type
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

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;

import mih.types.Serializeable;
import mih.types.basic.UnsignedInteger8;

public class ProxyAddr implements Serializeable {

	public ProxyAddr(Ip4Addr value) {
		selector = new UnsignedInteger8(0);
		object = value;
	}

	public ProxyAddr(Ip6Addr value) {
		selector = new UnsignedInteger8(1);
		object = value;
	}

	public ProxyAddr(Fqdn value) {
		selector = new UnsignedInteger8(2);
		object = value;
	}

	public ProxyAddr(ProxyAddr value) {
		selector = value.selector;
		object = value.object;
	}

	public ProxyAddr() {
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
			((Ip4Addr)object).toBytes(stream);
			break;

		case 1:
			((Ip6Addr)object).toBytes(stream);
			break;

		case 2:
			((Fqdn)object).toBytes(stream);
			break;
		}
	}

	public void fromBytes(ByteArrayInputStream stream) throws Exception {
		selector.fromBytes(stream);

		switch(selector.getValue()) {
		case 0:
			object = new Ip4Addr();
			((Ip4Addr)object).fromBytes(stream);
			break;

		case 1:
			object = new Ip6Addr();
			((Ip6Addr)object).fromBytes(stream);
			break;

		case 2:
			object = new Fqdn();
			((Fqdn)object).fromBytes(stream);
			break;
		}
	}

	UnsignedInteger8 selector;
	Object object;
}