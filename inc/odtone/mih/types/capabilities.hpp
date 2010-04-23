//=============================================================================
// Brief   : MIH Capabilities Types
// Authors : Bruno Santos <bsantos@av.it.pt>
//           Simao Reis   <sreis@av.it.pt>
//
//
// Copyright (C) 2009 Universidade Aveiro - Instituto de Telecomunicacoes Polo Aveiro
//
// This file is part of ODTONE - Open Dot Twenty One.
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//=============================================================================

#ifndef ODTONE_MIH_TYPES_CAPABILITIES__HPP_
#define ODTONE_MIH_TYPES_CAPABILITIES__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/mih/types/base.hpp>
#include <odtone/mih/types/link.hpp>
#include <odtone/mih/types/information.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
typedef boost::variant<std::vector<link_det_cfg>,
					   std::vector<link_cfg_param> > evt_cfg_info;

typedef std::vector<evt_cfg_info> evt_cfg_info_list;

///////////////////////////////////////////////////////////////////////////////
enum event_list_enum {
	link_detected = 0,
	link_up = 1,
	link_down = 2,
	link_parameters_report = 3,
	link_going_down = 4,
	link_handover_imminent = 5,
	link_handover_complete = 6,
	link_pdu_transmit_status = 7,
};

typedef bitmap<32, event_list_enum> event_list;

///////////////////////////////////////////////////////////////////////////////
enum command_list_enum {
	link_get_parameters = 0,
	link_configure_thresholds = 1,
	link_actions = 2,
	net_ho_candidate_query = 3,
	net_ho_commit = 3,
	n2n_ho_query_resources = 3,
	n2n_ho_commit = 3,
	n2n_ho_Complete = 3,
	mn_ho_candidate_query = 4,
	mn_ho_commit = 4,
	mn_ho_complete = 4,
};

typedef bitmap<32, command_list_enum> command_list;

///////////////////////////////////////////////////////////////////////////////
enum iq_type_list_enum {
	iq_type_binary_data = 0,
	iq_type_rdf_data = 1,
	iq_type_rdf_schema_url = 2,
	iq_type_rdf_schema = 3,
	iq_type_ie_network_type = 4,
	iq_type_ie_operator_id = 5,
	iq_type_ie_service_provider_id = 6,
	iq_type_ie_country_code = 7,
	iq_type_ie_network_id = 8,
	iq_type_ie_network_aux_id = 9,
	iq_type_ie_roaming_parteners = 10,
	iq_type_ie_cost = 11,
	iq_type_ie_network_qos = 12,
	iq_type_ie_network_data_rate = 13,
	iq_type_ie_net_regult_domain = 14,
	iq_type_ie_net_frequency_bands = 15,
	iq_type_ie_net_ip_cfg_methods = 16,
	iq_type_ie_net_capabilities = 17,
	iq_type_ie_net_supported_lcp = 18,
	iq_type_ie_net_mob_mgmt_prot = 19,
	iq_type_ie_net_emserv_proxy = 20,
	iq_type_ie_net_ims_proxy_cscf = 21,
	iq_type_ie_net_mobile_network = 22,
	iq_type_ie_poa_link_addr = 23,
	iq_type_ie_poa_location = 24,
	iq_type_ie_poa_channel_range = 25,
	iq_type_ie_poa_system_info = 26,
	iq_type_ie_poa_subnet_info = 27,
	iq_type_ie_poa_ip_addr = 28,
};

typedef bitmap<64, iq_type_list_enum> iq_type_list;

///////////////////////////////////////////////////////////////////////////////
enum transport_list_enum {
	transport_udp = 0,
	transport_tcp = 1,
};

typedef bitmap<16, transport_list_enum> transport_list;

///////////////////////////////////////////////////////////////////////////////
struct mbb_ho_supp {
	mbb_ho_supp() : supported(false)
	{ }

	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & first;
		ar & second;
		ar & supported;
	}


	network_type first;
	network_type second;
	bool         supported;
};

typedef std::vector<mbb_ho_supp> mbb_ho_supp_list;

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /*namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_TYPES_CAPABILITIES__HPP_ */
