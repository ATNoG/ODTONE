//=============================================================================
// Brief   : Link SAP Linux Main Entry Point
// Authors : Bruno Santos <bsantos@av.it.pt>
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

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/mih/types/information.hpp>
#include <odtone/mih/types/capabilities.hpp>
#include "../link_sap.hpp"
#include "../interface/if_802_11.hpp"
#include <odtone/debug.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>
#include "rtnetlink.hpp"
#include <iostream>

namespace po = boost::program_options;

odtone::mih::link_id       link_id;
odtone::mih::link_evt_list capabilities_event_list;
odtone::mih::link_cmd_list capabilities_command_list;

void __trim(odtone::mih::octet_string &str, const char chr)
{
	str.erase(std::remove(str.begin(), str.end(), chr), str.end());
}

//
// The following code is to extract from the config file the type of technology
// supported by the Link SAP and interface address that it manages
//
//
void set_supported_link_tec(odtone::mih::octet_string &tec)
{
	__trim(tec, ' ');
	using namespace boost;

	// Extract technology
	std::map<std::string, odtone::mih::link_type_enum> enum_map;

	enum_map["GSM"]           = odtone::mih::link_type_gsm;
	enum_map["GPRS"]          = odtone::mih::link_type_gprs;
	enum_map["EDGE"]          = odtone::mih::link_type_edge;
	enum_map["802.3"]         = odtone::mih::link_type_ethernet;
	enum_map["Other"]         = odtone::mih::link_type_wireless_other;
	enum_map["802_11"]        = odtone::mih::link_type_802_11;
	enum_map["CDMA2000"]      = odtone::mih::link_type_cdma2000;
	enum_map["UMTS"]          = odtone::mih::link_type_umts;
	enum_map["CDMA2000-HRPD"] = odtone::mih::link_type_cdma2000_hrpd;
	enum_map["802_16"]        = odtone::mih::link_type_802_16;
	enum_map["802_20"]        = odtone::mih::link_type_802_20;
	enum_map["802_22"]        = odtone::mih::link_type_802_22;

	if(enum_map.find(tec) != enum_map.end())
		link_id.type = odtone::mih::link_type(enum_map[tec]);
}

//
// The following code is to extract from the config file the type of technology
// supported by the Link SAP and interface address that it manages
//
//
enum StringValue { iMAC_ADDR,
	               i3GPP_2G_CELL_ID,
	               i3GPP_3G_CELL_ID,
	               i3GPP_ADDR,
	               i3GPP2_ADDR,
	               iOTHER };

void set_supported_link_addr(odtone::mih::octet_string &addr)
{
	__trim(addr, ' ');
	using namespace boost;

	char_separator<char> sep(",");
	tokenizer< char_separator<char> > tokens(addr, sep);

	std::map<std::string, StringValue> enum_map;

	enum_map["MAC_ADDR"]         = iMAC_ADDR;
	enum_map["3GPP_2G_CELL_ID"]  = i3GPP_2G_CELL_ID;
	enum_map["3GPP_3G_CELL_ID"]  = i3GPP_3G_CELL_ID;
	enum_map["3GPP_ADDR"]        = i3GPP_ADDR;
	enum_map["3GPP2_ADDR"]       = i3GPP2_ADDR;
	enum_map["OTHER"]            = iOTHER;

	odtone::mih::mac_addr      mac1;
	mac1.address(addr);
	link_id.addr = mac1;
}

//
// evts is a comma separated string whith the list of supported
// events
//
void set_supported_event_list(odtone::mih::octet_string &list)
{
	__trim(list, ' ');
	using namespace boost;

	char_separator<char> sep(",");
	tokenizer< char_separator<char> > tokens(list, sep);

	std::map<std::string, odtone::uint16> enum_map;

	enum_map["link_detected"]	         = (odtone::uint16) odtone::mih::evt_link_detected;
	enum_map["link_up"]		             = (odtone::uint16) odtone::mih::evt_link_up;
	enum_map["link_down"]		         = (odtone::uint16) odtone::mih::evt_link_down;
	enum_map["link_parameters_report"]   = (odtone::uint16) odtone::mih::evt_link_parameters_report;
	enum_map["link_going_down"]	         = (odtone::uint16) odtone::mih::evt_link_going_down;
	enum_map["link_handover_imminent"]   = (odtone::uint16) odtone::mih::evt_link_handover_imminent;
	enum_map["link_handover_complete"]   = (odtone::uint16) odtone::mih::evt_link_handover_complete;
	enum_map["link_pdu_transmit_status"] = (odtone::uint16) odtone::mih::evt_link_pdu_transmit_status;

	BOOST_FOREACH(odtone::mih::octet_string event, tokens) {
		if(enum_map.find(event) != enum_map.end())
			capabilities_event_list.set((odtone::mih::link_evt_list_enum) enum_map[event]);
	}
}

//
// command is a comma separated string whith the list of supported
// commands
//
void set_supported_command_list(odtone::mih::octet_string &list)
{
	__trim(list, ' ');
	using namespace boost;

	char_separator<char> sep(",");
	tokenizer< char_separator<char> > tokens(list, sep);

	std::map<std::string, odtone::uint16> enum_map;

	enum_map["link_subscribe"]            = (odtone::uint16) odtone::mih::cmd_link_event_subscribe;
	enum_map["link_unsubscribe"]          = (odtone::uint16) odtone::mih::cmd_link_event_unsubscribe;
	enum_map["link_get_parameters"]       = (odtone::uint16) odtone::mih::cmd_link_get_parameters;
	enum_map["link_configure_thresholds"] = (odtone::uint16) odtone::mih::cmd_link_configure_thresholds;
	enum_map["link_action"]               = (odtone::uint16) odtone::mih::cmd_link_action;

	BOOST_FOREACH(odtone::mih::octet_string command, tokens) {
		if(enum_map.find(command) != enum_map.end())
			capabilities_command_list.set((odtone::mih::link_cmd_list_enum) enum_map[command]);
	}
}

//
// The following code is to extract from the config file the type of techonology
// supported by the Link SAP and the address of each interface
//
void parse_interface_info(odtone::mih::config &cfg)
{
	odtone::mih::octet_string tec        = cfg.get<odtone::mih::octet_string>(odtone::sap::kConf_Tec);
	odtone::mih::octet_string inter_addr = cfg.get<odtone::mih::octet_string>(odtone::sap::kConf_Interface_Addr);

	set_supported_link_tec(tec);
	set_supported_link_addr(inter_addr);
}

void parse_link_capabilities(odtone::mih::config &cfg)
{
	odtone::mih::octet_string events = cfg.get<odtone::mih::octet_string>(odtone::sap::kConf_Evt_List);
	odtone::mih::octet_string commands = cfg.get<odtone::mih::octet_string>(odtone::sap::kConf_Cmd_List);

	set_supported_event_list(events);
	set_supported_command_list(commands);
}


///////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
	odtone::setup_crash_handler();

	try {
		// declare MIH Usr available options
		po::options_description desc("MIH Link SAP Configuration");
		desc.add_options()
			("help", "Display configuration options")
			(odtone::sap::kConf_File, po::value<std::string>()->default_value("link_sap.conf"), "Configuration file")
			(odtone::sap::kConf_Receive_Buffer_Len, po::value<uint>()->default_value(4096), "Receive buffer length")
			(odtone::sap::kConf_MIH_SAP_id, po::value<std::string>()->default_value("link"), "Link SAP ID")
			(odtone::sap::kConf_Port, po::value<ushort>()->default_value(1235), "Listening port")
			(odtone::sap::kConf_Tec, po::value<std::string>()->default_value(""), "Technology type")
			(odtone::sap::kConf_Interface_Addr, po::value<std::string>()->default_value(""), "Interface address")
			(odtone::sap::kConf_Evt_List, po::value<std::string>()->default_value(""), "List of supported events")
			(odtone::sap::kConf_Cmd_List, po::value<std::string>()->default_value(""), "List of supported commands")
			(odtone::sap::kConf_MIHF_Id, po::value<std::string>()->default_value("local-mihf"), "Local MIHF ID")		
			(odtone::sap::kConf_MIHF_Ip, po::value<std::string>()->default_value("127.0.0.1"), "Local MIHF IP")						
			(odtone::sap::kConf_MIHF_Local_Port, po::value<ushort>()->default_value(1025), "Local MIHF communication port")
		;

		odtone::mih::config cfg(desc);
		cfg.parse(argc, argv, odtone::sap::kConf_File);

		if (cfg.help()) {
			std::cerr << desc << std::endl;
			return EXIT_SUCCESS;
		}

		parse_interface_info(cfg);
		parse_link_capabilities(cfg);

		boost::asio::io_service ios;
		link_sap::link_sap ls(cfg, ios);
		boost::thread io(boost::bind(&boost::asio::io_service::run, &ios));

		rtnetlink nl(rtnetlink::link        |
					 rtnetlink::notify      |
					 rtnetlink::tc          |
					 rtnetlink::ipv4_ifaddr |
					 rtnetlink::ipv6_ifaddr |
					 rtnetlink::ipv6_ifinfo |
					 rtnetlink::ipv6_prefix);
		rtnetlink::message msg;

		for (;;) {
			nl.recv(msg);

			do {
				std::cout << "\ngot msg: " << msg.type() << std::endl;

				if (rtnetlink::if_link::is(msg)) {
					rtnetlink::if_link lnk(msg);
					link_sap::nic::interface* it = nullptr;

					std::cout << "if_type: " << lnk.type() << std::endl;
					std::cout << "if_index: " << lnk.index() << std::endl << std::hex;
					std::cout << "if_flags: " << lnk.flags() << std::endl << std::dec;

					if (lnk.has_address())
						std::cout << "if_address: " << lnk.address() << std::endl;
					if (lnk.has_bcast_addr())
						std::cout << "if_broadcast: " << lnk.bcast_addr() << std::endl;
					if (lnk.has_name())
						std::cout << "if_name: " << lnk.name() << std::endl;
					if (lnk.has_mtu())
						std::cout << "if_mtu: " << lnk.mtu() << std::endl;
					if (lnk.has_lnk_type())
						std::cout << "if_link_type: " << lnk.link_type() << std::endl;
					if (lnk.has_qdisc())
						std::cout << "if_qdisc: " << lnk.qdisc() << std::endl;


					it = new link_sap::nic::if_802_11(link_sap::nic::if_id(lnk.index()));

					if (lnk.flags() & rtnetlink::if_link::up)
						it->up(true);
					else
						it->up(false);
					it->name(lnk.name());
					it->link_addr(odtone::mih::mac_addr(lnk.address().get(), lnk.address().size()));

					ios.dispatch(boost::bind(&link_sap::link_sap::update, &ls, it));

				} else if (rtnetlink::if_addr::is(msg)) {
					rtnetlink::if_addr addr(msg);

					std::cout << "ifa_family: " << uint(addr.family()) << std::endl;
					std::cout << "ifa_prefixlen: " << uint(addr.prefixlen()) << std::endl;
					std::cout << "ifa_scope: " << uint(addr.scope()) << std::endl << std::hex;
					std::cout << "ifa_flags: " << uint(addr.flags()) << std::endl << std::dec;
					std::cout << "ifa_index: " << addr.index() << std::endl;

					if (addr.has_address())
						std::cout << "ifa_address: " << addr.address() << std::endl;
					if (addr.has_local())
						std::cout << "ifa_local: " << addr.local() << std::endl;
					if (addr.has_label())
						std::cout << "ifa_label: " << addr.label() << std::endl;
					if (addr.has_broadcast())
						std::cout << "ifa_broadcast: " << addr.broadcast() << std::endl;
					if (addr.has_anycast())
						std::cout << "ifa_anycast: " << addr.anycast() << std::endl;
				}

			} while (msg.next());
		}

	} catch(std::exception& e) {
		std::cerr << "exception: " << e.what() << std::endl;

	} catch(const char* str) {
		std::cerr << "exception: " << str << std::endl;
	}
}

// EOF ////////////////////////////////////////////////////////////////////////
