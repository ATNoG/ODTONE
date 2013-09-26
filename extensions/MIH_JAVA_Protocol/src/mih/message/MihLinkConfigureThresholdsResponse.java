//==============================================================================
// Brief   : MIH_Link_Configure_Thresholds Response Message
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

import mih.tlvs.ConfigureResponseListTlv;
import mih.tlvs.LinkIdentifierTlv;
import mih.tlvs.StatusTlv;
import mih.types.Serializeable;
import mih.types.basic.List;
import mih.types.general.Status;
import mih.types.links.LinkCfgStatus;
import mih.types.links.LinkTupleId;

public class MihLinkConfigureThresholdsResponse extends Message implements
		Serializeable {

	public MihLinkConfigureThresholdsResponse() {
		super();
		mid = MIH_Link_Configure_Thresholds_response;
		tlvList.add(new TlvInfo(new StatusTlv(), false));
		tlvList.add(new TlvInfo(new LinkIdentifierTlv(), false));
		tlvList.add(new TlvInfo(new ConfigureResponseListTlv(), true));
	}

	public MihLinkConfigureThresholdsResponse(int version, boolean ack_req,
			boolean ack_rsp, boolean uir, boolean m, int fn, boolean rsvd1,
			int rsvd2, int tid) {
		super(version, ack_req, ack_rsp, uir, m, fn, rsvd1,
				MIH_Link_Configure_Thresholds_response, rsvd2, tid);
		tlvList.add(new TlvInfo(new StatusTlv(), false));
		tlvList.add(new TlvInfo(new LinkIdentifierTlv(), false));
		tlvList.add(new TlvInfo(new ConfigureResponseListTlv(), true));
	}

	public Status getStatusTlv() {
		return ((StatusTlv) tlvList.get(0).getTlv()).getValue();
	}

	public void setStatusTlv(Status value) {
		((StatusTlv) tlvList.get(0).getTlv()).setValue(value);
	}

	public LinkTupleId getLinkIdentifierTlv() {
		return ((LinkIdentifierTlv) tlvList.get(1).getTlv()).getValue();
	}

	public void setLinkIdentifierTlv(LinkTupleId value) {
		((LinkIdentifierTlv) tlvList.get(1).getTlv()).setValue(value);
	}

	public boolean hasConfigureResponseListTlv() {
		return tlvList.get(2).getTlv().isInitialized();
	}

	public List<LinkCfgStatus> getConfigureResponseListTlv() {
		return ((ConfigureResponseListTlv) tlvList.get(2).getTlv()).getValue();
	}

	public void setConfigureResponseListTlv(List<LinkCfgStatus> value) {
		((ConfigureResponseListTlv) tlvList.get(2).getTlv()).setValue(value);
	}
}
