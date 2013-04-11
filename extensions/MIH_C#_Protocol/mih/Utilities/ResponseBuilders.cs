//==============================================================================
// Brief   : Class representing a ResponseBuilders.cs entity
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

﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


using MIH.MIHProtocol;
using MIH.DataTypes;
using MIH.Utilities;

//using LINK_SAP_CS_80211.Common.Information;
//using LINK_SAP_CS_80211.Events.EventClasses;
//using LINK_SAP_CS_80211.Connection.Message;
//using LINK_SAP_CS_80211.Connection.MIHProtocol;
//using LINK_SAP_CS_80211.Utilities;
//using LINK_SAP_CS_80211;
//using LINK_SAP_CS_80211.Common.Capabilities;
//using LINK_SAP_CS_80211.Actions.ActionClasses;
//using LINK_SAP_CS_80211.Common.CommonTypes;

namespace MIH.Utilities
{
    /// <summary>
    /// Class holding functions to build response-type 802.21 messages.
    /// </summary>
    public class ResponseBuilders
    {

        public static Message Link_Capability_Discover_Response_Builder(ID srcID, ID dstID, STATUS st, Link_Event_List lel, Link_CMD_List lcl)
        {
            Message m = new Message();
            m.MIHHeader = new MIHHeader();
            m.MIHHeader.MID = new MessageID(MessageID.ServiceIdentifier.SERVICE_MANAGEMENT, MessageID.OperationCode.CONFIRM, 1);
            m.MIHHeader.VersionValue = 1;

            //Link_Capability_Discover_Confirm lcdc = new Link_Capability_Discover_Confirm(STATUS.SUCCESS, lcl, lel);
            m.Payload = new Payload(srcID, dstID,
                Serialization.Sequence(
                Serialization.SerializeToTLV(TLV_VALUES.TLV_STATUS, BitConverter.GetBytes((int)st).Take(1).ToArray()),
                Serialization.SerializeToTLV(TLV_VALUES.TLV_LINK_EVENT_LIST, lel.ByteValue),
                Serialization.SerializeToTLV(TLV_VALUES.TLV_LINK_COMMAND_LIST, lcl.ByteValue)));
            m.MIHHeader.PayloadLength = (ushort)m.Payload.PayloadValue.Length;
            return m;
        }


        /// <summary>
        /// Generates an MIH Message based on a Link_Action_Response object.
        /// </summary>
        /// <param name="srcID">The source MIH ID.</param>
        /// <param name="dstID">The destination MIH ID</param>
        /// <param name="tid">The transaction ID, use the same as the request message.</param>
        /// <param name="laresp">The Link_Action_Response object to be the content of the message.</param>
        /// <returns>The MIH message to be sent to the MIHF.</returns>
        public static Message Link_Action_Response_Builder(ID srcID, ID dstID, ushort tid, Link_Action_Response laresp)
        {
            Message m = new Message();
            m.MIHHeader = new MIHHeader();
            MessageID mID = new MessageID(MessageID.ServiceIdentifier.COMMAND_SERVICE, MessageID.OperationCode.CONFIRM, (ushort)AIDCommandService.MIH_LINK_ACTIONS);
            m.MIHHeader.MID = mID;
            m.MIHHeader.TransactionID = tid;
            m.MIHHeader.VersionValue = 1;
            if (laresp.ScanResults.Count > 0)
                m.Payload = new Payload(dstID,
                                    srcID,
                                    Serialization.SerializeToTLV(TLV_VALUES.TLV_STATUS, BitConverter.GetBytes((int)laresp.Status).Take(1).ToArray()),
                                    Serialization.SerializeToTLV(TLV_VALUES.TLV_LINK_SCAN_RSP_LIST, Serialization.EncodingList(laresp.scanResultsAsByteArrayList().ToArray())),
                                    Serialization.SerializeToTLV(TLV_VALUES.TLV_LINK_AC_RESULT, BitConverter.GetBytes((int)laresp.Result).Take(1).ToArray()));
            else
                m.Payload = new Payload(dstID,
                                    srcID,
                                    Serialization.SerializeToTLV(TLV_VALUES.TLV_STATUS, BitConverter.GetBytes((int)laresp.Status).Take(1).ToArray()),
                                    Serialization.SerializeToTLV(TLV_VALUES.TLV_LINK_AC_RESULT, BitConverter.GetBytes((int)laresp.Result).Take(1).ToArray()));
            m.MIHHeader.PayloadLength = (ushort)m.Payload.PayloadValue.Length;
            return m;
        }

        /// <summary>
        /// Generates an MIH Message based on a Link_Event_Subscribe_Confirm object.
        /// </summary>
        /// <param name="srcID">The source MIH ID.</param>
        /// <param name="dstID">The destination MIH ID</param>
        /// <param name="tid">The transaction ID, use the same as the request message.</param>
        /// <param name="leconfirm">The Link_Event_Subscribe_Confirm object to be the content of the message.</param>
        /// <returns>The MIH message to be sent to the MIHF.</returns>
        public static Message Event_Subscribe_Response_Builder(ID srcID, ID dstID, ushort tid, Link_Event_Subscribe_Confirm leconfirm)
        {
            Message m = new Message();
            m.MIHHeader = new MIHHeader();
            MessageID mID = new MessageID(MessageID.ServiceIdentifier.SERVICE_MANAGEMENT, MessageID.OperationCode.CONFIRM, (ushort)AIDServiceManagement.MIH_EVENT_SUBSCRIBE);
            m.MIHHeader.MID = mID;
            m.MIHHeader.TransactionID = tid;
            m.MIHHeader.VersionValue = 1;

            byte[] status = new byte[1];
            status[0]= BitConverter.GetBytes((int)leconfirm.Status)[0];

            m.Payload = new Payload(srcID, dstID,
                Serialization.SerializeToTLV(TLV_VALUES.TLV_STATUS, status),
                Serialization.SerializeToTLV(TLV_VALUES.TLV_LINK_EVENT_LIST, leconfirm.LinkEventList.ByteValue));
            m.MIHHeader.PayloadLength = (ushort)m.Payload.PayloadValue.Length;
            return m;

        }

        /// <summary>
        /// Generates an MIH Message based on a Link_Event_Unsubscribe_Confirm object.
        /// </summary>
        /// <param name="srcID">The source MIH ID.</param>
        /// <param name="dstID">The destination MIH ID</param>
        /// <param name="tid">The transaction ID, use the same as the request message.</param>
        /// <param name="leconfirm">The Link_Event_Unsubscribe_Confirm object to be the content of the message.</param>
        /// <returns>The MIH message to be sent to the MIHF.</returns>
        public static Message Event_Unsubscribe_Response_Builder(ID srcID, ID dstID, ushort tid, Link_Event_Unsubscribe_Confirm leconfirm)
        {
            Message m = new Message();
            m.MIHHeader = new MIHHeader();
            MessageID mID = new MessageID(MessageID.ServiceIdentifier.SERVICE_MANAGEMENT, MessageID.OperationCode.CONFIRM, (ushort)AIDServiceManagement.MIH_EVENT_UNSUBSCRIBE);
            m.MIHHeader.MID = mID;
            m.MIHHeader.TransactionID = tid;
            m.MIHHeader.VersionValue = 1;

            byte[] status = new byte[1];
            status[0] = BitConverter.GetBytes((int)leconfirm.Status)[0];

            m.Payload = new Payload(srcID, dstID,
                Serialization.SerializeToTLV(TLV_VALUES.TLV_STATUS, status),
                Serialization.SerializeToTLV(TLV_VALUES.TLV_LINK_EVENT_LIST, leconfirm.LinkEventList.ByteValue));
            m.MIHHeader.PayloadLength = (ushort)m.Payload.PayloadValue.Length;
            return m;

        }

        /// <summary>
        /// Generates an MIH Message based on a Link_Configure_Thresholds_Confirm_Confirm object.
        /// </summary>
        /// <param name="srcID">The source MIH ID.</param>
        /// <param name="dstID">The destination MIH ID</param>
        /// <param name="tid">The transaction ID, use the same as the request message.</param>
        /// <param name="lctconfirm">The Link_Configure_Thresholds_Confirm object to be the content of the message.</param>
        /// <returns>The MIH message to be sent to the MIHF.</returns>
        public static Message Configure_Thresholds_Response_Builder(ID srcID, ID dstID, ushort tid, Link_Configure_Thresholds_Confirm lctconfirm)
        {
            Message m = new Message();
            m.MIHHeader = new MIHHeader();
            MessageID mID = new MessageID(MessageID.ServiceIdentifier.COMMAND_SERVICE, MessageID.OperationCode.CONFIRM, (ushort)AIDCommandService.MIH_LINK_CONFIGURE_THRESHOLDS);
            m.MIHHeader.MID = mID;
            m.MIHHeader.TransactionID = tid;
            m.MIHHeader.VersionValue = 1;

            byte[] st = new byte[1];
            st[0] = BitConverter.GetBytes((int)lctconfirm.Status)[0];

            m.Payload = new Payload(srcID, dstID,
                Serialization.SerializeToTLV(TLV_VALUES.TLV_STATUS, st),
                Serialization.SerializeToTLV(TLV_VALUES.TLV_CONFIGURE_RESPONSE_LIST, Serialization.EncodingList(lctconfirm.cfgStatusAsByteArrayList().ToArray())));

            m.MIHHeader.PayloadLength = (ushort)m.Payload.PayloadValue.Length;
            return m;
        }

        /// <summary>
        /// Generates an MIH Message based on a Link_Get_Parameters_Confirm object.
        /// </summary>
        /// <param name="srcID">The source MIH ID.</param>
        /// <param name="dstID">The destination MIH ID</param>
        /// <param name="tid">The transaction ID, use the same as the request message.</param>
        /// <param name="lgpconfirm">The Link_Event_SubscribeConfirm object to be the content of the message.</param>
        /// <returns>The MIH message to be sent to the MIHF.</returns>
        public static Message Get_Parameters_Response_Builder(ID srcID, ID dstID, ushort tid, Link_Get_Parameters_Confirm lgpconfirm)
        {
            Message m = new Message();
            m.MIHHeader = new MIHHeader();
            MessageID mID = new MessageID(MessageID.ServiceIdentifier.COMMAND_SERVICE, MessageID.OperationCode.CONFIRM, (ushort)AIDCommandService.MIH_LINK_GET_PARAMETERS);
            m.MIHHeader.MID = mID;
            m.MIHHeader.TransactionID = tid;
            m.MIHHeader.VersionValue = 1;

            byte[] st = new byte[1];
            st[0] = BitConverter.GetBytes((int)lgpconfirm.Status)[0];

            m.Payload = new Payload(srcID, dstID,
                Serialization.SerializeToTLV(TLV_VALUES.TLV_STATUS, st),
                Serialization.SerializeToTLV(TLV_VALUES.TLV_LINK_PARAMETERS_STATUS_LIST, Serialization.EncodingList(lgpconfirm.LinkParamListAsByteArray())),
                Serialization.SerializeToTLV(TLV_VALUES.TLV_LINK_STATES_RSP, Serialization.EncodingList(lgpconfirm.LinkStatesListAsByteArray())),
                Serialization.SerializeToTLV(TLV_VALUES.TLV_LINK_DESCRIPTOR_RSP, Serialization.EncodingList(lgpconfirm.LinkDescListAsByteArray())));

            m.MIHHeader.PayloadLength = (ushort)m.Payload.PayloadValue.Length;
            return m;
        }
    }
}
