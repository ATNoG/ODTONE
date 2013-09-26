//==============================================================================
// Brief   : MIH_IQ_TYPE_LST Data Type
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

package mih.types.capabilities;

import mih.types.Serializeable;
import mih.types.basic.Bitmap;

public class MihIqTypeLst extends Bitmap implements Serializeable {

	public enum MihIqTypeLstEnum {
		 BinaryData(0),
		 RdfData(1),
		 RdfSchemaUrl(2),
		 RdfSchema(3),
		 IeNetworkType(4),
		 IeOperatorId(5),
		 IeServiceProviderId(6),
		 IeCountryCode(7),
		 IeNetworkId(8),
		 IeNetworkAuxId(9),
		 IeRoamingPartners(10),
		 IeCost(11),
		 IeNetworkQos(12),
		 IeNetworkDataRate(13),
		 IeNetRegultDomain(14),
		 IeNetFrequencyBands(15),
		 IeNetIpCgfMethods(16),
		 IeNetCapabilities(17),
		 IeNetSupportedLcp(18),
		 IeNetMobMgmtProt(19),
		 IeNetEmservProxy(20),
		 IeNetImsProxyCscf(21),
		 IeNetMobileNetwork(22),
		 IePoaLinkAddr(23),
		 IePoaLocation(24),
		 IePoaChannelRange(25),
		 IePoaSystemInfo(26),
		 IePoaSubnetInfo(27),
		 IePoaIpAddr(28);

		 private MihIqTypeLstEnum(int id) {
			 this.id = id;
		 }

		 public final int id;
	}

	public MihIqTypeLst(MihIqTypeLstEnum value) {
		super(64);
		set(value.id);
	}

	public MihIqTypeLst(MihIqTypeLst value) {
		super(value);
	}

	public MihIqTypeLst() {
		super(64);
	}
}