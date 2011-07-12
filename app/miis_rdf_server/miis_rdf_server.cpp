//=============================================================================
// Brief   : MIIS Server Example with RDF Support
// Authors : Simao Reis <sreis@av.it.pt>
//------------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2009-2011 Universidade Aveiro
// Copyright (C) 2009-2011 Instituto de Telecomunicações - Pólo Aveiro
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
#include <boost/utility.hpp>
#include <boost/bind.hpp>
#include <iostream>

extern "C" {
#include <redland.h>
}

///////////////////////////////////////////////////////////////////////////////

namespace po = boost::program_options;

using odtone::uint;
using odtone::ushort;

odtone::logger log_("information server", std::cout);

static const char* const kConf_Databse               = "database";

///////////////////////////////////////////////////////////////////////////////
class miis_rdf_server : boost::noncopyable {
public:
	miis_rdf_server(const odtone::mih::config& cfg, boost::asio::io_service& io);
	~miis_rdf_server();

private:

	void event_handler(odtone::mih::message& msg, const boost::system::error_code& ec);
	void run_query(const unsigned char *qry, unsigned char *results);

	odtone::sap::user _mihf;
	odtone::mih::id   _mihfid;

	librdf_world	*_world;
	librdf_storage	*_storage;
	librdf_uri	*_uri;
	librdf_model	*_model;
	std::string     _path_to_database;
};

miis_rdf_server::miis_rdf_server(const odtone::mih::config& cfg, boost::asio::io_service& io)
	: _mihf(cfg, io, boost::bind(&miis_rdf_server::event_handler, this, _1, _2)),
	  _path_to_database(cfg.get<std::string>(kConf_Databse))
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
}

miis_rdf_server::~miis_rdf_server()
{
}

static void recv_handler(odtone::mih::message &m, boost::system::error_code e)
{
}

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

		_mihf.async_send(response, boost::bind(recv_handler, _1, _2));

		break;
	default:
		log_(0, "MIIS RDF Server received message with unsupported MIH opcode: ", msg.mid());
		break;
	}
}

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
			(odtone::sap::kConf_Port, po::value<ushort>()->default_value(1236), "Port")
			(odtone::sap::kConf_File, po::value<std::string>()->default_value("miis_rdf_server.conf"), "Configuration File")
			(odtone::sap::kConf_Receive_Buffer_Len, po::value<uint>()->default_value(4096), "Receive Buffer Length")
			(odtone::sap::kConf_MIHF_Ip, po::value<std::string>()->default_value("127.0.0.1"), "Local MIHF Ip")
			(odtone::sap::kConf_MIH_SAP_id, po::value<std::string>()->default_value("miis"), "MIIS Server ID")
			(odtone::sap::kConf_MIHF_Local_Port, po::value<ushort>()->default_value(1025), "MIHF Local Communications Port")
			(odtone::sap::kConf_MIH_SAP_dest, po::value<std::string>()->default_value(""), "MIH message destination of MIIS server")
			(kConf_Databse, po::value<std::string>()->default_value("database"), "/path/to MIIS server sqlite database ");

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
