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
 * Struct to store MIHF information such as IP Address, listening port
 * and transport protocol.
 */
struct address_entry
{
	mih::octet_string	ip;		/**< IP address.					*/
	uint16				port;	/**< Listening port.				*/
	mih::transport_list	trans;	/**< Supported transport protocols.	*/
};

/**
 * This class is used to store the information about all known peer MIHFs.
 * It makes the correspondence between the MIHF MIH Identifier and the
 * informations stored in the address_entry struct.
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
	 * @param t MIHF supported transport protocols.
	 */
	void add(const mih::octet_string &id, mih::octet_string &ip, uint16 port, mih::transport_list t);

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
