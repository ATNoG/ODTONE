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

#ifndef ODTONE_MIHF_USER_BOOK__HPP
#define ODTONE_MIHF_USER_BOOK__HPP

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/mih/types/odtone.hpp>

#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <map>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

/**
 * Struct to store MIH-User information such as IP Address, listening port and
 * handover support.
 */
struct user_entry
{
	mih::octet_string	ip;			/**< IP address.		*/
	uint16				port;		/**< Listening port.	*/
	mih::user_role		role;		/**< MIH-User role.		*/
	uint8				priority;	/**< Role priority.		*/
};

/**
 * This class is used to store the information about all known MIH-Users. It
 * makes the correspondence between the MIH-User MIH Identifier and the
 * information stored in the user_entry struct.
 */
class user_book
{
public:

	/**
	 * Add a new MIH-User entry in the user book.
	 *
	 * @param id MIH-User MIH Identifier.
	 * @param ip MIH-User IP address.
	 * @param port MIH-User listening port.
	 * @param role MIH-User role.
	 */
	void add(const mih::octet_string &id,
	         mih::octet_string &ip,
	         uint16 port,
	         mih::user_role	role);

	/**
	 * Set the IP address of an existing MIH-User entry.
	 *
	 * @param id MIH-User MIH Identifier.
	 * @param ip The IP address to set.
	 */
	void set_ip(const mih::octet_string &id, std::string ip);

	/**
	 * Set the port of an existing MIH-User entry.
	 *
	 * @param id MIH-User MIH Identifier.
	 * @param port The port to set.
	 */
	void set_port(const mih::octet_string &id, uint16 port);

	/**
	 * Remove an existing MIH-User entry.
	 *
	 * @param id MIH User MIH Identifier to remove.
	 */
	void del(mih::octet_string &id);

	/**
	 * Get the record for a given MIH-User.
	 *
	 * @param id MIH-User MIH Identifier.
	 * @return The record for a given MIH-User.
	 */
	const user_entry& get(const mih::octet_string &id);

	/**
	 * Get the list of all known MIH-Users.
	 *
	 * @return The list of all known MIH-Users.
	 */
	const std::vector<mih::octet_string> get_ids();

	/**
	 * Get the MIH-User associated to the handover operations.
	 *
	 * @return The identifier of the MIH-User associated to the handover
	 * operations.
	 */
	const mih::octet_string mobility_user();

	/**
	 * Get the MIH-User associated to the information server operations.
	 *
	 * @return The identifier of the MIH-User associated to the information
	 * server operations.
	 */
	const mih::octet_string information_user();

	/**
	 * Get the MIH-User associated with the discovery operations.
	 *
	 * @return The identifier of the MIH-User associated with the discovery
	 * operations.
	 */
	const mih::octet_string discovery_user();

	/**
	 * Check if exists a MIH-User associated with the discovery operations.
	 *
	 * @return True if exists a MIH-User associated with the discovery
	 * operations or false otherwise.
	 */
	bool has_discovery_user();

	/**
	 * Get the list of all known MIH-Users associated with the discovery
	 * operations.
	 *
	 * @return The list of all known MIH-Users associated with the
	 * discovery operations.
	 */
	const std::map<mih::octet_string, user_entry> get_discovery_users();

private:

	std::map<mih::octet_string, user_entry> _ubook;	/**< User book map.	*/
	boost::mutex _mutex;							/**< Mutex.			*/
};

} /* namespace mihf */ } /* namespace odtone */

#endif
