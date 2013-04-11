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
using System.Threading;

//using LINK_SAP_CS_80211.Events.EventClasses;
//using LINK_SAP_CS_80211.Common.Tools;
using LINK_SAP_CS_80211.Information;
using MIH.DataTypes;
using MIH.Utilities;


namespace LINK_SAP_CS_80211.LINK_SAP_80211.Events
{
    class Reports
    {
        private static List<ActiveThreshold> ost;
        public static List<ActiveThreshold> OneShotThresholds { get { if (ost == null) ost = new List<ActiveThreshold>(); return ost; } }

        private static List<ActiveThreshold> at;
        public static List<ActiveThreshold> ActiveThresholds { get { if (at == null) at = new List<ActiveThreshold>(); return at; } }

        private static List<TimedReport> tr;
        public static List<TimedReport> TimedReports { get { if (tr == null) tr = new List<TimedReport>(); return tr; } }

        public static void Cancel(Link_Cfg_Param param)
        {
            if (param.ThresholdList.Count == 0 ) //Kill all
            {
                TimedReport tr;
                do
                {
                    tr = TimedReport.FindTimedReport(param.Link_Param_Type.AbsoluteType, param.Timer_Interval, TimedReports);
                    if (tr!=null)
                    {
                        TimedReports.Remove(tr);
                        tr.Timer.Dispose();
                    }
                } while (tr != null);
                Console.WriteLine("Removed a timed report.");
            }

            foreach (ActiveThreshold a in ActiveThresholds)
            {
                if (a.Param_Type == param.Link_Param_Type.AbsoluteType && param.ThresholdList.Contains(a.Threshold))
                    ActiveThresholds.Remove(a);
            }
        }

        public static void PeriodicReport(Object stateInfo)
        {
            Console.WriteLine("Periodic report called");
            Link_Param_Abs_Type lpat = (Link_Param_Abs_Type)stateInfo;
            Console.WriteLine("Reporting param type " + lpat);
            switch (lpat)
            {
                case Link_Param_Abs_Type.GEN_Sig_Strenth:
                   Program.toMihf.Send(MessageBuilders.Link_Parameters_Report_Indication_MsgBuilder(
                        new ID(new OctetString(GenericInfo.myID)),
                        new ID(new OctetString(GenericInfo.mihfID)),
                        GenericInfo.WlanInterfaceInstance.CurrentConnection.wlanAssociationAttributes.Dot11Bssid,
                        GenericInfo.WlanInterfaceInstance.CurrentConnection.wlanAssociationAttributes.dot11Ssid.SSID,
                        Link_Param_Abs_Type.GEN_Sig_Strenth,
                        Link_Param_Gen.SignalStrength_1).ByteValue);
                    break;
                case Link_Param_Abs_Type.GEN_Data_Rate:
                    Program.toMihf.Send(MessageBuilders.Link_Parameters_Report_Indication_MsgBuilder(
                        new ID(new OctetString(GenericInfo.myID)),
                        new ID(new OctetString(GenericInfo.mihfID)),
                        GenericInfo.WlanInterfaceInstance.CurrentConnection.wlanAssociationAttributes.Dot11Bssid,
                        GenericInfo.WlanInterfaceInstance.CurrentConnection.wlanAssociationAttributes.dot11Ssid.SSID,
                        Link_Param_Abs_Type.GEN_Data_Rate,
                        Link_Param_Gen.DataRate_0).ByteValue);
                    break;
                case Link_Param_Abs_Type.GEN_Packet_Error_Rate:
                    Program.toMihf.Send(MessageBuilders.Link_Parameters_Report_Indication_MsgBuilder(
                        new ID(new OctetString(GenericInfo.myID)),
                        new ID(new OctetString(GenericInfo.mihfID)),
                        GenericInfo.WlanInterfaceInstance.CurrentConnection.wlanAssociationAttributes.Dot11Bssid,
                        GenericInfo.WlanInterfaceInstance.CurrentConnection.wlanAssociationAttributes.dot11Ssid.SSID,
                        Link_Param_Abs_Type.GEN_Packet_Error_Rate,
                        Link_Param_Gen.PacketErrorRate_4).ByteValue);
                    break;
                //TODO other params
            }
        }

        public static void CheckThresholds(Link_Param_Abs_Type type, int value)
        {
            foreach (ActiveThreshold a in OneShotThresholds)
            {
                if (a.Param_Type==type)
                    if (a.CheckIfCrossed(value))
                    {
                        Program.toMihf.Send(MessageBuilders.Link_Parameters_Report_Indication_MsgBuilder(
                            new ID(new OctetString(GenericInfo.myID)),
                            new ID(new OctetString(GenericInfo.mihfID)),
                            GenericInfo.WlanInterfaceInstance.CurrentConnection.wlanAssociationAttributes.Dot11Bssid,
                            GenericInfo.WlanInterfaceInstance.CurrentConnection.wlanAssociationAttributes.dot11Ssid.SSID,
                            type,
                            GenericInfo.GetValueForParam(type)).ByteValue);
                        OneShotThresholds.Remove(a);
                    }
            }

            foreach (ActiveThreshold a in ActiveThresholds)
            {
                if (a.Param_Type == type)
                    if (a.CheckIfCrossed(value))
                        Program.toMihf.Send(MessageBuilders.Link_Parameters_Report_Indication_MsgBuilder(
                            new ID(new OctetString(GenericInfo.myID)),
                            new ID(new OctetString(GenericInfo.mihfID)),
                            GenericInfo.WlanInterfaceInstance.CurrentConnection.wlanAssociationAttributes.Dot11Bssid,
                            GenericInfo.WlanInterfaceInstance.CurrentConnection.wlanAssociationAttributes.dot11Ssid.SSID,
                            type,
                            GenericInfo.GetValueForParam(type)).ByteValue);
            }
        }
    }

    class ActiveThreshold
    {
        public Threshold Threshold{get;set;}
        public Link_Param_Abs_Type Param_Type { get; set; }

        public ActiveThreshold(Threshold t, Link_Param_Abs_Type lpat)
        {
            this.Threshold = t;
            this.Param_Type = lpat;
        }

        public bool CheckIfCrossed(int val)
        {
            switch (Threshold.Threshold_dir)
            {
                case Threshold_X_Dir.ABOVE_THRESHOLD: return Threshold.Threshold_Val < val;
                case Threshold_X_Dir.BELOW_THRESHOLD: return Threshold.Threshold_Val > val;
            }
            return false;
        }

    }
}
