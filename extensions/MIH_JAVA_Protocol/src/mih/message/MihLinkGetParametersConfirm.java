//==============================================================================
// Brief   : MIH_Link_Get_Parameters Confirm Message
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

import mih.tlvs.DeviceStatesResponseListTlv;
import mih.tlvs.GetStatusResponseListTlv;
import mih.tlvs.StatusTlv;
import mih.types.Serializeable;
import mih.types.basic.List;
import mih.types.general.Status;
import mih.types.links.DevStatesRsp;
import mih.types.links.auxiliar.LinkIdLinkStatusRspSequence;

public class MihLinkGetParametersConfirm extends Message implements
		Serializeable {

	public MihLinkGetParametersConfirm() {
		super();
		mid = MIH_Link_Get_Parameters_confirm;
		tlvList.add(new TlvInfo(new StatusTlv(), false));
		tlvList.add(new TlvInfo(new DeviceStatesResponseListTlv(), true));
		tlvList.add(new TlvInfo(new GetStatusResponseListTlv(), true));
	}

	public MihLinkGetParametersConfirm(int version, boolean ack_req,
			boolean ack_rsp, boolean uir, boolean m, int fn, boolean rsvd1,
			int rsvd2, int tid) {
		super(version, ack_req, ack_rsp, uir, m, fn, rsvd1,
				MIH_Link_Get_Parameters_confirm, rsvd2, tid);
		tlvList.add(new TlvInfo(new StatusTlv(), false));
		tlvList.add(new TlvInfo(new DeviceStatesResponseListTlv(), true));
		tlvList.add(new TlvInfo(new GetStatusResponseListTlv(), true));
	}

	public Status getStatusTlv() {
		return ((StatusTlv) tlvList.get(0).getTlv()).getValue();
	}

	public void setStatusTlv(Status value) {
		((StatusTlv) tlvList.get(0).getTlv()).setValue(value);
	}

	public boolean hasDeviceStatesResponseListTlv() {
		return tlvList.get(1).getTlv().isInitialized();
	}

	public List<DevStatesRsp> getDeviceStatesResponseListTlv() {
		return ((DeviceStatesResponseListTlv) tlvList.get(1).getTlv()).getValue();
	}

	public void setDeviceStatesResponseListTlv(List<DevStatesRsp> value) {
		((DeviceStatesResponseListTlv) tlvList.get(1).getTlv()).setValue(value);
	}

	public boolean hasGetStatusResponseListTlv() {
		return tlvList.get(2).getTlv().isInitialized();
	}

	public List<LinkIdLinkStatusRspSequence> getGetStatusResponseListTlv() {
		return ((GetStatusResponseListTlv) tlvList.get(2).getTlv()).getValue();
	}

	public void setGetStatusResponseListTlv(List<LinkIdLinkStatusRspSequence> value) {
		((GetStatusResponseListTlv) tlvList.get(2).getTlv()).setValue(value);
	}
}
