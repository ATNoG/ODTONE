//==============================================================================
// Brief   : HO_RESULT Data Type
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

public class HoResult extends Enumerated<Number> implements Serializeable {

	public enum HoResultEnum {
		 Success(0),
		 Failure(1),
		 Rejected(2);

		 private HoResultEnum(int id) {
			 this.id = id;
		 }

		 public final int id;
	}

	public HoResult(HoResultEnum value) {
		super(value.id);
	}

	public HoResult(HoResult value) {
		super(value);
	}

	public HoResult() {
		super(0);
	}
}

