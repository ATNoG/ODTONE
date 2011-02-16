//=============================================================================
// Brief   : MIH Confirm Message Helper
// Authors : Carlos Guimarães <cguimaraes@av.it.pt>
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
 * This class permits parsing/generating MIH Confirm messages. It derives
 * from odtone::mih::message_helper and will inherit all the features from base
 * class.
 */
class confirm : public message_helper {
public:

	enum mid {
		capability_discover									/// MIH_Capability_Discover.indication
									= msg_id<1, 0, 1>::value,

		event_subscribe									/// MIH_Event_Subscribe.request
									= msg_id<1, 0, 4>::value,

		event_unsubscribe								/// MIH_Event_Unsubscribe.request
									= msg_id<1, 0, 5>::value,

		link_get_parameters								/// MIH_Link_Get_Parameters.request
									= msg_id<3, 0, 1>::value,

		link_configure_thresholds						/// MIH_Link_Configure_Thresholds.request
									= msg_id<3, 0, 2>::value,

		link_actions									/// MIH_Link_Actions.request
									= msg_id<3, 0, 3>::value,

	};

	/**
	 * Construct an MIH Confirm Message helper with MIH Message ID equals to
	 * 0 (zero) and a null pointer for MIH Message Destination MIHF ID.
	 */
	confirm() : message_helper(0, nullptr)
	{ }

	/**
	 * Construct an MIH Confirm Message helper
	 *
	 * @param m MIH Message ID
	 */
	explicit confirm(mid m) : message_helper(m, nullptr)
	{ }

	/**
	 * Construct an MIH Confirm Message helper
	 *
	 * @param m MIH Message ID
	 * @param destination MIH Message Destination MIHF ID
	 */
	confirm(mid m, const id& destination) : message_helper(m, &destination)
	{ }
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_CONFIRM__HPP_ */
