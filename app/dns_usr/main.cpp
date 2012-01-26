//=============================================================================
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
#include "dns_usr.hpp"

#include <iostream>
#include <boost/program_options.hpp>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>

namespace po = boost::program_options;

static const char* const kConf_Domain = "user.domain";
static const char* const kConf_Additional = "user.additional_rr";

using namespace odtone;

int main(int argc, char** argv)
{
	odtone::setup_crash_handler();

	try {
		boost::asio::io_service ios;

		// declare MIH User available options
		po::options_description desc(odtone::mih::octet_string("DNS-User Configuration"));
		desc.add_options()
			("help", "Display configuration options")
			(sap::kConf_File, po::value<std::string>()->default_value("dns.conf"), "Configuration File")
			(sap::kConf_MIH_SAP_id, po::value<std::string>()->default_value("DNS"), "MIH User ID")
			(sap::kConf_Port, po::value<odtone::ushort>()->default_value(1234), "Listening Port")
			(sap::kConf_Receive_Buffer_Len, po::value<odtone::uint>()->default_value(4096), "Receive Buffer Length")
			(sap::kConf_MIHF_Ip, po::value<std::string>()->default_value("127.0.0.1"), "MIHF Local Communications IP Address")
			(sap::kConf_MIHF_Local_Port, po::value<odtone::ushort>()->default_value(1025), "MIHF Local Communications Port")
			(kConf_Domain, po::value<std::string>()->default_value(""), "Domain name")
			(kConf_Additional, po::value<bool>()->default_value(true), "Use additional resource records")
		;

		// parse configurations
		odtone::mih::config cfg(desc);
		cfg.parse(argc, argv, odtone::sap::kConf_File);
		if (cfg.help()) {
			std::cerr << desc << std::endl;
			return EXIT_SUCCESS;
		}
		std::string domain = cfg.get<std::string>(kConf_Domain);
		bool additional = cfg.get<bool>(kConf_Additional);

		// create DNS-User interface
		dns_user usr(ios, cfg, domain, additional);

		// run
		ios.run();

	} catch(std::exception& e) {
		ODTONE_LOG(0, "exception: ", e.what());
	}
}
