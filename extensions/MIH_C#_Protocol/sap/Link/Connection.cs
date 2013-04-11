//==============================================================================
// Brief   : Class representing a Connection.cs entity
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
using System.Net;
using System.Net.Sockets;
using ProtocolHeaderDefinition;
using System.Collections;
using System.Threading;

namespace MIH_Connection.Link
{
    /// <summary>
    /// Class responsible for providing tools to establish connections with
    /// MIHF and to build and send UDP datagrams with MIH Protocol messsages.
    /// </summary>
    public class ConnectionHelper
    {
        /// <summary>
        /// Link_sap IP Address. Default: 127.0.0.1.
        /// </summary>
        private IPAddress link_sap_address = IPAddress.Parse("127.0.0.1");
        /// <summary>
        /// Link_sap local port. Default: 1235
        /// </summary>
        private ushort link_sap_port = 1235;

        /// <summary>
        /// MIHF IP Address. Default: 127.0.0.1.
        /// </summary>
        private IPAddress mihf_address = IPAddress.Parse("127.0.0.1");
        /// <summary>
        /// MIHF local port. Default: 1025
        /// </summary>
        private ushort mihf_port = 1025;

        /// <summary>
        /// IP Address to bind the socket to.
        /// </summary>
        private IPAddress bind_address = IPAddress.Any;

        /// <summary>
        /// IPEndPoint of the MIHF instance.
        /// </summary>
        private IPEndPoint IPEnd;


        /// <summary>
        /// Packet Headers
        /// </summary>
        private byte[] built_packet;
        private byte[] payLoad;
        private UdpHeader udpPacket = new UdpHeader();
        private ArrayList headerList = new ArrayList();
        private Socket rawSocket = null;
        private SocketOptionLevel socketLevel = SocketOptionLevel.IP;


        /// <summary>
        /// ConnectionHelper constructor.
        /// </summary>
        /// <param name="linkSapPort">The LinkSap communication port.</param>
        /// <param name="address">The IPAddress of this connection.</param>
        public ConnectionHelper(ushort linkSapPort, IPAddress address)
        {
            this.link_sap_port = linkSapPort;
            IPEnd = new IPEndPoint(address, mihf_port);
        }


        /// <summary>
        /// Receive Method.
        /// </summary>
        /// <returns>Data in a byte array form.</returns>
        public byte[] Receive()
        {
            using (UdpClient client = new UdpClient(link_sap_port))
            {
                byte[] rcvd = client.Receive(ref IPEnd);
                BitArray bar = new BitArray(rcvd);
                //LOGHERE
                //Console.WriteLine("Received "+rcvd.Length +" bytes");
                //if (Program.PACKET_LOG)
                //{
                //    Console.WriteLine("----------------");
                //    StringBuilder sb = new StringBuilder();
                //    foreach (byte b in rcvd)
                //        Console.Write(b.ToString("X2") + "\t");
                //    Console.WriteLine();
                //    Console.WriteLine("----------------");
                //}
                return rcvd;
            }
        }


        /// <summary>
        /// Send method.
        /// </summary>
        /// <param name="m">Serialized MIH Protocol message.</param>
        public void Send(byte[] m)
        {
            //if (Program.MESSAGE_DETAILS)
            //{
            //    Console.WriteLine("Sending message: ");
            //    Connection.MIHProtocol.PacketReader.PrintMessage(m);
            //}
            do
            {
                try
                {
                    using (UdpClient client = new UdpClient(link_sap_port))
                    {
                        client.Connect(IPEnd);
                        //LOGHERE
                        //Console.WriteLine("Sending " + m.ByteValue.Length + " bytes ("+m.MIHHeader.MID.AID+")");
                        //if (Program.PACKET_LOG)
                        //{
                        //    Console.WriteLine("----------------");
                        //    StringBuilder sb = new StringBuilder();
                        //    foreach (byte b in m.ByteValue)
                        //        Console.Write(b.ToString("X2") + "\t");
                        //    Console.WriteLine();
                        //    Console.WriteLine("----------------");
                        //}
                        client.Send(m, m.Length);
                        client.Close();
                        return;
                    }
                }
                catch (Exception e) {
                    Console.WriteLine(e.Message);
                    Console.WriteLine("Retrying...");
                    Console.WriteLine();
                    Thread.Sleep(new Random().Next(10, 1000)); } //Port in use error (caused by muti-threading), retry
            } while (true);
        }


    }
}
