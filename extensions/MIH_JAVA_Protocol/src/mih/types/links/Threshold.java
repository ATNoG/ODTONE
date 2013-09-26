//==============================================================================
// Brief   : THRESHOLD Data Type
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

package mih.types.links;

import mih.types.Serializeable;
import mih.types.basic.Sequence;

public class Threshold
		extends
		Sequence<ThresholdVal, ThresholdXDir, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull, Sequence.ObjectNull>
		implements Serializeable {

	public Threshold(ThresholdVal value, ThresholdXDir dir) {
		super(value, dir);
	}

	public Threshold(Threshold value) {
		super(value.getValue(), value.getDir());
	}

	public Threshold() {
		super(new ThresholdVal(), new ThresholdXDir());
	}

	public ThresholdVal getValue() {
		return getA();
	}

	public void setType(ThresholdVal value) {
		setA(value);
	}

	public ThresholdXDir getDir() {
		return getB();
	}

	public void setAddr(ThresholdXDir dir) {
		setB(dir);
	}
}
