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

#ifndef ODTONE_MIHF_ADDRESS_BOOK__HPP
#define ODTONE_MIHF_ADDRESS_BOOK__HPP

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/mih/message.hpp>
#include <odtone/mih/types/capabilities.hpp>

#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/optional.hpp>
#include <map>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

/**
 * Struct to store MIHF information like IP Address, listening port and transport
 * protocol.
 */
struct address_entry
{
	std::string ip;	/**< IP address.		*/
	uint16 port;	/**< Listening port.	*/

	// MIHF capabilities information
	boost::optional<mih::net_type_addr_list> capabilities_list_net_type_addr;
	boost::optional<mih::mih_evt_list>       capabilities_event_list;
	boost::optional<mih::mih_cmd_list>       capabilities_cmd_list;
	boost::optional<mih::iq_type_list>       capabilities_query_type;
	boost::optional<mih::transport_list>     capabilities_trans_list;
	boost::optional<mih::mbb_ho_supp_list>   capabilities_mbb_ho_supp;
};

/**
 * This class is used to store information about all known peer MIHFs. It makes
 * the correspondence between the MIHF MIH Identifier and the informations stored
 * in the address_entry struct.
 */
class address_book
{
public:
	/**
	 * Add a new MIHF entry in the address book.
	 *
	 * @param id MIHF MIH Identifier.
	 * @param entry_info MIHF entry information.
	 */
	void add(const mih::octet_string &id,
			 address_entry entry_info);

	/**
	 * Set the IP address of an existing MIHF entry.
	 *
	 * @param id MIHF MIH Identifier.
	 * @param ip The IP address to set.
	 */
	void set_ip(const mih::octet_string &id, std::string ip);

	/**
	 * Set the port of an existing MIHF entry.
	 *
	 * @param id MIHF MIH Identifier.
	 * @param port The port to set.
	 */
	void set_port(const mih::octet_string &id, uint16 port);

	/**
	 * Set the link address list of an existing MIHF entry.
	 *
	 * @param id MIHF MIH Identifier.
	 * @param list_net_type_addr The link address list to set.
	 */
	void set_link_address_list(const mih::octet_string &id,
							   boost::optional<mih::net_type_addr_list> list_net_type_addr);

	/**
	 * Set the list of supported events of an existing MIHF entry.
	 *
	 * @param id MIHF MIH Identifier.
	 * @param event_list The list of supported events to set.
	 */
	void set_event_list(const mih::octet_string &id,
							   boost::optional<mih::mih_evt_list> event_list);

	/**
	 * Set the list of supported commands of an existing MIHF entry.
	 *
	 * @param id MIHF MIH Identifier.
	 * @param cmd_list The list of supported commands to set.
	 */
	void set_command_list(const mih::octet_string &id,
							   boost::optional<mih::mih_cmd_list> cmd_list);

	/**
	 * Set the list of supported queries of an existing MIHF entry.
	 *
	 * @param id MIHF MIH Identifier.
	 * @param query_list The list of supported queries to set.
	 */
	void set_query_list(const mih::octet_string &id,
						boost::optional<mih::iq_type_list> query_list);

	/**
	 * Set the list of supported transport protocols of an existing MIHF entry.
	 *
	 * @param id MIHF MIH Identifier.
	 * @param trans_list The list of supported transport protocols to set.
	 */
	void set_transport_list(const mih::octet_string &id,
							boost::optional<mih::transport_list> trans_list);

	/**
	 * Set the mobility handover support list of an existing MIHF entry.
	 *
	 * @param id MIHF MIH Identifier.
	 * @param ho_list The mobility handover support list to set.
	 */
	void set_handover_list(const mih::octet_string &id,
						   boost::optional<mih::mbb_ho_supp_list> ho_list);

	/**
	 * Remove an existing MIHF entry.
	 *
	 * @param id MIHF MIH Identifier.
	 */
	void del(mih::octet_string &id);

	/**
	 * Get the record of a given MIHF.
	 *
	 * @param id MIHF MIH Identifier.
	 * @return The record of a given MIHF stored in the address book.
	 */
	const address_entry& get(const mih::octet_string &id);

private:
	std::map<mih::octet_string, address_entry> _abook;	/**< Address book map.	*/
	boost::mutex _mutex;								/**< Mutex.				*/
};

} /* namespace mihf */ } /* namespace odtone */

#endif
