//==============================================================================
// Brief   : MIH_MN_HO_Commit Indication Message
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
import mih.tlvs.TargetNetworkInfoTlv;
import mih.types.Serializeable;
import mih.types.handover.TgtNetInfo;
import mih.types.links.LinkType;

public class MihMnHoCommitIndication extends Message implements
		Serializeable {

	public MihMnHoCommitIndication() {
		super();
		mid = MIH_MN_HO_Commit_indication;
		tlvList.add(new TlvInfo(new LinkTypeTlv(), false));
		tlvList.add(new TlvInfo(new TargetNetworkInfoTlv(), false));
	}

	public MihMnHoCommitIndication(int version, boolean ack_req,
			boolean ack_rsp, boolean uir, boolean m, int fn, boolean rsvd1,
			int rsvd2, int tid) {
		super(version, ack_req, ack_rsp, uir, m, fn, rsvd1,
				MIH_MN_HO_Commit_indication, rsvd2, tid);
		tlvList.add(new TlvInfo(new LinkTypeTlv(), false));
		tlvList.add(new TlvInfo(new TargetNetworkInfoTlv(), false));
	}

	public LinkType getLinkTypeTlv() {
		return ((LinkTypeTlv)tlvList.get(0).getTlv()).getValue();
	}

	public void setLinkTypeTlv(LinkType value) {
		((LinkTypeTlv)tlvList.get(0).getTlv()).setValue(value);
	}

	public TgtNetInfo getTargetNetworkInfoTlv() {
		return ((TargetNetworkInfoTlv)tlvList.get(1).getTlv()).getValue();
	}

	public void setTargetNetworkInfoTlv(TgtNetInfo value) {
		((TargetNetworkInfoTlv)tlvList.get(1).getTlv()).setValue(value);
	}
}
