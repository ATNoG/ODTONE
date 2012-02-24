//==============================================================================
// Brief   : Link SAP Win32 Main Entry Point
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
#include "../link_sap.hpp"
#include "../interface/if_802_11.hpp"
#include <odtone/debug.hpp>
#include <odtone/mih/types/information.hpp>
#include <odtone/mih/types/capabilities.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>
#include <iostream>
#include "win32.hpp"
#include <ws2tcpip.h>
#include <Iphlpapi.h>
#include <Wlanapi.h>
#pragma comment(lib, "iphlpapi.lib")

///////////////////////////////////////////////////////////////////////////////
using link_sap::nic::interface;
using link_sap::nic::if_802_11;
using link_sap::nic::if_id;
using link_sap::ushort;
using link_sap::uint;

void wlan_event_handler(const WLAN_NOTIFICATION_DATA& nd, boost::asio::io_service& ios, link_sap::link_sap* ls)
{
	std::cout << "wlan notification[" << nd.NotificationCode << "]\n";

	if (nd.NotificationSource != WLAN_NOTIFICATION_SOURCE_ACM)
		return;

	switch (nd.NotificationCode) {
	case wlan_notification_acm_connection_complete: {
			WLAN_CONNECTION_NOTIFICATION_DATA* cnd = reinterpret_cast<WLAN_CONNECTION_NOTIFICATION_DATA*>(nd.pData);

			if (cnd->wlanReasonCode == WLAN_REASON_CODE_SUCCESS) {
				interface* it = new if_802_11(if_id(&nd.InterfaceGuid));
				it->up(true);
				
				MIB_IF_ROW2 it_info = link_sap::win32::get_interface_info(nd.InterfaceGuid);
				it->link_addr(odtone::mih::mac_addr(it_info.PhysicalAddress, 
				                                    it_info.PhysicalAddressLength));

				ios.dispatch(boost::bind(&link_sap::link_sap::update, ls, it));
			}
		}
		break;

	case wlan_notification_acm_disconnected: {
			interface* it = new if_802_11(if_id(&nd.InterfaceGuid));
			it->up(false);
			
			MIB_IF_ROW2 it_info = link_sap::win32::get_interface_info(nd.InterfaceGuid);
			it->link_addr(odtone::mih::mac_addr(it_info.PhysicalAddress, 
			                                    it_info.PhysicalAddressLength));

			ios.dispatch(boost::bind(&link_sap::link_sap::update, ls, it));
		}
	}
}

namespace po = boost::program_options;

odtone::mih::link_id link_id;
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

int main(int argc, char** argv)
{
	odtone::setup_crash_handler();

	try {
		po::options_description desc("MIH Link SAP Configuration");
		desc.add_options()
			("help", "Display configuration options")
			(odtone::sap::kConf_Port, po::value<ushort>()->default_value(1235), "Port")
			(odtone::sap::kConf_Tec, po::value<std::string>()->default_value(""), "Link SAP Technology")
			(odtone::sap::kConf_Interface_Addr, po::value<std::string>()->default_value(""), "Link SAP Interface Address")
			(odtone::sap::kConf_Evt_List, po::value<std::string>()->default_value(""), "List of supported events")
			(odtone::sap::kConf_Cmd_List, po::value<std::string>()->default_value(""), "List of supported commands")

			(odtone::sap::kConf_File, po::value<std::string>()->default_value("link_sap.conf"), "Configuration File")
			(odtone::sap::kConf_Receive_Buffer_Len, po::value<uint>()->default_value(4096), "Receive Buffer Length")
			(odtone::sap::kConf_MIHF_Ip, po::value<std::string>()->default_value("127.0.0.1"), "Local MIHF Ip")
			(odtone::sap::kConf_MIHF_Local_Port, po::value<ushort>()->default_value(1025), "MIHF Local Communications Port")
			(odtone::sap::kConf_MIHF_Id, po::value<std::string>()->default_value("local-mihf"), "Local MIHF Id")
			(odtone::sap::kConf_MIH_SAP_id, po::value<std::string>()->default_value("link"), "Link SAP Id");

		odtone::mih::config cfg(desc);
		cfg.parse(argc, argv, odtone::sap::kConf_File);

		if (cfg.help()) {
			std::cerr << desc << std::endl;
			return EXIT_SUCCESS;
		}

		parse_interface_info(cfg);
		parse_link_capabilities(cfg);

		std::cout << "cfg:"
		             " port=" << cfg.get<ushort>(odtone::sap::kConf_Port)
		          << " mihf.ip=" << cfg.get<std::string>(odtone::sap::kConf_MIHF_Ip)
		          << " mihf.local_port=" << cfg.get<ushort>(odtone::sap::kConf_MIHF_Local_Port)
		          << std::endl;

		boost::asio::io_service ios;
		link_sap::link_sap ls(cfg, ios);

		link_sap::win32::handle lan = link_sap::win32::wlan_open();
		link_sap::win32::wlan_if_list iflst = link_sap::win32::wlan_enum_interfaces(lan);

		for (uint i = 0; i < iflst->dwNumberOfItems; ++i) {
			interface* it;

			it = new if_802_11(if_id(&iflst->InterfaceInfo[i].InterfaceGuid));
			it->name(iflst->InterfaceInfo[i].strInterfaceDescription);
			
			MIB_IF_ROW2 it_info = link_sap::win32::get_interface_info(iflst->InterfaceInfo[i].InterfaceGuid);
			it->link_addr(odtone::mih::mac_addr(it_info.PhysicalAddress, 
			                                    it_info.PhysicalAddressLength));
						
			ios.dispatch(boost::bind(&link_sap::link_sap::update, &ls, it));
		}

		link_sap::win32::wlan_register_notification(lan, boost::bind(&wlan_event_handler, _1, boost::ref(ios), &ls));

		ios.run();

	} catch(std::exception& e) {
		std::cerr << "error: " << e.what() << std::endl;
	}
}

// EOF ////////////////////////////////////////////////////////////////////////
