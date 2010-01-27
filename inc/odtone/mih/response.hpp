//=============================================================================
// Brief   : MIH Response Message Helper
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

#ifndef ODTONE_MIH_RESPONSE__HPP_
#define ODTONE_MIH_RESPONSE__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/debug.hpp>
#include <odtone/mih/message.hpp>
#include <boost/utility.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
/**
 * \brief MIH Response Message helper
 */
class response : public message_helper {
public:
	/**
	 * \brief MIH Response Message ID
	 */
	enum mid {
		capability_discover								/// MIH_Capability_Discover.response
							= msg_id<1, 2, 1>::value,
		mih_register									/// MIH_Register.response
							= msg_id<1, 2, 2>::value,
		mih_deregister									/// MIH_DeRegister.response
							= msg_id<1, 2, 3>::value,
		event_subscribe									/// MIH_Event_Subscribe.response
							= msg_id<1, 2, 4>::value,
		event_unsubscribe								/// MIH_Event_Unsubscribe.response
							= msg_id<1, 2, 5>::value,

		link_get_parameters										/// MIH_Link_Get_Parameters.response
									= msg_id<3, 2, 1>::value,
		link_configure_thresholds								/// MIH_Link_Configure_Thresholds.response
									= msg_id<3, 2, 2>::value,
		link_actions											/// MIH_Link_Actions.response
									= msg_id<3, 2, 3>::value,
		net_ho_candidate_query									/// MIH_Net_HO_Candidate_Query.response
									= msg_id<3, 2, 4>::value,
		mn_ho_candidate_query									/// MIH_MN_HO_Candidate_Query.response
									= msg_id<3, 2, 5>::value,
		n2n_ho_query_resources									/// MIH_N2N_HO_Query_Resources.response
									= msg_id<3, 2, 6>::value,
		mn_ho_commit											/// MIH_MN_HO_Commit.response
									= msg_id<3, 2, 7>::value,
		net_ho_commit											/// MIH_Net_HO_Commit.response
									= msg_id<3, 2, 8>::value,
		n2n_ho_commit											/// MIH_N2N_HO_Commit.response
									= msg_id<3, 2, 9>::value,
		mn_ho_complete											/// MIH_N2N_HO_Complete.response
									= msg_id<3, 2, 10>::value,
		n2n_ho_complete											/// MIH_N2N_HO_Commlete.response
									= msg_id<3, 2, 11>::value,

		get_information								/// MIH_Get_Information.response
						= msg_id<4, 2, 1>::value,
	};

	/**
	 * \brief Construct a MIH Response Message helper
	 */
	response() : message_helper(0, nullptr)
	{ }

	/**
	 * \brief Construct an MIH Request Message helper
	 * \param m MIH Message ID
	 */
	explicit response(mid m) : message_helper(m, nullptr)
	{ }

	/**
	 * \brief Construct an MIH Request Message helper
	 * \param m MIH Message ID
	 * \param destination MIH Message Destination MIHF ID
	 */
	response(mid m, const id& destination) : message_helper(m, &destination)
	{ }
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_RESPONSE__HPP_ */
