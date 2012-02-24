//==============================================================================
// Brief   : Configuration Module
// Authors : Bruno Santos <bsantos@av.it.pt>
//           Simao Reis   <sreis@av.it.pt>
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

#include <odtone/mih/config.hpp>
#include <boost/program_options/parsers.hpp>
#include <fstream>

#ifdef BOOST_MSVC
#	pragma warning(push)
#	pragma warning(disable : 4800)
#endif

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
/**
 * Construct a configuration and command line options parser.
 *
 * @param desc A set of option descriptions.
 */
config::config(po::options_description &desc)
	: _desc(desc)
{
}

/**
 * Destruct a configuration and command line options parser.
 */
config::~config()
{
}

/**
 * Check if the help option was specified.
 *
 * @return True if the help option is present or false otherwise.
 */
bool config::help()
{
	return _vars.count("help");
}


/**
 * Parse the command line arguments.
 *
 * @param argc Number of arguments passed through the command line.
 * @param argv Arguments passed through the command line.
 * @param conf_file_option Name of configuration file.
 */
bool config::parse(int argc, char* argv[], const char* conf_file_option)
{
	po::store(po::parse_command_line(argc, argv, _desc), _vars);

	std::string file = get<std::string>(conf_file_option);

	std::ifstream ifs(file.c_str());

	if (ifs)
		po::store(po::parse_config_file(ifs, _desc), _vars);

	po::notify(_vars);

	return ifs.is_open();
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /* namespace odtone */

#ifdef BOOST_MSVC
#	pragma warning(pop)
#endif

// EOF ////////////////////////////////////////////////////////////////////////
