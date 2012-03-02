/***************************************************************************
                          mRALteInt_log.c  -  description
                             -------------------
    copyright            : (C) 2012 by Eurecom
    email                : davide.brizzolara@eurecom.com, michelle.wetterwald@eurecom.fr
 ***************************************************************************
 Dummy MT_RALte Debug and Error Logging
 ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#include <stdarg.h>
#include <syslog.h>

#include "mRALlteInt_log.h"

FILE *mRALu_file;
int log_output;

//-----------------------------------------------------------------------------
// Initialize logging system
int mRALu_log_usage(void) {
//-----------------------------------------------------------------------------
  printf(" >. In function mRALlteInt_log_usage \n\n");
  printf("MT_RALlteInt : \n\n");
  printf(" >./MT_RALlteInt LOG_location LOG_level \n\n");
  printf(" LOG_location can take the following values\n");
  printf(" 0 : Log to screen\n");
  printf(" 1 : Log to file (default is /tmp/log_MT_LTE.txt)\n");
  printf(" 2 : Log to system (syslog) -- FFS\n");
  printf(" \n");
  printf(" If no value is entered , default value as log to file is assumed.\n\n");
  printf(" LOG_level can take the following values\n");
  printf(" 0 : DEBUG + ERROR\n");
  printf(" 1 : ERROR only\n");
  return 0;
}

//-----------------------------------------------------------------------------
// Initialize logging system
int mRALu_log_init(unsigned int l_output) {
//-----------------------------------------------------------------------------
  log_output = l_output;
  switch (log_output){
    case LOG_TO_CONSOLE:
      printf("***** MT_RAL_LTE V%s logging \n\n",LTE_MT_RAL_VERSION);
      break;
    case LOG_TO_FILE:
      mRALu_file = fopen(LTE_LOGFILE_NAME,"w"); //start over new file
      //mRALu_file = fopen(LTE_LOGFILE_NAME,"a"); //start over former file
      if (mRALu_file == NULL){
        perror ("mRALu_log_init - error opening file");
        exit(1);
      }
      fprintf(mRALu_file, "***** MT_RAL_LTE V%s logging \n\n",LTE_MT_RAL_VERSION);
      fflush(mRALu_file);
      break;
    case LOG_TO_SYSTEM:
      openlog(LTE_SYSLOG_NAME,0, LOG_DAEMON);
      syslog(RAL_LTE_LOG_DEBUG,  "***** V%s starting logging \n\n",LTE_MT_RAL_VERSION);
      break;
    default:
      printf("mRALu_log_init: l_output error %d", log_output);
  }

  return 0;
}

//-----------------------------------------------------------------------------
// Log messages according to user settings
int mRALu_log_record(unsigned int level, char * log_msg, ...) {
//-----------------------------------------------------------------------------
  va_list log_ap;

  switch (log_output){
    case LOG_TO_CONSOLE:
      va_start(log_ap, log_msg);
      vprintf(log_msg, log_ap);
      va_end(log_ap);
      break;
    case LOG_TO_FILE:
      va_start(log_ap, log_msg);
      vfprintf(mRALu_file,log_msg, log_ap);
      va_end(log_ap);
      fflush(mRALu_file);
      break;
    case LOG_TO_SYSTEM:
      // FFS
      break;
    default:
      printf("mRALu_log_record: level error %d", level);
  }


  return 0;
}

//-----------------------------------------------------------------------------
// Close logging system
int mRALu_log_exit(void) {
//-----------------------------------------------------------------------------
  switch (log_output){
    case LOG_TO_CONSOLE:
      printf("***** MT_RAL_LTE stopping \n\n");
      break;
    case LOG_TO_FILE:
      fprintf(mRALu_file, "***** MT_RAL_LTE stopping \n\n");
      fflush(mRALu_file);
      fclose(mRALu_file);
      break;
    case LOG_TO_SYSTEM:
      syslog(RAL_LTE_LOG_DEBUG,  "***** stopping logging \n\n");
      closelog();
      break;
    default:
      printf("mRALu_log_exit: log_output error %d", log_output);
  }

  return 0;
}


