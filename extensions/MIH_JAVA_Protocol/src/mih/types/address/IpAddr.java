//==============================================================================
// Brief   : IP_ADDR Data Type
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

package mih.types.address;

import mih.types.Serializeable;
import mih.types.basic.OctetString;
import mih.types.basic.UnsignedInteger16;

public class IpAddr extends TransportAddress implements Serializeable {

	public enum IpAddrEnum {
		None(0),
		IPv4(1),
		IPv6(2);

		 private IpAddrEnum(int id) {
			 this.id = id;
		 }

		 public final int id;
	}


	public IpAddr(IpAddrEnum type, OctetString address) {
		super(new UnsignedInteger16(type.id), address);
	}

	public IpAddr(IpAddr address) {
		super(address);
	}

	public IpAddr() {
		super(new UnsignedInteger16(0), new OctetString(""));
	}
}
