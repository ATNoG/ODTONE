//==============================================================================
// Brief   : MIH_Link_Handover_Complete Indication Message
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

import mih.tlvs.LinkIdentifierTlv;
import mih.tlvs.NewAccessRouterTlv;
import mih.tlvs.NewLinkIdentifierTlv;
import mih.tlvs.OldAccessRouterTlv;
import mih.tlvs.StatusTlv;
import mih.types.Serializeable;
import mih.types.address.LinkAddr;
import mih.types.general.Status;
import mih.types.links.LinkTupleId;

public class MihLinkHandoverCompleteIndication extends Message implements
		Serializeable {

	public MihLinkHandoverCompleteIndication() {
		super();
		mid = MIH_Link_Handover_Complete_indication;
		tlvList.add(new TlvInfo(new LinkIdentifierTlv(), false));
		tlvList.add(new TlvInfo(new NewLinkIdentifierTlv(), false));
		tlvList.add(new TlvInfo(new OldAccessRouterTlv(), true));
		tlvList.add(new TlvInfo(new NewAccessRouterTlv(), true));
		tlvList.add(new TlvInfo(new StatusTlv(), false));
	}

	public MihLinkHandoverCompleteIndication(int version, boolean ack_req,
			boolean ack_rsp, boolean uir, boolean m, int fn, boolean rsvd1,
			int rsvd2, int tid) {
		super(version, ack_req, ack_rsp, uir, m, fn, rsvd1,
				MIH_Link_Handover_Complete_indication, rsvd2, tid);
		tlvList.add(new TlvInfo(new LinkIdentifierTlv(), false));
		tlvList.add(new TlvInfo(new NewLinkIdentifierTlv(), false));
		tlvList.add(new TlvInfo(new OldAccessRouterTlv(), true));
		tlvList.add(new TlvInfo(new NewAccessRouterTlv(), true));
		tlvList.add(new TlvInfo(new StatusTlv(), false));
	}

	public LinkTupleId getLinkIdentifierTlv() {
		return ((LinkIdentifierTlv) tlvList.get(0).getTlv()).getValue();
	}

	public void setLinkIdentifierTlv(LinkTupleId value) {
		((LinkIdentifierTlv) tlvList.get(0).getTlv()).setValue(value);
	}

	public LinkTupleId getNewLinkIdentifierTlv() {
		return ((NewLinkIdentifierTlv) tlvList.get(1).getTlv()).getValue();
	}

	public void setNewLinkIdentifierTlv(LinkTupleId value) {
		((NewLinkIdentifierTlv) tlvList.get(1).getTlv()).setValue(value);
	}

	public boolean hasOldAccessRouterTlv() {
		return tlvList.get(2).getTlv().isInitialized();
	}

	public LinkAddr getOldAccessRouterTlv() {
		return ((OldAccessRouterTlv) tlvList.get(2).getTlv()).getValue();
	}

	public void setOldAccessRouterTlv(LinkAddr value) {
		((OldAccessRouterTlv) tlvList.get(2).getTlv()).setValue(value);
	}

	public boolean hasNewAccessRouterTlv() {
		return tlvList.get(3).getTlv().isInitialized();
	}

	public LinkAddr getNewAccessRouterTlv() {
		return ((NewAccessRouterTlv) tlvList.get(3).getTlv()).getValue();
	}

	public void setNewAccessRouterTlv(LinkAddr value) {
		((NewAccessRouterTlv) tlvList.get(3).getTlv()).setValue(value);
	}

	public Status getStatusTlv() {
		return ((StatusTlv) tlvList.get(4).getTlv()).getValue();
	}

	public void setStatusTlv(Status value) {
		((StatusTlv) tlvList.get(4).getTlv()).setValue(value);
	}
}
