//==============================================================================
// Brief   : MIH_Net_HO_Commit Indication Message
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

import mih.tlvs.AssignedResourceSetTlv;
import mih.tlvs.LinkActionListTlv;
import mih.tlvs.LinkTypeTlv;
import mih.tlvs.ListOfTargetNetworkInfoTlv;
import mih.tlvs.TimeIntervalTlv;
import mih.types.Serializeable;
import mih.types.basic.List;
import mih.types.basic.UnsignedInteger16;
import mih.types.handover.AsgnResSet;
import mih.types.handover.TgtNetInfo;
import mih.types.links.LinkActionReq;
import mih.types.links.LinkType;

public class MihNetHoCommitIndication extends Message implements
		Serializeable {

	public MihNetHoCommitIndication() {
		super();
		mid = MIH_Net_HO_Commit_indication;
		tlvList.add(new TlvInfo(new LinkTypeTlv(), false));
		tlvList.add(new TlvInfo(new ListOfTargetNetworkInfoTlv(), false));
		tlvList.add(new TlvInfo(new AssignedResourceSetTlv(), false));
		tlvList.add(new TlvInfo(new TimeIntervalTlv(), false));
		tlvList.add(new TlvInfo(new LinkActionListTlv(), true));
	}

	public MihNetHoCommitIndication(int version, boolean ack_req,
			boolean ack_rsp, boolean uir, boolean m, int fn, boolean rsvd1,
			int rsvd2, int tid) {
		super(version, ack_req, ack_rsp, uir, m, fn, rsvd1,
				MIH_Net_HO_Commit_indication, rsvd2, tid);
		tlvList.add(new TlvInfo(new LinkTypeTlv(), false));
		tlvList.add(new TlvInfo(new ListOfTargetNetworkInfoTlv(), false));
		tlvList.add(new TlvInfo(new AssignedResourceSetTlv(), false));
		tlvList.add(new TlvInfo(new TimeIntervalTlv(), false));
		tlvList.add(new TlvInfo(new LinkActionListTlv(), true));
	}

	public LinkType getLinkTypeTlv() {
		return ((LinkTypeTlv)tlvList.get(0).getTlv()).getValue();
	}

	public void setLinkTypeTlv(LinkType value) {
		((LinkTypeTlv)tlvList.get(0).getTlv()).setValue(value);
	}

	public List<TgtNetInfo> getListOfTargetNetworkInfoTlv() {
		return ((ListOfTargetNetworkInfoTlv)tlvList.get(1).getTlv()).getValue();
	}

	public void setListOfTargetNetworkInfoTlv(List<TgtNetInfo> value) {
		((ListOfTargetNetworkInfoTlv)tlvList.get(1).getTlv()).setValue(value);
	}

	public AsgnResSet getAssignedResourceSetTlv() {
		return ((AssignedResourceSetTlv)tlvList.get(2).getTlv()).getValue();
	}

	public void setAssignedResourceSetTlv(AsgnResSet value) {
		((AssignedResourceSetTlv)tlvList.get(2).getTlv()).setValue(value);
	}

	public UnsignedInteger16 getTimeIntervalTlv() {
		return ((TimeIntervalTlv)tlvList.get(3).getTlv()).getValue();
	}

	public void setTimeIntervalTlv(UnsignedInteger16 value) {
		((TimeIntervalTlv)tlvList.get(3).getTlv()).setValue(value);
	}

	public boolean hasLinkActionListTlv() {
		return tlvList.get(4).getTlv().isInitialized();
	}

	public List<LinkActionReq> getLinkActionListTlv() {
		return ((LinkActionListTlv)tlvList.get(4).getTlv()).getValue();
	}

	public void setLinkActionListTlv(List<LinkActionReq> value) {
		((LinkActionListTlv)tlvList.get(4).getTlv()).setValue(value);
	}
}
