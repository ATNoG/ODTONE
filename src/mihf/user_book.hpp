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
#include <odtone/mih/types/capabilities.hpp>

#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <map>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

/**
 * Struct to store MIHF information like IP Address, listening port and handover
 * support.
 */
struct user_entry
{
	mih::octet_string ip;
	uint16            port;
	bool              mbbhandover_support;
};

/**
 * This class is used to store information about all known MIH Users. It makes
 * the correspondence between the MIH User MIH Identifier and the informations
 * stored in the user_entry struct.
 */
class user_book
{
public:

	/**
	 * Add a new MIH User entry in the user book.
	 *
	 * @param id MIH User MIH Identifier.
	 * @param ip MIH User IP address.
	 * @param port MIH User listening port.
	 * @param mbbsupport MIH User Handover support.
	 */
	void add(const mih::octet_string &id,
	         mih::octet_string &ip,
	         uint16 port,
	         bool mbbsupport);

	/**
	 * Remove a existing MIH User entry from the link book.
	 *
	 * @param id MIH User MIH Identifier.
	 */
	void del(mih::octet_string &id);

	/**
	 * Get all informations stored from a given MIH User.
	 *
	 * @param id MIH User MIH Identifier.
	 * @return All informations stored from a given MIH User.
	 */
	const user_entry& get(const mih::octet_string &id);

	/**
	 * Get the list of all known MIH Users.
	 *
	 * @return The list of all known MIH Users.
	 */
	const std::vector<mih::octet_string> get_ids();

	/**
	 * Get the MIH User for handover operations.
	 *
	 * @return The MIH User MIH Identifier for handover operations.
	 */
	const mih::octet_string handover_user();
private:

	std::map<mih::octet_string, user_entry> _ubook;
	boost::mutex _mutex;
};

} /* namespace mihf */ } /* namespace odtone */

#endif
