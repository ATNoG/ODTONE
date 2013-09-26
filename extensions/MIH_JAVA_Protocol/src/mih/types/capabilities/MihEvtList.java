//==============================================================================
// Brief   : MIH_EVT_LIST Data Type
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

package mih.types.capabilities;

import mih.types.Serializeable;
import mih.types.basic.Bitmap;

public class MihEvtList extends Bitmap implements Serializeable {

	public enum MihEvtListEnum {
		 MihLinkDetected(0),
		 MihLinkUp(1),
		 MihLinkDown(2),
		 MihLinkParameterReport(3),
		 MihLinkGoingDown(4),
		 MihLinkHandoverImminent(5),
		 MihLinkHandoverComplete(6),
		 MihLinkPduTransmitStatus(7);


		 private MihEvtListEnum(int id) {
			 this.id = id;
		 }

		 public final int id;
	}

	public MihEvtList(MihEvtListEnum value) {
		super(32);
		set(value.id);
	}

	public MihEvtList(MihEvtList value) {
		super(value);
	}

	public MihEvtList() {
		super(32);
	}
}