//==============================================================================
// Brief   : LINK_ACTION_REQ Data Type
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

public class LinkActionReq
		extends
		Sequence<LinkId, NullLinkAddrChoice, LinkAction, LinkAcExTime, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public LinkActionReq(LinkId linkId, NullLinkAddrChoice linkAddr, LinkAction linkAction, LinkAcExTime linkAcExTime) {
		super(linkId, linkAddr, linkAction, linkAcExTime);
	}

	public LinkActionReq(LinkActionReq value) {
		super(value.getLinkId(), value.getLinkAddr(), value.getLinkAction(), value.getLinkAcExTime());
	}

	public LinkActionReq() {
		super(new LinkId(), new NullLinkAddrChoice(), new LinkAction(), new LinkAcExTime());
	}

	public LinkId getLinkId() {
		return getA();
	}

	public void setLinkId(LinkId linkId) {
		setA(linkId);
	}

	public NullLinkAddrChoice getLinkAddr() {
		return getB();
	}

	public void setLinkAddr(NullLinkAddrChoice linkAddr) {
		setB(linkAddr);
	}

	public LinkAction getLinkAction() {
		return getC();
	}

	public void setLinkAction(LinkAction linkAction) {
		setC(linkAction);
	}

	public LinkAcExTime getLinkAcExTime() {
		return getD();
	}

	public void setLinkAcExTime(LinkAcExTime linkAcExTime) {
		setD(linkAcExTime);
	}
}
