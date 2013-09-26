//==============================================================================
// Brief   : Info Response RDF Schema URL List TLV
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

import mih.types.basic.List;
import mih.types.basic.UnsignedInteger8;
import mih.types.informationservicequery.IrSchmUrl;

public class InfoResponseRdfSchemaUrlListTlv extends Tlv<List<IrSchmUrl> > {

	public InfoResponseRdfSchemaUrlListTlv() {
		super(new UnsignedInteger8(50));
		value = new List<IrSchmUrl>(IrSchmUrl.class);
	}

	public InfoResponseRdfSchemaUrlListTlv(List<IrSchmUrl> value) {
		super(new UnsignedInteger8(50), value);
	}
}
