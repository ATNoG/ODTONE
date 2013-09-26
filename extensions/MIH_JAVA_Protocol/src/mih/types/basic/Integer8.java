//==============================================================================
// Brief   : INTEGER(1) Data Type
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

package mih.types.basic;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;

import mih.types.Serializeable;

public class Integer8  implements Serializeable {

	public Integer8(int value) {
		this.value = (byte) (value & 0xff);
	}

	public Integer8(Integer8 value) {
		this.value = value.value;
	}

	public Integer8() {
		this.value = 0;
	}

	public int getValue() {
		return value;
	}

	public void setValue(int value) {
		this.value = (byte) (value & 0xff);
	}

	public void toBytes(ByteArrayOutputStream stream) {
		stream.write( value       & 0xff);
	}

	public void fromBytes(ByteArrayInputStream stream) {
		value = 0;
		value |= stream.read();
	}

	private byte value;
}