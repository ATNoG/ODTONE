//==============================================================================
// Brief   : MIH_Register Request Message
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

import mih.tlvs.LinkIdentifierListTlv;
import mih.tlvs.RegisterRequestCodeTlv;
import mih.types.Serializeable;
import mih.types.basic.List;
import mih.types.links.LinkId;
import mih.types.registration.RegRequestCode;

public class MihRegisterRequest extends Message implements
		Serializeable {

	public MihRegisterRequest() {
		super();
		mid = MIH_Register_request;
		tlvList.add(new TlvInfo(new LinkIdentifierListTlv(), false));
		tlvList.add(new TlvInfo(new RegisterRequestCodeTlv(), false));
	}

	public MihRegisterRequest(int version, boolean ack_req,
			boolean ack_rsp, boolean uir, boolean m, int fn, boolean rsvd1,
			int rsvd2, int tid) {
		super(version, ack_req, ack_rsp, uir, m, fn, rsvd1,
				MIH_Register_request, rsvd2, tid);
		tlvList.add(new TlvInfo(new LinkIdentifierListTlv(), false));
		tlvList.add(new TlvInfo(new RegisterRequestCodeTlv(), false));
	}

	public List<LinkId> getLinkIdentifierListTlv() {
		return ((LinkIdentifierListTlv) tlvList.get(0).getTlv()).getValue();
	}

	public void setLinkIdentifierListTlv(List<LinkId> value) {
		((LinkIdentifierListTlv) tlvList.get(0).getTlv()).setValue(value);
	}

	public RegRequestCode getRegisterRequestCodeTlv() {
		return ((RegisterRequestCodeTlv) tlvList.get(1).getTlv()).getValue();
	}

	public void setRegisterRequestCodeTlv(RegRequestCode value) {
		((RegisterRequestCodeTlv) tlvList.get(1).getTlv()).setValue(value);
	}

}
