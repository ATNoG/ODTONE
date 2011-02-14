//=============================================================================
// Brief   : MIH Indication Message Helper
// Authors : Bruno Santos <bsantos@av.it.pt>
//------------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2009-2011 Universidade Aveiro
// Copyright (C) 2009-2011 Instituto de Telecomunicações - Pólo Aveiro
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//==============================================================================

#ifndef ODTONE_MIH_INDICATION__HPP_
#define ODTONE_MIH_INDICATION__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/debug.hpp>
#include <odtone/mih/message.hpp>
#include <boost/utility.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
/**
 * This class permits parsing/generating MIH Indication messages. It derives
 * from odtone::mih::message_helper and will inherit all the features from base
 * class.
 */
class indication : public message_helper {
public:
	/**
	 * MIH Indication Message ID
	 */
	enum mid {
		capability_discover									/// MIH_Capability_Discover.indication
								= msg_id<1, 3, 1>::value,
		mih_register										/// MIH_Register.indication
								= msg_id<1, 3, 2>::value,
		mih_deregister										/// MIH_DeRegister.indication
								= msg_id<1, 3, 3>::value,
		event_subscribe										/// MIH_Event_Subscribe.indication
								= msg_id<1, 3, 4>::value,
		event_unsubscribe									/// MIH_Event_Unsubscribe.indication
								= msg_id<1, 3, 5>::value,

		link_detected										/// MIH_Link_Detected.indication
								= msg_id<2, 3, 1>::value,
		link_up												/// MIH_Link_Up.indication
								= msg_id<2, 3, 2>::value,
		link_down											/// MIH_Link_Down.indication
								= msg_id<2, 3, 3>::value,
		link_parameters_report								/// MIH_Link_Parameters_Report.indication
								= msg_id<2, 3, 5>::value,
		link_going_down										/// MIH_Link_Going_Down.indication
								= msg_id<2, 3, 6>::value,
		link_handover_imminent								/// MIH_Link_Handover_Imminent.indication
								= msg_id<2, 3, 7>::value,
		link_handover_complete								/// MIH_Link_Handover_Complete.indication
								= msg_id<2, 3, 8>::value,

		link_get_parameters									/// MIH_Link_Get_Parameters.indication
								= msg_id<3, 3, 1>::value,
		link_configure_threshold							/// MIH_Link_Configure_Thresholds.indication
								= msg_id<3, 3, 2>::value,
		link_actions										/// MIH_Link_Actions.indication
								= msg_id<3, 3, 3>::value,
		net_ho_candidate_query								/// MIH_Net_HO_Candidate_Query.indication
								= msg_id<3, 3, 4>::value,
		mn_ho_candidate_query								/// MIH_MN_HO_Candidate_Query.indication
								= msg_id<3, 3, 5>::value,
		n2n_ho_query_resources								/// MIH_N2N_HO_Query_Resources.indication
								= msg_id<3, 3, 6>::value,
		mn_ho_commit										/// MIH_MN_HO_Commit.indication
								= msg_id<3, 3, 7>::value,
		net_ho_commit										/// MIH_Net_HO_Commit.indication
								= msg_id<3, 3, 8>::value,
		n2n_ho_commit										/// MIH_N2N_HO_Commit.indication
								= msg_id<3, 3, 9>::value,
		mn_ho_complete										/// MIH_N2N_HO_Complete.indication
								= msg_id<3, 3, 10>::value,
		n2n_ho_complete										/// MIH_N2N_HO_Commlete.indication
								= msg_id<3, 3, 11>::value,

		get_information 									/// MIH_Get_Information.indication
								= msg_id<4, 3, 1>::value,
		push_information									/// MIH_Push_Information.indication
								= msg_id<4, 3, 2>::value,

		// ODTONE specific messages
		link_register										/// Link_Register.indication
								= msg_id<1, 3, 6>::value,
		user_register										/// User_Register.indication
								= msg_id<1, 3, 7>::value
	};

	/**
	 * Construct an MIH Indication Message helper with MIH Message ID equals to
	 * 0 (zero) and a null pointer for MIH Message Destination MIHF ID.
	 */
	indication() : message_helper(0, nullptr)
	{ }

	/**
	 * Construct an MIH Indication Message helper
	 *
	 * @param m MIH Message ID
	 */
	explicit indication(mid m) : message_helper(m, nullptr)
	{ }

	/**
	 * Construct an MIH Indication Message helper
	 *
	 * @param m MIH Message ID
	 * @param destination MIH Message Destination MIHF ID
	 */
	indication(mid m, const id& destination) : message_helper(m, &destination)
	{ }
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_INDICATION__HPP_ */
