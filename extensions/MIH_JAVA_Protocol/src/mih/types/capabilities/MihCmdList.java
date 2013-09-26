//==============================================================================
// Brief   : MIH_CMD_LIST Data Type
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

package mih.types.capabilities;

import mih.types.Serializeable;
import mih.types.basic.Bitmap;

public class MihCmdList extends Bitmap implements Serializeable {

	public enum MihCmdListEnum {
		 MihLinkGetParameters(0),
		 MihLinkConfigureThresholds(1),
		 MihLinkActions(2),
		 MihNetHoCandidateQuery(3),
		 MihNetHoCommit(3),
		 MihN2NHoQueryResources(3),
		 MihN2NHoCommit(3),
		 MihN2NHoComplete(3),
		 MihMnHoCandidateQuery(4),
		 MihMnHoCommit(4),
		 MihMnHoComplete(4);

		 private MihCmdListEnum(int id) {
			 this.id = id;
		 }

		 public final int id;
	}

	public MihCmdList(MihCmdListEnum value) {
		super(32);
		set(value.id);
	}

	public MihCmdList(MihCmdList value) {
		super(value);
	}

	public MihCmdList() {
		super(32);
	}
}