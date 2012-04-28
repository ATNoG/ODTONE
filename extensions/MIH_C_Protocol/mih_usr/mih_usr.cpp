//==============================================================================
// Brief   : MIH-User
// Authors : Bruno Santos <bsantos@av.it.pt>
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

#include <odtone/base.hpp>
#include <odtone/debug.hpp>
#include <odtone/logger.hpp>
#include <odtone/mih/request.hpp>
#include <odtone/mih/response.hpp>
#include <odtone/mih/indication.hpp>
#include <odtone/mih/confirm.hpp>
#include <odtone/mih/tlv_types.hpp>
#include <odtone/sap/user.hpp>

#include <boost/utility.hpp>
#include <boost/bind.hpp>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>

#include <iostream>

#define THRESHOLD_VAL 100

///////////////////////////////////////////////////////////////////////////////

static const char* const kConf_MIH_Commands = "user.commands";
///////////////////////////////////////////////////////////////////////////////

namespace po = boost::program_options;

using odtone::uint;
using odtone::ushort;

odtone::logger log_("[mih_usr]", std::cout);

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
boost::optional<odtone::mih::mih_cmd_list> parse_supported_commands(const odtone::mih::config &cfg)
{
	using namespace boost;

	odtone::mih::mih_cmd_list commands;
	bool has_cmd = false;

	std::map<std::string, odtone::mih::mih_cmd_list_enum> enum_map;
	enum_map["mih_link_get_parameters"]       = odtone::mih::mih_cmd_link_get_parameters;
	enum_map["mih_link_configure_thresholds"] = odtone::mih::mih_cmd_link_configure_thresholds;
	enum_map["mih_link_actions"]              = odtone::mih::mih_cmd_link_actions;
	enum_map["mih_net_ho_candidate_query"]    = odtone::mih::mih_cmd_net_ho_candidate_query;
	enum_map["mih_net_ho_commit"]             = odtone::mih::mih_cmd_net_ho_commit;
	enum_map["mih_n2n_ho_query_resources"]    = odtone::mih::mih_cmd_n2n_ho_query_resources;
	enum_map["mih_n2n_ho_commit"]             = odtone::mih::mih_cmd_n2n_ho_commit;
	enum_map["mih_n2n_ho_complete"]           = odtone::mih::mih_cmd_n2n_ho_complete;
	enum_map["mih_mn_ho_candidate_query"]     = odtone::mih::mih_cmd_mn_ho_candidate_query;
	enum_map["mih_mn_ho_commit"]              = odtone::mih::mih_cmd_mn_ho_commit;
	enum_map["mih_mn_ho_complete"]            = odtone::mih::mih_cmd_mn_ho_complete;

	std::string tmp = cfg.get<std::string>(kConf_MIH_Commands);
	__trim(tmp, ' ');

	char_separator<char> sep1(",");
	tokenizer< char_separator<char> > list_tokens(tmp, sep1);

	BOOST_FOREACH(std::string str, list_tokens) {
		if(enum_map.find(str) != enum_map.end()) {
			commands.set((odtone::mih::mih_cmd_list_enum) enum_map[str]);
			has_cmd = true;
		}
	}

	boost::optional<odtone::mih::mih_cmd_list> supp_cmd;
	if(has_cmd)
		supp_cmd = commands;

	return supp_cmd;
}

///////////////////////////////////////////////////////////////////////////////
/**
 * This class provides an implementation of an IEEE 802.21 MIH-User.
 */
class mih_user : boost::noncopyable {
public:
	/**
	 * Construct the MIH-User.
	 *
	 * @param cfg Configuration options.
	 * @param io The io_service object that the MIH-User will use to
	 * dispatch handlers for any asynchronous operations performed on the socket.
	 */
	mih_user(const odtone::mih::config& cfg, boost::asio::io_service& io);

	/**
	 * Destruct the MIH-User.
	 */
	~mih_user();

protected:
	/**
	 * User registration handler.
	 *
	 * @param cfg Configuration options.
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
	 * Capability Discover handler.
	 *
	 * @param msg Received message.
	 * @param ec Error Code.
	 */
	void capability_discover_confirm(odtone::mih::message& msg, const boost::system::error_code& ec);

	/**
	 * Event subscribe handler.
	 *
	 * @param msg Received message.
	 * @param ec Error Code.
	 */
	void event_subscribe_response(odtone::mih::message& msg, const boost::system::error_code& ec);

	void link_configure_thresholds(odtone::mih::message& msg, const boost::system::error_code& ec);

	void link_configure_thresholds_confirm(odtone::mih::message& msg, const boost::system::error_code& ec);

	void link_get_parameters(odtone::mih::message& msg, const boost::system::error_code& ec);

	void link_get_parameters_confirm(odtone::mih::message& msg, const boost::system::error_code& ec);

	void link_detected(odtone::mih::message& msg, const boost::system::error_code& ec);

	void link_actions_request(odtone::mih::message& msg, const boost::system::error_code& ec);

	void link_actions_confirm(odtone::mih::message& msg, const boost::system::error_code& ec);

	void link_up_indication(odtone::mih::message& msg, const boost::system::error_code& ec);

	void link_going_down(odtone::mih::message& msg, const boost::system::error_code& ec);

	void link_down_indication(odtone::mih::message& msg, const boost::system::error_code& ec);

	void link_event_unsubscribe_confirm(odtone::mih::message& msg, const boost::system::error_code& ec);

	void link_event_unsubscribe(odtone::mih::message& msg, const boost::system::error_code& ec);

	void link_parameters_report(odtone::mih::message& msg, const boost::system::error_code& ec);

	void print_l2_3gpp_addr(odtone::mih::link_type& link_type, odtone::mih::l2_3gpp_addr& l2_3gpp_addr);


private:
	odtone::sap::user _mihf;	/**< User SAP helper.		*/
	odtone::mih::id   _mihfid;	/**< MIHF destination ID.	*/
	odtone::uint param_req, la_req;
	odtone::mih::net_type_addr rcv_net_type_addr;
	odtone::mih::link_id rcv_link_id;
};

/**
 * Construct the MIH-User.
 *
 * @param cfg Configuration options.
 * @param io The io_service object that the MIH-User will use to
 * dispatch handlers for any asynchronous operations performed on the socket.
 */
mih_user::mih_user(const odtone::mih::config& cfg, boost::asio::io_service& io)
	: _mihf(cfg, io, boost::bind(&mih_user::event_handler, this, _1, _2))
{
	odtone::mih::message m;
	boost::optional<odtone::mih::mih_cmd_list> supp_cmd = parse_supported_commands(cfg);

	m << odtone::mih::indication(odtone::mih::indication::user_register)
	    & odtone::mih::tlv_command_list(supp_cmd);

	log_(0, "User Register Indication - SENT ");
	log_(0, "	- User Name: ", m.source().to_string());
	log_(0, " ");

	m.destination(odtone::mih::id("local-mihf"));

	_mihf.async_send(m, boost::bind(&mih_user::user_reg_handler, this, boost::cref(cfg), _2));
}


/**
 * Destruct the MIH-User.
 */
mih_user::~mih_user()
{
}

/**
 * Print 3GPP Address.
 *
 * @param link_type Link Type.
 * @param l2_3gpp_addr 3GPP Address.
 */
void mih_user::print_l2_3gpp_addr(odtone::mih::link_type& link_type, odtone::mih::l2_3gpp_addr& l2_3gpp_addr)
{
	odtone::uint iter;
	if(link_type == odtone::mih::link_type_umts){ log_(0, "      Link Type: UMTS"); log_(0, "      3GPP Address: ");}

	std::printf("[mih_usr]:       ");
	for(iter=0; iter<l2_3gpp_addr.value.length(); iter++)
	{
		std::printf("-%hhx-", l2_3gpp_addr.value[iter]);
	}
	std::printf("\n");
}

/**
 * User registration handler.
 *
 * @param cfg Configuration options.
 * @param ec Error Code.
 */
void mih_user::user_reg_handler(const odtone::mih::config& cfg, const boost::system::error_code& ec)
{
	log_(0, "MIH-User register result: ", ec.message());
	log_(0, "");

	odtone::mih::message msg;

	odtone::mih::octet_string destination = cfg.get<odtone::mih::octet_string>(odtone::sap::kConf_MIH_SAP_dest);
	_mihfid.assign(destination.c_str());

	//
	// Let's fire a capability discover request to get things moving
	//
	msg << odtone::mih::request(odtone::mih::request::capability_discover, _mihfid);

	_mihf.async_send(msg, boost::bind(&mih_user::capability_discover_confirm, this, _1, _2));

	log_(0, "Capability_Discover.request - SENT (towards its local MIHF)");
	log_(0, "");
}

/**
 * Default MIH event handler.
 *
 * @param msg Received message.
 * @param ec Error code.
 */
void mih_user::event_handler(odtone::mih::message& msg, const boost::system::error_code& ec)
{
	if (ec) {
		log_(0, __FUNCTION__, " error: ", ec.message());
		return;
	}

	switch (msg.mid()) {
	case odtone::mih::indication::link_up:
		mih_user::link_up_indication(msg, ec);
		break;

	case odtone::mih::indication::link_down:
		mih_user::link_down_indication(msg, ec);
		sleep(2);
		mih_user::link_get_parameters(msg, ec);
		break;

	case odtone::mih::indication::link_detected:
		mih_user::link_detected(msg, ec);
		sleep(1);
		la_req = 0;
		mih_user::link_actions_request(msg, ec);
		break;

	case odtone::mih::indication::link_going_down:
		mih_user::link_going_down(msg,ec);
		sleep(1);
		param_req = 2;
        mih_user::link_get_parameters(msg, ec);
		break;

	case odtone::mih::indication::link_handover_imminent:
		log_(0, "MIH-User has received a local event \"link_handover_imminent\"");
		break;
	case odtone::mih::indication::link_handover_complete:
		log_(0, "MIH-User has received a local event \"link_handover_complete\"");
		break;

	case odtone::mih::confirm::link_configure_thresholds:
		mih_user::link_configure_thresholds_confirm(msg, ec);
		sleep(1);
        mih_user::link_get_parameters(msg, ec);
		break;

	case odtone::mih::confirm::link_get_parameters:
		switch(param_req)
		{
			case 1: mih_user::link_get_parameters_confirm(msg, ec); break;
			case 2: mih_user::link_get_parameters_confirm(msg, ec);
				    la_req = 1;
				    param_req = 3;
				    mih_user::link_actions_request(msg, ec);
					break;
			case 3: mih_user::link_get_parameters_confirm(msg, ec);
					mih_user::link_event_unsubscribe(msg, ec);
					break;
		}
		break;

		mih_user::link_get_parameters_confirm(msg, ec);
		sleep(1);
		break;

	case odtone::mih::confirm::link_actions:
		mih_user::link_actions_confirm(msg, ec);
		break;

	case odtone::mih::confirm::event_unsubscribe:
		mih_user::link_event_unsubscribe_confirm(msg, ec);
		break;

	case odtone::mih::indication::link_parameters_report:
		mih_user::link_parameters_report(msg, ec);
		break;
	}
}

void mih_user::link_parameters_report(odtone::mih::message& msg, const boost::system::error_code& ec)
{
	odtone::mih::link_tuple_id link;
	odtone::mih::link_param_rpt_list lprl;
	odtone::mih::l2_3gpp_addr local_l2_3gpp_addr;

	msg >> odtone::mih::indication()
		   & odtone::mih::tlv_link_identifier(link)
	       & odtone::mih::tlv_link_param_rpt_list(lprl);

	log_(0, "");
	log_(0, "Link Parameters report - RECEIVED - Begin");
	local_l2_3gpp_addr = boost::get<odtone::mih::l2_3gpp_addr>(link.addr);
	print_l2_3gpp_addr(link.type, local_l2_3gpp_addr);
	log_(0, "Link Parameters report  Confirm - End");
}


void mih_user::link_event_unsubscribe_confirm(odtone::mih::message& msg, const boost::system::error_code& ec)
{
	odtone::mih::status st;
	odtone::mih::link_tuple_id link;
	boost::optional<odtone::mih::mih_evt_list> evt;

	msg >> 	odtone::mih::confirm()
			& odtone::mih::tlv_status(st)
			& odtone::mih::tlv_link_identifier(link)
			& odtone::mih::tlv_event_list(evt);

	log_(0, "");
	log_(0, "Link Unsubscribe Confirm - RECEIVED - Begin");

	if (evt) {
		log_(0, "  - MIH_EVT_LIST - Event List:");
		if(evt->get(odtone::mih::mih_evt_link_detected) == 1) {log_(0, "     - link_detected");}
		if(evt->get(odtone::mih::mih_evt_link_up) == 1){log_(0, "     - link_up ");}
		if(evt->get(odtone::mih::mih_evt_link_down) == 1){log_(0, "     - link_down ");}
		if(evt->get(odtone::mih::mih_evt_link_parameters_report) == 1){log_(0, "     - link_parameters_report");}
		if(evt->get(odtone::mih::mih_evt_link_going_down) == 1){log_(0, "     - link_going_down");}
	}

	log_(0, "Link Unsubscribe Confirm  Confirm - End");
}

void mih_user::link_event_unsubscribe(odtone::mih::message& msg, const boost::system::error_code& ec)
{
	odtone::mih::message m;

	odtone::mih::link_tuple_id link;
	odtone::mih::mih_evt_list events;
	odtone::mih::l2_3gpp_addr l2_3gpp_addr;

	link.type = rcv_link_id.type;
	//address UMTS
	link.addr = rcv_link_id.addr;

	events.set(odtone::mih::mih_evt_link_detected);
	events.set(odtone::mih::mih_evt_link_up);
	events.set(odtone::mih::mih_evt_link_down);
	events.set(odtone::mih::mih_evt_link_parameters_report);
	events.set(odtone::mih::mih_evt_link_going_down);

	m << odtone::mih::request(odtone::mih::request::event_unsubscribe)
		 & odtone::mih::tlv_link_identifier(link)
		 & odtone::mih::tlv_event_list(events);

	m.destination(msg.source());

	_mihf.async_send(m, boost::bind(&mih_user::event_handler, this, _1, _2));

	log_(0, "Event Unsubscribe Request - SENT - Begin");

	log_(0, "  - MIH_EVT_LIST - Event List:");
	if(events.get(odtone::mih::mih_evt_link_detected)) {log_(0, "     - link_detected");}
	if(events.get(odtone::mih::mih_evt_link_up)){log_(0, "     - link_up ");}
	if(events.get(odtone::mih::mih_evt_link_down)) {log_(0, "     - link_down ");}
	if(events.get(odtone::mih::mih_evt_link_parameters_report)) {log_(0, "     - link_parameters_report ");}
	if(events.get(odtone::mih::mih_evt_link_going_down)) {log_(0, "     - link_going_down ");}

	log_(0, "Event_Subscribe.request - End");
}

void mih_user::link_down_indication(odtone::mih::message& msg, const boost::system::error_code& ec)
{
	odtone::mih::link_tuple_id link;
	odtone::mih::link_dn_reason ldr;
	odtone::mih::l2_3gpp_addr local_l2_3gpp_addr;

	msg >> odtone::mih::indication()
		   & odtone::mih::tlv_link_identifier(link)
	       & odtone::mih::tlv_link_dn_reason(ldr);

	log_(0, "");
	log_(0, "Link Down Indication - RECEIVED - Begin");

	local_l2_3gpp_addr = boost::get<odtone::mih::l2_3gpp_addr>(link.addr);

	print_l2_3gpp_addr(link.type, local_l2_3gpp_addr);

    if(ldr == odtone::mih::link_dn_reason_explicit_disconnect){log_(0, "    Link down reason:  explicit disconnect");}
    if(ldr == odtone::mih::link_dn_reason_packet_timeout){log_(0, "    Link down reason:  explicit disconnect");}
    if(ldr == odtone::mih::link_dn_reason_no_resource){log_(0, "    Link down reason:  no resource");}
    if(ldr == odtone::mih::link_dn_reason_no_broadcast){log_(0, "    Link down reason:  no broadcast");}
    if(ldr == odtone::mih::link_dn_reason_authentication_failure){log_(0, "    Link down reason: authentication failure");}
    if(ldr == odtone::mih::link_dn_reason_billing_failure){log_(0, "    Link down reason: authentication failure");}

	log_(0, "Link Down Indication - End");
}

void mih_user::link_going_down(odtone::mih::message& msg, const boost::system::error_code& ec)
{
	odtone::mih::link_tuple_id link;
	odtone::mih::link_gd_reason lgd;
	odtone::mih::link_ac_ex_time ex_time;

	odtone::mih::l2_3gpp_addr local_l2_3gpp_addr;

	msg >> odtone::mih::indication()
		   & odtone::mih::tlv_link_identifier(link)
	       & odtone::mih::tlv_time_interval(ex_time)
	       & odtone::mih::tlv_link_gd_reason(lgd);

	log_(0, "");
	log_(0, "Link Going Down - RECEIVED - Begin");

    local_l2_3gpp_addr = boost::get<odtone::mih::l2_3gpp_addr>(link.addr);
	local_l2_3gpp_addr = boost::get<odtone::mih::l2_3gpp_addr>(link.addr);

	print_l2_3gpp_addr(link.type, local_l2_3gpp_addr);
	log_(0, "     Time Interval :", (ex_time/256));

    if(lgd == odtone::mih::link_gd_reason_explicit_disconnect){log_(0, "     Link going down reason:  explicit disconnect");}
    if(lgd == odtone::mih::link_gd_reason_link_parameter_degrading){log_(0, "     Link going down reason:  explicit disconnect");}
    if(lgd == odtone::mih::link_gd_reason_low_power){log_(0, "     Link going down reason:  no resource");}
    if(lgd == odtone::mih::link_gd_reason_no_resource){log_(0, "     Link going down reason:  no broadcast");}

	log_(0, "Link Going Down - End");
}

void mih_user::link_up_indication(odtone::mih::message& msg, const boost::system::error_code& ec)
{
	odtone::mih::link_tuple_id link;
	odtone::mih::l2_3gpp_addr local_l2_3gpp_addr;

	msg >> 	odtone::mih::indication()
			& odtone::mih::tlv_link_identifier(link);

	log_(0, "");
	log_(0, "Link Up Indication - RECEIVED - Begin");

	local_l2_3gpp_addr = boost::get<odtone::mih::l2_3gpp_addr>(link.addr);
	print_l2_3gpp_addr(link.type, local_l2_3gpp_addr);
	log_(0, "Link Up Indication - End");
}

void mih_user::link_actions_confirm(odtone::mih::message& msg, const boost::system::error_code& ec)
{

	log_(0, "Link_Action.confirm - RECEIVED - Begin");

	if (ec) {
		log_(0, __FUNCTION__, " error: ", ec.message());
		return;
	}

	odtone::mih::status st;
	boost::optional<odtone::mih::link_action_rsp_list> larl;
	/*odtone::mih::link_action_rsp lar;
	odtone::mih::link_scan_rsp_list lsrl;
	odtone::mih::link_scan_rsp lsr;*/

	msg >> odtone::mih::confirm()
		   & odtone::mih::tlv_status(st)
		   & odtone::mih::tlv_link_action_rsp_list(larl);

	if(st.get() == 0){
		log_(0, "  - STATUS: Success (0)");
	}
	else {log_(0, "  - STATUS: not Success (1)");}

	//if(larl){log_(0, "  - Link Action Rsp List Received");}

	log_(0, "Link_Action.confirm - End");
}

void mih_user::link_actions_request(odtone::mih::message& msg, const boost::system::error_code& ec)
{
	odtone::mih::message m;

	odtone::mih::link_action_list lal;
	odtone::mih::link_action_req link_act_req;
	odtone::mih::l2_3gpp_addr local_l2_3gpp_addr;

	//address UMTS
	link_act_req.id.type = rcv_link_id.type;
	link_act_req.id.addr = rcv_link_id.addr;

	if(mih_user::la_req == 0){
			link_act_req.action.type = odtone::mih::link_ac_type_power_up;
			link_act_req.action.attr.set(odtone::mih::link_ac_attr_scan);
	}
	if(mih_user::la_req == 1){ link_act_req.action.type = odtone::mih::link_ac_type_power_down;}

	link_act_req.ex_time = 0;

	lal.push_back(link_act_req);

	m <<  	odtone::mih::request(odtone::mih::request::link_actions)
			& odtone::mih::tlv_link_action_list(lal);

	log_(0, "");
	log_(0, "Link_Action.request - SENT - Begin");

	log_(0, "   - LINK_ID: ");
	local_l2_3gpp_addr = boost::get<odtone::mih::l2_3gpp_addr>(link_act_req.id.addr);
	print_l2_3gpp_addr(link_act_req.id.type, local_l2_3gpp_addr);

	if(link_act_req.action.type == odtone::mih::link_ac_type_power_down){ log_(0, "   - Power Down");}
	if(link_act_req.action.type == odtone::mih::link_ac_type_power_up){ log_(0, "   - Power Up");}

	if(link_act_req.action.attr.get(odtone::mih::link_ac_attr_scan) == 1){ log_(0, "   - Link Scan required");}
	log_(0, "   - Link Action ex_time: ", link_act_req.ex_time);

	m.destination(msg.source());

	_mihf.async_send(m, boost::bind(&mih_user::event_handler, this, _1, _2));

	log_(0, "Link_Action.request - End");
	log_(0, "");
}

void mih_user::link_detected(odtone::mih::message& msg, const boost::system::error_code& ec)
{
	odtone::mih::link_det_info_list ldil;

	msg >> 	odtone::mih::indication()
			& odtone::mih::tlv_link_det_info_list(ldil);

	log_(0, "");
	log_(0, "Link Detected - RECEIVED - Begin");

	log_(0, "Link Detected - End");
}

void mih_user::link_get_parameters(odtone::mih::message& msg, const boost::system::error_code& ec)
{
	odtone::mih::message m;

	odtone::mih::dev_states_req dsr;
	odtone::uint iter;

	odtone::mih::link_id li;
	odtone::mih::link_id_list lil;

	odtone::mih::link_status_req lsr;

	//set values

	dsr.set(odtone::mih::dev_state_device_info); //optional

	li.type = rcv_link_id.type;
	li.addr = rcv_link_id.addr;
    lil.push_back(li);

	odtone::mih::link_param_gen lp = odtone::mih::link_param_gen_data_rate;

	lsr._states_req.set(odtone::mih::link_states_req_op_mode);
	lsr._param_type_list.push_back(lp);
	lsr._desc_req.set(odtone::mih::link_desc_req_classes_of_service_supported);

	m << odtone::mih::request(odtone::mih::request::link_get_parameters)
			& odtone::mih::tlv_dev_states_req(dsr)
		    & odtone::mih::tlv_link_id_list(lil)
			& odtone::mih::tlv_get_status_req_set(lsr);

	m.destination(msg.source());

	_mihf.async_send(m, boost::bind(&mih_user::event_handler, this, _1, _2));

	log_(0,"");
	log_(0, "Link_Get_Parameters.request - SENT - Begin");
	//log_(0, "  - DEVICE STATES REQUEST");

	odtone::mih::l2_3gpp_addr local_l2_3gpp_addr;

	log_(0, "  - LINK ID LIST - Length: ", lil.size());

	for(iter=0; iter<lil.size(); iter++)
	{
		log_(0, "      LINK ID ", iter);
		local_l2_3gpp_addr =  boost::get<odtone::mih::l2_3gpp_addr>(lil[iter].addr);
		print_l2_3gpp_addr(lil[iter].type, local_l2_3gpp_addr);
	}

	log_(0, "  - GET STATUS REQUEST ");
	if(lsr._states_req.get(odtone::mih::link_states_req_op_mode) == 1) {log_(0, "      Link power mode requested");}
	if(lsr._states_req.get(odtone::mih::link_states_req_channel_id) == 1) {log_(0, "      Channel identifier requested (as defined in the specific link technology)");}

	if(lp == odtone::mih::link_param_gen_data_rate) {log_(0, "      DATA RATE link parameter requested");}
	if(lp == odtone::mih::link_param_gen_signal_strength) {log_(0, "      SIGNAL STRENGTH link parameter is required");}
	if(lp == odtone::mih::link_param_gen_sinr) {log_(0, "      SINR link parameter is required");}
	if(lp == odtone::mih::link_param_gen_throughput) {log_(0, "      THROUGHPUT link parameter is required");}

	log_(0, "  - LINK DESCRIPTOR REQUESTED ");

	if(lsr._desc_req.get(odtone::mih::link_desc_req_classes_of_service_supported) == 1) {log_(0, "      Number of CoS Supported ");}
	if(lsr._desc_req.get(odtone::mih::link_desc_req_queues_supported) == 1) {log_(0, "      Number of Queues Supported ");}
	log_(0, "Link_Get_Parameters.request - End");
	log_(0, "");

}

void mih_user::link_get_parameters_confirm(odtone::mih::message& msg, const boost::system::error_code& ec)
{
	log_(0, "");
	log_(0, "Link_Get_Parameters.confirm - RECEIVED - Begin");

	odtone::mih::status st;
	odtone::mih::status_rsp_list srl;

	odtone::uint iter;


	msg >> odtone::mih::confirm()
		& odtone::mih::tlv_status(st)
	    & odtone::mih::tlv_get_status_rsp_list(srl);

	if(st.get() == 0){
		log_(0, "  - STATUS: Success (0)");
	}
	else {log_(0, "  - STATUS: not Success (1)");}

	odtone::mih::l2_3gpp_addr local_l2_3gpp_addr;

	log_(0, "  - STATUS RSP LIST - Length: ", srl.size());

	for(iter=0; iter<srl.size(); iter++)
	{
		log_(0, "      LINK ID ", iter+1, ":");
		local_l2_3gpp_addr =  boost::get<odtone::mih::l2_3gpp_addr>(srl[iter].id.addr);
		print_l2_3gpp_addr(srl[iter].id.type, local_l2_3gpp_addr);
		log_(0, "      LINK STATUS RSP List - Element: ", iter+1);

		/*odtone::uint iter1;

		log_(0, "        States Rsp List - Length: ", srl[iter].rsp.states_rsp_list.size());
		//States Rsp List (vector)
		for(iter1=0; iter1<srl[iter1].rsp.states_rsp_list.size(); iter1++)
		{
			//each element op_mode or channel_id
			log_(0, "        Element:", iter1+1, " - Value:", srl[iter1].rsp.states_rsp_list[iter1]);
		}

		log_(0, "        Param List - Length: ", srl[iter].rsp.param_list.size());
		//Param List
		for(iter1=0; iter1<srl[iter1].rsp.param_list.size(); iter1++)
		{
			//log_(0, "Element:", iter+1, "Type: ", srl[iter1].rsp.param_list[iter1].type ,"Value: ", srl[iter1].rsp.param_list[iter1]);
			// 1 - link_param_type
			// 2 - boost::variant<link_param_val, qos_param_val>
		}

		log_(0, "        Desc_rsp_list - Length: ", srl[iter].rsp.desc_rsp_list.size());
		//Desc_rsp_list
		  for(iter1=0; iter1<srl[iter1].rsp.desc_rsp_list.size(); iter1++)
		  {
			//log_(0, "Element:", iter+1, "Value", srl[iter1].rsp.desc_rsp_list[iter1]);
			//boost::variant<num_cos, num_queue>
			//uint8 num_cos - uint8 num_queue
		  }*/
	}
	log_(0, "Link_Get_Parameters.confirm - End");
	log_(0, "");
}


/**
 * Capability Discover handler.
 *
 * @param msg Received message.
 * @param ec Error Code.
 */
void mih_user::capability_discover_confirm(odtone::mih::message& msg, const boost::system::error_code& ec)
{
	if (ec) {
		log_(0, __FUNCTION__, " error: ", ec.message());
		return;
	}

	odtone::mih::status st;
	boost::optional<odtone::mih::net_type_addr_list> ntal;
	boost::optional<odtone::mih::mih_evt_list> evt;

	odtone::mih::l2_3gpp_addr local_l2_3gpp_addr;
	odtone::mih::link_tuple_id li;

	msg >> odtone::mih::confirm()
		& odtone::mih::tlv_status(st)
		& odtone::mih::tlv_net_type_addr_list(ntal)
		& odtone::mih::tlv_event_list(evt);
	    // MIH_TRANS_LIST could be added

    log_(0, "Capability_Discover.confirm - RECEIVED - Begin");

	if(st.get() == 0){
		log_(0, "  - STATUS: Success (0)");
	}
	else {log_(0, "  - STATUS: Not Success");}

	if (evt) {
		log_(0, "  - MIH_EVT_LIST - Event List:");
		if(evt->get(odtone::mih::mih_evt_link_detected) == 1) {log_(0, "     - link_detected");}
		if(evt->get(odtone::mih::mih_evt_link_up) == 1){log_(0, "     - link_up ");}
		if(evt->get(odtone::mih::mih_evt_link_down) == 1){log_(0, "     - link_down ");}
		if(evt->get(odtone::mih::mih_evt_link_going_down) == 1){log_(0, "     - link_going_down");}
		if(evt->get(odtone::mih::mih_evt_link_parameters_report) == 1){log_(0, "     - link_parameters_report");}
	}

	//log_(0, "MIH-User has received a Capability_Discover.response with status ",
	//		st.get(), " and the following capabilities:");

	log_(0, "  - LIST(NET_TYPE_ADDR) - Network Types and Link Address:");

	if (ntal) {
		for (odtone::mih::net_type_addr_list::iterator i = ntal->begin(); i != ntal->end(); ++i)
		{
			local_l2_3gpp_addr = boost::get<odtone::mih::l2_3gpp_addr>(i->addr);
			li.type = boost::get<odtone::mih::link_type>(i->nettype.link);

			rcv_net_type_addr.addr = boost::get<odtone::mih::l2_3gpp_addr>(i->addr);
			rcv_net_type_addr.nettype.link = boost::get<odtone::mih::link_type>(i->nettype.link);

			rcv_link_id.addr = boost::get<odtone::mih::l2_3gpp_addr>(i->addr);
			rcv_link_id.type = boost::get<odtone::mih::link_type>(i->nettype.link);

			print_l2_3gpp_addr(li.type, local_l2_3gpp_addr);

			//log_(0,  *i);
		}

	} else {
		log_(0,  "none");
	}

	log_(0, "");
	//
	// event subscription
	//
	// For every interface the MIHF sent in the
	// Capability_Discover.response send an Event_Subscribe.request
	// for all availabe events
	//
	if (ntal && evt) {
		for (odtone::mih::net_type_addr_list::iterator i = ntal->begin(); i != ntal->end(); ++i) {
			odtone::mih::message req;
			odtone::mih::link_tuple_id li;

			if (i->nettype.link.which() == 1)
				{
					li.addr = i->addr;
					li.type = boost::get<odtone::mih::link_type>(i->nettype.link);

					req << odtone::mih::request(odtone::mih::request::event_subscribe, _mihfid)
						& odtone::mih::tlv_link_identifier(li)
						& odtone::mih::tlv_event_list(evt);

					req.destination(msg.source());

					_mihf.async_send(req, boost::bind(&mih_user::event_subscribe_response, this, _1, _2));

					log_(0, "MIH-User has sent Event_Subscribe.request to ", req.destination().to_string());

					if (evt) {
						log_(0, "  - MIH_EVT_LIST - Event List:");
						if(evt->get(odtone::mih::mih_evt_link_detected) == 1) {log_(0, "     - link_detected");}
						if(evt->get(odtone::mih::mih_evt_link_up) == 1){log_(0, "     - link_up ");}
						if(evt->get(odtone::mih::mih_evt_link_down) == 1){log_(0, "     - link_down ");}
						if(evt->get(odtone::mih::mih_evt_link_going_down) == 1){log_(0, "     - link_going_down");}
						if(evt->get(odtone::mih::mih_evt_link_parameters_report) == 1){log_(0, "     - link_parameters_report");}
					}

				}
		}
	}
}

/**
 * Event subscribe handler.
 *
 * @param msg Received message.
 * @param ec Error Code.
 */
void mih_user::event_subscribe_response(odtone::mih::message& msg, const boost::system::error_code& ec)
{
	log_(0, __FUNCTION__, "(", msg.tid(), ")");

	if (ec) {
		log_(0, __FUNCTION__, " error: ", ec.message());
		return;
	}

	odtone::mih::status st;

	msg >> odtone::mih::response()
		& odtone::mih::tlv_status(st);

	log_(0, "status: ", st.get());

	mih_user::link_configure_thresholds(msg, ec);
}

void mih_user::link_configure_thresholds(odtone::mih::message& msg, const boost::system::error_code& ec)
{
	odtone::mih::message m;

	odtone::mih::threshold th;
	std::vector<odtone::mih::threshold> thl;

	odtone::mih::link_tuple_id lti;
	odtone::mih::l2_3gpp_addr local_l2_3gpp_addr;

	//link_tuple_id
	lti.type = rcv_link_id.type;
	lti.addr = rcv_link_id.addr;

	local_l2_3gpp_addr = boost::get<odtone::mih::l2_3gpp_addr>(lti.addr);

	//List of the link threshold parameters
	odtone::mih::link_cfg_param_list lcpl;
	odtone::mih::link_cfg_param lcp;
	odtone::mih::link_param_gen lp;

	lp = odtone::mih::link_param_gen_data_rate;

	lcp.type = lp;
	//0-set normal threshold; 1-set one shot threshold; 2-cancel threshold
	lcp.action = odtone::mih::th_action_normal;

	th.threshold_val = THRESHOLD_VAL;
	th.threshold_x_dir = odtone::mih::threshold::below_threshold;

	thl.push_back(th);
	lcp.threshold_list = thl;
	lcpl.push_back(lcp);

	m <<  odtone::mih::request(odtone::mih::request::link_configure_thresholds)
	      & odtone::mih::tlv_link_identifier(lti)
	      & odtone::mih::tlv_link_cfg_param_list(lcpl);

	m.destination(msg.source());

	_mihf.async_send(m, boost::bind(&mih_user::event_handler, this, _1, _2));

	log_(0,"");
	log_(0, "Link_Configure_Thresholds - SENT - Begin");

	log_(0, "  - LINK TUPLE ID - Network Types and Link Address:");
	print_l2_3gpp_addr(lti.type, local_l2_3gpp_addr);

	log_(0, "  - LINK CFG PARAM LIST - Length: ", lcpl.size());

	if(lp == odtone::mih::link_param_gen_data_rate) {log_(0, "     Generic link parameter DATA RATE ");}
	if(lp == odtone::mih::link_param_gen_signal_strength) {log_(0, "     Generic link parameter SIGNAL STRENGTH");}
	if(lp == odtone::mih::link_param_gen_sinr) {log_(0, "     Generic link parameter SINR");}
	if(lp == odtone::mih::link_param_gen_throughput) {log_(0, "     Generic link parameter THROUGHPUT");}

	if(lcp.action == odtone::mih::th_action_normal) {log_(0, "     Normal Threshold");}
	if(lcp.action == odtone::mih::th_action_one_shot) {log_(0, "     One Shot Threshold");}
	if(lcp.action == odtone::mih::th_action_cancel) {log_(0, "     Threshold to be canceled");}

	log_(0, "     Threshold value: ", th.threshold_val);

	if(th.threshold_x_dir == odtone::mih::threshold::below_threshold) {log_(0, "     Threshold direction BELOW");}
	if(th.threshold_x_dir == odtone::mih::threshold::above_threshold) {log_(0, "     Threshold direction ABOVE");}

	log_(0, "Link_Configure_Thresholds - End");
	log_(0,"");
}

void mih_user::link_configure_thresholds_confirm(odtone::mih::message& msg, const boost::system::error_code& ec)
{
	log_(0, "");
	log_(0, "Link Configure Thresholds Confirm - RECEIVED - Begin");

	odtone::uint iter;
	odtone::mih::status st;

	//boost::optional<odtone::mih::link_cfg_status_list> lcsl;
	odtone::mih::link_cfg_status_list lcsl;
	odtone::mih::link_cfg_status lcp;
	odtone::mih::link_param_gen lp;

	odtone::mih::link_tuple_id lti;

	msg >> odtone::mih::confirm()
		& odtone::mih::tlv_status(st)
	    & odtone::mih::tlv_link_identifier(lti)
	    & odtone::mih::tlv_link_cfg_status_list(lcsl);

	if(st.get() == 0){
		log_(0, "  - STATUS: Success (0)");
	}
	else {log_(0, "  - STATUS: not Success (1)");}

	log_(0, "  - LINK CFG STATUS LIST - Length: ", lcsl.size());

	for(iter=0; iter<lcsl.size(); iter++)
	{
		log_(0, "     Link Param Type: ", lcsl[0].type);
		log_(0, "     Threshold Val: ", (lcsl[0].thold.threshold_val/256));
		if(lcsl[0].thold.threshold_x_dir == odtone::mih::threshold::below_threshold) {log_(0, "     Threshold direction BELOW");}
		if(lcsl[0].thold.threshold_x_dir == odtone::mih::threshold::above_threshold) {log_(0, "     Threshold direction ABOVE");}
		if(lcsl[0].status == odtone::mih::status_success){log_(0, "     Config Status: Success ");}
		else {log_(0, "     Config Status: ", lcsl[0].status);}
	}

	log_(0, "Link Configure Thresholds Confirm - End");
	log_(0,"");
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
			(odtone::sap::kConf_File, po::value<std::string>()->default_value("mih_usr.conf"), "Configuration file")
			(odtone::sap::kConf_Receive_Buffer_Len, po::value<uint>()->default_value(4096), "Receive buffer length")
			(odtone::sap::kConf_Port, po::value<ushort>()->default_value(1234), "Listening port")
			(odtone::sap::kConf_MIH_SAP_id, po::value<std::string>()->default_value("user"), "MIH-User ID")
			(kConf_MIH_Commands, po::value<std::string>()->default_value(""), "MIH-User supported commands")
			(odtone::sap::kConf_MIHF_Ip, po::value<std::string>()->default_value("127.0.0.1"), "Local MIHF IP address")
			(odtone::sap::kConf_MIHF_Local_Port, po::value<ushort>()->default_value(1025), "Local MIHF communication port")
			(odtone::sap::kConf_MIH_SAP_dest, po::value<std::string>()->default_value(""), "MIHF destination");

		odtone::mih::config cfg(desc);
		cfg.parse(argc, argv, odtone::sap::kConf_File);

		if (cfg.help()) {
			std::cerr << desc << std::endl;
			return EXIT_SUCCESS;
		}

		mih_user usr(cfg, ios);

		ios.run();

	} catch(std::exception& e) {
		log_(0, "exception: ", e.what());
	}
}

// EOF ////////////////////////////////////////////////////////////////////////
