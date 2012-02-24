//==============================================================================
// Brief   : Meta Message
// Authors : Simao Reis <sreis@av.it.pt>
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

#ifndef ODTONE_MIHF_META_MESSAGE__HPP
#define ODTONE_MIHF_META_MESSAGE__HPP

#include <odtone/mih/message.hpp>
#include <boost/shared_ptr.hpp>

namespace odtone { namespace mihf {

/**
 * A meta_message is a derived class from odtone::mih::message with added metadata.
 * The metadata indicates if the message was received on the loopback interface
 * and also the IP address and port of the sender of the message.
 */
class meta_message
	: public mih::message
{
public:
	/**
	 * Construct an empty meta message.
	 */
	meta_message();

	/**
	 * Construct a meta message.
	 *
	 * @param fm The message frame from where extract the message data.
	 */
	meta_message(const mih::frame &fm);

	/**
	 * Construct a meta message.
	 *
	 * @param ip The source IP address.
	 * @param scope The scope ID.
	 * @param port The source port.
	 * @param fm The message frame from where extract the message data.
	 */
	meta_message(mih::octet_string ip, uint16 scope,
	             uint16 port, const mih::frame &fm);

	/**
	 * Check if the message is from a local entity.
	 *
	 * @return true if the message is from a local entity or false otherwise.
	 */
	bool is_local();

	/**
	 * Get the IP address of the source of the message.
	 *
	 * @return The IP address if the source of the message.
	 */
	mih::octet_string& ip();

	/**
	 * Get the scope ID of the message.
	 *
	 * @return The scope ID of the message.
	 */
	uint16 scope();

	/**
	 * Get the port of the source of the message.
	 *
	 * @return The port of the source of the message.
	 */
	uint16 port();

	/**
	 * Set the IP address of the source of the message.
	 *
	 * @param ip The IP address of the source of the message.
	 */
	void ip(const mih::octet_string &ip);

	/**
	 * Set the scope IP of the message.
	 *
	 * @param scope The scope IP of the message.
	 */
	void scope(uint16 scope);

	/**
	 * Set the port of the source of the message.
	 *
	 * @param p The port of the source of the message.
	 */
	void port(uint16 p);

protected:
	bool _local;			/**< True if message was sent from a local entity.	*/
	mih::octet_string _ip;	/**< The IP address of the source of the message.	*/
	uint16 _scope;			/**< The scope ID.									*/
	uint16 _port;			/**< The port of the source of the message.			*/
};

} /* namespace mihf */ } /* namespace odtone */

typedef boost::shared_ptr<odtone::mihf::meta_message> meta_message_ptr;

#endif
