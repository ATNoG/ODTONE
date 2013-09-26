//==============================================================================
// Brief   : NET_TYPE_INC Data Type
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

package mih.types.informationservicequery;

import mih.types.Serializeable;
import mih.types.basic.Bitmap;

public class NetTypeInc extends Bitmap implements Serializeable {

	public enum NetTypeIncEnum {
		 Wireless_GSM(0),
		 Wireless_GPRS(1),
		 Wireless_EDGE(2),
		 IEEE8023(3),
		 Wireless_Other(4),
		 Wireless_IEEE80211(5),
		 Wireless_CDMA2000(6),
		 Wireless_UMTS(7),
		 Wireless_CDMA2000_HRPD(8),
		 Wireless_IEEE80216(9),
		 Wireless_IEEE80220(10),
		 Wireless_IEEE80222(11);

		 private NetTypeIncEnum(int id) {
			 this.id = id;
		 }

		 public final int id;
	}

	public NetTypeInc(NetTypeInc value) {
		super(value);
	}

	public NetTypeInc() {
		super(64);
	}
}