//=============================================================================
// Brief   : MIH Message Request Helper
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
 * This class allows parsing/generating MIH Request messages.
 */
class request : public message_helper {
public:

	/**
	 * MIH Request Message ID
	 */
	enum mid {
		capability_discover	= msg_id<1, 1, 1>::value,		/**< MIH_Capability_Discover.request*/
		mih_register = msg_id<1, 1, 2>::value,				/**< MIH_Register.request			*/
		mih_deregister = msg_id<1, 1, 3>::value,			/**< MIH_DeRegister.request			*/
		event_subscribe = msg_id<1, 1, 4>::value,			/**< MIH_Event_Subscribe.request	*/
		event_unsubscribe = msg_id<1, 1, 5>::value,			/**< MIH_Event_Unsubscribe.request	*/
		link_get_parameters = msg_id<3, 1, 1>::value,		/**< MIH_Link_Get_Parameters.request*/
		link_configure_thresholds = msg_id<3, 1, 2>::value,	/**< MIH_Link_Configure_Thresholds.request*/
		link_actions = msg_id<3, 1, 3>::value,				/**< MIH_Link_Actions.request		*/
		net_ho_candidate_query = msg_id<3, 1, 4>::value,	/**< MIH_Net_HO_Candidate_Query.request*/
		mn_ho_candidate_query = msg_id<3, 1, 5>::value,		/**< MIH_MN_HO_Candidate_Query.request*/
		n2n_ho_query_resources = msg_id<3, 1, 6>::value,	/**< MIH_N2N_HO_Query_Resources.request*/
		mn_ho_commit = msg_id<3, 1, 7>::value,				/**< MIH_MN_HO_Commit.request		*/
		net_ho_commit = msg_id<3, 1, 8>::value,				/**< MIH_Net_HO_Commit.request		*/
		n2n_ho_commit = msg_id<3, 1, 9>::value,				/**< MIH_N2N_HO_Commit.request		*/
		mn_ho_complete = msg_id<3, 1, 10>::value,			/**< MIH_N2N_HO_Complete.request	*/
		n2n_ho_complete = msg_id<3, 1, 11>::value,			/**< MIH_N2N_HO_Commlete.request	*/
		get_information = msg_id<4, 1, 1>::value,			/**< MIH_Get_Information.request	*/
		push_information = msg_id<4, 1, 2>::value,			/**< MIH_Push_Information.request	*/
	};

	/**
	 * Construct an empty MIH Request Message helper.
	 */
	request() : message_helper(0, nullptr)
	{ }

	/**
	 * Construct an MIH Request Message helper.
	 *
	 * @param m The value of the MIH Message ID.
	 */
	explicit request(mid m) : message_helper(m, nullptr)
	{ }

	/**
	 * Construct an MIH Request Message helper.
	 *
	 * @param m The value of the MIH Message ID.
	 * @param destination The value of the MIH Message Destination MIHF ID.
	 */
	request(mid m, const id& destination) :message_helper(m, &destination)
	{ }
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_REQUEST__HPP_ */
