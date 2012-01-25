//=============================================================================
// Brief   : MIH Response Message Helper
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
 * This class allows parsing/generating MIH Response messages.
 */
class response : public message_helper {
public:

	/**
	 * MIH Response Message ID
	 */
	enum mid {
		capability_discover	= msg_id<1, 2, 1>::value,		/**< MIH_Capability_Discover.response	*/
		mih_register = msg_id<1, 2, 2>::value,				/**< MIH_Register.response				*/
		mih_deregister = msg_id<1, 2, 3>::value,			/**< MIH_DeRegister.response			*/
		event_subscribe	= msg_id<1, 2, 4>::value,			/**< MIH_Event_Subscribe.response		*/
		event_unsubscribe = msg_id<1, 2, 5>::value,			/**< MIH_Event_Unsubscribe.response		*/
		link_get_parameters	= msg_id<3, 2, 1>::value,		/**< MIH_Link_Get_Parameters.response	*/
		link_configure_thresholds = msg_id<3, 2, 2>::value,	/**< MIH_Link_Configure_Thresholds.response*/
		link_actions = msg_id<3, 2, 3>::value,				/**< MIH_Link_Actions.response			*/
		net_ho_candidate_query = msg_id<3, 2, 4>::value,	/**< MIH_Net_HO_Candidate_Query.response*/
		mn_ho_candidate_query = msg_id<3, 2, 5>::value,		/**< MIH_MN_HO_Candidate_Query.response	*/
		n2n_ho_query_resources = msg_id<3, 2, 6>::value,	/**< MIH_N2N_HO_Query_Resources.response*/
		mn_ho_commit = msg_id<3, 2, 7>::value,				/**< MIH_MN_HO_Commit.response			*/
		net_ho_commit = msg_id<3, 2, 8>::value,				/**< MIH_Net_HO_Commit.response			*/
		n2n_ho_commit = msg_id<3, 2, 9>::value,				/**< MIH_N2N_HO_Commit.response			*/
		mn_ho_complete = msg_id<3, 2, 10>::value,			/**< MIH_N2N_HO_Complete.response		*/
		n2n_ho_complete = msg_id<3, 2, 11>::value,			/**< MIH_N2N_HO_Commlete.response		*/
		get_information	= msg_id<4, 2, 1>::value,			/**< MIH_Get_Information.response		*/
	};

	/**
	 * Construct an empty MIH Response Message helper.
	 */
	response() : message_helper(0, nullptr)
	{ }

	/**
	 * Construct a MIH Response Message helper.
	 *
	 * @param m The value of the MIH Message ID.
	 */
	explicit response(mid m) : message_helper(m, nullptr)
	{ }

	/**
	 * Construct an MIH Response Message helper.
	 *
	 * @param m The value of the MIH Message ID.
	 * @param destination The value of the MIH Message Destination MIHF ID.
	 */
	response(mid m, const id& destination) : message_helper(m, &destination)
	{ }
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_RESPONSE__HPP_ */
