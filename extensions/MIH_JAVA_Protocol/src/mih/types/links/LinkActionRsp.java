//==============================================================================
// Brief   : LINK_ACTION_RSP Data Type
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
import mih.types.links.auxiliar.NullListLinkScanRspChoice;

public class LinkActionRsp
		extends
		Sequence<LinkId, LinkAcResult, NullListLinkScanRspChoice, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public LinkActionRsp(LinkId linkId, LinkAcResult linkAcResult, NullListLinkScanRspChoice linkScanRsp) {
		super(linkId, linkAcResult, linkScanRsp);
	}

	public LinkActionRsp(LinkActionRsp value) {
		super(value.getLinkId(), value.getLinkAcResult(), value.getLinkScanRsp());
	}

	public LinkActionRsp() {
		super(new LinkId(), new LinkAcResult(), new NullListLinkScanRspChoice());
	}

	public LinkId getLinkId() {
		return getA();
	}

	public void setLinkId(LinkId linkId) {
		setA(linkId);
	}

	public LinkAcResult getLinkAcResult() {
		return getB();
	}

	public void setLinkAcResult(LinkAcResult linkAcResult) {
		setB(linkAcResult);
	}

	public NullListLinkScanRspChoice getLinkScanRsp() {
		return getC();
	}

	public void setLinkScanRsp(NullListLinkScanRspChoice linkScanRsp) {
		setC(linkScanRsp);
	}
}
