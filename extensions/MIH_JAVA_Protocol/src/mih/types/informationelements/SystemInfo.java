//==============================================================================
// Brief   : SYSTEM_INFO Data Type
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

package mih.types.informationelements;

import mih.types.Serializeable;
import mih.types.address.LinkAddr;
import mih.types.basic.Sequence;
import mih.types.informationelements.auxiliar.NullParametersChoice;

public class SystemInfo
		extends
		Sequence<NetworkType, LinkAddr, NullParametersChoice, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public SystemInfo(NetworkType networkType, LinkAddr linkAddr, NullParametersChoice parameters) {
		super(networkType, linkAddr, parameters);
	}

	public SystemInfo(SystemInfo value) {
		super(value.getNetworkType(), value.getLinkAddr(), value.getParameters());
	}

	public SystemInfo() {
		super(new NetworkType(), new LinkAddr(), new NullParametersChoice());
	}

	public NetworkType getNetworkType() {
		return getA();
	}

	public void setNetworkType(NetworkType networkType) {
		setA(networkType);
	}

	public LinkAddr getLinkAddr() {
		return getB();
	}

	public void setLinkAddr(LinkAddr linkAddr) {
		setB(linkAddr);
	}

	public NullParametersChoice getParameters() {
		return getC();
	}

	public void setParameters(NullParametersChoice parameters) {
		setC(parameters);
	}
}
