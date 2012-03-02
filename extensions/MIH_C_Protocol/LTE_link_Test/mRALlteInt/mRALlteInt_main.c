/***************************************************************************
                          mRALteInt.c (main)  -  description
                             -------------------
    copyright            : (C) 2012 by Eurecom
    email                : davide.brizzolara@eurecom.fr, michelle.wetterwald@eurecom.fr
 ***************************************************************************
 mRALlte main
 ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/time.h>
#include <ctype.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "mRALlteInt_variables.h"
#include "mRALlteInt_log.h"
#include "mRALlteInt_proto.h"

#define NAS_UE_NETL_MAXLEN 500

// Global variables
int sock, sd_graal, s_nas;
struct sockaddr_in udp_socket, mihf_socket;
struct sockaddr_un ralu_socket;
int wait_start_mihf;
socklen_t sockaddr_len;
int listen_mih;

char message[NAS_UE_NETL_MAXLEN];

//-----------------------------------------------------------------------------
// Print the content of a buffer in hexadecimal
void mRALu_print_buffer(char * buffer,int length) {
//-----------------------------------------------------------------------------
   int i;
	 for (i=0;i<length;i++){
		 DEBUG ("-%hhx-",buffer[i]);
     if (i%8 == 7) DEBUG ("\n");
   }
	 DEBUG (",\t length %d\n\n", length);
}

//---------------------------------------------------------------------------
int mRALu_MTmihf_connect(void){
//---------------------------------------------------------------------------

	sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

	DEBUG ("\nTrying to connect to  UDP ...\n");

	udp_socket.sin_family = AF_INET;
	udp_socket.sin_port = htons(PORT_ODTONE);
	udp_socket.sin_addr.s_addr = inet_addr(SOCKET_ADDRESS);
	bzero(&(udp_socket.sin_zero),8);

	sockaddr_len = sizeof(struct sockaddr_in);

	return sock;
}

//---------------------------------------------------------------------------
int main(int argc, char *argv[]){
//---------------------------------------------------------------------------
	int rc, done, log_location;
	fd_set readfds;
	struct timeval tv;

    //added to manage log
	if (argc < 2){
      log_location = LOG_TO_DEFAULT;
    }else{
      if (strcmp(argv[1], "-h")==0){
        mRALu_log_usage();
        exit(0);
      }
      log_location = strtoul(argv[1], NULL, 0);
      if (log_location == LOG_TO_SYSTEM)
        log_location = LOG_TO_FILE;
      if ((log_location!= LOG_TO_CONSOLE)&&(log_location!= LOG_TO_FILE)){
        log_location = LOG_TO_DEFAULT;
      }
    }

    printf ("\n");
    mRALu_log_init(log_location);

    DEBUG ("mRALte: Initializing UDP socket\n");
    sd_graal = mRALu_MTmihf_connect();
    DEBUG ("mRALte: UDP socket initialized.\n\n");

    mRALte_send_link_register_indication();

    done=0;

    do{
		// Create fd_set and wait for input;
		FD_ZERO(&readfds);
		FD_SET(sd_graal, &readfds);
		tv.tv_sec = 0;
		tv.tv_usec = 100000;

		rc= select(FD_SETSIZE, &readfds, NULL, NULL, &tv);
		if(rc == -1){
			perror("select");
			done = 1;
		}

		//something received!
		if(rc >= 0){
			if(FD_ISSET(sd_graal, &readfds)){
				//DEBUG ("\n Something received sd_graal");
				done=process_mih_command();
			}
		}
    }while(!done);

    close(sock);
    close(sd_graal);
    mRALu_log_exit();
    return 0;
}
