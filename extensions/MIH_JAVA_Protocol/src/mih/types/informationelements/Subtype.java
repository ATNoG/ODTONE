//==============================================================================
// Brief   : SUBTYPE Data Type
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

public class Subtype extends Bitmap implements Serializeable {

	public enum SubtypeEnum {
		 EthernetIEEE8023_10Mb(0),
		 EthernetIEEE8023_100Mb(1),
		 EthernetIEEE8023_1000Mb(2),
		 WirelessIEEE80211_2_4GHz(0),
		 WirelessIEEE80211_5GHz(1),
		 WirelessIEEE80211_4_9GHz(2),
		 WirelessIEEE80211_3_65GHz(3),
		 WirelessIEEE80211_316THz(4),
		 WirelessUMTS_Rel99(0),
		 WirelessUMTS_Rel4(1),
		 WirelessUMTS_Rel5(2),
		 WirelessUMTS_Rel6(3),
		 WirelessUMTS_Rel7(4),
		 WirelessUMTS_Rel8(5),
		 WirelessCDMA2000_HRPD_Rev0(0),
		 WirelessCDMA2000_HRPD_RevA(1),
		 WirelessCDMA2000_HRPD_RevB(2),
		 WirelessCDMA2000_HRPD_RevC(3);

		 private SubtypeEnum(int id) {
			 this.id = id;
		 }

		 public final int id;
	}

	public Subtype(Subtype value) {
		super(value);
	}

	public Subtype() {
		super(64);
	}
}