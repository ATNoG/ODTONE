//==============================================================================
// Brief   : MIH_Link_Detected Indication Message
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

import mih.tlvs.LinkDetectedInfoListTlv;
import mih.types.Serializeable;
import mih.types.basic.List;
import mih.types.capabilities.LinkDetInfo;

public class MihLinkDetectedIndication extends Message implements
		Serializeable {

	public MihLinkDetectedIndication() {
		super();
		mid = MIH_Link_Detected_indication;
		tlvList.add(new TlvInfo(new LinkDetectedInfoListTlv(), false));
	}

	public MihLinkDetectedIndication(int version, boolean ack_req,
			boolean ack_rsp, boolean uir, boolean m, int fn, boolean rsvd1,
			int rsvd2, int tid) {
		super(version, ack_req, ack_rsp, uir, m, fn, rsvd1,
				MIH_Link_Detected_indication, rsvd2, tid);
		tlvList.add(new TlvInfo(new LinkDetectedInfoListTlv(), false));
	}

	public List<LinkDetInfo> getLinkDetectedInfoListTlv() {
		return ((LinkDetectedInfoListTlv) tlvList.get(0).getTlv()).getValue();
	}

	public void setLinkDetectedInfoListTlv(List<LinkDetInfo> value) {
		((LinkDetectedInfoListTlv) tlvList.get(0).getTlv()).setValue(value);
	}
}
