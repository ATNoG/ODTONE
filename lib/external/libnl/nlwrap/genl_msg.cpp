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

#include "genl_msg.hpp"

#include <netlink/genl/genl.h>

#include <stdexcept>

namespace nlwrap {

#define ETH_NLEN 6
#define ETH_ALEN 18

// Information elements
#define IE_SSID              0
#define IE_SUPP_RATES        1
#define IE_RSN              48
#define IE_EXT_SUPP_RATES   50
#define IE_INTERWORKING    107
#define IE_ADVERT_PROTO    108
#define IE_VENDOR          221

#define IE_VENDOR_MS_CIPHER_MAX   6
#define IE_VENDOR_IEEE_CIPHER_MAX 7

#define WLAN_CAPABILITY_QOS (1<<9)

struct bss_parse_policy {
	::nla_policy pol[NL80211_BSS_MAX + 1];
	bss_parse_policy();
} bss_policy;

struct stats_parse_policy {
	::nla_policy pol[NL80211_STA_INFO_MAX + 1];
	stats_parse_policy();
} stats_policy;

struct rate_parse_policy {
	::nla_policy pol[NL80211_RATE_INFO_MAX + 1];
	rate_parse_policy();
} rate_policy;

struct cqm_parse_policy {
	::nla_policy pol[NL80211_ATTR_CQM_MAX + 1];
	cqm_parse_policy();
} cqm_policy;

void mac_addr_n2a(char *mac_addr, unsigned char *arg);
int mac_addr_a2n(unsigned char *mac_addr, char *arg);

////////////////////////////////////////////////////////////////////////

genl_msg::genl_msg() : nl_msg()
{
}

genl_msg::genl_msg(int family, int type, int flags) : nl_msg()
{
	::genlmsg_put(_msg, 0, 0, family, 0, flags, type, 0);
}

genl_msg::genl_msg(::nl_msg *msg) : nl_msg(msg)
{
	::nlmsghdr    *nlh = ::nlmsg_hdr(_msg);
	::genlmsghdr *gnlh = static_cast< ::genlmsghdr * >(::nlmsg_data(nlh));
	_cmd = gnlh->cmd;

	// parse attr
	::nlattr *tb[NL80211_ATTR_MAX + 1];
	if (nla_parse(tb, NL80211_ATTR_MAX, ::genlmsg_attrdata(gnlh, 0), ::genlmsg_attrlen(gnlh, 0), NULL)) {
		throw std::runtime_error("Error parsing nl_msg attributes");
	}
	parse_attr(tb);

	// parse station info
	if (tb[NL80211_ATTR_STA_INFO]) {
		::nlattr *sta[NL80211_STA_INFO_MAX + 1];
		if (::nla_parse_nested(sta, NL80211_STA_INFO_MAX, tb[NL80211_ATTR_STA_INFO], stats_policy.pol)) {
			throw std::runtime_error("Error parsing nl_msg station attributes");
		}
		parse_sta(sta);
	}
	
	// parse cqm event
	if (tb[NL80211_ATTR_CQM]) {
		::nlattr *cqm[NL80211_ATTR_CQM_MAX + 1];
		if (::nla_parse_nested(cqm, NL80211_ATTR_CQM_MAX, tb[NL80211_ATTR_CQM], cqm_policy.pol)) {
			throw std::runtime_error("Error parsing nl_msg cqm attributes");
		}
		parse_cqm(cqm);
	}

	// parse bss
	if (!tb[NL80211_ATTR_BSS]) {
		return;
	}

	::nlattr *bss[NL80211_BSS_MAX + 1];
	if (::nla_parse_nested(bss, NL80211_BSS_MAX, tb[NL80211_ATTR_BSS], bss_policy.pol)) {
		throw std::runtime_error("Error parsing nl_msg bss attributes");
	}
	parse_bss(bss);

	// parse information elements
	if (!bss[NL80211_BSS_INFORMATION_ELEMENTS]) {
		return;
	}

	unsigned char *ie = static_cast<unsigned char *>(::nla_data(bss[NL80211_BSS_INFORMATION_ELEMENTS]));
	int ielen = ::nla_len(bss[NL80211_BSS_INFORMATION_ELEMENTS]);
	parse_information_elements(ie, ielen);
}

void genl_msg::put_ifindex(int ifindex)
{
	if (::nla_put_u32(_msg, NL80211_ATTR_IFINDEX, ifindex)) {
		throw std::runtime_error("Error putting IFINDEX in nl_msg");
	}
}

void genl_msg::put_family_name(std::string name)
{
	if (::nla_put_string(_msg, CTRL_ATTR_FAMILY_NAME, name.c_str())) {
		throw std::runtime_error("Error putting FAMILY_NAME in nl_msg");
	}
}

#ifdef NL80211_ATTR_PS_STATE
void genl_msg::put_ps_state(int state)
{
	if (::nla_put_u32(_msg, NL80211_ATTR_PS_STATE, state)) {
		throw std::runtime_error("Error putting PS_STATE in nl_msg");
	}
}
#endif /* NL80211_ATTR_PS_STATE */

void genl_msg::put_active_scanning()
{
	// set empty ssid list with "" wildcard for active scanning
	std::vector<std::string> ssids;
	ssids.push_back("");

	nl_msg nested;
	nested.put_ssids(ssids);

	if (::nla_put_nested(_msg, NL80211_ATTR_SCAN_SSIDS, nested)) {
		throw std::runtime_error("Error putting nested SSID list");
	}
}

void genl_msg::put_mac(const std::string &mac)
{
	unsigned char nmac[ETH_NLEN];
	if (!mac_addr_a2n(nmac, const_cast<char *>(mac.c_str()))) {
		throw std::runtime_error("Invalid mac address given");
	}

	if(::nla_put(_msg, NL80211_ATTR_MAC, ETH_NLEN, nmac)) {
		throw std::runtime_error("Error putting MAC in nl_msg");
	}
}

int genl_msg::cmd()
{
	return _cmd;
}

void genl_msg::put_cqm(int rssi_threshold, int hysteresis)
{
	nl_msg nested;
	nested.put_cqm(rssi_threshold, hysteresis);

	if (::nla_put_nested(_msg, NL80211_ATTR_CQM, nested)) {
		throw std::runtime_error("Error putting nested CQM parameters");
	}
}

void genl_msg::parse_attr(::nlattr *tb[NL80211_ATTR_MAX + 1])
{
	if (tb[NL80211_ATTR_IFINDEX]) {
		attr_ifindex = ::nla_get_u32(tb[NL80211_ATTR_IFINDEX]);
	}

	if (tb[NL80211_ATTR_STATUS_CODE]) {
		attr_status_code = ::nla_get_u16(tb[NL80211_ATTR_STATUS_CODE]);
	}

	if (tb[NL80211_ATTR_MAC]) {
		char addr[ETH_ALEN];
		mac_addr_n2a(addr, static_cast<unsigned char *>(::nla_data(tb[NL80211_ATTR_MAC])));
		attr_mac = std::string(addr, ETH_ALEN);
	}

	if (tb[NL80211_ATTR_REASON_CODE]) {
		attr_reason_code = ::nla_get_u16(tb[NL80211_ATTR_REASON_CODE]);
	}
	
	if (tb[NL80211_ATTR_IFTYPE]) {
		attr_iftype = ::nla_get_u32(tb[NL80211_ATTR_IFTYPE]);
	}

#ifdef NL80211_ATTR_PS_STATE
	if (tb[NL80211_ATTR_PS_STATE]) {
		attr_ps_state = ::nla_get_u32(tb[NL80211_ATTR_PS_STATE]);
	}
#endif /* NL80211_ATTR_PS_STATE */

	if (tb[NL80211_ATTR_BSS]) {
		attr_bss = true;
	}
}

void genl_msg::parse_cqm(::nlattr *cqm[NL80211_ATTR_CQM_MAX + 1])
{
	if (cqm[NL80211_ATTR_CQM_RSSI_THRESHOLD_EVENT]) {
		cqm_threshold_below =  ::nla_get_u32(cqm[NL80211_ATTR_CQM_RSSI_THRESHOLD_EVENT])
		                      == NL80211_CQM_RSSI_THRESHOLD_EVENT_LOW;
	}
}

void genl_msg::parse_bss(::nlattr *bss[NL80211_BSS_MAX + 1])
{
	if (bss[NL80211_BSS_STATUS]) {
		bss_status = ::nla_get_u32(bss[NL80211_BSS_STATUS]);
	}

	if (bss[NL80211_BSS_FREQUENCY]) {
		bss_frequency = ::nla_get_u32(bss[NL80211_BSS_FREQUENCY]);
	}

	if (bss[NL80211_BSS_BSSID]) {
		char addr[ETH_ALEN];
		mac_addr_n2a(addr, static_cast<unsigned char *>(::nla_data(bss[NL80211_BSS_BSSID])));
		bss_bssid = std::string(addr, ETH_ALEN);
	}

	if (bss[NL80211_BSS_SIGNAL_MBM]) {
		bss_signal_mbm = static_cast<int>(::nla_get_u32(bss[NL80211_BSS_SIGNAL_MBM])) / 100;
	}

	if (bss[NL80211_BSS_CAPABILITY]) {
		bss_qos_capable = ::nla_get_u16(bss[NL80211_BSS_CAPABILITY]) & WLAN_CAPABILITY_QOS;
	}
}

void genl_msg::parse_sta(::nlattr *sta[NL80211_STA_INFO_MAX + 1])
{
	if (sta[NL80211_STA_INFO_SIGNAL]) {
		sta_info_signal = nla_get_u8(sta[NL80211_STA_INFO_SIGNAL]);
	}

	if (sta[NL80211_STA_INFO_TX_BITRATE]) {
		::nlattr *rate[NL80211_RATE_INFO_MAX + 1];
		if (::nla_parse_nested(rate, NL80211_RATE_INFO_MAX, sta[NL80211_STA_INFO_TX_BITRATE], rate_policy.pol)) {
			throw std::runtime_error("Error parsing nl_msg rate attributes");
		}

		if (rate[NL80211_RATE_INFO_BITRATE]) {
			sta_rate_info_bitrate = nla_get_u16(rate[NL80211_RATE_INFO_BITRATE]);
		}
	}
}

void genl_msg::parse_information_elements(unsigned char *ie, int ielen)
{
	static unsigned char ms_oui[3] = { 0x00, 0x50, 0xf2 };
	static unsigned char ieee80211_oui[3] = { 0x00, 0x0f, 0xac };

	unsigned int max_rate = 0;
	unsigned int rate;

	unsigned char *data;

	while (ielen >= 2 && ielen >= ie[1]) {
		data = ie + 2;

		switch (ie[0]) {
		case IE_SSID:           // 802.11-2012 8.4.2.2
		    ie_ssid = std::string(reinterpret_cast<const char *>(data), ie[1]);
		    break;

		case IE_SUPP_RATES:     // 802.11-2012 8.4.2.3
		case IE_EXT_SUPP_RATES: // 802.11-2012 8.4.2.15
			for (unsigned int r = 0; r < ie[1]; r++) {
				rate = (data[r] & 0x7f) / 2;
				if (rate > max_rate) {
					max_rate = rate;
					ie_max_data_rate = max_rate;
				}
			}
			break;

		case IE_RSN:            // 802.11-2012 8.4.2.27
			ie_has_security_features = true;
			break;

		case IE_VENDOR:         // 802.11-2012 8.4.2.28
			if (ie[1] >= 4) {
				if (   (::memcmp(data, ms_oui, 3)        == 0 && data[3] < IE_VENDOR_MS_CIPHER_MAX)
				    || (::memcmp(data, ieee80211_oui, 3) == 0 && data[3] < IE_VENDOR_IEEE_CIPHER_MAX)) {
					ie_has_security_features = true;
				}
			}
			break;

		case IE_INTERWORKING:   // 802.11-2012 8.4.2.94
			ie_has_mih_capabilities = true;

			if ((data[0] & 0x10) != 0) {
				ie_has_internet_access = true;
			}

			if ((data[0] & 0xc0) != 0) {
				ie_has_emergency_services = true;
			}

			if (ie[1] == 7) {
				ie_hessid = odtone::mih::mac_addr(&data[1], ETH_NLEN);
			} else if (ie[1] == 9) {
				ie_hessid = odtone::mih::mac_addr(&data[3], ETH_NLEN);
			}

		case IE_ADVERT_PROTO:   // 802.11-2012 8.4.2.95
		{
			unsigned char *tuple;
			unsigned char jump;
			bool complete;
			for (tuple = data, complete = false;
			     tuple < data + ie[1] && !complete;
			     tuple += jump) {
				jump = 1;
				switch (tuple[1]) {
					case 1:
						ie_has_mih_information_service = true;
						break;
					case 2:
						ie_has_mih_command_service = true;
						ie_has_mih_event_service = true;
						break;
					case 221:   // 802.11-2012 8.4.2.28
						jump = tuple[3];
						break;
				}

				complete =    ie_has_mih_information_service
				           && ie_has_mih_command_service
				           && ie_has_mih_event_service;
			}
		}

		default:
			break;
		}

		ielen -= ie[1] + 2;
		ie += ie[1] + 2;
	}
}

////////////////////////////////////////////////////////////////////////

void mac_addr_n2a(char *mac_addr, unsigned char *arg)
{
	int i, l;

	l = 0;
	for (i = 0; i < ETH_NLEN; i++) {
		if (i == 0) {
			sprintf(mac_addr+l, "%02x", arg[i]);
			l += 2;
		} else {
			sprintf(mac_addr+l, ":%02x", arg[i]);
			l += 3;
		}
	}
}

int mac_addr_a2n(unsigned char *mac_addr, char *arg)
{
        int i;

        for (i = 0; i < ETH_ALEN ; i++) {
                int temp;
                char *cp = strchr(arg, ':');
                if (cp) {
                        *cp = 0;
                        cp++;
                }
                if (sscanf(arg, "%x", &temp) != 1)
                        return -1;
                if (temp < 0 || temp > 255)
                        return -1;

                mac_addr[i] = temp;
                if (!cp)
                        break;
                arg = cp;
        }
        if (i < ETH_ALEN - 1)
                return -1;

        return 0;
}

bss_parse_policy::bss_parse_policy() {
	pol[NL80211_BSS_TSF].type = NLA_U64;
	pol[NL80211_BSS_FREQUENCY].type = NLA_U32;
	pol[NL80211_BSS_BSSID] = { };
	pol[NL80211_BSS_BEACON_INTERVAL].type = NLA_U16;
	pol[NL80211_BSS_CAPABILITY].type = NLA_U16;
	pol[NL80211_BSS_INFORMATION_ELEMENTS] = { };
	pol[NL80211_BSS_SIGNAL_MBM].type = NLA_U32;
	pol[NL80211_BSS_SIGNAL_UNSPEC].type = NLA_U8;
	pol[NL80211_BSS_STATUS].type = NLA_U32;
#ifdef NL80211_BSS_SEEN_MS_AGO
	pol[NL80211_BSS_SEEN_MS_AGO].type = NLA_U32;
#endif /* NL80211_BSS_SEEN_MS_AGO */
#ifdef NL80211_BSS_BEACON_IES
	pol[NL80211_BSS_BEACON_IES] = { };
#endif /* NL80211_BSS_BEACON_IES */
}

stats_parse_policy::stats_parse_policy() {
	pol[NL80211_STA_INFO_INACTIVE_TIME].type = NLA_U32;
	pol[NL80211_STA_INFO_RX_BYTES].type = NLA_U32;
	pol[NL80211_STA_INFO_TX_BYTES].type = NLA_U32;
	pol[NL80211_STA_INFO_RX_PACKETS].type = NLA_U32;
	pol[NL80211_STA_INFO_TX_PACKETS].type = NLA_U32;
	pol[NL80211_STA_INFO_SIGNAL].type = NLA_U8;
	pol[NL80211_STA_INFO_TX_BITRATE].type = NLA_NESTED;
	pol[NL80211_STA_INFO_LLID].type = NLA_U16;
	pol[NL80211_STA_INFO_PLID].type = NLA_U16;
	pol[NL80211_STA_INFO_PLINK_STATE].type = NLA_U8;
#ifdef NL80211_STA_INFO_TX_RETRIES
	pol[NL80211_STA_INFO_TX_RETRIES].type = NLA_U32;
#endif /* NL80211_STA_INFO_TX_RETRIES */
#ifdef NL80211_STA_INFO_TX_FAILED
	pol[NL80211_STA_INFO_TX_FAILED].type = NLA_U32;
#endif /* NL80211_STA_INFO_TX_FAILED */
#ifdef NL80211_STA_INFO_STA_FLAGS
	pol[NL80211_STA_INFO_STA_FLAGS].minlen = sizeof(nl80211_sta_flag_update);
#endif /* NL80211_STA_INFO_STA_FLAGS */
}

rate_parse_policy::rate_parse_policy() {
	pol[NL80211_RATE_INFO_BITRATE].type = NLA_U16;
	pol[NL80211_RATE_INFO_MCS].type = NLA_U8;
	pol[NL80211_RATE_INFO_40_MHZ_WIDTH].type = NLA_FLAG;
	pol[NL80211_RATE_INFO_SHORT_GI].type = NLA_FLAG;
}

cqm_parse_policy::cqm_parse_policy() {
	pol[NL80211_ATTR_CQM_RSSI_THOLD].type = NLA_U32;
	pol[NL80211_ATTR_CQM_RSSI_HYST].type = NLA_U32;
	pol[NL80211_ATTR_CQM_RSSI_THRESHOLD_EVENT].type = NLA_U32;
}

}; // nlwrap
