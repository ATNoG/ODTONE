//==============================================================================
// Brief   : DHCP Client Interface
// Authors : Carlos Guimaraes <cguimaraes@av.it.pt>
//------------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2009-2012 Universidade Aveiro
// Copyright (C) 2009-2012 Instituto de Telecomunicações - Pólo Aveiro
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//==============================================================================

#include <string.h>
#include "callback.h"

#ifndef DHCLIENT_H
#define DHCLIENT_H

#ifdef __cplusplus
extern "C" {

namespace odtone {

struct mih_options {
	struct mih_options *next;
	char *id;
	char *ip;
	int port;
	int service;
};

typedef void (*dhcp_callback_t)(void* ctx, struct mih_options*);
#endif
	int init(const char* if_list[], int len, int version, dhcp_callback_t callback, void* callback_ctx);
	int init_session(const char* ifname);
	int terminate_session(const char* ifname);
	int request_info(const char* ifname);
#ifdef __cplusplus
}
}
#endif

#endif /* DHCLIENT_H */

