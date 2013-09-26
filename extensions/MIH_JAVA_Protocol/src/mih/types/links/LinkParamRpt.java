//==============================================================================
// Brief   : LINK_PARAM_RPT Data Type
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
import mih.types.links.auxiliar.NullThresholdChoice;

public class LinkParamRpt
		extends
		Sequence<LinkParam, NullThresholdChoice, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public LinkParamRpt(LinkParam linkParam, NullThresholdChoice threshold) {
		super(linkParam, threshold);
	}

	public LinkParamRpt(LinkParamRpt value) {
		super(value.getLinkParam(), value.getThreshold());
	}

	public LinkParamRpt() {
		super(new LinkParam(), new NullThresholdChoice());
	}

	public LinkParam getLinkParam() {
		return getA();
	}

	public void setLinkParam(LinkParam linkParam) {
		setA(linkParam);
	}

	public NullThresholdChoice getThreshold() {
		return getB();
	}

	public void setThreshold(NullThresholdChoice threshold) {
		setB(threshold);
	}
}
