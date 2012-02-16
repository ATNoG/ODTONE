//=============================================================================
// Brief   : Netlink Helper
// Authors : André Prata <aprata@av.it.pt>
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

#ifndef NL_HELPER__HPP_
#define NL_HELPER__HPP_

#define _LINUX_IF_H
#include <netlink/route/link.h>

#include <netlink/netlink.h>
#include <netlink/genl/genl.h>
#include <netlink/genl/ctrl.h>
#include <netlink/msg.h>
#include <netlink/attr.h>
#include <linux/nl80211.h>
#include <vector>

#include <odtone/mih/types/base.hpp>
#include <odtone/sap/link.hpp>

#define ETH_ALEN 6

///////////////////////////////////////////////////////////////////////////////
/**
 * This class aleviates some interactions with the LIBNL3 software, for an 802.11 device.
 * 
 * The typical initialization procedure consists of:
 *  - creating the object
 *  - calling init, which allocates and opens a generic netlink socket connection
 *  - setting custom callback
 *  - joining desired multicast groups
 *  - continuously receiving messages.
 * 
 * This is for multicast listening. Most other operations are handled on separate sockets.
 * 
 * Virtually all methods throw a descriptive std::string of failures, when they occurr.
 */
class nl80211_helper : boost::noncopyable {
public:
	/**
	 * Construct the helper object.
	 * 
	 * @param device The string that identifies the 802.11 device, like "wlan0", "eth1", etc.
	 */
	nl80211_helper(std::string device);

	/**
	 * Destruct the object.
	 */
	~nl80211_helper();

	/**
	 * Initialize the sockets, set the mac and if index for this object.
	 */
	void init();

	/**
	 * Join a series of multicast groups.
	 * 
	 * @param groups The multicast group name list.
	 *               Currently supports "scan", "mlme", "config", and "regulatory".
	 */
	void join_multicast_groups(std::vector<std::string> groups);

	/**
	 * Set a custom callback for the connection.
	 * The callback may receive messages not specific to the desired interface!
	 * 
	 * @param valid_handler A handler for valid messages, as defined by LIBNL3.
	 * @param data Data to pass to the callback.
	 */
	void set_custom_callback(nl_recvmsg_msg_cb_t valid_handler, void *data);

	/**
	 * Get the interface index for the given device.
	 * 
	 * @return The interface index.
	 */
	unsigned int if_index();

	/**
	 * Get the MAC Address for the given device.
	 * 
	 * @return The MAC Address.
	 */
	odtone::mih::mac_addr mac_address();

	/**
	 * Trigger a new scan operation on the device.
	 * 
	 * @warning This operation usually requires Super User permissions on the machine.
	 * @warning This operation will throw an exception if another
	 *          scan has been triggered and not yet complete
	 * 
	 * @param wait If set to True, the method blocks until the scan operation
	 *             has completed, either with success or failure.
	 */
	void trigger_scan(bool wait);

	/**
	 * Dump the scan results available in the device.
	 * 
	 * @param valid_handler The handler you want to parse the scan results with.
	 * @param data Data that will be passed to the handler.
	 */
	void get_scan_results(nl_recvmsg_msg_cb_t valid_handler, void *data);

	/**
	 * Receive one message.
	 */
	void recv_msgs();

	/**
	 * Get the current error state of the connection.
	 * 
	 * @return True if error has been set (failed recv_msgs, if callbacks properly set)
	 */
	bool error();

	/**
	 * Get the device's current operating mode.
	 * 
	 * @return The current op_mode of the device.
	 */
	odtone::mih::op_mode_enum get_op_mode();

	/**
	 * Set a specific operating mode on the device.
	 * 
	 * @warning This operation usually requires Super User permissions on the machine.
	 * 
	 * @param mode The mode to set to to.
	 */
	void set_op_mode(const odtone::mih::link_ac_type_enum &mode);

private:

	/**
	 * Auxiliary function to allocate and connect a new GENETLINK socket.
	 * 
	 * @return The allocated socket.
	 */
	static nl_sock *init_new_socket();

	/**
	 * Auxiliary function to join multicast groups on a given socket.
	 * 
	 * @param sock The socket to subscribe to multicast groups on.
	 * @param groups The multicast groups to join.
	 */
	void join_multicast_groups(nl_sock *sock, std::vector<std::string> groups);

	/**
	 * Auxiliary function to allocate and retrieve a given route link object.
	 * 
	 * @param sock A RTNETLINK socket, if reusable.
	 * 
	 * @return the allocated link object.
	 */
	rtnl_link *get_rtnl_link(nl_sock *sock = NULL);

	/**
	 * Auxiliary function to allocate and pre-configure a netlink message.
	 * 
	 * @param ifindex The interface index to send the message to.
	 * @param family_id The family_id to use the message in.
	 * @param command The command for the message.
	 * @param flags aditional flags for the message.
	 * 
	 * @return The allocated and preconfigured netlink message.
	 */
	static nl_msg *get_nlmsg(int ifindex, int family_id, int command, int flags = 0);

	/**
	 * Auxiliary function to allocate and preconfigure a callback.
	 * 
	 * @param err The error variable to pass to the standard callbacks.
	 * 
	 * @return The allocated and configured callback object.
	 */
	static nl_cb *get_standard_callback(int *err);

	/**
	 * Auxiliary function to allocate a desired callback.
	 * Performs preconfigured callback setup, first!
	 * 
	 * @param valid_handler The callback function for VALID messages.
	 * @param err The error variable to pass to the standard callbacks
	 * @param data The data variable to pass to the given callback.
	 * 
	 * @return The allocated and configured callback object.
	 */
	static nl_cb *get_custom_callback(nl_recvmsg_msg_cb_t valid_handler, int *err, void *data);

	/**
	 * Auxiliary function to set the mac and if index local variables.
	 */
	void set_mac_and_if_index();

	/**
	 * Get the multicast if of a given multicast group.
	 * 
	 * @param group The group name.
	 * 
	 * @return The multicast id of the given group.
	 */
	int get_multicast_id(const char *group);

private:
	std::string dev;
	int ifindex;
	odtone::mih::mac_addr mac;

	nl_sock *socket;
	int family_id;
	int err;
};

/**
 * 
 */
void mac_addr_n2a(char *mac_addr, unsigned char *arg);

/**
 * 
 */
std::string get_essid(unsigned char *ie, int ielen);

/**
 * 
 */
unsigned int get_max_supp_rate(unsigned char *ie, int ielen);

/**
 * 
 */
bool has_security_features(unsigned char *ie, int ielen);

/**
 * 
 */
bool has_qos_capabilities(odtone::uint16 capa);

/**
 * 
 */
unsigned int frequency_to_channel_id(unsigned int frequency);

/**
 * 
 */
struct bss_parse_policy {
	nla_policy pol[NL80211_BSS_MAX + 1];

	bss_parse_policy() {
		pol[NL80211_BSS_TSF].type = NLA_U64;
		pol[NL80211_BSS_FREQUENCY].type = NLA_U32;
		pol[NL80211_BSS_BSSID] = { };
		pol[NL80211_BSS_BEACON_INTERVAL].type = NLA_U16;
		pol[NL80211_BSS_CAPABILITY].type = NLA_U16;
		pol[NL80211_BSS_INFORMATION_ELEMENTS] = { };
		pol[NL80211_BSS_SIGNAL_MBM].type = NLA_U32;
		pol[NL80211_BSS_SIGNAL_UNSPEC].type = NLA_U8;
		pol[NL80211_BSS_STATUS].type = NLA_U32;
		pol[NL80211_BSS_SEEN_MS_AGO].type = NLA_U32;
		pol[NL80211_BSS_BEACON_IES] = { };
	}
};

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* NL_HELPER__HPP_ */
