//==============================================================================
// Brief   : GAP Data Type
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
import mih.types.basic.UnsignedInteger16;
import mih.types.basic.UnsignedInteger8;

public class Gap
		extends
		Sequence<UnsignedInteger16, UnsignedInteger8, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public Gap(UnsignedInteger16 ttg, UnsignedInteger8 rtg) {
		super(ttg, rtg);
	}

	public Gap(Gap value) {
		super(value.getTTG(), value.getRTG());
	}

	public Gap() {
		super(new UnsignedInteger16(), new UnsignedInteger8());
	}

	public UnsignedInteger16 getTTG() {
		return getA();
	}

	public void setTTG(UnsignedInteger16 ttg) {
		setA(ttg);
	}

	public UnsignedInteger8 getRTG() {
		return getB();
	}

	public void setRTG(UnsignedInteger8 rtg) {
		setB(rtg);
	}
}
