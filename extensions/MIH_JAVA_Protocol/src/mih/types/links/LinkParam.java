//==============================================================================
// Brief   : LINK_PARAM Data Type
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
import mih.types.links.auxiliar.LinkParamValQosParamValChoice;

public class LinkParam
		extends
		Sequence<LinkParamType, LinkParamValQosParamValChoice, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public LinkParam(LinkParamType type, LinkParamValQosParamValChoice value) {
		super(type, value);
	}

	public LinkParam(LinkParam value) {
		super(value.getType(), value.getValue());
	}

	public LinkParam() {
		super(new LinkParamType(), new LinkParamValQosParamValChoice());
	}

	public LinkParamType getType() {
		return getA();
	}

	public void setType(LinkParamType type) {
		setA(type);
	}

	public LinkParamValQosParamValChoice getValue() {
		return getB();
	}

	public void setAddr(LinkParamValQosParamValChoice value) {
		setB(value);
	}
}
