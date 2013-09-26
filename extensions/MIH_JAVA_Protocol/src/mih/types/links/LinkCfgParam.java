//==============================================================================
// Brief   : LINK_CFG_PARAM Data Type
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

public class LinkCfgParam
		extends
		Sequence<LinkParamType, Threshold, ConfigStatus, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public LinkCfgParam(LinkParamType linkParamType, Threshold threshold, ConfigStatus configStatus) {
		super(linkParamType, threshold, configStatus);
	}

	public LinkCfgParam(LinkCfgParam value) {
		super(value.getLinkParamType(), value.getThreshold(), value.getConfigStatus());
	}

	public LinkCfgParam() {
		super(new LinkParamType(), new Threshold(), new ConfigStatus());
	}

	public LinkParamType getLinkParamType() {
		return getA();
	}

	public void setLinkParamType(LinkParamType linkParamType) {
		setA(linkParamType);
	}

	public Threshold getThreshold() {
		return getB();
	}

	public void setThreshold(Threshold threshold) {
		setB(threshold);
	}

	public ConfigStatus getConfigStatus() {
		return getC();
	}

	public void setConfigStatus(ConfigStatus configStatus) {
		setC(configStatus);
	}
}
