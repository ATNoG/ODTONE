//==============================================================================
// Brief   : MIH_N2N_HO_Query_Resources Response Message
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

import mih.tlvs.PreferredLinkListTlv;
import mih.tlvs.ResourceStatusTlv;
import mih.tlvs.StatusTlv;
import mih.types.Serializeable;
import mih.types.basic.List;
import mih.types.general.Status;
import mih.types.handover.RqResult;
import mih.types.links.LinkResStatus;

public class MihN2nHoQueryResourcesResponse extends Message implements
		Serializeable {

	public MihN2nHoQueryResourcesResponse() {
		super();
		mid = MIH_N2N_HO_Query_Resoures_response;
		tlvList.add(new TlvInfo(new StatusTlv(), false));
		tlvList.add(new TlvInfo(new ResourceStatusTlv(), true));
		tlvList.add(new TlvInfo(new PreferredLinkListTlv(), true));
	}

	public MihN2nHoQueryResourcesResponse(int version, boolean ack_req,
			boolean ack_rsp, boolean uir, boolean m, int fn, boolean rsvd1,
			int rsvd2, int tid) {
		super(version, ack_req, ack_rsp, uir, m, fn, rsvd1,
				MIH_N2N_HO_Query_Resoures_response, rsvd2, tid);
		tlvList.add(new TlvInfo(new StatusTlv(), false));
		tlvList.add(new TlvInfo(new ResourceStatusTlv(), true));
		tlvList.add(new TlvInfo(new PreferredLinkListTlv(), true));
	}

	public Status getStatusTlv() {
		return ((StatusTlv) tlvList.get(0).getTlv()).getValue();
	}

	public void setStatusTlv(Status value) {
		((StatusTlv) tlvList.get(0).getTlv()).setValue(value);
	}

	public boolean hasResourceStatusTlv() {
		return tlvList.get(1).getTlv().isInitialized();
	}

	public LinkResStatus getResourceStatusTlv() {
		return ((ResourceStatusTlv) tlvList.get(1).getTlv()).getValue();
	}

	public void setResourceStatusTlv(LinkResStatus value) {
		((ResourceStatusTlv) tlvList.get(1).getTlv()).setValue(value);
	}

	public boolean hasPreferredLinkListTlv() {
		return tlvList.get(2).getTlv().isInitialized();
	}

	public List<RqResult> getPreferredLinkListTlv() {
		return ((PreferredLinkListTlv) tlvList.get(2).getTlv()).getValue();
	}

	public void setPreferredLinkListTlv(List<RqResult> value) {
		((PreferredLinkListTlv) tlvList.get(2).getTlv()).setValue(value);
	}
}
