//==============================================================================
// Brief   : MIH_DeRegister Confirm Message
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
import mih.types.Serializeable;
import mih.types.general.Status;

public class MihDeRegisterConfirm extends Message implements
		Serializeable {

	public MihDeRegisterConfirm() {
		super();
		mid = MIH_DeRegister_confirm;
		tlvList.add(new TlvInfo(new StatusTlv(), false));
	}

	public MihDeRegisterConfirm(int version, boolean ack_req,
			boolean ack_rsp, boolean uir, boolean m, int fn, boolean rsvd1,
			int rsvd2, int tid) {
		super(version, ack_req, ack_rsp, uir, m, fn, rsvd1,
				MIH_DeRegister_confirm, rsvd2, tid);
		tlvList.add(new TlvInfo(new StatusTlv(), false));
	}

	public Status getStatusTlv() {
		return ((StatusTlv) tlvList.get(0).getTlv()).getValue();
	}
}
