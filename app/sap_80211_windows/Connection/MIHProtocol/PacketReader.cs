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


using MIH.DataTypes;
using MIH.MIHProtocol;
using MIH.Utilities;


namespace LINK_SAP_CS_80211.Connection.MIHProtocol
{
    class PacketReader
    {
        /// <summary>
        /// Prints a serialized message.
        /// </summary>
        /// <param name="m">The serialized message to print.</param>
        public static void PrintMessage(Message m)
        {
            Payload.TLVIterator it =  m.Payload.GetTLVIterator();
            Console.Write("\t(");
            Console.Write(new ID(new OctetString(it.Next().Value)));
            Console.Write(" -> "+ new ID(new OctetString(it.Next().Value)));
            Console.Write(")");
            Console.WriteLine();
            switch (m.MIHHeader.MID.AID)
            {
                case AIDGlobal.COMMAND_SERVICE_MIH_LINK_ACTIONS:
                    if (m.MIHHeader.MID.OpCode == MessageID.OperationCode.REQUEST)
                    {
                        //LINK ACTION REQUEST
                        Console.WriteLine(new Link_Action_Request(MIHDeserializer.DeserializeLinkAction(it.Next()),
                                                    MIHDeserializer.DeserializeTimeInterval(it.Next()),
                                                    MIHDeserializer.DeserializePoA(it.Next())).ToString());
                    }
                    else
                    {
                        //LINK ACTION RESPONSE
                        if (it.Count == 5)
                            Console.WriteLine(new Link_Action_Response(MIHDeserializer.DeserializeStatus(it.Next()),
                                                    MIHDeserializer.DeserializeLinkScanRspList(it.Next()),
                                                    MIHDeserializer.DeserializeLinkAcResult(it.Next())));
                        else
                            Console.WriteLine(new Link_Action_Response(MIHDeserializer.DeserializeStatus(it.Next()),
                                                    new List<byte[]>(),
                                                    MIHDeserializer.DeserializeLinkAcResult(it.Next())));
                    }
                    break;
                case AIDGlobal.EVENT_SERVICE_MIH_LINK_UP:
                    Console.WriteLine(new Link_Up(MIHDeserializer.DeserializeLinkTupleId(it.Next()), null, null));
                    break;
                case AIDGlobal.EVENT_SERVICE_MIH_LINK_DOWN:
                    Console.WriteLine(
                        it.Count<5?
                        new Link_Down(MIHDeserializer.DeserializeLinkTupleId(it.Next()),
                            null,
                            MIHDeserializer.DeserializeLinkDnReason(it.Next()))
                            :
                        new Link_Down(MIHDeserializer.DeserializeLinkTupleId(it.Next()),
                            MIHDeserializer.DeserializeOldAccessRouter(it.Next()),
                            MIHDeserializer.DeserializeLinkDnReason(it.Next()))
                            );
                    break;
                case AIDGlobal.EVENT_SERVICE_MIH_LINK_DETECTED:
                    Console.WriteLine(new Link_Detected(MIHDeserializer.DeserializeLinkDetInfo(it.Next())));
                    break;
                case AIDGlobal.COMMAND_SERVICE_MIH_LINK_GET_PARAMETERS:
                    if (m.MIHHeader.MID.OpCode == MessageID.OperationCode.REQUEST)
                        Console.WriteLine(new Link_Get_Parameters_Request(MIHDeserializer.DeserializeLinkParamRequest(it.Next()),
                            it.Next().Value, it.Next().Value));
                    else
                        Console.WriteLine(new Link_Get_Parameters_Confirm(MIHDeserializer.DeserializeStatus(it.Next()),
                            MIHDeserializer.DeserializeLinkParamStatusList(it.Next()),
                            MIHDeserializer.DeserializeLinkStatesResponse(it.Next()),
                            MIHDeserializer.DeserializeLinkDescriptorsResponse(it.Next())));
                break;
                default: Console.WriteLine("N/A"); break;
            }
        }

    }
}
