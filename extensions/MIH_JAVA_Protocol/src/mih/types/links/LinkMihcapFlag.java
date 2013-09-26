//==============================================================================
// Brief   : LINK_MIHCAP_FLAG Data Type
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

public class LinkMihcapFlag extends Bitmap implements Serializeable {

	public enum LinkMihcapFlagEnum {
		 EventServiceSupported(1),
		 CommandServiceSupported(2),
		 InformationServiceSupported(3);

		 private LinkMihcapFlagEnum(int id) {
			 this.id = id;
		 }

		 public final int id;
	}

	public LinkMihcapFlag(LinkMihcapFlag value) {
		super(value);
	}

	public LinkMihcapFlag() {
		super(8);
	}
}