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

#include <odtone/mihf/transmit.hpp>
#include <odtone/mihf/log.hpp>

namespace odtone { namespace mihf {

transmit_t *transmit_t::ptr_instance = NULL;

transmit_t::transmit_t()
{
}

transmit_t *transmit_t::instance()
{
	if (ptr_instance == NULL)
        ptr_instance = new transmit_t();

	return ptr_instance;
}

transmit_t::~transmit_t()
{
	if(ptr_instance)
        delete ptr_instance;
}

void transmit_t::operator()(mih::message_ptr& msg)
{
	std::set<registration_t>::iterator r;

	for(r = _registrations.begin(); r != _registrations.end(); r++)
		{
			if(msg->destination().to_string().compare(r->name) == 0)
				{
					log(1, "(transmit) sending message to: ", r->name, " at ", r->ip, ":", r->port);
					if ((r->ip.length() == 0) || (r->ip.compare( "127.0.0.1") == 0))
						{
							comhand->send_to(msg, "127.0.0.1", r->port);
						}
					else
						{
							netsap->send_to(msg, r->ip.c_str(), r->port);
						}
					return;
				}
		}
}

void transmit_t::add(mih::octet_string name, mih::octet_string ip, uint16 port)
{
	registration_t r;

	r.name.assign(name);
	r.ip.assign(ip);
	r.port = port;

	std::pair< std::set<registration_t>::iterator, bool > pr;
	pr = _registrations.insert(r);

	if (!pr.second)
		log(1, "(transmit) error inserting pair: ", name, " ", ip, " ", port);

}


} /* namespace mihf */ } /* namespace odtone */
