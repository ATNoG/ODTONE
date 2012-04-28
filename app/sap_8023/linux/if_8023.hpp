//=============================================================================
// Brief   : Netlink interface for 802.3 devices
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

#ifndef IF_8023__HPP_
#define IF_8023__HPP_

#include <boost/asio.hpp>

#include <boost/noncopyable.hpp>
#include <boost/function.hpp>
#include <boost/thread.hpp>

#include <odtone/mih/tlv_types.hpp>

#include "../linux/nlwrap/nlwrap.hpp"

///////////////////////////////////////////////////////////////////////////////

using namespace odtone;

class if_8023 : boost::noncopyable {

	typedef boost::function<void(mih::link_tuple_id &tuple_id,
	                             boost::optional<mih::link_addr> &old_router,
	                             boost::optional<mih::link_addr> &new_router,
	                             boost::optional<bool> &ip_renew,
	                             boost::optional<mih::ip_mob_mgmt> &mobility_management)> link_up_handler;

	typedef boost::function<void(mih::link_tuple_id &tuple_id,
	                             boost::optional<mih::link_addr> &old_router,
	                             mih::link_dn_reason &dn_reason)> link_down_handler;

//	typedef boost::function<void(mih::link_det_info &det_info)> link_detected_handler;
//
//	typedef boost::function<void(mih::link_tuple_id &tuple_id,
//	                             mih::link_param_rpt_list &rpt_list)> link_parameters_report_handler;
//	typedef boost::function<void()> link_going_down_handler;
//	typedef boost::function<void()> link_handover_imminent_handler;
//	typedef boost::function<void()> link_pdu_transmit_status_handler;

public:
	/**
	 * Construct a new if_80211 object.
	 * The object tries to associate with the given interface.
	 *
	 * @param ios An io_service instance
	 * @param mac The MAC address of the underlying device.
	 */
	if_8023(boost::asio::io_service &ios, mih::mac_addr mac);

	/**
	 * Destruct the object.
	 */
	~if_8023();

	/**
	 * Get the interface index of this device.
	 *
	 * @return The interface index.
	 */
	unsigned int ifindex();

	/**
	 * Get the MAC address of this device.
	 *
	 * @return the MAC address of the device.
	 */
	mih::mac_addr mac_address();

	/**
	 * Get the link id of this device.
	 *
	 * @return The link_id of the device.
	 */
	mih::link_id link_id();

	/**
	 * Check if the link has an active L2 connection.
	 *
	 * @return True if the link has an active L2 connection, false otherwise.
	 */
	bool link_up();

	/**
	 * Get the current operating mode of the device.
	 *
	 * @return The current op mode.
	 */
	mih::op_mode_enum get_op_mode();

	/**
	 * Change the device's operating mode.
	 *
	 * @param mode The new operating mode.
	 */
	void set_op_mode(const mih::link_ac_type_enum &mode);

	/**
	 * Set the callback for LINK_UP events.
	 *
	 * @param h The callback.
	 */
	void link_up_callback(const link_up_handler &h);

	/**
	 * Set the callback for LINK_DOWN events.
	 *
	 * @param h The callback.
	 */
	void link_down_callback(const link_down_handler &h);

	struct ctx_data {
		ctx_data (boost::asio::io_service &ios) : _ios(ios) {}

		boost::asio::io_service &_ios;

		boost::optional<link_up_handler>       _up_handler;
		boost::optional<link_down_handler>     _down_handler;

		int                   _family_id;

		int                   _ifindex;
		std::string           _dev;
		odtone::mih::mac_addr _mac;
	};

private:
	ctx_data _ctx;
	nlwrap::rtnl_socket _socket;
	nlwrap::nl_cb       _callback;
};

// EOF ////////////////////////////////////////////////////////////////////////

#endif /* IF_8023__HPP_ */
