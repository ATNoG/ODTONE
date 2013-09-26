//==============================================================================
// Brief   : IP_SUBNET_INFO Data Type
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

package mih.types.ipconfiguration;

import mih.types.Serializeable;
import mih.types.address.IpAddr;
import mih.types.basic.Sequence;

public class IpSubnetInfo
		extends
		Sequence<IpPrefixLen, IpAddr, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public IpSubnetInfo(IpPrefixLen length, IpAddr addr) {
		super(length, addr);
	}

	public IpSubnetInfo(IpSubnetInfo value) {
		super(value.getLength(), value.getAddr());
	}

	public IpSubnetInfo() {
		super(new IpPrefixLen(), new IpAddr());
	}

	public IpPrefixLen getLength() {
		return getA();
	}

	public void setLength(IpPrefixLen length) {
		setA(length);
	}

	public IpAddr getAddr() {
		return getB();
	}

	public void setAddr(IpAddr attr) {
		setB(attr);
	}
}
