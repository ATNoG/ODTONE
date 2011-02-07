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

struct user_entry
{
	mih::octet_string        ip;
	uint16                   port;
};

class user_book
{
public:

	/**
	 * Add a new MIH User.
	 *
	 * @param id MIH User MIHF ID
	 * @param ip MIH User IP address
	 * @param port MIH User listening port
	 */
	void add(const mih::octet_string &id,
	         mih::octet_string &ip,
	         uint16 port);

	/**
	 * Remove a known MIH User.
	 *
	 * @param id MIH User MIHF ID
	 */
	void del(mih::octet_string &id);

	/**
	 * Get all informations stored from a given MIH User
	 *
	 * @param id MIH User MIHF ID
	 * @return all informations stored from a given MIH User
	 */
	const user_entry& get(const mih::octet_string &id);

	/**
	 * Get the list of all known MIH Users
	 *
	 * @return the list of all known MIH Users
	 */
	const std::vector<mih::octet_string> get_ids();
private:

	std::map<mih::octet_string, user_entry> _ubook;
	boost::mutex _mutex;
};

} /* namespace mihf */ } /* namespace odtone */

#endif
