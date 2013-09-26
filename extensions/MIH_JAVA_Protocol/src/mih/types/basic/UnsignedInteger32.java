//==============================================================================
// Brief   : UNSIGNED_INT(4) Data Type
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

public class UnsignedInteger32 implements Serializeable {

	public UnsignedInteger32(long value) {
		this.value = value & 0xffffffff;
	}

	public UnsignedInteger32(UnsignedInteger32 value) {
		this.value = value.value;
	}

	public UnsignedInteger32() {
		this.value = 0;
	}

	public long getValue() {
		return value;
	}

	public void setValue(long value) {
		this.value = value & 0xffffffff;
	}

	public void toBytes(ByteArrayOutputStream stream) {
		stream.write((int) ((value >> 24) & 0xff));
		stream.write((int) ((value >> 16) & 0xff));
		stream.write((int) ((value >> 8) & 0xff));
		stream.write((int)  (value       & 0xff));
	}

	public void fromBytes(ByteArrayInputStream stream) {
		value = 0;
		value |= stream.read() << 24;
		value |= stream.read() << 16;
		value |= stream.read() << 8;
		value |= stream.read();
	}

	private long value;
}