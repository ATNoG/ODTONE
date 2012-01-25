//=============================================================================
// Brief   : MIH Indication Message Helper
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
 * This class allows parsing/generating MIH Indication messages.
 */
class indication : public message_helper {
public:
	/**
	 * MIH Indication Message ID
	 */
	enum mid {
		capability_discover = msg_id<1, 3, 1>::value,		/**< MIH_Capability_Discover.indication*/
		mih_register = msg_id<1, 3, 2>::value,				/**< MIH_Register.indication*/
		mih_deregister = msg_id<1, 3, 3>::value,			/**< MIH_DeRegister.indication*/
		event_subscribe = msg_id<1, 3, 4>::value,			/**< MIH_Event_Subscribe.indication*/
		event_unsubscribe = msg_id<1, 3, 5>::value,			/**< MIH_Event_Unsubscribe.indication*/
		link_detected = msg_id<2, 3, 1>::value,				/**< MIH_Link_Detected.indication*/
		link_up = msg_id<2, 3, 2>::value,					/**< MIH_Link_Up.indication*/
		link_down = msg_id<2, 3, 3>::value,					/**< MIH_Link_Down.indication*/
		link_parameters_report = msg_id<2, 3, 5>::value,	/**< MIH_Link_Parameters_Report.indication*/
		link_going_down = msg_id<2, 3, 6>::value,			/**< MIH_Link_Going_Down.indication*/
		link_handover_imminent = msg_id<2, 3, 7>::value,	/**< MIH_Link_Handover_Imminent.indication*/
		link_handover_complete = msg_id<2, 3, 8>::value,	/**< MIH_Link_Handover_Complete.indication*/
		link_pdu_transmit_status = msg_id<2, 3, 9>::value,	/**< MIH_Link_PDU_transmit_status.indication*/
		link_get_parameters = msg_id<3, 3, 1>::value,		/**< MIH_Link_Get_Parameters.indication*/
		link_configure_threshold = msg_id<3, 3, 2>::value,	/**< MIH_Link_Configure_Thresholds.indication*/
		link_actions = msg_id<3, 3, 3>::value,				/**< MIH_Link_Actions.indication	*/
		net_ho_candidate_query = msg_id<3, 3, 4>::value,	/**< MIH_Net_HO_Candidate_Query.indication*/
		mn_ho_candidate_query = msg_id<3, 3, 5>::value,		/**< MIH_MN_HO_Candidate_Query.indication*/
		n2n_ho_query_resources = msg_id<3, 3, 6>::value,	/**< MIH_N2N_HO_Query_Resources.indication*/
		mn_ho_commit = msg_id<3, 3, 7>::value,				/**< MIH_MN_HO_Commit.indication	*/
		net_ho_commit = msg_id<3, 3, 8>::value,				/**< MIH_Net_HO_Commit.indication	*/
		n2n_ho_commit = msg_id<3, 3, 9>::value,				/**< MIH_N2N_HO_Commit.indication	*/
		mn_ho_complete = msg_id<3, 3, 10>::value,			/**< MIH_N2N_HO_Complete.indication	*/
		n2n_ho_complete = msg_id<3, 3, 11>::value,			/**< MIH_N2N_HO_Commlete.indication	*/
		get_information = msg_id<4, 3, 1>::value,			/**< MIH_Get_Information.indication	*/
		push_information = msg_id<4, 3, 2>::value,			/**< MIH_Push_Information.indication*/
		// ODTONE specific messages
		link_register = msg_id<1, 3, 6>::value,				/**< Link_Register.indication	*/
		user_register = msg_id<1, 3, 7>::value				/**< User_Register.indication	*/
	};

	/**
	 * Construct an empty MIH Indication Message helper.
	 */
	indication() : message_helper(0, nullptr)
	{ }

	/**
	 * Construct an MIH Indication Message helper.
	 *
	 * @param m The value of the MIH Message ID.
	 */
	explicit indication(mid m) : message_helper(m, nullptr)
	{ }

	/**
	 * Construct an MIH Indication Message helper.
	 *
	 * @param m The value of the MIH Message ID.
	 * @param destination The value of the MIH Message Destination MIHF ID.
	 */
	indication(mid m, const id& destination) : message_helper(m, &destination)
	{ }
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_INDICATION__HPP_ */
