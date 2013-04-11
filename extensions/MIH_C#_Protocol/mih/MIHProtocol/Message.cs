//==============================================================================
// Brief   : Class representing a Message.cs entity
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
using System.Collections;

using MIH.DataTypes;
using MIH.MIHProtocol;
using MIH.Utilities;

namespace MIH.MIHProtocol
{
    #region MIH Message Enums
    /// <summary>
    /// Service Management Actions Identifiers.
    /// </summary>
    enum AIDServiceManagement
    {
        MIH_CAPABILITY_DISCOVER = 1,
        MIH_REGISTER = 2,
        MIH_DEREGISTER = 3,
        MIH_EVENT_SUBSCRIBE = 4,
        MIH_EVENT_UNSUBSCRIBE = 5
    }

    /// <summary>
    /// Event Service Actions Identifiers.
    /// </summary>
    enum AIDEventService
    {
        MIH_LINK_DETECTED = 1,
        MIH_LINK_UP = 2,
        MIH_LINK_DOWN = 3,
        MIH_LINK_PARAMETERS_REPORT = 5,
        MIH_LINK_GOING_DOWN = 6,
        MIH_LINK_HANDOVER_IMMINENT = 7,
        MIH_LINK_HANDOVER_COMPLETE = 8
    }

    /// <summary>
    /// Command Service Actions Identifiers.
    /// </summary>
    enum AIDCommandService
    {
        MIH_LINK_GET_PARAMETERS = 1,
        MIH_LINK_CONFIGURE_THRESHOLDS = 2,
        MIH_LINK_ACTIONS = 3,
        MIH_NET_HO_CANDIDATE_QUERY = 4,
        MIH_MN_HO_CANDIDATE_QUERY = 5,
        MIH_N2N_HO_QUERY_RESOURCES = 6,
        MIH_MN_HO_COMMIT = 7,
        MIH_NET_HO_COMMIT = 8,
        MIH_N2N_HO_COMMIT = 9,
        MIH_MN_HO_COMPLETE = 10,
        MIH_N2N_HO_COMPLETE = 11
    }

    /// <summary>
    /// Information Service Actions Identifier.
    /// </summary>
    enum AIDInformationService
    {
        MIH_GET_INFORMATION = 1,
        MIH_PUSH_INFORMATION = 2
    }
    /// <summary>
    /// Global AID
    /// </summary>
    public enum AIDGlobal
    {
        SERVICE_MANAGEMENT_MIH_CAPABILITY_DISCOVER,
        SERVICE_MANAGEMENT_MIH_REGISTER,
        SERVICE_MANAGEMENT_MIH_DEREGISTER,
        SERVICE_MANAGEMENT_MIH_EVENT_SUBSCRIBE,
        SERVICE_MANAGEMENT_MIH_EVENT_UNSUBSCRIBE,
        EVENT_SERVICE_MIH_LINK_DETECTED,
        EVENT_SERVICE_MIH_LINK_UP,
        EVENT_SERVICE_MIH_LINK_DOWN,
        EVENT_SERVICE_MIH_LINK_PARAMETERS_REPORT,
        EVENT_SERVICE_MIH_LINK_GOING_DOWN,
        EVENT_SERVICE_MIH_LINK_HANDOVER_IMMINENT,
        EVENT_SERVICE_MIH_LINK_HANDOVER_COMPLETE,
        COMMAND_SERVICE_MIH_LINK_GET_PARAMETERS,
        COMMAND_SERVICE_MIH_LINK_CONFIGURE_THRESHOLDS,
        COMMAND_SERVICE_MIH_LINK_ACTIONS,
        COMMAND_SERVICE_MIH_NET_HO_CANDIDATE_QUERY,
        COMMAND_SERVICE_MIH_MN_HO_CANDIDATE_QUERY,
        COMMAND_SERVICE_MIH_N2N_HO_QUERY_RESOURCES,
        COMMAND_SERVICE_MIH_MN_HO_COMMIT,
        COMMAND_SERVICE_MIH_NET_HO_COMMIT,
        COMMAND_SERVICE_MIH_N2N_HO_COMMIT,
        COMMAND_SERVICE_MIH_MN_HO_COMPLETE,
        COMMAND_SERVICE_MIH_N2N_HO_COMPLETE,
        INFORMATION_SERVICE_MIH_GET_INFORMATION,
        INFORMATION_SERVICE_MIH_PUSH_INFORMATION
    }

    #endregion

    #region Message ID

    //////////////////////////////////////// MESSAGE ID
    /// <summary>
    /// The Message ID for an MIH message.
    /// </summary>
    public class MessageID
    {
        /// <summary>
        /// Different Values for the ServiceIdentifier
        /// </summary>
        public enum ServiceIdentifier
        {
            SERVICE_MANAGEMENT = 1,
            EVENT_SERVICE = 2,
            COMMAND_SERVICE = 3,
            INFORMATION_SERVICE = 4
        }
        /// <summary>
        /// Different types of the OperationCode.
        /// </summary>
        public enum OperationCode
        {
            CONFIRM = 0,
            REQUEST = 1,
            RESPONSE = 2,
            INDICATION = 3
        }
        /// <summary>
        /// Service Identifier for the different MIH services.
        /// </summary>
        public ServiceIdentifier SID { get; set; }

        /// <summary>
        /// Type of operation to be performed with respect to the SID.
        /// </summary>
        public OperationCode OpCode { get; set; }

        /// <summary>
        /// This indicates the action idetification value.
        /// </summary>
        public ushort AIDValue { get; set; }

        /// <summary>
        /// This indicates the action to be taken with regard to the SID.
        /// </summary>
        public AIDGlobal AID
        {
            get
            {
                return GetAID(SID, AIDValue);
            }
        }

        /// <summary>
        /// MessageID main constructor.
        /// </summary>
        /// <param name="serviceIdentifier">The Service Identifier (MIH Services).</param>
        /// <param name="operationCode">The Operation Code.</param>
        /// <param name="AID">The Action Identifier.</param>
        public MessageID(ServiceIdentifier serviceIdentifier, OperationCode operationCode, ushort AID)
        {
            this.SID = serviceIdentifier;
            this.OpCode = operationCode;
            this.AIDValue = AID;
        }

        /// <summary>
        /// MessageID alternative constructor.
        /// </summary>
        /// <param name="serviceIdentifier">The Service Identifier (MIH Services).</param>
        /// <param name="operationCode">The Operation Code.</param>
        /// <param name="AID">The Action Identifier.</param>
        public MessageID(int serviceIdentifier, int operationCode, ushort AID)
        {
            this.SID = (MessageID.ServiceIdentifier)Enum.ToObject(typeof(MessageID.ServiceIdentifier), serviceIdentifier);
            this.OpCode = (MessageID.OperationCode)Enum.ToObject(typeof(MessageID.OperationCode), operationCode);
            this.AIDValue = AID;
        }

        /// <summary>
        /// MessageID Empty constructor.
        /// </summary>
        public MessageID()
        {
            // TODO: Complete member initialization
        }

        /// <summary>
        /// Deserialization constructor for this object.
        /// </summary>
        /// <param name="messageId">Raw serialized MessageID object.</param>
        public MessageID(byte[] messageId)
        {
            //OCTECT1 -> SID (4 bits), OpCode (2 bits)
            //OCTECT1+2 -> AID (10 bits)

            SID = (ServiceIdentifier)((int)(messageId[0] & 0xF0) >> 4);
            OpCode = (OperationCode)((int)(messageId[0] & 0x0C) >> 2);
            AIDValue = Convert.ToUInt16(messageId[1]);
            //LOGHERE
            //if (Program.RECEIVED_LOG)
            //{
            //    Console.WriteLine("Service Identifier: " + SID);
            //    Console.WriteLine("Operation Code: " + OpCode);
            //    Console.WriteLine("Action ID: " + GetAID(SID, AIDValue));
            //}

        }

        /// <summary>
        /// Returns the 16-bit serialized MID
        /// </summary>
        public BitArray getBitArray()
        {
            BitArray result = new BitArray(16);
            int currPos = 0;
            //SID
            byte[] auxBytes = BitConverter.GetBytes((int)SID);
            BitArray aux = new BitArray(auxBytes);
            for (int i = 0; i < 4; i++)
                result[currPos++] = i < aux.Count ? aux[3 - i] : false;
            //OPCODE
            auxBytes = BitConverter.GetBytes((int)OpCode);
            aux = new BitArray(auxBytes);
            for (int i = 0; i < 2; i++)
                result[currPos++] = i < aux.Count ? aux[1 - i] : false;
            //AID
            auxBytes = BitConverter.GetBytes(AIDValue);
            aux = new BitArray(auxBytes);
            for (int i = 0; i < 10; i++)
                result[currPos++] = i < aux.Count ? aux[9 - i] : false;

            return result;

        }

        /// <summary>
        /// Retrieves a AID specification based on a given SID e AID.
        /// </summary>
        /// <param name="sid">Service Indentifier</param>
        /// <param name="aid">Action Identifier</param>
        /// <returns></returns>
        private AIDGlobal GetAID(ServiceIdentifier sid, ushort aid)
        {
            switch (sid)
            {
                case ServiceIdentifier.SERVICE_MANAGEMENT:
                    {
                        switch (aid)
                        {
                            case 1: { return AIDGlobal.SERVICE_MANAGEMENT_MIH_CAPABILITY_DISCOVER; }
                            case 2: { return AIDGlobal.SERVICE_MANAGEMENT_MIH_REGISTER; }
                            case 3: { return AIDGlobal.SERVICE_MANAGEMENT_MIH_DEREGISTER; }
                            case 4: { return AIDGlobal.SERVICE_MANAGEMENT_MIH_EVENT_SUBSCRIBE; }
                            case 5: { return AIDGlobal.SERVICE_MANAGEMENT_MIH_EVENT_UNSUBSCRIBE; }
                        }
                        break;
                    }
                case ServiceIdentifier.EVENT_SERVICE:
                    {
                        switch (aid)
                        {
                            case 1: { return AIDGlobal.EVENT_SERVICE_MIH_LINK_DETECTED; }
                            case 2: { return AIDGlobal.EVENT_SERVICE_MIH_LINK_UP; }
                            case 3: { return AIDGlobal.EVENT_SERVICE_MIH_LINK_DOWN; }
                            case 5: { return AIDGlobal.EVENT_SERVICE_MIH_LINK_PARAMETERS_REPORT; }
                            case 6: { return AIDGlobal.EVENT_SERVICE_MIH_LINK_GOING_DOWN; }
                            case 7: { return AIDGlobal.EVENT_SERVICE_MIH_LINK_HANDOVER_IMMINENT; }
                            case 8: { return AIDGlobal.EVENT_SERVICE_MIH_LINK_HANDOVER_COMPLETE; }
                        }
                        break;
                    }
                case ServiceIdentifier.INFORMATION_SERVICE:
                    {
                        switch (aid)
                        {
                            case 1: { return AIDGlobal.INFORMATION_SERVICE_MIH_GET_INFORMATION; }
                            case 2: { return AIDGlobal.INFORMATION_SERVICE_MIH_PUSH_INFORMATION; }
                        }
                        break;
                    }
                case ServiceIdentifier.COMMAND_SERVICE:
                    {
                        switch (aid)
                        {
                            case 1: { return AIDGlobal.COMMAND_SERVICE_MIH_LINK_GET_PARAMETERS; }
                            case 2: { return AIDGlobal.COMMAND_SERVICE_MIH_LINK_CONFIGURE_THRESHOLDS; }
                            case 3: { return AIDGlobal.COMMAND_SERVICE_MIH_LINK_ACTIONS; }
                            case 4: { return AIDGlobal.COMMAND_SERVICE_MIH_NET_HO_CANDIDATE_QUERY; }
                            case 5: { return AIDGlobal.COMMAND_SERVICE_MIH_MN_HO_CANDIDATE_QUERY; }
                            case 6: { return AIDGlobal.COMMAND_SERVICE_MIH_N2N_HO_QUERY_RESOURCES; }
                            case 7: { return AIDGlobal.COMMAND_SERVICE_MIH_MN_HO_COMMIT; }
                            case 8: { return AIDGlobal.COMMAND_SERVICE_MIH_NET_HO_COMMIT; }
                            case 9: { return AIDGlobal.COMMAND_SERVICE_MIH_N2N_HO_COMMIT; }
                            case 10: { return AIDGlobal.COMMAND_SERVICE_MIH_MN_HO_COMPLETE; }
                            case 11: { return AIDGlobal.COMMAND_SERVICE_MIH_N2N_HO_COMPLETE; }
                        }
                        break;
                    }
            }
            return 0;
        }
    }
    //////////////////////////////////////// EOF MESSAGE ID

    #endregion

    #region MIH Header
    //////////////////////////////////////// MIH HEADER

    /// <summary>
    /// The header for a MIH message.
    /// </summary>
    public class MIHHeader
    {
        /// <summary>
        /// Multiple versions of MIH protocol.
        /// </summary>
        public enum VersionTypes
        {
            NOT_TO_BE_USED = 0,
            FIRST_VERSION = 1
        }


        private byte verVal;
        /// <summary>
        /// MIHHeader Version Value.
        /// </summary>
        public byte VersionValue
        {
            get { return verVal; }
            set
            {
                byte[] b;
                byte mask = 0x0F;

                b = BitConverter.GetBytes(value);
                verVal = (byte)(b[0] & mask);
            }
        }

        /// <summary>
        /// Used for requesting an acknowledgement for the message.
        /// </summary>
        public bool AckReq { get; set; }

        /// <summary>
        /// Used for responding to the request for an acknowledgement for the message.
        /// </summary>
        public bool AckResp { get; set; }

        /// <summary>
        /// Unauthenticated Information Request, used by the MIHF Information service, to indicate if the protocol message is sent in pre-authentication/pre-
        /// association state, so that the length of the response message can be limited.
        /// </summary>
        public bool UIR { get; set; }

        /// <summary>
        /// More Fragment. Used for indicating that the message is a fragment to be fallowed by another fragment.
        /// </summary>
        public bool M { get; set; }

        private byte fn;
        /// <summary>
        /// Fragment Number. Represents the sequence number of a fragment.
        /// </summary>
        public byte FN
        {
            get { return fn; }
            set
            {
                byte[] b;
                byte mask = 0x03;

                b = BitConverter.GetBytes(value);
                fn = (byte)(b[0] & mask);
            }
        }

        /// <summary>
        /// MIH Message ID.
        /// </summary>
        public MessageID MID { get; set; }

        private byte rsvd2;
        /// <summary>
        /// Reserved 2 bits.
        /// </summary>
        public byte RSVD2
        {
            get { return rsvd2; }
            set
            {
                byte[] ba = BitConverter.GetBytes(value);
                ba[0] = (byte) (ba[0] | (ba[0] & 0x0F));

                rsvd2 = ba[0];
            }
        }

        /// <summary>
        /// Variable Payload Length. The total length of the variable payload embedded in the respective MIH protocol frame.
        /// </summary>
        public UInt16 PayloadLength { get; set; }

        /// <summary>
        /// Transaction ID. Used for matching Request and Response, as well as matching Request, Response and Indication to an ACK.
        /// </summary>
        public UInt16 TransactionID { get; set; }

        /*private byte[] byteVal;
        /// <summary>
        /// Serialized byte[] representation of this object.
        /// </summary>
        public byte[] ByteValue
        {
            get
            {
                GenerateValue();
                return byteVal;
            }
            private set { byteVal = value; }
        }*/

        /// <summary>
        /// Empty constructor.
        /// </summary>
        public MIHHeader() { }

        /// <summary>
        /// MIH Header Main Constructor.
        /// </summary>
        /// <param name="version">MIH Protocol Version</param>
        /// <param name="ackReq">Acknowledgement Request</param>
        /// <param name="ackResp">Acknowledgement Response</param>
        /// <param name="uir">Unauthenticated Information Request</param>
        /// <param name="m">More Fragment</param>
        /// <param name="fn">Fragment Number</param>
        /// <param name="mid">Message ID</param>
        /// <param name="rsvd2">Reserved 2</param>
        /// <param name="payloadLength">Payload Length</param>
        /// <param name="transactionId">Transaction ID</param>
        public MIHHeader(byte version, bool ackReq, bool ackResp, bool uir, bool m, byte fn, MessageID mid, byte rsvd2, UInt16 payloadLength, UInt16 transactionId ) 
        {
            VersionValue = version;
            AckReq = ackReq;
            AckResp = ackResp;
            UIR = uir;
            M = m;
            FN = fn;
            MID = mid;
            RSVD2 = rsvd2;
            PayloadLength = payloadLength;
            TransactionID = transactionId;
        }

        /// <summary>
        /// Serialized byte[] representation of this object.
        /// </summary>
        public byte[] ByteValue { get { return getBytes(); } }
        private byte[] getBytes()
        {

            BitArray finalBits = new BitArray(64);
            int bitArrayPos = 0;
            byte[] aux = new byte[1];
            aux[0] = VersionValue;
            BitArray holder = new BitArray(aux);
            for (bitArrayPos = 0; bitArrayPos < 4; bitArrayPos++)
                finalBits.Set(bitArrayPos, 3-bitArrayPos < holder.Count ? holder[3-bitArrayPos] : false);

            finalBits.Set(bitArrayPos++, AckReq);
            finalBits.Set(bitArrayPos++, AckResp);
            finalBits.Set(bitArrayPos++, UIR);
            finalBits.Set(bitArrayPos++, M);

            //@bit8
            aux[0] = FN;
            holder = new BitArray(aux);
            for (int i = 0; i < 7; i++)
                finalBits.Set(bitArrayPos++, 6-i < holder.Count ? holder[6-i] : false);

            finalBits.Set(bitArrayPos++, false); //RESERVED

            //@bit16
            holder = MID.getBitArray();
            for (int i = 0; i < 16; i++)
                finalBits.Set(bitArrayPos++, i < holder.Count ? holder[i] : false);

            //@bit32
            aux[0] = RSVD2;
            holder = new BitArray(aux);
            for (int i = 0; i < 2; i++)
                finalBits.Set(bitArrayPos++, 1-i < holder.Count ? holder[1-i] : false);

            aux[0] = Convert.ToByte(TransactionID);
            holder = new BitArray(aux);
            for (int i = 0; i < 14; i++)
                finalBits.Set(bitArrayPos++, 13-i < holder.Count ? holder[13-i] : false);

            //@bit48
            byte[] aux2 = new byte[2];
            aux2[0] = BitConverter.GetBytes(PayloadLength)[0];
            aux2[1] = BitConverter.GetBytes(PayloadLength)[1];
            holder = new BitArray(aux2);
            for (int i = 0; i < 16; i++)
                finalBits.Set(bitArrayPos++, 15-i < holder.Count ? holder[15-i] : false);

            //@bit64

            /*Console.WriteLine("----------------Bits");
            StringBuilder sb = new StringBuilder();
            foreach (bool b in finalBits)
                Console.Write(b ? "0" : "1");
            Console.WriteLine();
            Console.WriteLine("----------------//bits");*/
            return Utilities.Utilities.ToByteArray(finalBits);
        }


        /// <summary>
        /// This constructor allows the build of a MIHHeader object based on a byte array which contains a MIHMessage.
        /// </summary>
        /// <param name="mihHeader"></param>
        public MIHHeader(byte[] mihHeader)
        {

            // TODO melhorar a obtenção dos campos, ver implementação do construtor do Message ID.

            //OCTET1 -> Version (4bits), AckResp (1bit), AckRsp (1bit), UIR (1bit), M (1bit)

            byte[] aux = new byte[1];
            aux[0] = mihHeader[0];
            BitArray OCTET1 = new BitArray(aux);
            //Utilities.Utilities.ReverseBitArray(OCTET1);
            if (OCTET1.Count != 0)
            {
                BitArray version = new BitArray(8);
                for (int i = 0; i < 4; i++)
                {
                    version.Set(7-i, OCTET1.Get(4+i));
                }
                VersionValue = (byte)GetIntFromBitArray(version);
                AckReq = OCTET1.Get(3);
                AckResp = OCTET1.Get(2);
                UIR = OCTET1.Get(1);
                M = OCTET1.Get(0);

                //LOGHERE
                //if (Program.RECEIVED_LOG)
                //{
                //    Console.WriteLine("Version: " + VersionValue);
                //    Console.WriteLine("AckReq: " + AckReq);
                //    Console.WriteLine("AckResp: " + AckResp);
                //    Console.WriteLine("UIR: " + UIR);
                //    Console.WriteLine("M: " + M);
                //}
            }


            //OCTECT2 -> FN (7 bits), Reserved 1 (1bit, Filled with 0 by default)

            aux[0] = mihHeader[1];
            BitArray OCTET2 = new BitArray(aux);
            Utilities.Utilities.ReverseBitArray(OCTET2);

            if (OCTET2.Count != 0)
            {

                BitArray fragmentNumber = new BitArray(7);

                for (int i = 0; i < 7; i++)
                {
                    fragmentNumber[i] = OCTET2[i];
                }
                FN = (byte)GetUshortFromBitArray(fragmentNumber);
            }
            else
            {
                FN = 0;
            }

            //LOGHERE
            //if (Program.RECEIVED_LOG)
            //    Console.WriteLine("Fragment no.: " + FN);

            //OCTET3 AND OCTECT4 -> MIH Message ID

            MID = new MessageID(mihHeader.Skip(2).Take(2).ToArray());

            //OCTECT5 and OCTECT6 -> Reserved2 (4 bits, filled with 0's by default), Transaction ID (12 bits).

            BitArray OCTECT5and6 = new BitArray(mihHeader.Skip(4).Take(2).ToArray());
            Utilities.Utilities.ReverseBitArray(OCTECT5and6);
            if (OCTECT5and6.Count != 0)
            {

                BitArray transactionID = new BitArray(12);

                for (int i = 0, j = 4; i < 12; i++, j++)
                {
                    transactionID[i] = OCTECT5and6[j];
                }

                Utilities.Utilities.ReverseBitArray(transactionID);
                TransactionID = Convert.ToUInt16(GetIntFromBitArray(transactionID));
            }
            else
            {
                TransactionID = 0;
            }

            //LOGHERE
            //if (Program.RECEIVED_LOG)
            //    Console.WriteLine("Transaction ID: " + TransactionID);

            //OCTECT7 and OCTECT8 -> Variable Payload Length

            BitArray payloadLength = new BitArray(mihHeader.Skip(6).Take(2).ToArray());
            Utilities.Utilities.ReverseBitArray(payloadLength);

            PayloadLength = Convert.ToUInt16(GetIntFromBitArray(payloadLength));

            //LOGHERE
            //if (Program.RECEIVED_LOG)
            //    Console.WriteLine("Payload Length: "+PayloadLength);

        }

        /// <summary>
        /// Retrieves a Int value from a given BitArray.
        /// </summary>
        /// <param name="bitArray">The BitArray</param>
        /// <returns>Int value</returns>
        public static int GetIntFromBitArray(BitArray bitArray)
        {
            /*int[] array = new int[1];
            bitArray.CopyTo(array, 0);
            return array[0];*/

            return Utilities.Utilities.ToByteArray(bitArray)[0];
        }

        /// <summary>
        /// Retrieves a Ushort value from a given BitArray.
        /// </summary>
        /// <param name="bitArray">The BitArray</param>
        /// <returns>Ushort value</returns>
        public static ushort GetUshortFromBitArray(BitArray bitArray)
        {
            /*ushort[] array = new ushort[1];
            bitArray.CopyTo(array, 0);
            return array[0];*/
            return (ushort)Utilities.Utilities.ToByteArray(bitArray)[0];
        }

        /// <summary>
        /// Retrieves a Uint value from a given BitArray.
        /// </summary>
        /// <param name="bitArray">The BitArray</param>
        /// <returns>Ushort value</returns>
        public static uint GetUintFromBitArray(BitArray bitArray)
        {
            /*uint[] array = new uint[1];
            bitArray.CopyTo(array, 0);
            return array[0];*/
            return (ushort)Utilities.Utilities.ToByteArray(bitArray)[0];
        }

        /*/// <summary>
        /// Generates the byte[] value of the MIH Header.
        /// </summary>
        private void GenerateValue()
        {
            ByteValue = this.getBytes();
        }*/

    }
    //////////////////////////////////////// EOF MIH HEADER
    #endregion

    #region Payload

    /// <summary>
    /// This class represents the message Payload.
    /// </summary>
    public class Payload
    {
        /// <summary>
        /// The Source ID from this MIH payload.
        /// </summary>
        public ID SrcID
        {
            get
            {
                return new ID(new OctetString(PayloadValue.Skip(2).Take(PayloadValue[1]).ToArray()));
            }
        }

        /// <summary>
        /// The Destination ID from this MIH payload.
        /// </summary>
        public ID DstID
        {
            get
            {
                return new ID(new OctetString(PayloadValue.Skip(2 + PayloadValue[1] + 2).Take(2 + PayloadValue[1] + 1).ToArray()));
            }
        }

        /// <summary>
        /// Class that represents an iterator that goes through all the TLVs in a payload.
        /// </summary>
        public class TLVIterator
        {
            private int currentTLV = 0;
            private int[][] TLOs;
            private byte[] plVal;

            /// <summary>
            /// Default constructor for this iterator.
            /// </summary>
            /// <param name="plVal">The serialized payload value.</param>
            public TLVIterator(byte[] plVal)
            {
                TLOs = MIHDeserializer.getTLsFromPayload(plVal).ToArray();
                this.plVal = plVal;
            }

            /// <summary>
            /// The number of TLVs in this payload.
            /// </summary>
            public int Count { get { return TLOs.Count(); } }

            /// <summary>
            /// Gets the next TLV from the payload.
            /// </summary>
            /// <returns>A KeyValuePair representing the type of </returns>
            public KeyValuePair<int, byte[]> Next()//<Type, Content>
            {
                if (HasNext())
                    return new KeyValuePair<int, byte[]>(TLOs[currentTLV][0], plVal.Skip(TLOs[currentTLV][2]).Take(TLOs[currentTLV++][1]).ToArray());
                else
                    return new KeyValuePair<int,byte[]>(-1, null);
            }

            /// <summary>
            /// Checks if the iterator has any TLV to iterate to.
            /// </summary>
            /// <returns>True if there's more data, false otherwise.</returns>
            public bool HasNext()
            {
                return currentTLV < TLOs.Length;
            }



        }

        /// <summary>
        /// Returns a TLV iterator for this payload.
        /// </summary>
        /// <see cref="TLVIterator"/>
        /// <returns>A new TLV iterator for this payload's value.</returns>
        public TLVIterator GetTLVIterator()
        { return new TLVIterator(PayloadValue); }

        /// <summary>
        /// Payload byte[] value.
        /// </summary>
        public byte[] PayloadValue { get; set; }

        /// <summary>
        /// Constructs a message with only the Source and Destination's ID.
        /// </summary>
        /// <param name="source">Source ID</param>
        /// <param name="destination">Destination ID</param>
        public Payload(ID source, ID destination)
        {
            PayloadValue = Serialization.Sequence(
                Serialization.SerializeToTLV(TLV_VALUES.TLV_MIHF_ID_SOURCE, source.ByteValue),
                Serialization.SerializeToTLV(TLV_VALUES.TLV_MIHF_ID_DESTINATION, destination.ByteValue));

        }
        /// <summary>
        /// Constructs a message with the Source ID, Destination ID and one parameter.
        /// </summary>
        /// <param name="source">Source ID</param>
        /// <param name="destination">Destination ID</param>
        /// <param name="param1">Parameter</param>
        public Payload(ID source, ID destination, byte[] param1)
        {
            //Console.WriteLine("Creating payload...\tSrc: " + new String(Encoding.ASCII.GetChars(source.ByteValue.Skip(1).ToArray())) + "\tDst: " + new String(Encoding.ASCII.GetChars(destination.ByteValue.Skip(1).ToArray())));
            PayloadValue = Serialization.Sequence(
                Serialization.SerializeToTLV(TLV_VALUES.TLV_MIHF_ID_SOURCE, source.ByteValue),
                Serialization.SerializeToTLV(TLV_VALUES.TLV_MIHF_ID_DESTINATION, destination.ByteValue),
                param1);
        }
        /// <summary>
        /// Constructs a message with the Source ID, Destination ID and two parameters.
        /// </summary>
        /// <param name="source">Source ID</param>
        /// <param name="destination">Destination ID</param>
        /// <param name="param1">Parameter One</param>
        /// <param name="param2">Paremeter Two</param>
        public Payload(ID source, ID destination, byte[] param1, byte[] param2)
        {
            PayloadValue = Serialization.Sequence(
                Serialization.SerializeToTLV(TLV_VALUES.TLV_MIHF_ID_SOURCE, source.ByteValue),
                Serialization.SerializeToTLV(TLV_VALUES.TLV_MIHF_ID_DESTINATION, destination.ByteValue),
                param1,
                param2);
        }
        /// <summary>
        /// Constructs a message with the Source ID, Destination ID and three parameters.
        /// </summary>
        /// <param name="source">Source ID</param>
        /// <param name="destination">Destination ID</param>
        /// <param name="param1">Parameter One</param>
        /// <param name="param2">Parameter Two</param>
        /// <param name="param3">Parameter Three</param>
        public Payload(ID source, ID destination, byte[] param1, byte[] param2, byte[] param3)
        {
            PayloadValue = Serialization.Sequence(
                Serialization.SerializeToTLV(TLV_VALUES.TLV_MIHF_ID_SOURCE, source.ByteValue),
                Serialization.SerializeToTLV(TLV_VALUES.TLV_MIHF_ID_DESTINATION, destination.ByteValue),
                param1,
                param2,
                param3);
        }
        /// <summary>
        /// Constructs a message with the Source ID, Destination ID and four parameters.
        /// </summary>
        /// <param name="source">Source ID</param>
        /// <param name="destination">Destination ID</param>
        /// <param name="param1">Parameter One</param>
        /// <param name="param2">Parameter Two</param>
        /// <param name="param3">Parameter Three</param>
        /// <param name="param4">Parameter Four</param>
        public Payload(ID source, ID destination, byte[] param1, byte[] param2, byte[] param3, byte[] param4)
        {
            PayloadValue = Serialization.Sequence(
                Serialization.SerializeToTLV(TLV_VALUES.TLV_MIHF_ID_SOURCE, source.ByteValue),
                Serialization.SerializeToTLV(TLV_VALUES.TLV_MIHF_ID_DESTINATION, destination.ByteValue),
                param1,
                param2,
                param3,
                param4);
        }
        /// <summary>
        /// Constructs a message with the Source ID, Destination ID and five parameters.
        /// </summary>
        /// <param name="source">Source ID</param>
        /// <param name="destination">Destination ID</param>
        /// <param name="param1">Parameter One</param>
        /// <param name="param2">Parameter Two</param>
        /// <param name="param3">Parameter Three</param>
        /// <param name="param4">Parameter Four</param>
        /// <param name="param5">Parameter Five</param>
        public Payload(ID source, ID destination, byte[] param1, byte[] param2, byte[] param3, byte[] param4, byte[] param5)
        {
            PayloadValue = Serialization.Sequence(
                Serialization.SerializeToTLV(TLV_VALUES.TLV_MIHF_ID_SOURCE, source.ByteValue),
                Serialization.SerializeToTLV(TLV_VALUES.TLV_MIHF_ID_DESTINATION, destination.ByteValue),
                param1,
                param2,
                param3,
                param4,
                param5);
        }
        /// <summary>
        /// Constructs a message with the Source ID, Destination ID and six parameters.
        /// </summary>
        /// <param name="source">Source ID</param>
        /// <param name="destination">Destination ID</param>
        /// <param name="param1">Parameter One</param>
        /// <param name="param2">Parameter Two</param>
        /// <param name="param3">Parameter Three</param>
        /// <param name="param4">Parameter Four</param>
        /// <param name="param5">Parameter Five</param>
        /// <param name="param6">Parameter Six</param>
        public Payload(ID source, ID destination, byte[] param1, byte[] param2, byte[] param3, byte[] param4, byte[] param5, byte[] param6)
        {
            PayloadValue = Serialization.Sequence(
                Serialization.SerializeToTLV(TLV_VALUES.TLV_MIHF_ID_SOURCE, source.ByteValue),
                Serialization.SerializeToTLV(TLV_VALUES.TLV_MIHF_ID_DESTINATION, destination.ByteValue),
                param1,
                param2,
                param3,
                param4,
                param5,
                param6);
        }
        /// <summary>
        /// Constructs a message with the Source ID, Destination ID and seven parameters.
        /// </summary>
        /// <param name="source">Source ID</param>
        /// <param name="destination">Destination ID</param>
        /// <param name="param1">Parameter One</param>
        /// <param name="param2">Parameter Two</param>
        /// <param name="param3">Parameter Three</param>
        /// <param name="param4">Parameter Four</param>
        /// <param name="param5">Parameter Five</param>
        /// <param name="param6">Parameter Six</param>
        /// <param name="param7">Parameter Seven</param>
        public Payload(ID source, ID destination, byte[] param1, byte[] param2, byte[] param3, byte[] param4, byte[] param5, byte[] param6, byte[] param7)
        {
            PayloadValue = Serialization.Sequence(
                Serialization.SerializeToTLV(TLV_VALUES.TLV_MIHF_ID_SOURCE, source.ByteValue),
                Serialization.SerializeToTLV(TLV_VALUES.TLV_MIHF_ID_DESTINATION, destination.ByteValue),
                param1,
                param2,
                param3,
                param4,
                param5,
                param6,
                param7);
        }
    }

    #endregion

    #region MIH Message

    /// <summary>
    /// This class represents a MIH Message.
    /// </summary>
    public class Message
    {
        /// <summary>
        /// MIH Message Header
        /// </summary>
        public MIHHeader MIHHeader { get; set; }

        /// <summary>
        /// MIHMessage Payload
        /// </summary>
        public Payload Payload { get; set; }

        private byte[] byteVal;
        /// <summary>
        /// byte[] representation of MIH Message.
        /// </summary>
        public byte[] ByteValue
        {
            get
            {
                GenerateValue();
                return byteVal;
            }
            private set { byteVal = value; }
        }

        /// <summary>
        /// MIHMessage empty constructor.
        /// </summary>
        public Message()
        { }

        /// <summary>
        /// MIHMessage main constructor.
        /// </summary>
        /// <param name="message">The message in a byte array form. (To be de-serialized)</param>
        public Message(byte[] message)
        {
            //LOGHERE
            //if (Program.RECEIVED_LOG)
            //{
            //    Console.WriteLine();
            //    Console.WriteLine("<Received Message>");
            //    Console.WriteLine("[Type, Length, Offset]");
            //    foreach (int[] ia in MIHDeserializer.getTLsFromPayload(message.Skip(8).ToArray()))
            //    {
            //        Console.Write("[ ");
            //        foreach (int i in ia)
            //            Console.Write(i + " ");
            //        Console.Write("]");
            //        Console.WriteLine();

            //    }
            //    Console.WriteLine();
            //}
            this.MIHHeader = new MIHHeader(message.Take(8).ToArray());

            //this.Payload = new Payload(new Common.CommonTypes.ID(new Common.DataTypes.OctetString("mihf1")), new Common.CommonTypes.ID(new Common.DataTypes.OctetString("link1")));

            int tlvSrcLen = message.Skip(8+1).Take(1).ToArray()[0];
            int tlvDstLen = message.Skip(8 + 2 + tlvSrcLen + 1).Take(1).ToArray()[0];

            this.Payload = new Payload(new ID(new OctetString(message.Skip(8 + 2).Take(tlvSrcLen).ToArray())),
                                    new ID(new OctetString(message.Skip(8 + 2 + tlvSrcLen + 2).Take(tlvDstLen).ToArray())),
                                    message.Skip(8 + 1 + tlvSrcLen + 1 + 1 + tlvDstLen + 1).ToArray());
            //this.Payload.PayloadValue = message.Skip(2).ToArray();
            //LOGHERE
            //if (Program.RECEIVED_LOG)
            //{
            //    Console.WriteLine();
            //    Console.WriteLine("<End Received Message>");
            //    Console.WriteLine();
            //}
        }

        /// <summary>
        /// Generates the byte[] value of the MIH Message.
        /// </summary>
        private void GenerateValue()
        {
            this.ByteValue = Serialization.Sequence(this.MIHHeader.ByteValue, this.Payload.PayloadValue);
        }
    }
    #endregion
}
