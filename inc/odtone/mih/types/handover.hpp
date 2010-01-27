//=============================================================================
// Brief   : MIH Handover Types
// Authors : Bruno Santos <bsantos@av.it.pt>
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
enum ho_status_enum {
	ho_status_permitted = 0,
	ho_status_declined = 1,
};

typedef enumeration<ho_status_enum> ho_status;

///////////////////////////////////////////////////////////////////////////////
enum ho_result_enum {
	ho_result_success = 0,
	ho_result_failure = 1,
	ho_result_rejected = 3,
};

typedef enumeration<ho_result_enum> ho_result;

///////////////////////////////////////////////////////////////////////////////
enum ho_cause_enum {
	ho_cause_explicit_disconnect = 0,
	ho_cause_packet_timeout = 1,
	ho_cause_no_resource = 2,
	ho_cause_no_broadcast = 3,
	ho_cause_authentication_failure = 4,
	ho_cause_billing_failure = 5,
};

typedef enumeration<ho_cause_enum> ho_cause;

///////////////////////////////////////////////////////////////////////////////
struct rq_result {
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


	link_poa_list poa_list;
	qos_list      poa_qos_list;

	boost::variant<null, bool, ip_cfg_methods> opt_ip_cfg_methods;
	boost::variant<null, bool, ip_addr>        opt_dhcp_serv;
	boost::variant<null, bool, ip_addr>        opt_fn_agnt;
	boost::variant<null, bool, ip_addr>        opt_acc_rtr;
};

typedef std::vector<rq_result> rq_result_list;

///////////////////////////////////////////////////////////////////////////////
struct tgt_net_info_1 {
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & net;
		ar & aux_id;
	}

	network_id                       net;
	boost::variant<null, net_aux_id> aux_id;
};

typedef boost::variant<tgt_net_info_1, link_addr> tgt_net_info;
typedef std::vector<tgt_net_info>                 tgt_net_info_list;

///////////////////////////////////////////////////////////////////////////////
typedef uint8                                            predef_cfg_id;
typedef octet_string                                     tsp_carrier;
typedef boost::variant<null, predef_cfg_id, tsp_carrier> tsp_container;

///////////////////////////////////////////////////////////////////////////////
struct rq_res_set {
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & mn_qos_list;
		ar & transport;
		ar & cause;
	}


	qos_list      mn_qos_list;
	tsp_container transport;
	ho_cause      cause;
};

///////////////////////////////////////////////////////////////////////////////
struct asgn_res_set {
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & poa_qos_list;
		ar & transport;
	}


	qos_list      poa_qos_list;
	tsp_container transport;
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /*namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_TYPES_HANDOVER__HPP_ */
