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
using NativeWifi;
using System.Management;
using System.Net.NetworkInformation;


using MIH.DataTypes;
using MIH.Utilities;
using MIH.MIHProtocol;

//using LINK_SAP_CS_80211.Actions.ActionClasses;
//using LINK_SAP_CS_80211.Events.EventClasses;
//using LINK_SAP_CS_80211.Common.Capabilities;

namespace LINK_SAP_CS_80211.Common.Actions
{
    /// <summary>
    /// This class provides several methods that perform the multiple link actions.
    /// </summary>
    class ActionsInterface
    {
        /// <summary>
        /// Executes a disconnect on the interface and changes the Status of the Link_Action_Response.
        /// </summary>
        /// <param name="laresp">The Link_Action_Response for this action.</param>
        /// <param name="iface">The interface do disconnect the link from.</param>
        public static void Action_Disconnect(ref Link_Action_Response laresp, ref NativeWifi.WlanClient.WlanInterface iface)
        {

            if (iface != null)
            {
                iface.Disconnect();
                Console.WriteLine("Disconnected b/c a Disconnect Link Action was received.");
                laresp.Status = STATUS.SUCCESS;
                laresp.Result = Link_Ac_Result.SUCCESS;
            }
            else
            {
                Console.WriteLine("Cannot disconnect a disabled interface.");
                laresp.Status = STATUS.REJECTED;
                laresp.Result = Link_Ac_Result.REFUSED;
            }
        }

        /// <summary>
        /// Executes a Power Down (disable interface) on the interface and changes the Status of the Link_Action_Response.
        /// </summary>
        /// <param name="laresp">The Link_Action_Response for this action.</param>
        /// <param name="iface">The interface do disconnect the link from.</param>
        public static void Action_Power_Down(ref Link_Action_Response laresp, ref NativeWifi.WlanClient.WlanInterface iface)
        {
            Console.WriteLine("Disabling interface.");
            try
            {
                using (ManagementObjectSearcher mos = new ManagementObjectSearcher(@"SELECT *
                                                                                  FROM Win32_NetworkAdapter
                                                                                  WHERE GUID = '" + iface.InterfaceGuid.ToString() + "'"))
                {

                    ManagementObject objMO = mos.Get().Cast<ManagementObject>().SingleOrDefault();
                    objMO.InvokeMethod("Disable", null);
                }
                laresp.Status = STATUS.SUCCESS;
                laresp.Result = Link_Ac_Result.SUCCESS;
            }
            catch (Exception)
            {
                laresp.Status = STATUS.UNSPECIFIED_FAILURE;
                laresp.Result = Link_Ac_Result.FAILURE;
            }
        }


        /// <summary>
        /// Executes a Power Up (enable interface) on the interface and changes the Status of the Link_Action_Response.
        /// </summary>
        /// <param name="laresp">The Link_Action_Response for this action.</param>
        /// <param name="iface">The interface do disconnect the link from.</param>
        public static void Action_Power_Up(ref Link_Action_Response laresp, ref NativeWifi.WlanClient.WlanInterface iface)
        {
            Console.WriteLine("Enabling interface.");
            try
            {
                using (ManagementObjectSearcher mos = new ManagementObjectSearcher(@"SELECT *
                                                                                  FROM Win32_NetworkAdapter
                                                                                  WHERE GUID = '" + iface.InterfaceGuid.ToString() + "'"))
                {

                    ManagementObject objMO = mos.Get().Cast<ManagementObject>().SingleOrDefault();
                    objMO.InvokeMethod("Enable", null);
                }
                laresp.Status = STATUS.SUCCESS;
                laresp.Result = Link_Ac_Result.SUCCESS;
            }
            catch (Exception)
            {
                laresp.Status = STATUS.UNSPECIFIED_FAILURE;
                laresp.Result = Link_Ac_Result.FAILURE;
            }
        }

        /// <summary>
        /// Issues a scan order on the interface and processes (and sends) the rest of the message when the scan is completed.
        /// </summary>
        /// <param name="laresp">The Link_Action_Response for this action.</param>
        /// <param name="iface">The interface to scan.</param>
        /// <param name="m">The message to be processed and sent when the scan is complete.</param>
        public static void Action_Scan(Link_Action_Response laresp, NativeWifi.WlanClient.WlanInterface iface, Message m)
        {
            if (iface != null)
            {
                if(!iface.ScanRequested)
                    iface.Scan();
                iface.ScanRequested = true;
                Console.Write("Waiting for scan results...");
                Information.MiscData.PendingLinkActionResponses.Add(m, laresp); //Message sent at the WlanApi class, when a scan event occurs.
            }
            else
            {
                Console.WriteLine("Cannot scan a disabled interface.");
                laresp.Status = STATUS.REJECTED;
            }
        }

        /// <summary>
        /// To be called when a requested scan was complete. This method sends all pending Link_Action_Responses that were waiting for a scan result.
        /// </summary>
        public static void FinishScanAction()
        {
            List<Link_Scan_Rsp> scanResults = new List<Link_Scan_Rsp>();
            foreach (NativeWifi.Wlan.WlanBssEntry entry in Information.GenericInfo.WlanInterfaceInstance.Connections)
            {
                PhysicalAddress pa = new PhysicalAddress(entry.dot11Bssid);
                scanResults.Add(new Link_Scan_Rsp(new Link_Addr(Link_Addr.Address_Type.MAC_ADDR, Utilities.PhysicalAddressToString(pa)),
                    new OctetString(new String(Encoding.ASCII.GetChars(entry.dot11Ssid.SSID))),
                    (ushort)entry.linkQuality));
            }

            foreach (Message m in Information.MiscData.PendingLinkActionResponses.Keys)
            {
                Link_Action_Response laresp;
                Information.MiscData.PendingLinkActionResponses.TryGetValue(m, out laresp);
                laresp.ScanResults = scanResults;
                Payload.TLVIterator it = m.Payload.GetTLVIterator();
                ID srcID = new ID(new OctetString(it.Next().Value));
                ID dstID = new ID(new OctetString(it.Next().Value));
                Program.toMihf.Send(ResponseBuilders.Link_Action_Response_Builder(srcID, dstID, m.MIHHeader.TransactionID, laresp).ByteValue);
            }
            Information.MiscData.PendingLinkActionResponses.Clear();
        }

    }
}