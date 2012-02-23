//=============================================================================
// Brief   : Netlink interface for 802.11 devices
// Authors : André Prata <andreprata@av.it.pt>
//-----------------------------------------------------------------------------
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

#ifndef IF_80211__HPP_
#define IF_80211__HPP_

#include <boost/asio.hpp>

#include <boost/noncopyable.hpp>
#include <boost/function.hpp>
#include <boost/thread.hpp>

#include <odtone/mih/tlv_types.hpp>

#include "../linux/nlwrap/nlwrap.hpp"

///////////////////////////////////////////////////////////////////////////////

using namespace odtone;

struct poa_info : mih::link_det_info {
	uint channel_id;
};

class if_80211 : boost::noncopyable {
	typedef boost::function<void(mih::link_tuple_id &tuple_id,
	                             boost::optional<mih::link_addr> &old_router,
	                             boost::optional<mih::link_addr> &new_router,
	                             boost::optional<bool> &ip_renew,
	                             boost::optional<mih::ip_mob_mgmt> &mobility_management)> link_up_handler;

	typedef boost::function<void(mih::link_tuple_id &tuple_id,
	                             boost::optional< mih::link_addr> &old_router,
	                             mih::link_dn_reason &dn_reason)> link_down_handler;

	typedef boost::function<void(mih::link_det_info &det_info)> link_detected_handler;
//
//	typedef boost::function<void(mih::link_tuple_id &tuple_id,
//	                             mih::link_param_rpt_list &rpt_list)> link_parameters_report_handler;
//	typedef boost::function<void()> link_going_down_handler;
//	typedef boost::function<void()> link_handover_imminent_handler;
//	typedef boost::function<void()> link_pdu_transmit_status_handler;

public:
	if_80211(boost::asio::io_service &ios, odtone::mih::mac_addr mac);
	~if_80211();

	void init();

	unsigned int ifindex();
	mih::mac_addr mac_address();
	mih::link_id link_id();

	void trigger_scan(bool wait);
	mih::link_scan_rsp_list get_scan_results();
	poa_info get_poa_info();

	mih::op_mode_enum get_op_mode();
	void set_op_mode(const mih::link_ac_type_enum &mode);

	void process_threshold(mih::link_cfg_param &param);

	void link_up_callback(link_up_handler h);
	void link_down_callback(link_down_handler h);
	void link_detected_callback(link_detected_handler h);

	struct ctx_data {
		ctx_data (boost::asio::io_service &ios) : _ios(ios) {}

		boost::asio::io_service &_ios;

		boost::optional<link_up_handler>                _up_handler;
		boost::optional<link_down_handler>              _down_handler;
		boost::optional<link_detected_handler>          _detected_handler;

		bool				  _scanning;
		int                   _family_id;

		int                   _ifindex;
		std::string           _dev;
		odtone::mih::mac_addr _mac;
	};

private:
	ctx_data _ctx;
	nlwrap::genl_socket _socket;
	nlwrap::genl_cb     _callback;
};

// EOF ////////////////////////////////////////////////////////////////////////

#endif /* IF_80211__HPP_ */
