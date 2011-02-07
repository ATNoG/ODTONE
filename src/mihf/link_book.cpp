//
// Copyright (c) 2007-2009 2009 Universidade Aveiro - Instituto de
// Telecomunicacoes Polo Aveiro
// This file is part of ODTONE - Open Dot Twenty One.
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//
// Author:     Carlos Guimarães <cguimaraes@av.it.pt>
//

///////////////////////////////////////////////////////////////////////////////
#include "link_book.hpp"
#include "log.hpp"

///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

/**
 * Add a new Link SAP.
 *
 * @param id Link SAP MIHF ID
 * @param ip Link SAP IP address
 * @param port Link SAP listening port
 * @param link_id interfaces that Link SAP manages
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

	_lbook[id] = a;
	log(4, "(link_book) added: ", id, " ", ip, " ", port);
}

/**
 * Remove a known Link SAP.
 *
 * @param id Link SAP MIHF ID
 */
void link_book::del(mih::octet_string &id)
{
	boost::mutex::scoped_lock lock(_mutex);

	_lbook.erase(id);
}

/**
 * Get all informations stored from a given Link SAP
 *
 * @param id Link SAP MIHF ID
 * @return all informations stored from a given Link SAP
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
 * Get the list of all known Link SAPs
 *
 * @return the list of all known Link SAPs
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
 * Search for the link identifier of a given interface
 *
 * @return the link identifier
 */
const mih::octet_string link_book::search_interface(mih::link_type lt, mih::link_addr la)
{
	boost::mutex::scoped_lock lock(_mutex);

	mih::octet_string id;
	for(std::map<mih::octet_string, link_entry>::iterator it = _lbook.begin(); it != _lbook.end(); it++) {
		if(it->second.link_id.type == lt) {
			if(it->second.link_id.addr == la) {
				id = it->first;
				break;
			}
		}
	}

	return id;
}

} /* namespace mihf */ } /* namespace odtone */
