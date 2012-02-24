//==============================================================================
// Brief   : ICMP Link SAP Main Entry Point
// Authors : Carlos Guimarães <cguimaraes@av.it.pt>
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
#include "link_sap.hpp"

#include <odtone/base.hpp>
#include <odtone/debug.hpp>
#include <odtone/mih/types/information.hpp>
#include <odtone/mih/types/capabilities.hpp>

#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>

#include <iostream>

namespace po = boost::program_options;

odtone::mih::octet_string	ifname;
odtone::mih::link_id		link_id;
odtone::mih::link_evt_list	capabilities_event_list;
odtone::mih::link_cmd_list	capabilities_command_list;

/**
 *
 */
void __trim(odtone::mih::octet_string &str, const char chr)
{
	str.erase(std::remove(str.begin(), str.end(), chr), str.end());
}

/**
 * Extract (from the configuration file) the type of techonology
 * supported by the Link SAP.
 *
 * @param tec Link SAP interface technology.
 */
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

/**
 * Type of techonology enumeration.
 */
enum StringValue { iMAC_ADDR,
	               i3GPP_2G_CELL_ID,
	               i3GPP_3G_CELL_ID,
	               i3GPP_ADDR,
	               i3GPP2_ADDR,
	               iOTHER };

/**
 * Extract (from the configuration file) the interface name and address
 * that it will manage.
 *
 * @param addr Link SAP interface.
 */
void set_supported_link_addr(odtone::mih::octet_string &addr)
{
	using namespace boost;

	char_separator<char> sep(" ");
	tokenizer< char_separator<char> > tokens(addr, sep);
	std::vector<odtone::mih::octet_string> it(tokens.begin(), tokens.end());

	std::map<std::string, StringValue> enum_map;

	enum_map["MAC_ADDR"]         = iMAC_ADDR;
	enum_map["3GPP_2G_CELL_ID"]  = i3GPP_2G_CELL_ID;
	enum_map["3GPP_3G_CELL_ID"]  = i3GPP_3G_CELL_ID;
	enum_map["3GPP_ADDR"]        = i3GPP_ADDR;
	enum_map["3GPP2_ADDR"]       = i3GPP2_ADDR;
	enum_map["OTHER"]            = iOTHER;

	if(it.size() >= 2) {
		// Parse interface name
		ifname = it[0];

		// Parse interface address
		odtone::mih::mac_addr mac;
		mac.address(it[1]);
		link_id.addr = mac;
	}
}

/**
 * Extract (from the configuration file) the list of supported
 * events.
 *
 * @param list Comma separated list of the Link SAP supported events.
 */
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

/**
 * Extract (from the configuration file) the list of supported
 * commands.
 *
 * @param list Comma separated list of the Link SAP supported commands.
 */
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

/**
 * Extract (from the configuration file) the information related to
 * the Link SAP.
 *
 * @param cfg Configuration information.
 */
void parse_interface_info(odtone::mih::config &cfg)
{
	odtone::mih::octet_string tec        = cfg.get<odtone::mih::octet_string>(odtone::sap::kConf_Tec);
	odtone::mih::octet_string inter_addr = cfg.get<odtone::mih::octet_string>(odtone::sap::kConf_Interface_Addr);

	set_supported_link_tec(tec);
	set_supported_link_addr(inter_addr);
}

/**
 * Extract (from the configuration file) the capabilities of the Link SAP.
 *
 * @param cfg Configuration information.
 */
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
		// declare Link SAP available options
		po::options_description desc("MIH Link SAP Configuration");
		desc.add_options()
			("help", "Display configuration options")
			(odtone::sap::kConf_File, po::value<std::string>()->default_value("link_sap.conf"), "Configuration file")
			(odtone::sap::kConf_Receive_Buffer_Len, po::value<odtone::uint>()->default_value(4096), "Receive buffer length")
			(odtone::sap::kConf_MIH_SAP_id, po::value<std::string>()->default_value("link"), "Link SAP ID")
			(odtone::sap::kConf_Port, po::value<odtone::ushort>()->default_value(1235), "Listening port")
			(odtone::sap::kConf_Tec, po::value<std::string>()->default_value(""), "Technology type")
			(odtone::sap::kConf_Interface_Addr, po::value<std::string>()->default_value(""), "Interface address")
			(odtone::sap::kConf_Evt_List, po::value<std::string>()->default_value(""), "List of supported events")
			(odtone::sap::kConf_Cmd_List, po::value<std::string>()->default_value(""), "List of supported commands")
			(odtone::sap::kConf_MIHF_Ip, po::value<std::string>()->default_value("127.0.0.1"), "Local MIHF IP")
			(odtone::sap::kConf_MIHF_Id, po::value<std::string>()->default_value("local-mihf"), "Local MIHF ID")
			(odtone::sap::kConf_MIHF_Local_Port, po::value<odtone::ushort>()->default_value(1025), "Local MIHF communications port");

		odtone::mih::config cfg(desc);
		cfg.parse(argc, argv, odtone::sap::kConf_File);

		if (cfg.help()) {
			std::cerr << desc << std::endl;
			return EXIT_SUCCESS;
		}

		parse_interface_info(cfg);
		parse_link_capabilities(cfg);

		boost::asio::io_service ios;
		link_sap::link_sap ls(cfg, ios, ifname, link_id, capabilities_event_list, capabilities_command_list);

		ios.run();

	} catch(std::exception& e) {
		std::cerr << "exception: " << e.what() << std::endl;

	} catch(const char* str) {
		std::cerr << "exception: " << str << std::endl;
	}
}

// EOF ////////////////////////////////////////////////////////////////////////
