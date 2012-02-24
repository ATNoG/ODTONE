//==============================================================================
// Brief   : DHCP Callback Auxiliar
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

#ifndef CALLBACK_H
#define CALLBACK_H

struct mih_options {
	struct mih_options *next;
	char *id;
	char *ip;
	int port;
	int service;
};

typedef void (*dhcp_callback_t)(void* ctx, struct mih_options*);

#endif /* CALLBACK_H */
