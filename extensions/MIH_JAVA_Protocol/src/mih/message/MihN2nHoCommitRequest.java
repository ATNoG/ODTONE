//==============================================================================
// Brief   : MIH_N2N_HO_Commit Request Message
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

import mih.tlvs.MnLinkIdTlv;
import mih.tlvs.MobileNodeMihfIdTlv;
import mih.tlvs.PoaTlv;
import mih.tlvs.RequestResourceSetTlv;
import mih.types.Serializeable;
import mih.types.address.LinkAddr;
import mih.types.basic.OctetString;
import mih.types.handover.ReqResSet;
import mih.types.links.LinkId;

public class MihN2nHoCommitRequest extends Message implements
		Serializeable {

	public MihN2nHoCommitRequest() {
		super();
		mid = MIH_N2N_HO_Commit_request;
		tlvList.add(new TlvInfo(new MobileNodeMihfIdTlv(), false));
		tlvList.add(new TlvInfo(new MnLinkIdTlv(), false));
		tlvList.add(new TlvInfo(new PoaTlv(), false));
		tlvList.add(new TlvInfo(new RequestResourceSetTlv(), false));
	}

	public MihN2nHoCommitRequest(int version, boolean ack_req,
			boolean ack_rsp, boolean uir, boolean m, int fn, boolean rsvd1,
			int rsvd2, int tid) {
		super(version, ack_req, ack_rsp, uir, m, fn, rsvd1,
				MIH_N2N_HO_Commit_request, rsvd2, tid);
		tlvList.add(new TlvInfo(new MobileNodeMihfIdTlv(), false));
		tlvList.add(new TlvInfo(new MnLinkIdTlv(), false));
		tlvList.add(new TlvInfo(new PoaTlv(), false));
		tlvList.add(new TlvInfo(new RequestResourceSetTlv(), false));
	}

	public OctetString getMobileNodeMihfIdTlv() {
		return ((MobileNodeMihfIdTlv) tlvList.get(0).getTlv()).getValue();
	}

	public void setMobileNodeMihfIdTlv(OctetString value) {
		((MobileNodeMihfIdTlv) tlvList.get(0).getTlv()).setValue(value);
	}

	public LinkId getMnLinkIdTlv() {
		return ((MnLinkIdTlv) tlvList.get(1).getTlv()).getValue();
	}

	public void setMnLinkIdTlv(LinkId value) {
		((MnLinkIdTlv) tlvList.get(1).getTlv()).setValue(value);
	}

	public LinkAddr getPoaTlv() {
		return ((PoaTlv) tlvList.get(2).getTlv()).getValue();
	}

	public void setPoaTlv(LinkAddr value) {
		((PoaTlv) tlvList.get(2).getTlv()).setValue(value);
	}

	public ReqResSet getRequestResourceSetTlv() {
		return ((RequestResourceSetTlv) tlvList.get(3).getTlv()).getValue();
	}

	public void setRequestResourceSetTlv(ReqResSet value) {
		((RequestResourceSetTlv) tlvList.get(3).getTlv()).setValue(value);
	}
}
