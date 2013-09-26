//==============================================================================
// Brief   : MIH_MN_HO_Candidate_Query Indication Message
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

import mih.tlvs.AccessRouterAddressTlv;
import mih.tlvs.DhcpServerAddressTlv;
import mih.tlvs.FaAddressTlv;
import mih.tlvs.HandoverResourceQueryListTlv;
import mih.tlvs.IpAddressConfigurationMethodsTlv;
import mih.tlvs.LinkIdentifierTlv;
import mih.tlvs.ListOfLinkPoaListTlv;
import mih.types.Serializeable;
import mih.types.address.IpAddr;
import mih.types.basic.List;
import mih.types.ipconfiguration.IpCfgMthds;
import mih.types.links.LinkPoaList;
import mih.types.links.LinkTupleId;
import mih.types.qos.QosList;

public class MihMnHoCandidateQueryIndication extends Message implements
		Serializeable {

	public MihMnHoCandidateQueryIndication() {
		super();
		mid = MIH_MN_HO_Candidate_Query_indication;
		tlvList.add(new TlvInfo(new LinkIdentifierTlv(), false));
		tlvList.add(new TlvInfo(new ListOfLinkPoaListTlv(), false));
		tlvList.add(new TlvInfo(new HandoverResourceQueryListTlv(), false));
		tlvList.add(new TlvInfo(new IpAddressConfigurationMethodsTlv(), true));
		tlvList.add(new TlvInfo(new DhcpServerAddressTlv(), true));
		tlvList.add(new TlvInfo(new FaAddressTlv(), true));
		tlvList.add(new TlvInfo(new AccessRouterAddressTlv(), true));
	}

	public MihMnHoCandidateQueryIndication(int version, boolean ack_req,
			boolean ack_rsp, boolean uir, boolean m, int fn, boolean rsvd1,
			int rsvd2, int tid) {
		super(version, ack_req, ack_rsp, uir, m, fn, rsvd1,
				MIH_MN_HO_Candidate_Query_indication, rsvd2, tid);
		tlvList.add(new TlvInfo(new LinkIdentifierTlv(), false));
		tlvList.add(new TlvInfo(new ListOfLinkPoaListTlv(), false));
		tlvList.add(new TlvInfo(new HandoverResourceQueryListTlv(), false));
		tlvList.add(new TlvInfo(new IpAddressConfigurationMethodsTlv(), true));
		tlvList.add(new TlvInfo(new DhcpServerAddressTlv(), true));
		tlvList.add(new TlvInfo(new FaAddressTlv(), true));
		tlvList.add(new TlvInfo(new AccessRouterAddressTlv(), true));
	}

	public LinkTupleId getLinkIdentifierTlv() {
		return ((LinkIdentifierTlv) tlvList.get(0).getTlv()).getValue();
	}

	public void setLinkIdentifierTlv(LinkTupleId value) {
		((LinkIdentifierTlv) tlvList.get(0).getTlv()).setValue(value);
	}

	public List<LinkPoaList> getListOfLinkPoaListTlv() {
		return ((ListOfLinkPoaListTlv) tlvList.get(1).getTlv()).getValue();
	}

	public void setListOfLinkPoaListTlv(List<LinkPoaList> value) {
		((ListOfLinkPoaListTlv) tlvList.get(1).getTlv()).setValue(value);
	}

	public QosList getHandoverResourceQueryListTlv() {
		return ((HandoverResourceQueryListTlv) tlvList.get(2).getTlv()).getValue();
	}

	public void setHandoverResourceQueryListTlv(QosList value) {
		((HandoverResourceQueryListTlv) tlvList.get(2).getTlv()).setValue(value);
	}

	public boolean hasIpAddressConfigurationMethodsTlv() {
		return tlvList.get(3).getTlv().isInitialized();
	}

	public IpCfgMthds getIpAddressConfigurationMethodsTlv() {
		return ((IpAddressConfigurationMethodsTlv) tlvList.get(3).getTlv()).getValue();
	}

	public void setIpAddressConfigurationMethodsTlv(IpCfgMthds value) {
		((IpAddressConfigurationMethodsTlv) tlvList.get(3).getTlv()).setValue(value);
	}

	public boolean hasDhcpServerAddressTlv() {
		return tlvList.get(4).getTlv().isInitialized();
	}

	public IpAddr getDhcpServerAddressTlv() {
		return ((DhcpServerAddressTlv) tlvList.get(4).getTlv()).getValue();
	}

	public void setDhcpServerAddressTlv(IpAddr value) {
		((DhcpServerAddressTlv) tlvList.get(4).getTlv()).setValue(value);
	}

	public boolean hasFaAddressTlv() {
		return tlvList.get(5).getTlv().isInitialized();
	}

	public IpAddr getFaAddressTlv() {
		return ((FaAddressTlv) tlvList.get(5).getTlv()).getValue();
	}

	public void setFaAddressTlv(IpAddr value) {
		((FaAddressTlv) tlvList.get(5).getTlv()).setValue(value);
	}

	public boolean hasAccessRouterAddressTlv() {
		return tlvList.get(6).getTlv().isInitialized();
	}

	public IpAddr getAccessRouterAddressTlv() {
		return ((AccessRouterAddressTlv) tlvList.get(6).getTlv()).getValue();
	}

	public void setAccessRouterAddressTlv(IpAddr value) {
		((AccessRouterAddressTlv) tlvList.get(6).getTlv()).setValue(value);
	}
}
