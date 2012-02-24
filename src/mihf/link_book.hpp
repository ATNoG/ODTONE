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

#ifndef ODTONE_MIHF_LINK_BOOK__HPP
#define ODTONE_MIHF_LINK_BOOK__HPP

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/mih/types/capabilities.hpp>

#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <map>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

/**
 * Struct to store Link SAP information such as IP Address, listening port,
 * interface that Link SAP manages and the number of fail responses.
 */
struct link_entry
{
	mih::octet_string	ip;			/**< IP address.						*/
	uint16				port;		/**< Listening port.					*/
	mih::link_id		link_id;	/**< Link identifier.					*/
	mih::link_evt_list	event_list;	/**< Supported event list.				*/
	mih::link_cmd_list	cmd_list;	/**< Supported command list.			*/
	uint16				fail;		/**< Number of fail responses.			*/
	bool				status;		/**< Status of the Link SAP (on/off).	*/
};

/**
 * This class is used to store the information about all known Link SAPs.
 * It makes the correspondence between the Link SAP MIH Identifier and
 * the information stored in the link_entry struct.
 */
class link_book
{
public:

	/**
	 * Add a new Link SAP entry in the link book.
	 *
	 * @param id Link SAP MIH Identifier.
	 * @param ip Link SAP IP address.
	 * @param port Link SAP listening port.
	 * @param link_id interface that Link SAP manages.
	 */
	void add(const mih::octet_string &id,
	         mih::octet_string &ip,
	         uint16 port,
	         mih::link_id link_id);

	/**
	 * Set the IP address of an existing Link SAP entry.
	 *
	 * @param id Link SAP MIH Identifier.
	 * @param ip The IP address to set.
	 */
	void set_ip(const mih::octet_string &id, std::string ip);

	/**
	 * Set the port of an existing Link SAP entry.
	 *
	 * @param id Link SAP MIH Identifier.
	 * @param port The port to set.
	 */
	void set_port(const mih::octet_string &id, uint16 port);

	/**
	 * Update the events and commands supported by a Link SAP.
	 *
	 * @param id Link SAP MIH Identifier.
	 * @param event_list Supported event list.
	 * @param cmd_list Supported command list.
	 */
	void update_capabilities(const mih::octet_string &id,
							 mih::link_evt_list event_list,
							 mih::link_cmd_list cmd_list);

	/**
	 * Remove an existing Link SAP entry.
	 *
	 * @param id Link SAP MIH Identifier.
	 */
	void del(mih::octet_string &id);

	/**
	 * Inactive an existing Link SAP entry.
	 *
	 * @param id Link SAP MIH Identifier.
	 */
	void inactive(mih::octet_string &id);

	/**
	 * Get the record for a given Link SAP.
	 *
	 * @param id Link SAP MIH Identifier.
	 * @return The record for a given Link SAP.
	 */
	const link_entry& get(const mih::octet_string &id);

	/**
	 * Get the list of all known Link SAPs.
	 *
	 * @return The list of all known Link SAPs.
	 */
	const std::vector<mih::octet_string> get_ids();

	/**
	 * Search for the Link SAP MIH Identifier of a given interface.
	 *
	 * @param lt The link type of the Link SAP to search for.
	 * @param la The link address of the Link SAP to search for.
	 * @return The Link SAP MIH Identifier.
	 */
	const mih::octet_string search_interface(mih::link_type lt, mih::link_addr la);

	/**
	 * Update and return the number of fail responses of a given Link SAP.
	 *
	 * @param id Link SAP MIH Identifier.
	 * @return The number of fails responses.
	 */
	uint16 fail(const mih::octet_string &id);

	/**
	 * Reset the number of fail responses of a given Link SAP.
	 *
	 * @param id Link SAP MIH Identifier.
	 */
	void reset(const mih::octet_string &id);
private:

	std::map<mih::octet_string, link_entry> _lbook;	/**< Link book map.	*/
	boost::mutex _mutex;							/**< Mutex.			*/
};

} /* namespace mihf */ } /* namespace odtone */

#endif
