//==============================================================================
// Brief   : LINK_ID Data Type
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

import mih.types.Serializeable;
import mih.types.address.LinkAddr;
import mih.types.basic.Sequence;

public class LinkId
		extends
		Sequence<LinkType, LinkAddr, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public LinkId(LinkType type, LinkAddr addr) {
		super(type, addr);
	}

	public LinkId(LinkId value) {
		super(value.getType(), value.getAddr());
	}

	public LinkId() {
		super(new LinkType(), new LinkAddr());
	}

	public LinkType getType() {
		return getA();
	}

	public void setType(LinkType type) {
		setA(type);
	}

	public LinkAddr getAddr() {
		return getB();
	}

	public void setAddr(LinkAddr addr) {
		setB(addr);
	}
}
