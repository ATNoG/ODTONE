//=============================================================================
// Brief   : MIIS Server example with RDF support
// Authors : Simao Reis <sreis@av.it.pt>
//------------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2009-2013 Universidade Aveiro
// Copyright (C) 2009-2013 Instituto de Telecomunicações - Pólo Aveiro
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//==============================================================================

#include <odtone/base.hpp>
#include <odtone/debug.hpp>
#include <odtone/logger.hpp>
#include <odtone/mih/request.hpp>
#include <odtone/mih/response.hpp>
#include <odtone/mih/indication.hpp>
#include <odtone/mih/tlv_types.hpp>
#include <odtone/sap/user.hpp>

#include <iostream>

#include <boost/utility.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>

extern "C" {
	#include <redland.h>
}

///////////////////////////////////////////////////////////////////////////////
namespace po = boost::program_options;

using odtone::uint;
using odtone::ushort;

odtone::logger log_("information server", std::cout);

static const char* const kConf_Database = "database";
static const char* const kConf_MIH_Queries = "user.queries";

///////////////////////////////////////////////////////////////////////////////
void __trim(odtone::mih::octet_string &str, const char chr)
{
	str.erase(std::remove(str.begin(), str.end(), chr), str.end());
}

/**
 * Parse supported commands.
 *
 * @param cfg Configuration options.
 * @return A bitmap mapping the supported commands.
 */
boost::optional<odtone::mih::iq_type_list> parse_supported_queries(const odtone::mih::config &cfg)
{
	using namespace boost;

	odtone::mih::iq_type_list queries;
	bool has_iq = false;

	std::map<std::string, odtone::mih::iq_type_list_enum> enum_map;
	enum_map["iq_type_binary_data"]            = odtone::mih::iq_type_binary_data;
	enum_map["iq_type_rdf_data"]               = odtone::mih::iq_type_rdf_data;
	enum_map["iq_type_rdf_schema_url"]         = odtone::mih::iq_type_rdf_schema_url;
	enum_map["iq_type_rdf_schema"]             = odtone::mih::iq_type_rdf_schema;
	enum_map["iq_type_ie_network_type"]        = odtone::mih::iq_type_ie_network_type;
	enum_map["iq_type_ie_operator_id"]         = odtone::mih::iq_type_ie_operator_id;
	enum_map["iq_type_ie_service_provider_id"] = odtone::mih::iq_type_ie_service_provider_id;
	enum_map["iq_type_ie_country_code"]        = odtone::mih::iq_type_ie_country_code;
	enum_map["iq_type_ie_network_id"]          = odtone::mih::iq_type_ie_network_id;
	enum_map["iq_type_ie_network_aux_id"]      = odtone::mih::iq_type_ie_network_aux_id;
	enum_map["iq_type_ie_roaming_parteners"]   = odtone::mih::iq_type_ie_roaming_parteners;
	enum_map["iq_type_ie_cost"]                = odtone::mih::iq_type_ie_cost;
	enum_map["iq_type_ie_network_qos"]         = odtone::mih::iq_type_ie_network_qos;
	enum_map["iq_type_ie_network_data_rate"]   = odtone::mih::iq_type_ie_network_data_rate;
	enum_map["iq_type_ie_net_regult_domain"]   = odtone::mih::iq_type_ie_net_regult_domain;
	enum_map["iq_type_ie_net_frequency_bands"] = odtone::mih::iq_type_ie_net_frequency_bands;
	enum_map["iq_type_ie_net_ip_cfg_methods"]  = odtone::mih::iq_type_ie_net_ip_cfg_methods;
	enum_map["iq_type_ie_net_capabilities"]    = odtone::mih::iq_type_ie_net_capabilities;
	enum_map["iq_type_ie_net_supported_lcp"]   = odtone::mih::iq_type_ie_net_supported_lcp;
	enum_map["iq_type_ie_net_mob_mgmt_prot"]   = odtone::mih::iq_type_ie_net_mob_mgmt_prot;
	enum_map["iq_type_ie_net_emserv_proxy"]    = odtone::mih::iq_type_ie_net_emserv_proxy;
	enum_map["iq_type_ie_net_ims_proxy_cscf"]  = odtone::mih::iq_type_ie_net_ims_proxy_cscf;
	enum_map["iq_type_ie_net_mobile_network"]  = odtone::mih::iq_type_ie_net_mobile_network;
	enum_map["iq_type_ie_poa_link_addr"]       = odtone::mih::iq_type_ie_poa_link_addr;
	enum_map["iq_type_ie_poa_location"]        = odtone::mih::iq_type_ie_poa_location;
	enum_map["iq_type_ie_poa_channel_range"]   = odtone::mih::iq_type_ie_poa_channel_range;
	enum_map["iq_type_ie_poa_system_info"]     = odtone::mih::iq_type_ie_poa_system_info;
	enum_map["iq_type_ie_poa_subnet_info"]     = odtone::mih::iq_type_ie_poa_subnet_info;
	enum_map["iq_type_ie_poa_ip_addr "]        = odtone::mih::iq_type_ie_poa_ip_addr;

	std::string tmp = cfg.get<std::string>(kConf_MIH_Queries);
	__trim(tmp, ' ');

	char_separator<char> sep1(",");
	tokenizer< char_separator<char> > list_tokens(tmp, sep1);

	BOOST_FOREACH(std::string str, list_tokens) {
		if(enum_map.find(str) != enum_map.end()) {
			queries.set((odtone::mih::iq_type_list_enum) enum_map[str]);
			has_iq = true;
		}
	}

	boost::optional<odtone::mih::iq_type_list> supp_iq;
	if(has_iq)
		supp_iq = queries;

	return supp_iq;
}

///////////////////////////////////////////////////////////////////////////////
/**
 * This class provides an implementation of an MIIS RDF Server.
 */
class miis_rdf_server : boost::noncopyable {
public:
	/**
	 * Construct the MIIS RDF Server.
	 *
	 * @param cfg Configuration options.
	 * @param io The io_service object that MIIS RDF server will use to
	 * dispatch handlers for any asynchronous operations performed on the socket.
	 */
	miis_rdf_server(const odtone::mih::config& cfg, boost::asio::io_service& io);

	/**
	 * Destruct the MIIS RDF Server.
	 */
	~miis_rdf_server();

private:
	/**
	 * User registration handler.
	 *
	 * @param msg Received message.
	 * @param ec Error Code.
	 */
	void user_reg_handler(const odtone::mih::config& cfg, const boost::system::error_code& ec);

	/**
	 * Default MIH event handler.
	 *
	 * @param msg Received message.
	 * @param ec Error code.
	 */
	void event_handler(odtone::mih::message& msg, const boost::system::error_code& ec);

	/**
	 * Performs a query.
	 *
	 * @param qry The query to be performed.
	 * @param results Pointer to where to store the query results.
	 */
	void run_query(const unsigned char *qry, unsigned char *results);

	odtone::sap::user _mihf;	/**< User SAP helper.	*/

	librdf_world	*_world;			/**< Redland world class.	*/
	librdf_storage	*_storage;			/**< Redland storage class.	*/
	librdf_uri		*_uri;				/**< Redland URI class.		*/
	librdf_model	*_model;			/**< Redland model class.	*/
	std::string     _path_to_database;	/**< Path to the database.	*/
};

/**
 * Construct the MIIS RDF Server.
 *
 * @param cfg Configuration options.
 * @param io The io_service object that MIIS RDF server will use to
 * dispatch handlers for any asynchronous operations performed on the socket.
 */
miis_rdf_server::miis_rdf_server(const odtone::mih::config& cfg, boost::asio::io_service& io)
	: _mihf(cfg, io, boost::bind(&miis_rdf_server::event_handler, this, _1, _2)),
	  _path_to_database(cfg.get<std::string>(kConf_Database))
{
	_world = librdf_new_world();
	librdf_world_open(_world);

	_uri = librdf_new_uri(_world, (const unsigned char*)"odtone");
	if (!_uri) {
		log_(0, "Failed to create URI");
		throw("Failed to create URI");
	}

	// open previously populated sqlite database
	_storage = librdf_new_storage(_world, "sqlite", _path_to_database.c_str(), NULL);
	if (!_storage) {
		log_(0, "Failed to create new storage");
		throw("Failed to create new storage");
	}

	_model = librdf_new_model(_world, _storage, NULL);
	if (!_model) {
		log_(0, "Failed to create model");
		throw("Failed to create model");
	}

	// Register with the MIHF
	odtone::mih::message m;
	boost::optional<odtone::mih::iq_type_list> supp_iq = parse_supported_queries(cfg);

	m << odtone::mih::indication(odtone::mih::indication::user_register)
	    & odtone::mih::tlv_query_type_list(supp_iq);
	m.destination(odtone::mih::id("local-mihf"));

	_mihf.async_send(m, boost::bind(&miis_rdf_server::user_reg_handler, this, boost::cref(cfg), _2));
}

/**
 * Destruct the MIIS RDF Server.
 */
miis_rdf_server::~miis_rdf_server()
{
}

/**
 * User registration handler.
 *
 * @param msg Received message.
 * @param ec Error Code.
 */
void miis_rdf_server::user_reg_handler(const odtone::mih::config& cfg, const boost::system::error_code& ec)
{
	log_(0, "MIH-User register result: ", ec.message());
}

static void recv_handler(odtone::mih::message &m, boost::system::error_code e)
{
}

/**
 * Default MIH event handler.
 *
 * @param msg Received message.
 * @param ec Error code.
 */
void miis_rdf_server::event_handler(odtone::mih::message& msg, const boost::system::error_code& ec)
{
	if (ec) {
		log_(0, __FUNCTION__, " error: ", ec.message());
		return;
	}

	odtone::mih::iq_rdf_data_list query_list;

	unsigned char *query_str;
	unsigned char *result_str;
	size_t i;

	odtone::mih::message response;
	odtone::mih::ir_rdf_data rsp;
	odtone::mih::ir_rdf_data_list rsp_list;

	switch (msg.mid()) {
	case odtone::mih::indication::get_information:
		log_(0, "MIIS RDF Server received a MIH_Get_Information.indication ");

		msg >> odtone::mih::indication(odtone::mih::indication::get_information)
			& odtone::mih::tlv_info_query_rdf_data_list(query_list);

		log_(0, "List of queries received:");

		for(i = 0; i < query_list.size(); i++) {
			log_(0, "\n", query_list[0]._data, "\n");

			// run query
			query_str = (unsigned char *) query_list[0]._data.c_str();
			run_query(query_str, result_str);

			// add to ir_rdf_data_list
			rsp._data.assign((char *) result_str);
			rsp_list.push_back(rsp);
		}

		// send response
		response << odtone::mih::response(odtone::mih::response::get_information)
			& odtone::mih::tlv_status(odtone::mih::status_success)
			& odtone::mih::tlv_info_resp_rdf_data_list(rsp_list);

		response.tid(msg.tid());
		response.destination(msg.source());

		_mihf.async_send(response, boost::bind(recv_handler, _1, _2));

		break;
	default:
		log_(0, "MIIS RDF Server received message with unsupported MIH opcode: ", msg.mid());
		break;
	}
}

/**
 * Performs a query.
 *
 * @param qry The query to be performed.
 * @param results Pointer to where to store the query results.
 */
void miis_rdf_server::run_query(const unsigned char *qry, unsigned char *results)
{
	librdf_query *query;

	if ((query = librdf_new_query(_world, "sparql", _uri, qry, _uri)) == NULL) {
		log_(0, "Error creating query.\n");

		results = NULL;
		return;
	}

	librdf_query_results *r;

	if ((r = librdf_query_execute(query, _model)) == NULL) {
		log_(0, "Error executing query.\n");

		results = NULL;
		return;
	}

	// print results to screen
	if (librdf_query_results_to_file_handle(r, stdout, NULL, NULL) != 0) {
		fprintf(stderr, "Error writing results to stdout \n");
	}

	results = librdf_query_results_to_string(r, NULL, NULL);
}

int main(int argc, char** argv)
{
	odtone::setup_crash_handler();

	try {
		boost::asio::io_service ios;

		// declare MIH Usr available options
		po::options_description desc(odtone::mih::octet_string("MIH Usr Configuration"));

		desc.add_options()
			("help", "Display configuration options")
			(odtone::sap::kConf_File, po::value<std::string>()->default_value("miis_rdf_server.conf"), "Configuration file")
			(odtone::sap::kConf_Port, po::value<ushort>()->default_value(1236), "Listening port")
			(odtone::sap::kConf_Receive_Buffer_Len, po::value<uint>()->default_value(4096), "Receive Buffer Length")
			(odtone::sap::kConf_MIH_SAP_id, po::value<std::string>()->default_value("miis"), "MIIS Server ID")
			(kConf_MIH_Queries, po::value<std::string>()->default_value(""), "MIIS Server supported queries")
			(odtone::sap::kConf_MIHF_Ip, po::value<std::string>()->default_value("127.0.0.1"), "Local MIHF IP address")
			(odtone::sap::kConf_MIHF_Local_Port, po::value<ushort>()->default_value(1025), "Local MIHF communication port")
			(kConf_Database, po::value<std::string>()->default_value("database"), "/path/to MIIS server sqlite database ");

		odtone::mih::config cfg(desc);
		cfg.parse(argc, argv, odtone::sap::kConf_File);

		if (cfg.help()) {
			std::cerr << desc << std::endl;
			return EXIT_SUCCESS;
		}

		miis_rdf_server server(cfg, ios);

		ios.run();

	} catch(std::exception& e) {
		log_(0, "exception: ", e.what());
	}
}

// EOF ////////////////////////////////////////////////////////////////////////
