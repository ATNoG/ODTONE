//==============================================================================
// Brief   : MIH_Link_Actions Confirm Message
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

import mih.tlvs.LinkActionResultListTlv;
import mih.tlvs.StatusTlv;
import mih.types.Serializeable;
import mih.types.basic.List;
import mih.types.general.Status;
import mih.types.links.LinkActionRsp;

public class MihLinkActionsResponse extends Message implements
		Serializeable {

	public MihLinkActionsResponse() {
		super();
		mid = MIH_Link_Actions_response;
		tlvList.add(new TlvInfo(new StatusTlv(), false));
		tlvList.add(new TlvInfo(new LinkActionResultListTlv(), true));
	}

	public MihLinkActionsResponse(int version, boolean ack_req,
			boolean ack_rsp, boolean uir, boolean m, int fn, boolean rsvd1,
			int rsvd2, int tid) {
		super(version, ack_req, ack_rsp, uir, m, fn, rsvd1,
				MIH_Link_Actions_response, rsvd2, tid);
		tlvList.add(new TlvInfo(new StatusTlv(), false));
		tlvList.add(new TlvInfo(new LinkActionResultListTlv(), true));
	}

	public Status getStatusTlv() {
		return ((StatusTlv) tlvList.get(0).getTlv()).getValue();
	}

	public void setStatusTlv(Status value) {
		((StatusTlv) tlvList.get(0).getTlv()).setValue(value);
	}

	public boolean hasLinkActionResultListTlv() {
		return tlvList.get(1).getTlv().isInitialized();
	}

	public List<LinkActionRsp> getLinkActionResultListTlv() {
		return ((LinkActionResultListTlv) tlvList.get(1).getTlv()).getValue();
	}

	public void setLinkActionResultListTlv(List<LinkActionRsp> value) {
		((LinkActionResultListTlv) tlvList.get(1).getTlv()).setValue(value);
	}
}
