//==============================================================================
// Brief   : Class representing a Protocol.cs entity
// Authors : Marcelo Génio <marcelog@ua.pt>
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

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using MIH.DataTypes;
using MIH.MIHProtocol;

namespace LINK_SAP_CS_80211.Information
{
    public class MiscData
    {
        /// <summary>
        /// Used to store a Message and its corresponding Link_Action_Response that is waiting on the results of a Scan_Complete notification.
        /// </summary>
        public static Dictionary<Message, Link_Action_Response> PendingLinkActionResponses
        { get { return pla; } set { pla = value; } }

        private static Dictionary<Message, Link_Action_Response> pla = new Dictionary<Message, Link_Action_Response>();

    }
}
