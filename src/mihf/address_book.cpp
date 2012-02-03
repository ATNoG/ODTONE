//==============================================================================
// Brief   : Address Book
// Authors : Simao Reis <sreis@av.it.pt>
//           Carlos Guimarães <cguimaraes@av.it.pt>
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

	std::map<mih::octet_string, address_entry>::iterator it;
	it = _abook.find(id);

	if (it != _abook.end()) {
		entry_info.ip = it->second.ip;
		entry_info.port = it->second.port;
	}

	_abook[id] = entry_info;
	ODTONE_LOG(4, "(address_book) added: ", id);
}

/**
 * Set the IP address of an existing MIHF entry.
 *
 * @param id MIHF MIH Identifier.
 * @param ip The IP address to set.
 */
void address_book::set_ip(const mih::octet_string &id, std::string ip)
{
	boost::mutex::scoped_lock lock(_mutex);

	std::map<mih::octet_string, address_entry>::iterator it;
	it = _abook.find(id);

	if (it != _abook.end())
		it->second.ip = ip;
}

/**
 * Set the port of an existing MIHF entry.
 *
 * @param id MIHF MIH Identifier.
 * @param port The port to set.
 */
void address_book::set_port(const mih::octet_string &id, uint16 port)
{
	boost::mutex::scoped_lock lock(_mutex);

	std::map<mih::octet_string, address_entry>::iterator it;
	it = _abook.find(id);

	if (it != _abook.end())
		it->second.port = port;
}

/**
 * Set the link address list of an existing MIHF entry.
 *
 * @param id MIHF MIH Identifier.
 * @param list_net_type_addr The link address list to set.
 */
void address_book::set_link_address_list(const mih::octet_string &id,
							boost::optional<mih::net_type_addr_list> list_net_type_addr)
{
	boost::mutex::scoped_lock lock(_mutex);

	std::map<mih::octet_string, address_entry>::iterator it;
	it = _abook.find(id);

	if (it != _abook.end())
		it->second.capabilities_list_net_type_addr = list_net_type_addr;
}

/**
 * Set the list of supported events of an existing MIHF entry.
 *
 * @param id MIHF MIH Identifier.
 * @param event_list The list of supported events to set.
 */
void address_book::set_event_list(const mih::octet_string &id,
								  boost::optional<mih::mih_evt_list> event_list)
{
	boost::mutex::scoped_lock lock(_mutex);

	std::map<mih::octet_string, address_entry>::iterator it;
	it = _abook.find(id);

	if (it != _abook.end())
		it->second.capabilities_event_list = event_list;
}

/**
 * Set the list of supported commands of an existing MIHF entry.
 *
 * @param id MIHF MIH Identifier.
 * @param cmd_list The list of supported commands to set.
 */
void address_book::set_command_list(const mih::octet_string &id,
									boost::optional<mih::mih_cmd_list> cmd_list)
{
	boost::mutex::scoped_lock lock(_mutex);

	std::map<mih::octet_string, address_entry>::iterator it;
	it = _abook.find(id);

	if (it != _abook.end())
		it->second.capabilities_cmd_list = cmd_list;
}

/**
 * Set the list of supported queries of an existing MIHF entry.
 *
 * @param id MIHF MIH Identifier.
 * @param query_list The list of supported queries to set.
 */
void address_book::set_query_list(const mih::octet_string &id,
								  boost::optional<mih::iq_type_list> query_list)
{
	boost::mutex::scoped_lock lock(_mutex);

	std::map<mih::octet_string, address_entry>::iterator it;
	it = _abook.find(id);

	if (it != _abook.end())
		it->second.capabilities_query_type = query_list;
}

/**
 * Set the list of supported transport protocols of an existing MIHF entry.
 *
 * @param id MIHF MIH Identifier.
 * @param trans_list The list of supported transport protocols to set.
 */
void address_book::set_transport_list(const mih::octet_string &id,
									  boost::optional<mih::transport_list> trans_list)
{
	boost::mutex::scoped_lock lock(_mutex);

	std::map<mih::octet_string, address_entry>::iterator it;
	it = _abook.find(id);

	if (it != _abook.end())
		it->second.capabilities_trans_list = trans_list;
}

/**
 * Set the mobility handover support list of an existing MIHF entry.
 *
 * @param id MIHF MIH Identifier.
 * @param ho_list The mobility handover support list to set.
 */
void address_book::set_handover_list(const mih::octet_string &id,
									  boost::optional<mih::mbb_ho_supp_list> ho_list)
{
	boost::mutex::scoped_lock lock(_mutex);

	std::map<mih::octet_string, address_entry>::iterator it;
	it = _abook.find(id);

	if (it != _abook.end())
		it->second.capabilities_mbb_ho_supp = ho_list;
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
