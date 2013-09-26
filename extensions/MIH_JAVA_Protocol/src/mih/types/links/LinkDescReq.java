//==============================================================================
// Brief   : LINK_DESC_REQ Data Type
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

public class LinkDescReq extends Bitmap implements Serializeable {

	public enum LinkDescReqEnum {
		 NumberOfClassesOfServicesSupported(0),
		 NumberOfQueuesSupported(1);

		 private LinkDescReqEnum(int id) {
			 this.id = id;
		 }

		 public final int id;
	}

	public LinkDescReq(LinkDescReq value) {
		super(value);
	}

	public LinkDescReq() {
		super(16);
	}
}