//==============================================================================
// Brief   : MIH_N2N_HO_Commit Response Message
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
import mih.tlvs.LinkIdentifierTlv;
import mih.tlvs.MobileNodeMihfIdTlv;
import mih.tlvs.StatusTlv;
import mih.types.Serializeable;
import mih.types.basic.OctetString;
import mih.types.general.Status;
import mih.types.handover.AsgnResSet;
import mih.types.links.LinkTupleId;

public class MihN2nHoCommitResponse extends Message implements
		Serializeable {

	public MihN2nHoCommitResponse() {
		super();
		mid = MIH_N2N_HO_Commit_response;
		tlvList.add(new TlvInfo(new StatusTlv(), false));
		tlvList.add(new TlvInfo(new MobileNodeMihfIdTlv(), false));
		tlvList.add(new TlvInfo(new LinkIdentifierTlv(), true));
		tlvList.add(new TlvInfo(new AssignedResourceSetTlv(), true));
	}

	public MihN2nHoCommitResponse(int version, boolean ack_req,
			boolean ack_rsp, boolean uir, boolean m, int fn, boolean rsvd1,
			int rsvd2, int tid) {
		super(version, ack_req, ack_rsp, uir, m, fn, rsvd1,
				MIH_N2N_HO_Commit_response, rsvd2, tid);
		tlvList.add(new TlvInfo(new StatusTlv(), false));
		tlvList.add(new TlvInfo(new MobileNodeMihfIdTlv(), false));
		tlvList.add(new TlvInfo(new LinkIdentifierTlv(), true));
		tlvList.add(new TlvInfo(new AssignedResourceSetTlv(), true));
	}

	public Status getStatusTlv() {
		return ((StatusTlv) tlvList.get(0).getTlv()).getValue();
	}

	public void setStatusTlv(Status value) {
		((StatusTlv) tlvList.get(0).getTlv()).setValue(value);
	}

	public OctetString getMobileNodeMihfIdTlv() {
		return ((MobileNodeMihfIdTlv) tlvList.get(1).getTlv()).getValue();
	}

	public void setMobileNodeMihfIdTlv(OctetString value) {
		((MobileNodeMihfIdTlv) tlvList.get(1).getTlv()).setValue(value);
	}

	public boolean hasLinkIdentifierTlv() {
		return tlvList.get(2).getTlv().isInitialized();
	}

	public LinkTupleId getLinkIdentifierTlv() {
		return ((LinkIdentifierTlv) tlvList.get(2).getTlv()).getValue();
	}

	public void setLinkIdentifierTlv(LinkTupleId value) {
		((LinkIdentifierTlv) tlvList.get(2).getTlv()).setValue(value);
	}

	public boolean hasAssignedResourceSetTlv() {
		return tlvList.get(3).getTlv().isInitialized();
	}

	public AsgnResSet getAssignedResourceSetTlv() {
		return ((AssignedResourceSetTlv) tlvList.get(3).getTlv()).getValue();
	}

	public void setAssignedResourceSetTlv(AsgnResSet value) {
		((AssignedResourceSetTlv) tlvList.get(3).getTlv()).setValue(value);
	}
}
