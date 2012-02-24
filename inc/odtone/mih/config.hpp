//=============================================================================
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


#ifndef ODTONE_MIH_CONFIG__HPP_
#define ODTONE_MIH_CONFIG__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

namespace po = boost::program_options;


///////////////////////////////////////////////////////////////////////////////
/**
 * Configuration and command line options parser
 *
 * This class provides parsing for command line options and configuration
 * files for a set of predefined options description.
 */
class config {
public:
	/**
	 * Construct a configuration and command line options parser.
	 *
	 * @param desc A set of option descriptions.
	 */
	config(po::options_description &desc);

	/**
	 * Destruct a configuration and command line options parser.
	 */
	~config();

	/**
	 * Check if the help option was specified.
	 *
	 * @return True if the help option is present or false otherwise.
	 */
	bool help();

	/**
	 * Parse the command line arguments.
	 *
	 * @param argc Number of arguments passed through the command line.
	 * @param argv Arguments passed through the command line.
	 * @param conf_file_option Name of configuration file.
	 */
	bool parse(int argc, char* argv[], const char* conf_file_option);


	/**
	 * Get option variable value.
	 *
	 * @param var The variable name.
	 */
	template<class T>
	T get(const char* var) const
	{
		return _vars[var].as<T>();
	}

	/**
	 * Count the number of option variables.
	 *
	 * @param var Number of variables.
	 */
	uint count(const char *var)
	{
		return _vars.count(var);
	}

private:
	po::options_description _desc;	/**< Option description.			*/
	po::variables_map       _vars;	/**< Configuration parameters map.	*/
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_CONFIG__HPP_ */
