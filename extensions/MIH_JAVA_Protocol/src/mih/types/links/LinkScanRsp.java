//==============================================================================
// Brief   : LINK_SCAN_RSP Data Type
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
import mih.types.address.LinkAddr;
import mih.types.basic.Sequence;
import mih.types.informationelements.NetworkId;

public class LinkScanRsp
		extends
		Sequence<LinkAddr, NetworkId, SigStrength, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public LinkScanRsp(LinkAddr linkAddr, NetworkId networkId, SigStrength sigStrength) {
		super(linkAddr, networkId, sigStrength);
	}

	public LinkScanRsp(LinkScanRsp value) {
		super(value.getLinkAddr(), value.getNetworkId(), value.getSigStrength());
	}

	public LinkScanRsp() {
		super(new LinkAddr(), new NetworkId(), new SigStrength());
	}

	public LinkAddr getLinkAddr() {
		return getA();
	}

	public void setLinkAddr(LinkAddr linkAddr) {
		setA(linkAddr);
	}

	public NetworkId getNetworkId() {
		return getB();
	}

	public void setNetworkId(NetworkId networkId) {
		setB(networkId);
	}

	public SigStrength getSigStrength() {
		return getC();
	}

	public void setSigStrength(SigStrength sigStrength) {
		setC(sigStrength);
	}
}
