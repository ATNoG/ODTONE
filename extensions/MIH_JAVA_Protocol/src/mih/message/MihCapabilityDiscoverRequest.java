//==============================================================================
// Brief   : MIH_Capablity_Discover Request Message
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

import mih.tlvs.LinkAddressListTlv;
import mih.tlvs.MbbHandoverSupportTlv;
import mih.tlvs.MihCommandListTlv;
import mih.tlvs.MihEventListTlv;
import mih.tlvs.MiisQueryTypeListTlv;
import mih.tlvs.TransportOptionListTlv;
import mih.types.Serializeable;
import mih.types.basic.List;
import mih.types.capabilities.MbbHoSupp;
import mih.types.capabilities.MihCmdList;
import mih.types.capabilities.MihEvtList;
import mih.types.capabilities.MihIqTypeLst;
import mih.types.capabilities.MihTransLst;
import mih.types.capabilities.NetTypeAddr;

public class MihCapabilityDiscoverRequest extends Message implements
		Serializeable {

	public MihCapabilityDiscoverRequest() {
		super();
		mid = MIH_Capability_Discover_request;
		tlvList.add(new TlvInfo(new LinkAddressListTlv(), true));
		tlvList.add(new TlvInfo(new MihEventListTlv(), true));
		tlvList.add(new TlvInfo(new MihCommandListTlv(), true));
		tlvList.add(new TlvInfo(new MiisQueryTypeListTlv(), true));
		tlvList.add(new TlvInfo(new TransportOptionListTlv(), true));
		tlvList.add(new TlvInfo(new MbbHandoverSupportTlv(), true));
	}

	public MihCapabilityDiscoverRequest(int version, boolean ack_req,
			boolean ack_rsp, boolean uir, boolean m, int fn, boolean rsvd1,
			int rsvd2, int tid) {
		super(version, ack_req, ack_rsp, uir, m, fn, rsvd1,
				MIH_Capability_Discover_request, rsvd2, tid);
		tlvList.add(new TlvInfo(new LinkAddressListTlv(), true));
		tlvList.add(new TlvInfo(new MihEventListTlv(), true));
		tlvList.add(new TlvInfo(new MihCommandListTlv(), true));
		tlvList.add(new TlvInfo(new MiisQueryTypeListTlv(), true));
		tlvList.add(new TlvInfo(new TransportOptionListTlv(), true));
		tlvList.add(new TlvInfo(new MbbHandoverSupportTlv(), true));
	}

	public boolean hasLinkAddressListTlv() {
		return tlvList.get(0).getTlv().isInitialized();
	}

	public List<NetTypeAddr> getLinkAddressListTlv() {
		return ((LinkAddressListTlv) tlvList.get(0).getTlv()).getValue();
	}

	public void setLinkAddressListTlv(List<NetTypeAddr> value) {
		((LinkAddressListTlv) tlvList.get(0).getTlv()).setValue(value);
	}

	public boolean hasMihEventListTlv() {
		return tlvList.get(1).getTlv().isInitialized();
	}

	public MihEvtList getMihEventListTlv() {
		return ((MihEventListTlv) tlvList.get(1).getTlv()).getValue();
	}

	public void setMihEventListTlv(MihEvtList value) {
		((MihEventListTlv) tlvList.get(1).getTlv()).setValue(value);
	}

	public boolean hasMihCommandListTlv() {
		return tlvList.get(2).getTlv().isInitialized();
	}

	public MihCmdList getMihCommandListTlv() {
		return ((MihCommandListTlv) tlvList.get(2).getTlv()).getValue();
	}

	public void setMihCommandListTlv(MihCmdList value) {
		((MihCommandListTlv) tlvList.get(2).getTlv()).setValue(value);
	}

	public boolean hasMiisQueryTypeListTlv() {
		return tlvList.get(3).getTlv().isInitialized();
	}

	public MihIqTypeLst getMiisQueryTypeListTlv() {
		return ((MiisQueryTypeListTlv) tlvList.get(3).getTlv()).getValue();
	}

	public void setMiisQueryTypeListTlv(MihIqTypeLst value) {
		((MiisQueryTypeListTlv) tlvList.get(3).getTlv()).setValue(value);
	}

	public boolean hasTransportOptionListTlv() {
		return tlvList.get(4).getTlv().isInitialized();
	}

	public MihTransLst getTransportOptionListTlv() {
		return ((TransportOptionListTlv) tlvList.get(4).getTlv()).getValue();
	}

	public void setTransportOptionListTlv(MihTransLst value) {
		((TransportOptionListTlv) tlvList.get(4).getTlv()).setValue(value);
	}

	public boolean hasMbbHandoverSupportTlv() {
		return tlvList.get(5).getTlv().isInitialized();
	}

	public List<MbbHoSupp> getMbbHandoverSupportTlv() {
		return ((MbbHandoverSupportTlv) tlvList.get(5).getTlv()).getValue();
	}

	public void setMbbHandoverSupportTlv(List<MbbHoSupp> value) {
		((MbbHandoverSupportTlv) tlvList.get(5).getTlv()).setValue(value);
	}
}
