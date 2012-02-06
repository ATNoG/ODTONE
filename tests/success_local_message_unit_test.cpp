//==============================================================================
// Brief   : Successful local message exchange unit test
// Authors : Carlos Guimarães <cguimaraes@av.it.pt>
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

/*
 * Expected output (2 times):
 * success_unit_test: has received a "MIH_Capability_Discover.request"
 * success_unit_test: Send MIH_Capability_Discover.request
 * success_unit_test: has received a "MIH_Capability_Discover.confirm"
 * success_unit_test: Send MIH_Event_Subscribe.request
 * success_unit_test: has received a "MIH_Event_Subscribe.request"
 * success_unit_test: has received a "MIH_Event_Subscribe.confirm"
 * success_unit_test: Send MIH_Link_Up.indication
 * success_unit_test: has received a "MIH_Link_Up.indication"
 * success_unit_test: Send MIH_Link_Down.indication
 * success_unit_test: Send MIH_Event_Unsubscribe.request
 * success_unit_test: has received a "MIH_Event_Unsubscribe.request"
 * success_unit_test: has received a "MIH_Event_Unsubscribe.confirm"
 * success_unit_test: Send MIH_Link_Up.indication
 * success_unit_test: Send MIH_Link_Down.indication
 * success_unit_test: Send MIH_Link_Get_Parameters.request
 * success_unit_test: has received a "MIH_Link_Get_Parameters.request"
 * success_unit_test: has received a "MIH_Link_Get_Parameters.confirm"
 * success_unit_test: Send MIH_Link_Actions.request
 * success_unit_test: has received a "MIH_Link_Actions.request"
 * success_unit_test: has received a "MIH_Link_Actions.confirm"
 * success_unit_test: Send MIH_Link_Actions.request with PoA
 * success_unit_test: has received a "MIH_Link_Actions.request"
 * success_unit_test: has PoA TLV!
 * success_unit_test: has received a "MIH_Link_Actions.confirm"
 * success_unit_test: Send MIH_Link_Configure_Thresholds.request
 * success_unit_test: has received a "MIH_Link_Configure_Thresholds.request"
 * success_unit_test: has received a "MIH_Link_Configure_Thresholds.confirm"
 */

#include <iostream>

#include "lib/sap.hpp"

#include <odtone/base.hpp>
#include <odtone/debug.hpp>
#include <odtone/logger.hpp>
#include <odtone/mih/request.hpp>
#include <odtone/mih/response.hpp>
#include <odtone/mih/indication.hpp>
#include <odtone/mih/confirm.hpp>
#include <odtone/mih/tlv_types.hpp>

#include <boost/utility.hpp>
#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace po = boost::program_options;

odtone::logger log_("success_unit_test", std::cout);

///////////////////////////////////////////////////////////////////////////////
namespace odtone {

///////////////////////////////////////////////////////////////////////////////
class message_unit_test : boost::noncopyable {
public:

	message_unit_test(const mih::config& cfg, boost::asio::io_service& io);

	~message_unit_test();

protected:

	void event_handler(mih::message& msg, const boost::system::error_code& ec);

	void send_capability_discover();
	void send_event_subscribe();
	void send_event_unsubscribe();
	void send_link_get_parameters();
	void send_link_actions();
	void send_link_actions_with_poa();
	void send_link_configure_thresholds();
	void send_link_up();
	void send_link_down();


private:
	test::test	_mihf;
	std::map<uint16, boost::shared_ptr<boost::asio::deadline_timer> > _timer;
};

message_unit_test::message_unit_test(const mih::config& cfg, boost::asio::io_service& io)
	: _mihf(io, cfg, boost::bind(&message_unit_test::event_handler, this, _1, _2))
{
	// Register MIH-User
	mih::message user_message;
	user_message << mih::indication(mih::indication::user_register, mih::id("mihf1"));
	_mihf.async_send_mihf1(user_message);

	// Register Link SAP
	mih::link_id lid;
	lid.type = mih::link_type_802_11;
	mih::mac_addr mac;
	mac.address("00:11:22:33:44:55");
	lid.addr = mac;

	mih::message link_message;
	link_message << mih::indication(mih::indication::link_register, mih::id("mihf1"))
	    & mih::tlv_interface_type_addr(lid);
	_mihf.async_send_mihf1(link_message);

	// Set the timers to send the messages

	// MIH_Capability_Discover
	{
		boost::shared_ptr<boost::asio::deadline_timer> timer = boost::make_shared<boost::asio::deadline_timer>(io);
		timer->expires_from_now(boost::posix_time::milliseconds(1000));
		timer->async_wait(boost::bind(&message_unit_test::send_capability_discover, this));
		_timer[55] = timer;
	}

	//	MIH_Event_Subscribe
	{
		boost::shared_ptr<boost::asio::deadline_timer> timer = boost::make_shared<boost::asio::deadline_timer>(io);
		timer->expires_from_now(boost::posix_time::milliseconds(2000));
		timer->async_wait(boost::bind(&message_unit_test::send_event_subscribe, this));
		_timer[126] = timer;
	}

	//	MIH_Link_Up
	{
		boost::shared_ptr<boost::asio::deadline_timer> timer = boost::make_shared<boost::asio::deadline_timer>(io);
		timer->expires_from_now(boost::posix_time::milliseconds(3000));
		timer->async_wait(boost::bind(&message_unit_test::send_link_up, this));
		_timer[33] = timer;
	}

	//	MIH_Link_Down
	{
		boost::shared_ptr<boost::asio::deadline_timer> timer = boost::make_shared<boost::asio::deadline_timer>(io);
		timer->expires_from_now(boost::posix_time::milliseconds(4000));
		timer->async_wait(boost::bind(&message_unit_test::send_link_down, this));
		_timer[77] = timer;
	}

	//	MIH_Event_Unsubscribe
	{
		boost::shared_ptr<boost::asio::deadline_timer> timer = boost::make_shared<boost::asio::deadline_timer>(io);
		timer->expires_from_now(boost::posix_time::milliseconds(5000));
		timer->async_wait(boost::bind(&message_unit_test::send_event_unsubscribe, this));
		_timer[129] = timer;
	}

	//	MIH_Link_Up
	{
		boost::shared_ptr<boost::asio::deadline_timer> timer = boost::make_shared<boost::asio::deadline_timer>(io);
		timer->expires_from_now(boost::posix_time::milliseconds(6000));
		timer->async_wait(boost::bind(&message_unit_test::send_link_up, this));
		_timer[34] = timer;
	}

	//	MIH_Link_Down
	{
		boost::shared_ptr<boost::asio::deadline_timer> timer = boost::make_shared<boost::asio::deadline_timer>(io);
		timer->expires_from_now(boost::posix_time::milliseconds(7000));
		timer->async_wait(boost::bind(&message_unit_test::send_link_down, this));
		_timer[78] = timer;
	}

	//	MIH_Link_Get_Parameters
	{
		boost::shared_ptr<boost::asio::deadline_timer> timer = boost::make_shared<boost::asio::deadline_timer>(io);
		timer->expires_from_now(boost::posix_time::milliseconds(8000));
		timer->async_wait(boost::bind(&message_unit_test::send_link_get_parameters, this));
		_timer[321] = timer;
	}

	//	MIH_Link_Actions
	{
		boost::shared_ptr<boost::asio::deadline_timer> timer = boost::make_shared<boost::asio::deadline_timer>(io);
		timer->expires_from_now(boost::posix_time::milliseconds(9000));
		timer->async_wait(boost::bind(&message_unit_test::send_link_actions, this));
		_timer[654] = timer;
	}
	{
		boost::shared_ptr<boost::asio::deadline_timer> timer = boost::make_shared<boost::asio::deadline_timer>(io);
		timer->expires_from_now(boost::posix_time::milliseconds(10000));
		timer->async_wait(boost::bind(&message_unit_test::send_link_actions_with_poa, this));
		_timer[555] = timer;
	}

	//	MIH_Link_Configure_Thresholds
	{
		boost::shared_ptr<boost::asio::deadline_timer> timer = boost::make_shared<boost::asio::deadline_timer>(io);
		timer->expires_from_now(boost::posix_time::milliseconds(11000));
		timer->async_wait(boost::bind(&message_unit_test::send_link_configure_thresholds, this));
		_timer[999] = timer;
	}

	// Repeat the tests in order to check if the local transactions have been
	// removed

	// MIH_Capability_Discover
	{
		boost::shared_ptr<boost::asio::deadline_timer> timer = boost::make_shared<boost::asio::deadline_timer>(io);
		timer->expires_from_now(boost::posix_time::milliseconds(13000));
		timer->async_wait(boost::bind(&message_unit_test::send_capability_discover, this));
		_timer[1] = timer;
	}

	//	MIH_Event_Subscribe
	{
		boost::shared_ptr<boost::asio::deadline_timer> timer = boost::make_shared<boost::asio::deadline_timer>(io);
		timer->expires_from_now(boost::posix_time::milliseconds(14000));
		timer->async_wait(boost::bind(&message_unit_test::send_event_subscribe, this));
		_timer[2] = timer;
	}

	//	MIH_Link_Up
	{
		boost::shared_ptr<boost::asio::deadline_timer> timer = boost::make_shared<boost::asio::deadline_timer>(io);
		timer->expires_from_now(boost::posix_time::milliseconds(15000));
		timer->async_wait(boost::bind(&message_unit_test::send_link_up, this));
		_timer[3] = timer;
	}

	//	MIH_Link_Down
	{
		boost::shared_ptr<boost::asio::deadline_timer> timer = boost::make_shared<boost::asio::deadline_timer>(io);
		timer->expires_from_now(boost::posix_time::milliseconds(16000));
		timer->async_wait(boost::bind(&message_unit_test::send_link_down, this));
		_timer[4] = timer;
	}

	//	MIH_Event_Unsubscribe
	{
		boost::shared_ptr<boost::asio::deadline_timer> timer = boost::make_shared<boost::asio::deadline_timer>(io);
		timer->expires_from_now(boost::posix_time::milliseconds(17000));
		timer->async_wait(boost::bind(&message_unit_test::send_event_unsubscribe, this));
		_timer[5] = timer;
	}

	//	MIH_Link_Up
	{
		boost::shared_ptr<boost::asio::deadline_timer> timer = boost::make_shared<boost::asio::deadline_timer>(io);
		timer->expires_from_now(boost::posix_time::milliseconds(18000));
		timer->async_wait(boost::bind(&message_unit_test::send_link_up, this));
		_timer[6] = timer;
	}

	//	MIH_Link_Down
	{
		boost::shared_ptr<boost::asio::deadline_timer> timer = boost::make_shared<boost::asio::deadline_timer>(io);
		timer->expires_from_now(boost::posix_time::milliseconds(19000));
		timer->async_wait(boost::bind(&message_unit_test::send_link_down, this));
		_timer[7] = timer;
	}

	//	MIH_Link_Get_Parameters
	{
		boost::shared_ptr<boost::asio::deadline_timer> timer = boost::make_shared<boost::asio::deadline_timer>(io);
		timer->expires_from_now(boost::posix_time::milliseconds(20000));
		timer->async_wait(boost::bind(&message_unit_test::send_link_get_parameters, this));
		_timer[8] = timer;
	}

	//	MIH_Link_Actions
	{
		boost::shared_ptr<boost::asio::deadline_timer> timer = boost::make_shared<boost::asio::deadline_timer>(io);
		timer->expires_from_now(boost::posix_time::milliseconds(21000));
		timer->async_wait(boost::bind(&message_unit_test::send_link_actions, this));
		_timer[9] = timer;
	}
	{
		boost::shared_ptr<boost::asio::deadline_timer> timer = boost::make_shared<boost::asio::deadline_timer>(io);
		timer->expires_from_now(boost::posix_time::milliseconds(22000));
		timer->async_wait(boost::bind(&message_unit_test::send_link_actions_with_poa, this));
		_timer[10] = timer;
	}

	//	MIH_Link_Configure_Thresholds
	{
		boost::shared_ptr<boost::asio::deadline_timer> timer = boost::make_shared<boost::asio::deadline_timer>(io);
		timer->expires_from_now(boost::posix_time::milliseconds(23000));
		timer->async_wait(boost::bind(&message_unit_test::send_link_configure_thresholds, this));
		_timer[11] = timer;
	}
}

message_unit_test::~message_unit_test()
{
}

void message_unit_test::event_handler(mih::message& msg, const boost::system::error_code& ec)
{
	if (ec) {
		log_(0, __FUNCTION__, " error: ", ec.message());
		return;
	}

	switch (msg.mid()) {

		// MIH_Capability_Discover
		case mih::request::capability_discover: {
			log_(0, "has received a \"MIH_Capability_Discover.request\"");

			if(msg.source().to_string().compare("mihf1") != 0) {
				log_(0, "Error!");
				return;
			}

			mih::message 		rsp;
			mih::link_evt_list	capabilities_event_list;
			mih::link_cmd_list	capabilities_command_list;

			capabilities_event_list.set(mih::evt_link_up);
			capabilities_command_list.set(mih::cmd_link_get_parameters);

			rsp << mih::confirm(mih::confirm::capability_discover, mih::id("mihf1"))
				& mih::tlv_status(mih::status_success)
				& mih::tlv_link_evt_list(capabilities_event_list)
				& mih::tlv_link_cmd_list(capabilities_command_list);
			rsp.tid(msg.tid());

			_mihf.async_send_mihf1(rsp);
	} break;

	case mih::confirm::capability_discover: {
		log_(0, "has received a \"MIH_Capability_Discover.confirm\"");

			if(msg.source().to_string().compare("mihf1") != 0 || msg.tid() != 55) {
				log_(0, "Error!");
				return;
			}

			mih::status									st;
			boost::optional<mih::net_type_addr_list>	capabilities_list_net_type_addr;
			boost::optional<mih::mih_evt_list>			capabilities_event_list;
			boost::optional<mih::mih_cmd_list>			capabilities_cmd_list;
			boost::optional<mih::iq_type_list>			capabilities_query_type;
			boost::optional<mih::transport_list>		capabilities_trans_list;
			boost::optional<mih::mbb_ho_supp_list>		capabilities_mbb_ho_supp;

			msg >> mih::confirm(mih::confirm::capability_discover)
				& mih::tlv_status(st)
				& mih::tlv_net_type_addr_list(capabilities_list_net_type_addr)
				& mih::tlv_event_list(capabilities_event_list)
				& mih::tlv_command_list(capabilities_cmd_list)
				& mih::tlv_query_type_list(capabilities_query_type)
				& mih::tlv_transport_option_list(capabilities_trans_list)
				& mih::tlv_mbb_ho_supp_list(capabilities_mbb_ho_supp);

			if(st != mih::status_success) {
				log_(0, "Error!");
				return;
			}

			if(capabilities_event_list.get().get(mih::mih_evt_link_up) == 0
				&& capabilities_event_list.get().get(mih::mih_evt_link_down) == 1) {
				log_(0, "Error!");
				return;
			}

			if(!capabilities_trans_list.is_initialized()
				|| !capabilities_list_net_type_addr.is_initialized()) {
				log_(0, "Error!");
				return;
			}
	} break;
	//

	// MIH_Event_Subscribe
	case mih::request::event_subscribe: {
		log_(0, "has received a \"MIH_Event_Subscribe.request\"");

		if(msg.source().to_string().compare("mihf1") != 0) {
			log_(0, "Error!");
			return;
		}

		mih::link_evt_list event_list;

		msg >> mih::request(mih::request::event_subscribe)
			& mih::tlv_link_evt_list(event_list);

		mih::message rsp;

		rsp << mih::confirm(mih::confirm::event_subscribe, mih::id("mihf1"))
			& mih::tlv_status(mih::status_success)
			& mih::tlv_link_evt_list(event_list);
		rsp.tid(msg.tid());

		_mihf.async_send_mihf1(rsp);

	} break;

	case mih::confirm::event_subscribe: {
		log_(0, "has received a \"MIH_Event_Subscribe.confirm\"");

		if(msg.source().to_string().compare("mihf1") != 0 || msg.tid() != 126) {
			log_(0, "Error!");
			return;
		}

		mih::status							st;
		mih::link_tuple_id					lid;
		boost::optional<mih::mih_evt_list>	event_list;

		msg >> mih::confirm(mih::confirm::event_subscribe)
			& mih::tlv_status(st)
			& mih::tlv_link_identifier(lid)
			& mih::tlv_event_list(event_list);

		if(st != mih::status_success) {
			log_(0, "Error!");
			return;
		}

		mih::mac_addr mac = boost::get<mih::mac_addr>(lid.addr);
		mih::mac_addr other;
		other.address("00:11:22:33:44:55");
		if(!(mac == other)) {
			log_(0, "Error!");
			return;
		}

		if(event_list.get().get(mih::mih_evt_link_up) == 0
			&& event_list.get().get(mih::mih_evt_link_down) == 1) {
			log_(0, "Error!");
			return;
		}

	} break;
	//

	// MIH_Event_Unsubscribe
	case mih::request::event_unsubscribe: {
		log_(0, "has received a \"MIH_Event_Unsubscribe.request\"");

		if(msg.source().to_string().compare("mihf1") != 0) {
			log_(0, "Error!");
			return;
		}

		mih::link_evt_list event_list;

		msg >> mih::request(mih::request::event_unsubscribe)
			& mih::tlv_link_evt_list(event_list);

		mih::message rsp;

		rsp << mih::confirm(mih::confirm::event_unsubscribe, mih::id("mihf1"))
			& mih::tlv_status(mih::status_success)
			& mih::tlv_link_evt_list(event_list);
		rsp.tid(msg.tid());

		_mihf.async_send_mihf1(rsp);

	} break;

	case mih::confirm::event_unsubscribe: {
		log_(0, "has received a \"MIH_Event_Unsubscribe.confirm\"");

		if(msg.source().to_string().compare("mihf1") != 0 || msg.tid() != 219) {
			log_(0, "Error!");
			return;
		}

		mih::status							st;
		mih::link_tuple_id					lid;
		boost::optional<mih::mih_evt_list>	event_list;

		msg >> mih::confirm(mih::confirm::event_unsubscribe)
			& mih::tlv_status(st)
			& mih::tlv_link_identifier(lid)
			& mih::tlv_event_list(event_list);

		if(st != mih::status_success) {
			log_(0, "Error!");
			return;
		}

		mih::mac_addr mac = boost::get<mih::mac_addr>(lid.addr);
		mih::mac_addr other;
		other.address("00:11:22:33:44:55");
		if(!(mac == other)) {
			log_(0, "Error!");
			return;
		}

		if(event_list.get().get(mih::mih_evt_link_up) == 0
			&& event_list.get().get(mih::mih_evt_link_down) == 1) {
			log_(0, "Error!");
			return;
		}

	} break;
	//

	// MIH_Link_Get_Parameters
	case mih::request::link_get_parameters: {
		log_(0, "has received a \"MIH_Link_Get_Parameters.request\"");

		if(msg.source().to_string().compare("mihf1") != 0) {
			log_(0, "Error!");
			return;
		}

		mih::link_param_type_list lptl;
		mih::link_states_req      lsr;
		mih::link_desc_req        ldr;

		msg >> mih::request(mih::request::link_get_parameters)
			& mih::tlv_link_parameters_req(lptl)
		    & mih::tlv_link_states_req(lsr)
		    & mih::tlv_link_descriptor_req(ldr);

		mih::message rsp;
		mih::link_param_list lpl;
		mih::link_states_rsp_list lsrl;
		mih::link_desc_rsp_list ldrl;

		mih::link_param lp;
		mih::link_param_val val = 3;
		mih::link_param_802_11 type;
		type = mih::link_param_802_11_no_qos;
		lp.type = type;
		lp.value = val;

		lpl.push_back(lp);

		rsp << mih::confirm(mih::confirm::link_get_parameters, mih::id("mihf1"))
			& mih::tlv_status(mih::status_success)
			& mih::tlv_link_parameters_status_list(lpl)
			& mih::tlv_link_states_rsp(lsrl)
			& mih::tlv_link_descriptor_rsp(ldrl);
		rsp.tid(msg.tid());

		_mihf.async_send_mihf1(rsp);

	} break;

	case mih::confirm::link_get_parameters: {
		log_(0, "has received a \"MIH_Link_Get_Parameters.confirm\"");

		if(msg.source().to_string().compare("mihf1") != 0 || msg.tid() != 321) {
			log_(0, "Error!");
			return;
		}

		mih::status									st;
		boost::optional<mih::dev_states_rsp_list>	dsrl;
		boost::optional<mih::status_rsp_list>		srl;

		msg >> mih::confirm(mih::confirm::link_get_parameters)
			& mih::tlv_status(st)
			& mih::tlv_dev_states_rsp_list(dsrl)
			& mih::tlv_get_status_rsp_list(srl);

		if(st != mih::status_success) {
			log_(0, "Error!");
			return;
		}

		if(!srl.is_initialized()) {
			log_(0, "Error!");
			return;
		}

	} break;
	//

	// MIH_Link_Action
	case mih::request::link_actions: {
		log_(0, "has received a \"MIH_Link_Actions.request\"");

		if(msg.source().to_string().compare("mihf1") != 0) {
			log_(0, "Error!");
			return;
		}

		mih::link_action action;
		uint16 time;
		boost::optional<mih::link_addr> addr;

		msg >> mih::request(mih::request::link_actions)
		   & mih::tlv_link_action(action)
		   & mih::tlv_time_interval(time)
		   & mih::tlv_poa(addr);

		if(addr.is_initialized())
			log_(0, "has PoA TLV!");

		mih::message rsp;
		mih::link_scan_rsp_list lsrl;
		mih::link_ac_result lar;

		rsp << mih::confirm(mih::confirm::link_actions, mih::id("mihf1"))
			& mih::tlv_status(mih::status_success)
			& mih::tlv_link_scan_rsp_list(lsrl)
			& mih::tlv_link_ac_result(lar);
		rsp.tid(msg.tid());

		_mihf.async_send_mihf1(rsp);

	} break;

	case mih::confirm::link_actions: {
		log_(0, "has received a \"MIH_Link_Actions.confirm\"");

		if(msg.source().to_string().compare("mihf1") != 0
			|| (msg.tid() != 654 && msg.tid() != 555)) {
			log_(0, "Error!");
			return;
		}

		mih::status									st;
		boost::optional<mih::link_action_rsp_list>	larl;

		msg >> mih::confirm(mih::confirm::link_actions)
			& mih::tlv_status(st)
			& mih::tlv_link_action_rsp_list(larl);

		if(st != mih::status_success) {
			log_(0, "Error!");
			return;
		}

		if(!larl.is_initialized()) {
			log_(0, "Error!");
			return;
		}

	} break;
	//

	// MIH_Configure_Thresholds
	case mih::request::link_configure_thresholds: {
		log_(0, "has received a \"MIH_Link_Configure_Thresholds.request\"");

		if(msg.source().to_string().compare("mihf1") != 0) {
			log_(0, "Error!");
			return;
		}

		mih::link_cfg_param_list lcpl;

		msg >> mih::request(mih::request::link_configure_thresholds)
			   & mih::tlv_link_cfg_param_list(lcpl);

		mih::message rsp;
		mih::link_cfg_status_list lcsl;

		rsp << mih::confirm(mih::confirm::link_configure_thresholds, mih::id("mihf1"))
			& mih::tlv_status(mih::status_success)
			& mih::tlv_link_cfg_status_list(lcsl);
		rsp.tid(msg.tid());

		_mihf.async_send_mihf1(rsp);

	} break;

	case mih::confirm::link_configure_thresholds: {
		log_(0, "has received a \"MIH_Link_Configure_Thresholds.confirm\"");

		if(msg.source().to_string().compare("mihf1") != 0 || msg.tid() != 999) {
			log_(0, "Error!");
			return;
		}

		mih::status									st;
		mih::link_tuple_id							lid;
		boost::optional<mih::link_cfg_status_list>	lcsl;

		msg >> mih::confirm(mih::confirm::link_configure_thresholds)
			& mih::tlv_status(st)
			& mih::tlv_link_identifier(lid)
			& mih::tlv_link_cfg_status_list(lcsl);

		if(st != mih::status_success) {
			log_(0, "Error!");
			return;
		}

		mih::mac_addr mac = boost::get<mih::mac_addr>(lid.addr);
		mih::mac_addr other;
		other.address("00:11:22:33:44:55");
		if(!(mac == other)) {
			log_(0, "Error!");
			return;
		}

		if(!lcsl.is_initialized()) {
			log_(0, "Error!");
			return;
		}

	} break;
	//

	// MIH_Event_Link_Up
	case mih::indication::link_up: {
		log_(0, "has received a \"MIH_Link_Up.indication\"");

		if(msg.source().to_string().compare("mihf1") != 0 || msg.tid() != 33) {
			log_(0, "Error!");
			return;
		}

		mih::link_tuple_id					lid;
		boost::optional<mih::link_addr>		new_ar;
		boost::optional<mih::link_addr>		old_ar;
		boost::optional<bool>						renewal;
		boost::optional<mih::ip_mob_mgmt>	mob;

		msg >> mih::indication(mih::indication::link_up)
			& mih::tlv_link_identifier(lid)
			& mih::tlv_old_access_router(new_ar)
			& mih::tlv_new_access_router(old_ar)
			& mih::tlv_ip_renewal_flag(renewal)
			& mih::tlv_ip_mob_mgmt(mob);

		mih::mac_addr other;
		other.address("00:11:22:33:44:55");
		{
			mih::mac_addr mac = boost::get<mih::mac_addr>(lid.addr);
			if(!(mac == other)) {
				log_(0, "Error!");
				return;
			}
		}

		{
			mih::mac_addr mac = boost::get<mih::mac_addr>(new_ar.get());
			if(!(mac == other)) {
				log_(0, "Error!");
				return;
			}
		}

		{
			mih::mac_addr mac = boost::get<mih::mac_addr>(old_ar.get());
			if(!(mac == other)) {
				log_(0, "Error!");
				return;
			}
		}

		if(!renewal) {
			log_(0, "Error!");
			return;
		}

		if(mob.get().get(mih::ip_mob_ipv6) == 0
			&& mob.get().get(mih::ip_mob_ipv4) == 1) {
			log_(0, "Error!");
			return;
		}

	} break;
	//

	// MIH_Event_Link_Down
	case mih::indication::link_down:
		log_(0, "has received a \"MIH_Link_Down\"");
		break;
	//

	case mih::indication::link_detected:
		log_(0, "has received a local event \"mih_link_detected\"");
		break;

	case mih::indication::link_going_down:
		log_(0, "has received a local event \"mih_link_going_down\"");
		break;

	case mih::indication::link_handover_imminent:
		log_(0, "has received a local event \"mih_link_handover_imminent\"");
		break;

	case mih::indication::link_handover_complete:
		log_(0, "has received a local event \"mih_link_handover_complete\"");
		break;
	}
}

void message_unit_test::send_capability_discover()
{
	log_(0, "Send MIH_Capability_Discover.request");

	mih::message 		req;

	req << mih::request(mih::request::capability_discover, mih::id("mihf1"));
	req.tid(55);

	_mihf.async_send_mihf1(req);
}

void message_unit_test::send_event_subscribe()
{
	log_(0, "Send MIH_Event_Subscribe.request");

	mih::message		req;
	mih::link_tuple_id	lid;
	mih::mih_evt_list		event_list;

	event_list.set(mih::mih_evt_link_up);
	lid.type = mih::link_type_802_11;
	mih::mac_addr mac;
	mac.address("00:11:22:33:44:55");
	lid.addr = mac;

	req << mih::request(mih::request::event_subscribe, mih::id("mihf1"))
		& mih::tlv_link_identifier(lid)
		& mih::tlv_event_list(event_list);
	req.tid(126);

	_mihf.async_send_mihf1(req);
}

void message_unit_test::send_event_unsubscribe()
{
	log_(0, "Send MIH_Event_Unsubscribe.request");

	mih::message		req;
	mih::link_tuple_id	lid;
	mih::mih_evt_list		event_list;

	event_list.set(mih::mih_evt_link_up);
	lid.type = mih::link_type_802_11;
	mih::mac_addr mac;
	mac.address("00:11:22:33:44:55");
	lid.addr = mac;

	req << mih::request(mih::request::event_unsubscribe, mih::id("mihf1"))
		& mih::tlv_link_identifier(lid)
		& mih::tlv_event_list(event_list);
	req.tid(219);

	_mihf.async_send_mihf1(req);
}

void message_unit_test::send_link_get_parameters()
{
	log_(0, "Send MIH_Link_Get_Parameters.request");

	mih::message req;
	mih::link_tuple_id 	lid;
	mih::link_id_list	lil;
	mih::mac_addr      	mac;
	mih::dev_states_req	dsr;

	dsr.set(mih::dev_state_batt_level);
	mac.address("00:11:22:33:44:55");
	lid.type = mih::link_type_802_11;
	lid.addr = mac;
	lil.push_back(lid);
	mih::link_status_req	lsr;
	mih::link_param_802_11	lp = mih::link_param_802_11_rssi;
	lsr._states_req.set(mih::link_states_req_op_mode);
	lsr._param_type_list.push_back(lp);
	lsr._desc_req.set(mih::link_desc_req_classes_of_service_supported);

	req << mih::request(mih::request::link_get_parameters, mih::id("mihf1"))
		& mih::tlv_dev_states_req(dsr)
		& mih::tlv_link_id_list(lil)
		& mih::tlv_get_status_req_set(lsr);
	req.tid(321);

	_mihf.async_send_mihf1(req);
}

void message_unit_test::send_link_actions()
{
	log_(0, "Send MIH_Link_Actions.request");

	mih::message			req;
	mih::link_tuple_id		lid;
	mih::mac_addr			mac;
	mih::link_action_req	lar;
	mih::link_action_list	larl;

	mac.address("00:11:22:33:44:55");
	lid.type = mih::link_type_802_11;
	lid.addr = mac;
	lar.id = lid;
	lar.addr = mac;
	lar.action.type = mih::link_ac_type_none;
	lar.action.attr.set(mih::link_ac_attr_scan);
	lar.ex_time = 0;
	larl.push_back(lar);

	req << mih::request(mih::request::link_actions, mih::id("mihf1"))
		& mih::tlv_link_action_list(larl);
	req.tid(654);

	_mihf.async_send_mihf1(req);
}

void message_unit_test::send_link_actions_with_poa()
{
	log_(0, "Send MIH_Link_Actions.request with PoA");

	mih::message			req;
	mih::link_tuple_id		lid;
	mih::mac_addr			mac;
	mih::link_action_req	lar;
	mih::link_action_list	larl;

	mac.address("00:11:22:33:44:55");
	lid.type = mih::link_type_802_11;
	lid.addr = mac;
	lar.id = lid;
	lar.addr = mac;
	lar.action.type = mih::link_ac_type_none;
	lar.action.attr.set(mih::link_ac_attr_scan);
		lar.action.attr.set(mih::link_ac_attr_data_fwd_req);
	lar.ex_time = 0;
	larl.push_back(lar);

	req << mih::request(mih::request::link_actions, mih::id("mihf1"))
		& mih::tlv_link_action_list(larl);
	req.tid(555);

	_mihf.async_send_mihf1(req);
}


void message_unit_test::send_link_configure_thresholds()
{
	log_(0, "Send MIH_Link_Configure_Thresholds.request");

	mih::message				req;
	mih::link_tuple_id 			lid;
	mih::mac_addr      			mac;
	mih::link_cfg_param			lcp;
	mih::link_cfg_param_list	lcpl;

	mac.address("00:11:22:33:44:55");
	lid.type = mih::link_type_802_11;
	lid.addr = mac;
	std::vector<mih::threshold> th_list;
	lcp.type = mih::link_type_802_11;
	lcp.timer_interval = 1234;
	lcp.action = mih::th_action_normal;
	lcp.threshold_list = th_list;
	lcpl.push_back(lcp);

	req << mih::request(mih::request::link_configure_thresholds, mih::id("mihf1"))
		& mih::tlv_link_identifier(lid)
		& mih::tlv_link_cfg_param_list(lcpl);
	req.tid(999);

	_mihf.async_send_mihf1(req);
}

void message_unit_test::send_link_up()
{
	log_(0, "Send MIH_Link_Up.indication");

	mih::message 		req;

	mih::link_tuple_id	lid;
	mih::mac_addr		mac;
	mac.address("00:11:22:33:44:55");
	lid.type = mih::link_type_802_11;
	lid.addr = mac;
	mih::link_addr addr = mac;
	mih::ip_mob_mgmt mob;
	mob.set(mih::ip_mob_ipv6);

	req << mih::indication(mih::indication::link_up, mih::id("mihf1"))
		& mih::tlv_link_identifier(lid)
		& mih::tlv_old_access_router(addr)
		& mih::tlv_new_access_router(addr)
		& mih::tlv_ip_renewal_flag(true)
		& mih::tlv_ip_mob_mgmt(mob);
	req.tid(33);

	_mihf.async_send_mihf1(req);
}

void message_unit_test::send_link_down()
{
	log_(0, "Send MIH_Link_Down.indication");

	mih::message 		req;

	mih::link_tuple_id	lid;
	mih::mac_addr		mac;
	mac.address("00:11:22:33:44:55");
	lid.type = mih::link_type_802_11;
	lid.addr = mac;

	req << mih::indication(mih::indication::link_down, mih::id("mihf1"))
		& mih::tlv_link_identifier(lid)
		& mih::tlv_old_access_router(mac)
		& mih::tlv_link_dn_reason(mih::link_dn_reason_explicit_disconnect);
	req.tid(77);

	_mihf.async_send_mihf1(req);
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace odtone */

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
	odtone::setup_crash_handler();

	try {
		boost::asio::io_service ios;

		po::options_description desc(odtone::mih::octet_string("Configuration"));
		desc.add_options()
			("help", "Display configuration options")
			(odtone::test::kConf_File, po::value<std::string>()->default_value("test.conf"), "Configuration file")
			(odtone::test::kConf_Receive_Buffer_Len, po::value<uint>()->default_value(4096), "Receive buffer length")
			(odtone::test::kConf_Port, po::value<ushort>()->default_value(1235), "Listening port")
			(odtone::test::kConf_MIHF1_Local_Port, po::value<ushort>()->default_value(1025), "Local MIHF 1 communication port")
			(odtone::test::kConf_MIHF2_Local_Port, po::value<ushort>()->default_value(1026), "Local MIHF 2 communication port")
		;

		odtone::mih::config cfg(desc);
		cfg.parse(argc, argv, odtone::test::kConf_File);

		if (cfg.help()) {
			std::cerr << desc << std::endl;
			return EXIT_SUCCESS;
		}

		odtone::message_unit_test usr(cfg, ios);

		ios.run();

	} catch(std::exception& e) {
		log_(0, "exception: ", e.what());
	}
}

// EOF ////////////////////////////////////////////////////////////////////////
