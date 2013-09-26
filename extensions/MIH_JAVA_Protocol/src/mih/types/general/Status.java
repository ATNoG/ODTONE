//==============================================================================
// Brief   : STATUS Data Type
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

public class Status extends Enumerated<Number> implements Serializeable {

	public enum StatusEnum {
		 Success(0),
		 UnspecifiedFailure(1),
		 Rejected(2),
		 AuthorizationFailure(3),
		 NetworkError(4);

		 private StatusEnum(int id) {
			 this.id = id;
		 }

		 public final int id;
	}

	public Status(StatusEnum value) {
		super(value.id);
	}

	public Status(Status value) {
		super(value);
	}

	public Status() {
		super(0);
	}
}

