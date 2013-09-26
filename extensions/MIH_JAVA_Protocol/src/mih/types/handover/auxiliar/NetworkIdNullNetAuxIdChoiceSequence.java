//==============================================================================
// Brief   : SEQUENCE(NETWORK_ID, CHOICE(NULL, NET_AUX_ID)) Data Type
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

package mih.types.handover.auxiliar;

import mih.types.Serializeable;
import mih.types.basic.Sequence;
import mih.types.informationelements.NetworkId;

public class NetworkIdNullNetAuxIdChoiceSequence
		extends
		Sequence<NetworkId, NullNetAuxIdChoice, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public NetworkIdNullNetAuxIdChoiceSequence(NetworkId networkId, NullNetAuxIdChoice netAuxId) {
		super(networkId, netAuxId);
	}

	public NetworkIdNullNetAuxIdChoiceSequence(NetworkIdNullNetAuxIdChoiceSequence value) {
		super(value.getNetworkId(), value.getNetAuxId());
	}

	public NetworkIdNullNetAuxIdChoiceSequence() {
		super(new NetworkId(), new NullNetAuxIdChoice());
	}

	public NetworkId getNetworkId() {
		return getA();
	}

	public void setNetworkId(NetworkId networkId) {
		setA(networkId);
	}

	public NullNetAuxIdChoice getNetAuxId() {
		return getB();
	}

	public void setNetAuxId(NullNetAuxIdChoice netAuxId) {
		setB(netAuxId);
	}
}
