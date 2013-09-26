//==============================================================================
// Brief   : LINK_STATUS_REQ Data Type
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

public class LinkStatusReq
		extends
		Sequence<LinkStatesReq, List<LinkParamType>, LinkDescReq, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public LinkStatusReq(LinkStatesReq linkStatesReq, List<LinkParamType> linkParamTypeList, LinkDescReq linkDescReq) {
		super(linkStatesReq, linkParamTypeList, linkDescReq);
	}

	public LinkStatusReq(LinkStatusReq value) {
		super(value.getLinkStatesReq(), value.getLinkParamTypeList(), value.getLinkDescReq());
	}

	public LinkStatusReq() {
		super(new LinkStatesReq(), new List<LinkParamType>(LinkParamType.class), new LinkDescReq());
	}

	public LinkStatesReq getLinkStatesReq() {
		return getA();
	}

	public void setLinkStatesReq(LinkStatesReq linkStatesReq) {
		setA(linkStatesReq);
	}

	public List<LinkParamType> getLinkParamTypeList() {
		return getB();
	}

	public void setLinkParamTypeList(List<LinkParamType> linkParamTypeList) {
		setB(linkParamTypeList);
	}

	public LinkDescReq getLinkDescReq() {
		return getC();
	}

	public void setLinkDescReq(LinkDescReq linkDescReq) {
		setC(linkDescReq);
	}
}
