//==============================================================================
// Brief   : LINK_CMD_LIST Data Type
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

package mih.types.links;

import mih.types.Serializeable;
import mih.types.basic.Bitmap;

public class LinkCmdList extends Bitmap implements Serializeable {

	public enum LinkCmdListEnum {
		 Reserved(0),
		 LinkEventSubscribe(1),
		 LinkEventUnsubscribe(2),
		 LinkGetParameters(3),
		 LinkConfigureThresholds(4),
		 LinkAction(5);

		 private LinkCmdListEnum(int id) {
			 this.id = id;
		 }

		 public final int id;
	}

	public LinkCmdList(LinkCmdList value) {
		super(value);
	}

	public LinkCmdList() {
		super(32);
	}
}