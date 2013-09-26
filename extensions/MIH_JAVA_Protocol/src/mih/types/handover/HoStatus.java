//==============================================================================
// Brief   : HO_STATUS Data Type
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

package mih.types.handover;

import mih.types.Serializeable;
import mih.types.general.Enumerated;

public class HoStatus extends Enumerated<Number> implements Serializeable {

	public enum HoStatusEnum {
		 HandoverPermitted(0),
		 HandoverDeclined(1);

		 private HoStatusEnum(int id) {
			 this.id = id;
		 }

		 public final int id;
	}

	public HoStatus(HoStatusEnum value) {
		super(value.id);
	}

	public HoStatus(HoStatus value) {
		super(value);
	}

	public HoStatus() {
		super(0);
	}
}

