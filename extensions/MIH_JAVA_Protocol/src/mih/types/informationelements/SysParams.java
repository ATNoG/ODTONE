//==============================================================================
// Brief   : SYS_PARAMS Data Type
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

public class SysParams
		extends
		Sequence<BaseId, PilotPn, FreqId, BandClass, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public SysParams(BaseId baseId, PilotPn pilotPn, FreqId freqId, BandClass bandClass) {
		super(baseId, pilotPn, freqId, bandClass);
	}

	public SysParams(SysParams value) {
		super(value.getBaseId(), value.getPilotPn(), value.getFreqId(), value.getBandClass());
	}

	public SysParams() {
		super(new BaseId(), new PilotPn(), new FreqId(), new BandClass());
	}

	public BaseId getBaseId() {
		return getA();
	}

	public void setBaseId(BaseId baseId) {
		setA(baseId);
	}

	public PilotPn getPilotPn() {
		return getB();
	}

	public void setPilotPn(PilotPn pilotPn) {
		setB(pilotPn);
	}

	public FreqId getFreqId() {
		return getC();
	}

	public void setFreqId(FreqId freqId) {
		setC(freqId);
	}

	public BandClass getBandClass() {
		return getD();
	}

	public void setBandClass(BandClass bandClass) {
		setD(bandClass);
	}
}
