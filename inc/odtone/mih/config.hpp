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
#include <boost/program_options.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

namespace po = boost::program_options;

///////////////////////////////////////////////////////////////////////////////
static const char* const kConf_Port               = "conf.port";
static const char* const kConf_Receive_Buffer_Len = "conf.recv_buff_len";

static const char* const kConf_MIHF_DB_Path      = "mihf.DBName";
static const char* const kConf_MIHF_Peer_List    = "mihf.peers";
static const char* const kConf_MIHF_Users_List   = "mihf.users";
static const char* const kConf_MIHF_Links_List   = "mihf.links";
static const char* const kConf_MIHF_Ip           = "mihf.ip";
static const char* const kConf_MIHF_Id           = "mihf.id";
static const char* const kConf_MIHF_Remote_Port  = "mihf.remote_port";
static const char* const kConf_MIHF_Local_Port   = "mihf.local_port";
static const char* const kConf_MIHF_Evt_List     = "mihf.event_list";
static const char* const kConf_MIHF_Network_Type = "mihf.link_addr_list";

static const char* const kConf_MIH_SAP_id   = "user.id";
static const char* const kConf_MIH_SAP_dest = "dest";

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
	config();
	config(const char* file);
	config(int argc, char* argv[]);
	config(int argc, char* argv[], const char* file);
	~config();

	bool help();
	bool parse(const char* file);
	void parse(int argc, char* argv[]);

	/**
	 * \brief Get option variable value
	 * \param var variable name
	 */
	template<class T>
	T get(const char* var) const { return _vars[var].as<T>(); }

private:
	void init();

private:
	po::options_description _desc;
	po::variables_map       _vars;
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_CONFIG__HPP_ */
