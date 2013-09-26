//==============================================================================
// Brief   : LINK_CFG_STATUS Data Type
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
import mih.types.links.auxiliar.NullTimerIntervalChoice;

public class LinkCfgStatus
		extends
		Sequence<LinkParamType, NullTimerIntervalChoice, ThAction, List<Threshold>, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public LinkCfgStatus(LinkParamType linkParamType, NullTimerIntervalChoice timerInterval, ThAction thAction, List<Threshold> thresholdList) {
		super(linkParamType, timerInterval, thAction, thresholdList);
	}

	public LinkCfgStatus(LinkCfgStatus value) {
		super(value.getLinkParamType(), value.getTimerInterval(), value.getThAction(), value.getThresholdList());
	}

	public LinkCfgStatus() {
		super(new LinkParamType(), new NullTimerIntervalChoice(), new ThAction(), new List<Threshold>(Threshold.class));
	}

	public LinkParamType getLinkParamType() {
		return getA();
	}

	public void setLinkParamType(LinkParamType linkParamType) {
		setA(linkParamType);
	}

	public NullTimerIntervalChoice getTimerInterval() {
		return getB();
	}

	public void setTimerInterval(NullTimerIntervalChoice timerInterval) {
		setB(timerInterval);
	}

	public ThAction getThAction() {
		return getC();
	}

	public void setThAction(ThAction thAction) {
		setC(thAction);
	}

	public List<Threshold> getThresholdList() {
		return getD();
	}

	public void setThresholdList(List<Threshold> thresholdList) {
		setD(thresholdList);
	}
}
