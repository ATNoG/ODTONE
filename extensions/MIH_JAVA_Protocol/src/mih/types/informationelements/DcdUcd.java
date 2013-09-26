//==============================================================================
// Brief   : DCD_UCD Data Type
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

public class DcdUcd
		extends
		Sequence<BaseId, Bandwidth, DuCtrFreq, Eirp, Gap, BurstProf, CdmaCodes, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public DcdUcd(BaseId baseId, Bandwidth bandwidth, DuCtrFreq duCtrFreq, Eirp eirp, Gap gap, BurstProf burstProf, CdmaCodes cdmaCodes) {
		super(baseId, bandwidth, duCtrFreq, eirp, gap, burstProf, cdmaCodes);
	}

	public DcdUcd(DcdUcd value) {
		super(value.getBaseId(), value.getBandwidth(), value.getDuCtrFreq(), value.getEirp(), value.getGap(), value.getBurstProf(), value.getCdmaCodes());
	}

	public DcdUcd() {
		super(new BaseId(), new Bandwidth(), new DuCtrFreq(), new Eirp(), new Gap(), new BurstProf(), new CdmaCodes());
	}

	public BaseId getBaseId() {
		return getA();
	}

	public void setBaseId(BaseId baseId) {
		setA(baseId);
	}

	public Bandwidth getBandwidth() {
		return getB();
	}

	public void setBandwidth(Bandwidth bandwidth) {
		setB(bandwidth);
	}

	public DuCtrFreq getDuCtrFreq() {
		return getC();
	}

	public void setDuCtrFreq(DuCtrFreq duCtrFreq) {
		setC(duCtrFreq);
	}

	public Eirp getEirp() {
		return getD();
	}

	public void setEirp(Eirp eirp) {
		setD(eirp);
	}

	public Gap getGap() {
		return getE();
	}

	public void setGap(Gap gap) {
		setE(gap);
	}

	public BurstProf getBurstProf() {
		return getF();
	}

	public void setBurstProf(BurstProf burstProf) {
		setF(burstProf);
	}

	public CdmaCodes getCdmaCodes() {
		return getG();
	}

	public void setCdmaCodes(CdmaCodes cdmaCodes) {
		setG(cdmaCodes);
	}
}
