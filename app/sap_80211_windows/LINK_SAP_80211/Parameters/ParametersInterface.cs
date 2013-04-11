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
using System.Management;

using MIH.DataTypes;

namespace LINK_SAP_CS_80211.Common.Parameters
{
    #region OneShotParameters
    /// <summary>
    /// This class gathers the necessary mechanisms to handle and configure OneShotParameters Report Requests.
    /// </summary>
    class OneShotParameters
    {
        /// <summary>
        /// The EventList of configured params.
        /// </summary>
        private List<Link_Cfg_Param> configuredOneShotParams;

        /// <summary>
        /// Class main constructor.
        /// </summary>
        public OneShotParameters()
        {
            configuredOneShotParams = new List<Link_Cfg_Param>();
        }

        /// <summary>
        /// This method is reponsible for handling and registering a Link_Cfg_Param.
        /// </summary>
        /// <param name="linkCfgParam">The Link_Cfg_Param.</param>
        public void HandleOneShotParamConf(Link_Cfg_Param linkCfgParam)
        {

            switch (linkCfgParam.Link_Param_Type.Type)
            {
                case Link_Param_Types.LINK_PARAM_GEN:
                    {
                        HandleLinkParamGenType(linkCfgParam);
                        break;
                    }
                case Link_Param_Types.LINK_PARAM_802_11: { break; }
            }
        }

        /// <summary>
        /// This is a "submethod" that handles the Link_Cfg_Param of Generic Type in particular.
        /// </summary>
        /// <param name="linkCfgParam">The Link_Cfg_Param.</param>
        private void HandleLinkParamGenType(Link_Cfg_Param linkCfgParam)
        {
            switch (linkCfgParam.Link_Param_Type.SubType)
            {
                case (int)LINK_PARAM_GEN_SUBTYPES.DataRate:
                    {
                        subscribeLinkParamGen_DataRate(linkCfgParam);
                        break;
                    }
                case (int)LINK_PARAM_GEN_SUBTYPES.PacketErrorRate: { break; }
                case (int)LINK_PARAM_GEN_SUBTYPES.SINR: { break; }
                case (int)LINK_PARAM_GEN_SUBTYPES.Throughtput: { break; }
            }
        }

        /// <summary>
        /// This method handles a Link_Cfg_Param related with the DataRate analisis.
        /// </summary>
        /// <param name="linkCfgParam">The Link_Cfg_Param</param>
        private void subscribeLinkParamGen_DataRate(Link_Cfg_Param linkCfgParam)
        {
            List<LinkParamGenDataRateEventWatcher> thList = new List<LinkParamGenDataRateEventWatcher>();
            foreach (Threshold th in linkCfgParam.ThresholdList)
            {
                LinkParamGenDataRateEventWatcher lpgdre = new LinkParamGenDataRateEventWatcher(th);
                lpgdre.Start();
                thList.Add(lpgdre);
            }

        }
    }

    /// <summary>
    /// This class encapsulates the mecanism for subscribing DataRate events.
    /// </summary>
    class LinkParamGenDataRateEventWatcher
    {
        /// <summary>
        /// The WqlEventQuery
        /// </summary>
        private System.Management.WqlEventQuery wqlquery=null;
        /// <summary>
        /// The ManagementEventWatcher
        /// </summary>
        private ManagementEventWatcher mw=null;
        /// <summary>
        /// The Threshold to subscribe
        /// </summary>
        private Threshold th=null;

        public LinkParamGenDataRateEventWatcher(Threshold th)
        {
            this.th = th;
            subscribeEvent(th);
        }

        private void subscribeEvent(Threshold th)
        {
            string dirSymbol;
            if (th.Threshold_dir == Threshold_X_Dir.ABOVE_THRESHOLD)
                dirSymbol = ">";
            else
                dirSymbol = "<";

            wqlquery = new System.Management.WqlEventQuery("__InstanceModificationEvent"
                , new TimeSpan(0, 0, 1)
                , "TargetInstance isa \"Win32_NetworkAdapter\" AND TargetInstance.GUID='" + Information.GenericInfo.InterfaceGUID + "' AND TargetInstance.Speed " + dirSymbol + th.Threshold_Val);
            mw = new System.Management.ManagementEventWatcher(wqlquery);
            mw.EventArrived += new System.Management.EventArrivedEventHandler(mw_EventArrived);
            mw.Start();
        }

        public void Start()
        {
            mw.Start();
        }

        public void Stop()
        {
            mw.Stop();
        }

        void mw_EventArrived(object sender, System.Management.EventArrivedEventArgs e)
        {
            Console.WriteLine("Link speed crossed threshold! ( " + th.Threshold_Val + " / " + th.Threshold_dir + ")");
            mw.Stop();
        }
    }
    #endregion

    #region PeriodicParameters
    class PeriodicParameters
    {
        /// <summary>
        /// List of Link_Cfg_Param for test only. (In the final release the link_cfg_params will be obtained dinamically).
        /// </summary>
        private List<Link_Cfg_Param> configuredParams;

        private List<KeyValuePair<Link_Cfg_Param, Timer>> configuredPeriodicReports;

        /// <summary>
        /// PeriodicParameters class constructor.
        /// </summary>
        public PeriodicParameters()
        {
            configuredParams = new List<Link_Cfg_Param>();
            configuredPeriodicReports = new List<KeyValuePair<Link_Cfg_Param, Timer>>();
        }

        public void HandlePeriodicParameterConfig(Link_Cfg_Param linkCfgParam)
        {
            throw new System.NotImplementedException();
        }

        public bool RegisterLinkCfgParam(Link_Cfg_Param linkCfgParam)
        {

            Timer timer = new Timer(FindParamCallback(linkCfgParam), null, linkCfgParam.Timer_Interval, linkCfgParam.Timer_Interval);

            if (linkCfgParam.Th_Action == TH_Action.CANCEL_THRESHOLD)
            {
                CancelThreshold(linkCfgParam);
                return true;
            }

            configuredPeriodicReports.Add(new KeyValuePair<Link_Cfg_Param, Timer>(linkCfgParam, timer));

            return true;
        }

        private void CancelThreshold(Link_Cfg_Param linkCfgParam)
        {
            // TODO optimizar condições de verificação. i.e. verificar o tipo de linkcfgparam.

            configuredPeriodicReports.Where(t => t.Key.Link_Param_Type == linkCfgParam.Link_Param_Type && t.Key.Link_Param_Type.SubType == linkCfgParam.Link_Param_Type.SubType).Single().Value.Change(Timeout.Infinite, Timeout.Infinite);
        }

        private TimerCallback FindParamCallback(Link_Cfg_Param linkCfgParam)
        {
            switch (linkCfgParam.Link_Param_Type.Type)
            {
                case Link_Param_Types.LINK_PARAM_GEN:
                    {
                        return LinkParamGenTimerCallBacks.LinkParamGenSubTypeTimerCallBack(linkCfgParam.Link_Param_Type.SubType);
                    }
                case Link_Param_Types.LINK_PARAM_802_11:
                    {
                        return LinkParam80211TimerCallBacks.linkParam80211SubTypeTimerCallBack(linkCfgParam.Link_Param_Type.SubType);
                    }
                default: return null;
            }
        }
     }


    #region LinkParamGenTimerCallBacks
    class LinkParamGenTimerCallBacks
    {
        private static Link_Type linkType = Link_Type.Wireless_IEEE80211;

        public static TimerCallback LinkParamGenSubTypeTimerCallBack(ushort subType)
        {
            switch (subType)
            {
                case 0:
                    {
                        return LinkParamGen_0;
                    }
                case 1:
                    {
                        return LinkParamGen_1;
                    }
                case 2:
                    {
                        return LinkParamGen_2;
                    }
                case 3:
                    {
                        return LinkParamGen_3;
                    }
                case 4:
                    {
                        return LinkParamGen_3;
                    }
                default: return null;
            }

        }

        // TODO callbacks apenas imprimem na consola!
        public static void LinkParamGen_0(object stateInfo)
        {
            Console.WriteLine(ReportBuilder(0, LINK_SAP_CS_80211.Information.Link_Param_Gen.DataRate_0).ToString());
        }

        public static void LinkParamGen_1(object stateInfo)
        {
            Console.WriteLine(ReportBuilder(1, LINK_SAP_CS_80211.Information.Link_Param_Gen.SignalStrength_1).ToString());
        }

        public static void LinkParamGen_2(object stateInfo)
        {
            Console.WriteLine(ReportBuilder(2, LINK_SAP_CS_80211.Information.Link_Param_Gen.SINR_2).ToString());
        }

        public static void LinkParamGen_3(object stateInfo)
        {
            Console.WriteLine(ReportBuilder(3, LINK_SAP_CS_80211.Information.Link_Param_Gen.Throughput_3).ToString());
        }

        public static void LinkParamGen_4(object stateInfo)
        {
            Console.WriteLine(ReportBuilder(4, LINK_SAP_CS_80211.Information.Link_Param_Gen.PacketErrorRate_4).ToString());
        }

        private static Link_Parameters_Report ReportBuilder(ushort subType, ushort value)
        {
            //Link Identification Information
            Link_Addr linkAddr = new Link_Addr(Link_Addr.Address_Type.MAC_ADDR, Information.GenericInfo.PhysicalAddress.ToString());
            Link_Id linkId = new Link_Id(linkType, linkAddr);
            Link_Tuple_Id linkTuppleId = new Link_Tuple_Id(linkId, linkAddr);
            Link_Tuple_Id nicTupple = new Link_Tuple_Id(linkId, linkAddr);

            //Specified Parameter information and report building
            List<Link_Param_Rpt> paramsList = new List<Link_Param_Rpt>();
            Link_Param_Type linkParamType = new Link_Param_Type(Link_Param_Types.LINK_PARAM_GEN, subType);
            Link_Param linkParam = new Link_Param(linkParamType, value);
            Link_Param_Rpt reportSingle = new Link_Param_Rpt(linkParam, null);
            paramsList.Add(reportSingle);
            return new Link_Parameters_Report(nicTupple, paramsList);
        }

    }
    #endregion

    #region LinkParam80211TimerCallBacks
    class LinkParam80211TimerCallBacks
    {
        private static Link_Type linkType = Link_Type.Wireless_IEEE80211;

        public static TimerCallback linkParam80211SubTypeTimerCallBack(ushort subType)
        {
            switch (subType)
            {
                case 0: { return LinkParam80211_0; }
                case 1: { return LinkParam80211_1; }
                default: return null;
            }
        }

        // TODO callbacks apenas imprimem na consola!
        public static void LinkParam80211_0(object stateInfo)
        {
            // TODO verificar situação do RSSI -> uint
            //Console.WriteLine(reportBuilder(0,(Link_Param_802_11.GetRSSI_0(nicMACAddr));
        }

        public static void LinkParam80211_1(object stateInfo)
        {
            Console.WriteLine(reportBuilder(1, Information.Link_Param_802_11.GetMulticastPacketLossrate_2));
        }

        private static Link_Parameters_Report reportBuilder(ushort subType, ushort value)
        {
            //Link Identification Information
            Link_Addr linkAddr = new Link_Addr(Link_Addr.Address_Type.MAC_ADDR, Information.GenericInfo.PhysicalAddress.ToString());
            Link_Id linkId = new Link_Id(linkType, linkAddr);
            Link_Tuple_Id linkTuppleId = new Link_Tuple_Id(linkId, linkAddr);
            Link_Tuple_Id nicTupple = new Link_Tuple_Id(linkId, linkAddr);

            //Specified Parameter information and report building
            List<Link_Param_Rpt> paramsList = new List<Link_Param_Rpt>();
            Link_Param_Type linkParamType = new Link_Param_Type(Link_Param_Types.LINK_PARAM_GEN, subType);
            Link_Param linkParam = new Link_Param(linkParamType, value);
            Link_Param_Rpt reportSingle = new Link_Param_Rpt(linkParam, null);
            paramsList.Add(reportSingle);
            return new Link_Parameters_Report(nicTupple, paramsList);
        }

    }
    #endregion

    #endregion

    #region GetParameters

    class GetParameters
    {
        public void HandleLinkGetParametersRequest(Link_Get_Parameters_Request linkGetParametersRequest)
        {
            Console.WriteLine(linkGetParametersRequest);

            List<Link_Param> linkParams = new List<Link_Param>();

            foreach (Link_Param_Type lpt in linkGetParametersRequest.LinkParametersRequest)
            {
                switch (lpt.Type)
                {
                    case Link_Param_Types.LINK_PARAM_GEN:
                        {
                            linkParams.Add(HandleLinkParamGenParameter(lpt));
                            break;
                        }
                    case Link_Param_Types.LINK_PARAM_802_11:
                        {
                            linkParams.Add(HandleLinkParam80211Parameter(lpt));
                            break;
                        }
                }
            }

            ResponseBuilder(linkParams);
        }

        private Link_Param HandleLinkParamGenParameter(Link_Param_Type linkParamType)
        {
            Link_Param linkParam = new Link_Param();

            linkParam.LinkParamType = linkParamType;

            switch (linkParamType.SubType)
            {
                case (int)LINK_PARAM_GEN_SUBTYPES.DataRate:
                    {
                        linkParam.LinkParamVal = Information.Link_Param_Gen.DataRate_0;
                        break;
                    }
                case (int)LINK_PARAM_GEN_SUBTYPES.PacketErrorRate:
                    {
                        linkParam.LinkParamVal = Information.Link_Param_Gen.PacketErrorRate_4;
                        break;
                    }
                case (int)LINK_PARAM_GEN_SUBTYPES.SignalStrength:
                    {
                        linkParam.LinkParamVal = Information.Link_Param_Gen.SignalStrength_1;
                        break;
                    }
                case (int)LINK_PARAM_GEN_SUBTYPES.SINR:
                    {
                        linkParam.LinkParamVal = Information.Link_Param_Gen.SINR_2;
                        break;
                    }
                case (int)LINK_PARAM_GEN_SUBTYPES.Throughtput:
                    {
                        linkParam.LinkParamVal = Information.Link_Param_Gen.Throughput_3;
                        break;
                    }
            }

            return linkParam;

        }
        private Link_Param HandleLinkParam80211Parameter(Link_Param_Type linkParamType)
        {
            Link_Param linkParam = new Link_Param();

            linkParam.LinkParamType = linkParamType;

            switch (linkParamType.SubType)
            {
                case (int)LINK_PARAM_802_11_SUBTYPES.MulticastPacketLossRate:
                    {
                        linkParam.LinkParamVal = Information.Link_Param_802_11.GetMulticastPacketLossrate_2;
                        break;
                    }
                case (int)LINK_PARAM_802_11_SUBTYPES.RSSI:
                    {
                        linkParam.LinkParamVal = Information.Link_Param_802_11.GetRSSI_0;
                        break;
                    }
                case (int)LINK_PARAM_802_11_SUBTYPES.NoQoS:
                    {
                        linkParam.LinkParamVal = 0;
                        break;
                    }
            }

            return linkParam;
        }

        private void ResponseBuilder(List<Link_Param> linkParams)
        {
            Link_Get_Parameters_Confirm lgpc = new Link_Get_Parameters_Confirm();

            lgpc.Status = STATUS.SUCCESS;
            lgpc.LinkParametersStatusList = linkParams;

            Console.WriteLine(lgpc);
        }
    }

    #endregion
}
