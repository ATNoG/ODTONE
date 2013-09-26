//==============================================================================
// Brief   : LINK_STATUS_RSP Data Type
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

public class LinkStatusRsp
		extends
		Sequence<List<LinkStatesRsp>, List<LinkParam>, List<LinkDescRsp>, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public LinkStatusRsp(List<LinkStatesRsp> linkStatesRspList, List<LinkParam> linkParamList, List<LinkDescRsp> linkDescRspList) {
		super(linkStatesRspList, linkParamList, linkDescRspList);
	}

	public LinkStatusRsp(LinkStatusRsp value) {
		super(value.getLinkStatesRspList(), value.getLinkParamList(), value.getLinkDescRspList());
	}

	public LinkStatusRsp() {
		super(new List<LinkStatesRsp>(LinkStatesRsp.class), new List<LinkParam>(LinkParam.class), new List<LinkDescRsp>(LinkDescRsp.class));
	}

	public List<LinkStatesRsp> getLinkStatesRspList() {
		return getA();
	}

	public void setLinkStatesRspList(List<LinkStatesRsp> linkStatesRspList) {
		setA(linkStatesRspList);
	}

	public List<LinkParam> getLinkParamList() {
		return getB();
	}

	public void setLinkParamList(List<LinkParam> linkParamList) {
		setB(linkParamList);
	}

	public List<LinkDescRsp> getLinkDescRspList() {
		return getC();
	}

	public void setLinkDescRspList(List<LinkDescRsp> linkDescRspList) {
		setC(linkDescRspList);
	}
}
