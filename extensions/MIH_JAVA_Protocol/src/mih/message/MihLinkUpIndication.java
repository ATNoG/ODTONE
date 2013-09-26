//==============================================================================
// Brief   : MIH_Link_Up Indication Message
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

package mih.message;

import mih.tlvs.IpRenewalFlagTlv;
import mih.tlvs.LinkIdentifierTlv;
import mih.tlvs.MobilityManagementSupportTlv;
import mih.tlvs.NewAccessRouterTlv;
import mih.tlvs.OldAccessRouterTlv;
import mih.types.Serializeable;
import mih.types.address.LinkAddr;
import mih.types.ipconfiguration.IpMobMgmt;
import mih.types.ipconfiguration.IpRenewalFlag;
import mih.types.links.LinkTupleId;

public class MihLinkUpIndication extends Message implements
		Serializeable {

	public MihLinkUpIndication() {
		super();
		mid = MIH_Link_Up_indication;
		tlvList.add(new TlvInfo(new LinkIdentifierTlv(), false));
		tlvList.add(new TlvInfo(new OldAccessRouterTlv(), true));
		tlvList.add(new TlvInfo(new NewAccessRouterTlv(), true));
		tlvList.add(new TlvInfo(new IpRenewalFlagTlv(), true));
		tlvList.add(new TlvInfo(new MobilityManagementSupportTlv(), true));
	}

	public MihLinkUpIndication(int version, boolean ack_req,
			boolean ack_rsp, boolean uir, boolean m, int fn, boolean rsvd1,
			int rsvd2, int tid) {
		super(version, ack_req, ack_rsp, uir, m, fn, rsvd1,
				MIH_Link_Up_indication, rsvd2, tid);
		tlvList.add(new TlvInfo(new LinkIdentifierTlv(), false));
		tlvList.add(new TlvInfo(new OldAccessRouterTlv(), true));
		tlvList.add(new TlvInfo(new NewAccessRouterTlv(), true));
		tlvList.add(new TlvInfo(new IpRenewalFlagTlv(), true));
		tlvList.add(new TlvInfo(new MobilityManagementSupportTlv(), true));
	}

	public LinkTupleId getLinkIdentifierTlv() {
		return ((LinkIdentifierTlv) tlvList.get(0).getTlv()).getValue();
	}

	public void setLinkIdentifierTlv(LinkTupleId value) {
		((LinkIdentifierTlv) tlvList.get(0).getTlv()).setValue(value);
	}

	public boolean hasOldAccessRouterTlv() {
		return tlvList.get(1).getTlv().isInitialized();
	}

	public LinkAddr getOldAccessRouterTlv() {
		return ((OldAccessRouterTlv) tlvList.get(1).getTlv()).getValue();
	}

	public void setOldAccessRouterTlv(LinkAddr value) {
		((OldAccessRouterTlv) tlvList.get(1).getTlv()).setValue(value);
	}

	public boolean hasNewAccessRouterTlv() {
		return tlvList.get(2).getTlv().isInitialized();
	}

	public LinkAddr getNewAccessRouterTlv() {
		return ((NewAccessRouterTlv) tlvList.get(2).getTlv()).getValue();
	}

	public void setNewAccessRouterTlv(LinkAddr value) {
		((NewAccessRouterTlv) tlvList.get(2).getTlv()).setValue(value);
	}

	public boolean hasIpRenewalFlagTlv() {
		return tlvList.get(3).getTlv().isInitialized();
	}

	public IpRenewalFlag getIpRenewalFlagTlv() {
		return ((IpRenewalFlagTlv) tlvList.get(3).getTlv()).getValue();
	}

	public void setIpRenewalFlagTlv(IpRenewalFlag value) {
		((IpRenewalFlagTlv) tlvList.get(3).getTlv()).setValue(value);
	}

	public boolean hasMobilityManagementSupportTlv() {
		return tlvList.get(4).getTlv().isInitialized();
	}

	public IpMobMgmt getMobilityManagementSupportTlv() {
		return ((MobilityManagementSupportTlv) tlvList.get(4).getTlv()).getValue();
	}

	public void setMobilityManagementSupportTlv(IpMobMgmt value) {
		((MobilityManagementSupportTlv) tlvList.get(4).getTlv()).setValue(value);
	}
}
