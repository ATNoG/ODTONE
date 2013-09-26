//==============================================================================
// Brief   : MIH Command List TLV
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

package mih.tlvs;

import mih.types.basic.UnsignedInteger8;
import mih.types.capabilities.MihCmdList;

public class MihCommandListTlv extends Tlv<MihCmdList> {

	public MihCommandListTlv() {
		super(new UnsignedInteger8(6));
		value = new MihCmdList();
	}

	public MihCommandListTlv(MihCmdList value) {
		super(new UnsignedInteger8(6), value);
	}
}
