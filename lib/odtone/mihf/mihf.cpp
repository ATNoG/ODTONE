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

#include <odtone/mihf/mihf.hpp>
#include <boost/asio.hpp>
#include <odtone/mihf/mihfid.hpp>
#include <odtone/mihf/transmit.hpp>
#include <odtone/mih/types/link.hpp>

#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>

namespace odtone { namespace mihf {

mihf::mihf()
{
}

mih::event_list			capabilities_event_list;
mih::net_type_addr_list capabilities_list_net_type_addr;

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

	enum_map["link_detected"]		   = (uint16) mih::link_detected;
	enum_map["link_up"]				   = (uint16) mih::link_up;
	enum_map["link_down"]			   = (uint16) mih::link_down;
	enum_map["link_parameters_report"] = (uint16) mih::link_parameters_report;
	enum_map["link_going_down"]		   = (uint16) mih::link_going_down;
	enum_map["link_handover_imminent"] = (uint16) mih::link_handover_imminent;
	enum_map["link_handover_complete"] = (uint16) mih::link_handover_complete;

	BOOST_FOREACH(mih::octet_string event, tokens)
		{
			if(enum_map.find(event) != enum_map.end())
				{
					capabilities_event_list.set((mih::event_list_enum) enum_map[event]);
				}
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
	enum_map["802_11"]	 = mih::link_type_802_11;

	char_separator<char> sep1(",");
	char_separator<char> sep2(" ");
	tokenizer< char_separator<char> > list_tokens(list, sep1);

	BOOST_FOREACH(mih::octet_string str, list_tokens)
		{
			tokenizer< char_separator<char> > tokens(str, sep2);
			tokenizer< char_separator<char> >::iterator it = tokens.begin();

			mih::octet_string link_type = *it;
			++it;
			mih::octet_string link_addr = *it;

			mih::net_type_addr nta;

			if(enum_map.find(link_type) != enum_map.end())
				{
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

			transmit.add(id, ip, port_);
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

			transmit.add(id, "127.0.0.1", port_);
		}
}

void mihf::init(const mih::config &cfg)
{
	mih::octet_string	id		= cfg.get<mih::octet_string>(mih::kConf_MIHF_Id);
	mih::octet_string	mihf_ip	= cfg.get<mih::octet_string>(mih::kConf_MIHF_Ip);
	mih::octet_string	events	= cfg.get<mih::octet_string>(mih::kConf_MIHF_Evt_List);
	mih::octet_string   links	= cfg.get<mih::octet_string>(mih::kConf_MIHF_Network_Type);
	mih::octet_string   mihfs	= cfg.get<mih::octet_string>(mih::kConf_MIHF_Peer_List);
	mih::octet_string   users	= cfg.get<mih::octet_string>(mih::kConf_MIHF_Users_List);
	mih::octet_string   lsaps   = cfg.get<mih::octet_string>(mih::kConf_MIHF_Links_List);
	uint16 remote_port = cfg.get<uint16>(mih::kConf_MIHF_Remote_Port);
	uint16 local_port  = cfg.get<uint16>(mih::kConf_MIHF_Local_Port);

	mihfid_t::instance()->assign(id.c_str());
	log.level(3);

	set_supported_event_list(events);
	set_supported_link_list(links);
	set_list_peer_mihfs(mihfs);
	set_users_links(users);
	set_users_links(lsaps);

	/// initiate listening services
	comhand->init("127.0.0.1", local_port, 1);
	netsap->init(mihf_ip.c_str(), remote_port, 1);
}

void mihf::run()
{
	io_service.run();
}

} /* namespace mihf */  } /* namespace odtone */
