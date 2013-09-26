//==============================================================================
// Brief   : LINK_DET_CFG Data Type
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

package mih.types.capabilities;

import mih.types.Serializeable;
import mih.types.basic.Sequence;
import mih.types.capabilities.auxiliar.NullLinkDataRateChoice;
import mih.types.capabilities.auxiliar.NullNetworkIdChoice;
import mih.types.capabilities.auxiliar.NullSigStrengthChoice;

public class LinkDetCfg
		extends
		Sequence<NullNetworkIdChoice, NullSigStrengthChoice, NullLinkDataRateChoice, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public LinkDetCfg(NullNetworkIdChoice networkId, NullSigStrengthChoice sigStrength, NullLinkDataRateChoice linkDataRate) {
		super(networkId, sigStrength, linkDataRate);
	}

	public LinkDetCfg(LinkDetCfg value) {
		super(value.getNetworkId(), value.getSigStrength(), value.getLinkDataRate());
	}

	public LinkDetCfg() {
		super(new NullNetworkIdChoice(), new NullSigStrengthChoice(), new NullLinkDataRateChoice());
	}

	public NullNetworkIdChoice getNetworkId() {
		return getA();
	}

	public void setNetworkId(NullNetworkIdChoice networkType) {
		setA(networkType);
	}

	public NullSigStrengthChoice getSigStrength() {
		return getB();
	}

	public void setSigStrength(NullSigStrengthChoice sigStrength) {
		setB(sigStrength);
	}

	public NullLinkDataRateChoice getLinkDataRate() {
		return getC();
	}

	public void setLinkDataRate(NullLinkDataRateChoice linkDataRate) {
		setC(linkDataRate);
	}
}
