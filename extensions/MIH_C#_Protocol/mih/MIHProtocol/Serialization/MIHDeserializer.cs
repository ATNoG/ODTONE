#region Copyright
//==============================================================================
// Brief   : Class representing a MIHDeserializer.cs entity
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
#endregion

﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.NetworkInformation;

using MIH.DataTypes;

namespace MIH.MIHProtocol
{
    /// <summary>
    /// Contains methods to deserialize 802.21 objects.
    /// </summary>
    public class MIHDeserializer
    {
        #region Utilities
        /// <summary>
        /// Gets the types and corresponding lengths from a payload.
        /// The format is a List of arrays that contain [Type, Length, Offset] for each TLV.
        /// </summary>
        /// <param name="payloadVal">The serialized payload from a message.</param>
        /// <returns>A List of arrays that contain [Type, Length, Offset] for each TLV.</returns>
        public static List<int[]> getTLsFromPayload (byte[] payloadVal) //[Type, Length, Offset]
        {
            List<int[]> vals = new List<int[]>();
            int arrayPos=0;
            while (arrayPos < payloadVal.Length)
            {
                int[] aux = new int[3]; //{Type, Length, AbsoluteOffset}
                aux[0] = payloadVal.Skip(arrayPos++).Take(1).ToArray()[0];
                //Length
                aux[1] = payloadVal.Skip(arrayPos++).Take(1).ToArray()[0];
                if (aux[1] > 128)
                {
                    int length = 128;
                    int octets = aux[1]-128;
                    for (int i = 0; i < octets; i++)
                        length += payloadVal.Skip(arrayPos++).Take(1).ToArray()[0]*(int)(Math.Pow(256,octets-i-1));
                    aux[1] = length;
                }

                //-------
                aux[2] = arrayPos;
                arrayPos += aux[1];
                vals.Add(aux);
            }

            return vals;
        }

        #endregion

        #region Deserialization

        /// <summary>
        /// Deserializes a Link_Action type object.
        /// </summary>
        /// <param name="rawLinkAction">A serialized Link_Action object.</param>
        /// <returns>The deserialized Link_Action object.</returns>
        public static Link_Action DeserializeLinkAction(byte[] rawLinkAction){return new Link_Action(rawLinkAction);}
        /// <summary>
        /// Deserializes a Link_Action type object from the TLV iterator.
        /// </summary>
        /// <param name="fromIterator">The key value pair from the iterator, this corresponds to the value type (from TLV) and the serialized object.</param>
        /// <returns>The deserialized Link_Action object.</returns>
        public static Link_Action DeserializeLinkAction(KeyValuePair<int, byte[]> fromIterator)
        {
            if (fromIterator.Key == -1)
                return null;
            if (fromIterator.Key != TLV_VALUES.TLV_LINK_ACTION)
                throw new InvalidOperationException("Wrong package formatting received.\nError deserializing LinkAction, expected type " + TLV_VALUES.TLV_LINK_ACTION + ", got " + fromIterator.Key + ".");
            else
                return DeserializeLinkAction(fromIterator.Value);
        }

        /// <summary>
        /// Deserializes a Time_Interval type object (which is a 16 bit unsigned int).
        /// </summary>
        /// <param name="rawTimeInterval">The serialized time interval, expectedly a 2 byte-long array.</param>
        /// <returns>An unsigned 16 bit integer, corresponding to the Time_Interval object.</returns>
        public static ushort DeserializeTimeInterval(byte[] rawTimeInterval) {return BitConverter.ToUInt16(rawTimeInterval, 0);}
        /// <summary>
        /// Deserializes a Time_Interval type object (which is a 16 bit unsigned int).
        /// </summary>
        /// <param name="fromIterator">The key value pair from the iterator, this corresponds to the value type (from TLV) and the serialized object.</param>
        /// <returns>An unsigned 16 bit integer, corresponding to the Time_Interval object.</returns>
        public static ushort DeserializeTimeInterval(KeyValuePair<int, byte[]> fromIterator)
        {
            if (fromIterator.Key == -1)
                return 0;
            if (fromIterator.Key != TLV_VALUES.TLV_TIME_INTERVAL)
                throw new InvalidOperationException("Wrong package formatting received.\nError deserializing TimeInterval, expected type " + TLV_VALUES.TLV_TIME_INTERVAL+ ", got " + fromIterator.Key + ".");
            else
                return DeserializeTimeInterval(fromIterator.Value);
        }

        /// <summary>
        /// Deserializes a Link_Addr type object.
        /// </summary>
        /// <param name="rawPoA">The serialized Link_Addr object.</param>
        /// <returns>The deserialized Link_Addr object.</returns>
        public static Link_Addr DeserializePoA(byte[] rawPoA) { return new Link_Addr(rawPoA); }
        /// <summary>
        /// Deserializes a Link_Addr type object from the TLV iterator.
        /// </summary>
        /// <param name="fromIterator">The key value pair from the iterator, this corresponds to the value type (from TLV) and the serialized object.</param>
        /// <returns>The deserialized Link_Addr object.</returns>
        public static Link_Addr DeserializePoA(KeyValuePair<int, byte[]> fromIterator)
        {
            if (fromIterator.Key == -1)
                return null;
            if (fromIterator.Key != TLV_VALUES.TLV_POA)
                throw new InvalidOperationException("Wrong package formatting received.\nError deserializing PoA, expected type " + TLV_VALUES.TLV_POA + ", got " + fromIterator.Key + ".");
            else
                return DeserializePoA(fromIterator.Value);
        }

        /// <summary>
        /// Deserializes a Status type object.
        /// </summary>
        /// <param name="rawData">The serialized status object (a 1 byte-long byte array).</param>
        /// <returns>The deserialized Status object.</returns>
        public static STATUS DeserializeStatus(byte[] rawData) { return (STATUS)((int)rawData[0]); }
        /// <summary>
        /// Deserializes a Status type object from the TLV iterator.
        /// </summary>
        /// <param name="fromIterator">The key value pair from the iterator, this correspondes to the value type (from TLV) and the serialized object.</param>
        /// <returns>The deserialized Status object.</returns>
        public static STATUS DeserializeStatus(KeyValuePair<int, byte[]> fromIterator)
        {
            if (fromIterator.Key == -1)
                return STATUS.UNSPECIFIED_FAILURE;
            if (fromIterator.Key != TLV_VALUES.TLV_STATUS)
                throw new InvalidOperationException("Wrong package formatting received.\nError deserializing Status, expected type " + TLV_VALUES.TLV_STATUS + ", got " + fromIterator.Key + ".");
            else
                return DeserializeStatus(fromIterator.Value);
        }

        /// <summary>
        /// Deserializes a Link_Scan_Rsp_List object.
        /// </summary>
        /// <param name="serializedList">The serialized Link_Scan_Rsp_List object.</param>
        /// <returns>The deserialized Link_Scan_Rsp_List object, in the form of a List of Link_Scan_Rsp objects.</returns>
        public static List<Link_Scan_Rsp> DeserializeLinkScanRspList(byte[] serializedList)
        {
            int capacity = serializedList[0];
            List<Link_Scan_Rsp> result = new List<Link_Scan_Rsp>(serializedList[0]);
            int currOffset = 1;
            for (int i = 0; i < capacity; i++)
            {
                result.Add(new Link_Scan_Rsp(serializedList.Skip(currOffset).ToArray()));
                currOffset += result.Last().ByteValue.Length; //FIXME pouco eficiente!!
            }
            return result;

        }
        /// <summary>
        /// Deserializes a Link_Scan_Rsp_List type object from the TLV iterator.
        /// </summary>
        /// <param name="fromIterator">The key value pair from the iterator, this corresponds to the value type (from TLV) and the serialized object.</param>
        /// <returns>The deserialized Link_Scan_Rsp_List object, in the form of a List of Link_Scan_Rsp objects.</returns>
        public static List<Link_Scan_Rsp> DeserializeLinkScanRspList(KeyValuePair<int, byte[]> fromIterator)
        {
            if (fromIterator.Key == -1)
                return null;
            if (fromIterator.Key != TLV_VALUES.TLV_LINK_SCAN_RSP_LIST)
                throw new InvalidOperationException("Wrong package formatting received.\nError deserializing Link_Scan_Rsp_List, expected type " + TLV_VALUES.TLV_LINK_SCAN_RSP_LIST + ", got " + fromIterator.Key + ".");
            else
                return DeserializeLinkScanRspList(fromIterator.Value);
        }

        /// <summary>
        /// Deserializes a Link_Ac_Result type object.
        /// </summary>
        /// <param name="rawData">The serialized Link Action Result.</param>
        /// <returns>The deserialized Link_Ac_Result.</returns>
        public static Link_Ac_Result DeserializeLinkAcResult(byte[] rawData) { return (Link_Ac_Result)((int)rawData[0]); }
        /// <summary>
        /// Deserializes a Link_Ac_Result type object from the TLV iterator.
        /// </summary>
        /// <param name="fromIterator">The key value pair from the iterator, this corresponds to the value type (from TLV) and the serialized object.</param>
        /// <returns>The deserialized Link_Ac_Result object.</returns>
        public static Link_Ac_Result DeserializeLinkAcResult(KeyValuePair<int, byte[]> fromIterator)
        {
            if (fromIterator.Key == -1)
                return Link_Ac_Result.FAILURE;
            if (fromIterator.Key != TLV_VALUES.TLV_LINK_AC_RESULT)
                throw new InvalidOperationException("Wrong package formatting received.\nError deserializing Link_Ac_Result, expected type " + TLV_VALUES.TLV_LINK_AC_RESULT + ", got " + fromIterator.Key + ".");
            else
                return DeserializeLinkAcResult(fromIterator.Value);
        }

        /// <summary>
        /// Deserializes a Link_Addr type object.
        /// </summary>
        /// <param name="rawData">The serialized Link Address</param>
        /// <returns>The deserialized Link_Addr.</returns>
        public static Link_Addr DeserializeLinkAddr(byte[] rawData) { return new Link_Addr(rawData); }
        /// <summary>
        /// Deserializes a Link_Addr (corresponding to the Old_Access_Router data type) type object from the TLV iterator.
        /// </summary>
        /// <param name="fromIterator">The key value pair from the iterator, this corresponds to the value type (from TLV) and the serialized object.</param>
        /// <returns>The deserialized Link_Addr object, corresponding to the Old_Access_Router data type.</returns>
        public static Link_Addr DeserializeOldAccessRouter(KeyValuePair<int, byte[]> fromIterator)
        {
            if (fromIterator.Key == -1)
                return null;
            if (fromIterator.Key != TLV_VALUES.TLV_OLD_ACCESS_ROUTER)
                throw new InvalidOperationException("Wrong package formatting received.\nError deserializing Old_Access_Router, expected type " + TLV_VALUES.TLV_OLD_ACCESS_ROUTER + ", got " + fromIterator.Key + ".");
            else
                return DeserializeLinkAddr(fromIterator.Value);
        }
        /// <summary>
        /// Deserializes a Link_Addr (corresponding to the New_Access_Router data type) type object from the TLV iterator.
        /// </summary>
        /// <param name="fromIterator">The key value pair from the iterator, this corresponds to the value type (from TLV) and the serialized object.</param>
        /// <returns>The deserialized Link_Addr object, corresponding to the New_Access_Router data type.</returns>
        public static Link_Addr DeserializeNewAccessRouter(KeyValuePair<int, byte[]> fromIterator)
        {
            if (fromIterator.Key == -1)
                return null;
            if (fromIterator.Key != TLV_VALUES.TLV_NEW_ACCESS_ROUTER)
                throw new InvalidOperationException("Wrong package formatting received.\nError deserializing New_Access_Router, expected type " + TLV_VALUES.TLV_NEW_ACCESS_ROUTER + ", got " + fromIterator.Key + ".");
            else
                return DeserializeLinkAddr(fromIterator.Value);
        }

        /// <summary>
        /// Deserializes a Link_Det_Info type object.
        /// </summary>
        /// <param name="rawData">The serialized Link_Det_Info object.</param>
        /// <returns>The deserialized Link_Det_Info.</returns>
        public static Link_Det_Info DeserializeLinkDetInfo(byte[] rawData) { return new Link_Det_Info(rawData); }
        /// <summary>
        /// Deserializes a Link_Det_Info type object from the TLV iterator.
        /// </summary>
        /// <param name="fromIterator">The key value pair from the iterator, this corresponds to the value type (fromTLV) and the serialized object.</param>
        /// <returns>The deserialized Link_Det_Info object.</returns>
        public static Link_Det_Info DeserializeLinkDetInfo(KeyValuePair<int, byte[]> fromIterator)
        {
            if (fromIterator.Key == -1)
                return null;
            if (fromIterator.Key != TLV_VALUES.TLV_LINK_DET_INFO)
                throw new InvalidOperationException("Wrong package formatting received.\nError deserializing Link_Det_Info, expected type " + TLV_VALUES.TLV_LINK_DET_INFO + ", got " + fromIterator.Key + ".");
            else
                return DeserializeLinkDetInfo(fromIterator.Value);
        }

        /// <summary>
        /// Deserializes a Link_Dn_Reason object.
        /// </summary>
        /// <param name="rawData">The serialized Link_Dn_Reason, that is a 1-byte long byte array containing the reason code.</param>
        /// <returns>The deserialized Link_Dn_Reason.</returns>
        public static Link_Dn_Reason DeserializeLinkDnReason(byte[] rawData) { return (Link_Dn_Reason)((int)rawData[0]); }
        /// <summary>
        /// Deserializes a Link_Dn_Reason type object from the TLV iterator.
        /// </summary>
        /// <param name="fromIterator">The key value pair from the iterator, this corresponds to the value type (from TLV) and the serialized object.</param>
        /// <returns>The deserialized Link_Dn_Reason object.</returns>
        public static Link_Dn_Reason DeserializeLinkDnReason(KeyValuePair<int, byte[]> fromIterator)
        {
            if (fromIterator.Key == -1)
                throw new InvalidCastException();
            if (fromIterator.Key != TLV_VALUES.TLV_LINK_DOWN_REASON_CODE)
                throw new InvalidOperationException("Wrong package formatting received.\nError deserializing Link_Dn_Reason, expected type " + TLV_VALUES.TLV_LINK_DOWN_REASON_CODE + ", got " + fromIterator.Key + ".");
            else
                return DeserializeLinkDnReason(fromIterator.Value);
        }

        /// <summary>
        /// Deserializes a Link_Tuple_Id object.
        /// </summary>
        /// <param name="rawData">The serialized Link_Tuple_Id.</param>
        /// <returns>The deserialized Link_Tuple_Id.</returns>
        public static Link_Tuple_Id DeserializeLinkTupleId(byte[] rawData) { return new Link_Tuple_Id(rawData); }
        /// <summary>
        /// Deserializes a Link_Tuple_Id type object from the TLV iterator.
        /// </summary>
        /// <param name="fromIterator">The key value pair from the iterator, this corresponds to the value type (from TLV) and the serialized object.</param>
        /// <returns>The deserialized Link_Tuple_Id object.</returns>
        public static Link_Tuple_Id DeserializeLinkTupleId(KeyValuePair<int, byte[]> fromIterator)
        {
            if (fromIterator.Key == -1)
                return null;
            if (fromIterator.Key != TLV_VALUES.TLV_LINK_IDENTIFIER)
                throw new InvalidOperationException("Wrong package formatting received.\nError deserializing Link_Identifier, expected type " + TLV_VALUES.TLV_LINK_IDENTIFIER + ", got " + fromIterator.Key + ".");
            else
                return DeserializeLinkTupleId(fromIterator.Value);
        }

        /// <summary>
        /// Deserializes a Link_Event_List object.
        /// </summary>
        /// <param name="rawData">The serialized Link_Event_List.</param>
        /// <returns>The deserialized Link_Event_List.</returns>
        public static Link_Event_List DeserializeLinkEventList(byte[] rawData) { return new Link_Event_List(rawData); }
        /// <summary>
        /// Deserializes a Link_Event_List type object from the TLV iterator.
        /// </summary>
        /// <param name="fromIterator">The key value pair from the iterator, this corresponds to the value type (from TLV) and the serialized object.</param>
        /// <returns>The deserialized Link_Event_List object.</returns>
        public static Link_Event_List DeserializeLinkEventList(KeyValuePair<int, byte[]> fromIterator)
        {
            if (fromIterator.Key == -1)
                return null;
            if (fromIterator.Key != TLV_VALUES.TLV_LINK_EVENT_LIST)
                throw new InvalidOperationException("Wrong package formatting received.\nError deserializing Link_Event_List, expected type " + TLV_VALUES.TLV_LINK_EVENT_LIST + ", got " + fromIterator.Key + ".");
            else
                return DeserializeLinkEventList(fromIterator.Value);
        }

        /// <summary>
        /// Deserializes a Link_Cfg_Param_List object.
        /// </summary>
        /// <param name="serializedList">The serialized Link_Cfg_Param_List object.</param>
        /// <returns>The deserialized Link_Cfg_Param_List in the form of a List of Link_Cfg_Param objects.</returns>
        public static List<Link_Cfg_Param> DeserializeLinkCfgParamList(byte[] serializedList)
        {
            int capacity = serializedList[0];
            List<Link_Cfg_Param> result = new List<Link_Cfg_Param>(capacity);
            int currOffset = 1;
            for (int i = 0; i < capacity; i++)
            {
                result.Add(new Link_Cfg_Param(serializedList.Skip(currOffset).ToArray()));
                currOffset += result.Last().ByteValue.Length; //FIXME pouco eficiente!!
            }
            return result;
        }
        /// <summary>
        /// Deserializes a Link_Cfg_Param_List type object from the TLV iterator.
        /// </summary>
        /// <param name="fromIterator">The key value pair from the iterator, this corresponds to the value type (from TLV) and the serialized object.</param>
        /// <returns>The deserialized Link_Cfg_Param_List in the form of a List_Cfg_Param objects.</returns>
        public static List<Link_Cfg_Param> DeserializeLinkCfgParamList(KeyValuePair<int, byte[]> fromIterator)
        {
            if (fromIterator.Key == -1)
                return null;
            if (fromIterator.Key != TLV_VALUES.TLV_CONFIGURE_REQUEST_LIST)
                throw new InvalidOperationException("Wrong package formatting received.\nError deserializing Link_Cfg_Param_List, expected type " + TLV_VALUES.TLV_CONFIGURE_REQUEST_LIST + ", got " + fromIterator.Key + ".");
            else
                return DeserializeLinkCfgParamList(fromIterator.Value);
        }

        /// <summary>
        /// Deserializes a Threshold_List object.
        /// </summary>
        /// <param name="serializedList">The serialized Threshold_List object.</param>
        /// <returns>The deserialized Threshold_List in the form of a List of Thresholds</returns>
        public static List<Threshold> DeserializeThresholdList(byte[] serializedList)
        {
            int capacity = serializedList[0];
            List<Threshold> result = new List<Threshold>(capacity);
            int currOffset = 1;
            for (int i = 0; i < capacity; i++)
            {
                result.Add(new Threshold(serializedList.Skip(currOffset).ToArray()));
                currOffset += 3;
            }
            return result;
        }

        /// <summary>
        /// Deserializes a Link_Param_Request.
        /// </summary>
        /// <param name="serializedList">A serialized list of Link_Param_Type objects, representing a Link_Param_Request.</param>
        /// <returns>A list of Link_Param_Type objects, representing a Link_Param_Request.</returns>
        public static List<Link_Param_Type> DeserializeLinkParamRequest(byte[] serializedList)
        {
            int capacity = serializedList[0];
            List<Link_Param_Type> result = new List<Link_Param_Type>(capacity);
            int currOffset = 1;
            for (int i = 0; i < capacity; i++)
            {
                result.Add(new Link_Param_Type(serializedList.Skip(currOffset).Take(2).ToArray()));
                currOffset += 2;
            }
            return result;
        }
        /// <summary>
        /// Deserializes a Link_Param_Request type object from the TLV iterator.
        /// </summary>
        /// <param name="fromIterator">The key value pair from the iterator, this corresponds to the value type (from TLV) and the serialized object.</param>
        /// <returns>A list of Link_Param_Type objects, representing a Link_Param_Request.</returns>
        public static List<Link_Param_Type> DeserializeLinkParamRequest(KeyValuePair<int, byte[]> fromIterator)
        {
            if (fromIterator.Key == -1)
                return null;
            if (fromIterator.Key != TLV_VALUES.TLV_LINK_PARAMETERS_REQ)
                throw new InvalidOperationException("Wrong package formatting received.\nError deserializing LinkParametersRequest, expected type " + TLV_VALUES.TLV_LINK_PARAMETERS_REQ + ", got " + fromIterator.Key + ".");
            else
                return DeserializeLinkParamRequest(fromIterator.Value);
        }

        /// <summary>
        /// Deserializes a Link_Param_Status_List object.
        /// </summary>
        /// <param name="serializedList">A serialized Link_Param_Status_List.</param>
        /// <returns>A deserialized Link_Param_Status_List, in the form of a List of Link_Param objects.</returns>
        public static List<Link_Param> DeserializeLinkParamStatusList(byte[] serializedList)
        {
            int capacity = serializedList[0];
            List<Link_Param> result = new List<Link_Param>(capacity);
            int currOffset = 1;
            for (int i = 0; i < capacity; i++)
            {
                result.Add(new Link_Param(serializedList.Skip(currOffset).ToArray()));
                currOffset += result.Last().ByteValue.Length; //TODO pouco eficiente
            }
            return result;
        }
        /// <summary>
        /// Deserializes a Link_Param_Status_List type object from the TLV iterator.
        /// </summary>
        /// <param name="fromIterator">The key value pair from the iterator, this corresponds to the value type (from TLV) and the serialized object.</param>
        /// <returns>A deserialized Link_Param_Status_List, in the form of a list of Link_Param objects.</returns>
        public static List<Link_Param> DeserializeLinkParamStatusList(KeyValuePair<int, byte[]> fromIterator)
        {
            if (fromIterator.Key == -1)
                return null;
            if (fromIterator.Key != TLV_VALUES.TLV_LINK_PARAMETERS_STATUS_LIST)
                throw new InvalidOperationException("Wrong package formatting received.\nError deserializing LinkParametersStatusList, expected type " + TLV_VALUES.TLV_LINK_PARAMETERS_STATUS_LIST + ", got " + fromIterator.Key + ".");
            else
                return DeserializeLinkParamStatusList(fromIterator.Value);
        }

        /// <summary>
        /// Deserializes a Link_States_Response object.
        /// </summary>
        /// <param name="serializedList">The serialized Link_States_Response list.</param>
        /// <returns>The deserialized Link_States_Response, in the form of a list of Link_States_Rsp objects.</returns>
        public static List<Link_Get_Parameters_Confirm.Link_States_Rsp> DeserializeLinkStatesResponse(byte[] serializedList)
        {
            int capacity = serializedList[0];
            List<Link_Get_Parameters_Confirm.Link_States_Rsp> result = new List<Link_Get_Parameters_Confirm.Link_States_Rsp>(capacity);
            int currOffset = 1;
            for (int i = 0; i < capacity; i++)
            {
                result.Add(new Link_Get_Parameters_Confirm.Link_States_Rsp(serializedList.Skip(currOffset).ToArray()));
                currOffset += (result.Last().ChoiceType == Link_Get_Parameters_Confirm.Link_States_Rsp.Type.OP_MODE ? 2 : 3);
            }
            return result;
        }
        /// <summary>
        /// Deserializes a Link_States_Response type object from the TLV iterator.
        /// </summary>
        /// <param name="fromIterator">The key value pair from the iterator, this corresponds to the value type (from TLV) and the serialized object.</param>
        /// <returns>The deserialized Link_States_Response, in the form of a list of Link_States_Rsp objects.</returns>
        public static List<Link_Get_Parameters_Confirm.Link_States_Rsp> DeserializeLinkStatesResponse(KeyValuePair<int, byte[]> fromIterator)
        {
            if (fromIterator.Key == -1)
                return null;
            if (fromIterator.Key != TLV_VALUES.TLV_LINK_STATES_RSP)
                throw new InvalidOperationException("Wrong package formatting received.\nError deserializing LinkStatesResponse, expected type " + TLV_VALUES.TLV_LINK_STATES_RSP + ", got " + fromIterator.Key + ".");
            else
                return DeserializeLinkStatesResponse(fromIterator.Value);
        }

        /// <summary>
        /// Deserializes a Link_Descriptors_Response object.
        /// </summary>
        /// <param name="serializedList">The serialized Link_Descriptors_Response object.</param>
        /// <returns>The deserialized Link_Descriptors_Response object, in the form of a List of Link_Dsc_Rsp objects.</returns>
        public static List<Link_Get_Parameters_Confirm.Link_Desc_Rsp> DeserializeLinkDescriptorsResponse(byte[] serializedList)
        {
            int capacity = serializedList[0];
            List<Link_Get_Parameters_Confirm.Link_Desc_Rsp> result = new List<Link_Get_Parameters_Confirm.Link_Desc_Rsp>(capacity);
            int currOffset = 1;
            for (int i = 0; i < capacity; i++)
            {
                result.Add(new Link_Get_Parameters_Confirm.Link_Desc_Rsp(serializedList.Skip(currOffset).ToArray()));
                currOffset += 2;
            }
            return result;
        }
        /// <summary>
        /// Deserializes a Link_Descriptors_Response type object from the TLV iterator.
        /// </summary>
        /// <param name="fromIterator">The key value pair from the iterator, this corresponds to the value type (from TLV) and the serialized object.</param>
        /// <returns>The deserialized Link_Descriptors_Response object, in the form of a List of Link_Dsc_Rsp objects.</returns>
        public static List<Link_Get_Parameters_Confirm.Link_Desc_Rsp> DeserializeLinkDescriptorsResponse(KeyValuePair<int, byte[]> fromIterator)
        {
            if (fromIterator.Key == -1)
                return null;
            if (fromIterator.Key != TLV_VALUES.TLV_LINK_DESCRIPTOR_RSP)
                throw new InvalidOperationException("Wrong package formatting received.\nError deserializing LinkDescriptorsResponse, expected type " + TLV_VALUES.TLV_LINK_DESCRIPTOR_RSP + ", got " + fromIterator.Key + ".");
            else
                return DeserializeLinkDescriptorsResponse(fromIterator.Value);
        }


        #endregion

    }
}
