//==============================================================================
// Brief   : MBB_HO_SUPP Data Type
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
import mih.types.informationelements.NetworkType;
import mih.types.general.Boolean;

public class MbbHoSupp
		extends
		Sequence<NetworkType, NetworkType, Boolean, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public MbbHoSupp(NetworkType first, NetworkType second, Boolean mbb) {
		super(first, second, mbb);
	}

	public MbbHoSupp(MbbHoSupp value) {
		super(value.getFirstNetworkType(), value.getSecondNetworkType(), value.getMbbSupport());
	}

	public MbbHoSupp() {
		super(new NetworkType(), new NetworkType(), new Boolean());
	}

	public NetworkType getFirstNetworkType() {
		return getA();
	}

	public void setFirstNetworkType(NetworkType type) {
		setA(type);
	}

	public NetworkType getSecondNetworkType() {
		return getB();
	}

	public void setSecondNetworkType(NetworkType type) {
		setB(type);
	}

	public Boolean getMbbSupport() {
		return getC();
	}

	public void setMbbSupport(Boolean mbb) {
		setC(mbb);
	}
}
