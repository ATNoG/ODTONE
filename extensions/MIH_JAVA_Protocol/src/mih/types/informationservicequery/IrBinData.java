//==============================================================================
// Brief   : IR_BIN_DATA Data Type
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
import mih.types.basic.InfoElement;
import mih.types.basic.List;

public class IrBinData extends List<InfoElement> implements Serializeable {

	public IrBinData() {
		super(InfoElement.class);
	}

	public IrBinData(IrBinData value) {
		super(value);
	}
}
