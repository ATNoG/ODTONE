//==============================================================================
// Brief   : TH_ACTION Data Type
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
import mih.types.general.Enumerated;

public class ThAction extends Enumerated<Number> implements Serializeable {

	public enum ThActionEnum {
		 SetNormalThreshold(0),
		 SetOneShotThreshold(1),
		 CancelThreshold(2);

		 private ThActionEnum(int id) {
			 this.id = id;
		 }

		 public final int id;
	}

	public ThAction(ThActionEnum value) {
		super(value.id);
	}

	public ThAction(ThAction value) {
		super(value);
	}

	public ThAction() {
		super(0);
	}
}

