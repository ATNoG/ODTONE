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

using LINK_SAP_CS_80211.Common.Events;
using LINK_SAP_CS_80211.Information;
using MIH.DataTypes;
using MIH.Utilities;
using MIH_Connection.Link;
using NativeWifi;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.NetworkInformation;

namespace LINK_SAP_CS_80211.LINK_SAP_80211.Events
{
    class EventHandler
    {
        public static void HandleLinkUp(Wlan.WlanNotificationData notifyData)
        {
            NativeWifi.WlanClient.WlanInterface wlanIface = null;// = GenericInfo.WlanInterface;
            foreach (NativeWifi.WlanClient.WlanInterface wli in Information.GenericInfo.ClientInstance.Interfaces)
                if (wli.InterfaceGuid == notifyData.interfaceGuid)
                    if (wli.NetworkInterface.GetPhysicalAddress().Equals(PhysicalAddress.Parse(Program.MAC.Replace(":", "-").ToUpper()))) //Event filtering
                        wlanIface = wli;

            if (wlanIface != null)
            {
                ConnectionHelper ch = Program.toMihf;
                ID myLinkID = new ID(new OctetString(GenericInfo.myID));
                ID mihfID = new ID(new OctetString(GenericInfo.mihfID));

                wlanIface.LatestConnection = wlanIface.CurrentConnection;

                if (Subscriptions.List.Link_Up)
                    ch.Send(MessageBuilders.Link_Up_Indication_MsgBuilder(myLinkID, mihfID,
                        new String(Encoding.ASCII.GetChars(wlanIface.CurrentConnection.wlanAssociationAttributes.dot11Ssid.SSID)),
                        wlanIface.CurrentConnection.wlanAssociationAttributes.Dot11Bssid).ByteValue);
            }

        }

        public static void HandleLinkDown(Wlan.WlanNotificationData notifyData)
        {
            NativeWifi.WlanClient.WlanInterface wlanIface = null;// = GenericInfo.WlanInterface;
            foreach (NativeWifi.WlanClient.WlanInterface wli in Information.GenericInfo.ClientInstance.Interfaces)
                if (wli.InterfaceGuid == notifyData.interfaceGuid)
                    if (wli.NetworkInterface.GetPhysicalAddress().Equals(PhysicalAddress.Parse(Program.MAC.Replace(":", "-").ToUpper()))) //Event filtering
                        wlanIface = wli;

            if (wlanIface != null)
            {
                ConnectionHelper ch = Program.toMihf;
                ID myLinkID = new ID(new OctetString(GenericInfo.myID));
                ID mihfID = new ID(new OctetString(GenericInfo.mihfID));

                if (Subscriptions.List.Link_Down)
                    ch.Send(MessageBuilders.Link_Down_Indication_802_11_MsgBuilder(myLinkID, mihfID,
                        new String(Encoding.ASCII.GetChars(wlanIface.LatestConnection.wlanAssociationAttributes.dot11Ssid.SSID)),
                        wlanIface.LatestConnection.wlanAssociationAttributes.Dot11Bssid,
                        Link_Dn_Reason.ExplicitDisconnect).ByteValue);//TODO get reasons
            }
        }

        public static void HandleScanComplete(Wlan.WlanNotificationData notifyData)
        {
            NativeWifi.WlanClient.WlanInterface wlanIface = null;// = GenericInfo.WlanInterface;
            foreach (NativeWifi.WlanClient.WlanInterface wli in Information.GenericInfo.ClientInstance.Interfaces)
                if (wli.InterfaceGuid == notifyData.interfaceGuid)
                    if (wli.NetworkInterface.GetPhysicalAddress().Equals(PhysicalAddress.Parse(Program.MAC.Replace(":", "-").ToUpper()))) //Event filtering
                        wlanIface = wli;

            if (wlanIface != null)
            {
                ConnectionHelper ch = Program.toMihf;
                ID myLinkID = new ID(new OctetString(GenericInfo.myID));
                ID mihfID = new ID(new OctetString(GenericInfo.mihfID));

                bool newLinks = wlanIface.UpdateSSIDs(wlanIface.GetNetworkBssList());
                if (wlanIface.ScanRequested)
                    LINK_SAP_CS_80211.Common.Actions.ActionsInterface.FinishScanAction(); //Scan Actions from Link_Action.Requests are replied here.
                wlanIface.ScanRequested = false;
                //LINK DETECTED INDICATION
                if (Subscriptions.List.Link_Detected)
                    if (newLinks)
                        foreach (Wlan.WlanBssEntry entry in wlanIface.newConns)
                            ch.Send(MessageBuilders.Link_Detected_Indication_MsgBuilder(myLinkID, mihfID,
                                entry.dot11Bssid, entry.dot11Ssid.SSID, entry.linkQuality, entry.rssi, Utilities.getMax(entry.wlanRateSet.Rates)).ByteValue);
            }
        }

        public static void HandleParamsReport(Wlan.WlanNotificationData notifyData)
        {
            NativeWifi.WlanClient.WlanInterface wlanIface = null;// = GenericInfo.WlanInterface;
            foreach (NativeWifi.WlanClient.WlanInterface wli in Information.GenericInfo.ClientInstance.Interfaces)
                if (wli.InterfaceGuid == notifyData.interfaceGuid)
                    if (wli.NetworkInterface.GetPhysicalAddress().Equals(PhysicalAddress.Parse(Program.MAC.Replace(":", "-").ToUpper()))) //Event filtering
                        wlanIface = wli;

            if (wlanIface != null)
            {
                ConnectionHelper ch = Program.toMihf;
                ID myLinkID = new ID(new OctetString(GenericInfo.myID));
                ID mihfID = new ID(new OctetString(GenericInfo.mihfID));

                if (Subscriptions.List.Link_Parameters_Report) //Generic subscription
                    ch.Send(MessageBuilders.Link_Parameters_Report_Indication_MsgBuilder(
                        myLinkID, mihfID,
                        wlanIface.CurrentConnection.wlanAssociationAttributes.Dot11Bssid,
                        wlanIface.CurrentConnection.wlanAssociationAttributes.dot11Ssid.SSID,
                        Link_Param_Abs_Type.GEN_Sig_Strenth,
                        Link_Param_Gen.SignalStrength_1).ByteValue);
                Reports.CheckThresholds(Link_Param_Abs_Type.GEN_Sig_Strenth, (int)wlanIface.RSSI);
            }
        }

    }
}
