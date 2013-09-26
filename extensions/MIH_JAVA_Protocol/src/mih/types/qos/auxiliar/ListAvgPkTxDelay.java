//==============================================================================
// Brief   : LIST(AVG_PK_TX_DELAY) Data Type
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

package mih.types.qos.auxiliar;

import mih.types.Serializeable;
import mih.types.basic.List;
import mih.types.qos.AvgPkTxDelay;

public class ListAvgPkTxDelay extends List<AvgPkTxDelay> implements Serializeable {

	public ListAvgPkTxDelay() {
		super(AvgPkTxDelay.class);
	}

	public ListAvgPkTxDelay(ListAvgPkTxDelay value) {
		super(value);
	}
}