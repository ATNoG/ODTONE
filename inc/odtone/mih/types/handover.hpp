//=============================================================================
// Brief   : MIH Handover Types
// Authors : Bruno Santos <bsantos@av.it.pt>
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

#ifndef ODTONE_MIH_TYPES_HANDOVER__HPP_
#define ODTONE_MIH_TYPES_HANDOVER__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/mih/types/base.hpp>
#include <odtone/mih/types/qos.hpp>
#include <odtone/mih/types/address.hpp>
#include <odtone/mih/types/ipconfig.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
/**
 * HO_STATUS data type enumeration.
 */
enum ho_status_enum {
	ho_status_permitted = 0,	/**< Handover status permitted.	*/
	ho_status_declined = 1,		/**< Handover status declined.	*/
};

/**
 * HO_STATUS data type.
 */
typedef enumeration<ho_status_enum> ho_status;

///////////////////////////////////////////////////////////////////////////////
/**
 * HO_RESULT data type enumeration.
 */
enum ho_result_enum {
	ho_result_success = 0,	/**< Handover result success.	*/
	ho_result_failure = 1,	/**< Handover result failure.	*/
	ho_result_rejected = 3,	/**< Handover result rejected.	*/
};

/**
 * HO_RESULT data type.
 */
typedef enumeration<ho_result_enum> ho_result;

///////////////////////////////////////////////////////////////////////////////
/**
 * HO_CAUSE data type enumeration.
 */
enum ho_cause_enum {
	ho_cause_explicit_disconnect = 0,		/**< Handover cause explicit disconnect.	*/
	ho_cause_packet_timeout = 1,			/**< Handover cause packet timeout.			*/
	ho_cause_no_resource = 2,				/**< Handover cause no resources.			*/
	ho_cause_no_broadcast = 3,				/**< Handover cause no broadcast.			*/
	ho_cause_authentication_failure = 4,	/**< Handover cause authentication failure.	*/
	ho_cause_billing_failure = 5,			/**< Handover cause billing failure.		*/
};

/**
 * HO_CAUSE data type.
 */
typedef enumeration<ho_cause_enum> ho_cause;

///////////////////////////////////////////////////////////////////////////////
/**
 * RQ_RESULT data type.
 */
struct rq_result {
	/**
	 * Serialize/deserialize the RQ_RESULT data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & poa_list;
		ar & poa_qos_list;
		ar & opt_ip_cfg_methods;
		ar & opt_dhcp_serv;
		ar & opt_fn_agnt;
		ar & opt_acc_rtr;
	}


	link_poa_list poa_list;		/**< PoA list.	*/
	qos_list      poa_qos_list;	/**< Available resources for the PoA list.	*/

	boost::variant<null, bool, ip_cfg_methods> opt_ip_cfg_methods;	/**< IP configuration method.			*/
	boost::variant<null, bool, dhcp_serv>      opt_dhcp_serv;		/**< DHCP server IP address.			*/
	boost::variant<null, bool, fn_agent>       opt_fn_agnt;			/**< Foreign agent IP address.			*/
	boost::variant<null, bool, acc_rtr>        opt_acc_rtr;			/**< Candidate access router IP address.*/
};

/**
 * LIST(RQ_RESULT) data type.
 */
typedef std::vector<rq_result> rq_result_list;

///////////////////////////////////////////////////////////////////////////////
/**
 * Auxiliar TGT_NET_INFO data type.
 */
struct tgt_net_info_1 {
	/**
	 * Serialize/deserialize the auxiliar TGT_NET_INFO data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & net;
		ar & aux_id;
	}

	network_id                       net;		/**< Network identifier.		  */
	boost::variant<null, net_aux_id> aux_id;	/**< Auxiliar network identifieer.*/
};

/**
 * TGT_NET_INFO data type.
 */
typedef boost::variant<tgt_net_info_1, link_addr> tgt_net_info;

/**
 * LIST(TGT_NET_INFO) data type.
 */
typedef std::vector<tgt_net_info> tgt_net_info_list;

///////////////////////////////////////////////////////////////////////////////
/**
 * PREDEF_CFG_ID data type.
 */
typedef sint8 predef_cfg_id;

/**
 * TSP_CARRIER data type.
 */
typedef octet_string tsp_carrier;

/**
 * TSP_CONTAINER data type.
 */
typedef boost::variant<null, predef_cfg_id, tsp_carrier> tsp_container;

///////////////////////////////////////////////////////////////////////////////
/**
 * REQ_RES_SET data type.
 */
struct rq_res_set {
	/**
	 * Serialize/deserialize the REQ_RES_SET data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & mn_qos_list;
		ar & transport;
		ar & cause;
	}

	qos_list      mn_qos_list;	/**< Resources parameters.	*/
	tsp_container transport;	/**< Transparent container.	*/
	ho_cause      cause;		/**< Handover cause.		*/
};

///////////////////////////////////////////////////////////////////////////////
/**
 * ASGN_RES_SET data type.
 */
struct asgn_res_set {
	/**
	 * Serialize/deserialize the ASGN_RES_SET data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & poa_qos_list;
		ar & transport;
	}


	qos_list      poa_qos_list;	/**< Resources parameters.	*/
	tsp_container transport;	/**< Transparent container.	*/
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /*namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_TYPES_HANDOVER__HPP_ */
