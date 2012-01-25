//==============================================================================
// Brief   : Link Response Pool
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
//==============================================================================

///////////////////////////////////////////////////////////////////////////////
#include "link_response_pool.hpp"
#include "log.hpp"

#include <odtone/mih/confirm.hpp>
#include <odtone/mih/tlv_types.hpp>

///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

/**
 * Construct a Link Response Pool.
 */
link_response_pool::link_response_pool()
{
}

/**
 * Add a new entry in the Link Responde Pool.
 *
 * @param user The MIH source identifier.
 * @param tid The transaction identifier.
 * @param link_status The link status response.
 */
void link_response_pool::add(mih::octet_string user,
                             uint16 tid,
                             mih::link_status_rsp link_status)
{
	pending_link_response p;

	p.user.assign(user);
	p.tid = tid;
	p.response = link_status;

	boost::mutex::scoped_lock lock(_mutex);
	_cpool.push_back(p);

}

/**
 * Add a new entry in the Link Responde Pool.
 *
 * @param user MIH source identifier.
 * @param tid The transaction identifier.
 * @param link_scan_rsp_list The link scan response list.
 * @param link_ac_result The link action result
 */
void link_response_pool::add(mih::octet_string user,
                             uint16 tid,
                             boost::optional<mih::link_scan_rsp_list> link_scan_rsp_list,
                             mih::link_ac_result link_ac_result)
{
	pending_link_response p;

	p.user.assign(user);
	p.tid = tid;
	action ac;
	if(link_scan_rsp_list.is_initialized()) {
		ac.link_scan_rsp_list = link_scan_rsp_list;
	}
	ac.link_ac_result = link_ac_result;
	p.response = ac;

	boost::mutex::scoped_lock lock(_mutex);
	_cpool.push_back(p);
}

/**
 * Remove an existing record from the Link Response Pool
 *
 * @param tid The transaction identifier to be removed.
 * @param id The MIH source identifier to be removed.
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
 * Searchs for a record in the Link Response Pool.
 *
 * @param tid The transaction identifier to search for.
 * @param id The MIH source identifier to search for.
 * @return The Link Response record found.
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
 * Check the existence of a record in the Link Response Pool.
 *
 * @param tid The transaction identifier to search for.
 * @param id The MIH source identifier to search for.
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
