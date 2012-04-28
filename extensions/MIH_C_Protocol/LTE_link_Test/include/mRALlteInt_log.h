/***************************************************************************
                          mRALteInt_log.h  -  description
                             -------------------
    copyright            : (C) 2012 by Eurecom
    email                : davide.brizzolara@eurecom.com, michelle.wetterwald@eurecom.fr
 ***************************************************************************
 mRALlte Debug and Error Logging
 ***************************************************************************/
#ifndef __mRALlte_LOG_H__
#define __mRALlte_LOG_H__

//
#define LOG_CONST 0

#define LOG_TO_CONSOLE 0
#define LOG_TO_FILE    1
#define LOG_TO_SYSTEM  2
//default value
#define LOG_TO_DEFAULT LOG_TO_CONSOLE

#define RAL_LTE_LOG_DEBUG  4
#define RAL_LTE_LOG_ERROR  8

#define LTE_LOGFILE_NAME "/tmp/log_MT_RALlte.txt"
#define LTE_SYSLOG_NAME "MT_RALlte"
#define LTE_MT_RAL_VERSION "D0.1"  //Release date :  see readme

#define DEBUG(args...) mRALu_log_record( (RAL_LTE_LOG_DEBUG), ##args)

#define ERROR(args...) mRALu_log_record( (RAL_LTE_LOG_ERROR), ##args)

int mRALu_log_usage(void);
int mRALu_log_init(unsigned int level);
int mRALu_log_record(unsigned int level, char * log_msg, ...);
int mRALu_log_exit(void);

#endif
