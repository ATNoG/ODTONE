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
#include "user_book.hpp"
#include "log.hpp"

///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

/**
 * Add a new MIH User.
 *
 * @param id MIH User MIHF ID
 * @param ip MIH User IP address
 * @param port MIH User listening port
 */
void user_book::add(const mih::octet_string &id,
		            mih::octet_string& ip,
		            uint16 port)
{
	boost::mutex::scoped_lock lock(_mutex);
	// TODO: add thread safety
	user_entry a;

	a.ip.assign(ip);
	a.port = port;

	_ubook[id] = a;
	log(4, "(user_book) added: ", id, " ", ip, " ", port);
}

/**
 * Remove a known MIH User.
 *
 * @param id MIH User MIHF ID
 */
void user_book::del(mih::octet_string &id)
{
	boost::mutex::scoped_lock lock(_mutex);

	_ubook.erase(id);
}

/**
 * Get all informations stored from a given MIH User
 *
 * @param id MIH User MIHF ID
 * @return all informations stored from a given MIH User
 */
const user_entry& user_book::get(const mih::octet_string &id)
{
	boost::mutex::scoped_lock lock(_mutex);

	std::map<mih::octet_string, user_entry>::const_iterator it;
	it = _ubook.find(id);

	if (it == _ubook.end())
		throw ("no entry in user_book for this id");

	return it->second;
}

/**
 * Get the list of all known MIH Users
 *
 * @return the list of all known MIH Users
 */
const std::vector<mih::octet_string> user_book::get_ids()
{
	boost::mutex::scoped_lock lock(_mutex);

	std::vector<mih::octet_string> ids;
	for(std::map<mih::octet_string, user_entry>::iterator it = _ubook.begin(); it != _ubook.end(); it++) {
		ids.push_back(it->first);
	}

	return ids;
}


} /* namespace mihf */ } /* namespace odtone */
