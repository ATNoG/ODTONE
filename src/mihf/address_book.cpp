//==============================================================================
// Brief   : Address Book
// Authors : Simao Reis <sreis@av.it.pt>
//           Carlos Guimarães <cguimaraes@av.it.pt>
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
 * @param entry_info MIHF entry information.
 */
void address_book::add(const mih::octet_string &id,
					   address_entry entry_info)
{
	boost::mutex::scoped_lock lock(_mutex);

	std::map<mih::octet_string, address_entry>::const_iterator it;
	it = _abook.find(id);

	if (it == _abook.end()) {
		_abook[id] = entry_info;
		ODTONE_LOG(4, "(address_book) added: ", id);
	} else {
		if(entry_info.capabilities_list_net_type_addr.is_initialized()) {
			_abook[id].capabilities_list_net_type_addr = entry_info.capabilities_list_net_type_addr;
		}

		if(entry_info.capabilities_event_list.is_initialized()) {
			_abook[id].capabilities_event_list = entry_info.capabilities_event_list;
		}

		if(entry_info.capabilities_cmd_list.is_initialized()) {
			_abook[id].capabilities_cmd_list = entry_info.capabilities_cmd_list;
		}

		if(entry_info.capabilities_query_type.is_initialized()) {
			_abook[id].capabilities_query_type = entry_info.capabilities_query_type;
		}

		if(entry_info.capabilities_trans_list.is_initialized()) {
			_abook[id].capabilities_trans_list = entry_info.capabilities_trans_list;
		}

		if(entry_info.capabilities_mbb_ho_supp.is_initialized()) {
			_abook[id].capabilities_mbb_ho_supp = entry_info.capabilities_mbb_ho_supp;
		}

		ODTONE_LOG(4, "(address_book) updated: ", id);
	}
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

	if (it == _abook.end()) {
		throw ("no entry in address_book for this id");
	}

	return it->second;
}


} /* namespace mihf */ } /* namespace odtone */
