//==============================================================================
// Brief   : MIH_Event_Unsubscribe Indication Message
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
import mih.tlvs.MihEventListTlv;
import mih.types.Serializeable;
import mih.types.capabilities.MihEvtList;
import mih.types.links.LinkTupleId;

public class MihEventUnsubscribeIndication extends Message implements
		Serializeable {

	public MihEventUnsubscribeIndication() {
		super();
		mid = MIH_Event_Unsubscribe_indication;
		tlvList.add(new TlvInfo(new LinkIdentifierTlv(), false));
		tlvList.add(new TlvInfo(new MihEventListTlv(), false));
	}

	public MihEventUnsubscribeIndication(int version, boolean ack_req,
			boolean ack_rsp, boolean uir, boolean m, int fn, boolean rsvd1,
			int rsvd2, int tid) {
		super(version, ack_req, ack_rsp, uir, m, fn, rsvd1,
				MIH_Event_Unsubscribe_indication, rsvd2, tid);
		tlvList.add(new TlvInfo(new LinkIdentifierTlv(), false));
		tlvList.add(new TlvInfo(new MihEventListTlv(), false));
	}

	public LinkTupleId getLinkIdentifierTlv() {
		return ((LinkIdentifierTlv) tlvList.get(0).getTlv()).getValue();
	}

	public void setLinkIdentifierTlv(LinkTupleId value) {
		((LinkIdentifierTlv) tlvList.get(0).getTlv()).setValue(value);
	}

	public MihEvtList getMihEventListTlv() {
		return ((MihEventListTlv) tlvList.get(1).getTlv()).getValue();
	}

	public void setMihEventListTlv(MihEvtList value) {
		((MihEventListTlv) tlvList.get(1).getTlv()).setValue(value);
	}
}
