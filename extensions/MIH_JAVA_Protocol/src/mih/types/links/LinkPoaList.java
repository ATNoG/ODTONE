//==============================================================================
// Brief   : LINK_POA_LIST Data Type
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
import mih.types.basic.List;
import mih.types.basic.Sequence;
import mih.types.address.LinkAddr;

public class LinkPoaList
		extends
		Sequence<LinkId, List<LinkAddr>, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public LinkPoaList(LinkId id, List<LinkAddr> addrList) {
		super(id, addrList);
	}

	public LinkPoaList(LinkPoaList value) {
		super(value.getId(), value.getAddrList());
	}

	public LinkPoaList() {
		super(new LinkId(), new List<LinkAddr>(LinkAddr.class));
	}

	public LinkId getId() {
		return getA();
	}

	public void setId(LinkId id) {
		setA(id);
	}

	public List<LinkAddr> getAddrList() {
		return getB();
	}

	public void setAddrList(List<LinkAddr> addrList) {
		setB(addrList);
	}
}
