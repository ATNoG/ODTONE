//==============================================================================
// Brief   : MIH_Get_Information Response Message
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

import mih.tlvs.InfoResponseBinaryDataListTlv;
import mih.tlvs.InfoResponseRdfDataListTlv;
import mih.tlvs.InfoResponseRdfSchemaListTlv;
import mih.tlvs.InfoResponseRdfSchemaUrlListTlv;
import mih.tlvs.StatusTlv;
import mih.types.Serializeable;
import mih.types.basic.List;
import mih.types.general.Status;
import mih.types.informationservicequery.IrBinData;
import mih.types.informationservicequery.IrRdfData;
import mih.types.informationservicequery.IrRdfSchm;
import mih.types.informationservicequery.IrSchmUrl;

public class MihGetInformationResponse extends Message implements
		Serializeable {

	public MihGetInformationResponse() {
		super();
		mid = MIH_Get_Information_response;
		tlvList.add(new TlvInfo(new StatusTlv(), false));
		tlvList.add(new TlvInfo(new InfoResponseBinaryDataListTlv(), true));
		tlvList.add(new TlvInfo(new InfoResponseRdfDataListTlv(), true));
		tlvList.add(new TlvInfo(new InfoResponseRdfSchemaUrlListTlv(), true));
		tlvList.add(new TlvInfo(new InfoResponseRdfSchemaListTlv(), true));
	}

	public MihGetInformationResponse(int version, boolean ack_req,
			boolean ack_rsp, boolean uir, boolean m, int fn, boolean rsvd1,
			int rsvd2, int tid) {
		super(version, ack_req, ack_rsp, uir, m, fn, rsvd1,
				MIH_Get_Information_response, rsvd2, tid);
		tlvList.add(new TlvInfo(new StatusTlv(), false));
		tlvList.add(new TlvInfo(new InfoResponseBinaryDataListTlv(), true));
		tlvList.add(new TlvInfo(new InfoResponseRdfDataListTlv(), true));
		tlvList.add(new TlvInfo(new InfoResponseRdfSchemaUrlListTlv(), true));
		tlvList.add(new TlvInfo(new InfoResponseRdfSchemaListTlv(), true));
	}

	public Status getStatusTlv() {
		return ((StatusTlv) tlvList.get(0).getTlv()).getValue();
	}

	public void setStatusTlv(Status value) {
		((StatusTlv) tlvList.get(0).getTlv()).setValue(value);
	}

	public boolean hasInfoResponseBinaryDataListTlv() {
		return tlvList.get(1).getTlv().isInitialized();
	}

	public List<IrBinData> getInfoResponseBinaryDataListTlv() {
		return ((InfoResponseBinaryDataListTlv) tlvList.get(1).getTlv()).getValue();
	}

	public void setInfoResponseBinaryDataListTlv(List<IrBinData> value) {
		((InfoResponseBinaryDataListTlv) tlvList.get(1).getTlv()).setValue(value);
	}

	public boolean hasInfoResponseRdfDataListTlv() {
		return tlvList.get(2).getTlv().isInitialized();
	}

	public List<IrRdfData> getInfoResponseRdfDataListTlv() {
		return ((InfoResponseRdfDataListTlv) tlvList.get(2).getTlv()).getValue();
	}

	public void setInfoResponseRdfDataListTlv(List<IrRdfData> value) {
		((InfoResponseRdfDataListTlv) tlvList.get(2).getTlv()).setValue(value);
	}

	public boolean hasInfoResponseRdfSchemaUrlListTlv() {
		return tlvList.get(3).getTlv().isInitialized();
	}

	public List<IrSchmUrl> getInfoResponseRdfSchemaUrlListTlv() {
		return ((InfoResponseRdfSchemaUrlListTlv) tlvList.get(3).getTlv()).getValue();
	}

	public void setInfoResponseRdfSchemaUrlListTlv(List<IrSchmUrl> value) {
		((InfoResponseRdfSchemaUrlListTlv) tlvList.get(3).getTlv()).setValue(value);
	}

	public boolean hasInfoResponseRdfSchemaListTlv() {
		return tlvList.get(4).getTlv().isInitialized();
	}

	public List<IrRdfSchm> getInfoResponseRdfSchemaListTlv() {
		return ((InfoResponseRdfSchemaListTlv) tlvList.get(4).getTlv()).getValue();
	}

	public void setInfoResponseRdfSchemaListTlv(List<IrRdfSchm> value) {
		((InfoResponseRdfSchemaListTlv) tlvList.get(4).getTlv()).setValue(value);
	}
}
