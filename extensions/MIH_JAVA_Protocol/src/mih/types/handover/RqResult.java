//==============================================================================
// Brief   : RQ_RESULT Data Type
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

package mih.types.handover;

import mih.types.Serializeable;
import mih.types.basic.Sequence;
import mih.types.handover.auxiliar.NullBooleanAccRtrChoice;
import mih.types.handover.auxiliar.NullBooleanDhcpServChoice;
import mih.types.handover.auxiliar.NullBooleanFnAgntChoice;
import mih.types.handover.auxiliar.NullBooleanIpCfgMthdsChoice;
import mih.types.links.LinkPoaList;
import mih.types.qos.QosList;

public class RqResult
		extends
		Sequence<LinkPoaList, QosList, NullBooleanIpCfgMthdsChoice, NullBooleanDhcpServChoice, NullBooleanFnAgntChoice, NullBooleanAccRtrChoice, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public RqResult(LinkPoaList linkPoaList, QosList qosList, NullBooleanIpCfgMthdsChoice ipCfgMthds, NullBooleanDhcpServChoice dhcpServ, NullBooleanFnAgntChoice fnAgnt, NullBooleanAccRtrChoice accRtr) {
		super(linkPoaList, qosList, ipCfgMthds, dhcpServ, fnAgnt, accRtr);
	}

	public RqResult(RqResult value) {
		super(value.getLinkPoaList(), value.getQosList(), value.getIpCfgMthds(), value.getDhcpServ(), value.getFnAgnt(), value.getAccRtr());
	}

	public RqResult() {
		super(new LinkPoaList(), new QosList(), new NullBooleanIpCfgMthdsChoice(), new NullBooleanDhcpServChoice(), new NullBooleanFnAgntChoice(), new NullBooleanAccRtrChoice());
	}

	public LinkPoaList getLinkPoaList() {
		return getA();
	}

	public void setLinkPoaList(LinkPoaList linkPoaList) {
		setA(linkPoaList);
	}

	public QosList getQosList() {
		return getB();
	}

	public void setQosList(QosList qosList) {
		setB(qosList);
	}

	public NullBooleanIpCfgMthdsChoice getIpCfgMthds() {
		return getC();
	}

	public void setIpCfgMthds(NullBooleanIpCfgMthdsChoice ipCfgMthds) {
		setC(ipCfgMthds);
	}

	public NullBooleanDhcpServChoice getDhcpServ() {
		return getD();
	}

	public void setDhcpServ(NullBooleanDhcpServChoice dhcpServ) {
		setD(dhcpServ);
	}

	public NullBooleanFnAgntChoice getFnAgnt() {
		return getE();
	}

	public void setFnAgnt(NullBooleanFnAgntChoice fnAgnt) {
		setE(fnAgnt);
	}

	public NullBooleanAccRtrChoice getAccRtr() {
		return getF();
	}

	public void setAccRtr(NullBooleanAccRtrChoice accRtr) {
		setF(accRtr);
	}
}
