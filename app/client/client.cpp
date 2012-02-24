//==============================================================================
// Brief   : Client Application
// Authors : Simao Reis <sreis@av.it.pt>
//           Carlos Guimarães <cguimaraes@av.it.pt>
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

#include <odtone/debug.hpp>
#include <odtone/mih/message.hpp>
#include <odtone/mih/indication.hpp>
#include <odtone/mih/response.hpp>
#include <odtone/mih/request.hpp>
#include <odtone/mih/types/information.hpp>
#include <odtone/mih/types/capabilities.hpp>
#include <odtone/mih/types/capabilities.hpp>
#include <odtone/mih/config.hpp>
#include <odtone/mih/tlv.hpp>
#include <odtone/mih/tlv_types.hpp>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/variant/apply_visitor.hpp>

#include <odtone/mih/types/information_elements.hpp>

using namespace odtone;
using boost::asio::ip::udp;

namespace po = boost::program_options;

static const char* const kConf_MIH_Dest = "dest";
static const char* const kConf_MIH_Port = "port";
static const char* const kConf_File     = "client.conf";

static const char* const kConf_MIH_LinkUp_indication = "indication.link_up";
static const char* const kConf_MIH_LinkDown_indication = "indication.link_down";
static const char* const kConf_MIH_LinkDetected_indication = "indication.link_detected";
static const char* const kConf_MIH_LinkGoingDown_indication = "indication.link_going_down";
static const char* const kConf_MIH_LinkHandoverImminent_indication = "indication.link_handover_imminent";
static const char* const kConf_MIH_LinkHandoverComplete_indication = "indication.link_handover_complete";
static const char* const kConf_MIH_LinkConfigureThresholds_request = "request.link_configure_thresholds";
static const char* const kConf_MIH_LinkGetParameters_request = "request.link_get_parameters";
static const char* const kConf_MIH_LinkActions_request = "request.link_actions";
static const char* const kConf_MIH_EventUnsubscribe_request = "request.event_unsubscribe";

/**
 * Dummy synchronous MIH SAP handler.
 */
class handler
{
public:
	/**
	 * Construct a dummy synchronous MIH SAP handler.
	 *
	 * @param dst_ip Destination IP address.
	 * @param dsp_port Destination listening port.
	 */
	handler(const mih::octet_string &dst_ip, const mih::octet_string &dst_port)
		: _io_service(),
		_soc(_io_service, udp::endpoint(udp::v4(), 0)),
		_res(_io_service),
		_qry(udp::v4(), dst_ip, dst_port)
	{
		_it = _res.resolve(_qry);
	}

	/**
	 * Send a message.
	 *
	 * @param msg The message to send.
	 */
	void send(mih::message &msg)
	{
		mih::frame_vla fm;
		void *sbuff;
		size_t slen;

		msg.get_frame(fm);

		sbuff = fm.get();
		slen = fm.size();

		_soc.send_to(boost::asio::buffer(sbuff, slen), *_it);
	}

private:
	boost::asio::io_service _io_service;
	udp::socket             _soc;
	udp::resolver           _res;
	udp::resolver::query    _qry;
	udp::resolver::iterator _it;
};

/**
 * Create and send a MIH_Link_Up.indication message.
 *
 * @param sap The SAP helper.
 * @param dst The destination MIH ID.
 */
void send_link_up_indication(handler &sap, const char *dst)
{
	mih::message p;

	mih::link_tuple_id	li;
	mih::mac_addr			mac;

	mac.address("00:11:22:33:44:55");
	li.type = mih::link_type_802_11;
	li.addr = mac;

	p << mih::indication(mih::indication::link_up)
		& mih::tlv_link_identifier(li);

	p.source(mih::id("link"));
	p.destination(mih::id(dst));

	sap.send(p);
}

/**
 * Create and send a MIH_Link_Down.indication message.
 *
 * @param sap The SAP helper.
 * @param dst The destination MIH ID.
 */
void send_link_down_indication(handler &sap, const char *dst)
{
	mih::message p;

	mih::link_tuple_id	li;
	mih::mac_addr			mac;

	mac.address("00:11:22:33:44:55");
	li.type = mih::link_type_802_11;
	li.addr = mac;

	p << mih::indication(mih::indication::link_down)
		& mih::tlv_link_identifier(li);

	p.source(mih::id("link"));
	p.destination(mih::id(dst));

	sap.send(p);
}

/**
 * Create and send a MIH_Link_Detected.indication message.
 *
 * @param sap The SAP helper.
 * @param dst The destination MIH ID.
 */
void send_link_detected_indication(handler &sap, const char *dst)
{
	mih::message p;

	mih::link_det_info_list		list;
	mih::link_det_info			link;
	mih::mac_addr					mac;

	mac.address("00:11:22:33:44:55");

	link.id.addr = mac;
	link.id.type = mih::link_type_802_11;

	list.push_back(link);

	p << mih::indication(mih::indication::link_detected)
		& mih::tlv_link_det_info_list(list);

	p.source(mih::id("link"));
	p.destination(mih::id(dst));

	sap.send(p);
}

/**
 * Create and send a MIH_Link_Going_Down.indication message.
 *
 * @param sap The SAP helper.
 * @param dst The destination MIH ID.
 */
void send_link_going_down_indication(handler &sap, const char *dst)
{
	mih::message p;

	mih::link_tuple_id	li;
	mih::mac_addr		mac;

	mac.address("00:11:22:33:44:55");
	li.type = mih::link_type_802_11;
	li.addr = mac;

	p << mih::indication(mih::indication::link_going_down)
		& mih::tlv_link_identifier(li);

	p.source(mih::id("link"));
	p.destination(mih::id(dst));

	sap.send(p);
}

/**
 * Create and send a MIH_Link_Handover_Imminent.indication message.
 *
 * @param sap The SAP helper.
 * @param dst The destination MIH ID.
 */
void send_link_handover_imminent_indication(handler &sap, const char *dst)
{
	mih::message p;

	mih::link_tuple_id	oli;
	mih::link_tuple_id	nli;
	mih::mac_addr		mac;

	mac.address("00:11:22:33:44:55");
	oli.type = mih::link_type_802_11;
	oli.addr = mac;

	mac.address("66:77:88:99:00:11");
	nli.type = mih::link_type_ethernet;
	nli.addr = mac;

	p << mih::indication(mih::indication::link_handover_imminent)
		& mih::tlv_link_identifier(oli)
		& mih::tlv_new_link_identifier(nli);

	p.source(mih::id("link"));
	p.destination(mih::id(dst));

	sap.send(p);
}

/**
 * Create and send a MIH_Link_Handover_Complete.indication message.
 *
 * @param sap The SAP helper.
 * @param dst The destination MIH ID.
 */
void send_link_handover_complete_indication(handler &sap, const char *dst)
{
	mih::message p;

	mih::link_tuple_id oli;
	mih::link_tuple_id nli;
	mih::mac_addr      mac;

	mac.address("00:11:22:33:44:55");
	oli.type = mih::link_type_802_11;
	oli.addr = mac;

	mac.address("66:77:88:99:00:11");
	nli.type = mih::link_type_ethernet;
	nli.addr = mac;

	p << mih::indication(mih::indication::link_handover_complete)
		& mih::tlv_link_identifier(oli)
		& mih::tlv_new_link_identifier(nli);

	p.source(mih::id("link"));
	p.destination(mih::id(dst));

	sap.send(p);
}

/**
 * Create and send a MIH_Link_Configure_Thresholds.request message.
 *
 * @param sap The SAP helper.
 * @param dst The destination MIH ID.
 */
void send_link_configure_thresholds_request(handler &sap, const char *dst)
{
	mih::message p;

	mih::link_tuple_id 			li;
	mih::mac_addr      			mac;
	mih::link_cfg_param			lcp;
	mih::link_cfg_param_list 	lcpl;

	mac.address("00:11:22:33:44:55");
	li.type = mih::link_type_802_11;
	li.addr = mac;

	std::vector<mih::threshold> th_list;

	lcp.type = mih::link_type_802_11;
	lcp.timer_interval = 1234;
	lcp.action = mih::th_action_normal;
	lcp.threshold_list = th_list;
	lcpl.push_back(lcp);

	p << mih::request(mih::request::link_configure_thresholds)
		& mih::tlv_link_identifier(li)
		& mih::tlv_link_cfg_param_list(lcpl);

	p.source(mih::id("user"));
	p.destination(mih::id(dst));

	sap.send(p);
}

/**
 * Create and send a MIH_Link_Get_Parameters.request message.
 *
 * @param sap The SAP helper.
 * @param dst The destination MIH ID.
 */
void send_link_get_parameters_request(handler &sap, const char *dst)
{
	mih::message p;

	mih::link_tuple_id 	li;
	mih::link_id_list	lil;
	mih::mac_addr      	mac;

	mac.address("00:11:22:33:44:55");
	li.type = mih::link_type_802_11;
	li.addr = mac;
	lil.push_back(li);

	mih::link_status_req	lsr;
	mih::link_param_802_11	lp = mih::link_param_802_11_rssi;
	lsr._states_req.set(mih::link_states_req_op_mode);
	lsr._param_type_list.push_back(lp);
	lsr._desc_req.set(mih::link_desc_req_classes_of_service_supported);

	p << mih::request(mih::request::link_get_parameters)
		& mih::tlv_link_id_list(lil)
		& mih::tlv_get_status_req_set(lsr);

	p.source(mih::id("user"));
	p.destination(mih::id(dst));

	sap.send(p);
}

/**
 * Create and send a MIH_Link_Actions.request message.
 *
 * @param sap The SAP helper.
 * @param dst The destination MIH ID.
 */
void send_link_actions_request(handler &sap, const char *dst)
{
	mih::message p;

	mih::link_tuple_id 	li;
	mih::mac_addr      	mac;

	mac.address("00:11:22:33:44:55");
	li.type = mih::link_type_802_11;
	li.addr = mac;

	mih::link_action_req 	lar;
	mih::link_action_list	larl;
	lar.id = li;
	lar.addr = mac;
	lar.action.type = mih::link_ac_type_none;
	lar.action.attr.set(mih::link_ac_attr_scan);
	lar.ex_time = 0;

	larl.push_back(lar);

	p << mih::request(mih::request::link_actions)
		& mih::tlv_link_action_list(larl);

	p.source(mih::id("user"));
	p.destination(mih::id(dst));

	sap.send(p);
}

/**
 * Create and send a MIH_Link_Event_Unsubscribe.request message.
 *
 * @param sap The SAP helper.
 * @param dst The destination MIH ID.
 */
void send_event_unsubscribe_request(handler &sap, const char *dst)
{
	mih::message p;

	mih::link_tuple_id 	li;
	mih::mac_addr      	mac;

	mac.address("00:11:22:33:44:55");
	li.type = mih::link_type_802_11;
	li.addr = mac;
	odtone::mih::mih_evt_list evt;
	evt.set(odtone::mih::mih_evt_link_up);

	p << mih::request(mih::request::event_unsubscribe)
		& odtone::mih::tlv_link_identifier(li)
		& odtone::mih::tlv_event_list(evt);

	p.source(mih::id("user"));
	p.destination(mih::id(dst));

	sap.send(p);
}

/**
 * Create and send a MIH_Get_Information.request message.
 *
 * @param sap The SAP helper.
 * @param dst The destination MIH ID.
 */
void send_rdf_get_information_request(handler &sap, const char *dst)
{
	mih::message		p;

	mih::iq_rdf_data query;
	mih::iq_rdf_data_list query_list;

	p.source(mih::id("user"));
	p.destination(mih::id(dst));

	// Below is an example of IS query. The MIH client queries
	// available networks for a specific location identified by
	// cellular cell ID “800”. The client requires the server to
	// return the network_id and link_type of all available
	// networks for this location.
	query._data.assign("PREFIX mihbasic: <http://www.mih.org/2006/09/rdf-basic-schema#> \
	PREFIX xsd: <http://www.w3.org/2001/XMLSchema#>			\
	SELECT ?network_id ?link_type					\
	WHERE {								\
	  ?network mihbasic:ie_network_id ?network_id .			\
		  ?network mihbasic:ie_network_type ?network_type .	\
		  ?network_type mihbasic:link_type ?link_type .		\
		  ?network mihbasic:ie_container_poa ?poa .		\
		  ?poa mihbasic:ie_poa_location ?x1 .			\
		  ?x1 mihbasic:location_cell_id \"1\" .		\
	}");

	// other queries can be added in the request
	query_list.push_back(query);

	// create and send a Get_Information request
	p << mih::request(mih::request::get_information)
		& mih::tlv_info_query_rdf_data_list(query_list);

	sap.send(p);
}

//
// example on how to create a TLV binary encoded
// Get_Information.response
//
/**
 * Create and send a MIH_Get_Information.response message.
 *
 * @param sap The SAP helper.
 * @param dst The destination MIH ID.
 */
void send_bin_get_information_response(handler &sap, const char *dst)
{
	mih::message		p;

	mih::ie_container_poa					poa;
	mih::ie_container_network				net;
	mih::ie_container_list_of_networks		list;

	// ie_container_poa
	//
	mih::ie_poa_link_addr		poa_la;
	mih::link_addr				la;
	mih::mac_addr				mac;
	mih::ie_poa_location		poa_loc;
	mih::cell_id				poa_cell;
	mih::ch_range				range;

	mac.address("00:11:22:33:44:55");
	la	   = mac;
	poa_la = la;

	poa_cell = 10;				// random value
	poa_loc	 = poa_cell;

	range.high = 2;
	range.low  = 1;

	poa.poa_link_addr	  = poa_la;
	poa.poa_location	  = poa_loc;
	poa.poa_channel_range = range;
	//

	// ie_container_network
	//
	mih::link_type				lt;
	mih::ie_network_type		nt;
	mih::ie_operator_id		opid;

	lt		= mih::link_type_802_11;
	nt.link = lt;

	opid.opname = "name";
	opid.opnamespace = mih::op_namespace_gsm_umts;

	net.network_type = nt;
	net.operator_id = opid;

	net.poas.push_back(poa);
	//

	// ie_container_list_of_networks
	//
	list.push_back(net);
	//

	//
	mih::ir_bin_data			bin_data;
	mih::ir_bin_data_list		bin_data_list;

	bin_data.output() & mih::tlv_ie_container_list_of_networks(list);
	bin_data_list.push_back(bin_data);
	//

	p << mih::response(mih::response::get_information)
		& mih::tlv_info_resp_bin_data_list(bin_data_list);

	p.uir(true);
	p.source(mih::id("user"));
	p.destination(mih::id(dst));

	sap.send(p);
}


int main(int argc, char **argv)
{
	po::options_description desc(mih::octet_string("Client Configuration Options"));

	desc.add_options()
		("help", "Display available Options")
		(kConf_File, po::value<std::string>()->default_value("client.conf"), "Configuration File")
		(kConf_MIH_Port, po::value<mih::octet_string>()->default_value("1025"), "MIHFs port")
		(kConf_MIH_Dest, po::value<mih::octet_string>()->default_value("local-mihf"), "MIH Destination identifier")
		(kConf_MIH_LinkUp_indication, "Send a MIH_LinkUp.indication to MIHF")
		(kConf_MIH_LinkDown_indication, "Send a MIH_LinkDown.indication to MIHF")
		(kConf_MIH_LinkDetected_indication, "Send a MIH_LinkDetected.indication to MIHF")
		(kConf_MIH_LinkGoingDown_indication, "Send a MIH_LinkGoingDown.indication to MIHF")
		(kConf_MIH_LinkHandoverImminent_indication, "Send a MIH_LinkHandoverImminent.indication to MIHF")
		(kConf_MIH_LinkHandoverComplete_indication, "Send a MIH_LinkHandoverComplete.indication to MIHF")
		(kConf_MIH_LinkConfigureThresholds_request, "Send a MIH_LinkConfigureThresholds.request to MIHF")
		(kConf_MIH_LinkGetParameters_request, "Send a MIH_LinkGetParameters.request to MIHF")
		(kConf_MIH_LinkActions_request, "Send a MIH_LinkActions.request to MIHF")
		(kConf_MIH_EventUnsubscribe_request, "Send a MIH_EventUnsubscribe.request to MIHF")
		 ;
	mih::config cfg(desc);

	cfg.parse(argc, argv, kConf_File);

	if (cfg.help() || argc == 1) {
		std::cerr << desc << std::endl;
		return EXIT_SUCCESS;
	}


	mih::octet_string dest = cfg.get<mih::octet_string>(kConf_MIH_Dest);
	mih::octet_string port = cfg.get<mih::octet_string>(kConf_MIH_Port);

	handler sap("127.0.0.1", port.c_str());

	if (cfg.count(kConf_MIH_LinkUp_indication)) {
	    std::cout << "sent link up indication to " << dest.c_str() << std::endl;
	    send_link_up_indication(sap, dest.c_str());
	}

	if (cfg.count(kConf_MIH_LinkDown_indication)) {
		std::cout << "sent link down indication to " << dest.c_str() << std::endl;
		send_link_down_indication(sap, dest.c_str());
	}

	if (cfg.count(kConf_MIH_LinkDetected_indication)) {
		std::cout << "sent link detected indication to " << dest.c_str() << std::endl;
		send_link_detected_indication(sap, dest.c_str());
	}

	if (cfg.count(kConf_MIH_LinkGoingDown_indication)) {
		std::cout << "sent link going down indication to " << dest.c_str() << std::endl;
		send_link_going_down_indication(sap, dest.c_str());
	}

	if (cfg.count(kConf_MIH_LinkHandoverImminent_indication)) {
		std::cout << "sent link handover imminent indication to " << dest.c_str() << std::endl;
		send_link_handover_imminent_indication(sap, dest.c_str());
	}

	if (cfg.count(kConf_MIH_LinkHandoverComplete_indication)) {
		std::cout << "sent link handover complete indication to " << dest.c_str() << std::endl;
		send_link_handover_complete_indication(sap, dest.c_str());
	}

	if (cfg.count(kConf_MIH_LinkConfigureThresholds_request)) {
		std::cout << "sent link configure thresholds request to " << dest.c_str() << std::endl;
		send_link_configure_thresholds_request(sap, dest.c_str());
	}

	if (cfg.count(kConf_MIH_LinkGetParameters_request)) {
		std::cout << "sent link get parameters request to " << dest.c_str() << std::endl;
		send_link_get_parameters_request(sap, dest.c_str());
	}

	if (cfg.count(kConf_MIH_LinkActions_request)) {
		std::cout << "sent link actions request to " << dest.c_str() << std::endl;
		send_link_actions_request(sap, dest.c_str());
	}

	if (cfg.count(kConf_MIH_EventUnsubscribe_request)) {
		std::cout << "sent event unsubscribe request to " << dest.c_str() << std::endl;
		send_event_unsubscribe_request(sap, dest.c_str());
	}

	return 0;
}
