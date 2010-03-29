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
// Author:     Simao Reis <sreis@av.it.pt>
//

#ifndef ODTONE_MIHF_META_MESSAGE__HPP
#define ODTONE_MIHF_META_MESSAGE__HPP

#include <odtone/mih/message.hpp>
#include <boost/shared_ptr.hpp>

namespace odtone { namespace mihf {

class meta_message
	: public mih::message
{
public:
	meta_message();
	meta_message(const mih::frame &fm);
	meta_message(mih::octet_string ip, uint16 port, const mih::frame &fm);

	bool is_local();
	const mih::octet_string& from_ip();
	uint16 from_port();

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


