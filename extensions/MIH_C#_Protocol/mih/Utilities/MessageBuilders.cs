//==============================================================================
// Brief   : Class representing a MessageBuilders.cs entity
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
using System.Net.NetworkInformation;

using MIH.DataTypes;
using MIH.MIHProtocol;


//using LINK_SAP_CS_80211.Common.Information;
//using LINK_SAP_CS_80211.Events.EventClasses;
//using LINK_SAP_CS_80211.Connection.Message;
//using LINK_SAP_CS_80211.Connection.MIHProtocol;
//using LINK_SAP_CS_80211.Utilities;
//using LINK_SAP_CS_80211;
//using LINK_SAP_CS_80211.Common.CommonTypes;
//using NativeWifi;

namespace MIH.Utilities
{
    /// <summary>
    /// Class holding functions to build 802.21 messages.
    /// </summary>
    public class MessageBuilders
    {

        /// <summary>
        /// Generates an 802.21-encoded message representing a LinkUp Event.
        /// </summary>
        /// <param name="srcID">The local node ID</param>
        /// <param name="dstID">The destination MIHF ID</param>
        /// <param name="ssid">The SSID of the established connection</param>
        /// <param name="PoAMac">The Physical Address for the Point of Access</param>
        /// <returns>A fully encoded, ready to be sent Message representing a LinkUp</returns>
        public static Message Link_Up_Indication_MsgBuilder(ID srcID, ID dstID, String ssid, PhysicalAddress PoAMac)
        {
            Message m = new Message();
            m.MIHHeader = new MIHHeader();
            m.MIHHeader.MID = new MessageID(MessageID.ServiceIdentifier.EVENT_SERVICE, MessageID.OperationCode.INDICATION, 2);
            m.MIHHeader.VersionValue = 1;
            Link_Tuple_Id linkIdentifier = new Link_Tuple_Id(
                        new Link_Id(Link_Type.Wireless_IEEE80211, new Link_Addr(Link_Addr.Address_Type.OTHER_L2_ADDR, ssid)),
                        new Link_Addr(Link_Addr.Address_Type.MAC_ADDR, Utilities.PhysicalAddressToString(PoAMac)));
            m.Payload = new Payload(srcID,
                                    dstID,
                                    TLV_HELPERS.TLVLinkIdentifier(linkIdentifier));
            m.MIHHeader.PayloadLength = (ushort)m.Payload.PayloadValue.Length;
            return m;
        }

        /// <summary>
        /// Generates an 802.21-encoded message representing a LinkDown Event.
        /// </summary>
        /// <param name="srcID">The local node ID</param>
        /// <param name="dstID">The destination MIHF ID</param>
        /// <param name="ssid">The SSID of the disconnected network</param>
        /// <param name="PoAMac">The Physical Address for the Point of Access</param>
        /// <param name="reason">The reason for the disconnect</param>
        /// <returns>A fully encoded, ready to be sent Message representing a LinkDown</returns>
        public static Message Link_Down_Indication_802_11_MsgBuilder(ID srcID, ID dstID, String ssid, PhysicalAddress PoAMac, Link_Dn_Reason reason)
        {
            Message m = new Message();
            m.MIHHeader = new MIHHeader();
            m.MIHHeader.MID = new MessageID(MessageID.ServiceIdentifier.EVENT_SERVICE, MessageID.OperationCode.INDICATION, 3);
            m.MIHHeader.VersionValue = 1;
            Link_Tuple_Id linkIdentifier = new Link_Tuple_Id(
                        new Link_Id(Link_Type.Wireless_IEEE80211, new Link_Addr(Link_Addr.Address_Type.OTHER_L2_ADDR, ssid)),
                        new Link_Addr(Link_Addr.Address_Type.MAC_ADDR, Utilities.PhysicalAddressToString(PoAMac)));
            Link_Dn_Reason downReason = reason;

            m.Payload = new Payload(srcID, dstID,
                TLV_HELPERS.TLVLinkIdentifier(linkIdentifier), TLV_HELPERS.TLVLinkDnReason(downReason));
            m.MIHHeader.PayloadLength = (ushort)m.Payload.PayloadValue.Length;
            return m;
        }

        /// <summary>
        /// Generates an 802.21-encoded message representing a LinkDown Event.
        /// </summary>
        /// <param name="srcID">The local node ID</param>
        /// <param name="dstID">The destination MIHF ID</param>
        /// <param name="imsi">The IMSI (International Mobile Subscriber Identity) for this network</param>
        /// <param name="PoAMac">The Physical Address for the Point of Access</param>
        /// <param name="reason">The reason for the disconnect</param>
        /// <returns>A fully encoded, ready to be sent Message representing a LinkDown</returns>
        public static Message Link_Down_Indication_3G_MsgBuilder(ID srcID, ID dstID, String imsi, PhysicalAddress PoAMac, Link_Dn_Reason reason)
        {
            Message m = new Message();
            m.MIHHeader = new MIHHeader();
            m.MIHHeader.MID = new MessageID(MessageID.ServiceIdentifier.EVENT_SERVICE, MessageID.OperationCode.INDICATION, 3);
            m.MIHHeader.VersionValue = 1;
            Link_Tuple_Id linkIdentifier = new Link_Tuple_Id(
                        new Link_Id(Link_Type.Wireless_UMTS, new Link_Addr(Link_Addr.Address_Type._3GPP_ADDR, imsi)),
                        new Link_Addr(Link_Addr.Address_Type.MAC_ADDR, Utilities.PhysicalAddressToString(PoAMac)));
            Link_Dn_Reason downReason = reason;

            m.Payload = new Payload(srcID, dstID,
                TLV_HELPERS.TLVLinkIdentifier(linkIdentifier), TLV_HELPERS.TLVLinkDnReason(downReason));
            m.MIHHeader.PayloadLength = (ushort)m.Payload.PayloadValue.Length;
            return m;
        }

        /// <summary>
        /// Creates a Link_Detected.Indication message
        /// </summary>
        /// <param name="srcID">The local node ID</param>
        /// <param name="dstID">The destination MIHF ID</param>
        /// <param name="BSSID">The link's BSSID (the MAC of the access point).</param>
        /// <param name="SSID">The link's SSID.</param>
        /// <param name="linkQuality">The link quality for the specified link.</param>
        /// <param name="rssi">The RSSI (Received Signal Strength Indication) for this link.</param>
        /// <param name="maxRate">The max transfer rate on this connection.</param>
        /// <returns>A fully encoded, ready to be sent Message representing a LinkDetected indication</returns>
        public static Message Link_Detected_Indication_MsgBuilder(ID srcID, ID dstID, byte[] BSSID, byte[] SSID, uint linkQuality, int rssi, int maxRate)
        {
            Message m = new Message();
            m.MIHHeader = new MIHHeader();
            m.MIHHeader.MID = new MessageID(MessageID.ServiceIdentifier.EVENT_SERVICE, MessageID.OperationCode.INDICATION, 1);
            m.MIHHeader.VersionValue = 1;

            //byte[] hessid = new byte[entry.dot11Bssid.Length + 1];
            string hessid = Utilities.PhysicalAddressToString(new PhysicalAddress(BSSID));
            //hessid[0] = BitConverter.GetBytes(entry.dot11Bssid.Length)[0];
            //for (int i = 0; i < entry.dot11Bssid.Length; i++)
            //    hessid[1 + i] = entry.dot11Bssid[i];

            Link_Det_Info linkDetInfo = new Link_Det_Info(
                                        new Link_Tuple_Id(
                                            new Link_Id(Link_Type.Wireless_IEEE80211, new Link_Addr(Link_Addr.Address_Type.OTHER_L2_ADDR,
                                                    new string(Encoding.ASCII.GetChars(SSID)))),
                                            new Link_Addr(Link_Addr.Address_Type.MAC_ADDR,
                                                    Utilities.PhysicalAddressToString(new PhysicalAddress(BSSID)))),
                                        new OctetString(new String(Encoding.ASCII.GetChars(SSID))),
                                        new OctetString(hessid),
                                        linkQuality,
                                        rssi,
                                        0,
                                        (int)((double)(maxRate) * 8) / 1024,
                                        new Link_MIHCap_Flag(true, true, true),
                                        new Net_Caps(false, false, false, false, false, false, false, true, false, true));

            m.Payload = new Payload(srcID, dstID, Serialization.SerializeToTLV(TLV_VALUES.TLV_LINK_DET_INFO, linkDetInfo.ByteVal));
            m.MIHHeader.PayloadLength = (ushort)m.Payload.PayloadValue.Length;
            return m;
        }

        /// <summary>
        /// Generates a Link_Parameters_Report.Indication message, reporting the specified value of the specified parameter type.
        /// </summary>
        /// <param name="src">The source MIHF ID</param>
        /// <param name="dst">The destination MIHF ID</param>
        /// <param name="APMac">The Physical Address of the Access Point (corresponding to the active link)</param>
        /// <param name="networkSSID">The SSID for the active link</param>
        /// <param name="paramType">The type of parameter to report</param>
        /// <param name="value">The value of the parameter</param>
        /// <returns>A Link_Parameters_Report.Indication message ready to be sent.</returns>
        public static Message Link_Parameters_Report_Indication_MsgBuilder(ID src, ID dst, PhysicalAddress APMac, byte[] networkSSID, Link_Param_Abs_Type paramType, ushort value )
        {
            Message m = new Message();
            m.MIHHeader = new MIHHeader();
            m.MIHHeader.MID = new MessageID(MessageID.ServiceIdentifier.EVENT_SERVICE, MessageID.OperationCode.INDICATION, 5);
            m.MIHHeader.VersionValue = 1;
            Link_Tuple_Id linkIdentifier = new Link_Tuple_Id(
                        new Link_Id(Link_Type.Wireless_IEEE80211, new Link_Addr(Link_Addr.Address_Type.MAC_ADDR, Utilities.PhysicalAddressToString(APMac))),
                        new Link_Addr(Link_Addr.Address_Type.OTHER_L2_ADDR, new String(Encoding.ASCII.GetChars(networkSSID))));

            Link_Param_Rpt lpr = new Link_Param_Rpt(
                                    new Link_Param(
                                        Link_Param_Type.FromAbsType(paramType),
                                        (ushort)value,
                                        0 /*TODO 0=LinkParamVal (choice)*/),
                                    null);
            List<byte[]> lprList = new List<byte[]>();
            lprList.Add(lpr.ByteValue);

            m.Payload = new Payload(src,
                                    dst,
                                    Serialization.SerializeToTLV(TLV_VALUES.TLV_LINK_IDENTIFIER, linkIdentifier.ByteValue),
                                    Serialization.SerializeToTLV(TLV_VALUES.TLV_LINK_PARAM_REPORT_LIST, Serialization.EncodingList(lprList.ToArray())));
            m.MIHHeader.PayloadLength = (ushort)m.Payload.PayloadValue.Length;
            return m;
        }
    }
}
