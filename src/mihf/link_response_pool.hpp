//==============================================================================
// Brief   : Link Response Pool
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
//==============================================================================

#ifndef ODTONE_MIHF_LINK_RESPONSE_POOL__HPP
#define ODTONE_MIHF_LINK_RESPONSE_POOL__HPP

///////////////////////////////////////////////////////////////////////////////
#include "meta_message.hpp"

#include <odtone/base.hpp>
#include <odtone/mih/types.hpp>

#include <boost/thread.hpp>
#include <list>

///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

/**
 * Struct to store pending Link Responses informations.
 */
struct pending_link_response {
	mih::octet_string    user;
	uint16               tid;
	struct capabilities {
		mih::event_list   event_list;
		mih::command_list command_list;
	} cap;
	mih::link_status_rsp link_status;
	struct action_response {
		boost::optional<mih::link_ac_result>     link_ac_result;
		boost::optional<mih::link_scan_rsp_list> link_scan_rsp_list;
	} action;
};

/**
 * This class allows to store a pool of pending link responses.
 */
class link_response_pool
{
public:
	/**
	 * Link Response Pool constructor.
	 */
	link_response_pool();

	/**
	 * Add a new Link Response entry in the Link Responde Pool.
	 *
	 * @param user MIH User MIH Identifier.
	 * @param tid MIH Message Transaction ID.
	 * @param event event list.
	 * @param command command list.
	 */
	void add(mih::octet_string user,
                 uint16 tid,
                 mih::event_list event,
                 mih::command_list command);

	/**
	 * Add a new Link Response entry in the Link Responde Pool.
	 *
	 * @param user MIH User MIH Identifier.
	 * @param tid MIH Message Transaction ID.
	 * @param link_status link status response.
	 */
	void add(mih::octet_string user,
                 uint16 tid,
	         mih::link_status_rsp link_status);

	/**
	 * Add a new Link Response entry in the Link Responde Pool.
	 *
	 * @param user MIH User MIH Identifier.
	 * @param tid MIH Message Transaction ID.
	 * @param link_scan_rsp_list Link Scan Response List
	 * @param link_ac_result Link AC Result
	 */
	void add(mih::octet_string user,
                 uint16 tid,
	         boost::optional<mih::link_scan_rsp_list> link_scan_rsp_list,
	         boost::optional<mih::link_ac_result> link_ac_result);

	/**
	 * Remove a existing Link Response entry from the Link Response Pool
	 *
	 * @param tid MIH Message Transaction ID.
	 * @param id MIH User MIH Identifier.
	 */
	void del(const uint16 tid, const mih::octet_string id);

	/**
	 * Find a Link Response entry in the Link Response Pool
	 *
	 * @param tid MIH Message Transaction ID.
	 * @param id MIH User MIH Identifier.
	 * @return The Link Response entry.
	 */
	pending_link_response find(const uint16 tid, const mih::octet_string id);

	/**
	 * Check the existence of a Link Response entry in the Link Response Pool
	 *
	 * @param tid MIH Message Transaction ID.
	 * @param id MIH User MIH Identifier.
	 * @return True if exists or false otherwise.
	 */
	bool check(const uint16 tid, const mih::octet_string id);

protected:
	std::list<pending_link_response> _cpool;
	boost::mutex _mutex;
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace mihf */ } /* namespace odtone */


#endif
