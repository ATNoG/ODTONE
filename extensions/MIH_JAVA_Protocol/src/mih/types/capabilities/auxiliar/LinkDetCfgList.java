//==============================================================================
// Brief   : LIST(LINK_DET_CFG) Data Type
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

package mih.types.capabilities.auxiliar;

import mih.types.Serializeable;
import mih.types.basic.List;
import mih.types.capabilities.LinkDetCfg;

public class LinkDetCfgList extends List<LinkDetCfg> implements Serializeable {

	public LinkDetCfgList() {
		super(LinkDetCfg.class);
	}

	public LinkDetCfgList(LinkDetCfgList value) {
		super(value);
	}
}