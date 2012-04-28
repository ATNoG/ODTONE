/**************************************************************************
                          MIH_C_Link_Primitives.h  -  description
                             -------------------
    copyright            : (C) 2012 by Eurecom
    email                : davide.brizzolara@eurecom.fr; michelle.wetterwald@eurecom.fr
***************************************************************************
Type definition and structure for ODTONE interface
***************************************************************************/

#include <sys/types.h>
#include "MIH_C_Link_Constants.h"

typedef u_int8_t MIH_C_Header_Vers;
typedef u_int8_t MIH_C_Header_FN;
typedef u_int16_t MIH_C_Message_ID;
typedef u_int16_t MIH_C_Transaction_ID;
typedef u_int16_t MIH_C_Variable_Payload_Length;
typedef u_int8_t MIH_C_Type;
typedef u_int8_t MIH_C_Length;
typedef u_int8_t MIH_C_Link_Type;
typedef u_int16_t MIH_C_Address_Family;
typedef u_int8_t MIH_C_Length_Address;
typedef u_int8_t MIH_C_Status_Value;
typedef u_int8_t MIH_C_Reason_Code;
typedef u_int8_t MIH_C_Exec_Delay;
typedef u_int8_t MIH_C_Link_State_Req_Value;
typedef u_int8_t MIH_C_Link_Param_Type_Value;
typedef u_int16_t MIH_C_Link_States_Req_Value;
typedef u_int16_t MIH_C_Link_Desc_Req_Value;
typedef u_int16_t MIH_C_Link_Param_Value;
typedef u_int8_t MIH_C_Link_Ac_Type;
typedef u_int8_t MIH_C_Link_Ac_Attr;
typedef u_int8_t MIH_C_Choice;
typedef u_int8_t MIH_C_Link_States_Rsp_Value;
typedef u_int8_t MIH_C_Link_Desc_Rsp_Value;
typedef u_int8_t MIH_C_Choice_Address;
typedef u_int8_t MIH_C_Link_Mihcap_Flag;
typedef u_int16_t MIH_C_Time_Interval_Value;
typedef u_int8_t MIH_C_Link_Going_Down_Reason_Value;
typedef u_int16_t MIH_C_SINR;
typedef u_int32_t MIH_C_Link_Data_Rate;

//Link Get Parameters Confirm
typedef u_int8_t MIH_C_List_Length;

//Link_Configure_Threshold_Request
typedef u_int8_t MIH_C_Link_Param_Type_Num;
typedef u_int16_t MIH_C_Timer_Interval;
typedef u_int8_t MIH_C_Th_Action;
typedef u_int16_t MIH_C_Threshold_Val;
typedef u_int8_t MIH_C_Threshold_X_Dir;

//Link_Configure_Threshold_Confirm
typedef u_int8_t MIH_C_Config_Status;

//Link_Action_Request
typedef u_int16_t MIH_C_Link_Ac_Ex_Time;
typedef u_int8_t MIH_C_Link_Addr[LINK_ADDRESS_LENGTH];
typedef u_int16_t MIH_C_Execution_Delay;

// Link_Action_Confirm
typedef u_int8_t MIH_C_Link_Ac_Result_Value;
typedef u_int8_t MIH_C_Link_Sig_Strength_Value;

typedef u_int8_t MIH_C_VariablePayload;

typedef struct {
	MIH_C_Choice Choice;
	MIH_C_Link_Sig_Strength_Value Link_Sig_Strength_Value;
}__attribute__((__packed__))MIH_C_Link_Sig_Strength;

typedef struct {
	MIH_C_Choice Choice;
    MIH_C_Link_States_Rsp_Value Link_States_Rsp_Value;
}__attribute__((__packed__))MIH_C_Link_States_Rsp;

typedef struct {
	MIH_C_Choice Choice;
    MIH_C_Link_Desc_Rsp_Value Link_Desc_Rsp_Value;
}__attribute__((__packed__))MIH_C_Link_Desc_Rsp;

typedef struct{
	MIH_C_Choice Param_Type_Choice;
	MIH_C_Link_Param_Type_Num Link_Param_Type_Num;
	MIH_C_Choice Choice;
	MIH_C_Link_Param_Value Link_Param_Value;
}__attribute__((__packed__))MIH_C_Link_Param;

typedef struct{
	MIH_C_Choice Choice;
	MIH_C_Link_Param_Type_Value Link_Param_Type_Value;
}__attribute__((__packed__))MIH_C_Link_Param_Type;

typedef struct{
	 u_int8_t MAC_Addr_Val[MIH_MAC_ADDRESS_LENGTH];
}__attribute__((__packed__))MIH_C_MAC_Address;

typedef struct{
	 u_int8_t Addr_Val_List_Length;
	 u_int8_t Addr_Val_3GPP[MIH_3GPP_ADDRESS_LENGTH];
}__attribute__((__packed__))MIH_C_Address_3GPP;

typedef struct{
	 u_int8_t PLMN_ID[3];
	 u_int32_t Address_3GPP_CellId_Value;
}__attribute__((__packed__))MIH_C_Address_3GPP_CellId;

typedef struct{
	 u_int8_t Net_Aux_Id_Length;
	 char Net_Aux_Id_Value[MIH_NET_AUX_ID_LENGTH];
}__attribute__((__packed__))MIH_C_Net_Aux_Id;

typedef struct{
	 u_int8_t Network_Id_Length;
	 char Network_Id_Value[MIH_NETWORK_ID_LENGTH];
}__attribute__((__packed__))MIH_C_Network_Id;

typedef struct{
	MIH_C_Choice Choice;
	u_int8_t Sig_Strength_Value; //Integer or Percentage
}__attribute__((__packed__))MIH_C_Sig_Strength;

typedef struct{
	 u_int8_t Length;
	 char Link_ID_Char[MIHF_MAX_LINK_ID_NAME_MIHF];
}__attribute__((__packed__))MIH_C_Link_ID_Name_Mihf;

typedef struct{
	 u_int8_t Length;
	 char Link_ID_Char[MIHF_MAX_LINK_ID_NAME_LINK];
}__attribute__((__packed__))MIH_C_Link_ID_Name_Link;

typedef struct{
	u_int8_t Length;
	char Link_ID_Char[MIHF_MAX_LINK_ID_NAME_USER];
}__attribute__((__packed__))MIH_C_Link_ID_Name_User;

typedef struct{
	 u_int8_t Evt_List_Oct[MIHF_EVT_LIST_LENGTH];
}__attribute__((__packed__))MIH_C_Evt_List_Data;

typedef struct{
	 u_int8_t Cmd_List_Oct[MIHF_CMD_LIST_LENGTH];
}__attribute__((__packed__))MIH_C_Cmd_List_Data;

typedef enum
{
	NONE = 0,
	LINK_DISCONNECT = 1,
	LINK_LOW_POWER = 2,
	LINK_POWER_DOWN = 3,
	LINK_POWER_UP = 4,
} MIH_C_Link_AC_Type;

// Struct Message Header
typedef struct{
	MIH_C_Header_Vers Header_Vers;
	MIH_C_Header_FN Header_FN;
	MIH_C_Message_ID Message_ID;
	MIH_C_Transaction_ID Transaction_ID;
	MIH_C_Variable_Payload_Length Payload_Length;
}__attribute__((__packed__))MIH_C_Header;

// struct Link_ID
typedef struct{
	MIH_C_Link_Type LinkType;
	MIH_C_Choice_Address Choice_Address;
	MIH_C_Address_3GPP Address_3GPP;
}__attribute__((__packed__))MIH_C_Link_ID_3GPP;

typedef struct{
	MIH_C_Link_Type LinkType;
	MIH_C_Address_Family AddressFamily;
	MIH_C_Length_Address LengthAddress;
	MIH_C_MAC_Address MAC_Address;
}__attribute__((__packed__))MIH_C_Link_ID;

typedef struct{
	MIH_C_Link_ID_3GPP Link_ID_3GPP;
    MIH_C_Choice Choice;
    // MIH_C_Choice_Address Choice_Address; (optional)
    // MIH_C_Link_Addr Link_Addr (optional)
    MIH_C_Network_Id Network_Id;
    MIH_C_Net_Aux_Id Net_Aux_Id;
    MIH_C_SINR Sinr;
    MIH_C_Link_Data_Rate Link_Data_Rate;
    MIH_C_Sig_Strength Sig_Strength;
    MIH_C_Link_Mihcap_Flag Link_Mihcap_Flag;
    u_int32_t Net_Caps;
}__attribute__((__packed__))MIH_C_Link_Det_Info_Value;

/******************************
*  TLV List
******************************/

// MIHF - TLV source 1 - TLV destination 2
typedef struct{
	MIH_C_Type  Type;
	MIH_C_Length Length;
	MIH_C_Link_ID_Name_Mihf Link_ID_Name_Mihf;
}__attribute__((__packed__))MIH_C_Mihf_ID_Mihf;

// Link - TLV source 1 - TLV destination 2
typedef struct{
	MIH_C_Type  Type;
	MIH_C_Length Length;
	MIH_C_Link_ID_Name_Link Link_ID_Name_Link;
}__attribute__((__packed__))MIH_C_Mihf_ID_Link;

// User - TLV source 1 - TLV destination 2
typedef struct{
	MIH_C_Type  Type;
	MIH_C_Length Length;
	MIH_C_Link_ID_Name_User Link_ID_Name_User;
}__attribute__((__packed__))MIH_C_Mihf_ID_User;

// ODTONE specific Link_Register_Information - 101
typedef struct {
	MIH_C_Type Type;
	MIH_C_Length Length;
	MIH_C_Link_ID_3GPP Link_ID_3GPP;
}__attribute__((__packed__))MIH_C_Link_Register_Information;

// STATUS - 3
typedef struct {
	MIH_C_Type Type;
	MIH_C_Length Length;
	MIH_C_Status_Value Status_Value;
}__attribute__((__packed__))MIH_C_Status;

// Event List - 5
typedef struct {
	MIH_C_Type Type;
	MIH_C_Length Length;
	MIH_C_Evt_List_Data Evt_List_Data;
}__attribute__((__packed__))MIH_C_MIH_Evt_List;

//Command List - 6
typedef struct {
	MIH_C_Type Type;
	MIH_C_Length Length;
	MIH_C_Cmd_List_Data Cmd_List_Data;
}__attribute__((__packed__))MIH_C_MIH_Cmd_List;

//Link Identifier - Type 113
typedef struct {
	MIH_C_Type Type;
	MIH_C_Length Length;
	MIH_C_Link_ID_3GPP Link_ID_3GPP;
}__attribute__((__packed__))MIH_C_Link_Identifier;

typedef struct {
	  MIH_C_Type Type;
      MIH_C_Length Length;
      MIH_C_Link_ID Link_ID;
      MIH_C_Choice Choice;
      // MIH_C_Link_Addr Link_Addr (optional)
}__attribute__((__packed__))MIH_C_Link_Tuple_Id;

typedef struct {
	  MIH_C_Type Type;
      MIH_C_Length Length;
      MIH_C_Link_ID_3GPP Link_ID_3GPP;
      MIH_C_Choice Choice;
      // MIH_C_Link_Addr Link_Addr (optional)
}__attribute__((__packed__))MIH_C_Link_Tuple_Id_3GPP;

//Link Dn Reason -
typedef struct {
      MIH_C_Type Type;
      MIH_C_Length Length;
      MIH_C_Reason_Code Reason;
}__attribute__((__packed__))MIH_C_Link_Dn_Reason;

// struct link_action
typedef struct {
    MIH_C_Link_Ac_Type Link_Ac_Type;
    MIH_C_Link_Ac_Attr Link_Ac_Attr;
}__attribute__((__packed__))MIH_C_Action_Value;

// ODTONE SPECIFIC - Link_Evt_List - Type 101
typedef struct {
	MIH_C_Type Type;
	MIH_C_Length Length;
	MIH_C_Evt_List_Data Evt_List_Data;
}__attribute__((__packed__))MIH_C_Link_Evt_List;

// ODTONE SPECIFIC - Link_Cmd_List - Type 102
typedef struct {
	MIH_C_Type Type;
	MIH_C_Length Length;
	MIH_C_Cmd_List_Data Cmd_List_Data;
}__attribute__((__packed__))MIH_C_Link_Cmd_List;

// ODTONE SPECIFIC - LINK_ACTION  108
typedef struct {
    MIH_C_Type Type;
    MIH_C_Length Length;
    MIH_C_Action_Value Link_Action_Value;
}__attribute__((__packed__))MIH_C_Link_Action;

//link_id List 25
typedef struct {
	MIH_C_Type Type;
    MIH_C_Length Length;
    MIH_C_Link_ID Link_ID[MAX_NUMBER_LINK_ID];
}__attribute__((__packed__))MIH_C_List_Link_ID;

// ODTONE SPECIFIC - LIST(LINK_PARAM_TYPE)
// TLV 102 - LinkParametersRequest (Link Get Parameters Request)
typedef struct {
	MIH_C_Type Type;
	MIH_C_Length Length;
	MIH_C_List_Length List_Length;
	MIH_C_Link_Param_Type Link_Param_Type[LINK_PARAM_TYPE_LIST_LENGTH];
}__attribute__((__packed__))MIH_C_Link_Param_Type_List;

// ODTONE SPECIFIC - LINK_STATES_REQ
// TLV 105 - LinkStatesRequest (Link Get Parameters Request)
typedef struct {
    MIH_C_Type Type;
    MIH_C_Length Length;
    MIH_C_Link_States_Req_Value Link_States_Req_Value;
}__attribute__((__packed__))MIH_C_Link_States_Req;

// ODTONE SPECIFIC - LINK_DESC_REQ
// TLV 107 - LinkDescriptorsRequest (Link Get Parameters Request)
typedef struct {
    MIH_C_Type Type;
    MIH_C_Length Length;
    MIH_C_Link_Desc_Req_Value Link_Desc_Req_Value;
}__attribute__((__packed__))MIH_C_Link_Desc_Req;

// ODTONE SPECIFIC - LIST(LINK_PARAM_TYPE)
// TLV 103 - LinkParametersStatusList (Link Get Parameters Confirm)
typedef struct {
    MIH_C_Type Type;
    MIH_C_Length Length;
    MIH_C_List_Length List_Length;
    MIH_C_Link_Param Link_Param[LINK_PARAM_TYPE_LIST_LENGTH];
}__attribute__((__packed__))MIH_C_Link_Param_List;

// ODTONE SPECIFIC Link States Rsp List  - 105
typedef struct {
    MIH_C_Type Type;
    MIH_C_Length Length;
    MIH_C_List_Length List_Length;
    MIH_C_Link_States_Rsp Link_States_Rsp[LINK_STATES_RSP_LIST_LENGTH];
}__attribute__((__packed__))MIH_C_Link_States_Rsp_List;

// ODTONE SPECIFIC Link Description Responce List - 107
typedef struct {
    MIH_C_Type Type;
    MIH_C_Length Length;
    MIH_C_List_Length List_Length;
    MIH_C_Link_Desc_Rsp Link_Desc_Rsp[LINK_DESC_RSP_LIST_LENGTH];
}__attribute__((__packed__))MIH_C_Link_Desc_Rsp_List;

// ODTONE SPECIFIC Link Action Confirm - 109
typedef struct {
    MIH_C_Type Type;
    MIH_C_Length Length;
    MIH_C_Link_Ac_Result_Value Link_Ac_Result_Value;
}__attribute__((__packed__))MIH_C_Link_Ac_Result;

//Link Configure Threshold
typedef struct MIH_C_Threshold{
	MIH_C_Threshold_Val Threshold_Val;
	MIH_C_Threshold_X_Dir Threshold_X_Dir;
}__attribute__((__packed__))MIH_C_Threshold;

//Threshold List - struct
typedef struct MIH_C_Threshold_List {
	MIH_C_Length Length;
	MIH_C_Threshold Threshold[TRESHOLD_LIST_LENGTH];
}__attribute__((__packed__))MIH_C_Threshold_List;

//Link Configure Parameter
typedef struct MIH_C_Link_Cfg_Param{
    MIH_C_Choice Link_Param_Type_Choice;
    MIH_C_Link_Param_Type_Num Link_Param_Type_Num;
    MIH_C_Choice Choice;
	// MIH_C_Timer_Interval Timer_Interval;
	MIH_C_Th_Action Th_Action;
	MIH_C_Threshold_List Threshold_List;
}__attribute__((__packed__))MIH_C_Link_Cfg_Param;

//Link Configure Parameter List - 29
typedef struct MIH_C_Link_Cfg_Param_List{
	MIH_C_Type Type;
	MIH_C_Length Length;
	MIH_C_List_Length List_Length;
	MIH_C_Link_Cfg_Param Link_Cfg_Param[LINK_CFG_PARAM_LIST_LENGTH];
}__attribute__((__packed__))MIH_C_Link_Cfg_Param_List;

//Link Configure Responce struct
typedef struct MIH_C_Link_Cfg_Rsp{
    MIH_C_Link_Param_Type_Num Link_Param_Type_Num;
    MIH_C_Threshold Threshold;
	MIH_C_Config_Status Config_Status;
}__attribute__((__packed__))MIH_C_Link_Cfg_Rsp;

// Link_Cfg_Status - Link Configure Thresholds Confirm
typedef struct MIH_C_Link_Cfg_Status{
	MIH_C_Choice Param_Type_Choice;
	MIH_C_Link_Param_Type_Num Link_Param_Type_Num;
	MIH_C_Threshold Threshold;
	MIH_C_Config_Status Config_Status;
}__attribute__((__packed__))MIH_C_Link_Cfg_Status;

//Link Configure Status List - 30
typedef struct MIH_C_Link_Cfg_Status_List{
	MIH_C_Type Type;
    MIH_C_Length Length;
    MIH_C_List_Length List_Length;
	MIH_C_Link_Cfg_Status Link_Cfg_Status[LINK_CFG_STATUS_LIST_LENGTH];
}__attribute__((__packed__))MIH_C_Link_Cfg_Status_List;

//Link Action Request struct
typedef struct MIH_C_Link_Action_Req{
      MIH_C_Link_ID_3GPP Link_ID;
      MIH_C_Choice Choice;
      //MIH_C_Link_Addr Link_Addr;
      MIH_C_Action_Value Link_Action_Value;
      MIH_C_Link_Ac_Ex_Time Link_Ac_Ex_Time;
}__attribute__((__packed__))MIH_C_Link_Action_Req;

//Link Action Request -
typedef struct MIH_C_Link_Action_Req_List{
      MIH_C_Type Type;
      MIH_C_Length Length;
      MIH_C_List_Length List_Length;
      MIH_C_Link_Action_Req Link_Action_Req[LINK_ACTION_REQ_LIST_LENGTH];
}__attribute__((__packed__))MIH_C_Link_Action_Req_List;

//Link Scan Responce struct
typedef struct MIH_C_Link_Scan_Rsp{
	MIH_C_Choice Choice;
	MIH_C_Address_3GPP_CellId Address_3GPP_CellId;
	MIH_C_Network_Id Network_Id;
	MIH_C_Link_Sig_Strength Link_Sig_Strength;
}__attribute__((__packed__))MIH_C_Link_Scan_Rsp;

//Link Scan Response List
typedef struct MIH_C_Link_Scan_Rsp_List{
	MIH_C_List_Length List_Length;
	MIH_C_Link_Scan_Rsp Link_Scan_Rsp[LINK_SCAN_RSP_LIST_LENGTH];
}__attribute__((__packed__))MIH_C_Link_Scan_Rsp_List;

// 	Link_Action_Confirm - Link Action Rsp List
typedef struct MIH_C_Link_Action_Rsp_List{
     MIH_C_Type Type;
     MIH_C_Length Length;
     MIH_C_Link_Scan_Rsp_List Link_Scan_Rsp_List;
}__attribute__((__packed__))MIH_C_Link_Action_Rsp_List;

typedef struct MIH_C_Link_Det_Info_List{
     MIH_C_Type Type;
     MIH_C_Length Length;
     MIH_C_List_Length List_Length;
     MIH_C_Link_Det_Info_Value Link_Det_Info_Value[LINK_DET_INFO_VALUE_LIST_LENGTH];
}__attribute__((__packed__))MIH_C_Link_Det_Info_List;

typedef struct MIH_C_Link_Det_Info{
     MIH_C_Type Type;
     MIH_C_Length Length;
     MIH_C_Link_Det_Info_Value Link_Det_Info_Value;
}__attribute__((__packed__))MIH_C_Link_Det_Info;

typedef struct MIH_C_Time_Interval{
     MIH_C_Type Type;
     MIH_C_Length Length;
     MIH_C_Time_Interval_Value Time_Interval_Value;
}__attribute__((__packed__))MIH_C_Time_Interval;

typedef struct MIH_C_Link_Going_Down_Reason{
     MIH_C_Type Type;
     MIH_C_Length Length;
     MIH_C_Link_Going_Down_Reason_Value Link_Going_Down_Reason_Value;
}__attribute__((__packed__))MIH_C_Link_Going_Down_Reason;

typedef struct{
	MIH_C_Link_Param Link_Param;
	MIH_C_Choice Choice;
	//MIH_C_Threshold Threshold;
}__attribute__((__packed__))MIH_C_Link_Param_Rpt;

typedef struct{
	MIH_C_List_Length List_Length;
	MIH_C_Link_Param_Rpt Link_Param_Rpt[LIST_PARAM_RPT_LENGTH_VALUE];
}__attribute__((__packed__))MIH_C_Link_Param_Rpt_List_Value;

//Link Param Rpt List - 23
typedef struct{
	MIH_C_Type Type;
	MIH_C_Length Length;
	MIH_C_Link_Param_Rpt_List_Value Link_Param_Rpt_List_Value;
}__attribute__((__packed__))MIH_C_Link_Param_Rpt_List;

/*****************************************************
 *  MIH_C_Link_Register_Indication (SID=1 Op=3 AID=6)
*****************************************************/

typedef struct MIH_C_Link_Register_Indication{
	MIH_C_Header Header;
	MIH_C_Mihf_ID_Link MIHF_Source;
	MIH_C_Mihf_ID_Mihf MIHF_Destination;
	MIH_C_Link_Register_Information LinkRegister;
}__attribute__((__packed__))MIH_C_Link_Register_Indication;

/**************************************************
 *  Link_Up_Indication (SID=2 Op=3 AID=2)
**************************************************/

typedef struct MIH_C_Link_Up_Indication{
	MIH_C_Header Header;
	MIH_C_Mihf_ID_Link MIHF_Source;
	MIH_C_Mihf_ID_Mihf MIHF_Destination;
	MIH_C_Link_Tuple_Id_3GPP Link_Tuple_Id_3GPP;
	// MIH_C_Link_Address OldAccessRouter; // (optional)
	// MIH_C_Link_Address NewAccessRouter; // (optional)
	// MIH_IP_Renewal_Flag IPRenewalFlag;  // (optional)
	// MIH_IP_MOB_MGMT MobilityManagementSupport; // (optional)
}__attribute__((__packed__))MIH_C_Link_Up_Indication;

/************************************************
 *  Link_Down_Indication (SID=2 Op=3 AID=3)
*************************************************/
typedef struct MIH_C_Link_Down_Indication{
      MIH_C_Header Header;
      MIH_C_Mihf_ID_Link MIHF_Source;
      MIH_C_Mihf_ID_Mihf MIHF_Destination;
      MIH_C_Link_Tuple_Id_3GPP Link_Tuple_Id_3GPP;
      // MIH_C_Link_Address OldAccessRouter; // (optional)
      MIH_C_Link_Dn_Reason Reason_Code;
}__attribute__((__packed__))MIH_C_Link_Down_Indication;

/**************************************************
 *  Capability_Discover.request (SID=1 Op=1 AID=1)
*************************************************/

typedef struct MIH_C_Capability_Discover_Req{
      MIH_C_Header Header;
      MIH_C_Mihf_ID_Mihf MIHF_Source;
      MIH_C_Mihf_ID_Link MIHF_Destination;
}__attribute__((__packed__))MIH_C_Capability_Discover_Req;

/**************************************************
 *  Capability_Discover.confirm (SID=1 Op=0 AID=1)
*************************************************/
typedef struct MIH_C_Capability_Discover_Conf{
      MIH_C_Header Header;
      MIH_C_Mihf_ID_Link MIHF_Source;
      MIH_C_Mihf_ID_Mihf MIHF_Destination;
      MIH_C_Status Status;
      MIH_C_Link_Evt_List Link_Evt_List; // (optional - only if Status = Success)
      MIH_C_Link_Cmd_List Link_Cmd_List; // (optional - only if Status = Success)
}__attribute__((__packed__))MIH_C_Capability_Discover_Conf;

/**************************************************
 *  MIH_Event_Subscribe.request (SID=1 Op=1 AID=4)
*************************************************/
typedef struct MIH_C_Event_Subscribe_Req{
      MIH_C_Header Header;
      MIH_C_Mihf_ID_Mihf MIHF_Source;
      MIH_C_Mihf_ID_Link MIHF_Destination;
      MIH_C_Link_Evt_List Link_Evt_List;
}__attribute__((__packed__))MIH_C_Event_Subscribe_Req;

/**************************************************
 *  MIH_Event_Subscribe.confirm  (SID=1 Op=0 AID=4)
*************************************************/
typedef struct MIH_C_Event_Subscribe_Conf{
      MIH_C_Header Header;
      MIH_C_Mihf_ID_Link MIHF_Source;
      MIH_C_Mihf_ID_Mihf MIHF_Destination;
      MIH_C_Status Status;
      MIH_C_Link_Evt_List Link_Evt_List;
}__attribute__((__packed__))MIH_C_Event_Subscribe_Conf;

/*************************************************
*  MIH_Event_Unsubscribe.request (SID=1 Op=1 AID=5)
*************************************************/
typedef struct MIH_C_Event_Unsubscribe_Req{
      MIH_C_Header Header;
      MIH_C_Mihf_ID_Mihf MIHF_Source;
      MIH_C_Mihf_ID_Link MIHF_Destination;
      MIH_C_Link_Evt_List Requested_MIH_Evt_List;
}__attribute__((__packed__))MIH_C_Event_Unsubscribe_Req;

/*************************************************
*  Link Event Unsubscribe Confirm (SID=1 Op=0 AID=5)
*************************************************/
typedef struct MIH_C_Event_Unsubscribe_Conf{
      MIH_C_Header Header;
      MIH_C_Mihf_ID_Link MIHF_Source;
      MIH_C_Mihf_ID_Mihf MIHF_Destination;
      MIH_C_Status Status;
      MIH_C_Link_Evt_List Responce_MIH_Evt_List; // not included if Status = 0 (not successful)
}__attribute__((__packed__))MIH_C_Event_Unsubscribe_Conf;

/*************************************************
* Link Get Parameters Request (SID=3 Op=1 AID=1)
*************************************************/
typedef struct MIH_C_Get_Parameters_Req{
      MIH_C_Header Header;
      MIH_C_Mihf_ID_Mihf MIHF_Source;
      MIH_C_Mihf_ID_Link MIHF_Destination;
      MIH_C_Link_Param_Type_List Link_Param_Type_List;
      MIH_C_Link_States_Req Link_States_Req;
      MIH_C_Link_Desc_Req Link_Desc_Req;
}__attribute__((__packed__))MIH_C_Get_Parameters_Req;

/*************************************************
* Link Get Parameters Confirm (SID=3 Op=0 AID=1)
*************************************************/
typedef struct MIH_C_Get_Parameters_Confirm{
	MIH_C_Header Header;
    MIH_C_Mihf_ID_Link MIHF_Source;
    MIH_C_Mihf_ID_Mihf MIHF_Destination;
	MIH_C_Status Status;
	MIH_C_Link_Param_List Link_Param_List; // not included if Status = 0
    MIH_C_Link_States_Rsp_List Link_States_Rsp_List; // not included if Status = 0
    MIH_C_Link_Desc_Rsp_List Link_Desc_Rsp_List; // not included if Status = 0
}__attribute__((__packed__))MIH_C_Get_Parameters_Confirm;

/*************************************************
* Link Configure Threshold Request (SID=3 Op=1 AID=2)
*************************************************/
typedef struct MIH_C_Link_Configure_Thresholds_Req{
	MIH_C_Header Header;
	MIH_C_Mihf_ID_Mihf MIHF_Source;
	MIH_C_Mihf_ID_Link MIHF_Destination;
	MIH_C_Link_Cfg_Param_List Link_Cfg_Param_List;
}__attribute__((__packed__))MIH_C_Link_Configure_Thresholds_Req;

/*************************************************
* Link Configure Thresholds Confirm (SID=3 Op=0 AID=2)
*************************************************/
typedef struct MIH_C_Link_Configure_Thresholds_Confirm{
    MIH_C_Header Header;
    MIH_C_Mihf_ID_Link MIHF_Source;
    MIH_C_Mihf_ID_Mihf MIHF_Destination;
    MIH_C_Status Status;
	MIH_C_Link_Cfg_Status_List Link_Cfg_Status_List;
}__attribute__((__packed__))MIH_C_Link_Configure_Thresholds_Confirm;

/*************************************************
* Link Action Request (SID=3 Op=1 AID=3)
*************************************************/
typedef struct MIH_C_Link_Action_Request{
    MIH_C_Header Header;
    MIH_C_Mihf_ID_Mihf MIHF_Source;
    MIH_C_Mihf_ID_Link MIHF_Destination;
    MIH_C_Link_Action Link_Action;
    MIH_C_Execution_Delay Execution_Delay;
    // MIH_C_Link_Addr //Link_Addr (optional)
}__attribute__((__packed__))MIH_C_Link_Action_Request;

/*************************************************
* Link Action Confirm (SID=3 Op=0 AID=3)
*************************************************/
typedef struct MIH_C_Link_Action_Confirm{
    MIH_C_Header Header;
    MIH_C_Mihf_ID_Link MIHF_Source;
    MIH_C_Mihf_ID_Mihf MIHF_Destination;
    MIH_C_Status Status;
    MIH_C_Link_Ac_Result Link_Ac_Result;
}__attribute__((__packed__))MIH_C_Link_Action_Confirm;

typedef struct MIH_C_Link_Action_Confirm_Lsr{
    MIH_C_Header Header;
    MIH_C_Mihf_ID_Link MIHF_Source;
    MIH_C_Mihf_ID_Mihf MIHF_Destination;
    MIH_C_Status Status;
    MIH_C_Link_Action_Rsp_List Link_Action_Rsp_List;
    MIH_C_Link_Ac_Result Link_Ac_Result;
}__attribute__((__packed__))MIH_C_Link_Action_Confirm_Lsr;

/*************************************************
* Link Detected Indication (SID=2 Op=3 AID=1)
*************************************************/
typedef struct MIH_C_Link_Detected_Indication{
    MIH_C_Header Header;
    MIH_C_Mihf_ID_Link MIHF_Source;
    MIH_C_Mihf_ID_Mihf MIHF_Destination;
    MIH_C_Link_Det_Info Link_Det_Info;
}__attribute__((__packed__))MIH_C_Link_Detected_Indication;

/*************************************************
* Link Going Down Indication (SID=3 Op=0 AID=3)
*************************************************/
typedef struct MIH_C_Link_Going_Down_Indication{
    MIH_C_Header Header;
    MIH_C_Mihf_ID_Link MIHF_Source;
    MIH_C_Mihf_ID_Mihf MIHF_Destination;
    MIH_C_Link_Tuple_Id_3GPP Link_Tuple_Id_3GPP;
    MIH_C_Time_Interval Time_Interval;
    MIH_C_Link_Going_Down_Reason Link_Going_Down_Reason;
}__attribute__((__packed__))MIH_C_Link_Going_Down_Indication;

/*************************************************
* Link Going Down Indication (SID=3 Op=0 AID=3)
*************************************************/
typedef struct MIH_C_Link_Parameters_Report_Indication{
    MIH_C_Header Header;
    MIH_C_Mihf_ID_Link MIHF_Source;
    MIH_C_Mihf_ID_Mihf MIHF_Destination;
    MIH_C_Link_Tuple_Id_3GPP Link_Tuple_Id_3GPP;
    MIH_C_Link_Param_Rpt_List Link_Param_Rpt_List;
}__attribute__((__packed__))MIH_C_Link_Parameters_Report_Indication;
