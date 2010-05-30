//=============================================================================
// Brief   : MIH Information Elements
// Authors : Simao Reis   <sreis@av.it.pt>
//           Bruno Santos <bsantos@av.it.pt>
// ----------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2009-2010 Universidade de Aveiro
// Copyrigth (C) 2009-2010 Instituto de Telecomunicações - Pólo de Aveiro
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//=============================================================================

#ifndef ODTONE_MIH_TYPES_INFORMATION_ELEMENTS__HPP_
#define ODTONE_MIH_TYPES_INFORMATION_ELEMENTS__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/cast.hpp>
#include <odtone/mih/tlv.hpp>
#include <odtone/mih/types/information.hpp>
#include <odtone/mih/types/address.hpp>
#include <odtone/mih/types/location.hpp>
#include <odtone/mih/types/link.hpp>
#include <odtone/mih/types/ipconfig.hpp>
#include <odtone/mih/types/qos.hpp>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
// general information elements
typedef network_type   ie_network_type;
typedef operator_id    ie_operator_id;
typedef sp_id          ie_service_provider_id;
typedef cntry_code     ie_country_code;

// access network specific information elements
typedef network_id     ie_network_id;
typedef net_aux_id     ie_network_aux_id;
typedef roaming_ptns   ie_roaming_partners;
typedef cost           ie_cost;
typedef qos_list       ie_network_qos;
typedef data_rate      ie_network_data_rate;
typedef regu_domain    ie_net_regulat_domain;
typedef freq_bands     ie_net_frequency_bands;
typedef ip_config      ie_net_ip_cfg_methods;
typedef net_caps       ie_net_capabilities;
typedef supported_lcp  ie_net_supported_lcp;
typedef ip_mob_mgmt    ie_net_mob_mgmt_prot;
typedef proxy_addr     ie_net_emserv_proxy;
typedef proxy_addr     ie_net_ims_proxy_cscf;
typedef bool           ie_net_mobile_network;

// POA specific information elements
typedef link_addr      ie_poa_link_addr;
typedef location       ie_poa_location;
typedef ch_range       ie_poa_channel_range;
typedef system_info    ie_poa_system_info;

// POA specific higher layer service information elements
typedef ip_subnet_info ie_poa_subnet_info;
typedef ip_addr        ie_poa_ip_addr;

// IE Containers
struct ie_container_poa;
struct ie_container_network;
class  ie_container_list_of_networks;

///////////////////////////////////////////////////////////////////////////////
static const tlv_cast_<ie_network_type,               tlv4_<0x10000000> > tlv_ie_network_type = {};
static const tlv_cast_<ie_operator_id,                tlv4_<0x10000001> > tlv_ie_operator_id = {};
static const tlv_cast_<ie_service_provider_id,        tlv4_<0x10000002> > tlv_ie_service_provider_id = {};
static const tlv_cast_<ie_country_code,               tlv4_<0x10000003> > tlv_ie_country_code = {};
static const tlv_cast_<ie_network_id,                 tlv4_<0x10000100> > tlv_ie_network_id = {};
static const tlv_cast_<ie_network_aux_id,             tlv4_<0x10000101> > tlv_ie_network_aux_id = {};
static const tlv_cast_<ie_roaming_partners,           tlv4_<0x10000102> > tlv_ie_roaming_partners = {};
static const tlv_cast_<ie_cost,                       tlv4_<0x10000103> > tlv_ie_cost = {};
static const tlv_cast_<ie_network_qos,                tlv4_<0x10000105> > tlv_ie_network_qos = {};
static const tlv_cast_<ie_network_data_rate,          tlv4_<0x10000106> > tlv_ie_network_data_rate = {};
static const tlv_cast_<ie_net_regulat_domain,         tlv4_<0x10000107> > tlv_ie_net_regulat_domain = {};
static const tlv_cast_<ie_net_frequency_bands,        tlv4_<0x10000108> > tlv_ie_net_frequency_bands = {};
static const tlv_cast_<ie_net_ip_cfg_methods,         tlv4_<0x10000109> > tlv_ie_net_ip_cfg_methods = {};
static const tlv_cast_<ie_net_capabilities,           tlv4_<0x1000010A> > tlv_ie_net_capabilities = {};
static const tlv_cast_<ie_net_supported_lcp,          tlv4_<0x1000010B> > tlv_ie_net_supported_lcp = {};
static const tlv_cast_<ie_net_mob_mgmt_prot,          tlv4_<0x1000010C> > tlv_ie_net_mob_mgmt_prot = {};
static const tlv_cast_<ie_net_emserv_proxy,           tlv4_<0x1000010D> > tlv_ie_net_emserv_proxy = {};
static const tlv_cast_<ie_net_ims_proxy_cscf,         tlv4_<0x1000010E> > tlv_ie_net_ims_proxy_cscf = {};
static const tlv_cast_<ie_net_mobile_network,         tlv4_<0x1000010F> > tlv_ie_net_mobile_network = {};
static const tlv_cast_<ie_poa_link_addr,              tlv4_<0x10000200> > tlv_ie_poa_link_addr = {};
static const tlv_cast_<ie_poa_location,               tlv4_<0x10000201> > tlv_ie_poa_location = {};
static const tlv_cast_<ie_poa_channel_range,          tlv4_<0x10000202> > tlv_ie_poa_channel_range = {};
static const tlv_cast_<ie_poa_system_info,            tlv4_<0x10000203> > tlv_ie_poa_system_info = {};
static const tlv_cast_<ie_poa_subnet_info,            tlv4_<0x10000204> > tlv_ie_poa_subnet_info = {};
static const tlv_cast_<ie_poa_ip_addr,                tlv4_<0x10000205> > tlv_ie_poa_ip_addr = {};
static const tlv_cast_<ie_container_poa,              tlv4_<0x10000302> > tlv_ie_container_poa = {};
static const tlv_cast_<ie_container_network,          tlv4_<0x10000301> > tlv_ie_container_network = {};
static const tlv_cast_<ie_container_list_of_networks, tlv4_<0x10000300> > tlv_ie_container_list_of_networks = {};

///////////////////////////////////////////////////////////////////////////////
struct ie_poa_subnet_info_list : private std::vector<ie_poa_subnet_info> {
	typedef std::vector<ie_poa_subnet_info> base;

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

	void serialize(oarchive& ar)
	{
		for (base::iterator i = base::begin(); i != base::end(); ++i)
			ar & tlv_ie_poa_subnet_info(*i);
	}

	void serialize(iarchive& ar)
	{
		while (ar.position() < ar.length()) {
			base::resize(base::size() + 1);
			ie_poa_subnet_info& cn = base::back();

			ar & tlv_ie_poa_subnet_info(cn);
		}
	}
};

///////////////////////////////////////////////////////////////////////////////
struct ie_poa_ip_addr_list : private std::vector<ie_poa_ip_addr> {
	typedef std::vector<ie_poa_ip_addr> base;

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

	void serialize(oarchive& ar)
	{
		for (base::iterator i = base::begin(); i != base::end(); ++i)
			ar & tlv_ie_poa_ip_addr(*i);
	}

	void serialize(iarchive& ar)
	{
		while (ar.position() < ar.length()) {
			base::resize(base::size() + 1);
			ie_poa_ip_addr& cn = base::back();

			ar & tlv_ie_poa_ip_addr(cn);
		}
	}
};

///////////////////////////////////////////////////////////////////////////////
struct ie_container_poa
{
	ie_poa_link_addr          poa_link_addr;
	ie_poa_location           poa_location;
	ie_poa_channel_range      poa_channel_range;
	ie_poa_system_info        poa_system_info;
	ie_poa_subnet_info_list   poa_subnet_info;
	ie_poa_ip_addr_list       poa_ip_addr;

	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & tlv_ie_poa_link_addr(poa_link_addr);
		ar & tlv_ie_poa_location(poa_location);
		ar & tlv_ie_poa_channel_range(poa_channel_range);
		ar & tlv_ie_poa_system_info(poa_system_info);
		ar & poa_subnet_info;
		ar & poa_ip_addr;
	}
};

///////////////////////////////////////////////////////////////////////////////
class ie_container_poa_list : private std::vector<ie_container_poa> {
	typedef std::vector<ie_container_poa> base;

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

	void serialize(oarchive& ar)
	{
		for (base::iterator i = base::begin(); i != base::end(); ++i)
			ar & tlv_ie_container_poa(*i);
	}

	void serialize(iarchive& ar)
	{
		while (ar.position() < ar.length()) {
			base::resize(base::size() + 1);
			ie_container_poa& cn = base::back();

			ar & tlv_ie_container_poa(cn);
		}
	}
};

///////////////////////////////////////////////////////////////////////////////
struct ie_container_network {
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

	ie_container_poa_list poas;

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
		ar & poas;
	}
};

///////////////////////////////////////////////////////////////////////////////
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

	void serialize(oarchive& ar)
	{
		for (base::iterator i = base::begin(); i != base::end(); ++i)
			ar & tlv_ie_container_network(*i);
	}

	void serialize(iarchive& ar)
	{
		while (ar.position() < ar.length()) {
			base::resize(base::size() + 1);
			ie_container_network& cn = base::back();

			ar & tlv_ie_container_network(cn);
		}
	}
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */  }  /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_TYPES_INFORMATION_ELEMENTS__HPP_ */
