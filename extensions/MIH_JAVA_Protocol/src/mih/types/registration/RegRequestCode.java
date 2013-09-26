//==============================================================================
// Brief   : REG_REQUEST_CODE Data Type
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

package mih.types.registration;

import mih.types.Serializeable;
import mih.types.general.Enumerated;

public class RegRequestCode extends Enumerated<Number> implements Serializeable {

	public enum RegRequestCodeEnum {
		 Registration(0),
		 ReRegistration(1);

		 private RegRequestCodeEnum(int id) {
			 this.id = id;
		 }

		 public final int id;
	}

	public RegRequestCode(RegRequestCodeEnum value) {
		super(value.id);
	}

	public RegRequestCode(RegRequestCode value) {
		super(value);
	}

	public RegRequestCode() {
		super(0);
	}
}