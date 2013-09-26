//==============================================================================
// Brief   : IQ_RDF_DATA Data Type
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

package mih.types.informationservicequery;

import mih.types.Serializeable;
import mih.types.basic.OctetString;
import mih.types.basic.Sequence;
import mih.types.informationservicequery.auxiliar.NullMimeTypeChoice;

public class IqRdfData
		extends
		Sequence<NullMimeTypeChoice, OctetString, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public IqRdfData(NullMimeTypeChoice mimeType, OctetString data) {
		super(mimeType, data);
	}

	public IqRdfData(IqRdfData value) {
		super(value.getMimeType(), value.getData());
	}

	public IqRdfData() {
		super(new NullMimeTypeChoice(), new OctetString());
	}

	public NullMimeTypeChoice getMimeType() {
		return getA();
	}

	public void setMimeType(NullMimeTypeChoice mimeType) {
		setA(mimeType);
	}

	public OctetString getData() {
		return getB();
	}

	public void setData(OctetString data) {
		setB(data);
	}
}
