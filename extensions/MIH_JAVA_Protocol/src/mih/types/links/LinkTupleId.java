//==============================================================================
// Brief   : LINK_TUPLE_ID Data Type
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
import mih.types.links.auxiliar.NullLinkAddrChoice;

public class LinkTupleId
		extends
		Sequence<LinkId, NullLinkAddrChoice, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public LinkTupleId(LinkId id, NullLinkAddrChoice addr) {
		super(id, addr);
	}

	public LinkTupleId(LinkTupleId value) {
		super(value.getId(), value.getAddr());
	}

	public LinkTupleId() {
		super(new LinkId(), new NullLinkAddrChoice());
	}

	public LinkId getId() {
		return getA();
	}

	public void setId(LinkId id) {
		setA(id);
	}

	public NullLinkAddrChoice getAddr() {
		return getB();
	}

	public void setAddr(NullLinkAddrChoice addr) {
		setB(addr);
	}
}
