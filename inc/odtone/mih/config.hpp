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
 * \brief Configuration and command line options parser
 *
 * This class provides parsing for command line options and configuration
 * files for a set of predefined options description. It's used for configuring
 * the odtone::sap IO services and the odtone MIHF implementation.
 */
class config {
public:
	config(po::options_description &desc);
	~config();

	bool help();
	void parse(int argc, char* argv[], const char* conf_file_option);


	/**
	 * \brief Get option variable value
	 * \param var variable name
	 */
	template<class T>
	T get(const char* var) const { return _vars[var].as<T>(); }

private:
	po::options_description _desc;
	po::variables_map       _vars;
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_CONFIG__HPP_ */
