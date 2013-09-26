//==============================================================================
// Brief   : BIN_GEO_LOC Data Type
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

package mih.types.location;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;

import mih.types.Serializeable;
import mih.types.basic.UnsignedInteger8;

public class BinGeoLoc implements Serializeable {

	public BinGeoLoc(int[] value) {
		this.value = new UnsignedInteger8[16];

		for(int i = 0; i < value.length; ++i)
			this.value[i] = new UnsignedInteger8(value[i]);
	}

	public BinGeoLoc(BinGeoLoc value) {
		this.value = value.value;
	}

	public BinGeoLoc() {
		this.value = new UnsignedInteger8[16];

		for(int i = 0; i < value.length; ++i)
			this.value[i] = new UnsignedInteger8(0);
	}

	public UnsignedInteger8[] getValue() {
		return value;
	}

	public void setValue(int[] value) {
		for(int i = 0; i < value.length; ++i)
			this.value[i] = new UnsignedInteger8(value[i]);
	}

	public void toBytes(ByteArrayOutputStream stream) {
		for(int i = value.length - 1; i >= 0; --i)
			value[i].toBytes(stream);
	}

	public void fromBytes(ByteArrayInputStream stream) {
		for(int i = value.length - 1; i >= 0; --i) {
			value[i] = new UnsignedInteger8(0);
			value[i].fromBytes(stream);
		}
	}

	private UnsignedInteger8[] value;
}