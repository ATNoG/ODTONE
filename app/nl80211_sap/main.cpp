//=============================================================================
// Brief   : nl80211 Link SAP entry point
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

///////////////////////////////////////////////////////////////////////////////

#include "log.hpp"

#include <unistd.h> // for geteuid

#include <iostream>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/thread.hpp>

#include <odtone/sap/link.hpp>
#include <odtone/mih/types/base.hpp>
#include <odtone/mih/message.hpp>
#include <odtone/mih/indication.hpp>
#include <odtone/mih/request.hpp>
#include <odtone/mih/response.hpp>
#include <odtone/mih/confirm.hpp>
#include <odtone/mih/tlv_types.hpp>

#include "nl80211_helper.hpp"
#include "timer_task.hpp"

namespace po = boost::program_options;
using namespace odtone;

///////////////////////////////////////////////////////////////////////////////
//// Auxiliary Variables and Types
///////////////////////////////////////////////////////////////////////////////

nla_policy bss_policy[NL80211_BSS_MAX + 1];

struct scan_results_data {
	mih::link_det_info_list l;

	bool associated_only;
	boost::optional<uint> associated_channel_id;
	boost::optional<uint> associated_index;

	scan_results_data() : associated_only(false) {}
	scan_results_data(bool assoc_filter) : associated_only(assoc_filter) {}
};

struct periodic_report_data {
	mih::link_param_802_11 type;
	timer_task *task;
	void _report_value();
};

struct threshold_cross_data {
	bool one_shot;
	mih::link_param_802_11 type;
	mih::threshold th;
};

///////////////////////////////////////////////////////////////////////////////
//// Configuration variables
///////////////////////////////////////////////////////////////////////////////

static const char* const kConf_Dev_Id = "link.name";
static const char* const kConf_Sched_Scan_Period = "link.sched_scan_period";
static const char* const kConf_Default_Threshold_Period = "link.default_th_period";

mih::link_id link_id;
mih::link_evt_list capabilities_event_list;
mih::link_cmd_list capabilities_command_list;

///////////////////////////////////////////////////////////////////////////////
//// State variables
///////////////////////////////////////////////////////////////////////////////

boost::asio::io_service ios;
sap::link* ls;
nl80211_helper *nl80211;
bool _scanning = false;

mih::link_evt_list subscribed_event_list;

boost::shared_mutex _th_list_mutex;
std::vector<threshold_cross_data> th_cross_list;
std::vector<periodic_report_data> period_rpt_list;
timer_task *_th_check;

///////////////////////////////////////////////////////////////////////////////
//// Auxiliary Functions
///////////////////////////////////////////////////////////////////////////////

// To send link_register message to the MIHF.
void mihf_sap_init()
{
	mih::message m;

	m << mih::indication(mih::indication::link_register)
		& mih::tlv_interface_type_addr(link_id);

	ls->async_send(m);
}

// To set the link_id for the managed device.
void set_link_id()
{
	link_id.addr = nl80211->mac_address();
	link_id.type = mih::link_type(mih::link_type_802_11);
}

// Auxiliary function to set the supported event list. (hardcoded)
void set_supported_event_list()
{
	capabilities_event_list.set(mih::evt_link_detected);
	capabilities_event_list.set(mih::evt_link_up);
	capabilities_event_list.set(mih::evt_link_down);
	capabilities_event_list.set(mih::evt_link_parameters_report);
	//capabilities_event_list.set(mih::evt_link_going_down);
	//capabilities_event_list.set(mih::evt_link_handover_imminent);
	//capabilities_event_list.set(mih::evt_link_handover_complete);
	//capabilities_event_list.set(mih::evt_link_pdu_transmit_status);
}

// Auxiliary function to set the supported command list. (hardcoded)
void set_supported_command_list()
{
	capabilities_command_list.set(mih::cmd_link_event_subscribe);
	capabilities_command_list.set(mih::cmd_link_event_unsubscribe);
	capabilities_command_list.set(mih::cmd_link_get_parameters);
	capabilities_command_list.set(mih::cmd_link_configure_thresholds);
	capabilities_command_list.set(mih::cmd_link_action);
}

///////////////////////////////////////////////////////////////////////////////
//// Event dispatchers
///////////////////////////////////////////////////////////////////////////////

// Dispatch a link_up event.
//
// This primitive does not indicate the new POA.
// It is unlikely that this will be called, since
// the event usually always contains the attached POA's address
//
// See dispatch_link_up(mih::mac_addr&)
void dispatch_link_up()
{
	ODTONE_LOG(0, "(event) Dispatching link_up message");

	mih::link_tuple_id lid;
	lid.type = link_id.type;
	lid.addr = link_id.addr;

	mih::message m;
	m << mih::indication(mih::indication::link_up)
		& mih::tlv_link_identifier(lid)
//		& mih::tlv_ip_renewal_flag(true) // according to docs
		;

	ls->async_send(m);
}

// Dispatch a link_up event, with POA indication.
//
// This is the expected code to be run once 
// the kernel informs on the link establishment.
//
// LINK_UP implies that the Link was down,
// so an (new) IP must be re-configured, always.
void dispatch_link_up(mih::mac_addr &poa_addr)
{
	ODTONE_LOG(0, "(event) Dispatching link_up message with poa indication");

	mih::link_tuple_id lid;
	lid.type = link_id.type;
	lid.addr = link_id.addr;

	mih::message m;
	m << mih::indication(mih::indication::link_up)
		& mih::tlv_link_identifier(lid)
		& mih::tlv_poa(poa_addr)
//		& mih::tlv_ip_renewal_flag(true)
		;

	ls->async_send(m);
}

// Dispatch a link_down event.
//
// The reason codes for the event are translated
// based on the iw's source code description.
// The translation table is far from complete
// and might be inaccurate!
void dispatch_link_down(unsigned short rc)
{
	ODTONE_LOG(0, "(event) Dispatching link_down message");

	mih::link_tuple_id lid;
	lid.type = link_id.type;
	lid.addr = link_id.addr;

	// based on iw's reason.c [ http://linuxwireless.org/en/users/Documentation/iw ]
	mih::link_dn_reason rs;
	switch (rc) {
		case 39:
			rs = mih::link_dn_reason(mih::link_dn_reason_packet_timeout);
			break;
		case 5:
		case 31:
		case 32:
		case 33:
		case 34:
		case 45:
			rs = mih::link_dn_reason(mih::link_dn_reason_no_resource);
			break;
		case 4:
		//case 39:
			rs = mih::link_dn_reason(mih::link_dn_reason_no_broadcast);
			break;
		case 2:
		case 6:
		case 7:
		case 9:
		case 23:
		case 24:
			rs = mih::link_dn_reason(mih::link_dn_reason_authentication_failure);
			break;
		default:
			rs = mih::link_dn_reason(mih::link_dn_reason_explicit_disconnect);
	}

	mih::message m;
	m << mih::indication(mih::indication::link_down)
		& mih::tlv_link_identifier(lid)
		& mih::tlv_link_dn_reason(rs);
	
	ls->async_send(m);
}

// Dispatch a link_parameters_report event.
void dispatch_link_parameters_report(mih::link_tuple_id lid, mih::link_param_rpt_list &rpt_list)
{
	ODTONE_LOG(0, "(event) Dispatching link_parameters_report message.");

	mih::message m;
	m << mih::indication(mih::indication::link_parameters_report)
		& mih::tlv_link_identifier(lid)
		& mih::tlv_link_param_rpt_list(rpt_list);

	ls->async_send(m);
}

// Dispatch a link_detected event.
void dispatch_link_detected(mih::link_det_info &l)
{
	ODTONE_LOG(0, "(event) Dispatching link_detected message. SSID \"", l.network_id, "\"");

	mih::message m;
	m << mih::indication(mih::indication::link_detected)
		& mih::tlv_link_det_info(l);

	ls->async_send(m);
}

// Dispatches one link_detected per SSID (strongest signal), except for attached SSID.
void dispatch_strongest_scan_results(scan_results_data &d)
{
	std::map<mih::octet_string, bool> announced;
	if (d.associated_index) {
		announced[d.l[d.associated_index.get()].network_id] = true;
	}

	std::vector<mih::link_det_info>::iterator aux_it, strongest_it;
	std::vector<mih::link_det_info>::iterator l_it = d.l.begin();
	while (l_it != d.l.end()) {
		if (!announced[l_it->network_id]) {
			announced[l_it->network_id] = true;

			// this code just selects the strongest signal with the same SSID
			aux_it = strongest_it = l_it;
			while (aux_it != d.l.end()) {
				if (aux_it->network_id == strongest_it->network_id) {
					// compare the signal between both
					sint8 *aux_dbm = boost::get<sint8>(&aux_it->signal);
					sint8 *strongest_dbm = boost::get<sint8>(&strongest_it->signal);
					if (aux_dbm && strongest_dbm) {
						if (*aux_dbm > *strongest_dbm) {
							strongest_it = aux_it;
						}
					} else {
						mih::percentage *aux_pct = boost::get<mih::percentage>(&aux_it->signal);
						mih::percentage *strongest_pct = boost::get<mih::percentage>(&strongest_it->signal);
						if (aux_pct && strongest_pct) {
							if (*aux_pct > *strongest_pct) {
								strongest_it = aux_it;
							}
						}
					}
				}
				++aux_it;
			}
			ios.dispatch(boost::bind(&dispatch_link_detected, *strongest_it));
		}
		++l_it;
	}
}

///////////////////////////////////////////////////////////////////////////////
//// Handlers
///////////////////////////////////////////////////////////////////////////////

// For scheduled scans
void _trigger_scan()
{
	ODTONE_LOG(0, "(link) Triggering scheduled scan");
	if (_scanning) {
		ODTONE_LOG(0, "(link) Another ongoing scan detected");
		return;
	}

	try {
		// Consider changing to true for high frequency scanning (prevent overlapping)
		nl80211->trigger_scan(false);
	} catch (std::string str) {
		ODTONE_LOG(0, "Error triggering scheduled scan. \"", str, "\"");
	}
}

// For NL80211_CMD_GET_SCAN message.
int handle_scan_results(nl_msg *msg, void *arg)
{
	struct nlmsghdr *nlh = nlmsg_hdr(msg);
	struct genlmsghdr *gnlh = (genlmsghdr *)nlmsg_data(nlh);
	struct nlattr *tb[NL80211_ATTR_MAX + 1];
	struct nlattr *bss[NL80211_BSS_MAX + 1];
	char addr[3 * ETH_ALEN];
	scan_results_data *d = static_cast<scan_results_data*>(arg);

	nla_parse(tb, NL80211_ATTR_MAX, genlmsg_attrdata(gnlh, 0), genlmsg_attrlen(gnlh, 0), NULL);

	if (gnlh->cmd != NL80211_CMD_NEW_SCAN_RESULTS && gnlh->cmd != NL80211_CMD_SCAN_ABORTED) {
		return NL_SKIP;
	}

	if (!tb[NL80211_ATTR_BSS]) {
		ODTONE_LOG(0, "BSS info missing from scan dump item");
		return NL_SKIP;
	}

	if (nla_parse_nested(bss, NL80211_BSS_MAX, tb[NL80211_ATTR_BSS], bss_policy)) {
		ODTONE_LOG(0, "Error parsing scan dump item");
		return NL_SKIP;
	}

	if (!bss[NL80211_BSS_BSSID]
		|| !bss[NL80211_BSS_INFORMATION_ELEMENTS]
		|| (!bss[NL80211_BSS_SIGNAL_MBM] && !bss[NL80211_BSS_SIGNAL_UNSPEC])) {
		ODTONE_LOG(0, "Not all required elements in scan dump item");
		return NL_SKIP;
	}

	mih::link_det_info i;
	bool associated = false;

	// If associated to this one, store the channel id
	// For non standard frequencies, check the frequency_to_channel_id function
	if (bss[NL80211_BSS_STATUS]) {
		if (nla_get_u32(bss[NL80211_BSS_STATUS]) == NL80211_BSS_STATUS_ASSOCIATED) {
			if (bss[NL80211_BSS_FREQUENCY]) {
				unsigned int frequency = nla_get_u32(bss[NL80211_BSS_FREQUENCY]);
				d->associated_channel_id = frequency_to_channel_id(frequency);
				d->associated_index = d->l.size(); // .size(), before inserting!
				associated = true;
			}
		}
	}

	if (d->associated_only && !associated) {
		return NL_SKIP;
	}

	// Parse network name (specific information element. see scan.c from iw)
	unsigned char *ie = (unsigned char*)nla_data(bss[NL80211_BSS_INFORMATION_ELEMENTS]);
	int ielen = nla_len(bss[NL80211_BSS_INFORMATION_ELEMENTS]);
	i.network_id = get_essid(ie, ielen);
	if (i.network_id == "") {
		return NL_SKIP;
	}

	// Parse mac address
	mac_addr_n2a(addr, (unsigned char*)nla_data(bss[NL80211_BSS_BSSID]));
	mih::mac_addr mac(addr);
	i.id.type = link_id.type;
	i.id.addr = link_id.addr;
	i.id.poa_addr = mac;

	// Parse signal strength
	if (bss[NL80211_BSS_SIGNAL_MBM]) {
		int signal = (int)nla_get_u32(bss[NL80211_BSS_SIGNAL_MBM]) / 100;
		i.signal = signal;
	} else if(bss[NL80211_BSS_SIGNAL_UNSPEC]) {
		mih::percentage signal;
		signal = (unsigned int)nla_get_u8(bss[NL80211_BSS_SIGNAL_UNSPEC]);
		i.signal = signal;
	}

	// Parse the noise level. This value can be retrieved with a GET_SURVEY command
	// But it has to be after all scan results have been parsed!
	i.sinr = 0;

	// Parse data rate
	i.data_rate = get_max_supp_rate(ie, ielen);

	// Parse mih capabilities
	i.mih_capabilities = mih::link_mihcap_flag();

	// Parse (some) network capabilities
	mih::net_caps caps;
	if (has_security_features(ie, ielen)) {
		caps.set(mih::net_caps_security);
	}
	if (bss[NL80211_BSS_CAPABILITY]) {
		if (has_qos_capabilities(nla_get_u16(bss[NL80211_BSS_CAPABILITY]))) {
			caps.set(mih::net_caps_qos_0); // can't assume classes!
		}
	}
	i.net_capabilities = caps;

	d->l.push_back(i);

	if (d->associated_only && associated) {
		return NL_STOP;
	}

	return NL_SKIP;
}

// For cross-value-alert threshold types
void _check_global_thresholds()
{
	if (!subscribed_event_list.get(mih::evt_link_parameters_report)) { return; }
	ODTONE_LOG(0, "(link) Performing periodic threshold check");

	scan_results_data d(true);

	nl80211->get_scan_results(handle_scan_results, &d);
	if (!d.associated_index) {
		ODTONE_LOG(0, "(link) Scan dump did not return associated station info");
		return;
	}

	mih::link_det_info i = d.l[d.associated_index.get()];
	mih::link_tuple_id lid = i.id;
	mih::link_param_rpt_list rpt_list;

	sint8 *d_signal = boost::get<sint8>(&i.signal);
	if (!d_signal) {
		ODTONE_LOG(0, "(link) Periodic data did not include RSSI");
		return;
	}

	boost::unique_lock<boost::shared_mutex> lock(_th_list_mutex); // easier for now

	std::vector<threshold_cross_data>::iterator th_it = th_cross_list.begin();
	while (th_it != th_cross_list.end()) {
		boost::optional<boost::variant<mih::link_param_val, mih::qos_param_val>> value;

		if (th_it->type == mih::link_param_802_11_rssi) {
			sint8 t_signal = static_cast<sint8>(th_it->th.threshold_val);

			ODTONE_LOG(0, "(link) Checking threshold RSSI value ", (int)t_signal,
				", cross dir ", th_it->th.threshold_x_dir, ", against ", *d_signal);

			if (th_it->th.threshold_x_dir == mih::threshold::above_threshold) {
				if (*d_signal > t_signal) {
					ODTONE_LOG(0, "(link) Current RSSI (", (int)*d_signal, ") above ", (int)t_signal);
					value = static_cast<uint16>(*d_signal);
				}
			} else /*if (the.threshold_x_dir == mih::threshold::below_threshold) */{
				if (*d_signal < t_signal) {
					ODTONE_LOG(0, "(link) Current RSSI (", (int)*d_signal, ") below ", (int)t_signal);
					value = static_cast<uint16>(*d_signal);
				}
			}
//		} else {
//			// No other supported
		}

		if (value) {
			mih::link_param_report rpt;
			rpt.param.type = th_it->type;
			rpt.param.value = value.get();
			rpt.thold = th_it->th;
			rpt_list.push_back(rpt);
		}

		if (value && th_it->one_shot) {
			ODTONE_LOG(0, "(link) Removing one-shot type threshold from list");
			th_it = th_cross_list.erase(th_it);
		} else {
			++th_it;
		}
	}

	if (rpt_list.size() > 0) {
		ios.dispatch(boost::bind(&dispatch_link_parameters_report, lid, rpt_list));
	}
}

// For multicast messages from the kernel (groups "scan", "mlme", etc)
int handle_nl_event(nl_msg *msg, void *arg)
{
	struct nlmsghdr *nlh = nlmsg_hdr(msg);
	struct genlmsghdr *gnlh = (genlmsghdr *)nlmsg_data(nlh);
	struct nlattr *tb[NL80211_ATTR_MAX + 1];

	nla_parse(tb, NL80211_ATTR_MAX, genlmsg_attrdata(gnlh, 0), genlmsg_attrlen(gnlh, 0), NULL);

	if(!tb[NL80211_ATTR_IFINDEX] || nl80211->if_index() != nla_get_u32(tb[NL80211_ATTR_IFINDEX])) {
		return NL_SKIP;
	}

	// Parse the event
	switch (gnlh->cmd) {
	case NL80211_CMD_TRIGGER_SCAN:
		{
			// This event is caught just to set this variable,
			// and try to prevent overlapping ongoing scans
			ODTONE_LOG(0, "(nl mc) Scan started");
			_scanning = true;
		}
		break;
	case NL80211_CMD_CONNECT: // LINK_UP
		{
			ODTONE_LOG(0, "(nl mc) Connect event");
			if (!subscribed_event_list.get(mih::evt_link_up)) { break; }

			if (!tb[NL80211_ATTR_STATUS_CODE]) {
				ODTONE_LOG(0, "(nl mc) Unknown connect status");
			} else if (nla_get_u16(tb[NL80211_ATTR_STATUS_CODE]) == 0) {
				ODTONE_LOG(0, "(nl mc) Connection success");
				if (tb[NL80211_ATTR_MAC]) {
					char addr[3 * ETH_ALEN];
					mac_addr_n2a(addr, (unsigned char*)nla_data(tb[NL80211_ATTR_MAC]));
					mih::mac_addr mac(addr);
					ios.dispatch(boost::bind(&dispatch_link_up, mac));
				} else {
					ios.dispatch(boost::bind(&dispatch_link_up));
				}
			} else {
				ODTONE_LOG(0, "(nl mc) Connection failure, code ", nla_get_u16(tb[NL80211_ATTR_STATUS_CODE]));
			}
		}
		break;

//	case NL80211_CMD_DEAUTHENTICATE:
//	case NL80211_CMD_DISASSOCIATE:
	case NL80211_CMD_DISCONNECT: // LINK_DOWN
		{
			ODTONE_LOG(0, "(nl mc) Disconnect");
			if (!subscribed_event_list.get(mih::evt_link_down)) { break; }

			unsigned short reason_code = 0; // "local request"
			if (tb[NL80211_ATTR_REASON_CODE]) {
				reason_code = nla_get_u16(tb[NL80211_ATTR_REASON_CODE]);
			}

			ios.dispatch(boost::bind(&dispatch_link_down, reason_code));
		}
		break;

	case NL80211_CMD_SCAN_ABORTED: // LINK_DETECTED?
		{
			_scanning = false;
			ODTONE_LOG(0, "(nl mc) Scan aborted");
		}
		break;
	case NL80211_CMD_NEW_SCAN_RESULTS: // LINK DETECTED
		{
			_scanning = false;
			ODTONE_LOG(0, "(nl mc) New scan results");
			if (!subscribed_event_list.get(mih::evt_link_detected)) { break; }

			// The multicast message just informs of new results.
			// The complete information must be retrieved with a GET_SCAN.

			scan_results_data d;
			nl80211->get_scan_results(handle_scan_results, static_cast<void*>(&d));
			dispatch_strongest_scan_results(d);
		}
		break;

	default:
		break;
	}

	return NL_SKIP;
}

// For periodic metric reporting
void periodic_report_data::_report_value()
{
	ODTONE_LOG(0, "(link) Handling periodic report");
	boost::shared_lock<boost::shared_mutex> lock(_th_list_mutex);

	mih::link_param_rpt_list rpt_list;
	mih::link_tuple_id lid;

	if (type == mih::link_param_802_11_rssi) {
		scan_results_data d(true);
		nl80211->get_scan_results(handle_scan_results, &d);
		if (!d.associated_index) {
			ODTONE_LOG(0, "(link) Scan dump did not return associated station info");
			return;
		}

		mih::link_param_report rpt;

		rpt.param.type = type;

		uint index = d.associated_index.get();
		lid = d.l[index].id;

		sint8 *d_signal = boost::get<sint8>(&d.l[index].signal);
		rpt.param.value = *d_signal;

		rpt_list.push_back(rpt);
//	} else if (type == mih::link_param_802_11_no_qos) {
//		// not supported
//	} else if (type == mih::link_param_802_11_multicast_packet_loss_rate) {
//		// not supported
	}

	ios.dispatch(boost::bind(&dispatch_link_parameters_report, lid, rpt_list));
}

///////////////////////////////////////////////////////////////////////////////
//// Command handling functions
///////////////////////////////////////////////////////////////////////////////

// Dispatch failure message for command errors.
void dispatch_status_failure(uint16 tid, mih::confirm::mid mid)
{
	ODTONE_LOG(0, "(cmd) Dispatching status_failure");

	mih::message m;
	mih::status st = mih::status_failure;

	m << mih::confirm(mid)
		& mih::tlv_status(st);

	m.tid(tid);

	ls->async_send(m);
}

// Dispatch a capability_discover confirm.
// Fully supported, but check the supported events and commands lists.
void handle_capability_discover(uint16 tid)
{
	ODTONE_LOG(0, "(cmd) Handling capability_discover");

	ODTONE_LOG(0, "(cmd) Dispatching status success");

	mih::message m;
	mih::status st = mih::status_success;

	m << mih::confirm(mih::confirm::capability_discover)
		& mih::tlv_status(st)
		& mih::tlv_link_evt_list(capabilities_event_list)
		& mih::tlv_link_cmd_list(capabilities_command_list);

	m.tid(tid);

	ls->async_send(m);
}

// Dispatch an event_subscribe confirm.
// Fully supported, but check the supported events list.
void handle_event_subscribe(uint16 tid, mih::link_evt_list &events)
{
	ODTONE_LOG(0, "(cmd) Handling event_subscribe");

	// Set the common events between the requested and the supported
	// (will not successfully subscribe unsupported events...)
	events.common(capabilities_event_list);

	// Save the new list (don't unsubscribe previous bits!)
	subscribed_event_list.merge(events);

	ODTONE_LOG(0, "(cmd) Dispatching status success");

	mih::message m;
	mih::status st = mih::status_success;

	m << mih::confirm(mih::confirm::event_subscribe)
		& mih::tlv_status(st)
		& mih::tlv_link_evt_list(events);

	m.tid(tid);

	ls->async_send(m);
}

// Dispatch an event unsubscribe confirm.
// Fully supported, but check the supported events list.
void handle_event_unsubscribe(uint16 tid, mih::link_evt_list &events)
{
	ODTONE_LOG(0, "(cmd) Handling event_unsubscribe");

	// Set the common events between the requested and the supported
	// (will not successfully unsubscribe unsupported events...)
	events.common(capabilities_event_list);

	// Remove the requested events from the subscription list
	subscribed_event_list.except(events);

	ODTONE_LOG(0, "(cmd) Dispatching status success");

	mih::message m;
	mih::status st = mih::status_success;

	m << mih::confirm(mih::confirm::event_unsubscribe)
		& mih::tlv_status(st)
		& mih::tlv_link_evt_list(events);

	m.tid(tid);

	ls->async_send(m);
}

// Dispatch a link_get_parameters confirm.
// Partially supported.
//
// Fails if scan fails to return an associated network.
// Aditionally, will fail if requesting any parameter outside of this list:
// - link_param_802_11_rssi, link_states_req_op_mode, link_states_req_channel_id
void handle_link_get_parameters(uint16 tid,
		mih::link_param_type_list &param_list,
		mih::link_states_req &states_req,
		mih::link_desc_req &desc_req)
{
	ODTONE_LOG(0, "(cmd) Handling link_get_parameters");

	try {
	// NOTE: Most effective code would use a GET_STATION command,
	//       but that won't yield all the required information...
	scan_results_data d(true);
	nl80211->get_scan_results(handle_scan_results, static_cast<void*>(&d));

	// If the scan results failed to return associated ap, fail
	if (!d.associated_index) {
		ODTONE_LOG(0, "(cmd) Scan dump did not return associated station info");
		dispatch_status_failure(tid, mih::confirm::link_get_parameters);
		return;
	}

	mih::link_det_info ap_info = d.l[d.associated_index.get()];

	mih::link_param_list status_list;
	mih::link_param status_param;

	BOOST_FOREACH (mih::link_param_type &pt, param_list) {
		mih::link_param_802_11 *param = boost::get<mih::link_param_802_11>(&pt);
		if (!param) {
			ODTONE_LOG(0, "No link_param_802_11 link_param_type specified");
			dispatch_status_failure(tid, mih::confirm::link_get_parameters);
			return;
		}

		mih::link_param status_param;
		status_param.type = *param;

		if (*param == mih::link_param_802_11_rssi) {
			if (mih::percentage *v = boost::get<mih::percentage>(&ap_info.signal)) {
				status_param.value = (uint)*v;
			} else if (sint8 *v = boost::get<sint8>(&ap_info.signal)) {
				status_param.value = *v;
			}
		} else if (*param == mih::link_param_802_11_no_qos) {
			status_param.value = !ap_info.net_capabilities.get(mih::net_caps_qos_0);
		} else if (*param == mih::link_param_802_11_multicast_packet_loss_rate) {
			// not supported
			ODTONE_LOG(0, "No support for specified link_param_802_11");
			dispatch_status_failure(tid, mih::confirm::link_get_parameters);
			return;
		} else {
			// huh??
			ODTONE_LOG(0, "No support for specified link_param_802_11");
			dispatch_status_failure(tid, mih::confirm::link_get_parameters);
			return;
		}

		status_list.push_back(status_param);
	}

	mih::link_states_rsp_list states_list;
	mih::link_states_rsp states_param;
	if (states_req.get(mih::link_states_req_channel_id)) {
		states_param = d.associated_channel_id.get();
		states_list.push_back(states_param);
	}
	if (states_req.get(mih::link_states_req_op_mode)) {
		states_param = nl80211->get_op_mode();
		states_list.push_back(states_param);
	}

	mih::link_desc_rsp_list desc_list;
	if (desc_req.get(mih::link_desc_req_classes_of_service_supported)) {
		// not supported
		ODTONE_LOG(0, "No support for specified link_desc_req");
		dispatch_status_failure(tid, mih::confirm::link_get_parameters);
		return;
	}
	if (desc_req.get(mih::link_desc_req_queues_supported)) {
		// not supported
		ODTONE_LOG(0, "No support for specified link_desc_req");
		dispatch_status_failure(tid, mih::confirm::link_get_parameters);
		return;
	}

	ODTONE_LOG(0, "(cmd) Dispatching status success");

	mih::message m;
	mih::status st = mih::status_success;

	m << mih::confirm(mih::confirm::link_get_parameters)
		& mih::tlv_status(st)
		& mih::tlv_link_parameters_status_list(status_list)
		& mih::tlv_link_states_rsp(states_list)
		& mih::tlv_link_descriptor_rsp(desc_list);

	m.tid(tid);

	ls->async_send(m);
	} catch (std::string str) {
		ODTONE_LOG(0, "(cmd) Exception: ", str);
		dispatch_status_failure(tid, mih::confirm::link_get_parameters);
	}
}

// Dispatch a link_configure_thresholds confirm
// Partially supported. Only RSSI, for now!
void handle_link_configure_thresholds(uint16 tid,
		mih::link_cfg_param_list &param_list)
{
	ODTONE_LOG(0, "(cmd) Handling link_configure_thresholds");

	bool fail = false;

	try {
	std::vector<threshold_cross_data> cross_list;
	std::vector<periodic_report_data> rpt_list;

	std::vector<threshold_cross_data>::iterator cross_it;
	std::vector<periodic_report_data>::iterator rpt_it;

	mih::link_cfg_status_list status_list;

	BOOST_FOREACH (mih::link_cfg_param &param, param_list) {
		mih::link_param_802_11 *type = boost::get<mih::link_param_802_11>(&param.type);
		if (!type) {
			ODTONE_LOG(0, "(cmd) No link_param_802_11 link_param_type specified");
			fail = true;
			break;
		}
		if (*type != mih::link_param_802_11_rssi) {
			ODTONE_LOG(0, "(cmd) No support for specified link_param_802_11");
			fail = true;
			break;
		}

		if (param.action == mih::th_action_cancel) { // cancel thresholds
			boost::unique_lock<boost::shared_mutex> lock(_th_list_mutex);

			if (param.threshold_list.size() == 0) { // cancel all of type 'type'
				ODTONE_LOG(0, "(cmd) Cancelling all configured thresholds of type ", *type);

				cross_it = th_cross_list.begin();
				while (cross_it != th_cross_list.end()) {
					if (cross_it->type == *type) {
						cross_it = th_cross_list.erase(cross_it);
					} else {
						++cross_it;
					}
				}

				rpt_it = period_rpt_list.begin();
				while (rpt_it != period_rpt_list.end()) {
					if (rpt_it->type == *type) {
						delete rpt_it->task;
						rpt_it = period_rpt_list.erase(rpt_it);
					} else {
						++rpt_it;
					}
				}
			} else { // cancel specific only.
				ODTONE_LOG(0, "(cmd) Cancelling some thresholds of type ", *type);

				BOOST_FOREACH (mih::threshold &th, param.threshold_list) {
					cross_it = th_cross_list.begin();
					while (cross_it != th_cross_list.end()) {
						if (cross_it->type == *type
							&& cross_it->th.threshold_val == th.threshold_val
							&& cross_it->th.threshold_x_dir == th.threshold_x_dir) {
							cross_it = th_cross_list.erase(cross_it);
						} else {
							++cross_it;
						}
					}
				}
			}
		} else { // insert it
			uint16 *period = boost::get<uint16>(&param.timer_interval);
			if (period) {
				// dealing with a periodic configuration
				ODTONE_LOG(0, "(cmd) Inserting periodic report");

				periodic_report_data p;
				p.type = *type;
				p.task = new timer_task(ios, *period, boost::bind(&periodic_report_data::_report_value, p));
				rpt_list.push_back(p);
			} else {
				// dealing with a value-crossing threshold configuration
				BOOST_FOREACH (mih::threshold &th, param.threshold_list) {
					ODTONE_LOG(0, "(cmd) Inserting value-cross-alert threshold");

					threshold_cross_data t;
					t.one_shot = param.action == mih::th_action_one_shot;
					t.type = *type;
					t.th = th;
					cross_list.push_back(t);

					mih::link_cfg_status status;
					status.type = *type;
					status.thold = th;
					status.status = true;
					status_list.push_back(status);
				}
			}
		}

		if (fail) {
			break;
		}
	}

	if (fail) {
		// cleanup
		BOOST_FOREACH (periodic_report_data &d, rpt_list) {
			delete d.task;
		}

		// fail
		dispatch_status_failure(tid, mih::confirm::link_configure_thresholds);
		return;
	}

	// Merge valid configurations
	if (cross_list.size() > 0 || rpt_list.size() > 0) {
		boost::unique_lock<boost::shared_mutex> lock(_th_list_mutex);

		// Merge valid configurations
		th_cross_list.insert(th_cross_list.end(), cross_list.begin(), cross_list.end());
		period_rpt_list.insert(period_rpt_list.end(), rpt_list.begin(), rpt_list.end());
	}

	// Start/stop periodic threshold check based on threshold configuration existence
	if (th_cross_list.size() > 0 && !_th_check->running()) {
		_th_check->start();
	} else if (th_cross_list.size() == 0 && _th_check->running()) {
		_th_check->stop();
	}

	// Launch periodic tasks
	for (rpt_it = rpt_list.begin(); rpt_it != rpt_list.end(); ++rpt_it) {
		rpt_it->task->start();
	}

	ODTONE_LOG(0, "(cmd) Dispatching status success");

	mih::message m;
	mih::status st = mih::status_success;

	m << mih::confirm(mih::confirm::link_configure_thresholds)
		& mih::tlv_status(st)
		& mih::tlv_link_cfg_status_list(status_list);

	m.tid(tid);

	ls->async_send(m);
	} catch (std::string str) {
		ODTONE_LOG(0, "(cmd) Exception: ", str);
		dispatch_status_failure(tid, mih::confirm::link_configure_thresholds);
	}
}

// Dispatch a link actions confirm.
// Partially supported.
//
// Will fail if requested attributes include:
// - data_fwd_req, link_res_retain
//
// Scan might fail if action type is power_down.
//
// Aditionally, a failure will occur if the process has no
// permission to perform such actions on the link.
//
// Low power mode cannot be enforced here,
// instead we just enable power saving features on the device.
void handle_link_actions(uint16 tid,
		mih::link_action action,
		uint16 delay,
		boost::optional<mih::link_addr> poa)
{
	ODTONE_LOG(0, "(cmd) Handling link_action");
	// Use specific "ac_results" instead of status failure?

	try {
	// This should be processed after the delay, but
	// it's being processed before due to the lack of support
	if (action.attr.get(mih::link_ac_attr_data_fwd_req)) {
		// not supported
		ODTONE_LOG(0, "(cmd) No support for specified link_ac_attr");
		dispatch_status_failure(tid, mih::confirm::link_actions);
		return;
	}
	if (action.attr.get(mih::link_ac_attr_res_retain)) {
		// not supported
		ODTONE_LOG(0, "(cmd) No support for specified link_ac_attr");
		dispatch_status_failure(tid, mih::confirm::link_actions);
		return;
	}
	if (poa) {
		// not supported
		ODTONE_LOG(0, "(cmd) No support for specified attribute (poa addr)");
		dispatch_status_failure(tid, mih::confirm::link_actions);
		return;
	}

	if (delay > 0) {
		boost::asio::deadline_timer timer(ios);
		timer.expires_from_now(boost::posix_time::milliseconds(delay));
		timer.wait();
		// Should we async_wait, and free the link_sap for more message processing?
	}

	nl80211->set_op_mode(action.type.get());

	mih::link_scan_rsp_list scan_rsp_list;
	if (action.type != mih::link_ac_type_power_down) {
		if (action.attr.get(mih::link_ac_attr_scan)) {
			// We could check if there's an ongoing scan and just wait
			// for the results, but they could arrive in the meantime,
			// and then we'd be facing a race condition
			nl80211->trigger_scan(true);

			scan_results_data d;
			nl80211->get_scan_results(handle_scan_results, static_cast<void*>(&d));

			BOOST_FOREACH (mih::link_det_info &i, d.l) {
				mih::link_scan_rsp scan_rsp;
				scan_rsp.id = boost::get<mih::link_addr>(i.id.poa_addr);
				scan_rsp.net_id = i.network_id;
				scan_rsp.signal = i.signal;
				scan_rsp_list.push_back(scan_rsp);
			}
		}
	}

	ODTONE_LOG(0, "(cmd) Dispatching status success");

	mih::message m;
	mih::status st = mih::status_success;

	m << mih::confirm(mih::confirm::link_actions)
		& mih::tlv_status(st)
		& mih::tlv_link_scan_rsp_list(scan_rsp_list)
		& mih::tlv_link_ac_result(mih::link_ac_success);

	m.tid(tid);

	ls->async_send(m);
	} catch (std::string str) {
		// This status_failure is tricky. For example, the scan operation
		// may throw an exception, but the oper_mode is still correctly set!
		ODTONE_LOG(0, "(cmd) Exception: ", str);
		dispatch_status_failure(tid, mih::confirm::link_actions);
	}
}

///////////////////////////////////////////////////////////////////////////////
//// Special MIHF callback
///////////////////////////////////////////////////////////////////////////////

// Callback for MIHF-sent messages (commands).
void default_handler(mih::message& msg, const boost::system::error_code& ec)
{
	if (ec) {
		return;
	}

	switch (msg.mid()) {
	case mih::request::capability_discover:
		{
			ODTONE_LOG(0, "(cmd) Received cpability_discover message");
			handle_capability_discover(msg.tid());
		}
		break;

	case mih::request::event_subscribe:
		{
			ODTONE_LOG(0, "(cmd) Received event_subscribe message");
			mih::link_evt_list events;
				msg >> mih::request()
				& mih::tlv_link_evt_list(events);

			handle_event_subscribe(msg.tid(), events);
		}
		break;

	case mih::request::event_unsubscribe:
		{
			ODTONE_LOG(0, "(cmd) Received event_unsubscribe message");
			mih::link_evt_list events;
			msg >> mih::request()
				& mih::tlv_link_evt_list(events);

			handle_event_unsubscribe(msg.tid(), events);
		}
		break;

	case mih::request::link_get_parameters:
		{
			ODTONE_LOG(0, "(cmd) Received link_get_parameters message");
			mih::message m;

			mih::link_param_type_list param_list;
			mih::link_states_req states_req;
			mih::link_desc_req desc_req;

			msg >> mih::request()
				& mih::tlv_link_parameters_req(param_list)
				& mih::tlv_link_states_req(states_req)
				& mih::tlv_link_descriptor_req(desc_req);

			handle_link_get_parameters(msg.tid(), param_list, states_req, desc_req);
		}
		break;

	case mih::request::link_configure_thresholds:
		{
			ODTONE_LOG(0, "(cmd) Received link_configure_thresholds message");
			mih::link_cfg_param_list param_list;

			msg >> mih::request()
				& mih::tlv_link_cfg_param_list(param_list);

			handle_link_configure_thresholds(msg.tid(), param_list);
		}
		break;

	case mih::request::link_actions:
		{
			ODTONE_LOG(0, "(cmd) Received link_actions message");
			mih::link_action action;
			uint16 delay;
			boost::optional<mih::link_addr> poa;

			msg >> mih::request()
				& mih::tlv_link_action(action)
				& mih::tlv_time_interval(delay)
				& mih::tlv_poa(poa);

			handle_link_actions(msg.tid(), action, delay, poa);
		}
		break;

	default:
		ODTONE_LOG(0, "(cmd) Received unknown message");
		dispatch_status_failure(msg.tid(), mih::confirm::capability_discover);
	}
}

///////////////////////////////////////////////////////////////////////////////
//// Main
///////////////////////////////////////////////////////////////////////////////

// Main entry point
int main(int argc, char** argv)
{
	setup_crash_handler();

	std::map<uint32, std::string> msg_type_map;

	if (geteuid()) {
		std::cerr << "###########" << std::endl;
		std::cerr << "# WARNING: some functionalities may fail without root privileges" << std::endl;
		std::cerr << "###########" << std::endl;
	}

	try {
		// Declare Link SAP available options
		po::options_description desc("MIH Link SAP Configuration");
		desc.add_options()
			("help", "Display configuration options")
			(kConf_Dev_Id, po::value<std::string>()->default_value("wlan0"), "Device name")
			(kConf_Sched_Scan_Period, po::value<uint>()->default_value(0), "Scheduled scan interval (millis)")
			(kConf_Default_Threshold_Period, po::value<uint>()->default_value(1000), "Default threshold checking interval (millis)")
			(sap::kConf_Port, po::value<ushort>()->default_value(1235), "Port")
			(sap::kConf_File, po::value<std::string>()->default_value("nl80211_sap.conf"), "Configuration File")
			(sap::kConf_Receive_Buffer_Len, po::value<uint>()->default_value(4096), "Receive Buffer Length")
			(sap::kConf_MIHF_Ip, po::value<std::string>()->default_value("127.0.0.1"), "Local MIHF Ip")
			(sap::kConf_MIHF_Local_Port, po::value<ushort>()->default_value(1025), "MIHF Local Communications Port")
			(sap::kConf_MIHF_Id, po::value<std::string>()->default_value("local-mihf"), "Local MIHF Id")
			(sap::kConf_MIH_SAP_id, po::value<std::string>()->default_value("link"), "Link SAP Id");

		mih::config cfg(desc);
		cfg.parse(argc, argv, sap::kConf_File);

		if (cfg.help()) {
			std::cerr << desc << std::endl;
			return EXIT_SUCCESS;
		}

		// Check and set the default threshold period
		uint th_period = cfg.get<uint>(kConf_Default_Threshold_Period);
		if (th_period < 0) {
			ODTONE_LOG(0, "(link) Invalid threshold period specified");
			return EXIT_FAILURE;
		}
		_th_check = new timer_task(ios, th_period, boost::bind(&_check_global_thresholds));

		// Generic netlink setup
		std::vector<std::string> multicast_groups;
		multicast_groups.push_back("mlme");
		multicast_groups.push_back("scan"); // "config", "regulatory"

		nl80211 = new nl80211_helper(cfg.get<std::string>(kConf_Dev_Id));
		nl80211->init();
		nl80211->set_custom_callback(handle_nl_event, NULL);
		nl80211->join_multicast_groups(multicast_groups);

		init_bss_policy(bss_policy);

		// Set some local variables
		set_link_id();
		set_supported_event_list();
		set_supported_command_list();

		// Create and initialize the link_sap
		ls = new sap::link(cfg, ios, boost::bind(&default_handler, _1, _2));
		mihf_sap_init();

		// Initialize the io service
		boost::thread io(boost::bind(&boost::asio::io_service::run, &ios));

		// Start the scheduled scan, if configured to.
		uint scan_period = cfg.get<uint>(kConf_Sched_Scan_Period);
		timer_task *sched_scan;
		if (scan_period > 0) {
			sched_scan = new timer_task(ios, scan_period, boost::bind(&_trigger_scan));
			sched_scan->start();
		}

		ODTONE_LOG(0, "(link) Setup completed");

		while (!nl80211->error()) {
			nl80211->recv_msgs();
		}
	} catch(std::exception& e) {
		std::cerr << "exception: " << e.what() << std::endl;
	} catch(const char* str) {
		std::cerr << "exception: " << str << std::endl;
	} catch(std::string str) {
		std::cerr << "exception: " << str << std::endl;
	}
	
	delete nl80211;
	delete ls;
	delete _th_check;
}

// EOF ////////////////////////////////////////////////////////////////////////
