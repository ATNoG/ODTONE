//=============================================================================
// Brief   : Configuration Module
// Authors : Bruno Santos <bsantos@av.it.pt>
//           Simao Reis   <sreis@av.it.pt>
//
//
// Copyright (C) 2009 Universidade Aveiro - Instituto de Telecomunicacoes Polo Aveiro
//
// This file is part of ODTONE - Open Dot Twenty One.
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//=============================================================================

#include <odtone/mih/config.hpp>
#include <fstream>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
config::config()
	: _desc("Configuration")
{
	init();
}

/**
 * \brief Construct and parse the file
 */
config::config(const char* filename)
	: _desc("Configuration")
{
	init();
	parse(filename);
}

/**
 * \brief Construct and parse the command line
 */
config::config(int argc, char* argv[])
	: _desc("Configuration")
{
	init();
	parse(argc, argv);
}

/**
 * \brief Construct and parse the file and then the command line
 */
config::config(int argc, char* argv[], const char* file)
	: _desc("Configuration")
{
	init();
	parse(file);
	parse(argc, argv);
}

config::~config()
{
}

/**
 * \brief Check if the \a help option was specified
 *
 * \returns \b true if the \a help option is present
 *          \b false otherwise
 */
bool config::help()
{
	return _vars.count("help");
}

/**
 * \brief Parse the configuration file
 *
 * \returns \b true if the file was parsed, \b false otherwise (failed to open
 * the file)
 */
bool config::parse(const char* file)
{
	std::ifstream ifs(file);

	if (!ifs)
		return false;

	po::store(po::parse_config_file(ifs, _desc), _vars);
	po::notify(_vars);
	return true;
}

/**
 * \brief Parse the command line
 */
void config::parse(int argc, char* argv[])
{
	po::store(po::parse_command_line(argc, argv, _desc), _vars);
	po::notify(_vars);
}

void config::init()
{
	_desc.add_options()
		(
		 "help",
		 "Display configuration options"
		 )
		(
		 kConf_Port,
		 po::value<ushort>()->default_value(1234),
		 "Port"
		 )
		(
		 kConf_Receive_Buffer_Len,
		 po::value<uint>()->default_value(4096),
		 "Receive Buffer Length"
		 )
		(
		 kConf_MIHF_DB_Path,
		 po::value<std::string>()->default_value("odtone.db"),
		 "MIHF Database Path"
		 )
		(
		 kConf_MIHF_Ip,
		 po::value<std::string>()->default_value("0.0.0.0"),
		 "MIHF IP Address"
		 )
		(
		 kConf_MIHF_Id,
		 po::value<std::string>()->default_value("mihf"),
		 "MIHF Id"
		 )
		(
		 kConf_MIHF_Peer_List,
		 po::value<std::string>()->default_value(""),
		 "List of peer MIHFs"
		 )
		(
		 kConf_MIHF_Users_List,
		 po::value<std::string>()->default_value("user 1234"),
		 "List of User SAPs"
		 )
		(
		 kConf_MIHF_Links_List,
		 po::value<std::string>()->default_value("link 1235"),
		 "List of Links SAPs"
		 )
		(
		 kConf_MIHF_Remote_Port,
		 po::value<ushort>()->default_value(4551),
		 "MIHF Remote Communications Port"
		 )
		(
		 kConf_MIHF_Local_Port,
		 po::value<ushort>()->default_value(1025),
		 "MIHF Local Communications Port"
		 )
		(
		 kConf_MIHF_Evt_List,
		 po::value<std::string>()->default_value(""),
		 "MIHF List of supported events"
		 )
		(
		 kConf_MIHF_Network_Type,
		 po::value<std::string>()->default_value(""),
		 "MIHF Network Type list"
		 )
		(
		 kConf_MIH_SAP_id,
		 po::value<std::string>()->default_value("user"),
		 "User Id"
		 )
		(
		 kConf_MIH_SAP_dest,
		 po::value<std::string>()->default_value(""),
		 "Destination of MIH messages of MIH SAP User"
		 );
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
