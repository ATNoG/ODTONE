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
using NativeWifi;
using System.Collections;

using MIH.MIHProtocol;
using MIH.DataTypes;
using MIH_Connection.Link;
using System.IO;

namespace LINK_SAP_CS_80211
{
    class Program
    {
        public static ConnectionHelper toMihf;

        #region ConfigParams
        public static string MAC = "";
        private const string configPath = ".\\linksap.cfg";
        public const bool PACKET_LOG = false;
        public const bool RECEIVED_LOG = false;
        public const bool MESSAGE_DETAILS = true;
        #endregion

        static void Main(string[] args)
        {
            Console.WriteLine("LinkSAP For Windows - 802.11");
            Console.WriteLine("______________________________________________");

            using (StreamReader sr = new StreamReader(configPath))
            {
                String var, val, line;
                Dictionary<string, string> vars = new Dictionary<string,string>();
                do
                {
                    line = sr.ReadLine();
                    if(!line.StartsWith("#") && line!="")
                    {

                        var = line.Split("=".ToCharArray())[0].TrimEnd(" ".ToCharArray()).ToLower();
                        val = line.Split("=".ToCharArray())[1].TrimStart(" ".ToCharArray()).TrimEnd(" \n".ToCharArray()).ToLower();
                        vars.Add(var, val);
                    }
                }while(!sr.EndOfStream);
                sr.Close();
                bool sub_LinkDet, sub_LinkUp, sub_LinkDown, sub_LinkParamRpt, sub_LinkGoingDown, sub_HandoverIm, sub_HandoverCm, sub_PDU_TransmitSt;
                String holder;
                vars.TryGetValue("sub_linkdet", out holder);
                sub_LinkDet = Boolean.Parse(holder);

                vars.TryGetValue("sub_linkup", out holder);
                sub_LinkUp = Boolean.Parse(holder);

                vars.TryGetValue("sub_linkdown", out holder);
                sub_LinkDown = Boolean.Parse(holder);

                vars.TryGetValue("sub_linkparamrpt", out holder);
                sub_LinkParamRpt = Boolean.Parse(holder);

                vars.TryGetValue("sub_linkgoingdown", out holder);
                sub_LinkGoingDown = Boolean.Parse(holder);

                vars.TryGetValue("sub_handoverim", out holder);
                sub_HandoverIm = Boolean.Parse(holder);

                vars.TryGetValue("sub_handovercm", out holder);
                sub_HandoverCm = Boolean.Parse(holder);

                vars.TryGetValue("sub_pdu_transmitst", out holder);
                sub_PDU_TransmitSt = Boolean.Parse(holder);

                vars.TryGetValue("interface_mac", out MAC);

                vars.TryGetValue("send_port", out holder);
                ushort port = UInt16.Parse(holder);

                vars.TryGetValue("mihf_ip", out holder);
                System.Net.IPAddress addr = System.Net.IPAddress.Parse(holder);
                toMihf = new ConnectionHelper(port, addr);

                vars.TryGetValue("rcv_port", out holder);
                ushort fromMIHFPort = UInt16.Parse(holder);

                vars.TryGetValue("myid", out holder);
                LINK_SAP_CS_80211.Information.GenericInfo.myID = holder;

                vars.TryGetValue("mihfid", out holder);
                LINK_SAP_CS_80211.Information.GenericInfo.mihfID = holder;

                Common.Events.Subscriptions.Subscribe(new Link_Event_List(sub_LinkDet, sub_LinkUp, sub_LinkDown, sub_LinkParamRpt, sub_LinkGoingDown, sub_HandoverIm, sub_HandoverCm, sub_PDU_TransmitSt));
                Startup.BootUp s = new Startup.BootUp(MAC, fromMIHFPort, addr);
            }
            //WlanClient.WlanInterface interf = Common.Utilities.WlanHelper.getInterfaceByGuid(Startup.BootUp.getGuidForMac("00:22:FA:12:35:16"));

            Console.ReadLine();
        }
    }
}
