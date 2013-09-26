//==============================================================================
// Brief   : NET_CAPS Data Type
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

package mih.types.informationelements;

import mih.types.Serializeable;
import mih.types.basic.Bitmap;

public class NetCaps extends Bitmap implements Serializeable {

	public enum NetCapsEnum {
		 Security(0),
		 QoSClass0(1),
		 QoSClass1(2),
		 QoSClass2(3),
		 QoSClass3(4),
		 QoSClass4(5),
		 QoSClass5(6),
		 InternetAccess(7),
		 EmergencyServices(8),
		 MihCapability(9);

		 private NetCapsEnum(int id) {
			 this.id = id;
		 }

		 public final int id;
	}

	public NetCaps(NetCaps value) {
		super(value);
	}

	public NetCaps() {
		super(32);
	}
}