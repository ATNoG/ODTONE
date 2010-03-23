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

#ifndef ODTONE_MIHF_ADDRESS_BOOK__HPP
#define ODTONE_MIHF_ADDRESS_BOOK__HPP

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/mih/message.hpp>
#include <odtone/mih/types/capabilities.hpp>

#include <boost/bind.hpp>
#include <map>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

struct address_entry
{
	mih::octet_string		ip;
	uint16				port;
	mih::transport_list_enum	trans; // send by UDP or TCP
};

class address_book
{
public:
	void add(const mih::octet_string &id, mih::octet_string &ip, uint16 port, mih::transport_list_enum t);
	void del(mih::octet_string &id);

	const address_entry& get(const mih::octet_string &id);
private:
	std::map<mih::octet_string, address_entry> _abook;
};

} /* namespace mihf */ } /* namespace odtone */

#endif
