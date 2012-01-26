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

#include "meta_message.hpp"

namespace odtone { namespace mihf {

/**
 * Construct an empty meta message.
 */
meta_message::meta_message()
	: message()
{
	_scope = 0;
}

/**
 * Construct a meta message.
 *
 * @param fm The message frame from where extract the message data.
 */
meta_message::meta_message(const mih::frame &fm)
	: message(fm)
{
	_scope = 0;
}

/**
 * Construct a meta message.
 *
 * @param ip The source IP address.
 * @param scope The scope ID.
 * @param port The source port.
 * @param fm The message frame from where extract the message data.
 */
meta_message::meta_message(mih::octet_string ip,
                           uint16 scope,
                           uint16 port,
                           const mih::frame &fm)
	: mih::message(fm),
	  _ip(ip)
{
	_local = (_ip.compare("127.0.0.1") == 0 || _ip.compare("::1") == 0);
	_scope = scope;
	_port = port;
}

/**
 * Check if the message is from a local entity.
 *
 * @return true if the message is from a local entity or false otherwise.
 */
bool meta_message::is_local()
{
	return _local;
}

/**
 * Get the IP address of the source of the message.
 *
 * @return The IP address if the source of the message.
 */
mih::octet_string& meta_message::ip()
{
	return _ip;
}

/**
 * Get the scope ID of the message.
 *
 * @return The scope ID of the message.
 */
uint16 meta_message::scope()
{
	return _scope;
}

/**
 * Get the port of the source of the message.
 *
 * @return The port of the source of the message.
 */
uint16 meta_message::port()
{
	return _port;
}

/**
 * Set the IP address of the source of the message.
 *
 * @param ip The IP address of the source of the message.
 */
void meta_message::ip(const mih::octet_string &ip)
{
	_ip.assign(ip);
}

/**
 * Set the scope IP of the message.
 *
 * @param scope The scope IP of the message.
 */
void meta_message::scope(uint16 scope)
{
	_scope = scope;
}

/**
 * Set the port of the source of the message.
 *
 * @param p The port of the source of the message.
 */
void meta_message::port(uint16 port)
{
	_port = port;
}

} /* namespace mihf */ } /* namespace odtone */
