//==============================================================================
// Brief   : MIH_MN_HO_Commit Response Message
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

import mih.tlvs.LinkTypeTlv;
import mih.tlvs.StatusTlv;
import mih.tlvs.TargetNetworkInfoTlv;
import mih.types.Serializeable;
import mih.types.general.Status;
import mih.types.handover.TgtNetInfo;
import mih.types.links.LinkType;

public class MihMnHoCommitResponse extends Message implements
		Serializeable {

	public MihMnHoCommitResponse() {
		super();
		mid = MIH_MN_HO_Commit_response;
		tlvList.add(new TlvInfo(new StatusTlv(), false));
		tlvList.add(new TlvInfo(new LinkTypeTlv(), false));
		tlvList.add(new TlvInfo(new TargetNetworkInfoTlv(), false));
	}

	public MihMnHoCommitResponse(int version, boolean ack_req,
			boolean ack_rsp, boolean uir, boolean m, int fn, boolean rsvd1,
			int rsvd2, int tid) {
		super(version, ack_req, ack_rsp, uir, m, fn, rsvd1,
				MIH_MN_HO_Commit_response, rsvd2, tid);
		tlvList.add(new TlvInfo(new StatusTlv(), false));
		tlvList.add(new TlvInfo(new LinkTypeTlv(), false));
		tlvList.add(new TlvInfo(new TargetNetworkInfoTlv(), false));
	}

	public Status getStatusTlv() {
		return ((StatusTlv)tlvList.get(0).getTlv()).getValue();
	}

	public void setStatusTlv(Status value) {
		((StatusTlv)tlvList.get(0).getTlv()).setValue(value);
	}

	public LinkType getLinkTypeTlv() {
		return ((LinkTypeTlv)tlvList.get(1).getTlv()).getValue();
	}

	public void setLinkTypeTlv(LinkType value) {
		((LinkTypeTlv)tlvList.get(1).getTlv()).setValue(value);
	}

	public TgtNetInfo getTargetNetworkInfoTlv() {
		return ((TargetNetworkInfoTlv)tlvList.get(2).getTlv()).getValue();
	}

	public void setTargetNetworkInfoTlv(TgtNetInfo value) {
		((TargetNetworkInfoTlv)tlvList.get(2).getTlv()).setValue(value);
	}
}
