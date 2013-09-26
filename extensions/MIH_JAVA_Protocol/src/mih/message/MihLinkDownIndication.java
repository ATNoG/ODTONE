//==============================================================================
// Brief   : MIH_Link_Down Indication Message
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

import mih.tlvs.LinkDownReasonCodeTlv;
import mih.tlvs.LinkIdentifierTlv;
import mih.tlvs.OldAccessRouterTlv;
import mih.types.Serializeable;
import mih.types.address.LinkAddr;
import mih.types.links.LinkDnReason;
import mih.types.links.LinkTupleId;

public class MihLinkDownIndication extends Message implements
		Serializeable {

	public MihLinkDownIndication() {
		super();
		mid = MIH_Link_Down_indication;
		tlvList.add(new TlvInfo(new LinkIdentifierTlv(), false));
		tlvList.add(new TlvInfo(new OldAccessRouterTlv(), true));
		tlvList.add(new TlvInfo(new LinkDownReasonCodeTlv(), false));
	}

	public MihLinkDownIndication(int version, boolean ack_req,
			boolean ack_rsp, boolean uir, boolean m, int fn, boolean rsvd1,
			int rsvd2, int tid) {
		super(version, ack_req, ack_rsp, uir, m, fn, rsvd1,
				MIH_Link_Down_indication, rsvd2, tid);
		tlvList.add(new TlvInfo(new LinkIdentifierTlv(), false));
		tlvList.add(new TlvInfo(new OldAccessRouterTlv(), true));
		tlvList.add(new TlvInfo(new LinkDownReasonCodeTlv(), false));
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

	public LinkDnReason getLinkDownReasonCodeTlv() {
		return ((LinkDownReasonCodeTlv) tlvList.get(2).getTlv()).getValue();
	}

	public void setLinkDownReasonCodeTlv(LinkDnReason value) {
		((LinkDownReasonCodeTlv) tlvList.get(2).getTlv()).setValue(value);
	}
}
