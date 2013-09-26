//==============================================================================
// Brief   : CDMA_CODES Data Type
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

public class CdmaCodes
		extends
		Sequence<InitCode, HoCode, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public CdmaCodes(InitCode initCode, HoCode hoCode) {
		super(initCode, hoCode);
	}

	public CdmaCodes(CdmaCodes value) {
		super(value.getInitCode(), value.getHoCode());
	}

	public CdmaCodes() {
		super(new InitCode(), new HoCode());
	}

	public InitCode getInitCode() {
		return getA();
	}

	public void setInitCode(InitCode initCode) {
		setA(initCode);
	}

	public HoCode getHoCode() {
		return getB();
	}

	public void setHoCode(HoCode hoCode) {
		setB(hoCode);
	}
}
