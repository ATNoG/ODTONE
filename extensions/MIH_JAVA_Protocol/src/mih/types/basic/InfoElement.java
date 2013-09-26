//==============================================================================
// Brief   : INFO_ELEMENT Data Type
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

public class InfoElement<T extends Serializeable> implements Serializeable {

	public InfoElement(UnsignedInteger32 tag) {
		this.tag = tag;
		hasValue = false;
	}

	public InfoElement(UnsignedInteger32 tag, T value) {
		this.tag = tag;
		this.value = value;
		this.hasValue = true;
	}

	public UnsignedInteger32 getTag() {
		return tag;
	}

	public void setTag(UnsignedInteger32 tag) {
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
	UnsignedInteger32 tag;
	UnsignedInteger8 length = new UnsignedInteger8(-1);
	T value;
}