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
using System.Net.NetworkInformation;
using System.Diagnostics;
using System.IO;
using System.Management;
using NativeWifi;

using MIH.DataTypes;

namespace LINK_SAP_CS_80211.Information
{
    #region GenericInfo
    /// <summary>
    /// This class provides generic info of the default (802.11 type) machine network adapter. Such as the GUID, Physical Address, NetworkInterface object, and others.
    /// </summary>
    class GenericInfo
    {
        /// <summary>
        /// This property represents your ID as sent to the MIHF
        /// </summary>
        public static String myID{get; set;}

        /// <summary>
        /// This property represents the MIHF ID to which messages are sent.
        /// </summary>
        public static String mihfID{get;set;}


        /// <summary>
        /// This property provides the active WlanClient instance from which all information is gathered.
        /// </summary>
        public static WlanClient ClientInstance
        {
            set
            {
                _wlanc = value;
            }
            get { return _wlanc; }
        }
        private static WlanClient _wlanc;

        /// <summary>
        /// This property provides the WlanInterface being used in this LinkSap instance.
        /// </summary>
        public static WlanClient.WlanInterface WlanInterfaceInstance
        {
            get {return _wlanc.Interfaces.Single(itf => itf.InterfaceGuid.ToString() == InterfaceGUIDTrimmed); }
        }


        /// <summary>
        /// This property provides the PhysicalAdress of the (802.11 type) machine network adapter. (Similar behaviour in the method Get80211nicPHYAddress())
        /// </summary>
        public static PhysicalAddress PhysicalAddress
        {
            get
            {
                if (_physicalAddress == null)
                {
                        _physicalAddress = _wlanc.Interfaces.Single(itf => itf.InterfaceGuid == GUID).NetworkInterface.GetPhysicalAddress();
                        return _physicalAddress;
                }
                else
                    return _physicalAddress;
            }
        }
        private static PhysicalAddress _physicalAddress = null;


        /// <summary>
        /// This property provides the GUID of the (802.11 type) machine network adapter, using a Win32_NetworkAdapter query.
        /// (With this implementation the GUID can be retrieved in disabled or turned off interfaces)
        /// </summary>
        public static string GUIDString
        {
            get
            {
                if (_GUIDString == null)
                {
                    using (ManagementObjectSearcher mos = new ManagementObjectSearcher(@"SELECT *
                                                                              FROM Win32_NetworkAdapter
                                                                              WHERE Manufacturer != 'Microsoft'
                                                                              AND NOT PNPDeviceID LIKE 'ROOT\\%'"))
                    {
                        _GUIDString = (string)mos.Get().Cast<ManagementObject>().Last().GetPropertyValue("GUID");
                        return _GUIDString;
                    }
                }
                else
                    return _GUIDString;
            }
        }
        private static string _GUIDString = null;

        /// <summary>
        /// This property provides the GUID of the (802.11 type) machine network adapter.
        /// (This implementation only allows the GUID retrieval in enabled/turned on interfaces)
        /// </summary>
        public static Guid GUID
        {
            get
            {
                if (_GUID.ToString() == "00000000-0000-0000-0000-000000000000")
                {
                        _GUID = _wlanc.Interfaces.Single(itf => itf.InterfaceGuid.ToString() == InterfaceGUIDTrimmed).InterfaceGuid;
                        return _GUID;
                }
                else
                    return _GUID;
            }
        }
        private static Guid _GUID = new Guid();

        /// <summary>
        /// This property holds the GUID of the LinkSAP interface in the form of {XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX}.
        /// This property is set everytime the LinkSAP is instantiated.
        /// </summary>
        public static string InterfaceGUID
        {
            get
            {
                return _interfaceGUID;
            }
            set
            {
                _interfaceGUID = value;
                InterfaceGUIDTrimmed = value;
            }


        }
        private static string _interfaceGUID;

        /// <summary>
        /// This property holds the GUID of the LinkSAP interface in the form of xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx.
        /// </summary>
        public static string InterfaceGUIDTrimmed
        {
            get
            {
                if (_InterfaceGUIDTrimmed == "" || _InterfaceGUIDTrimmed==null)
                    InterfaceGUIDTrimmed = GUIDString;
                return _InterfaceGUIDTrimmed;
            }
            set
            {
                if (value.Contains('{'))
                {
                    _InterfaceGUIDTrimmed = value.Substring(1, value.Length - 2).ToLower();
                }
                else
                    _InterfaceGUIDTrimmed = value;

            }
        }
        public static string _InterfaceGUIDTrimmed;


        /// <summary>
        /// This property indicates the interface availability, as a boolean value.
        /// </summary>
        public static bool InterfaceState
        {
            get
            {
                Wlan.WlanInterfaceState wlanIntState = _wlanc.Interfaces.Single(itf => itf.InterfaceGuid.ToString() == InterfaceGUIDTrimmed).InterfaceState;
                switch (wlanIntState)
                {
                    case Wlan.WlanInterfaceState.Connected: return true;
                    case Wlan.WlanInterfaceState.Associating:
                    case Wlan.WlanInterfaceState.Authenticating:
                    case Wlan.WlanInterfaceState.Disconnected:
                    case Wlan.WlanInterfaceState.Disconnecting:
                    case Wlan.WlanInterfaceState.Discovering:
                    case Wlan.WlanInterfaceState.NotReady:
                    default: return false;
                }
            }
        }

        /// <summary>
        /// This property provides the NetworkInterface object of the (802.11 type) machine network adapter.
        /// </summary>
        public static NetworkInterface Interface
        {
            get
            {
                if (_interface == null)
                {
                    _interface = NetworkInterface.GetAllNetworkInterfaces().Where(nic => nic.GetPhysicalAddress().Equals(PhysicalAddress)).SingleOrDefault();
                    return _interface;
                }
                else
                    return _interface;
            }
        }
        public static NetworkInterface _interface = null;


        public static ushort GetValueForParam(Link_Param_Abs_Type type)
        {
            switch (type)
            {
                case Link_Param_Abs_Type.P80211_RSSI: return Link_Param_802_11.GetRSSI_0;
                case Link_Param_Abs_Type.GEN_Sig_Strenth: return Link_Param_Gen.SignalStrength_1;
                case Link_Param_Abs_Type.GEN_Data_Rate: return Link_Param_Gen.DataRate_0;
                case Link_Param_Abs_Type.GEN_Packet_Error_Rate: return Link_Param_Gen.PacketErrorRate_4;
                default: throw new NotImplementedException();
            }
        }
    }


    #endregion

    #region LinkParamGen
    /// <summary>
    /// This class allows the retrieval of several link parameters, according to 802.21 specification for LINK_PARAM_GER parameters group.
    /// </summary>
    class Link_Param_Gen
    {

        /// <summary>
        /// This property provides the DataRate of the interface.
        /// </summary>
        public static ushort DataRate_0
        {
            get { return Convert.ToUInt16(GenericInfo.Interface.Speed / 1024); } //The Speed attribute comes in bits/line
        }

        /// <summary>
        /// This property provides the Signal Strength of the interface.
        /// </summary>
        public static ushort SignalStrength_1
        {
            get
            {
                return (ushort)GenericInfo.WlanInterfaceInstance.CurrentConnection.wlanAssociationAttributes.wlanSignalQuality;
            }
        }

        /// <summary>
        /// This property provides the SINR of the specified interface.
        /// </summary>
        public static ushort SINR_2
        {
            get { throw new NotImplementedException(); }
        }

        /// <summary>
        /// This property provides the Signal Throughput of the specified interface.
        /// </summary>
        public static ushort Throughput_3
        {
            get { throw new NotImplementedException(); }
        }

        /// <summary>
        /// This method provides the Packet Error Rate of the specified interface.
        /// </summary>
        public static ushort PacketErrorRate_4
        {
            get
            {
                uint packetErrorRate = 0;

                IPv4InterfaceStatistics interfaceStatistics = GenericInfo.Interface.GetIPv4Statistics();

                if (interfaceStatistics.NonUnicastPacketsSent != 0)
                {
                    packetErrorRate = Convert.ToUInt16(interfaceStatistics.IncomingPacketsWithErrors / interfaceStatistics.NonUnicastPacketsSent);
                }

                return (ushort) packetErrorRate;
            }
        }
    }
    #endregion

    #region LinkParam80211
    /// <summary>
    /// This class allows the retrieval of several link parameters, according to 802.21 specification for LINK_PARAM_802_11 parameters group.
    /// </summary>
    class Link_Param_802_11
    {
        /// <summary>
        /// This property provides the RSSI of the specified MACAddress'line interface.
        /// </summary>
        public static ushort GetRSSI_0
        {
            get
            {
                return Convert.ToUInt16(GenericInfo.WlanInterfaceInstance.RSSI);
            }
        }

        /// <summary>
        /// (Not Implemented) This property provides the MulticastPacketLossRate of the specified MACAddress'line interface.
        /// </summary>
        public static ushort GetMulticastPacketLossrate_2
        {
            get
            {
                throw new NotImplementedException();
            }
        }
    }
    #endregion
}
