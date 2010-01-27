//=============================================================================
// Brief   : MIH Indication Message Helper
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
 * \brief MIH Indication Message helper
 */
class indication : public message_helper {
public:
	/**
	 * \brief MIH Indication Message ID
	 */
	enum mid {
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

		push_information								/// MIH_Push_Information.indication
							= msg_id<4, 3, 2>::value,
	};

	/**
	 * \brief Construct a MIH Indication Message helper
	 */
	indication() : message_helper(0, nullptr)
	{ }

	/**
	 * \brief Construct an MIH Indication Message helper
	 * \param m MIH Message ID
	 */
	explicit indication(mid m) : message_helper(m, nullptr)
	{ }

	/**
	 * \brief Construct an MIH Indication Message helper
	 * \param m MIH Message ID
	 * \param destination MIH Message Destination MIHF ID
	 */
	indication(mid m, const id& destination) : message_helper(m, &destination)
	{ }
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_INDICATION__HPP_ */
