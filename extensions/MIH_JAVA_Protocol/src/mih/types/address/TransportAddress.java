//==============================================================================
// Brief   : TRANSPORT_ADDRESS Data Type
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
import mih.types.basic.Sequence;
import mih.types.basic.UnsignedInteger16;

public class TransportAddress
		extends
		Sequence<UnsignedInteger16, OctetString, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public TransportAddress(UnsignedInteger16 type, OctetString address) {
		super(type, address);
	}

	public TransportAddress(TransportAddress value) {
		super(value.getType(), value.getAddress());
	}

	public TransportAddress() {
		super(new UnsignedInteger16(), new OctetString());
	}

	public UnsignedInteger16 getType() {
		return getA();
	}

	public void setType(UnsignedInteger16 type) {
		setA(type);
	}

	public OctetString getAddress() {
		return getB();
	}

	public void setAddress(OctetString address) {
		setB(address);
	}
}
