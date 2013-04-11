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
using System.Threading;
using System.Collections;
using System.ComponentModel;


using MIH.DataTypes;
using MIH.MIHProtocol;
using MIH_Connection.Link;
//using LINK_SAP_CS_80211.Common.Events;
//using LINK_SAP_CS_80211.Events.EventClasses;
//using LINK_SAP_CS_80211.Common.Registration;
//using LINK_SAP_CS_80211.Common.Capabilities;
//using LINK_SAP_CS_80211.Connection.Message;
using LINK_SAP_CS_80211.Connection.MIHProtocol;

namespace LINK_SAP_CS_80211.Common
{
    class LinkSAP80211
    {
        ConnectionHelper connHelper;

        public LinkSAP80211(string GUID, ushort rcvPort, System.Net.IPAddress mihAddr)
        {
            Information.GenericInfo.InterfaceGUID = GUID;

            Init(rcvPort, mihAddr);

            #region # Tests #############################

            #region Parameters Testing

            Parameters.PeriodicParameters periodicParams = new Parameters.PeriodicParameters();

            //// A link Configuration parameter to subscribe periodic thresholds
            //LINK_SAP_CSHARP.Events.EventClasses.Link_Cfg_Param aLinkCfg = new LINK_SAP_CSHARP.Events.EventClasses.Link_Cfg_Param();

            //// Param Type
            //aLinkCfg.Link_Param_Type = LINK_SAP_CSHARP.Events.EventClasses.Link_Param_Types.LINK_PARAM_GEN;
            //// Param Subtype 0=DataRate, 1=SignalStrength, etc
            //aLinkCfg.Link_Param_SubType = (int)LINK_SAP_CSHARP.Events.EventClasses.LINK_PARAM_GEN_SUBTYPES.DataRate;
            //// Timer Interval in miliseconds
            //aLinkCfg.Timer_Interval = 2000;
            //// Threshold Action (One-Shot, normal, etc)
            //aLinkCfg.Th_Action = LINK_SAP_CSHARP.Events.EventClasses.TH_Action.NORMAL_THRESHOLD;
            //// Threshold EventList, can be null
            //aLinkCfg.ThresholdList = null;

            //// The registration of the link configuration parameter
            //periodicParams.RegisterLinkCfgParam(aLinkCfg);



            //LINK_SAP_CSHARP.Events.EventClasses.Link_Cfg_Param anotherLinkCfg = new LINK_SAP_CSHARP.Events.EventClasses.Link_Cfg_Param(LINK_SAP_CSHARP.Events.EventClasses.Link_Param_Types.LINK_PARAM_GEN,
            //    1, 500, LINK_SAP_CSHARP.Events.EventClasses.TH_Action.NORMAL_THRESHOLD, null);


            //periodicParams.RegisterLinkCfgParam(anotherLinkCfg);

            //aLinkCfg.Th_Action = LINK_SAP_CSHARP.Events.EventClasses.TH_Action.CANCEL_THRESHOLD;

            //periodicParams.RegisterLinkCfgParam(aLinkCfg);

            ////////////////////

            //Parameters.ParametersHandler ph = new Parameters.ParametersHandler();

            //List<Link_Cfg_Param> EventList = new List<Link_Cfg_Param>();

            //Link_Cfg_Param lcp = new Link_Cfg_Param();

            //lcp.Link_Param_Type = (int)Link_Param_Type.LINK_PARAM_GEN;
            //lcp.Link_Param_SubType = (int)LINK_PARAM_GEN_SUBTYPES.DataRate;

            //lcp.Timer_Interval = 0;

            //lcp.ThresholdList = new List<Threshold>();

            //lcp.ThresholdList.Add(new Threshold(54000000,Threshold_X_Dir.BELOW_THRESHOLD));
            //lcp.ThresholdList.Add(new Threshold(20000000, Threshold_X_Dir.ABOVE_THRESHOLD));

            //EventList.Add(lcp);

            //ph.linkConfigureThresholds(EventList);

            #endregion

            #region Actions Testing

            //Actions.ActionsHandler ah = new Actions.ActionsHandler();

            //LINK_SAP_CSHARP.Actions.ActionClasses.Link_Action_Request larPowerDown = new LINK_SAP_CSHARP.Actions.ActionClasses.Link_Action_Request();

            //larPowerDown.ExecutionDelay = 0;
            //larPowerDown.LinkAction = LINK_SAP_CSHARP.Actions.ActionClasses.Actions.LINK_POWER_DOWN;

            //ah.registerLinkActionRequest(larPowerDown);

            //LINK_SAP_CSHARP.Actions.ActionClasses.Link_Action_Request larPowerUp = new LINK_SAP_CSHARP.Actions.ActionClasses.Link_Action_Request();

            //larPowerUp.ExecutionDelay = 2000;
            //larPowerUp.LinkAction = LINK_SAP_CSHARP.Actions.ActionClasses.Actions.LINK_POWER_UP;

            //ah.registerLinkActionRequest(larPowerUp);

            //LINK_SAP_CSHARP.Actions.ActionClasses.Link_Action_Request larDisconnect = new LINK_SAP_CSHARP.Actions.ActionClasses.Link_Action_Request();

            //larDisconnect.ExecutionDelay = 2000;
            //larDisconnect.LinkAction = LINK_SAP_CSHARP.Actions.ActionClasses.Actions.LINK_DISCONNECT;

            //ah.registerLinkActionRequest(larDisconnect);

            #endregion

            #region Events Testing

            //EventsHandler eh = new EventsHandler();

            //Link_Event_Subscribe_Request lesr = new Link_Event_Subscribe_Request();

            //bool[] linkEventListInBool = new bool[32]
            //{
            //    false, //Link_Detected
            //    true,  //Link_Up
            //    true, //Link_Down
            //    false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };

            //lesr.LinkEventList = new BitArray(linkEventListInBool);

            //eh.registerSubscriptionRequest(lesr);

            #endregion

            #endregion

        }

        private void Init(ushort rcvPort, System.Net.IPAddress mihAddr)
        {
            Link_Register_Indication lri = new Link_Register_Indication(
                Link_Type.Wireless_IEEE80211, //LinkType
                Link_Addr.Address_Type.MAC_ADDR, //LinkAdrressType
                Information.GenericInfo.Interface.GetPhysicalAddress().ToString()); //LinkAddressValue

            //Console.WriteLine(lri);

            connHelper = new ConnectionHelper(rcvPort, mihAddr);
            //connHelper.Send(lri.GetMessage());
            ID myLinkID = new ID(new OctetString(Information.GenericInfo.myID));
            ID mihfID = new ID(new OctetString(Information.GenericInfo.mihfID));

            while (true)
            {
                //TODO colocar a recepção das mensagens aqui.
                //messageHandler.HandleMessage(m);

                byte[] messageAsBytes = connHelper.Receive();

                //Console.WriteLine("!Received: " + messageAsBytes.Length + " bytes from local MIHF.");

                Message m = new Message(messageAsBytes);
                if (Program.MESSAGE_DETAILS)
                {
                    Console.WriteLine("Received message: ("+m.MIHHeader.MID.AID+")");
                    Connection.MIHProtocol.PacketReader.PrintMessage(m);
                }
                //Console.WriteLine("AID: "+m.MIHHeader.MID.AID);
                //Console.WriteLine("Opcode: " + m.MIHHeader.MID.OpCode);
                //Console.WriteLine("SID: " + m.MIHHeader.MID.SID);
                MessageHandler.HandleMessage(m);
            }
        }
    }
}
