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

///////////////////////////////////////////////////////////////////////////////
#include "link_response_pool.hpp"
#include "log.hpp"

#include <odtone/mih/confirm.hpp>
#include <odtone/mih/tlv_types.hpp>

///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

/**
 * Link Response Pool constructor.
 */
link_response_pool::link_response_pool()
{
}

/**
 * Add a new Link Response entry in the Link Responde Pool.
 *
 * @param user MIH User MIH Identifier.
 * @param tid MIH Message Transaction ID.
 * @param event event list.
 * @param command command list.
 */
void link_response_pool::add(mih::octet_string user,
                             uint16 tid,
                             mih::event_list event,
                             mih::command_list command)
{
	pending_link_response p;

	p.user.assign(user);
	p.tid = tid;
	p.cap.event_list = event;
	p.cap.command_list = command;

	boost::mutex::scoped_lock lock(_mutex);
	_cpool.push_back(p);

}

/**
 * Add a new Link Response entry in the Link Responde Pool.
 *
 * @param user MIH User MIH Identifier.
 * @param tid MIH Message Transaction ID.
 * @param link_status link status response.
 */
void link_response_pool::add(mih::octet_string user,
                             uint16 tid,
                             mih::link_status_rsp link_status)
{
	pending_link_response p;

	p.user.assign(user);
	p.tid = tid;
	p.link_status = link_status;

	boost::mutex::scoped_lock lock(_mutex);
	_cpool.push_back(p);

}

/**
 * Add a new Link Response entry in the Link Responde Pool.
 *
 * @param user MIH User MIH Identifier.
 * @param tid MIH Message Transaction ID.
 * @param link_scan_rsp_list Link Scan Response List
 * @param link_ac_result Link AC Result
 */
void link_response_pool::add(mih::octet_string user,
                             uint16 tid,
                             boost::optional<mih::link_scan_rsp_list> link_scan_rsp_list,
                             mih::link_ac_result link_ac_result)
{
	pending_link_response p;

	p.user.assign(user);
	p.tid = tid;
	if(link_scan_rsp_list.is_initialized()) {
		p.action.link_scan_rsp_list = link_scan_rsp_list;
	}
	p.action.link_ac_result = link_ac_result;

	boost::mutex::scoped_lock lock(_mutex);
	_cpool.push_back(p);
}

/**
 * Remove a existing Link Response entry from the Link Response Pool
 *
 * @param tid MIH Message Transaction ID.
 * @param id MIH User MIH Identifier.
 */
void link_response_pool::del(const uint16 tid, const mih::octet_string id)
{
	std::list<pending_link_response>::iterator it;

	for(it = _cpool.begin(); it != _cpool.end(); it++) {
		if (it->tid == tid && it->user == id)
		{
			_cpool.erase(it);
			break;
		}
	}
}

/**
 * Find a Link Response entry in the Link Response Pool
 *
 * @param tid MIH Message Transaction ID.
 * @param id MIH User MIH Identifier.
 * @return The Link Response entry.
 */
pending_link_response link_response_pool::find(const uint16 tid, const mih::octet_string id)
{
	std::list<pending_link_response>::iterator it;

	for(it = _cpool.begin(); it != _cpool.end(); it++) {
		if (it->tid == tid && it->user == id)
			break;
	}
	return *it;
}

/**
 * Check the existence of a Link Response entry in the Link Response Pool
 *
 * @param tid MIH Message Transaction ID.
 * @param id MIH User MIH Identifier.
 * @return True if exists or false otherwise.
 */
bool link_response_pool::check(const uint16 tid, const mih::octet_string id)
{
	std::list<pending_link_response>::iterator it;

	for(it = _cpool.begin(); it != _cpool.end(); it++) {
		if (it->tid == tid && it->user == id)
			return true;
	}
	return false;
}


} /* namespace mihf */ } /* namespace odtone */
