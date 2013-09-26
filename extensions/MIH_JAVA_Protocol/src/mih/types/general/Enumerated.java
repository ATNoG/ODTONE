//==============================================================================
// Brief   : ENUMERATED Data Type
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

package mih.types.general;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;

import mih.types.Serializeable;

public class Enumerated<T extends Number> implements Serializeable {

	public Enumerated(T value) {
		this.value = (Integer) value & 0xff;
	}

	public Enumerated(Enumerated<T> value) {
		this.value = value.value;
	}

	public Enumerated() {
		this.value = 0;
	}

	public int getValue() {
		return value;
	}

	public void setValue(int value) {
		this.value = value & 0xff;
	}

	public void toBytes(ByteArrayOutputStream stream) {
		stream.write( value       & 0xff);
	}

	public void fromBytes(ByteArrayInputStream stream) {
		value = 0;
		value |= stream.read();
	}

	private int value;
}