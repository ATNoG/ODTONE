/**************************************************************************
                          MIH_C_Link_Constants.h
                             -------------------
    copyright            : (C) 2012 by Eurecom
    email                : davide.brizzolara@eurecom.fr; michelle.wetterwald@eurecom.fr
***************************************************************************
mRALlte Constants
***************************************************************************/

#ifndef __mRALlte_LINK_CONSTANTS_H__
#define __mRALlte_LINK_CONSTANTS_H__

#define PROTOCOL_VERSION 16   		// 0001 0000 (10)
#define ACK_REQ_ON 8			// 0000 1000
#define ACK_RSP_ON 4			// 0000 0100
#define MIH_LINK_HEADER_2 0   		// 0000 0000 (00)

/*********************CONSTANTS FORMAT***************************************************
// Primitive name					// SID(4bit)+OP(2bit)+AID(8bit) (HEX)
**********************CONSTANTS FORMAT***************************************************/

// Link Register Indication
#define MIH_LINK_HEADER_3_ES_Ind 1564			//1c 06
#define MIH_LINK_HEADER_4_ES_Ind 0			    // 00 00

// Link_Up Indication
#define MIH_LINK_HEADER_3_Link_Up_Ind 556		// 2c 02 (2 3 2)
#define MIH_LINK_HEADER_4_Link_Up_Ind 0			// 00 00

// Link_Down Indication
#define MIH_LINK_HEADER_3_Link_Down_Ind 812		// 2c 03 (2 3 3)
#define MIH_LINK_HEADER_4_Link_Down_Ind 0		// 00 00

// Capability discover request
#define MIH_LINK_HEADER_3_Cap_Disc_Req 276		// 14 01 (1 1 1)

// Capability discover confirm
#define MIH_LINK_HEADER_3_Cap_Disc_Conf 272		// 10 01 (1 0 1)

// Event subscribe request
#define MIH_LINK_HEADER_3_Evt_Sub_Req 1044		// 14 04 (1 1 4)

// Event subscribe confirm
#define MIH_LINK_HEADER_3_Evt_Sub_Conf 1040	 	// 10 04 (1 0 4)

// Event unsubscribe request
#define MIH_LINK_HEADER_3_Evt_Unsub_Req 1300    // 14 05 (1 1 5)

// Event unsubscribe confirm
#define MIH_LINK_HEADER_3_Evt_Unsub_Conf 1296	// 10 05 (1 0 5)

// Link Get Parameters Request
#define MIH_LINK_HEADER_3_Get_Param_Req 308		// 34 01 (3 1 1)

// Link Get Parameters Confirm
#define MIH_LINK_HEADER_3_Get_Param_Conf 304	// 30 01 (3 0 1)

// Link Configure Threshold Request
#define MIH_LINK_HEADER_3_Link_Conf_Thres_Req 564	// 34 02 (3 1 2)

// Link Configure Threshold Confirm
#define MIH_LINK_HEADER_3_Link_Conf_Thres_Conf 560 	// 30 02 (3 0 2)

// Link Action Request
#define MIH_LINK_HEADER_3_Link_Act_Req 820		// 34 03 (3 1 3)

// Link Action Confirm
#define MIH_LINK_HEADER_3_Link_Act_Conf 816		// 30 03 (3 0 3)

// Link Detected Indication
#define MIH_LINK_HEADER_3_Link_Detected_Ind 300	// 2c 01 (2 3 1)
#define MIH_LINK_HEADER_4_Link_Detected_Ind 0	// 00 00

// Link Going Down
#define MIH_LINK_HEADER_3_Link_Going_Down 1580	// 2c 06 (2 3 6)
#define MIH_LINK_HEADER_4_Link_Going_Down 0		// 00 00

//Link Parameters Report Indication
#define MIH_LINK_HEADER_3_Link_Param_Report 1324  // 2c 05 (2 3 5)
#define MIH_LINK_HEADER_4_Link_Param_Report 0     // 00 00

// Primitives Data Setting

#define MIH_NETWORK_ID_LENGTH 7
#define MIH_LINK_HEADER_LENGTH 8
#define MIH_NET_AUX_ID_LENGTH 6
#define NET_CAP_LENGTH 4
#define MIH_MAC_ADDRESS_LENGTH 6
#define MIH_3GPP_ADDRESS_LENGTH 8
#define MIH_3GPP_ADDRESS_CELL_ID_LENGTH 4
#define MIHF_MAX_LINK_ID_NAME 6
#define MIHF_MAX_LINK_ID_NAME_MIHF 5
#define MIHF_MAX_LINK_ID_NAME_LINK 4
#define MIHF_MAX_LINK_ID_NAME_USER 4
#define MIHF_EVT_LIST_LENGTH 4
#define MIHF_CMD_LIST_LENGTH 4
#define MAX_NUMBER_LINK_ID 2
#define GET_STATUS_RESPONSE_LIST_LENGTH 2
#define LINK_DET_INFO_VALUE_LIST_LENGTH 1
#define LINK_STATES_RSP_LIST_LENGTH 1
#define LINK_PARAM_TYPE_LIST_LENGTH 1
#define LINK_DESC_RSP_LIST_LENGTH 1
#define GET_STATUS_RSP_LIST_LENGTH 1
#define LIST_PARAM_RPT_LENGTH_VALUE 1

#define LINK_SCAN_RSP_LIST_LENGTH 1
#define LINK_ACTION_REQ_LIST_LENGTH 1
#define TRESHOLD_LIST_LENGTH 1
#define LINK_CFG_STATUS_LIST_LENGTH 1
#define LINK_ADDRESS_LENGTH 2
#define LINK_ACTION_RSP_LENGTH 1
#define LINK_CFG_PARAM_LIST_LENGTH 1

// SID - Service Identifier
#define SID_SERVICE_MANAGEMENT 1 //Service Management
#define SID_EVENT_SERVICE 2 // Event Service
#define SID_COMMAND_SERVICE 3 // Command Service
#define SID_INFORMATION_SERVICE 4 // Information Service

// OP - Operation Code
#define OP_CONFIRM 0 // Confirm
#define OP_REQUEST 1 // Request
#define OP_RESPONCE 2 // Responce
#define OP_INDICATION 3 // Indication

//AID - Action Identifier
//MIH messages for Service Management
#define AID_CAPABILITY_DISCOVER 1
#define AID_EVENT_SUBSCRIBE 4
#define AID_EVENT_UNSUBSCRIBE 5
#define AID_LINK_REGISTER_INDICATION 6 //ODTONE SPECIFIC
//MIH messages for Event Service
#define AID_LINK_DETECTED 1
#define AID_LINK_UP 2
#define AID_LINK_DOWN 3
#define AID_LINK_PARAMETERS_REPORT 5
#define AID_LINK_GOING_DOWN 6
//MIH messages for Command Service
#define AID_LINK_GET_PARAMETERS 1
#define AID_LINK_CONFIGURE_THRESHOLDS 2
#define AID_LINK_ACTIONS 3

#define CHOICE_MAC_ADDRESS 0
#define CHOICE_ADDRESS_3GPP 3

/***************
 * TLV VALUE
 ***************/

#define TLV_MIHF_ID_SOURCE 1
#define TLV_MIHF_ID_DESTINATION 2
#define TLV_STATUS 3
#define TLV_EVENT_LIST 5
#define TLV_COMMAND_LIST 6
#define TLV_LINK_TUPLE_ID 13
#define TLV_LINK_DOWN_REASON_CODE 20
#define TLV_LINK_TIME_INTERVAL 21
#define TLV_LINK_GOING_DOWN_REASON 22
#define TLV_LINK_PARAM_RPT_LIST 23
#define TLV_LINK_CFG_PARAM_LIST 29
#define TLV_LINK_CFG_STATUS_LIST 30
#define TLV_LINK_DET_INFO_LIST 58

// ODTONE SPECIFIC
#define TLV_LINK_EVENT_LIST 101
#define TLV_LINK_CMD_LIST 102
#define TLV_LIST_LINK_PARAM_TYPE 103
#define TLV_LINK_PARAMETERS_STATUS_LIST 104
#define TLV_LINK_STATES_RSP 106
#define TLV_LINK_DESCRIPTOR_RSP 108
#define TLV_LINK_ACTION 109
#define TLV_LINK_AC_RESULT 110
#define TLV_LINK_SCAN_RSP_LIST 111
#define TLV_LINK_DET_INFO 112
#define TLV_LINK_REGISTER_TYPE 113

#endif
