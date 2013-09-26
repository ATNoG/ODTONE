//==============================================================================
// Brief   : CURR_PREF Data Type
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

package mih.types.informationservicequery;

import mih.types.Serializeable;
import mih.types.informationelements.CostCurr;

public class CurrPref extends CostCurr implements Serializeable {

	public CurrPref(int[] value) {
		super(value);
	}

	public CurrPref(CurrPref value) {
		super(value);
	}

	public CurrPref() {
		super();
	}
}