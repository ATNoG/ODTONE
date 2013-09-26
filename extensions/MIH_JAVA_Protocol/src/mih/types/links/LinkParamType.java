//==============================================================================
// Brief   : LINK_PARAM_TYPE Data Type
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

package mih.types.links;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;

import mih.types.Serializeable;
import mih.types.basic.UnsignedInteger8;

public class LinkParamType implements Serializeable {

	public LinkParamType(LinkParamGen type) {
		selector = new UnsignedInteger8(0);
		object = type;
	}

	public LinkParamType(LinkParamQoS type) {
		selector = new UnsignedInteger8(1);
		object = type;
	}

	public LinkParamType(LinkParamGG type) {
		selector = new UnsignedInteger8(2);
		object = type;
	}

	public LinkParamType(LinkParamEdge type) {
		selector = new UnsignedInteger8(3);
		object = type;
	}

	public LinkParamType(LinkParamEth type) {
		selector = new UnsignedInteger8(4);
		object = type;
	}

	public LinkParamType(LinkParam80211 type) {
		selector = new UnsignedInteger8(5);
		object = type;
	}

	public LinkParamType(LinkParamC2K type) {
		selector = new UnsignedInteger8(6);
		object = type;
	}

	public LinkParamType(LinkParamFdd type) {
		selector = new UnsignedInteger8(7);
		object = type;
	}

	public LinkParamType(LinkParamHrpd type) {
		selector = new UnsignedInteger8(8);
		object = type;
	}

	public LinkParamType(LinkParam80216 type) {
		selector = new UnsignedInteger8(9);
		object = type;
	}

	public LinkParamType(LinkParam80220 type) {
		selector = new UnsignedInteger8(10);
		object = type;
	}

	public LinkParamType(LinkParam80222 type) {
		selector = new UnsignedInteger8(11);
		object = type;
	}

	public LinkParamType(LinkParamType value) {
		this.selector = value.selector;
		this.object = value.object;
	}

	public LinkParamType() {
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

	public void toBytes(ByteArrayOutputStream stream) {
		selector.toBytes(stream);

		switch(selector.getValue()) {
		case 0:
			((LinkParamGen)object).toBytes(stream);
			break;

		case 1:
			((LinkParamQoS)object).toBytes(stream);
			break;

		case 2:
			((LinkParamGG)object).toBytes(stream);
			break;

		case 3:
			((LinkParamEdge)object).toBytes(stream);
			break;

		case 4:
			((LinkParamEth)object).toBytes(stream);
			break;

		case 5:
			((LinkParam80211)object).toBytes(stream);
			break;

		case 6:
			((LinkParamC2K)object).toBytes(stream);
			break;

		case 7:
			((LinkParamFdd)object).toBytes(stream);
			break;

		case 8:
			((LinkParamHrpd)object).toBytes(stream);
			break;

		case 9:
			((LinkParam80216)object).toBytes(stream);
			break;

		case 10:
			((LinkParam80220)object).toBytes(stream);
			break;

		case 11:
			((LinkParam80222)object).toBytes(stream);
			break;
		}
	}

	public void fromBytes(ByteArrayInputStream stream) {
		selector.fromBytes(stream);

		switch(selector.getValue()) {
		case 0:
			object = new LinkParamGen();
			((LinkParamGen)object).fromBytes(stream);
			break;

		case 1:
			object = new LinkParamQoS();
			((LinkParamQoS)object).fromBytes(stream);
			break;

		case 2:
			object = new LinkParamGG();
			((LinkParamGG)object).fromBytes(stream);
			break;

		case 3:
			object = new LinkParamEdge();
			((LinkParamEdge)object).fromBytes(stream);
			break;

		case 4:
			object = new LinkParamEth();
			((LinkParamEth)object).fromBytes(stream);
			break;

		case 5:
			object = new LinkParam80211();
			((LinkParam80211)object).fromBytes(stream);
			break;

		case 6:
			object = new LinkParamC2K();
			((LinkParamC2K)object).fromBytes(stream);
			break;

		case 7:
			object = new LinkParamFdd();
			((LinkParamFdd)object).fromBytes(stream);
			break;

		case 8:
			object = new LinkParamHrpd();
			((LinkParamHrpd)object).fromBytes(stream);
			break;

		case 9:
			object = new LinkParam80216();
			((LinkParam80216)object).fromBytes(stream);
			break;

		case 10:
			object = new LinkParam80220();
			((LinkParam80220)object).fromBytes(stream);
			break;

		case 11:
			object = new LinkParam80222();
			((LinkParam80222)object).fromBytes(stream);
			break;
		}
	}

	UnsignedInteger8 selector;
	Object object;
}