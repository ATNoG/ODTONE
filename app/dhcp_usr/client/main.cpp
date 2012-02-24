//==============================================================================
// Brief   : Main
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

#include "log.hpp"
#include "dhcp_usr.hpp"

#include <iostream>

#include <boost/program_options.hpp>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>

namespace po = boost::program_options;

static const char* const kConf_MIH_NIC = "user.nic";
static const char* const kConf_Ip_Version = "user.ip_version";

using namespace odtone;

void parse_nic(std::string &list, std::map<std::string, std::string> &nic)
{
	using namespace boost;

	char_separator<char> sep1(",");
	char_separator<char> sep2(" ");
	tokenizer< char_separator<char> > list_tokens(list, sep1);

	BOOST_FOREACH(std::string str, list_tokens) {
		tokenizer< char_separator<char> > tokens(str, sep2);
		tokenizer< char_separator<char> >::iterator it = tokens.begin();

		std::string id = *it;
		++it;
		std::string value = *it;

		nic[id] = value;
	}
}

int main(int argc, char** argv)
{
	odtone::setup_crash_handler();

	try {
		boost::asio::io_service io;

		// declare MIH User available options
		po::options_description desc(std::string("DHCP-User Configuration"));
		desc.add_options()
			("help", "Display configuration options")
			(sap::kConf_File, po::value<std::string>()->default_value("dhcp_usr.conf"), "Configuration File")
			(sap::kConf_MIH_SAP_id, po::value<std::string>()->default_value("DHCP"), "MIH User ID")
			(sap::kConf_Port, po::value<odtone::ushort>()->default_value(1234), "Listening Port")
			(sap::kConf_Receive_Buffer_Len, po::value<odtone::uint>()->default_value(4096), "Receive Buffer Length")
			(kConf_Ip_Version, po::value<odtone::ushort>()->default_value(4), "IP Protocol Version (4/6)")
			(kConf_MIH_NIC, po::value<std::string>()->default_value(""), "Interface Info List")
			(sap::kConf_MIHF_Ip, po::value<std::string>()->default_value("127.0.0.1"), "MIHF Local Communications IP Address")
			(sap::kConf_MIHF_Local_Port, po::value<odtone::ushort>()->default_value(1025), "MIHF Local Communications Port");


		// parse configurations
		odtone::mih::config cfg(desc);
		cfg.parse(argc, argv, odtone::sap::kConf_File);

		if (cfg.help()) {
			std::cerr << desc << std::endl;
			return EXIT_SUCCESS;
		}

		// parse known NIC list
		std::map<std::string, std::string> nic;
		std::string nic_list = cfg.get<std::string>(kConf_MIH_NIC);
		parse_nic(nic_list, nic);

		// create MIH-User interface
		dhcp_user usr(io, cfg, nic, cfg.get<odtone::ushort>(kConf_Ip_Version));

		// run
		io.run();

	} catch(std::exception& e) {
		ODTONE_LOG(0, "exception: ", e.what());
	}
}
