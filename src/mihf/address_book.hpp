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

#ifndef ODTONE_MIHF_ADDRESS_BOOK__HPP
#define ODTONE_MIHF_ADDRESS_BOOK__HPP

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/mih/message.hpp>
#include <odtone/mih/types/capabilities.hpp>

#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <map>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

/**
 * Struct to store MIHF information like IP Address, listening port and transport
 * protocol.
 */
struct address_entry
{
	mih::octet_string		ip;
	uint16				port;
	mih::transport_list_enum	trans; // send by UDP or TCP
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
	 * @param ip MIHF IP Address.
	 * @param port MIHF listening port.
	 * @param t MIHF transport protocol.
	 */
	void add(const mih::octet_string &id, mih::octet_string &ip, uint16 port, mih::transport_list_enum t);

	/**
	 * Remove a existing MIHF entry from the address book
	 *
	 * @param id MIHF MIH Identifier.
	 */
	void del(mih::octet_string &id);

	/**
	 * Get the address_entry of a given MIHF presented in the address book.
	 *
	 * @param id MIHF MIH Identifier.
	 */
	const address_entry& get(const mih::octet_string &id);
private:
	std::map<mih::octet_string, address_entry> _abook;

	boost::mutex _mutex;
};

} /* namespace mihf */ } /* namespace odtone */

#endif
