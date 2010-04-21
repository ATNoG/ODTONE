//
// Copyright (c) 2007-2009 2009 Universidade Aveiro - Instituto de
// Telecomunicacoes Polo Aveiro
// This file is part of ODTONE - Open Dot Twenty One.
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//
// Author:     Simao Reis <sreis@av.it.pt>
//

#ifndef ODTONE_IES_CONTAINERS_HPP
#define ODTONE_IES_CONTAINERS_HPP

#include <odtone/base.hpp>
#include <odtone/cast.hpp>
#include <odtone/mih/tlv.hpp>
#include <odtone/miis/information_elements.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>

#include <vector>

namespace odtone { namespace miis {

static const mih::tlv_cast_<ie_network_type, mih::tlv4_<0x10000000> > tlv_ie_network_type = {};
static const mih::tlv_cast_<ie_operator_id, mih::tlv4_<0x10000001> > tlv_ie_operator_id = {};
static const mih::tlv_cast_<ie_service_provider_id, mih::tlv4_<0x10000002> > tlv_ie_service_provider_id = {};
static const mih::tlv_cast_<ie_country_code, mih::tlv4_<0x10000003> > tlv_ie_country_code = {};
static const mih::tlv_cast_<ie_network_id, mih::tlv4_<0x10000100> > tlv_ie_network_id = {};
static const mih::tlv_cast_<ie_network_aux_id, mih::tlv4_<0x10000101> > tlv_ie_network_aux_id = {};
static const mih::tlv_cast_<ie_roaming_partners, mih::tlv4_<0x1000002> > tlv_ie_roaming_partners = {};
static const mih::tlv_cast_<ie_cost, mih::tlv4_<0x10000103> > tlv_ie_cost = {};
static const mih::tlv_cast_<ie_network_qos, mih::tlv4_<0x10000105> > tlv_ie_network_qos = {};
static const mih::tlv_cast_<ie_network_data_rate, mih::tlv4_<0x10000106> > tlv_ie_network_data_rate = {};
static const mih::tlv_cast_<ie_net_regulat_domain, mih::tlv4_<0x10000107> > tlv_ie_net_regulat_domain = {};
static const mih::tlv_cast_<ie_net_frequency_bands, mih::tlv4_<0x10000108> > tlv_ie_net_frequency_bands = {};
static const mih::tlv_cast_<ie_net_ip_cfg_methods, mih::tlv4_<0x10000109> > tlv_ie_net_ip_cfg_methods = {};
static const mih::tlv_cast_<ie_net_capabilities, mih::tlv4_<0x1000010A> > tlv_ie_net_capabilities = {};
static const mih::tlv_cast_<ie_net_supported_lcp, mih::tlv4_<0x1000010B> > tlv_ie_net_supported_lcp = {};
static const mih::tlv_cast_<ie_net_mob_mgmt_prot, mih::tlv4_<0x1000010C> > tlv_ie_net_mob_mgmt_prot = {};
static const mih::tlv_cast_<ie_net_emserv_proxy, mih::tlv4_<0x1000010D> > tlv_ie_net_emserv_proxy = {};
static const mih::tlv_cast_<ie_net_ims_proxy_cscf, mih::tlv4_<0x1000010E> > tlv_ie_net_ims_proxy_cscf = {};
static const mih::tlv_cast_<ie_net_mobile_network, mih::tlv4_<0x1000010F> > tlv_ie_net_mobile_network = {};
static const mih::tlv_cast_<ie_poa_link_addr, mih::tlv4_<0x10000200> > tlv_ie_poa_link_addr = {};
static const mih::tlv_cast_<ie_poa_location, mih::tlv4_<0x10000201> > tlv_ie_poa_location = {};
static const mih::tlv_cast_<ie_poa_channel_range, mih::tlv4_<0x10000202> > tlv_ie_poa_channel_range = {};
static const mih::tlv_cast_<ie_poa_system_info, mih::tlv4_<0x10000203> > tlv_ie_poa_system_info = {};
static const mih::tlv_cast_<ie_poa_subnet_info, mih::tlv4_<0x10000204> > tlv_ie_poa_subnet_info = {};
static const mih::tlv_cast_<ie_poa_ip_addr, mih::tlv4_<0x10000205> > tlv_ie_poa_ip_addr = {};

struct ie_container_poa
{
	boost::optional<ie_poa_link_addr > poa_link_addr;
	boost::optional<ie_poa_location > poa_location;
	boost::optional<ie_poa_channel_range > poa_channel_range;
	boost::optional<std::vector<ie_poa_subnet_info> > poa_subnet_info;
	boost::optional<std::vector<ie_poa_ip_addr> > poa_ip_addr;

	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & tlv_ie_poa_link_addr(poa_link_addr);
		ar & tlv_ie_poa_location(poa_location);
		ar & tlv_ie_poa_channel_range(poa_channel_range);
		ar & tlv_ie_poa_subnet_info(poa_subnet_info);
		ar & tlv_ie_poa_ip_addr(poa_ip_addr);
	}
};

static const mih::tlv_cast_<ie_container_poa, mih::tlv4_<0x10000302> > tlv_ie_container_poa;

struct ie_container_network
{
	ie_network_type network_type;
	ie_operator_id operator_id;

	boost::optional<ie_service_provider_id > service_provider_id;
	boost::optional<ie_country_code > country_code;
	boost::optional<ie_network_id > network_id;
	boost::optional<ie_network_aux_id > network_aux_id;
	boost::optional<ie_roaming_partners > roaming_partners;
	boost::optional<ie_cost > cost;
	boost::optional<ie_network_qos > network_qos;
	boost::optional<ie_network_data_rate > network_data_rate;
	boost::optional<ie_net_regulat_domain > net_regulat_domain;
	boost::optional<ie_net_frequency_bands > net_frequency_bands;
	boost::optional<ie_net_ip_cfg_methods > net_ip_cfg_methods;
	boost::optional<ie_net_capabilities > net_capabilities;
	boost::optional<ie_net_supported_lcp > net_supported_lcp;
	boost::optional<ie_net_mob_mgmt_prot > net_mob_mgmt_prot;
	boost::optional<ie_net_emserv_proxy > net_emserv_proxy;
	boost::optional<ie_net_ims_proxy_cscf > net_ims_proxy_cscf;
	boost::optional<ie_net_mobile_network > net_mobile_network;

	std::vector<ie_container_poa> poas;

	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & tlv_ie_network_type(network_type);
		ar & tlv_ie_operator_id(operator_id);

		ar & tlv_ie_service_provider_id(service_provider_id);
		ar & tlv_ie_country_code(country_code);
		ar & tlv_ie_network_id(network_id);
		ar & tlv_ie_network_aux_id(network_aux_id);
		ar & tlv_ie_roaming_partners(roaming_partners);
		ar & tlv_ie_cost(cost);
		ar & tlv_ie_network_qos(network_qos);
		ar & tlv_ie_network_data_rate(network_data_rate);
		ar & tlv_ie_net_regulat_domain(net_regulat_domain);
		ar & tlv_ie_net_frequency_bands(net_frequency_bands);
		ar & tlv_ie_net_ip_cfg_methods(net_ip_cfg_methods);
		ar & tlv_ie_net_capabilities(net_capabilities);
		ar & tlv_ie_net_supported_lcp(net_supported_lcp);
		ar & tlv_ie_net_mob_mgmt_prot(net_mob_mgmt_prot);
		ar & tlv_ie_net_emserv_proxy(net_emserv_proxy);
		ar & tlv_ie_net_ims_proxy_cscf(net_ims_proxy_cscf);
		ar & tlv_ie_net_mobile_network(net_mobile_network);
	}
};

static const mih::tlv_cast_<ie_container_network, mih::tlv4_<0x10000301> > tlv_ie_container_network = {};

class ie_container_list_of_networks : private std::vector<ie_container_network> {
	typedef std::vector<ie_container_network> base;

public:
	using base::iterator;
	using base::const_iterator;

	using base::push_back;
	using base::pop_back;
	using base::front;
	using base::back;
	using base::begin;
	using base::end;
	using base::size;
	using base::resize;
	using base::operator[];

	void serialize(mih::oarchive& ar)
	{
		uint len = truncate_cast<uint>(base::size());

		for (base::iterator i = base::begin(); i != base::end(); ++i)
			ar & tlv_ie_container_network(*i);
	}

	void serialize(mih::iarchive& ar)
	{
		try {
			for (;;) {
				ie_container_network cn;

				ar & tlv_ie_container_network(cn);
				base::push_back(cn);
			}

		} catch (mih::bad_tlv& e) {
		}
	}
};

static const mih::tlv_cast_<ie_container_list_of_networks, mih::tlv4_<0x10000300> > tlv_ie_container_list_of_networks = {};

} /* namespace miis */  }  /* namespace odtone */

#endif
