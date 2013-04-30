//=============================================================================
// Brief   : Ethtool interface for fetching data rate.
// Authors : André Prata <andreprata@av.it.pt>
//-----------------------------------------------------------------------------
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

#include "ethtool.hpp"

#include <net/if.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <linux/sockios.h>
#include <linux/ethtool.h>
#include <stdexcept>

namespace odtone {

unsigned int get_interface_speed(const std::string &ifname)
{
	int sock;
	::ifreq ifr;
	::ethtool_cmd edata;
	int rc;

	sock = ::socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
	if (sock < 0) {
		throw std::runtime_error("Error opening ethtool socket");
	}

	rc = ifname.copy(ifr.ifr_name, IFNAMSIZ, 0);
	ifr.ifr_name[rc] = '\0';

	edata.cmd = ETHTOOL_GSET;
	ifr.ifr_data = reinterpret_cast<char *>(&edata);

	rc = ::ioctl(sock, SIOCETHTOOL, &ifr);
	if (rc < 0) {
		throw std::runtime_error("Error performing ethtool request");
	}

	return edata.speed;
}

}; // namespace odtone

// EOF ////////////////////////////////////////////////////////////////////////
