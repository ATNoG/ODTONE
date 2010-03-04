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

#ifndef ODTONE_MIHF_TRANSMIT_HPP
#define ODTONE_MIHF_TRANSMIT_HPP

#include <set>
#include <boost/noncopyable.hpp>

#include <odtone/base.hpp>
#include <odtone/debug.hpp>
#include <odtone/mih/message.hpp>
#include <odtone/mihf/net_sap.hpp>
#include <odtone/mihf/comm_handler.hpp>


namespace odtone { namespace mihf {

struct registration_t
{
   mih::octet_string name;
   uint16 port;
   mih::octet_string ip;

   bool operator<(const registration_t &other) const
	  {
		  if (name == other.name) {
			  if (ip == other.ip)
			  {
				  return false;
			  }
			  else
			  {
				  return (port < other.port);
			  }
		  }

		  return (name < other.name);
	  }
};

class transmit_t
	: private boost::noncopyable
{
public:
   static transmit_t* instance();
   ~transmit_t();

   void operator()(mih::message_ptr& msg);
   void send(mih::message_ptr& msg);

   void add(mih::octet_string name, mih::octet_string ip, uint16 port);

   std::set<registration_t> _registrations;

protected:
   transmit_t();

   static transmit_t *ptr_instance;
};

#define transmit (*transmit_t::instance())

} /* namespace mihf */ } /* namespace odtone */

#endif
