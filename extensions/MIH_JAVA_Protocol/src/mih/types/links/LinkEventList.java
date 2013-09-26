//==============================================================================
// Brief   : LINK_EVENT_LIST Data Type
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

public class LinkEventList extends Bitmap implements Serializeable {

	public enum LinkEventListEnum {
		 LinkDetected(0),
		 LinkUp(1),
		 LinkDown(2),
		 LinkParameterReport(3),
		 LinkGoingDown(4),
		 LinkHandoverImminent(5),
		 LinkHandoverComplete(6),
		 LinkPduTransmitStatus(7);

		 private LinkEventListEnum(int id) {
			 this.id = id;
		 }

		 public final int id;
	}

	public LinkEventList(LinkEventList value) {
		super(value);
	}

	public LinkEventList() {
		super(32);
	}
}