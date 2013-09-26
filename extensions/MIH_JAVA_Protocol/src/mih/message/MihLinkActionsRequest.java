//==============================================================================
// Brief   : MIH_Link_Actions Request Message
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

import mih.tlvs.LinkActionListTlv;
import mih.types.Serializeable;
import mih.types.basic.List;
import mih.types.links.LinkActionReq;

public class MihLinkActionsRequest extends Message implements
		Serializeable {

	public MihLinkActionsRequest() {
		super();
		mid = MIH_Link_Actions_request;
		tlvList.add(new TlvInfo(new LinkActionListTlv(), false));
	}

	public MihLinkActionsRequest(int version, boolean ack_req,
			boolean ack_rsp, boolean uir, boolean m, int fn, boolean rsvd1,
			int rsvd2, int tid) {
		super(version, ack_req, ack_rsp, uir, m, fn, rsvd1,
				MIH_Link_Actions_request, rsvd2, tid);
		tlvList.add(new TlvInfo(new LinkActionListTlv(), false));
	}

	public List<LinkActionReq> getLinkActionListTlv() {
		return ((LinkActionListTlv) tlvList.get(0).getTlv()).getValue();
	}

	public void setLinkActionListTlv(List<LinkActionReq> value) {
		((LinkActionListTlv) tlvList.get(0).getTlv()).setValue(value);
	}

}
