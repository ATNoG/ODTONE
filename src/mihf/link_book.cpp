//==============================================================================
// Brief   : Link Book
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
#include "link_book.hpp"
#include "log.hpp"

///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

/**
 * Add a new Link SAP entry in the link book.
 *
 * @param id Link SAP MIH Identifier.
 * @param ip Link SAP IP address.
 * @param port Link SAP listening port.
 * @param link_id interfaces that Link SAP manages.
 */
void link_book::add(const mih::octet_string &id,
		            mih::octet_string& ip,
		            uint16 port,
		            mih::link_id link_id)
{
	boost::mutex::scoped_lock lock(_mutex);
	// TODO: add thread safety
	link_entry a;

	a.ip.assign(ip);
	a.port = port;
	a.link_id = link_id;
	a.fail = 0;
	a.status = true;

	_lbook[id] = a;
	ODTONE_LOG(4, "(link_book) added: ", id, " ", ip, " ", port);
}

/**
 * Set the IP address of an existing Link SAP entry.
 *
 * @param id Link SAP MIH Identifier.
 * @param ip The IP address to set.
 */
void link_book::set_ip(const mih::octet_string &id, std::string ip)
{
	boost::mutex::scoped_lock lock(_mutex);

	std::map<mih::octet_string, link_entry>::iterator it;
	it = _lbook.find(id);

	if (it != _lbook.end())
		it->second.ip = ip;
}

/**
 * Set the port of an existing Link SAP entry.
 *
 * @param id Link SAP MIH Identifier.
 * @param port The port to set.
 */
void link_book::set_port(const mih::octet_string &id, uint16 port)
{
	boost::mutex::scoped_lock lock(_mutex);

	std::map<mih::octet_string, link_entry>::iterator it;
	it = _lbook.find(id);

	if (it != _lbook.end())
		it->second.port = port;
}

/**
 * Update the events and commands supported by a Link SAP.
 *
 * @param id Link SAP MIH Identifier.
 * @param event_list Supported event list.
 * @param cmd_list Supported command list.
 */
void link_book::update_capabilities(const mih::octet_string &id,
									mih::link_evt_list event_list,
									mih::link_cmd_list cmd_list)

{
	boost::mutex::scoped_lock lock(_mutex);

	std::map<mih::octet_string, link_entry>::iterator it;
	it = _lbook.find(id);

	if (it != _lbook.end()) {
		it->second.event_list = event_list;
		it->second.cmd_list = cmd_list;
	}
}

/**
 * Remove an existing Link SAP entry.
 *
 * @param id Link SAP MIH Identifier.
 */
void link_book::del(mih::octet_string &id)
{
	boost::mutex::scoped_lock lock(_mutex);

	_lbook.erase(id);
}

/**
 * Inactive an existing Link SAP entry.
 *
 * @param id Link SAP MIH Identifier.
 */
void link_book::inactive(mih::octet_string &id)
{
	boost::mutex::scoped_lock lock(_mutex);

	std::map<mih::octet_string, link_entry>::iterator it;
	it = _lbook.find(id);

	if (it != _lbook.end())
		it->second.status = false;
}

/**
 * Get the record for a given Link SAP.
 *
 * @param id Link SAP MIH Identifier.
 * @return The record for a given Link SAP.
 */
const link_entry& link_book::get(const mih::octet_string &id)
{
	boost::mutex::scoped_lock lock(_mutex);

	std::map<mih::octet_string, link_entry>::const_iterator it;
	it = _lbook.find(id);

	if (it == _lbook.end())
		throw ("no entry in link_book for this id");

	return it->second;
}

/**
 * Get the list of all known Link SAPs.
 *
 * @return The list of all known Link SAPs.
 */
const std::vector<mih::octet_string> link_book::get_ids()
{
	boost::mutex::scoped_lock lock(_mutex);

	std::vector<mih::octet_string> ids;
	for(std::map<mih::octet_string, link_entry>::iterator it = _lbook.begin(); it != _lbook.end(); it++) {
		ids.push_back(it->first);
	}

	return ids;
}

/**
 * Search for the Link SAP MIH Identifier of a given interface.
 *
 * @param lt The link type of the Link SAP to search for.
 * @param la The link address of the Link SAP to search for.
 * @return The Link SAP MIH Identifier.
 */
const mih::octet_string link_book::search_interface(mih::link_type lt, mih::link_addr la)
{
	boost::mutex::scoped_lock lock(_mutex);

	mih::octet_string id;
	for(std::map<mih::octet_string, link_entry>::iterator it = _lbook.begin(); it != _lbook.end(); it++) {
		if(it->second.link_id.type == lt) {
			if(it->second.link_id.addr == la) {
				if(it->second.status) {
					id = it->first;
					break;
				}
			}
		}
	}

	return id;
}

/**
 * Update and return the number of fail responses of a given Link SAP.
 *
 * @param id Link SAP MIH Identifier.
 * @return The number of fails responses.
 */
uint16 link_book::fail(const mih::octet_string &id)
{
	boost::mutex::scoped_lock lock(_mutex);

	std::map<mih::octet_string, link_entry>::iterator it;
	it = _lbook.find(id);

	if (it == _lbook.end())
		throw ("no entry in link_book for this id");

	(it->second.fail)++;
	return it->second.fail;
}

/**
 * Reset the number of fail responses of a given Link SAP.
 *
 * @param id Link SAP MIH Identifier.
 */
void link_book::reset(const mih::octet_string &id)
{
	boost::mutex::scoped_lock lock(_mutex);

	std::map<mih::octet_string, link_entry>::iterator it;
	it = _lbook.find(id);

	if (it == _lbook.end())
		throw ("no entry in link_book for this id");

	it->second.fail = 0;
	it->second.status = true;
}

} /* namespace mihf */ } /* namespace odtone */
