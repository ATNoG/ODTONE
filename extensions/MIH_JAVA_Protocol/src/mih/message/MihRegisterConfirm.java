//==============================================================================
// Brief   : MIH_Register Confirm Message
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

import mih.tlvs.StatusTlv;
import mih.tlvs.ValidTimeIntervalTlv;
import mih.types.Serializeable;
import mih.types.basic.UnsignedInteger32;
import mih.types.general.Status;

public class MihRegisterConfirm extends Message implements
		Serializeable {

	public MihRegisterConfirm() {
		super();
		mid = MIH_Register_confirm;
		tlvList.add(new TlvInfo(new StatusTlv(), false));
		tlvList.add(new TlvInfo(new ValidTimeIntervalTlv(), true));
	}

	public MihRegisterConfirm(int version, boolean ack_req,
			boolean ack_rsp, boolean uir, boolean m, int fn, boolean rsvd1,
			int rsvd2, int tid) {
		super(version, ack_req, ack_rsp, uir, m, fn, rsvd1,
				MIH_Register_confirm, rsvd2, tid);
		tlvList.add(new TlvInfo(new StatusTlv(), false));
		tlvList.add(new TlvInfo(new ValidTimeIntervalTlv(), true));
	}

	public Status getStatusTlv() {
		return ((StatusTlv) tlvList.get(0).getTlv()).getValue();
	}

	public void setStatusTlv(Status value) {
		((StatusTlv) tlvList.get(0).getTlv()).setValue(value);
	}

	public boolean hasValidTimeIntervalTlv() {
		return tlvList.get(1).getTlv().isInitialized();
	}

	public UnsignedInteger32 getValidTimeIntervalTlv() {
		return ((ValidTimeIntervalTlv) tlvList.get(1).getTlv()).getValue();
	}

	public void setValidTimeIntervalTlv(UnsignedInteger32 value) {
		((ValidTimeIntervalTlv) tlvList.get(1).getTlv()).setValue(value);
	}

}
