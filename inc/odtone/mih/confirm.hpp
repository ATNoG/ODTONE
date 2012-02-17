//=============================================================================
// Brief   : MIH Confirm Message Helper
// Authors : Carlos Guimarães <cguimaraes@av.it.pt>
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
//=============================================================================

#ifndef ODTONE_MIH_CONFIRM__HPP_
#define ODTONE_MIH_CONFIRM__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/debug.hpp>
#include <odtone/mih/message.hpp>
#include <boost/utility.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
/**
 * This class allows parsing and generating MIH Confirm messages.
 */
class confirm : public message_helper {
public:

	/**
	 * MIH Confirm Message ID
	 */
	enum mid {
		capability_discover	= msg_id<1, 0, 1>::value,		/**< MIH_Capability_Discover.confirm		*/
		event_subscribe	= msg_id<1, 0, 4>::value,			/**< MIH_Event_Subscribe.confirm			*/
		event_unsubscribe = msg_id<1, 0, 5>::value,			/**< MIH_Event_Unsubscribe.confirm			*/
		link_get_parameters = msg_id<3, 0, 1>::value,		/**< MIH_Link_Get_Parameters.confirm		*/
		link_configure_thresholds = msg_id<3, 0, 2>::value,	/**< MIH_Link_Configure_Thresholds.confirm	*/
		link_actions = msg_id<3, 0, 3>::value,				/**< MIH_Link_Actions.confirm				*/
		net_ho_candidate_query = msg_id<3, 0, 4>::value,	/**< MIH_Net_HO_Candidate_Query.confirm		*/
		mn_ho_candidate_query = msg_id<3, 0, 5>::value,		/**< MIH_MN_HO_Candidate_Query.confirm		*/
		n2n_ho_query_resources = msg_id<3, 0, 6>::value,	/**< MIH_N2N_HO_Query_Resources.confirm		*/
		mn_ho_commit = msg_id<3, 0, 7>::value,				/**< MIH_MN_HO_Commit.confirm				*/
		net_ho_commit = msg_id<3, 0, 8>::value,				/**< MIH_Net_HO_Commit.confirm				*/
		n2n_ho_commit = msg_id<3, 0, 9>::value,				/**< MIH_N2N_HO_Commit.confirm				*/
		mn_ho_complete = msg_id<3, 0, 10>::value,			/**< MIH_N2N_HO_Complete.confirm			*/
		n2n_ho_complete = msg_id<3, 0, 11>::value,			/**< MIH_N2N_HO_Commlete.confirm			*/
		get_information = msg_id<4, 0, 1>::value,			/**< MIH_Get_Information.confirm			*/
	};

	/**
	 * Construct an empty MIH Confirm Message helper.
	 */
	confirm() : message_helper(0, nullptr)
	{ }

	/**
	 * Construct a MIH Confirm Message helper.
	 *
	 * @param m The value of the MIH Message ID.
	 */
	explicit confirm(mid m) : message_helper(m, nullptr)
	{ }

	/**
	 * Construct a MIH Confirm Message helper.
	 *
	 * @param m The value of the MIH Message ID.
	 * @param destination The value of the MIH Message Destination MIHF ID.
	 */
	confirm(mid m, const id& destination) : message_helper(m, &destination)
	{ }
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_CONFIRM__HPP_ */
