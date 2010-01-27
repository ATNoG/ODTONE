//=============================================================================
// Brief   : MIH Message Request Helper
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

#ifndef ODTONE_MIH_REQUEST__HPP_
#define ODTONE_MIH_REQUEST__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/debug.hpp>
#include <odtone/mih/message.hpp>
#include <boost/utility.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
/**
 * \brief MIH Request Message helper
 */
class request : public message_helper {
public:
	/**
	 * \brief MIH Request Message ID
	 */
	enum mid {
		capability_discover								/// MIH_Capability_Discover.request
							= msg_id<1, 1, 1>::value,
		mih_register									/// MIH_Register.request
							= msg_id<1, 1, 2>::value,
		mih_deregister									/// MIH_DeRegister.request
							= msg_id<1, 1, 3>::value,
		event_subscribe									/// MIH_Event_Subscribe.request
							= msg_id<1, 1, 4>::value,
		event_unsubscribe								/// MIH_Event_Unsubscribe.request
							= msg_id<1, 1, 5>::value,

		link_get_parameters										/// MIH_Link_Get_Parameters.request
									= msg_id<3, 1, 1>::value,
		link_configure_thresholds								/// MIH_Link_Configure_Thresholds.request
									= msg_id<3, 1, 2>::value,
		link_actions											/// MIH_Link_Actions.request
									= msg_id<3, 1, 3>::value,
		net_ho_candidate_query									/// MIH_Net_HO_Candidate_Query.request
									= msg_id<3, 1, 4>::value,
		mn_ho_candidate_query									/// MIH_MN_HO_Candidate_Query.request
									= msg_id<3, 1, 5>::value,
		n2n_ho_query_resources									/// MIH_N2N_HO_Query_Resources.request
									= msg_id<3, 1, 6>::value,
		mn_ho_commit											/// MIH_MN_HO_Commit.request
									= msg_id<3, 1, 7>::value,
		net_ho_commit											/// MIH_Net_HO_Commit.request
									= msg_id<3, 1, 8>::value,
		n2n_ho_commit											/// MIH_N2N_HO_Commit.request
									= msg_id<3, 1, 9>::value,
		mn_ho_complete											/// MIH_N2N_HO_Complete.request
									= msg_id<3, 1, 10>::value,
		n2n_ho_complete											/// MIH_N2N_HO_Commlete.request
									= msg_id<3, 1, 11>::value,

		get_information								/// MIH_Get_Information.request
						= msg_id<4, 1, 1>::value,

		push_information							/// MIH_Push_Information.request
		= msg_id<4, 1, 2>::value,
	};

	/**
	 * \brief Construct a MIH Request Message helper
	 */
	request() : message_helper(0, nullptr)
	{ }

	/**
	 * \brief Construct an MIH Request Message helper
	 * \param m MIH Message ID
	 */
	explicit request(mid m) : message_helper(m, nullptr)
	{ }

	/**
	 * \brief Construct an MIH Request Message helper
	 * \param m MIH Message ID
	 * \param destination MIH Message Destination MIHF ID
	 */
	request(mid m, const id& destination) :message_helper(m, &destination)
	{ }
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_REQUEST__HPP_ */
