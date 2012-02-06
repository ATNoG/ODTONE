//=============================================================================
// Brief   : MIH Capabilities Types
// Authors : Bruno Santos <bsantos@av.it.pt>
//           Simao Reis   <sreis@av.it.pt>
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

#ifndef ODTONE_MIH_TYPES_CAPABILITIES__HPP_
#define ODTONE_MIH_TYPES_CAPABILITIES__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/mih/types/base.hpp>
#include <odtone/mih/types/link.hpp>
#include <odtone/mih/types/information.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
/**
 * EVT_CFG_INFO data type.
 */
typedef boost::variant<std::vector<link_det_cfg>,
					   std::vector<link_cfg_param> > evt_cfg_info;

/**
 * LIST(EVT_CFG_INFO) data type.
 */
typedef std::vector<evt_cfg_info> evt_cfg_info_list;

///////////////////////////////////////////////////////////////////////////////
/**
 * MIH_EVT_LIST data type enumeration.
 */
enum mih_evt_list_enum {
	mih_evt_link_detected = 0,				/**< Link detected				*/
	mih_evt_link_up = 1,					/**< Link up					*/
	mih_evt_link_down = 2,					/**< Link down					*/
	mih_evt_link_parameters_report = 3,		/**< Link parameters report		*/
	mih_evt_link_going_down = 4,			/**< Link doing down			*/
	mih_evt_link_handover_imminent = 5,		/**< Link handover imminent		*/
	mih_evt_link_handover_complete = 6,		/**< Link handover complete		*/
	mih_evt_link_pdu_transmit_status = 7,	/**< Link PDU transmit status	*/
};

/**
 * MIH_EVT_LIST data type.
 */
typedef bitmap<32, mih_evt_list_enum> mih_evt_list;

///////////////////////////////////////////////////////////////////////////////
/**
 * MIH_CMD_LIST data type enumeration.
 */
enum mih_cmd_list_enum {
	mih_cmd_link_get_parameters = 0,		/**< Link get parameters			*/
	mih_cmd_link_configure_thresholds = 1,	/**< Link configure thresholds 		*/
	mih_cmd_link_actions = 2,				/**< Link actions					*/
	mih_cmd_net_ho_candidate_query = 3,		/**< NET handover candidate query	*/
	mih_cmd_net_ho_commit = 3,				/**< NET handover commit			*/
	mih_cmd_n2n_ho_query_resources = 3,		/**< N2N handover query resources	*/
	mih_cmd_n2n_ho_commit = 3,				/**< N2N handover commit			*/
	mih_cmd_n2n_ho_complete = 3,			/**< N2N handover complete			*/
	mih_cmd_mn_ho_candidate_query = 4,		/**< MN handover candidate query	*/
	mih_cmd_mn_ho_commit = 4,				/**< MN handover commit				*/
	mih_cmd_mn_ho_complete = 4,				/**< MN handover complete			*/
};

/**
 * MIH_CMD_LIST data type.
 */
typedef bitmap<32, mih_cmd_list_enum> mih_cmd_list;

///////////////////////////////////////////////////////////////////////////////
/**
 * IQ_TYPE_LIST data type enumeration.
 */
enum iq_type_list_enum {
	iq_type_binary_data = 0,			/**< Binary data					*/
	iq_type_rdf_data = 1,				/**< RDF data						*/
	iq_type_rdf_schema_url = 2,			/**< RDF schema URL					*/
	iq_type_rdf_schema = 3,				/**< RDF schema						*/
	iq_type_ie_network_type = 4,		/**< IE network type				*/
	iq_type_ie_operator_id = 5,			/**< IE operator ID					*/
	iq_type_ie_service_provider_id = 6,	/**< IE service provider ID			*/
	iq_type_ie_country_code = 7,		/**< IE country code				*/
	iq_type_ie_network_id = 8,			/**< IE network ID					*/
	iq_type_ie_network_aux_id = 9,		/**< IE network auxiliar ID			*/
	iq_type_ie_roaming_parteners = 10,	/**< IE roaming parteners			*/
	iq_type_ie_cost = 11,				/**< IE cost						*/
	iq_type_ie_network_qos = 12,		/**< IE network QoS					*/
	iq_type_ie_network_data_rate = 13,	/**< IE network data rate			*/
	iq_type_ie_net_regult_domain = 14,	/**< IE NET result domain			*/
	iq_type_ie_net_frequency_bands = 15,/**< IE NET frequency bands			*/
	iq_type_ie_net_ip_cfg_methods = 16,	/**< IE IP config methods			*/		
	iq_type_ie_net_capabilities = 17,	/**< IE NET capabilities			*/
	iq_type_ie_net_supported_lcp = 18,	/**< IE NET supported LCP			*/
	iq_type_ie_net_mob_mgmt_prot = 19,	/**< IE NET mobility management protocl	*/
	iq_type_ie_net_emserv_proxy = 20,	/**< IE NET Server Proxy			*/
	iq_type_ie_net_ims_proxy_cscf = 21,	/**< IE NET IMS Proxy CSCF			*/
	iq_type_ie_net_mobile_network = 22,	/**< IE NET mobile network			*/
	iq_type_ie_poa_link_addr = 23,		/**< IE PoA link address			*/
	iq_type_ie_poa_location = 24,		/**< IE PoA location				*/
	iq_type_ie_poa_channel_range = 25,	/**< IE PoA channel range			*/
	iq_type_ie_poa_system_info = 26,	/**< IE PoA system info				*/
	iq_type_ie_poa_subnet_info = 27,	/**< IE PoA subnet info				*/
	iq_type_ie_poa_ip_addr = 28,		/**< IE PoA IP address				*/
};

/**
 * IQ_TYPE_LIST data type.
 */
typedef bitmap<64, iq_type_list_enum> iq_type_list;

///////////////////////////////////////////////////////////////////////////////
/**
 * TRANSPORT_LIST data type enumeration.
 */
enum transport_list_enum {
	transport_udp = 0,	/**< UDP	*/
	transport_tcp = 1,	/**< TCP	*/
};

/**
 * TRANSPORT_LIST data type.
 */
typedef bitmap<16, transport_list_enum> transport_list;

///////////////////////////////////////////////////////////////////////////////
/**
 * MBB_HO_SUPP data type.
 */
struct mbb_ho_supp {
	/**
	 * Construct a MBB_HO_SUPP data type.
	 */	
	mbb_ho_supp() : supported(false)
	{ }

	/**
	 * Serialize/deserialize the MBB_HO_SUPP data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & first;
		ar & second;
		ar & supported;
	}


	network_type first;		/**< First network					*/
	network_type second;	/**< Second network					*/
	bool         supported;	/**< Make before break supported	*/
};

/**
 * LIST(MBB_HO_SUPP) data type.
 */
typedef std::vector<mbb_ho_supp> mbb_ho_supp_list;

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /*namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_TYPES_CAPABILITIES__HPP_ */
