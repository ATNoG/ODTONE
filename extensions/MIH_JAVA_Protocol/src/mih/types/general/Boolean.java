//==============================================================================
// Brief   : BOOLEAN Data Type
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

package mih.types.general;

import mih.types.Serializeable;

public class Boolean extends Enumerated<Number> implements Serializeable {

	public enum BooleanEnum {
		 False(0),
		 True(1);

		 private BooleanEnum(int id) {
			 this.id = id;
		 }

		 public final int id;
	}

	public Boolean(BooleanEnum value) {
		super(value.id);
	}

	public Boolean(Boolean value) {
		super(value);
	}

	public Boolean() {
		super(0);
	}
}

