//==============================================================================
// Brief   : MAC_ADDR Data Type
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

public class MacAddr extends TransportAddress implements Serializeable {

	public MacAddr(OctetString address) {
		super(new UnsignedInteger16(6), new OctetString(""));
		setAddress(address);
	}

	public MacAddr(MacAddr address) {
		super(address);
	}

	public MacAddr() {
		super(new UnsignedInteger16(6), new OctetString(""));
	}

	public OctetString getAddress() {
		StringBuilder tmp = new StringBuilder();

		for(int i = 0; i < getB().getValue().toString().length(); ++i) {
			tmp.append(String.format("%02X", Integer.valueOf(getB().getValue().toString().charAt(i))));
			tmp.append(":");
		}
		tmp.deleteCharAt(tmp.length() - 1);

		return new OctetString(tmp.toString());
	}

	public void setAddress(OctetString address) {
		String[] substring = address.getValue().split(":");

		byte[] tmp = new byte[substring.length];

		for(int i = 0; i < substring.length; ++i) {
			tmp[i] = (byte) Integer.parseInt(substring[i], 16);
		}

		setB(new OctetString(new String(tmp)));
	}
}
