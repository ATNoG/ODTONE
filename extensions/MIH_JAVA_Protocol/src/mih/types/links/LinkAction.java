//==============================================================================
// Brief   : LINK_ACTION Data Type
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
import mih.types.basic.Sequence;

public class LinkAction
		extends
		Sequence<LinkAcType, LinkAcAttr, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public LinkAction(LinkAcType type, LinkAcAttr attr) {
		super(type, attr);
	}

	public LinkAction(LinkAction value) {
		super(value.getType(), value.getAttr());
	}

	public LinkAction() {
		super(new LinkAcType(), new LinkAcAttr());
	}

	public LinkAcType getType() {
		return getA();
	}

	public void setType(LinkAcType type) {
		setA(type);
	}

	public LinkAcAttr getAttr() {
		return getB();
	}

	public void setAttr(LinkAcAttr attr) {
		setB(attr);
	}
}
