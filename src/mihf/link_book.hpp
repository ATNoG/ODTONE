//
// Copyright (c) 2007-2009 2009 Universidade Aveiro - Instituto de
// Telecomunicacoes Polo Aveiro
// This file is part of ODTONE - Open Dot Twenty One.
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//
// Author:     Carlos Guimarães <cguimaraes@av.it.pt>
//

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

struct link_entry
{
	mih::octet_string  ip;
	uint16             port;
	mih::link_id       link_id;
};

class link_book
{
public:

	/**
	 * Add a new Link SAP.
	 *
	 * @param id Link SAP MIHF ID
	 * @param ip Link SAP IP address
	 * @param port Link SAP listening port
	 * @param link_id interfaces that Link SAP manages
	 */
	void add(const mih::octet_string &id,
	         mih::octet_string &ip,
	         uint16 port,
	         mih::link_id link_id);

	/**
	 * Remove a known Link SAP.
	 *
	 * @param id Link SAP MIHF ID
	 */
	void del(mih::octet_string &id);

	/**
	 * Get all informations stored from a given Link SAP
	 *
	 * @param id Link SAP MIHF ID
	 * @return all informations stored from a given Link SAP
	 */
	const link_entry& get(const mih::octet_string &id);

	/**
	 * Get the list of all known Link SAPs
	 *
	 * @return the list of all known Link SAPs
	 */
	const std::vector<mih::octet_string> get_ids();

	/**
	 * Search for the link identifier of a given interface
	 *
	 * @return the link identifier
	 */
	const mih::octet_string search_interface(mih::link_type lt, mih::link_addr la);
private:

	std::map<mih::octet_string, link_entry> _lbook;
	boost::mutex _mutex;
};

} /* namespace mihf */ } /* namespace odtone */

#endif
