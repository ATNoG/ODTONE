//==============================================================================
// Brief   : OCTET_STRING Data Type
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

public class OctetString implements Serializeable {

	public OctetString() {
		octet = "";
	}

	public OctetString(String octet) {
		this.octet = octet;
	}

	public OctetString(OctetString octet) {
		this.octet = octet.octet;
	}

	public String getValue() {
		return octet;
	}

	public void setValue(String octet) {
		this.octet = octet;
	}

	public void toBytes(ByteArrayOutputStream stream) {
		stream.write(octet.length());

		for (int i = 0; i < octet.length(); ++i) {
			stream.write(octet.charAt(i));
		}
	}

	public void fromBytes(ByteArrayInputStream stream) {
		int size = stream.read();

		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < size; ++i) {
			sb.append((char)stream.read());
		}

		octet = sb.toString();
	}

	private String octet;

}