//==============================================================================
// Brief   : NETWORK_TYPE Data Type
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
import mih.types.basic.Sequence;
import mih.types.informationelements.auxiliar.NullLinkTypeChoice;
import mih.types.informationelements.auxiliar.NullSubtypeChoice;
import mih.types.informationelements.auxiliar.NullTypeExtChoice;

public class NetworkType
		extends
		Sequence<NullLinkTypeChoice, NullSubtypeChoice, NullTypeExtChoice, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public NetworkType(NullLinkTypeChoice linkType, NullSubtypeChoice subtype, NullTypeExtChoice typeExt) {
		super(linkType, subtype, typeExt);
	}

	public NetworkType(NetworkType value) {
		super(value.getLinkType(), value.getSubtype(), value.getTypeExt());
	}

	public NetworkType() {
		super(new NullLinkTypeChoice(), new NullSubtypeChoice(), new NullTypeExtChoice());
	}

	public NullLinkTypeChoice getLinkType() {
		return getA();
	}

	public void setLinkType(NullLinkTypeChoice linkType) {
		setA(linkType);
	}

	public NullSubtypeChoice getSubtype() {
		return getB();
	}

	public void setSubtype(NullSubtypeChoice subtype) {
		setB(subtype);
	}

	public NullTypeExtChoice getTypeExt() {
		return getC();
	}

	public void setTypeExt(NullTypeExtChoice typeExt) {
		setC(typeExt);
	}
}