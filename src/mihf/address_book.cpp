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

///////////////////////////////////////////////////////////////////////////////
#include "address_book.hpp"
#include "log.hpp"
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

void address_book::add(const mih::octet_string &id,
		       mih::octet_string& ip,
		       uint16 port,
		       mih::transport_list_enum t)
{
	// TODO: add thread safety
	address_entry a;

	a.ip.assign(ip);
	a.port = port;
	a.trans = t;

	_abook[id] = a;
	log(4, "(address_book) added: ", id, " ", ip, " ", port);
}

void address_book::del(mih::octet_string &id)
{
	// TODO finish and add thread safety
}

const address_entry& address_book::get(const mih::octet_string &id)
{
	std::map<mih::octet_string, address_entry>::const_iterator it;
	it = _abook.find(id);

	if (it == _abook.end())
		throw ("no entry in address_book for this id");

	return it->second;
}


} /* namespace mihf */ } /* namespace odtone */
