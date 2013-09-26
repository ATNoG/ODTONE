//==============================================================================
// Brief   : IQ_BIN_DATA Data Type
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
import mih.types.basic.Sequence;
import mih.types.informationservicequery.auxiliar.NullCurrPrefChoice;
import mih.types.informationservicequery.auxiliar.NullNetTypeIncChoice;
import mih.types.informationservicequery.auxiliar.NullNetwkIncChoice;
import mih.types.informationservicequery.auxiliar.NullQuerierLocChoice;
import mih.types.informationservicequery.auxiliar.NullRptLimitChoice;
import mih.types.informationservicequery.auxiliar.NullRptTemplChoice;

public class IqBinData
		extends
		Sequence<NullQuerierLocChoice, NullNetTypeIncChoice, NullNetwkIncChoice, NullRptTemplChoice, NullRptLimitChoice, NullCurrPrefChoice, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public IqBinData(NullQuerierLocChoice querierLoc, NullNetTypeIncChoice netTypeInc, NullNetwkIncChoice netwkInc, NullRptTemplChoice rptTempl, NullRptLimitChoice rptLimit, NullCurrPrefChoice currPref) {
		super(querierLoc, netTypeInc, netwkInc, rptTempl, rptLimit, currPref);
	}

	public IqBinData(IqBinData value) {
		super(value.getQuerierLoc(), value.getNetTypeInc(), value.getNetwkInc(), value.getRptTempl(), value.getRptLimit(), value.getCurrPref());
	}

	public IqBinData() {
		super(new NullQuerierLocChoice(), new NullNetTypeIncChoice(), new NullNetwkIncChoice(), new NullRptTemplChoice(), new NullRptLimitChoice(), new NullCurrPrefChoice());
	}

	public NullQuerierLocChoice getQuerierLoc() {
		return getA();
	}

	public void setQuerierLoc(NullQuerierLocChoice querierLoc) {
		setA(querierLoc);
	}

	public NullNetTypeIncChoice getNetTypeInc() {
		return getB();
	}

	public void setNetTypeInc(NullNetTypeIncChoice netTypeInc) {
		setB(netTypeInc);
	}

	public NullNetwkIncChoice getNetwkInc() {
		return getC();
	}

	public void setNetwkInc(NullNetwkIncChoice netwkInc) {
		setC(netwkInc);
	}

	public NullRptTemplChoice getRptTempl() {
		return getD();
	}

	public void setRptTempl(NullRptTemplChoice rptTempl) {
		setD(rptTempl);
	}

	public NullRptLimitChoice getRptLimit() {
		return getE();
	}

	public void setRptLimit(NullRptLimitChoice rptLimit) {
		setE(rptLimit);
	}

	public NullCurrPrefChoice getCurrPref() {
		return getF();
	}

	public void setCurrPref(NullCurrPrefChoice currPref) {
		setF(currPref);
	}
}
