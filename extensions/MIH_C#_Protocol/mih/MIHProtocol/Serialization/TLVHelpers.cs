//==============================================================================
// Brief   : Class representing a TLVHelpers.cs entity
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

namespace MIH.MIHProtocol
{
    /// <summary>
    /// This class contains constant values corresponding to the 802.21 data types to use in TLV encoding.
    /// </summary>
    public class TLV_VALUES
    {
        // Specified by 802.21
        public const int TLV_MIHF_ID_SOURCE = 1;
        public const int TLV_MIHF_ID_DESTINATION = 2;
        public const int TLV_STATUS = 3;
        public const int TLV_LINK_TYPE = 4;
        public const int TLV_MIH_EVENT_LIST = 5;
        public const int TLV_MIH_COMMAND_LIST = 6;
        public const int TLV_MIH_QUERY_TYPE_LIST = 7;
        public const int TLV_TRANSPORT_OPT_LIST = 8;
        public const int TLV_LINK_ADDRESS_LIST = 9;
        public const int TLV_MBB_HANDOVER_SUPPORT = 10;
        public const int TLV_REGISTER_REQ_CODE = 11;
        public const int TLV_VALID_TIME_INTERVAL = 12;
        public const int TLV_LINK_IDENTIFIER = 13;
        public const int TLV_NEW_LINK_IDENTIFIER = 14;
        public const int TLV_OLD_ACCESS_ROUTER = 15;
        public const int TLV_NEW_ACCESS_ROUTER = 16;
        public const int TLV_IP_RENEWAL_FLAG = 17;
        public const int TLV_MOBILITY_MANAGEMENT_SUPPORT = 18;
        public const int TLV_IP_ADDRESS_CONFIGURATION_METHODS = 19;
        public const int TLV_LINK_DOWN_REASON_CODE = 20;
        public const int TLV_TIME_INTERVAL = 21;
        public const int TLV_LINK_GOING_DOWN_REASON = 22;
        public const int TLV_LINK_PARAM_REPORT_LIST = 23;
        public const int TLV_DEVICE_STATES_REQUEST = 24;
        public const int TLV_LINK_IDENTIFIER_LIST = 25;
        public const int TLV_DEVICE_STATES_RESPONSE = 26;
        public const int TLV_GET_STATUS_RESQUEST_SET = 27;
        public const int TLV_GET_STATUS_RESPONSE_LIST = 28;
        public const int TLV_CONFIGURE_REQUEST_LIST = 29;
        public const int TLV_CONFIGURE_RESPONSE_LIST = 30;
        public const int TLV_LIST_OF_LINK_POA_LIST = 31;
        public const int TLV_PREFERRED_LINK_LIST = 32;
        public const int TLV_HANDOVER_RESOURCE_QUERY_LIST = 33;
        public const int TLV_HANDOVER_STATUS = 34;
        public const int TLV_ACCESS_ROUTER_ADDRESS = 35;
        public const int TLV_DHCP_SERVER_ADDRESS = 36;
        public const int TLV_FA_ADDRESS = 37;
        public const int TLV_LINK_ACTIONS_LIST = 38;
        public const int TLV_LINK_ACTIONS_RESULT_LIST = 39;
        public const int TLV_HANDOVER_RESULT = 40;
        public const int TLV_RESOURCE_STATUS = 41;
        public const int TLV_RESOURCE_RETENTION_STATUS = 42;
        public const int TLV_INFO_QUERY_BINARY_DATA_LIST = 43;
        public const int TLV_INFO_QUERY_RDF_DATA_LIST = 44;
        public const int TLV_INFO_QUERY_RDF_SCHEMA_URL = 45;
        public const int TLV_INFO_QUERY_RDF_SCHEMA_LIST = 46;
        public const int TLV_MAX_RESPONSE_SIZE = 47;
        public const int TLV_INFO_RESPONSE_BINARY_DATA_LIST = 48;
        public const int TLV_INFO_RESPONSE_RDF_DATA_LIST = 49;
        public const int TLV_INFO_RESPONSE_RDF_SCHEMA_URL_LIST = 50;
        public const int TLV_INFO_RESPONSE_RDF_SCEMA_LIST = 51;
        public const int TLV_MOBILE_NODE_MIHF_ID = 52;
        public const int TLV_QUERY_RESOURCE_REPORT_FLAG = 53;
        public const int TLV_EVENT_CONDIFURATION_INFO_LIST = 54;
        public const int TLV_TARGET_NETWORK_INFO = 55;
        public const int TLV_LIST_OF_TARGET_NETWORK_INFO = 56;
        public const int TLV_ASSIGNED_RESOURCE_SET = 57;
        public const int TLV_LINK_DETECTED_INFO_LIST = 58;
        public const int TLV_MN_LINK_ID = 59;
        public const int TLV_POA = 60;
        public const int TLV_UNAUTHENTICATED_INFORMATION_REQUEST = 61;
        public const int TLV_NETWORK_TYPE = 62;
        public const int TLV_REQUESTED_RESOURCE_SET = 63;
        public const int TLV_VENDOR_SPECIFIC_TLV = 100;

        /*public const int TLV_EVENT_LIST = 5;
        public const int TLV_COMMAND_LIST = 6;
        public const int TLV_LINK_CFG_PARAM_LIST = 29;
        public const int TLV_LINK_CFG_STATUS_LIST = 30;
        public const int TLV_LINK_DET_INFO_LIST = 58;
        public const int TLV_LINK_TIME_INTERVAL = 21;
        public const int TLV_LINK_GOING_DOWN_REASON = 22;
        public const int TLV_LINK_PARAM_RPT_LIST = 23;
        public const int TLV_ACCESS_ROUTER_ADDR = 35;
        public const int TLV_DESTINATION_ID = 2;
        public const int TLV_SOURCE_ID = 1;
        public const int TLV_DEV_STATES_REQ = 24;
        public const int TLV_REG_REQUEST_CODE = 11;
        public const int TLV_IP_RENEWAL_FLAG = 17;
        */

        //ODTONE Specific
        public const int TLV_LINK_EVENT_LIST = 101;
        public const int TLV_LINK_COMMAND_LIST=102;
        public const int TLV_LINK_PARAMETERS_REQ = 103;
        public const int TLV_LINK_PARAMETERS_STATUS_LIST = 104;
        public const int TLV_LINK_STATES_REQ = 105;
        public const int TLV_LINK_STATES_RSP = 106;
        public const int TLV_LINK_DESC_REQ = 107;
        public const int TLV_LINK_DESCRIPTOR_RSP = 108;
        public const int TLV_LINK_ACTION = 109;
        public const int TLV_LINK_AC_RESULT = 110;
        public const int TLV_LINK_SCAN_RSP_LIST = 111;
        public const int TLV_LINK_DET_INFO = 112;
        public const int TLV_INTERFACE_TYPE_ADDR = 113;
        public const int TLV_MOS_DSCV = 114;

        //Choices
        /*public const int CHOICE_LINK_PARAM_GEN = 0;
        public const int CHOICE_LINK_PARAM_QOS = 1;
        public const int CHOICE_LINK_PARAM_GG = 2;
        public const int CHOICE_LINK_PARAM_EDGE = 3;
        public const int CHOICE_LINK_PARAM_ETH = 4;
        public const int CHOICE_LINK_PARAM_802_11 = 5;
        public const int CHOICE_LINK_PARAM_C2K = 6;
        public const int CHOICE_LINK_PARAM_FDD = 7;
        public const int CHOICE_LINK_PARAM_HRPD = 8;
        public const int CHOICE_LINK_PARAM_802_16 = 9;
        public const int CHOICE_LINK_PARAM_802_20 = 10;
        public const int CHOICE_LINK_PARAM_802_22 = 11;
        */
        public const int CHOICE_SIG_STR_DBM = 0;
        public const int CHOICE_SIG_STR_PERCENTAGE = 1;

    }

    /// <summary>
    /// This clase is used to serialize various classes into TLV format.
    /// </summary>
    public class TLV_HELPERS
    {
        /// <summary>
        /// MIHProtocol of Source Identifier.
        /// </summary>
        /// <param name="id">ID object.</param>
        /// <returns>Source Identifier serialization.</returns>
        public static byte[] TLVSourceIdentifier(ID id)
        {
            return Serialization.SerializeToTLV(TLV_VALUES.TLV_MIHF_ID_SOURCE, id.ByteValue);
        }

        /// <summary>
        /// MIHProtocol of Destination Identifier.
        /// </summary>
        /// <param name="id">ID object.</param>
        /// <returns>Destination Indentifier Serialization.</returns>
        public static byte[] TLVDestinationIdentifier(ID id)
        {
            return Serialization.SerializeToTLV(TLV_VALUES.TLV_MIHF_ID_DESTINATION, id.ByteValue);
        }

        /// <summary>
        /// MIHProtocol of a Link Address List.
        /// </summary>
        /// <returns>Link Address List Serialization.</returns>
        public static byte[] TLVLinkAddressList()
        {
            // TODO to be implemented.
            return null;
        }

        /// <summary>
        /// MIHProtocol of a Supported MIH Event List.
        /// </summary>
        /// <param name="MIHEventList">MIH Event List in a BitArray Form.</param>
        /// <returns>Supported MIH Event List MIHProtocol</returns>
        public static byte[] TLVSupportedMIHEventList(BitArray MIHEventList)
        {
            return Serialization.SerializeToTLV(TLV_VALUES.TLV_MIH_EVENT_LIST, BitArrayToByteArray(MIHEventList));
        }

        /// <summary>
        /// MIHProtocol of a Supported MIH Command List.
        /// </summary>
        /// <param name="MIHCMDList">MIH Command List in a BitArray Form.</param>
        /// <returns>Supported MIH Command List Serialization.</returns>
        public static byte[] TLVSupportedMIHCommandList(BitArray MIHCMDList)
        {
            return Serialization.SerializeToTLV(TLV_VALUES.TLV_MIH_COMMAND_LIST, BitArrayToByteArray(MIHCMDList));
        }

        /// <summary>
        /// MIHProtocol of a STATUS object.
        /// </summary>
        /// <param name="status">STATUS choice.</param>
        /// <returns>STATUS serialization.</returns>
        public static byte[] TLVStatus(STATUS status)
        {
            return Serialization.SerializeToTLV(TLV_VALUES.TLV_STATUS, BitConverter.GetBytes((int)status));
        }

        /// <summary>
        /// MIHProtocol of a Link Indetifier List.
        /// </summary>
        /// <param name="linkIdentifierList">The EventList of Link Identifiers List.</param>
        /// <returns>Link Identifier EventList serialization.</returns>
        public static byte[] TLVLinkIdentifierList(List<Link_Id> linkIdentifierList)
        {
            throw new NotImplementedException();
            //return Serialization.SerializeToTLV(TLV_VALUES.TLV_LINK_IDENTIFIER_LIST, Serialization.EncodingList(
        }

        /// <summary>
        /// MIHProtocol of a Reg Request Code.
        /// </summary>
        /// <param name="requestCode">The request code.</param>
        /// <returns>Request Code serialization.</returns>
        public static byte[] TLVRegRequestCode(int requestCode)
        {
            return Serialization.SerializeToTLV(TLV_VALUES.TLV_REGISTER_REQ_CODE, BitConverter.GetBytes(requestCode));
        }

        /// <summary>
        /// MIHProtocol of a Link Identifier.
        /// </summary>
        /// <param name="linkIdentifier">The Link Identifier, represented as a Link_Tuple_Id.</param>
        /// <returns>Link Identifier Serialization.</returns>
        public static byte[] TLVLinkIdentifier(Link_Tuple_Id linkIdentifier)
        {
            return Serialization.SerializeToTLV(TLV_VALUES.TLV_LINK_IDENTIFIER, linkIdentifier.ByteValue);
        }

        public static byte[] TLVLinkId(Link_Id linkID)
        {
            return Serialization.SerializeToTLV(TLV_VALUES.TLV_MN_LINK_ID, linkID.ByteValue);
        }

        public static byte[] TLVPoALinkAddress(Link_Addr la)
        {
            return Serialization.SerializeToTLV(TLV_VALUES.TLV_POA, la.ByteValue);
        }


        public static byte[] TLVLinkDnReason(Link_Dn_Reason linkDnReason)
        {
            byte[] aux = { IntToByte((int)linkDnReason) };
            return Serialization.SerializeToTLV(TLV_VALUES.TLV_LINK_DOWN_REASON_CODE, aux);
        }

        private static byte IntToByte(int value)
        {
            byte[] intBytes = BitConverter.GetBytes(value);
            if (!BitConverter.IsLittleEndian)
                Array.Reverse(intBytes);
            return intBytes[0];
        }

        /// <summary>
        /// MIHProtocol of a Valid Time Interval.
        /// </summary>
        /// <param name="time">Time value.</param>
        /// <returns>Time serialization.</returns>
        public static byte[] TLVValidTimeInternal(uint time)
        {
            return Serialization.SerializeToTLV(TLV_VALUES.TLV_TIME_INTERVAL, BitConverter.GetBytes(time));
        }

        /// <summary>
        /// MIHProtocol of a Requested MIH Event List.
        /// </summary>
        /// <param name="requestedMIHEventList">Requested MIH Event List in a BitArry form.</param>
        /// <returns>Requested MIH Event List Serialization.</returns>
        public static byte[] TLVRequestMIHEventList(BitArray requestedMIHEventList)
        {
            return Serialization.SerializeToTLV(TLV_VALUES.TLV_MIH_EVENT_LIST,BitArrayToByteArray(requestedMIHEventList));
        }


        /// <summary>
        /// MIHProtocol of a Event Configuration Info List.
        /// </summary>
        /// <returns>Event Configuration Info List Serialization.</returns>
        public static byte[] TLVEventConfigurationInfoList ()
        {
            // TODO to be implemented.
            return null;
        }

        /// <summary>
        /// MIHProtocol of a Response MIH Event List.
        /// </summary>
        /// <param name="responseMIHEventList">ResponseMIHEventList in a BitArray form.</param>
        /// <returns>ResponseMIHEventList Serialization.</returns>
        public static byte[] TLVResponseMIHEventList(BitArray responseMIHEventList)
        {
            return Serialization.SerializeToTLV(TLV_VALUES.TLV_MIH_EVENT_LIST, BitArrayToByteArray(responseMIHEventList));
        }

        /// <summary>
        /// MIHProtocol of a LinkDetectedInfoList.
        /// </summary>
        /// <returns>LinkDetectedInfoList Serialization.</returns>
        public static byte[] TLVLinkDetectedInfoList()
        {
            //TODO to be implemented.
            return null;
        }

        /// <summary>
        /// MIHProtocol of a OldAccessRouter Address.
        /// </summary>
        /// <param name="linkAddr">The address of the old access router.</param>
        /// <returns>OldAccessRouter address serialization.</returns>
        public static byte[] TLVOldAccessRouter(Link_Addr linkAddr)
        {
            return Serialization.SerializeToTLV(TLV_VALUES.TLV_ACCESS_ROUTER_ADDRESS, linkAddr.ByteValue);
        }

        /// <summary>
        /// MIHProtocol of a NewAccessRouter Address.
        /// </summary>
        /// <param name="linkAddr">The address of the new access router.</param>
        /// <returns>NewAccessRouter address serialization.</returns>
        public static byte[] TLVNewAccessRouter(Link_Addr linkAddr)
        {
            return Serialization.SerializeToTLV(TLV_VALUES.TLV_ACCESS_ROUTER_ADDRESS, linkAddr.ByteValue);
        }

        /// <summary>
        /// MIHProtocol of the IPRenewalFlag.
        /// </summary>
        /// <param name="boolFlag">The Ip Renewal Flag as a byte array.</param>
        /// <returns>IPRenewalFlag Serialization.</returns>
        public static byte[] TLVIpRenewalFlag(byte[] boolFlag)
        {
            return Serialization.SerializeToTLV(TLV_VALUES.TLV_IP_RENEWAL_FLAG, boolFlag);
        }

        /// <summary>
        /// MIHProtocol of a Link Parameter Report List.
        /// </summary>
        /// <param name="linkParametersReport">A link parameters report.</param>
        /// <returns>Link Parameters Report List Serialization.</returns>
        public static byte[] TLVLinkParameterReportList(Link_Parameters_Report linkParametersReport)
        {
            return Serialization.SerializeToTLV(TLV_VALUES.TLV_LINK_PARAM_REPORT_LIST,linkParametersReport.LinkParametersReportListByteValue);
        }

        /// <summary>
        /// MIHProtocol of a Timer Interval.
        /// </summary>
        /// <param name="timerInterval">Timer interval value.</param>
        /// <returns>Timer Value serialization.</returns>
        public static byte[] TLVTimerInterval(uint timerInterval)
        {
            return Serialization.SerializeToTLV(TLV_VALUES.TLV_TIME_INTERVAL, BitConverter.GetBytes(timerInterval));
        }

        /// <summary>
        /// MIHProtocol of a Old link identifier.
        /// </summary>
        /// <param name="linkTuppleId">Link_Tuple_Id as the Old Link Identifier.</param>
        /// <returns>The Old Link Identifier Serialization.</returns>
        public static byte[] TLVOldLinkIdentifier(Link_Tuple_Id linkTuppleId)
        {
            return Serialization.SerializeToTLV(TLV_VALUES.TLV_LINK_IDENTIFIER, linkTuppleId.ByteValue);
        }

        /// <summary>
        /// MIHProtocol of a New Link Identifier.
        /// </summary>
        /// <param name="linkTuppleId">The Link Tupple Id as the New Link Identifier.</param>
        /// <returns>New Link Identifier serialization.</returns>
        public static byte[] TLVNewLinkIdentifier(Link_Tuple_Id linkTuppleId)
        {
            return Serialization.SerializeToTLV(TLV_VALUES.TLV_NEW_LINK_IDENTIFIER, linkTuppleId.ByteValue);
        }

        /// <summary>
        /// MIHProtocol of a Link Handover Status.
        /// </summary>
        /// <param name="status">The Link Handover Status,</param>
        /// <returns></returns>
        public static byte[] TLVLinkHandoverStatus(int status)
        {
            return Serialization.SerializeToTLV(TLV_VALUES.TLV_STATUS, BitConverter.GetBytes(status));
        }

        /// <summary>
        /// MIHProtocol of a Devices States Request.
        /// </summary>
        /// <param name="deviceStatesRequest">The Device States Request as a BitArray.</param>
        /// <returns>Devices States Request Serialization.</returns>
        public static byte[] TLVDeviceStatesRequest(BitArray deviceStatesRequest)
        {
            return Serialization.SerializeToTLV(TLV_VALUES.TLV_DEVICE_STATES_REQUEST, BitArrayToByteArray(deviceStatesRequest));
        }

        /// <summary>
        /// MIHProtocol of a Link States Request.
        /// </summary>
        /// <param name="linkStatesRequest">The Link States Request as a BitArray.</param>
        /// <returns>Link States Request Serialization.</returns>
        public static byte[] TLVLinkStatesRequest(BitArray linkStatesRequest)
        {
            return Serialization.SerializeToTLV(TLV_VALUES.TLV_LINK_STATES_REQ, BitArrayToByteArray(linkStatesRequest));
        }

        public static byte[] TLVDeviceStatesRsp()
        {
            return null;
        }

        public static byte[] TLVGetStatusResponseList()
        {
            return null;
        }

        public static byte[] TLVConfigureResponseList()
        {
            return null;
        }

        public static byte[] TLVLinkActionList()
        {
            return null;
        }

        public static byte[] TLVLinkActionsResulList()
        {
            return null;
        }

        public static byte[] TLVListOfLinkPOAList()
        {
            return null;
        }

        public static byte[] TLVQueryResourceReportFlag()
        {
            return null;
        }

        public static byte[] TLVHandoverStatus()
        {
            return null;
        }

        public static byte[] TLVPreferredLinkList()
        {
            return null;
        }

        public static byte[] TLVHandoverResourceQueryList()
        {
            return null;
        }

        public static byte[] TLVIPAddressConfigurationMethods()
        {
            return null;
        }

        public static byte[] TLVDHCPServerAddress()
        {
            return null;
        }

        public static byte[] TLVFAAddress()
        {
            return null;
        }

        public static byte[] TLVAccessRouterAddress()
        {
            return null;
        }

        public static byte[] TLVResourceStatus()
        {
            return null;
        }

        public static byte[] TLVLinkType(Link_Type type)
        {
            return null;
        }
        
        
        public static byte[] TLVPOA(Link_Addr linkAddress)
        {
            return null;
        }

        public static byte[] TLVLinkType()
        {
            return null;
        }

        public static byte[] TLVLinkDetectedInfo(Link_Det_Info linkDetInfo)
        {
            return Serialization.SerializeToTLV(TLV_VALUES.TLV_LINK_DET_INFO, linkDetInfo.ByteVal);
        }

        private static byte[] BitArrayToByteArray(BitArray bits)
        {
            byte[] ret = new byte[bits.Length / 8];
            bits.CopyTo(ret, 0);
            return ret;
        }

    }
}
