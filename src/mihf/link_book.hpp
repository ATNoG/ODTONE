//==============================================================================
// Brief   : Link Book
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
 * Struct to store Link SAP information like IP Address, listening port, transport
 * protocol and interface that Link SAP manages.
 */
struct link_entry
{
	mih::octet_string  ip;
	uint16             port;
	mih::link_id       link_id;
};

/**
 * This class is used to store information about all known Link SAPs. It makes
 * the correspondence between the Link SAP MIH Identifier and the informations
 * stored in the link_entry struct.
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
	 * Remove a existing Link SAP entry from the link book.
	 *
	 * @param id Link SAP MIH Identifier.
	 */
	void del(mih::octet_string &id);

	/**
	 * Get all informations stored from a given Link SAP.
	 *
	 * @param id Link SAP MIH Identifier.
	 * @return All informations stored from a given Link SAP.
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
	 * @return The Link SAP MIH Identifier.
	 */
	const mih::octet_string search_interface(mih::link_type lt, mih::link_addr la);
private:

	std::map<mih::octet_string, link_entry> _lbook;
	boost::mutex _mutex;
};

} /* namespace mihf */ } /* namespace odtone */

#endif
