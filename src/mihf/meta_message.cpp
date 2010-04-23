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

#include "meta_message.hpp"

namespace odtone { namespace mihf {

meta_message::meta_message()
	: message()
{
}


meta_message::meta_message(const mih::frame &fm)
	: message(fm)
{
}

meta_message::meta_message(mih::octet_string ip, uint16 port, const mih::frame &fm)
	: mih::message(fm),
	  _ip(ip)
{
	_local = (_ip.compare("127.0.0.1") == 0);
	_port = port;
}

bool meta_message::is_local()
{
	return _local;
}

const mih::octet_string& meta_message::ip()
{
	return _ip;
}

uint16 meta_message::port()
{
	return _port;
}

void meta_message::ip(const mih::octet_string &ip)
{
	_ip.assign(ip);
}

void meta_message::port(uint16 port)
{
	_port = port;
}

} /* namespace mihf */ } /* namespace odtone */
