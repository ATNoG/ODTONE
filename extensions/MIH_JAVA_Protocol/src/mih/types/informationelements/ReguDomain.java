//==============================================================================
// Brief   : REGU_DOMAIN Data Type
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
import mih.types.basic.UnsignedInteger8;

public class ReguDomain
		extends
		Sequence<CntryCode, UnsignedInteger8, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public ReguDomain(CntryCode cntrycode, UnsignedInteger8 regClass) {
		super(cntrycode, regClass);
	}

	public ReguDomain(ReguDomain value) {
		super(value.getCntryCode(), value.getRegulatoryClass());
	}

	public ReguDomain() {
		super(new CntryCode(), new UnsignedInteger8());
	}

	public CntryCode getCntryCode() {
		return getA();
	}

	public void setCntryCode(CntryCode cntrycode) {
		setA(cntrycode);
	}

	public UnsignedInteger8 getRegulatoryClass() {
		return getB();
	}

	public void setRegulatoryClass(UnsignedInteger8 regClass) {
		setB(regClass);
	}
}
