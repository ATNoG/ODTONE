//=============================================================================
// Brief   : GENetlink message RAI wrapper
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

#ifndef __NLWRAP_GENL_MSG_
#define __NLWRAP_GENL_MSG_

#include <boost/optional.hpp>
#include <string>

#include <odtone/mih/types/address.hpp>
#include <linux/nl80211.h>
#include "nl_msg.hpp"

namespace nlwrap {

/**
 * This class provides a RAI wrapper for the nl_msg datatype
 */
class genl_msg : public nl_msg {

public:
	/**
	 * @see nlwrap::nl_msg::nl_msg()
	 */
	genl_msg();

	/**
	 * Construct a new genl_msg object, providing a family, command and flags.
	 *
	 * @param family The family of the message recipient.
	 * @param type The command of the message.
	 * @param flags Aditional message flags.
	 */
	genl_msg(int family, int type, int flags);

	/**
	 * @see nlwrap::nl_msg::nl_msg(::nl_msg *msg)
	 */
	genl_msg(::nl_msg *msg);

	/**
	 * Put an IFINDEX element in the message.
	 *
	 * @param ifindex The desired IFINDEX.
	 */
	void put_ifindex(int ifindex);

	/**
	 * Put a FAMILY_NAME string into the message.
	 *
	 * @param name The desired FAMILY_NAME.
	 */
	void put_family_name(std::string name);

#ifdef NL80211_ATTR_PS_STATE
	/**
	 * Put a PS_STATE value in the message.
	 *
	 * @param state The desired PS_STATE.
	 */
	void put_ps_state(int state);
#endif /* NL80211_ATTR_PS_STATE */

	/**
	 * Set the NL80211_ATTR_SCAN_SSIDS to active scanning.
	 */
	void put_active_scanning();

	/**
	 * Put a MAC attribute in the message.
	 *
	 * @param mac The mac address to put.
	 */
	void put_mac(const std::string &mac);

	/**
	 * Get the command from a parsed message.
	 *
	 * @return The command from the parsed message.
	 */
	int cmd();

	boost::optional<int> attr_ifindex;
	boost::optional<int> attr_iftype;
	boost::optional<int> attr_status_code;
	boost::optional<std::string> attr_mac;
	boost::optional<int> attr_reason_code;
	boost::optional<int> attr_ps_state;
	boost::optional<bool> attr_bss;

	boost::optional<int> bss_status;
	boost::optional<int> bss_frequency;
	boost::optional<std::string> bss_bssid;
	boost::optional<int> bss_signal_mbm;
	boost::optional<bool> bss_qos_capable;

	boost::optional<std::string> ie_ssid;
	boost::optional<unsigned int> ie_max_data_rate;
	boost::optional<bool> ie_has_security_features;
	boost::optional<bool> ie_has_mih_capabilities;
	boost::optional<bool> ie_has_internet_access;
	boost::optional<bool> ie_has_emergency_services;
	boost::optional<odtone::mih::mac_addr> ie_hessid;
	boost::optional<bool> ie_has_mih_event_service;
	boost::optional<bool> ie_has_mih_command_service;
	boost::optional<bool> ie_has_mih_information_service;

	boost::optional<int> sta_info_signal;
	boost::optional<int> sta_rate_info_bitrate; // 54MBit = 540

private:
	void parse_attr(::nlattr *tb[NL80211_ATTR_MAX + 1]);
	void parse_bss(::nlattr *bss[NL80211_BSS_MAX + 1]);
	void parse_sta(::nlattr *bss[NL80211_STA_INFO_MAX + 1]);
	void parse_information_elements(unsigned char *ie, int ielen);

private:
	int       _cmd;
};

}

// EOF ////////////////////////////////////////////////////////////////////////

#endif /* __NLWRAP_GENL_MSG_ */
