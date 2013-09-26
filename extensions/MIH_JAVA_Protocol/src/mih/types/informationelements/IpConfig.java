//==============================================================================
// Brief   : IP_CONFIG Data Type
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
import mih.types.informationelements.auxiliar.NullAccRtrChoice;
import mih.types.informationelements.auxiliar.NullDhcpServChoice;
import mih.types.informationelements.auxiliar.NullFnAgntChoice;
import mih.types.ipconfiguration.IpCfgMthds;

public class IpConfig
		extends
		Sequence<IpCfgMthds, NullDhcpServChoice, NullFnAgntChoice, NullAccRtrChoice, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public IpConfig(IpCfgMthds ipCfgMthds, NullDhcpServChoice dhcpServ, NullFnAgntChoice fnAgnt, NullAccRtrChoice accRtr) {
		super(ipCfgMthds, dhcpServ, fnAgnt, accRtr);
	}

	public IpConfig(IpConfig value) {
		super(value.getIpCfgMthds(), value.getDhcpServ(), value.getFnAgnt(), value.getAccRtr());
	}

	public IpConfig() {
		super(new IpCfgMthds(), new NullDhcpServChoice(), new NullFnAgntChoice(), new NullAccRtrChoice());
	}

	public IpCfgMthds getIpCfgMthds() {
		return getA();
	}

	public void setIpCfgMthds(IpCfgMthds ipCfgMthds) {
		setA(ipCfgMthds);
	}

	public NullDhcpServChoice getDhcpServ() {
		return getB();
	}

	public void setDhcpServ(NullDhcpServChoice dhcpServ) {
		setB(dhcpServ);
	}

	public NullFnAgntChoice getFnAgnt() {
		return getC();
	}

	public void setFnAgnt(NullFnAgntChoice fnAgnt) {
		setC(fnAgnt);
	}

	public NullAccRtrChoice getAccRtr() {
		return getD();
	}

	public void setAccRtr(NullAccRtrChoice accRtr) {
		setD(accRtr);
	}
}
