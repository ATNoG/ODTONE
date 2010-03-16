//
// Copyright (c) 2007-2009 2009 Universidade Aveiro - Instituto de
// Telecomunicacoes Polo Aveiro
// This file is part of ODTONE - Open Dot Twenty One.
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//
// Author:     Simao Reis <sreis@av.it.pt>
//

///////////////////////////////////////////////////////////////////////////////
#include "transmit.hpp"
#include "mihfid.hpp"
#include "log.hpp"
#include "transaction_ack_service.hpp"
#include "transaction_manager.hpp"
#include "service_access_controller.hpp"

#include <odtone/debug.hpp>
#include <odtone/mih/config.hpp>

#include <iostream>

#include <boost/program_options.hpp>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>
///////////////////////////////////////////////////////////////////////////////

using namespace odtone;
using namespace odtone::mihf;

namespace po = boost::program_options;

// TODO: pass a reference to the necessary objects
boost::asio::io_service io_service;

// TODO
mih::event_list		capabilities_event_list;
mih::net_type_addr_list capabilities_list_net_type_addr;

// available config options
static const char* const kConf_File               = "conf.file";
static const char* const kConf_Receive_Buffer_Len = "conf.recv_buff_len";

static const char* const kConf_MIHF_Id           = "mihf.id";
static const char* const kConf_MIHF_Ip           = "mihf.ip";
static const char* const kConf_MIHF_Peer_List    = "mihf.peers";
static const char* const kConf_MIHF_Users_List   = "mihf.users";
static const char* const kConf_MIHF_Links_List   = "mihf.links";
static const char* const kConf_MIHF_Remote_Port  = "mihf.remote_port";
static const char* const kConf_MIHF_Local_Port   = "mihf.local_port";
static const char* const kConf_MIHF_Evt_List     = "mihf.event_list";
static const char* const kConf_MIHF_Network_Type = "mihf.link_addr_list";


//
// The following code is to extract from the config file
// the capabilities for the mihf and store them in the service
// management object.
//
// The next version will query the underlying link sap for it's
// capabilities.

void __trim(mih::octet_string &str, const char chr)
{
	str.erase(std::remove(str.begin(), str.end(), chr), str.end());
}

//
// @param evts is a comma separated string whith the list of supported
// events
//
void set_supported_event_list(mih::octet_string &list)
{
	__trim(list, ' ');
	using namespace boost;

	char_separator<char> sep(",");
	tokenizer< char_separator<char> > tokens(list, sep);

	std::map<std::string, uint16> enum_map;

	enum_map["link_detected"]	   = (uint16) mih::link_detected;
	enum_map["link_up"]		   = (uint16) mih::link_up;
	enum_map["link_down"]		   = (uint16) mih::link_down;
	enum_map["link_parameters_report"] = (uint16) mih::link_parameters_report;
	enum_map["link_going_down"]	   = (uint16) mih::link_going_down;
	enum_map["link_handover_imminent"] = (uint16) mih::link_handover_imminent;
	enum_map["link_handover_complete"] = (uint16) mih::link_handover_complete;

	BOOST_FOREACH(mih::octet_string event, tokens) {
		log(0, "evt: ", event);
		if(enum_map.find(event) != enum_map.end())
			capabilities_event_list.set((mih::event_list_enum) enum_map[event]);
	}
}


//
// list is a comma separated string with the network types
//
// example: ethernet 00:11:22:33:44:55, 802_11 55:66:77:88:99:00
//
//
void set_supported_link_list(mih::octet_string &list)
{
	using namespace boost;

	std::map<std::string, mih::link_type_enum> enum_map;

	enum_map["ethernet"] = mih::link_type_ethernet;
	enum_map["802_11"]   = mih::link_type_802_11;

	char_separator<char> sep1(",");
	char_separator<char> sep2(" ");
	tokenizer< char_separator<char> > list_tokens(list, sep1);

	BOOST_FOREACH(mih::octet_string str, list_tokens) {
		tokenizer< char_separator<char> > tokens(str, sep2);
		tokenizer< char_separator<char> >::iterator it = tokens.begin();

		mih::octet_string link_type = *it;
		++it;
		mih::octet_string link_addr = *it;
		log(0, "lt: ", link_type, " la: ", link_addr);
		mih::net_type_addr nta;

		if(enum_map.find(link_type) != enum_map.end()) {
			mih::mac_addr mac;
			mac.address(link_addr);

			nta.addr = mac;
			nta.nettype.link = mih::link_type(enum_map[link_type]);

			capabilities_list_net_type_addr.push_back(nta);
		}
	}
}

//
// list is a comma separated list of mihf id ip and port
//
// example: mihf2 192.168.0.1 4551
//
void set_list_peer_mihfs(mih::octet_string &list)
{
	using namespace boost;

	char_separator<char> sep1(",");
	char_separator<char> sep2(" ");
	tokenizer< char_separator<char> > list_tokens(list, sep1);

	BOOST_FOREACH(mih::octet_string str, list_tokens)
	{
		tokenizer< char_separator<char> > tokens(str, sep2);
		tokenizer< char_separator<char> >::iterator it = tokens.begin();

		mih::octet_string id = *it;
		++it;
		mih::octet_string ip = *it;
		++it;
		mih::octet_string port = *it;

		uint16 port_;
		std::istringstream iss(port);
		if ((iss >> port_).fail())
			throw "invalid port";

		// transmit.add(id, ip, port_);
	}
}

void set_users_links(mih::octet_string &list)
{
	using namespace boost;

	char_separator<char> sep1(",");
	char_separator<char> sep2(" ");
	tokenizer< char_separator<char> > list_tokens(list, sep1);

	BOOST_FOREACH(mih::octet_string str, list_tokens)
	{
		tokenizer< char_separator<char> > tokens(str, sep2);
		tokenizer< char_separator<char> >::iterator it = tokens.begin();

		mih::octet_string id = *it;
		++it;
		mih::octet_string port = *it;

		uint16 port_;
		std::istringstream iss(port);
		if ((iss >> port_).fail())
			throw "invalid port";

		// transmit.add(id, "127.0.0.1", port_);
	}
}

void init_services(mih::config &cfg)
{
	mih::octet_string	id	= cfg.get<mih::octet_string>(kConf_MIHF_Id);
	mih::octet_string	mihf_ip	= cfg.get<mih::octet_string>(kConf_MIHF_Ip);
	mih::octet_string	events	= cfg.get<mih::octet_string>(kConf_MIHF_Evt_List);
	mih::octet_string	links	= cfg.get<mih::octet_string>(kConf_MIHF_Network_Type);
	mih::octet_string	mihfs	= cfg.get<mih::octet_string>(kConf_MIHF_Peer_List);
	mih::octet_string	users	= cfg.get<mih::octet_string>(kConf_MIHF_Users_List);
	mih::octet_string	lsaps	= cfg.get<mih::octet_string>(kConf_MIHF_Links_List);

	uint16	remote_port = cfg.get<uint16>(kConf_MIHF_Remote_Port);
	uint16	local_port  = cfg.get<uint16>(kConf_MIHF_Local_Port);

	mihfid_t::instance()->assign(id.c_str());
	log.level(3);

	set_supported_event_list(events);
	set_supported_link_list(links);
	set_list_peer_mihfs(mihfs);
	set_users_links(users);
	set_users_links(lsaps);

	log(0, events);
	log(0, links);
	log(0, users);
	log(0, lsaps);

	/// initiate listening services
	// comhand->init("127.0.0.1", local_port, 1);
	// netsap->init(mihf_ip.c_str(), remote_port, 1);

}

int main(int argc, char **argv)
{
	odtone::setup_crash_handler();

	// declare MIHF supported options
	po::options_description desc("MIHF Configuration Options");

	desc.add_options()
		("help", "Display configuration options")
		(kConf_File, po::value<std::string>()->default_value("odtone.conf"), "Configuration File")
		(kConf_Receive_Buffer_Len, po::value<uint16>()->default_value(4096), "Receive Buffer Length")
		(kConf_MIHF_Id, po::value<std::string>()->default_value("mihf"), "MIHF Id")
		(kConf_MIHF_Ip, po::value<std::string>()->default_value("127.0.0.1"), "MIHF Ip")
		(kConf_MIHF_Peer_List, po::value<std::string>()->default_value(""), "List of peer MIHFs")
		(kConf_MIHF_Users_List, po::value<std::string>()->default_value("user 1234"), "List of User SAPs")
		(kConf_MIHF_Links_List, po::value<std::string>()->default_value("link 1235"), "List of Links SAPs")
		(kConf_MIHF_Remote_Port, po::value<uint16>()->default_value(4551), "MIHF Remote Communications Port")
		(kConf_MIHF_Local_Port, po::value<uint16>()->default_value(1025), "MIHF Local Communications Port")
		(kConf_MIHF_Evt_List, po::value<std::string>()->default_value(""), "MIHF List of supported events")
		(kConf_MIHF_Network_Type, po::value<std::string>()->default_value(""), "MIHF Network Type list");

	odtone::mih::config cfg(desc);
	cfg.parse(argc, argv, kConf_File);

	if (cfg.help()) {
		std::cerr << desc << std::endl;
		return EXIT_SUCCESS;
	}

	init_services(cfg);

	// start
	io_service.run();

	return EXIT_SUCCESS;
}
