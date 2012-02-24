//==============================================================================
// Brief   : DHCP Control
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

#include "dhcp_control.hpp"
#include "log.hpp"
extern "C" {
	#include "dhclient.h"
}

#include <odtone/mih/types/address.hpp>
#include <odtone/mih/types/odtone.hpp>

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/foreach.hpp>
#include <boost/thread/thread.hpp>
#include <boost/make_shared.hpp>

namespace odtone {


/**
 * dhclient callback adapter.
 *
 * @param ctx The callback context.
 * @param mo The IEEE 802.21 DHCP options results.
 */
static void callback_adapter(void* ctx, mih_options *mo) {
	dhcp_control *dc = reinterpret_cast<dhcp_control*>(ctx);
	dc->callback(mo);
}

///////////////////////////////////////////////////////////////////////////////
/**
 * Construct the DHCP Control.
 *
 * @param version The DHCP version to use.
 * @param nic Mapping of the local network interfaces.
 * @param app_callback The DHCP-User callback.
 */
dhcp_control::dhcp_control(ushort version,
						   std::map<std::string, std::string> nic,
						   dhcp_results_t app_callback)
	: _app_callback(app_callback)
{
	_version = version;

	// Initialize DHCP Control interface
	int if_list_len = 0;
	const char** if_list = (const char**)malloc(sizeof(char*) * nic.size());

	std::pair<std::string, std::string> it;
	BOOST_FOREACH(it, nic) {
		if_list[if_list_len] = it.second.c_str();
		++if_list_len;
	}

	// Run this on a new thread due to the blocking dispatch instruction
	init(if_list, if_list_len, version, callback_adapter, this);
}

/**
 * Destruct the DHCP Control.
 */
dhcp_control::~dhcp_control()
{
}

/**
 * Initiates a new DHCP session.
 *
 * @param interface The network interface name identifier associated
 * to the new session.
 */
void dhcp_control::new_session(std::string interface)
{
	boost::shared_ptr<boost::thread> a = boost::make_shared<boost::thread>(boost::bind(&init_session, interface.c_str()));
}

/**
 * Terminates an active DHCP session.
 *
 * @param interface The network interface name identifier associated
 * to the session to terminate.
 */
void dhcp_control::shutdown_session(std::string interface)
{
	terminate_session(interface.c_str());
}

/**
 * Requests configuration settings (but not addresses).
 *
 * @param interface The network interface name identifier associated
 * to the session to request.
 */
void dhcp_control::request(std::string interface)
{
	boost::shared_ptr<boost::thread> a = boost::make_shared<boost::thread>(boost::bind(&request_info, interface.c_str()));
}

/**
 * Callback to process the MIH DHCP Options results .
 *
 * @param options A linked-list storing the MIH DHCP Options results.
 */
void dhcp_control::callback(struct mih_options *options)
{
	mih::mos_dscv pos_list;

	if(options == NULL)
		return;

	struct mih_options *tmp;
	tmp = (struct mih_options*)malloc(sizeof(struct mih_options));
	tmp = options;

	do {
		mih::mos_info pos;

		pos.id.assign(tmp->id);
		std::string ip_str;
		ip_str.assign(tmp->ip);
		if(ip_str.size() != 0) {
			boost::asio::ip::address ip = boost::asio::ip::address::from_string(ip_str);
			if(ip.is_v4()) {
				mih::ip_addr ip_addr(mih::ip_addr::ipv4, ip_str);
				pos.ip = ip_addr;
			} else if(ip.is_v6()) {
				mih::ip_addr ip_addr(mih::ip_addr::ipv6, ip_str);
				pos.ip = ip_addr;
			}
		}
		pos.port = tmp->port;

		switch(tmp->service) {
			case 1: {
				pos_list.is.push_back(pos);
			} break;
			case 2: {
				pos_list.cs.push_back(pos);
			} break;
			case 3: {
				pos_list.es.push_back(pos);
			} break;
		}
		tmp = tmp->next;
	} while(tmp != NULL);

	_app_callback(pos_list);
}

} /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
