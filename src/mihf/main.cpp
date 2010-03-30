//
// Copyright (c) 2007-2009 2009 Universidade Aveiro - Instituto de
// Telecomunicacoes Polo Aveiro
// This file is part of ODTONE - Open Dot Twenty One.
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//
// Author:     Simao Reis <sreis@av.it.pt>
//

///////////////////////////////////////////////////////////////////////////////

#include "mihfid.hpp"
#include "log.hpp"
// #include "transaction_ack_service.hpp"
// #include "transaction_manager.hpp"
#include "address_book.hpp"
#include "local_transaction_pool.hpp"
#include "transaction_pool.hpp"

#include "net_sap.hpp"
#include "message_out.hpp"
#include "transmit.hpp"
#include "service_management.hpp"
#include "event_service.hpp"
#include "command_service.hpp"
#include "information_service.hpp"
#include "service_access_controller.hpp"

#include "message_in.hpp"
#include "udp_listener.hpp"

#include <odtone/base.hpp>
#include <odtone/debug.hpp>
#include <odtone/mih/config.hpp>
#include <odtone/mih/request.hpp>
#include <odtone/mih/response.hpp>
#include <odtone/mih/indication.hpp>
#include <odtone/mih/types/capabilities.hpp>

#include <list>
#include <iostream>

#include <boost/program_options.hpp>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>
#include <boost/asio.hpp>
///////////////////////////////////////////////////////////////////////////////
// using namespace odtone::mihf;
using namespace odtone;
using namespace odtone::mihf;


namespace po = boost::program_options;

// TODO
mih::event_list		capabilities_event_list;
mih::net_type_addr_list capabilities_list_net_type_addr;

// available config options
static const char* const kConf_File               = "conf.file";
static const char* const kConf_Receive_Buffer_Len = "conf.recv_buff_len";

static const char* const kConf_MIHF_Id           = "mihf.id";
static const char* const kConf_MIHF_Ip           = "mihf.ip";
static const char* const kConf_MIHF_Peer_List    = "mihf.peers";
static const char* const kConf_MIHF_Users_List   = "mihf.users";
static const char* const kConf_MIHF_Links_List   = "mihf.links";
static const char* const kConf_MIHF_Remote_Port  = "mihf.remote_port";
static const char* const kConf_MIHF_Local_Port   = "mihf.local_port";
static const char* const kConf_MIHF_Evt_List     = "mihf.event_list";
static const char* const kConf_MIHF_Network_Type = "mihf.link_addr_list";
static const char* const kConf_MIHF_BRDCAST      = "handle_broadcast";
static const char* const kConf_MIHF_Verbosity    = "log";


//
// The following code is to extract from the config file
// the capabilities for the mihf and store them in the service
// management object.
//
// The next version will query the underlying link sap for it's
// capabilities.

void __trim(mih::octet_string &str, const char chr)
{
	str.erase(std::remove(str.begin(), str.end(), chr), str.end());
}

//
// @param evts is a comma separated string whith the list of supported
// events
//
void set_supported_event_list(mih::octet_string &list)
{
	__trim(list, ' ');
	using namespace boost;

	char_separator<char> sep(",");
	tokenizer< char_separator<char> > tokens(list, sep);

	std::map<std::string, uint16> enum_map;

	enum_map["link_detected"]	   = (uint16) mih::link_detected;
	enum_map["link_up"]		   = (uint16) mih::link_up;
	enum_map["link_down"]		   = (uint16) mih::link_down;
	enum_map["link_parameters_report"] = (uint16) mih::link_parameters_report;
	enum_map["link_going_down"]	   = (uint16) mih::link_going_down;
	enum_map["link_handover_imminent"] = (uint16) mih::link_handover_imminent;
	enum_map["link_handover_complete"] = (uint16) mih::link_handover_complete;

	BOOST_FOREACH(mih::octet_string event, tokens) {
		// log(0, "evt: ", event);
		if(enum_map.find(event) != enum_map.end())
			capabilities_event_list.set((mih::event_list_enum) enum_map[event]);
	}
}


//
// list is a comma separated string with the network types
//
// example: ethernet 00:11:22:33:44:55, 802_11 55:66:77:88:99:00
//
//
void set_supported_link_list(mih::octet_string &list)
{
	using namespace boost;

	std::map<std::string, mih::link_type_enum> enum_map;

	enum_map["ethernet"] = mih::link_type_ethernet;
	enum_map["802_11"]   = mih::link_type_802_11;

	char_separator<char> sep1(",");
	char_separator<char> sep2(" ");
	tokenizer< char_separator<char> > list_tokens(list, sep1);

	BOOST_FOREACH(mih::octet_string str, list_tokens) {
		tokenizer< char_separator<char> > tokens(str, sep2);
		tokenizer< char_separator<char> >::iterator it = tokens.begin();

		mih::octet_string link_type = *it;
		++it;
		mih::octet_string link_addr = *it;
		// log(0, "lt: ", link_type, " la: ", link_addr);
		mih::net_type_addr nta;

		if(enum_map.find(link_type) != enum_map.end()) {
			mih::mac_addr mac;
			mac.address(link_addr);

			nta.addr = mac;
			nta.nettype.link = mih::link_type(enum_map[link_type]);

			capabilities_list_net_type_addr.push_back(nta);
		}
	}
}

//
// list is a comma separated list of mihf id ip and port
//
// example: mihf2 192.168.0.1 4551
//
void set_list_peer_mihfs(mih::octet_string &list, address_book &abook)
{
	using namespace boost;

	char_separator<char> sep1(",");
	char_separator<char> sep2(" ");
	tokenizer< char_separator<char> > list_tokens(list, sep1);

	BOOST_FOREACH(mih::octet_string str, list_tokens)
	{
		tokenizer< char_separator<char> > tokens(str, sep2);
		tokenizer< char_separator<char> >::iterator it = tokens.begin();

		mih::octet_string id = *it;
		++it;
		mih::octet_string ip = *it;
		++it;
		mih::octet_string port = *it;

		uint16 port_;
		std::istringstream iss(port);
		if ((iss >> port_).fail())
			throw "invalid port";

		abook.add(id, ip, port_, mih::transport_udp);
	}
}

void set_users_links(mih::octet_string &list, address_book &abook)
{
	using namespace boost;

	char_separator<char> sep1(",");
	char_separator<char> sep2(" ");
	tokenizer< char_separator<char> > list_tokens(list, sep1);

	BOOST_FOREACH(mih::octet_string str, list_tokens) {
		tokenizer< char_separator<char> > tokens(str, sep2);
		tokenizer< char_separator<char> >::iterator it = tokens.begin();

		mih::octet_string id = *it;
		++it;
		mih::octet_string port = *it;

		mih::octet_string ip("127.0.0.1");
		uint16 port_;
		std::istringstream iss(port);
		if ((iss >> port_).fail())
			throw "invalid port";


		abook.add(id, ip, port_, mih::transport_udp);
	}
}

void parse_link_capabilities(mih::config &cfg)
{
	mih::octet_string events = cfg.get<mih::octet_string>(kConf_MIHF_Evt_List);
	mih::octet_string links	= cfg.get<mih::octet_string>(kConf_MIHF_Network_Type);

	set_supported_event_list(events);
	set_supported_link_list(links);
}

void parse_peer_registrations(mih::config &cfg, address_book &abook)
{
	mih::octet_string mihfs	= cfg.get<mih::octet_string>(kConf_MIHF_Peer_List);

	set_list_peer_mihfs(mihfs, abook);
}

void parse_sap_registrations(mih::config &cfg, address_book &abook)
{
	mih::octet_string users	= cfg.get<mih::octet_string>(kConf_MIHF_Users_List);
	mih::octet_string lsaps	= cfg.get<mih::octet_string>(kConf_MIHF_Links_List);

	set_users_links(users, abook);
	set_users_links(lsaps, abook);
}

void sm_register_callbacks(service_management &sm)
{
	sac_register_callback(mih::request::capability_discover,
			      boost::bind(&service_management::capability_discover_request,
					  boost::ref(sm), _1, _2));

	sac_register_callback(mih::response::capability_discover,
			      boost::bind(&service_management::capability_discover_response,
					  boost::ref(sm), _1, _2));
}

void mies_register_callbacks(event_service &mies)
{
	sac_register_callback(mih::request::event_subscribe,
			      boost::bind(&event_service::event_subscribe_request,
					  boost::ref(mies), _1, _2));
	sac_register_callback(mih::response::event_subscribe,
			      boost::bind(&event_service::event_subscribe_response,
					  boost::ref(mies), _1,  _2));
	sac_register_callback(mih::indication::link_up,
			      boost::bind(&event_service::link_up_indication,
					  boost::ref(mies), _1, _2));
	sac_register_callback(mih::indication::link_up,
			      boost::bind(&event_service::link_up_indication,
					  boost::ref(mies), _1, _2));
	sac_register_callback(mih::indication::link_down,
			      boost::bind(&event_service::link_down_indication,
					  boost::ref(mies), _1, _2));
	sac_register_callback(mih::indication::link_detected,
			      boost::bind(&event_service::link_detected_indication,
					  boost::ref(mies), _1, _2));
	sac_register_callback(mih::indication::link_going_down,
			      boost::bind(&event_service::link_going_down_indication,
					  boost::ref(mies), _1, _2));
	sac_register_callback(mih::indication::link_handover_imminent,
			      boost::bind(&event_service::link_handover_imminent_indication,
			      boost::ref(mies), _1, _2));
	sac_register_callback(mih::indication::link_handover_complete,
			      boost::bind(&event_service::link_handover_complete_indication,
					  boost::ref(mies), _1, _2));
	sac_register_callback(mih::request::event_unsubscribe,
			      boost::bind(&event_service::event_unsubscribe_request,
			      boost::ref(mies), _1, _2));
	sac_register_callback(mih::response::event_unsubscribe,
			      boost::bind(&event_service::event_unsubscribe_response,
					  boost::ref(mies), _1, _2));
}
// REGISTER(event_service::link_pdu_transmit_status_indication)

void mics_register_callbacks(command_service &mics)
{
	sac_register_callback(mih::request::link_get_parameters,
			      boost::bind(&command_service::link_get_parameters_request,
					  boost::ref(mics), _1, _2));
	sac_register_callback(mih::response::link_get_parameters,
			      boost::bind(&command_service::link_get_parameters_response,
					  boost::ref(mics), _1, _2));
	sac_register_callback(mih::request::link_configure_thresholds,
			      boost::bind(&command_service::link_configure_thresholds_request,
					  boost::ref(mics), _1, _2));
	sac_register_callback(mih::response::link_configure_thresholds,
			      boost::bind(&command_service::link_configure_thresholds_response,
					  boost::ref(mics), _1, _2));
	sac_register_callback(mih::request::link_actions,
			      boost::bind(&command_service::link_actions_request,
					  boost::ref(mics), _1, _2));
	sac_register_callback(mih::response::link_actions,
			      boost::bind(&command_service::link_actions_response,
					  boost::ref(mics), _1, _2));
	sac_register_callback(mih::request::net_ho_candidate_query,
			      boost::bind(&command_service::net_ho_candidate_query_request,
					  boost::ref(mics), _1, _2));
	sac_register_callback(mih::response::net_ho_candidate_query,
			      boost::bind(&command_service::net_ho_candidate_query_response,
					  boost::ref(mics), _1, _2));
	sac_register_callback(mih::request::mn_ho_candidate_query,
			      boost::bind(&command_service::mn_ho_candidate_query_request,
					  boost::ref(mics), _1, _2));
	sac_register_callback(mih::response::mn_ho_candidate_query,
			      boost::bind(&command_service::mn_ho_candidate_query_response,
					  boost::ref(mics), _1, _2));
	sac_register_callback(mih::request::n2n_ho_query_resources,
			      boost::bind(&command_service::n2n_ho_query_resources_request,
					  boost::ref(mics), _1, _2));
	sac_register_callback(mih::response::n2n_ho_query_resources,
			      boost::bind(&command_service::n2n_ho_query_resources_response,
					  boost::ref(mics), _1, _2));
	sac_register_callback(mih::request::mn_ho_commit,
			      boost::bind(&command_service::mn_ho_commit_request,
					  boost::ref(mics), _1, _2));
	sac_register_callback(mih::response::mn_ho_commit,
			      boost::bind(&command_service::mn_ho_commit_response,
					  boost::ref(mics), _1, _2));
	sac_register_callback(mih::request::n2n_ho_commit,
			      boost::bind(&command_service::n2n_ho_commit_request,
					  boost::ref(mics), _1, _2));
	sac_register_callback(mih::response::n2n_ho_commit,
			      boost::bind(&command_service::n2n_ho_commit_response,
					  boost::ref(mics), _1, _2));
	sac_register_callback(mih::request::n2n_ho_complete,
			      boost::bind(&command_service::n2n_ho_complete_request,
					  boost::ref(mics), _1, _2));
	sac_register_callback(mih::response::n2n_ho_complete,
			      boost::bind(&command_service::n2n_ho_complete_response,
					  boost::ref(mics), _1, _2));
}

void miis_register_callbacks(information_service &miis)
{
	sac_register_callback(mih::request::get_information,
			      boost::bind(&information_service::get_information_request,
					  boost::ref(miis), _1, _2));
	sac_register_callback(mih::response::get_information,
			      boost::bind(&information_service::get_information_response,
					  boost::ref(miis), _1, _2));
	sac_register_callback(mih::request::push_information,
			      boost::bind(&information_service::push_information_request,
					  boost::ref(miis), _1, _2));
	sac_register_callback(mih::indication::push_information,
			      boost::bind(&information_service::push_information_indication,
					  boost::ref(miis), _1, _2));
}

int main(int argc, char **argv)
{
	odtone::setup_crash_handler();

	boost::asio::io_service io;

	// declare MIHF supported options
	po::options_description desc(mih::octet_string("MIHF Configuration Options"));

	desc.add_options()
		("help", "Display configuration options")
		(kConf_File, po::value<std::string>()->default_value("odtone.conf"), "Configuration File")
		(kConf_Receive_Buffer_Len, po::value<uint16>()->default_value(4096), "Receive Buffer Length")
		(kConf_MIHF_Id, po::value<std::string>()->default_value("mihf"), "MIHF Id")
		(kConf_MIHF_Ip, po::value<std::string>()->default_value("127.0.0.1"), "MIHF Ip")
		(kConf_MIHF_Peer_List, po::value<std::string>()->default_value(""), "List of peer MIHFs")
		(kConf_MIHF_Users_List, po::value<std::string>()->default_value("user 1234"), "List of User SAPs")
		(kConf_MIHF_Links_List, po::value<std::string>()->default_value("link 1235"), "List of Links SAPs")
		(kConf_MIHF_Remote_Port, po::value<uint16>()->default_value(4551), "MIHF Remote Communications Port")
		(kConf_MIHF_Local_Port, po::value<uint16>()->default_value(1025), "MIHF Local Communications Port")
		(kConf_MIHF_Evt_List, po::value<std::string>()->default_value(""), "MIHF List of supported events")
		(kConf_MIHF_Network_Type, po::value<std::string>()->default_value(""), "MIHF Network Type list")
		(kConf_MIHF_BRDCAST, po::value<bool>()->default_value(false), "MIHF responds to broadcast messages")
		(kConf_MIHF_Verbosity, po::value<uint16>()->default_value(1), "MIHF log level [0-4]")
		;

	odtone::mih::config cfg(desc);
	cfg.parse(argc, argv, kConf_File);

	if (cfg.help()) {
		std::cerr << desc << std::endl;
		return EXIT_SUCCESS;
	}

	// get command line parameters
	bool enable_broadcast = cfg.get<bool>(kConf_MIHF_BRDCAST);
	uint16 lport = cfg.get<uint16>(kConf_MIHF_Local_Port);
	uint16 rport = cfg.get<uint16>(kConf_MIHF_Remote_Port);
	mih::octet_string id = cfg.get<mih::octet_string>(kConf_MIHF_Id);
	uint16 loglevel = cfg.get<uint16>(kConf_MIHF_Verbosity);
	//

	// set this mihf id
	mihfid_t::instance()->assign(id.c_str());
	// set log level
	log.level(loglevel);

	// set link capabilities
	parse_link_capabilities(cfg);

	// create address books that stores info on how to contact mih
	// saps and peer mihfs
	address_book		remote_abook, local_abook;
	parse_sap_registrations(cfg, local_abook);
	parse_peer_registrations(cfg, remote_abook);
	//

	// pool of pending transactions with peer mihfs
	transaction_pool	tpool(io);

	// pool of pending transactions with local mih saps (user and
	// links)
	local_transaction_pool	lpool;

	// handler for remote messages
	handler_t process_message = boost::bind(&sac_process_message, _1, _2);

	// wrapper for sending messages
	net_sap			netsap(io, remote_abook);

	// transaction manager for outgoing messages
	message_out		msgout(tpool, process_message, netsap);
	transmit		trnsmt(io, local_abook, msgout);

	// instantiate mihf services
	event_service		mies(lpool, trnsmt);
	command_service		mics(lpool, trnsmt);
	information_service	miis(lpool, trnsmt);
	service_management	sm(lpool, trnsmt);

	// register callbacks with service access controller
	sm_register_callbacks(sm);
	mies_register_callbacks(mies);
	mics_register_callbacks(mics);
	miis_register_callbacks(miis);

	// transaction manager for incoming messages
	message_in msgin(tpool, process_message, netsap);

	// sac dispatch is for handling messages from local mih saps
	// (users and links)
	sac_dispatch sacd(trnsmt);

	// handler of messages received on local port
	dispatch_t ldispatch = boost::bind(&sac_dispatch::operator(), sacd, _1);
	// handler of messages received from peer mihfs
	dispatch_t rdispatch = boost::bind(&message_in::operator(), msgin, _1);

	// create and bind to port 'lport' on loopback interface and
	// call ldispatch when a message is received
	udp_listener commhand(io, ip::udp::v4(), "127.0.0.1", lport, ldispatch);

	// create and bind to port rport and call rdispatch when a
	// message is received
	udp_listener remotelistener(io, ip::udp::v4(), "0.0.0.0", rport, rdispatch);

	// start listening on local and remote ports
	commhand.start();
	remotelistener.start();

	io.run();

	return EXIT_SUCCESS;
}
