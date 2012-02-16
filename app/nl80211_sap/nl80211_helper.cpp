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

#include <boost/foreach.hpp>
#include <boost/scope_exit.hpp>

#include "nl80211_helper.hpp"

#include "log.hpp"

int no_seq_check(nl_msg *msg, void *arg);
int error_handler(sockaddr_nl *nla, nlmsgerr *err, void *arg);
int finish_handler(nl_msg *msg, void *arg);
int ack_handler(nl_msg *msg, void *arg);
int family_handler(nl_msg *msg, void *arg);
int operstate_handler(nl_msg *msg, void *arg);

int signal_scan_finish_handler(nl_msg *msg, void *arg);

struct handler_args {
	const char *group;
	int id;
};

nl80211_helper::nl80211_helper(std::string device)
{
	dev = device;

	err = 0;
	ifindex = 0;
}

nl80211_helper::~nl80211_helper()
{
	if (socket) {
		nl_cb_put(nl_socket_get_cb(socket));
		nl_close(socket);
		nl_socket_free(socket);
	}
}

void nl80211_helper::init()
{
	socket = init_new_socket();
	family_id = genl_ctrl_resolve(socket, "nl80211");
	set_mac_and_if_index();
}

nl_sock* nl80211_helper::init_new_socket()
{
	bool s_err = false;
	nl_sock *sock = NULL;

	BOOST_SCOPE_EXIT ((&s_err) (&sock)) {
		if (s_err && sock) {
			nl_close(sock);
			nl_socket_free(sock);
			sock = NULL;
		}
	} BOOST_SCOPE_EXIT_END

	sock = nl_socket_alloc();
	if (!sock) {
		throw "Unable to allocate netlink socket (generic)";
	}

	if (genl_connect(sock)) {
		s_err = true;
		throw "Unable to connect generic netlink socket";
	}

	return sock;
}

rtnl_link *nl80211_helper::get_rtnl_link(nl_sock *sock)
{
	bool own_sock = false;
	rtnl_link *link = NULL;
	nl_sock *sk = sock;
	nl_cache *cache = NULL;

	BOOST_SCOPE_EXIT ((&cache) (&own_sock) (&sk)) {
		nl_cache_free(cache);
		if (own_sock && sk) {
			nl_close(sk);
			nl_socket_free(sk);
		}
	} BOOST_SCOPE_EXIT_END

	if (!sk) {
		own_sock = true;

		sk = nl_socket_alloc();
		if (!sk) {
			throw "unable to allocate netlink socket (route)";
		}

		if (nl_connect(sk, NETLINK_ROUTE)) {
			throw "unable to connect to route socket";
		}
	}

	if (rtnl_link_alloc_cache(sk, AF_UNSPEC, &cache)) {
		throw "unnable to allocate nl_cache";
	}

	link = rtnl_link_get_by_name(cache, dev.c_str());
	if (!link) {
		throw "could not find such link, " + dev;
	}

	return link;
}

void nl80211_helper::set_mac_and_if_index()
{
	rtnl_link *link = NULL;

	BOOST_SCOPE_EXIT ((&link)) {
		rtnl_link_put(link); // verifies null
	} BOOST_SCOPE_EXIT_END

	link = get_rtnl_link();

	// save the link addr
	char mac_addr[3 * ETH_ALEN];
	nl_addr *addr = rtnl_link_get_addr(link);
	if (!addr) {
		throw "unable to get mac address of device " + dev;
	}

	nl_addr2str(addr, mac_addr, 3 * ETH_ALEN);
	mac.address(mac_addr);

	ifindex = rtnl_link_get_ifindex(link);
	if (ifindex == 0) {
		throw "could not determine ifindex of device " + dev;
	}
}

void nl80211_helper::set_custom_callback(nl_recvmsg_msg_cb_t valid_handler, void* data)
{
	nl_cb_put(nl_socket_get_cb(socket));
	nl_socket_set_cb(socket, get_custom_callback(valid_handler, &err, data));
}

nl_msg *nl80211_helper::get_nlmsg(int ifindex, int family_id, int command, int flags)
{
	bool s_err = false;
	nl_msg *msg = NULL;

	BOOST_SCOPE_EXIT ((&s_err) (&msg)) {
		if (s_err && msg) {
			nlmsg_free(msg);
		}
	} BOOST_SCOPE_EXIT_END

	msg = nlmsg_alloc();
	if (!msg) {
		throw "unable to allocate message";
	}

	genlmsg_put(msg, 0, 0, family_id, 0, flags, command, 0);
	if (nla_put_u32(msg, NL80211_ATTR_IFINDEX, ifindex)) {
		s_err = true;
		throw "unable to add ifindex attribute to message";
	}

	return msg;
}

nl_cb *nl80211_helper::get_standard_callback(int *error)
{
	bool s_err = false;
	nl_cb *cb = NULL;

	BOOST_SCOPE_EXIT ((&s_err) (&cb)) {
		if (s_err) {
			nl_cb_put(cb);
		}
	} BOOST_SCOPE_EXIT_END

	cb = nl_cb_alloc(NL_CB_DEFAULT);
	if (!cb) {
		throw "unable to allocate callback";
	}

	if (nl_cb_set(cb, NL_CB_SEQ_CHECK, NL_CB_CUSTOM, no_seq_check, NULL)) {
		s_err = true;
		throw "failed to set no_sequence_check callback";
	}

	if (nl_cb_set(cb, NL_CB_FINISH, NL_CB_CUSTOM, finish_handler, error)) {
		s_err = true;
		throw "failed to set finish callback";
	}

	if (nl_cb_set(cb, NL_CB_ACK, NL_CB_CUSTOM, ack_handler, error)) {
		s_err = true;
		throw "failed to set ack callback";
	}

	if (nl_cb_err(cb, NL_CB_CUSTOM, error_handler, error)) {
		s_err = true;
		throw "failed to set error callback";
	}

	return cb;
}

nl_cb *nl80211_helper::get_custom_callback(nl_recvmsg_msg_cb_t valid_handler, int *error, void *data)
{
	bool s_err = false;
	nl_cb *cb = NULL;

	BOOST_SCOPE_EXIT ((&s_err) (&cb)) {
		if (s_err) {
			nl_cb_put(cb);
		}
	} BOOST_SCOPE_EXIT_END

	cb = get_standard_callback(error);

	if (nl_cb_set(cb, NL_CB_VALID, NL_CB_CUSTOM, valid_handler, data)) {
		s_err = true;
		throw "failed to set custom callback";
	}

	return cb;
}

int nl80211_helper::get_multicast_id(const char *group)
{
	nl_sock *sk = NULL;
	nl_msg *msg = NULL;
	nl_cb *cb = NULL;
	int ret, ctrlid;
	handler_args grp = { group, -ENOENT };

	BOOST_SCOPE_EXIT ((&msg) (&cb) (&sk)) {
		nl_cb_put(cb);
		nlmsg_free(msg);
		if (sk) {
			nl_close(sk);
			nl_socket_free(sk);
		}
	} BOOST_SCOPE_EXIT_END

	sk = init_new_socket();

	msg = nlmsg_alloc();
	if (!msg) {
		throw "failed to allocate nl_msg";
	}

	ctrlid = genl_ctrl_resolve(sk, "nlctrl");

	genlmsg_put(msg, 0, 0, ctrlid, 0, 0, CTRL_CMD_GETFAMILY, 0);
	nla_put_string(msg, CTRL_ATTR_FAMILY_NAME, "nl80211");

	if (nl_send_auto_complete(sk, msg) < 0) {
		throw "failed to send message";
	}

	ret = 1;
	cb = get_custom_callback(family_handler, &ret, &grp);

	while (ret > 0) {
		nl_recvmsgs(sk, cb);
	}

	if (ret == 0) {
		ret = grp.id;
	}

	return ret;
}

void nl80211_helper::join_multicast_groups(nl_sock *sock, std::vector<std::string> groups)
{
	int multicast_id;
	int err;

	BOOST_FOREACH (std::string group, groups) {
		multicast_id = get_multicast_id(group.c_str());
		err = nl_socket_add_membership(sock, multicast_id);
		if (err) {
			throw "failed to join " + group + " multicast group."
				+ " error " + boost::lexical_cast<std::string>(err)
				+ ", multicast id " + boost::lexical_cast<std::string>(multicast_id);
		}
	}
}

void nl80211_helper::join_multicast_groups(std::vector<std::string> groups)
{
	join_multicast_groups(socket, groups);
}

unsigned int nl80211_helper::if_index()
{
	if (ifindex == 0) {
		throw "must init first";
	}

	return ifindex;
}

odtone::mih::mac_addr nl80211_helper::mac_address()
{
//	if (!mac) {
//		throw "must init first";
//	}

	return mac;
}

void nl80211_helper::trigger_scan(bool wait)
{
	ODTONE_LOG(2, "(nl) Triggering scan");

	int error = 1;
	int command = -1;

	nl_cb *cb = NULL;
	nl_msg *msg = NULL;
	nl_sock* sk = NULL;

	BOOST_SCOPE_EXIT ((&cb) (&msg) (&sk)) {
		nl_cb_put(cb);
		nlmsg_free(msg);
		if (sk) {
			nl_close(sk);
			nl_socket_free(sk);
		}
	} BOOST_SCOPE_EXIT_END

	sk = init_new_socket();

	if (wait) {
		cb = get_custom_callback(signal_scan_finish_handler, &error, &command);
		std::vector<std::string> v;
		v.push_back("scan");
		join_multicast_groups(sk, v);
	} else {
		cb = get_standard_callback(&error);
		command = 1;
	}

	msg = get_nlmsg(ifindex, family_id, NL80211_CMD_TRIGGER_SCAN);

	if(nl_send_auto_complete(sk, msg) < 0) {
		throw "failed to send trigger_scan message";
	}

	//while (error > 0 || (wait && command < 0 && !(error < 0))) {
	while (error > 0 || (command < 0 && error >= 0)) {
		nl_recvmsgs(sk, cb);
	}

	if (error < 0) {
		throw "netlink error, code: " + boost::lexical_cast<std::string>(error);
	}

	ODTONE_LOG(2, "(nl) Scan triggered");
}

void nl80211_helper::get_scan_results(nl_recvmsg_msg_cb_t valid_handler, void *data)
{
	ODTONE_LOG(2, "(nl) Dumping scan results");

	int error = 1;
	nl_cb *cb = NULL;
	nl_msg *msg = NULL;
	nl_sock *sk = NULL;

	BOOST_SCOPE_EXIT ((&cb) (&msg) (&sk)) {
		nl_cb_put(cb);
		nlmsg_free(msg);
		if (sk) {
			nl_close(sk);
			nl_socket_free(sk);
		}
	} BOOST_SCOPE_EXIT_END

	sk = init_new_socket();
	msg = get_nlmsg(ifindex, family_id, NL80211_CMD_GET_SCAN, NLM_F_DUMP);
	cb = get_custom_callback(valid_handler, &error, data);

	if (nl_send_auto_complete(sk, msg) < 0) {
		throw "failed to send get_scan message";
	}

	while (error > 0) {
		nl_recvmsgs(sk, cb);
	}

	if (error < 0) {
		throw "error, code: " + boost::lexical_cast<std::string>(error);
	}

	ODTONE_LOG(2, "(nl) Dumped scan results");
}

void nl80211_helper::recv_msgs()
{
	nl_recvmsgs_default(socket);
}

bool nl80211_helper::error()
{
	return err != 0;
}

odtone::mih::op_mode_enum nl80211_helper::get_op_mode()
{
	ODTONE_LOG(2, "(nl) Getting link op_mode");

	int error = 1;
	int operstate;
	nl_msg *msg = NULL;
	nl_cb *cb = NULL;
	nl_sock *sk = NULL;
	rtnl_link *link = NULL;

	BOOST_SCOPE_EXIT ((&cb) (&msg) (&sk) (&link)) {
		nl_cb_put(cb);
		nlmsg_free(msg);
		rtnl_link_put(link);
		if (sk) {
			nl_close(sk);
			nl_socket_free(sk);
		}
	} BOOST_SCOPE_EXIT_END

	link = get_rtnl_link();

	operstate = rtnl_link_get_flags(link);
	if (!(operstate & IFF_UP)) {
		return odtone::mih::op_mode_powered_down;
	}
	////
	
	sk = init_new_socket();
	msg = get_nlmsg(ifindex, family_id, NL80211_CMD_GET_POWER_SAVE);

	operstate = -1;
	cb = get_custom_callback(operstate_handler, &error, &operstate);

	if (nl_send_auto_complete(sk, msg) < 0) {
		throw "failed to send get_scan message";
	}

	while (error > 0 || (operstate < 0 && error >= 0)) {
		nl_recvmsgs(sk, cb);
	}

	if (error < 0) {
		throw "error, code: " + boost::lexical_cast<std::string>(error);
	}

	if (operstate == NL80211_PS_ENABLED) {
		return odtone::mih::op_mode_power_saving;
	}

	return odtone::mih::op_mode_normal;
}

#define IF_OPER_DOWN 2 // linux/if.h
#define IF_OPER_LOWERLAYERDOWN 3
void nl80211_helper::set_op_mode(const odtone::mih::link_ac_type_enum &mode)
{
	ODTONE_LOG(2, "(nl) Setting link op_mode");

	switch (mode) {
	case odtone::mih::link_ac_type_none:
		// nothing
		break;

	case odtone::mih::link_ac_type_power_down:
	case odtone::mih::link_ac_type_power_up:
		{
			nl_sock *sk = NULL;
			rtnl_link *change = NULL, *link = NULL;

			BOOST_SCOPE_EXIT ((&sk) (&change) (&link)) {
				rtnl_link_put(change);
				rtnl_link_put(link);
				if (sk) {
					nl_close(sk);
					nl_socket_free(sk);
				}
			} BOOST_SCOPE_EXIT_END

			sk = nl_socket_alloc(); /* route socket */
			if (!sk) {
				throw "unable to allocate netlink socket (route)";
			}

			if (nl_connect(sk, NETLINK_ROUTE)) {
				throw "unable to connect to route socket";
			}

			change = rtnl_link_alloc();
			if (!change) {
				throw "unable to allocate link object";
			}

			// check if not really changing anything?
			if (mode == odtone::mih::link_ac_type_power_down) {
				rtnl_link_unset_flags(change, IFF_UP);
			} else /*if (mode == odtone::mih::link_ac_type_power_up) */{
				rtnl_link_set_flags(change, IFF_UP);
			}

			link = get_rtnl_link(sk);

			int ret;
			if ((ret = rtnl_link_change(sk, link, change, 0))) {
				throw "error, code: " + boost::lexical_cast<std::string>(ret);
			}
		}
		break;

	case odtone::mih::link_ac_type_disconnect:
	case odtone::mih::link_ac_type_low_power:
		{
			nl_msg *msg = NULL;
			nl_cb *cb = NULL;
			nl_sock *sk = NULL;

			BOOST_SCOPE_EXIT ((&msg) (&cb) (&sk)) {
				nlmsg_free(msg);
				nl_cb_put(cb);
				if (sk) {
					nl_close(sk);
					nl_socket_free(sk);
				}
			} BOOST_SCOPE_EXIT_END

			sk = init_new_socket();

			if (mode == odtone::mih::link_ac_type_disconnect) {
				msg = get_nlmsg(ifindex, family_id, NL80211_CMD_DISCONNECT);
			} else /*if (command == odtone::mih::link_ac_type_low_power) */{
				msg = get_nlmsg(ifindex, family_id, NL80211_CMD_SET_POWER_SAVE);
				if (nla_put_u32(msg, NL80211_ATTR_PS_STATE, NL80211_PS_ENABLED)) {
					nlmsg_free(msg);
					throw "unable to add ifindex attribute to message";
				}
			}

			int error = 1;
			cb = get_standard_callback(&error);

			if (nl_send_auto_complete(sk, msg) < 0) {
				throw "failed to send get_scan message";
			}

			while (error > 0) {
				nl_recvmsgs(sk, cb);
			}

			if (error < 0) {
				throw "error, code: " + boost::lexical_cast<std::string>(error);
			}
		}
		break;

	default:
		throw "mode not supported";
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////

void mac_addr_n2a(char *mac_addr, unsigned char *arg)
{
	int i, l;

	l = 0;
	for (i = 0; i < ETH_ALEN ; i++) {
		if (i == 0) {
			sprintf(mac_addr+l, "%02x", arg[i]);
			l += 2;
		} else {
			sprintf(mac_addr+l, ":%02x", arg[i]);
			l += 3;
		}
	}
}


#define IE_ARRAY_SIZE 128
#define IE_WIFI_SIZE 4

// for ESSID
#define IE_SSID_INDEX 0

// for data rates
#define IE_SUPP_RATES_INDEX 1
#define IE_EXTENDED_SUPP_RATES_INDEX 50

// for security features
#define IE_RNS_INDEX 48
#define IE_VENDOR 221 // doesn't count for ARRAY_SIZE

#define WLAN_CAPABILITY_QOS (1<<9)

std::string get_essid(unsigned char *ie, int ielen)
{
	std::string result = "";
	const char *data;
	while (ielen >= 2 && ielen >= ie[1]) {
		if (ie[0] < IE_ARRAY_SIZE &&
		    ie[0] == IE_SSID_INDEX) { // ssid
		    data = (const char*)ie + 2;
		    size_t len = ie[1];
		    result.assign(data, len);
		    break;
		}

		ielen -= ie[1] + 2;
		ie += ie[1] + 2;
	}

	return result;
}

unsigned int get_max_supp_rate(unsigned char *ie, int ielen)
{
	unsigned int max_rate = 0;
	unsigned int rate;
	unsigned int r;

	unsigned char* data;
	unsigned int len;

	int passes = 0;
	while (ielen >= 2 && ielen >= ie[1] && passes < 2) {
		if (ie[0] < IE_ARRAY_SIZE && ie[0] == IE_SUPP_RATES_INDEX) {
			passes ++;

			data = ie + 2;
			len = ie[1];

			for (r = 0; r < len; r++) {
				rate = (data[r] & 0x7f) / 2;
				if (rate > max_rate) {
					max_rate = rate;
				}
			}
		} else if (ie[0] < IE_ARRAY_SIZE &&	ie[0] == IE_EXTENDED_SUPP_RATES_INDEX) {
			passes ++;

			data = ie + 2;
			len = ie[1];

			for (r = 0; r < len; r++) {
				rate = (data[r] & 0x7f) / 2;
				if (rate > max_rate) {
					max_rate = rate;
				}
			}
		}

		ielen -= ie[1] + 2;
		ie += ie[1] + 2;
	}

	return max_rate * 1000;
}

bool has_security_features(unsigned char *ie, int ielen)
{
	static unsigned char ms_oui[3] = { 0x00, 0x50, 0xf2 };
	unsigned int len;
	unsigned char* data;

	while (ielen >= 2 && ielen >= ie[1]) {
		if (ie[0] < IE_ARRAY_SIZE && ie[0] == IE_SUPP_RATES_INDEX) {
			return true;
		} else if (ie[0] == IE_VENDOR) {
			data = ie + 2;
			len = ie[1];

			if (len >= 4 && memcmp(data, ms_oui, 3) == 0) {
				return true;
			}
		}

		ielen -= ie[1] + 2;
		ie += ie[1] + 2;
	}

	return false;
}

bool has_qos_capabilities(odtone::uint16 capa)
{
	return (capa & WLAN_CAPABILITY_QOS);
}

//
//
// Commented code refers to country specific frequencies
//
unsigned int frequency_to_channel_id(unsigned int frequency)
{
	int ret = 0;

	if (frequency > 5000) {
		ret = (frequency - 5000) / 5;
//	} else if (frequency > 4000) {
//		ret = (frequency - 4000) / 5;
//	} else if (frequency > 3000) {
//		// not all of these are integer, and we are uncertain of
//		// how the kernel encodes those, but assume the integer
//		// part of such frequencies, the function works as well!
//		ret = (frequency - 3000) / 5
//
//		// special case
//		if (frequency == 3689) {
//			//(frequency - 3000) / 5 + 1;
//			ret = 138;
//		}
//	// another special case
//	} else if (frequency == 2484) {
//		ret = 14;
	} else if (frequency > 2400) {
		ret = (frequency - 2407) / 5;
	}

	return ret;
}

///////////////////////////////////////////////////////////////////////////////

int no_seq_check(nl_msg *msg, void *arg)
{
    return NL_OK;
}

int error_handler(sockaddr_nl *nla, nlmsgerr *err, void *arg)
{
	int *ret = (int *)arg;
	*ret = err->error;
	return NL_STOP;
}

int finish_handler(nl_msg *msg, void *arg)
{
	int *ret = (int *)arg;
	*ret = 0;
	return NL_SKIP;
}

int ack_handler(nl_msg *msg, void *arg)
{
	int *ret = (int *)arg;
	*ret = 0;
	return NL_STOP;
}

int family_handler(nl_msg *msg, void *arg) {
	handler_args *grp = (handler_args *)arg;
	nlattr *tb[CTRL_ATTR_MAX + 1];
	genlmsghdr *gnlh = (genlmsghdr *)nlmsg_data(nlmsg_hdr(msg));
	nlattr *mcgrp;
	int rem_mcgrp;

	nla_parse(tb, CTRL_ATTR_MAX, genlmsg_attrdata(gnlh, 0), genlmsg_attrlen(gnlh, 0), NULL);

	if (!tb[CTRL_ATTR_MCAST_GROUPS]) {
		return NL_SKIP;
	}

	mcgrp = (nlattr *)nla_data(tb[CTRL_ATTR_MCAST_GROUPS]);
	rem_mcgrp = nla_len(tb[CTRL_ATTR_MCAST_GROUPS]);
	for ( ; nla_ok(mcgrp, rem_mcgrp); mcgrp = nla_next(mcgrp, &(rem_mcgrp))) {
	// causes compilation warning, conversion from void* to nlattr*
	//nla_for_each_nested(mcgrp, tb[CTRL_ATTR_MCAST_GROUPS], rem_mcgrp) {
		nlattr *tb_mcgrp[CTRL_ATTR_MCAST_GRP_MAX + 1];

		nla_parse(tb_mcgrp, CTRL_ATTR_MCAST_GRP_MAX, (nlattr *)nla_data(mcgrp), nla_len(mcgrp), NULL);

		if (!tb_mcgrp[CTRL_ATTR_MCAST_GRP_NAME] || !tb_mcgrp[CTRL_ATTR_MCAST_GRP_ID]) {
			continue;
		}
		if (strncmp((char *)nla_data(tb_mcgrp[CTRL_ATTR_MCAST_GRP_NAME]),
			grp->group, nla_len(tb_mcgrp[CTRL_ATTR_MCAST_GRP_NAME]))) {
			continue;
		}
		grp->id = nla_get_u32(tb_mcgrp[CTRL_ATTR_MCAST_GRP_ID]);
		break;
	}

	return NL_SKIP;
}

int signal_scan_finish_handler(nl_msg *msg, void *arg)
{
	int *command = (int*)arg;
	genlmsghdr *gnlh = (genlmsghdr*)nlmsg_data(nlmsg_hdr(msg));

	if (gnlh->cmd == NL80211_CMD_NEW_SCAN_RESULTS || gnlh->cmd == NL80211_CMD_SCAN_ABORTED) {
		*command = (int)gnlh->cmd;
	}

	return NL_SKIP;
}

int operstate_handler(nl_msg *msg, void *arg)
{
	int *state = (int*)arg;
	nlattr *tb[NL80211_ATTR_MAX + 1];
	genlmsghdr *gnlh = (genlmsghdr*)nlmsg_data(nlmsg_hdr(msg));

	nla_parse(tb, NL80211_ATTR_MAX, genlmsg_attrdata(gnlh, 0), genlmsg_attrlen(gnlh, 0), NULL);

	if (!tb[NL80211_ATTR_PS_STATE]) {
		return NL_SKIP;
	}

	*state = nla_get_u32(tb[NL80211_ATTR_PS_STATE]);

	return NL_SKIP;
}

// EOF ////////////////////////////////////////////////////////////////////////
