//==============================================================================
// Brief   : User Book
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
#include "user_book.hpp"
#include "log.hpp"

///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

/**
 * Add a new MIH-User entry in the user book.
 *
 * @param id MIH-User MIH Identifier.
 * @param ip MIH-User IP address.
 * @param port MIH-User listening port.
 * @param supp_cmd MIH-User list of supported commands.
 * @param supp_iq MIH-User list of supported information server queries.
 */
void user_book::add(const mih::octet_string &id,
		            mih::octet_string& ip,
		            uint16 port,
		            boost::optional<mih::mih_cmd_list> supp_cmd,
		            boost::optional<mih::iq_type_list> supp_iq)
{
	boost::mutex::scoped_lock lock(_mutex);

	user_entry a;
	a.ip.assign(ip);
	a.port = port;
	a.supp_cmd = supp_cmd;
	a.supp_iq = supp_iq;

	_ubook[id] = a;
	ODTONE_LOG(4, "(user_book) added: ", id, " : ", ip, " : ", port);
}

/**
 * Set the IP address of an existing MIH-User entry.
 *
 * @param id MIH-User MIH Identifier.
 * @param ip The IP address to set.
 */
void user_book::set_ip(const mih::octet_string &id, std::string ip)
{
	boost::mutex::scoped_lock lock(_mutex);

	std::map<mih::octet_string, user_entry>::iterator it;
	it = _ubook.find(id);

	if (it == _ubook.end())
		it->second.ip = ip;
}

/**
 * Set the port of an existing MIH-User entry.
 *
 * @param id MIH-User MIH Identifier.
 * @param port The port to set.
 */
void user_book::set_port(const mih::octet_string &id, uint16 port)
{
	boost::mutex::scoped_lock lock(_mutex);

	std::map<mih::octet_string, user_entry>::iterator it;
	it = _ubook.find(id);

	if (it == _ubook.end())
		it->second.port = port;
}

/**
 * Remove an existing MIH-User entry.
 *
 * @param id MIH User MIH Identifier to remove.
 */
void user_book::del(mih::octet_string &id)
{
	boost::mutex::scoped_lock lock(_mutex);

	_ubook.erase(id);
}

/**
 * Get the record for a given MIH-User.
 *
 * @param id MIH-User MIH Identifier.
 * @return The record for a given MIH-User.
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
 * Get the list of all known MIH-Users.
 *
 * @return The list of all known MIH-Users.
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

/**
 * Get the MIH-User associated with the information server operations.
 *
 * @return The identifier of the MIH-User associated with the information
 * server operations.
 */
const boost::optional<mih::octet_string> user_book::information_user()
{
	boost::mutex::scoped_lock lock(_mutex);

	boost::optional<mih::octet_string> ret;



	return ret;
}

} /* namespace mihf */ } /* namespace odtone */
