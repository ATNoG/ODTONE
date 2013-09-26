//==============================================================================
// Brief   : TRANSPORT_TYPE Data Type
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

package mih.types.mihnetsap;

import mih.types.Serializeable;
import mih.types.general.Enumerated;

public class TransportType extends Enumerated<Number> implements Serializeable {

	public enum TransportTypeEnum {
		 L2(0),
		 L3OrHigherLayerProtocols(1);

		 private TransportTypeEnum(int id) {
			 this.id = id;
		 }

		 public final int id;
	}

	public TransportType(TransportTypeEnum value) {
		super(value.id);
	}

	public TransportType(TransportType value) {
		super(value);
	}

	public TransportType() {
		super(0);
	}
}

