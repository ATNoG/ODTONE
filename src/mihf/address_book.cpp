//==============================================================================
// Brief   : Address Book
// Authors : Simao Reis <sreis@av.it.pt>
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
#include "address_book.hpp"
#include "log.hpp"
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

/**
 * Add a new MIHF entry in the address book.
 *
 * @param id MIHF MIH Identifier.
 * @param ip MIHF IP Address.
 * @param port MIHF listening port.
 * @param t MIHF supported transport protocols.
 */
void address_book::add(const mih::octet_string &id,
		       mih::octet_string& ip,
		       uint16 port,
		       mih::transport_list t)
{
	boost::mutex::scoped_lock lock(_mutex);
	// TODO: add thread safety
	address_entry a;

	a.ip.assign(ip);
	a.port = port;
	a.trans = t;

	_abook[id] = a;
	ODTONE_LOG(4, "(address_book) added: ", id, " ", ip, " ", port);
}

/**
 * Remove an existing MIHF entry.
 *
 * @param id MIHF MIH Identifier.
 */
void address_book::del(mih::octet_string &id)
{
	boost::mutex::scoped_lock lock(_mutex);

	_abook.erase(id);
}

/**
 * Get the record of a given MIHF.
 *
 * @param id MIHF MIH Identifier.
 * @return The record of a given MIHF stored in the address book.
 */
const address_entry& address_book::get(const mih::octet_string &id)
{
	boost::mutex::scoped_lock lock(_mutex);

	std::map<mih::octet_string, address_entry>::const_iterator it;
	it = _abook.find(id);

	if (it == _abook.end())
		throw ("no entry in address_book for this id");

	return it->second;
}


} /* namespace mihf */ } /* namespace odtone */
