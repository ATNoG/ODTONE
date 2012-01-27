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
		capability_discover	= msg_id<1, 0, 1>::value,		/**< MIH_Capability_Discover.indication	*/
		event_subscribe	= msg_id<1, 0, 4>::value,			/**< MIH_Event_Subscribe.request		*/
		event_unsubscribe = msg_id<1, 0, 5>::value,			/**< MIH_Event_Unsubscribe.request		*/
		link_get_parameters = msg_id<3, 0, 1>::value,		/**< MIH_Link_Get_Parameters.request	*/
		link_configure_thresholds = msg_id<3, 0, 2>::value,	/**< MIH_Link_Configure_Thresholds.request*/
		link_actions = msg_id<3, 0, 3>::value,				/**< MIH_Link_Actions.request			*/
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
