//==============================================================================
// Brief   : Class representing a Protocol.cs entity
// Authors : Marcelo Génio <marcelog@ua.pt>
//           Rui Fonseca <ruimfonseca@av.it.pt>
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

namespace LINK_SAP_CS_80211.Capabilities
{
    /// <summary>
    /// This class contains all the methods to handle Capabilities requests.
    /// </summary>
    class CapabilitiesHandler
    {
        public static Link_Event_List SupportedEventList
        {
            get
            {
                Link_Event_List lel = new Link_Event_List();
                lel.Link_Detected = true;
                lel.Link_Down = true;
                lel.Link_Going_Down = false;
                lel.Link_Handover_Complete = false;
                lel.Link_Handover_Imminent = false;
                lel.Link_Parameters_Report = true;
                lel.Link_PDU_Transmit_Status = false;
                lel.Link_Up = true;
                return lel;
            }
        }

        public static Link_CMD_List SupportedCommandsList
        {
            get
            {
                Link_CMD_List lcl = new Link_CMD_List();
                lcl.Link_Action = true;
                lcl.Link_Configure_Thresholds = true;
                lcl.Link_Event_Subscribe = true;
                lcl.Link_Event_Unsubscribe = true;
                lcl.Link_Get_Parameters = true;
                return lcl;
            }
        }
    }
}
