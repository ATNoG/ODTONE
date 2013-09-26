//==============================================================================
// Brief   : IR_RDF_SCHM Data Type
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

public class IrRdfSchm
		extends
		Sequence<NullMimeTypeChoice, OctetString, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public IrRdfSchm(NullMimeTypeChoice mimeType, OctetString schema) {
		super(mimeType, schema);
	}

	public IrRdfSchm(IrRdfSchm value) {
		super(value.getMimeType(), value.getSchema());
	}

	public IrRdfSchm() {
		super(new NullMimeTypeChoice(), new OctetString());
	}

	public NullMimeTypeChoice getMimeType() {
		return getA();
	}

	public void setMimeType(NullMimeTypeChoice mimeType) {
		setA(mimeType);
	}

	public OctetString getSchema() {
		return getB();
	}

	public void setSchema(OctetString schema) {
		setB(schema);
	}
}
