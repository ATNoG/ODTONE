//==============================================================================
// Brief   : Meta Message
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

#ifndef ODTONE_MIHF_META_MESSAGE__HPP
#define ODTONE_MIHF_META_MESSAGE__HPP

#include <odtone/mih/message.hpp>
#include <boost/shared_ptr.hpp>

namespace odtone { namespace mihf {

/**
 * A meta_message is a derived class from odtone::mih::message with added metadata.
 * The metadata indicates if the message was received on the loopback interface
 * and also the IP address and port of the sender of the message. It's useful
 * mostly due to broadcast messages.
 */
class meta_message
	: public mih::message
{
public:
	/**
	 * Meta-message constructor.
	 */
	meta_message();

	/**
	 * Meta-message constructor.
	 *
	 * @param fm message frame.
	 */
	meta_message(const mih::frame &fm);

	/**
	 * Meta-message constructor.
	 *
	 * @param ip source IP Address.
	 * @param port source port.
	 * @param fm message frame.
	 */
	meta_message(mih::octet_string ip, uint16 port, const mih::frame &fm);

	/**
	 * Check if the message in from a local entity.
	 *
	 * @return true if the message is from a local entity or false otherwise.
	 */
	bool is_local();

	/**
	 * Get the source IP Address of the message.
	 *
	 * @return The source IP Address.
	 */
	const mih::octet_string& ip();

	/**
	 * Get the source port of the message.
	 *
	 * @return The source port.
	 */
	uint16 port();

	/**
	 * Set the source IP Address of the message.
	 *
	 * @param ip source IP Address.
	 */
	void ip(const mih::octet_string &ip);

	/**
	 * Set the source port of the message.
	 *
	 * @param p source port.
	 */
	void port(uint16 p);

protected:
	// true if message was sent from a local user/link sap
	bool			_local;
	// ip and port of who sent the message
	mih::octet_string	_ip;
	uint16			_port;
};

} /* namespace mihf */ } /* namespace odtone */

typedef boost::shared_ptr<odtone::mihf::meta_message> meta_message_ptr;

#endif


