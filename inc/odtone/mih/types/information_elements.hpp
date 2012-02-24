//=============================================================================
// Brief   : MIH Information Elements
// Authors : Simao Reis   <sreis@av.it.pt>
//           Bruno Santos <bsantos@av.it.pt>
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
#include <odtone/mih/types/vendor_ie.hpp>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
// general information elements
typedef network_type   ie_network_type;			/**< Network type IE type.	*/
typedef operator_id    ie_operator_id;			/**< Operator ID IE type.	*/
typedef sp_id          ie_service_provider_id;	/**< Service provider ID IE type.*/
typedef cntry_code     ie_country_code;			/**< Countrry code IE type.	*/

// access network specific information elements
typedef network_id     ie_network_id;			/**< Network ID IE type.		*/
typedef net_aux_id     ie_network_aux_id;		/**< Auxiliar network ID  IE type.*/
typedef roaming_ptns   ie_roaming_partners;		/**< Roaming partners IE type.	*/
typedef cost           ie_cost;					/**< Cost IE type.				*/
typedef qos_list       ie_network_qos;			/**< Network QoS IE type.		*/
typedef data_rate      ie_network_data_rate;	/**< Network data rate IE type.	*/
typedef regu_domain    ie_net_regulat_domain;	/**< Network regulatory class IE type.*/
typedef freq_bands     ie_net_frequency_bands;	/**< Network frequency bands IE type.*/
typedef ip_config      ie_net_ip_cfg_methods;	/**< Network IP configuration methods IE type.*/
typedef net_caps       ie_net_capabilities;		/**< Network capabilities IE type.*/
typedef supported_lcp  ie_net_supported_lcp;	/**< Network supported LCP IE type.*/
typedef ip_mob_mgmt    ie_net_mob_mgmt_prot;	/**< Network mobility management protocol IE type.*/
typedef proxy_addr     ie_net_emserv_proxy;		/**< Network proxy PSAP IE type.*/
typedef proxy_addr     ie_net_ims_proxy_cscf;	/**< Network IMS proxy P-CSCF IE type.*/
typedef bool           ie_net_mobile_network;	/**< Network mobile IE type.	*/

// POA specific information elements
typedef link_addr      ie_poa_link_addr;	/**< PoA link address IE type.		*/
typedef location       ie_poa_location;		/**< PoA location IE type.			*/
typedef ch_range       ie_poa_channel_range;/**< PoA channel range IE type.		*/
typedef system_info    ie_poa_system_info;	/**< PoA system information IE type.*/

// POA specific higher layer service information elements
typedef ip_subnet_info ie_poa_subnet_info;	/**< PoA subnet information IE type.*/
typedef ip_addr        ie_poa_ip_addr;		/**< PoA IP address IE type.		*/

// IE Containers
struct ie_container_poa;					/**< PoA IE container.				*/
struct ie_container_network;				/**< PoA network container.			*/
class  ie_container_list_of_networks;		/**< List of networks container.	*/

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
/**
 * PoA subnet info list IE type.
 */
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
	using base::clear;
	using base::resize;
	using base::operator[];

	/**
	 * Serialize the PoA subnet info list IE type.
	 *
	 * @param ar The archive to where serialize the data type.
	 */
	void serialize(oarchive& ar)
	{
		for (base::iterator i = base::begin(); i != base::end(); ++i)
			ar & tlv_ie_poa_subnet_info(*i);

		vendor_ies.serialize(ar);
	}

	/**
	 * Deserialize the PoA subnet info list IE type.
	 *
	 * @param ar The archive from where deserialize the data type.
	 */
	void serialize(iarchive& ar)
	{
		while (ar.position() < ar.length()) {
			boost::optional<ie_poa_subnet_info> cn;

			ar & tlv_ie_poa_subnet_info(cn);
			if (!cn)
				break;

			base::push_back(*cn);
		}

		if(base::size() < 1)
			boost::throw_exception(bad_tlv()); //FIXME: set proper exception

		vendor_ies.serialize(ar);
	}

public:
	vendor_ie_list vendor_ies;		
};

///////////////////////////////////////////////////////////////////////////////
/**
 * PoA IP address list IE type.
 */
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
	using base::clear;
	using base::resize;
	using base::operator[];

	/**
	 * Deserialize the PoA IP address list IE type.
	 *
	 * @param ar The archive from where deserialize the data type.
	 */
	void serialize(oarchive& ar)
	{
		for (base::iterator i = base::begin(); i != base::end(); ++i)
			ar & tlv_ie_poa_ip_addr(*i);

		vendor_ies.serialize(ar);
	}

	/**
	 * Serialize the PoA IP address list IE type.
	 *
	 * @param ar The archive to where serialize the data type.
	 */
	void serialize(iarchive& ar)
	{
		while (ar.position() < ar.length()) {
			boost::optional<ie_poa_ip_addr> cn;

			ar & tlv_ie_poa_ip_addr(cn);
			if (!cn)
				break;

			base::push_back(*cn);
		}

		if(base::size() < 1)
			boost::throw_exception(bad_tlv()); //FIXME: set proper exception

		vendor_ies.serialize(ar);
	}

public:
	vendor_ie_list vendor_ies;
};

///////////////////////////////////////////////////////////////////////////////
/**
 * PoA IE type.
 */
struct ie_container_poa
{
	ie_poa_link_addr          poa_link_addr;
	ie_poa_location           poa_location;
	ie_poa_channel_range      poa_channel_range;
	ie_poa_system_info        poa_system_info;
	ie_poa_subnet_info_list   poa_subnet_info;
	ie_poa_ip_addr_list       poa_ip_addr;
	vendor_ie_list            vendor_ies;

	/**
	 * Serialize/deserialize the PoA IE type.
	 *
	 * @param ar The archive from/to where serialize/deserialize the data type.
	 */
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & tlv_ie_poa_link_addr(poa_link_addr);
		ar & tlv_ie_poa_location(poa_location);
		ar & tlv_ie_poa_channel_range(poa_channel_range);
		ar & tlv_ie_poa_system_info(poa_system_info);

		serialize_opt_lists(ar);

		vendor_ies.serialize(ar);
	}

	/**
	 * Deserialize optional IEs.
	 *
	 * @param ar The archive to where deserialize the data type.
	 */
	void serialize_opt_lists(iarchive& ar)
	{
		poa_subnet_info.clear();

		while (ar.position() < ar.length()) {
			boost::optional<ie_poa_subnet_info> cn;

			ar & tlv_ie_poa_subnet_info(cn);
			if (!cn)
				break;

			poa_subnet_info.push_back(*cn);
		}

		poa_ip_addr.clear();

		while (ar.position() < ar.length()) {
			boost::optional<ie_poa_ip_addr> cn;

			ar & tlv_ie_poa_ip_addr(cn);
			if (!cn)
				break;

			poa_ip_addr.push_back(*cn);
		}
	}

	/**
	 * Serialize optional IEs.
	 *
	 * @param ar The archive from where serialize the data type.
	 */
	void serialize_opt_lists(oarchive& ar)
	{
		for (ie_poa_subnet_info_list::iterator i = poa_subnet_info.begin(), e = poa_subnet_info.end(); i != e; ++i)
			ar & tlv_ie_poa_subnet_info(*i);

		for (ie_poa_ip_addr_list::iterator i = poa_ip_addr.begin(), e = poa_ip_addr.end(); i != e; ++i)
			ar & tlv_ie_poa_ip_addr(*i);
	}
};

///////////////////////////////////////////////////////////////////////////////
/**
 * PoA list IE type.
 */
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
	using base::clear;
	using base::resize;
	using base::operator[];

	/**
	 * Serialize the PoA list IE type.
	 *
	 * @param ar The archive to where serialize the data type.
	 */
	void serialize(oarchive& ar)
	{
		for (base::iterator i = base::begin(); i != base::end(); ++i)
			ar & tlv_ie_container_poa(*i);

		vendor_ies.serialize(ar);
	}

	/**
	 * Deserialize the PoA list IE type.
	 *
	 * @param ar The archive from where deserialize the data type.
	 */
	void serialize(iarchive& ar)
	{
		base::clear();

		while (ar.position() < ar.length()) {
			boost::optional<ie_container_poa> cn;

			ar & tlv_ie_container_poa(cn);
			if (!cn)
				break;

			base::push_back(*cn);
		}

		if(base::size() < 1)
			boost::throw_exception(bad_tlv()); //FIXME: set proper exception

		vendor_ies.serialize(ar);
	}

public:
	vendor_ie_list vendor_ies;
};

///////////////////////////////////////////////////////////////////////////////
/**
 * Network IE type.
 */
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
	vendor_ie_list        vendor_ies;

	/**
	 * Serialize/deserialize the network IE type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
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

		serialize_opt_lists(ar);

		vendor_ies.serialize(ar);
	}

	/**
	 * Deserialize optional IEs.
	 *
	 * @param ar The archive to where deserialize the data type.
	 */
	void serialize_opt_lists(iarchive& ar)
	{
		poas.clear();

		while (ar.position() < ar.length()) {
			boost::optional<ie_container_poa> cn;

			ar & tlv_ie_container_poa(cn);
			if (!cn)
				break;

			poas.push_back(*cn);
		}
	}

	/**
	 * Serialize optional IEs.
	 *
	 * @param ar The archive from where serialize the data type.
	 */
	void serialize_opt_lists(oarchive& ar)
	{
		for (ie_container_poa_list::iterator i = poas.begin(), e = poas.end(); i != e; ++i)
			ar & tlv_ie_container_poa(*i);
	}
};

///////////////////////////////////////////////////////////////////////////////
/**
 * Network list IE type.
 */
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
	using base::clear;
	using base::resize;
	using base::operator[];

	/**
	 * Serialize the network list IE type.
	 *
	 * @param ar The archive to where serialize the data type.
	 */
	void serialize(oarchive& ar)
	{
		for (base::iterator i = base::begin(), e = base::end(); i != e; ++i)
			ar & tlv_ie_container_network(*i);

		vendor_ies.serialize(ar);
	}

	/**
	 * Deserialize the network list IE type.
	 *
	 * @param ar The archive from where deserialize the data type.
	 */
	void serialize(iarchive& ar)
	{
		base::clear();

		while (ar.position() < ar.length()) {
			boost::optional<ie_container_network> cn;

			ar & tlv_ie_container_network(cn);
			if (!cn)
				break;

			base::push_back(*cn);
		}

		if(base::size() < 1)
			boost::throw_exception(bad_tlv()); //FIXME: set proper exception

		vendor_ies.serialize(ar);
	}

public:
	vendor_ie_list vendor_ies;
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */  }  /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_TYPES_INFORMATION_ELEMENTS__HPP_ */
