//==============================================================================
// Brief   : User Book
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
#include "user_book.hpp"
#include "log.hpp"

///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

/**
 * Add a new MIH User entry in the user book.
 *
 * @param id MIH User MIH Identifier.
 * @param ip MIH User IP address.
 * @param port MIH User listening port.
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
 * Remove a existing MIH User entry from the link book.
 *
 * @param id MIH User MIH Identifier.
 */
void user_book::del(mih::octet_string &id)
{
	boost::mutex::scoped_lock lock(_mutex);

	_ubook.erase(id);
}

/**
 * Get all informations stored from a given MIH User.
 *
 * @param id MIH User MIH Identifier.
 * @return All informations stored from a given MIH User.
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
 * Get the list of all known MIH Users.
 *
 * @return The list of all known MIH Users.
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
