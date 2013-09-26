//==============================================================================
// Brief   : MIH_Net_HO_Candidate_Query Indication Message
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

import mih.types.general.Boolean;
import mih.tlvs.ListOfLinkPoaListTlv;
import mih.tlvs.QueryResourceReportFlagTlv;
import mih.types.Serializeable;
import mih.types.basic.List;
import mih.types.links.LinkPoaList;

public class MihNetHoCandidateQueryIndication extends Message implements
		Serializeable {

	public MihNetHoCandidateQueryIndication() {
		super();
		mid = MIH_Net_HO_Candidate_Query_indication;
		tlvList.add(new TlvInfo(new ListOfLinkPoaListTlv(), false));
		tlvList.add(new TlvInfo(new QueryResourceReportFlagTlv(), false));
	}

	public MihNetHoCandidateQueryIndication(int version, boolean ack_req,
			boolean ack_rsp, boolean uir, boolean m, int fn, boolean rsvd1,
			int rsvd2, int tid) {
		super(version, ack_req, ack_rsp, uir, m, fn, rsvd1,
				MIH_Net_HO_Candidate_Query_indication, rsvd2, tid);
		tlvList.add(new TlvInfo(new ListOfLinkPoaListTlv(), false));
		tlvList.add(new TlvInfo(new QueryResourceReportFlagTlv(), false));
	}

	public List<LinkPoaList> getListOfLinkPoaListTlv() {
		return ((ListOfLinkPoaListTlv)tlvList.get(0).getTlv()).getValue();
	}

	public void setListOfLinkPoaListTlv(List<LinkPoaList> value) {
		((ListOfLinkPoaListTlv)tlvList.get(0).getTlv()).setValue(value);
	}

	public Boolean getQueryResourceReportFlagTlv() {
		return ((QueryResourceReportFlagTlv)tlvList.get(1).getTlv()).getValue();
	}

	public void setQueryResourceReportFlagTlv(Boolean value) {
		((QueryResourceReportFlagTlv)tlvList.get(1).getTlv()).setValue(value);
	}
}
