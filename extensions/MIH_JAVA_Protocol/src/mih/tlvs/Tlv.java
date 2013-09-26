//==============================================================================
// Brief   : Generic TLV
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

package mih.tlvs;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;

import mih.types.Serializeable;
import mih.types.basic.UnsignedInteger8;

public abstract class Tlv<T extends Serializeable> implements Serializeable {

	public Tlv(UnsignedInteger8 tag) {
		this.tag = tag;
		hasValue = false;
	}

	public Tlv(UnsignedInteger8 tag, T value) {
		this.tag = tag;
		this.value = value;
		this.hasValue = true;
	}

	public UnsignedInteger8 getTag() {
		return tag;
	}

	public void setTag(UnsignedInteger8 tag) {
		this.tag = tag;
	}

	public UnsignedInteger8 getLength() {
		return length;
	}

	public void setLength(UnsignedInteger8 length) {
		this.length = length;
	}

	public T getValue() {
		if(hasValue)
			return value;
		else
			return null;
	}

	public void setValue(T value) {
		this.value = value;
		this.hasValue = true;
	}

	public boolean isInitialized() {
		return hasValue;
	}

	public void toBytes(ByteArrayOutputStream stream) throws Exception {
		if(hasValue) {
			ByteArrayOutputStream tmp = new ByteArrayOutputStream();
			value.toBytes(tmp);
			length.setValue(tmp.size());

			tag.toBytes(stream);
			length.toBytes(stream);
			value.toBytes(stream);
		}
	}

	public void fromBytes(ByteArrayInputStream stream) throws Exception {
		stream.mark(0);
		int tagRead = stream.read();
		stream.reset();

		if(tag.getValue() == tagRead) {
			tag.fromBytes(stream);
			length.fromBytes(stream);
			value.fromBytes(stream);
			hasValue = true;
		}
	}

	boolean hasValue;
	UnsignedInteger8 tag;
	UnsignedInteger8 length = new UnsignedInteger8(-1);
	T value;
}
