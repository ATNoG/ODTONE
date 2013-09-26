//==============================================================================
// Brief   : NET_TYPE_ADDR Data Type
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
import mih.types.address.LinkAddr;
import mih.types.basic.Sequence;
import mih.types.informationelements.NetworkType;

public class NetTypeAddr
		extends
		Sequence<NetworkType, LinkAddr, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public NetTypeAddr(NetworkType type, LinkAddr addr) {
		super(type, addr);
	}

	public NetTypeAddr(NetTypeAddr value) {
		super(value.getNetworkType(), value.getAddr());
	}

	public NetTypeAddr() {
		super(new NetworkType(), new LinkAddr());
	}

	public NetworkType getNetworkType() {
		return getA();
	}

	public void setNetworkType(NetworkType type) {
		setA(type);
	}

	public LinkAddr getAddr() {
		return getB();
	}

	public void setAddr(LinkAddr addr) {
		setB(addr);
	}
}
