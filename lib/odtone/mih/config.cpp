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

#ifdef BOOST_MSVC
#	pragma warning(push)
#	pragma warning(disable : 4800)
#endif

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
config::config(po::options_description &desc)
	: _desc(desc)
{
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
 * \brief Parse the command line
 */
void config::parse(int argc, char* argv[], const char* conf_file_option)
{
	po::store(po::parse_command_line(argc, argv, _desc), _vars);

	std::string file = get<std::string>(conf_file_option);
	std::ifstream ifs(file.c_str());

	if (ifs)
		po::store(po::parse_config_file(ifs, _desc), _vars);

	po::notify(_vars);
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /* namespace odtone */

#ifdef BOOST_MSVC
#	pragma warning(pop)
#endif

// EOF ////////////////////////////////////////////////////////////////////////
