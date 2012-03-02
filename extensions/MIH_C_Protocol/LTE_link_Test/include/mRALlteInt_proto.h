/***************************************************************************
                          mRALlteInt_proto.h  -  description
                             -------------------
    copyright            : (C) 2012 by Eurecom
    email                : davide.brizzolara@eurecom.fr, michelle.wetterwald@eurecom.fr
 ***************************************************************************
 mRALlteInt prototypes
 ***************************************************************************/
#ifndef __mRALlte_PROTO_H__
#define __mRALlte_PROTO_H__

void mRALu_print_buffer(char * buffer,int length);
void print_header(char* str);
void print_mihf_id(char* str);
void print_link_id_3GPP(char* str);
void print_link_tuple_id_3GPP(char* str);
void print_status(char* str);
void print_link_evt_list(char* str);
void print_link_cmd_list(char* str);
void print_link_cfg_param(char* str);
void print_link_cfg_status(char* str);
void load_3gpp_address(char* str);

int send_to_mih(char * str, int prim_length);
int process_mih_command(void);

void mRALte_decode_link_get_parameters_request(char* str);
void mRALte_decode_link_capability_discover_request(char* str);
void mRALte_decode_link_configure_threshold_request(char* str);
void mRALte_decode_event_subscribe_request(char * str);
void mRALte_decode_link_action_request(char * str);
void mRALte_decode_event_unsubscribe_request(char * str);

int mRALte_send_link_register_indication(void);
int mRALte_send_link_up_indication(void);
int mRALte_send_link_down_indication(void);
int mRALte_send_capability_discover_confirm(void);
int mRALte_send_event_subscribe_confirm(void);
int mRALte_send_event_unsubscribe_confirm(void);
int mRALte_send_link_get_parameters_confirm(void);
int mRALte_send_link_configure_thresholds_confirm(void);
int mRALte_send_link_action_confirm(void);
int mRALte_send_link_action_confirm_lsr(void);
int mRALte_send_link_detected_indication(void);
int mRALte_send_link_going_down_indication(void);

#endif

