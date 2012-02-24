//=============================================================================
// Brief   : DNS Types
// Authors : Carlos Guimaraes <cguimaraes@av.it.pt>
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

#ifndef ODTONE_MIH_TYPES_DNS__HPP_
#define ODTONE_MIH_TYPES_DNS__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <string>
#include <boost/asio.hpp>

#include <odtone/base.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace dns {

///////////////////////////////////////////////////////////////////////////////
struct question {
	question(std::string domain, uint16 qtype, uint16 qclass)
	{
		_domain	= domain;
		_type 	= qtype;
		_class	= qclass;
	}

	std::string	_domain;
	uint16 		_type;
	uint16		_class;
};

struct resource_record {
	resource_record(std::string qname, uint16 qtype, uint16 qclass, uint32 ttl, uint16 rr_len, std::vector<uint8> rr_data)
	{
		_name	= qname;
		_type	= qtype;
		_class	= qclass;
		_ttl	= ttl;
		_rr_len	= rr_len;
		_rr_data = rr_data;
	}

	std::string			_name;
	uint16 				_type;
	uint16 				_class;
	uint32 				_ttl;
	uint16				_rr_len;
	std::vector<uint8>	_rr_data;
};

struct a_record {
	a_record(std::string ipv4)
	{
		_ipv4 = ipv4;
	}

	std::string	_ipv4;
};

struct aaaa_record {
	aaaa_record(std::string ipv6)
	{
		_ipv6 = ipv6;
	}

	std::string	_ipv6;
};

struct naptr_record {
	naptr_record(uint16 order, uint16 preference, std::string flags, std::string service, std::string regex, std::string replacement)
	{
		_order = order;
		_preference = preference;
		_flags = flags;
		_service = _service;
		_regex = regex;
		_replacement = replacement;
	}

	uint16 		_order;
	uint16		_preference;
	std::string _flags;
	std::string _service;
	std::string _regex;
	std::string _replacement;
};

struct srv_record {
	srv_record(uint16 priority, uint16 weight, uint16 port, std::string target)
	{
		_priority = priority;
		_weight = weight;
		_port = port;
		_target = target;
	}

	uint16 		_priority;
	uint16		_weight;
	uint16 		_port;
	std::string _target;
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace dns */ } /*namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_TYPES_DNS__HPP_ */
