//==============================================================================
// Brief   : MIH_N2N_HO_Complete Indication Message
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

import mih.tlvs.HandoverResultTlv;
import mih.tlvs.LinkIdentifierTlv;
import mih.tlvs.MobileNodeMihfIdTlv;
import mih.tlvs.NewLinkIdentifierTlv;
import mih.types.Serializeable;
import mih.types.basic.OctetString;
import mih.types.handover.HoResult;
import mih.types.links.LinkTupleId;

public class MihN2nHoCompleteIndication extends Message implements
		Serializeable {

	public MihN2nHoCompleteIndication() {
		super();
		mid = MIH_N2N_HO_Complete_indication;
		tlvList.add(new TlvInfo(new MobileNodeMihfIdTlv(), false));
		tlvList.add(new TlvInfo(new LinkIdentifierTlv(), false));
		tlvList.add(new TlvInfo(new NewLinkIdentifierTlv(), false));
		tlvList.add(new TlvInfo(new HandoverResultTlv(), false));
	}

	public MihN2nHoCompleteIndication(int version, boolean ack_req,
			boolean ack_rsp, boolean uir, boolean m, int fn, boolean rsvd1,
			int rsvd2, int tid) {
		super(version, ack_req, ack_rsp, uir, m, fn, rsvd1,
				MIH_N2N_HO_Complete_indication, rsvd2, tid);
		tlvList.add(new TlvInfo(new MobileNodeMihfIdTlv(), false));
		tlvList.add(new TlvInfo(new LinkIdentifierTlv(), false));
		tlvList.add(new TlvInfo(new NewLinkIdentifierTlv(), false));
		tlvList.add(new TlvInfo(new HandoverResultTlv(), false));
	}

	public OctetString getMobileNodeMihfIdTlv() {
		return ((MobileNodeMihfIdTlv) tlvList.get(0).getTlv()).getValue();
	}

	public void setMobileNodeMihfIdTlv(OctetString value) {
		((MobileNodeMihfIdTlv) tlvList.get(0).getTlv()).setValue(value);
	}

	public LinkTupleId getLinkIdentifierTlv() {
		return ((LinkIdentifierTlv) tlvList.get(1).getTlv()).getValue();
	}

	public void setLinkIdentifierTlv(LinkTupleId value) {
		((LinkIdentifierTlv) tlvList.get(1).getTlv()).setValue(value);
	}

	public LinkTupleId getNewLinkIdentifierTlv() {
		return ((NewLinkIdentifierTlv) tlvList.get(2).getTlv()).getValue();
	}

	public void setNewLinkIdentifierTlv(LinkTupleId value) {
		((NewLinkIdentifierTlv) tlvList.get(2).getTlv()).setValue(value);
	}

	public HoResult getHandoverResultTlv() {
		return ((HandoverResultTlv) tlvList.get(3).getTlv()).getValue();
	}

	public void setHandoverResultTlv(HoResult value) {
		((HandoverResultTlv) tlvList.get(3).getTlv()).setValue(value);
	}
}
