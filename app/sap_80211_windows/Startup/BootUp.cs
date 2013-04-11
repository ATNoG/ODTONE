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
using System.Management;

using NativeWifi;
using System.Threading;
using LINK_SAP_CS_80211.Common;

namespace LINK_SAP_CS_80211.Startup
{
    class BootUp
    {
        const string wlanAdaptersQuery = "SELECT * FROM MSNdis_80211_BaseServiceSetIdentifier WHERE Active = True";
        const string wlanSSIDsQuery = "SELECT * FROM MSNDis_80211_BSSIList";
        const string testQuery = "SELECT * FROM MSNdis_80211_ServiceSetIdentifier";

        private string mac;

        public BootUp(string mac, ushort fromMIHFPort, System.Net.IPAddress mihAddr)
        {
            this.mac = mac;
            //LINK_SAP_80211.Information.GenericInfo.PhysicalAddress = System.Net.NetworkInformation.PhysicalAddress.Parse(mac.Replace(':', '-'));
            Information.GenericInfo.ClientInstance = new WlanClient();
            try
            {
                Information.GenericInfo.WlanInterfaceInstance.Scan();
                Information.GenericInfo.WlanInterfaceInstance.LatestConnection = Information.GenericInfo.WlanInterfaceInstance.CurrentConnection;
            }
            catch (Exception e) {
                Console.WriteLine("Ignorable error: " + e.Message);
            }
            //Wlan.WlanInterfaceInfo iInf = new Wlan.WlanInterfaceInfo();
            //iInf.interfaceGuid = new Guid(getGuidForMac(mac));
            //WlanClient.WlanInterface interf = LINK_SAP_80211.Information.GenericInfo.WlanInterfaceInstance;
            //LINK_SAP_80211.Information.GenericInfo.

            //foreach (Wlan.WlanBssEntry entry in interf.GetNetworkBssList())
            //{
            //    char[] txt = Encoding.ASCII.GetChars(entry.dot11Ssid.SSID);
            //    Console.WriteLine(new String(txt) + ", " + entry.linkQuality + "%");
            //}
            Start(mac, fromMIHFPort, mihAddr);
            //interf.Disconnect();
        }


        public static void Start(string macAddress, ushort fromMIHFPort, System.Net.IPAddress mihAddr){

            LinkSAP80211 linkSap80211Instance;
            ManagementObject linkSap80211MO;
            //start------------
            Console.WriteLine("Setting Up Link SAP for 802.11 interface with MAC Address "+macAddress+"...");

            /////////////////////////Statistics///////////////////////////////
            var s1 = System.Diagnostics.Stopwatch.StartNew();
            /////////////////////////Statistics///////////////////////////////

            linkSap80211MO = get80211InterfaceByMac(macAddress);
            if (linkSap80211MO != null)
            {
                Console.WriteLine("Instantiating...");
                linkSap80211Instance = Instantiate80211(linkSap80211MO, fromMIHFPort, mihAddr);
            }
            Console.WriteLine("All done!");
            /////////////////////////Statistics///////////////////////////////
            s1.Stop();
            /////////////////////////Statistics///////////////////////////////

            Console.WriteLine("Setup Finished in " + s1.Elapsed.Milliseconds + "ms");
            Console.WriteLine("______________________________________________");

        }

        public static string getGuidForMac(string mac)
        {
            using (ManagementObjectSearcher mos = new ManagementObjectSearcher(@"SELECT *
                                                                                      FROM Win32_NetworkAdapter
                                                                                      WHERE Manufacturer != 'Microsoft'
                                                                                      AND NOT PNPDeviceID LIKE 'ROOT\\%'
                                                                                      AND (NetConnectionID LIKE 'Wireless%'
                                                                                        OR NetConnectionID LIKE 'WiFi%')" + //Needed for Windows 8
                                                                                      "AND MACAddress LIKE'" + mac + "'"))
            {

                String guid="";
                IEnumerable<ManagementObject> mOs80211 = mos.Get().Cast<ManagementObject>();
                foreach (ManagementObject mo in mOs80211)
                    guid = (string) mo.GetPropertyValue("GUID");
                return guid;
            }
        }

        private static ManagementObject get80211InterfaceByMac(String macAddress)
        {

            ManagementObject instance = null;

            /*using (ManagementObjectSearcher mos = new ManagementObjectSearcher(@"SELECT *
                                                                                      FROM Win32_NetworkAdapter
                                                                                      WHERE Manufacturer != 'Microsoft'
                                                                                      AND NOT PNPDeviceID LIKE 'ROOT\\%'
                                                                                      AND NetConnectionID LIKE 'Wireless%'
                                                                                      AND MACAddress LIKE'" + macAddress + "'"))
            {*/
            using (ManagementObjectSearcher mos = new ManagementObjectSearcher(@"SELECT *
                                                                                      FROM Win32_NetworkAdapter
                                                                                      WHERE Manufacturer != 'Microsoft'
                                                                                      AND NOT PNPDeviceID LIKE 'ROOT\\%'
                                                                                      AND (NetConnectionID LIKE 'Wireless%'
                                                                                        OR NetConnectionID LIKE 'WiFi%')"+ //Needed for Windows 8
                                                                                      "AND MACAddress LIKE'" + macAddress + "'"))
            {

                IEnumerable<ManagementObject> mOs80211 = mos.Get().Cast<ManagementObject>();

                foreach (ManagementObject mo in mOs80211)
                    instance = mo;

                if (instance != null)
                    Console.WriteLine("Interface found.");
                else
                    Console.WriteLine("Interface not found.");
                return instance;
            }
        }

        private static LinkSAP80211 Instantiate80211(ManagementObject linkSap80211MO, ushort fromMIHFPort, System.Net.IPAddress mihAddr)
        {
            return new LinkSAP80211((string)linkSap80211MO.GetPropertyValue("GUID"), fromMIHFPort, mihAddr);
        }
    }
}
