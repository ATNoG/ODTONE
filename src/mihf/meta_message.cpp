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

#include "meta_message.hpp"

namespace odtone { namespace mihf {

/**
 * Meta-message constructor.
 */
meta_message::meta_message()
	: message()
{
}

/**
 * Meta-message constructor.
 *
 * @param fm message frame.
 */
meta_message::meta_message(const mih::frame &fm)
	: message(fm)
{
}

/**
 * Meta-message constructor.
 *
 * @param ip source IP Address.
 * @param port source port.
 * @param fm message frame.
 */
meta_message::meta_message(mih::octet_string ip, uint16 port, const mih::frame &fm)
	: mih::message(fm),
	  _ip(ip)
{
	_local = (_ip.compare("127.0.0.1") == 0 || _ip.compare("::1") == 0);
	_port = port;
}

/**
 * Check if the message in from a local entity.
 *
 * @return true if the message is from a local entity or false otherwise.
 */
bool meta_message::is_local()
{
	return _local;
}

/**
 * Get the source IP Address of the message.
 *
 * @return The source IP Address.
 */
const mih::octet_string& meta_message::ip()
{
	return _ip;
}

/**
 * Get the source port of the message.
 *
 * @return The source port.
 */
uint16 meta_message::port()
{
	return _port;
}

/**
 * Set the source IP Address of the message.
 *
 * @param ip source IP Address.
 */
void meta_message::ip(const mih::octet_string &ip)
{
	_ip.assign(ip);
}

/**
 * Set the source port of the message.
 *
 * @param p source port.
 */
void meta_message::port(uint16 port)
{
	_port = port;
}

} /* namespace mihf */ } /* namespace odtone */
