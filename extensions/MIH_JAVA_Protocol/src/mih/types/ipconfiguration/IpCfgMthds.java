//==============================================================================
// Brief   : IP_CFG_MTHDS Data Type
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

package mih.types.ipconfiguration;

import mih.types.Serializeable;
import mih.types.basic.Bitmap;

public class IpCfgMthds extends Bitmap implements Serializeable {

	public enum IpCfgMthdsEnum {
		 Ipv4StaticConfiguration(0),
		 Ipv4DynamicConfiguration(1),
		 MobileIpv4WithFACoA(2),
		 MobileIpv4WithoutFA(3),
		 Ipv6StatelessAddressConfiguration(11),
		 Ipv6StatefulAddressConfiguration(12),
		 Ipv6ManualConfiguration(12);

		 private IpCfgMthdsEnum(int id) {
			 this.id = id;
		 }

		 public final int id;
	}

	public IpCfgMthds(IpCfgMthds value) {
		super(value);
	}

	public IpCfgMthds() {
		super(32);
	}
}