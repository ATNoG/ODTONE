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
using System.Collections;
using System.Management;

using MIH.DataTypes;
using MIH.MIHProtocol;
using MIH.Utilities;

//using LINK_SAP_CS_80211.Connection.Message;
//using LINK_SAP_CS_80211.Connection.MIHProtocol;
//using LINK_SAP_CS_80211.Events.EventClasses;
//using LINK_SAP_CS_80211.Common.Tools;
//using LINK_SAP_CS_80211;

namespace LINK_SAP_CS_80211.Common.Events
{
    class Subscriptions
    {

        public static Link_Event_List List = new Link_Event_List();


        public static void Unsubscribe (Link_Event_List unsubList)
        {
            BitArray oldList = List.toBitArray();
            BitArray unsubs = unsubList.toBitArray();
            BitArray newList = new BitArray(32);
            for (int i = 0; i < newList.Count; i++)
                newList[i] = !unsubs[i] & oldList[i];
            List = new Link_Event_List(newList);
        }

        public static void Subscribe(Link_Event_List subList)
        {
            BitArray oldList = List.toBitArray();
            BitArray subs = subList.toBitArray();
            BitArray newList = new BitArray(32);
            for (int i = 0; i < newList.Count; i++)
                newList[i] = subs[i] | oldList[i];
            List = new Link_Event_List(newList);
        }

    }
}
