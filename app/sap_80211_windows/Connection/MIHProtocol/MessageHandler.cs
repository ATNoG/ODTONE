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
using System.Threading;
using System.Net.NetworkInformation;
using System.Management;

using MIH.MIHProtocol;
using MIH.DataTypes;
using MIH_Connection.Link;
using MIH.Utilities;
using LINK_SAP_CS_80211.LINK_SAP_80211.Events;
using LINK_SAP_CS_80211.Common.Events;
using LINK_SAP_CS_80211.Information;
using LINK_SAP_CS_80211.Common.Actions;

namespace LINK_SAP_CS_80211.Connection.MIHProtocol
{
    class MessageHandler
    {

        #region Callbacks

        public static void LinkActionCallback(Object stateInfo)
        {
            Message m = (Message)stateInfo;
            ConnectionHelper ch = Program.toMihf;
            ushort transactionID = m.MIHHeader.TransactionID;
            Payload.TLVIterator it = m.Payload.GetTLVIterator();
            ID srcID = new ID(new OctetString(it.Next().Value));
            ID dstID = new ID(new OctetString(it.Next().Value));
            Link_Action_Request lar = new Link_Action_Request(MIHDeserializer.DeserializeLinkAction(it.Next()),
                                                    MIHDeserializer.DeserializeTimeInterval(it.Next()),
                                                    MIHDeserializer.DeserializePoA(it.Next()));

            Link_Action_Response laresp = new Link_Action_Response();
            laresp.Status = STATUS.UNSPECIFIED_FAILURE;
            laresp.Result = Link_Ac_Result.INCAPABLE;

            NativeWifi.WlanClient.WlanInterface iface = null;
            try { iface = Information.GenericInfo.WlanInterfaceInstance; }
            catch (Exception e) { /*nothing*/ }
            switch (lar.LinkAction.LinkAcType)
            {
                case Link_Ac_Type.LINK_DISCONNECT:
                    ActionsInterface.Action_Disconnect(ref laresp, ref iface);
                    break;
                case Link_Ac_Type.NONE:
                    Console.WriteLine("No action performed.");
                    laresp.Status = STATUS.SUCCESS;
                    laresp.Result = Link_Ac_Result.SUCCESS;
                    break;
                case Link_Ac_Type.LINK_POWER_DOWN:
                    ActionsInterface.Action_Power_Down(ref laresp, ref iface);
                    break;
                case Link_Ac_Type.LINK_POWER_UP:
                    ActionsInterface.Action_Power_Up(ref laresp, ref iface);
                    break;
                default:
                    throw new InvalidOperationException("Unsupported Operation");

            }
            laresp.ScanResults = new List<Link_Scan_Rsp>();
            if (lar.LinkAction.LinkAcAttr.Link_Scan)
            {
                ActionsInterface.Action_Scan(laresp, iface, m);//Message is sent inside this  branch, after the scan is complete.
            }
            else
                ch.Send(ResponseBuilders.Link_Action_Response_Builder(srcID, dstID, transactionID, laresp).ByteValue);

        }
        #endregion

        #region HandlerFunctions

        /// <summary>
        /// This method is called to handle a message containing a Link_Capability_Discover, returning to the MIHF the appropriate response.
        /// </summary>
        /// <param name="m">The received Link_Capability_Discover message object</param>
        public static void HandleCapabilityDiscover(Message m)
        {
            Payload.TLVIterator it = m.Payload.GetTLVIterator();
            ID srcID = new ID(new OctetString(it.Next().Value));
            ID dstID = new ID(new OctetString(it.Next().Value));
            Program.toMihf.Send(ResponseBuilders.Link_Capability_Discover_Response_Builder(dstID,srcID, STATUS.SUCCESS,
                Capabilities.CapabilitiesHandler.SupportedEventList,
                Capabilities.CapabilitiesHandler.SupportedCommandsList).ByteValue);
        }

        /// <summary>
        /// This method is called to handle a message containing a Link_Action_Request, and sets it to be called on a timer according to the delay parameter
        /// </summary>
        /// <param name="m">The Link_Action_Request message object</param>
        public static void HandleCommandLinkActions(Message m)
        {
            Payload.TLVIterator it = m.Payload.GetTLVIterator();
            it.Next();//srcID
            it.Next();//dstID
            it.Next();//eventlist
            int delay = MIHDeserializer.DeserializeTimeInterval(it.Next());

            Timer t = new Timer(LinkActionCallback, m, delay, Timeout.Infinite);
        }

        /// <summary>
        /// This method is called to handle a subscription request message
        /// </summary>
        /// <param name="m">The serialized subscription request message</param>
        public static void HandleSubscribe(Message m)
        {
            ConnectionHelper ch = Program.toMihf;
            ushort transactionID = m.MIHHeader.TransactionID;
            Payload.TLVIterator it = m.Payload.GetTLVIterator();
            ID srcID = new ID(new OctetString(it.Next().Value));
            ID dstID = new ID(new OctetString(it.Next().Value));
            Link_Event_Subscribe_Request lesr = new Link_Event_Subscribe_Request(MIHDeserializer.DeserializeLinkEventList(it.Next()));
            Subscriptions.Subscribe(lesr.EventList);
            Link_Event_Subscribe_Confirm lesc = new Link_Event_Subscribe_Confirm(STATUS.SUCCESS, lesr.EventList);
            ch.Send(ResponseBuilders.Event_Subscribe_Response_Builder(dstID, srcID, m.MIHHeader.TransactionID, lesc).ByteValue);
        }

        /// <summary>
        /// This method is called to handle an unsubscribe request message
        /// </summary>
        /// <param name="m">The serialized unsubscribe request message</param>
        public static void HandleUnsubscribe(Message m)
        {
            ConnectionHelper ch = Program.toMihf;
            ushort transactionID = m.MIHHeader.TransactionID;
            Payload.TLVIterator it = m.Payload.GetTLVIterator();
            ID srcID = new ID(new OctetString(it.Next().Value));
            ID dstID = new ID(new OctetString(it.Next().Value));
            Link_Event_Unsubscribe_Request leur = new Link_Event_Unsubscribe_Request(MIHDeserializer.DeserializeLinkEventList(it.Next()));
            Subscriptions.Unsubscribe(leur.EventList);
            Link_Event_Unsubscribe_Confirm leuc = new Link_Event_Unsubscribe_Confirm(STATUS.SUCCESS, leur.EventList);
            ch.Send(ResponseBuilders.Event_Unsubscribe_Response_Builder(dstID, srcID, m.MIHHeader.TransactionID, leuc).ByteValue);
        }

        /// <summary>
        /// This method is called to handle a Threshold configuration request message
        /// </summary>
        /// <param name="m">The serialized Config_Thresholds message</param>
        public static void HandleConfigThresholds(Message m)
        {
            ConnectionHelper ch = Program.toMihf;
            ushort transactionID = m.MIHHeader.TransactionID;
            Payload.TLVIterator it = m.Payload.GetTLVIterator();
            ID srcID = new ID(new OctetString(it.Next().Value));
            ID dstID = new ID(new OctetString(it.Next().Value));
            List<Link_Cfg_Param> lcparams = MIHDeserializer.DeserializeLinkCfgParamList(it.Next());
            List<Link_Cfg_Status> lcstatus = new List<Link_Cfg_Status>();
            foreach (Link_Cfg_Param param in lcparams)
            {
                if (param.Timer_Interval > 0 && param.Th_Action != TH_Action.CANCEL_THRESHOLD)
                {
                    Reports.TimedReports.Add(new TimedReport(param.Link_Param_Type.AbsoluteType, param.Timer_Interval));
                }
                switch (param.Th_Action)
                {
                    case TH_Action.ONE_SHOT_THRESHOLD:
                        foreach (Threshold t in param.ThresholdList)
                        {
                            try
                            {
                                Reports.OneShotThresholds.Add(new ActiveThreshold(t, param.Link_Param_Type.AbsoluteType));
                                lcstatus.Add(new Link_Cfg_Status(param.Link_Param_Type, t, true));
                            }
                            catch (Exception e)
                            { lcstatus.Add(new Link_Cfg_Status(param.Link_Param_Type, t, false)); }
                        }
                        break;
                    case TH_Action.NORMAL_THRESHOLD:
                        foreach (Threshold t in param.ThresholdList)
                        {
                            try
                            {
                                Reports.ActiveThresholds.Add(new ActiveThreshold(t, param.Link_Param_Type.AbsoluteType));
                                lcstatus.Add(new Link_Cfg_Status(param.Link_Param_Type, t, true));
                            }
                            catch (Exception e)
                            { lcstatus.Add(new Link_Cfg_Status(param.Link_Param_Type, t, false)); }
                        }
                        break;
                    case TH_Action.CANCEL_THRESHOLD:
                        Reports.Cancel(param); //TODO MORE
                        break;
                }
            }

            ch.Send(ResponseBuilders.Configure_Thresholds_Response_Builder(dstID, srcID, m.MIHHeader.TransactionID,
                new Link_Configure_Thresholds_Confirm(STATUS.SUCCESS,lcstatus)).ByteValue);
        }

        /// <summary>
        /// This method is called to handle a Get_Parameters request
        /// </summary>
        /// <param name="m">The serialized Get_Parameters_Request message.</param>
        public static void HandleGetParameters(Message m)
        {
            ConnectionHelper ch = Program.toMihf;
            ushort transactionID = m.MIHHeader.TransactionID;
            Payload.TLVIterator it = m.Payload.GetTLVIterator();
            ID srcID = new ID(new OctetString(it.Next().Value));
            ID dstID = new ID(new OctetString(it.Next().Value));
            Link_Get_Parameters_Request lgpr = new Link_Get_Parameters_Request(MIHDeserializer.DeserializeLinkParamRequest(it.Next()),
                new System.Collections.BitArray(it.Next().Value.Reverse().ToArray()),
                new System.Collections.BitArray(it.Next().Value.Reverse().ToArray()));

            Link_Get_Parameters_Confirm lgpc = new Link_Get_Parameters_Confirm();
            try
            {
                lgpc.LinkParametersStatusList = new List<Link_Param>(lgpr.LinkParametersRequest.Count);
                lgpc.LinkStatesRspList = new List<Link_Get_Parameters_Confirm.Link_States_Rsp>();
                lgpc.LinkDescRspList = new List<Link_Get_Parameters_Confirm.Link_Desc_Rsp>();
                foreach (Link_Param_Type lpt in lgpr.LinkParametersRequest)
                {
                    switch (lpt.AbsoluteType)
                    {
                        case Link_Param_Abs_Type.P80211_RSSI: lgpc.LinkParametersStatusList.Add(new Link_Param(lpt, Link_Param_802_11.GetRSSI_0)); break;
                        case Link_Param_Abs_Type.GEN_Data_Rate: lgpc.LinkParametersStatusList.Add(new Link_Param(lpt, Link_Param_Gen.DataRate_0)); break;
                        case Link_Param_Abs_Type.GEN_Sig_Strenth: lgpc.LinkParametersStatusList.Add(new Link_Param(lpt, Link_Param_Gen.SignalStrength_1)); break;
                        case Link_Param_Abs_Type.GEN_Packet_Error_Rate: lgpc.LinkParametersStatusList.Add(new Link_Param(lpt, Link_Param_Gen.PacketErrorRate_4)); break;
                    }
                }

                //-------LinkStates
                if (lgpr.LinkStatesRequest[0]) //OP_MODE
                    lgpc.LinkStatesRspList.Add(new Link_Get_Parameters_Confirm.Link_States_Rsp(Link_Get_Parameters_Confirm.Link_States_Rsp.Type.OP_MODE, (ushort)GenericInfo.WlanInterfaceInstance.OP_Mode_802_21));

                if (lgpr.LinkStatesRequest[1])
                    lgpc.LinkStatesRspList.Add(new Link_Get_Parameters_Confirm.Link_States_Rsp(Link_Get_Parameters_Confirm.Link_States_Rsp.Type.CHANNEL_ID, (ushort)GenericInfo.WlanInterfaceInstance.Channel));
                //-----------

                //-------LinkDesc
                if (lgpr.LinkDescriptorsRequest[0])
                    lgpc.LinkDescRspList.Add(new Link_Get_Parameters_Confirm.Link_Desc_Rsp(Link_Get_Parameters_Confirm.Link_Desc_Rsp.Type.NUM_CoS, 0)); //TODO (not supported)

                if (lgpr.LinkDescriptorsRequest[1])
                    lgpc.LinkDescRspList.Add(new Link_Get_Parameters_Confirm.Link_Desc_Rsp(Link_Get_Parameters_Confirm.Link_Desc_Rsp.Type.NUM_QUEUE, 1)); //TODO (not supported)
                //-----------

                lgpc.Status = STATUS.SUCCESS;
            }
            catch (Exception e) { lgpc.Status = STATUS.UNSPECIFIED_FAILURE;}

            Message toSend = ResponseBuilders.Get_Parameters_Response_Builder(dstID, srcID, m.MIHHeader.TransactionID, lgpc);

            if (Program.MESSAGE_DETAILS)
            {
                Console.WriteLine("Sending message: ("+m.MIHHeader.MID.AID+")");
                Connection.MIHProtocol.PacketReader.PrintMessage(toSend);
            }

            ch.Send(toSend.ByteValue);
        }

        #endregion

        #region MainFunction

        /// <summary>
        /// This method processes a message and calls the appropriate method to act on it.
        /// </summary>
        /// <param name="m">The received message.</param>
        public static void HandleMessage(Message m)
        {
            switch (m.MIHHeader.MID.AID)
            {
                case AIDGlobal.SERVICE_MANAGEMENT_MIH_CAPABILITY_DISCOVER:
                    HandleCapabilityDiscover(m);
                    break;
                case AIDGlobal.COMMAND_SERVICE_MIH_LINK_ACTIONS:
                    HandleCommandLinkActions(m);
                    break;
                case AIDGlobal.SERVICE_MANAGEMENT_MIH_EVENT_SUBSCRIBE:
                    HandleSubscribe(m);
                    break;
                case AIDGlobal.SERVICE_MANAGEMENT_MIH_EVENT_UNSUBSCRIBE:
                    HandleUnsubscribe(m);
                    break;
                case AIDGlobal.COMMAND_SERVICE_MIH_LINK_CONFIGURE_THRESHOLDS:
                    HandleConfigThresholds(m);
                    break;
                case AIDGlobal.COMMAND_SERVICE_MIH_LINK_GET_PARAMETERS:
                    HandleGetParameters(m);
                    break;
            }

        }

        #endregion
    }
}
