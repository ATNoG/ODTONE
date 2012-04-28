/**************************************************************************
                          mRALlte_variables.h
                             -------------------
    copyright            : (C) 2011 by Eurecom
    email                : davide.brizzolara@eurecom.fr; michelle.wetterwald@eurecom.fr
***************************************************************************
mRALlte Constants
***************************************************************************/
#ifndef __mRALlte_VARIABLES_H__
#define __mRALlte_VARIABLES_H__

#include "MIH_C_Link_Primitives.h"

/**********
 * DEBUG
 **********/
#define OUTPUT_LEVEL_1 // print relevant information
//#define OUTPUT_LEVEL_2 // print all contents
//#define OUTPUT_LEVEL_3 // print hex

#define HEADER_VERSION_PRINT 240
#define HEADER_VERSION_0 0
#define HEADER_VERSION_1 16

#define ACK_REQ_PRINT 8
#define ACK_RSP_PRINT 4
#define ACK_UIR_PRINT 2
#define MORE_FRAGMENT_PRINT 1
#define FRAGMENT_NUMBER_PRINT 254
#define RESERVED1_PRINT 1
#define SID_PRINT 240
#define OPCODE_PRINT 12
#define AID_PRINT 1023
#define RSVD2_PRINT 15
#define TID_PRINT 255

#define LINK_PARAM_VAL 0
#define QOS_PARAM_VAL 1

#define LINK_TH_ACTION_SET_NORMAL 0
#define LINK_TH_ACTION_SET_ONE_SHOT 1
#define LINK_TH_ACTION_CANCEL 2

#define ABOVE_THRESHOLD 0
#define BELOW_THRESHOLD 1

#define CONFIG_STATUS_SUCCESS 0
#define CONFIG_STATUS_ERROR 1

/*END DEBUG*/

#define CONVERSION 256
#define LINK_TYPE_802_11 19
#define LINK_TYPE_3GPP 23

#define LINK_ADDR_FAMILY_MAC 6
#define LENGTH_MAC_ADDRESS 6

#define IP_ADDRESS "127.0.0.1"
#define SOCKET_ADDRESS "127.0.0.1"
#define PORT_MIHF 1235
#define PORT_ODTONE 1025

#define MIHLink_MAX_LENGTH 500
#define MIH_C_MESSAGE_MAX_LENGTH 50

#define ADDRESS_3GPP "0335060080149150"

/************* support for reception *************/
typedef struct MIH_C_ODTONE_Message{
	MIH_C_Header Header;
	MIH_C_Mihf_ID_Mihf MIHF_Source;
	MIH_C_Mihf_ID_Link MIHF_Destination;
	MIH_C_VariablePayload variablePayload[MIH_C_MESSAGE_MAX_LENGTH];
}__attribute__((__packed__))MIH_C_ODTONE_Message;
/*************************************************/

/********************
 * PRIMITIVE VALUES
 *******************/

#define MIH_SOURCE_ID "link"
#define MIH_DESTINATION_ID "mihf1"
#define MIH_SOURCE_ID_LINK_UP "link"
#define MIH_NETWORK_ID "eurecom"
#define MIH_NETAUX "netaux"

//Link_Register (send reg indication)
#define VALUE_NULL 0
#define CHOICE_NULL 0

//Link Down Indication
#define REASON_CODE_LENGTH 1
#define LINK_DOWN_RC_EXPLICIT_DISCONNECT 0
#define LINK_DOWN_RC_PACKET_TIMEOUT 1
#define LINK_DOWN_RC_NO_RESOURCE 2
#define LINK_DOWN_RC_NO_BROADCAST 3
#define LINK_DOWN_RC_AUTHENTICATION_FAILURE 4
#define LINK_DOWN_RC_BILLING_FAILURE 5

// Status
#define STATUS_SUCCESS 0
#define STATUS_UNSPECIFIED_FAILURE 1
#define STATUS_REJECTED 2
#define STATUS_AUTHORIZATION_FAILURE 3
#define STATUS_NETWORK_ERROR 4

//Event List
#define EVT_LIST_LINK_DETECTED 1
#define EVT_LIST_LINK_UP 2
#define EVT_LIST_LINK_DOWN 4
#define EVT_LIST_LINK_PARAMETERS_REPORT 8
#define EVT_LIST_LINK_GOING_DOWN 16
#define EVT_LIST_LINK_HANDOVER_IMMINENT 32
#define EVT_LIST_LINK_HANDOVER_COMPLETE 64
#define EVT_LIST_PDU_TRANSMIT_STATUS 128

//Command List
#define CMD_LIST_LINK_EVENT_SUBSCRIBE 2
#define CMD_LIST_LINK_EVENT_UNSUBSCRIBE 4
#define CMD_LIST_LINK_GET_PARAMETERS 8
#define CMD_LIST_LINK_CONFIGURE_THRESHOLDS 16
#define CMD_LIST_LINK_ACTION 32

//Link_Param
#define CHOICE_LINK_PARAM_VAL 0
#define CHOICE_QOS_PARAM_VAL 1
#define LINK_PARAM_VAL_VALUE 100

//Link_States_Rsp
#define CHOICE_OP_MODE 0
#define CHOICE_CHANNEL_ID 1

#define OP_MODE_NORMAL_MODE 0
#define OP_MODE_POWER_SAVING_MODE 1
#define OP_MODE_POWERED_DOWN 2

//Link_Desc_Rsp
#define CHOICE_NUM_COS 0
#define CHOICE_NUM_QUEUE 1

#define NUM_COS_VALUE 6
#define NUM_NUM_QUEUE_VALUE 8

//Config Status
#define CONFIG_STATUS_TRUE 0
#define CONFIG_STATUS_FALSE 1

//Link Action
#define LINK_ACTION_LENGTH 1

#define LINK_AC_TYPE_NONE 0
#define LINK_AC_TYPE_LINK_DISCONNECT 1
#define LINK_AC_TYPE_LOW_POWER 2
#define LINK_AC_TYPE_POWER_DOWN 3
#define LINK_AC_TYPE_POWER_UP 4

#define LINK_SCAN 1

//Link Get Parameter Confirm
#define LINK_GET_PARAMETERS_CONFIRM_LINK_PARAM_LENGTH 6
#define LINK_GET_PARAMETERS_CONFIRM_LINK_PARAM_LIST_LENGTH 1

#define LINK_GET_PARAMETERS_CONFIRM_LINK_STATES_RSP_LIST_LENGTH 1

#define LINK_GET_PARAMETERS_CONFIRM_LINK_DESC_LIST_LENGTH 1

//Link Configure Threshold Confirm
#define LINK_CONF_THRES_CONF_LINK_CFG_STATUS_LIST_TYPE 30
#define LINK_CONF_THRES_CONF_LINK_CFG_STATUS_LENGTH 7
#define LINK_CONF_THRES_CONF_LINK_CFG_STATUS_LIST_LENGTH 1

#define LINK_CONF_THRES_CONF_LINK_CFG_STATUS_THRESHOLD_VAL 100
#define LINK_CONF_THRES_CONF_LINK_CFG_STATUS_THRESHOLD_X_DIR 1

//Link Action Confirm
#define LINK_ACTION_CONF_STATUS_LENGTH 1
#define LINK_ACTION_CONF_STATUS_VALUE 0
#define LINK_ACTION_CONF_LINK_AC_RESULT 0

#define LINK_ADDR_3GPP_3G_CELL_ID 2
#define MCC 208
#define MNC 01
#define CELL_ID 45
#define SIG_STRENGTH_VALUE 100

//Link Get Parameters
#define LINK_PARAM_802_11 5
#define LINK_PARAM_GEN 0
#define LINK_PARAM_GEN_VAL 0
#define OP_MODE 1
#define CHANNEL_ID 2
#define CLASSES_SERVICE 1
#define QUEUES_SUPPORTED 2

//Link Detected Indication
#define LINK_DETECTED_INDICATION_SIG_STRENGTH 5
#define LINK_DETECTED_INDICATION_SINR 45
#define LINK_DETECTED_INDICATION_LINK_DATA_RATE 1000

#define EVENT_SERVICE_SUPPORTED_ON 1
#define COMMAND_SERVICE_SUPPORTED_ON 2
#define INFORMATION_SERVICE_SUPPORTED_ON 4

#define NET_CAPS_QOS_CLASS_0 2
#define NET_CAPS_QOS_CLASS_1 4
#define NET_CAPS_INTERNET_ACCESS 64

//Link Going Down Reason
#define LINK_DETECTED_TIME_INTERVAL 50 //ms
#define LINK_GOING_DOWN_REASON_EXPLICIT_DISCONNECT 0
#define LINK_GOING_DOWN_REASON_LINK_PARAM_DEGRADING 1
#define LINK_GOING_DOWN_REASON_LOW_POWER 2
#define LINK_GOING_DOWN_REASON_NO_RESOURCE 3

#endif
