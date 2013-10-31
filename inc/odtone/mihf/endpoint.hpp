//==============================================================================
// Brief   : MIHF Message Dispatch Rules
// Authors : Bruno Santos <bsantos@cppdev.net>
// -----------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2013 Universidade Aveiro
// Copyright (C) 2013 Instituto de Telecomunicações - Pólo Aveiro
// Copyright (C) 2013 Bruno Santos
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//==============================================================================

#ifndef ODTONE_MIHF_ENDPOINT__HPP_
#define ODTONE_MIHF_ENDPOINT__HPP_

////////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>

#include <string>
#include <vector>

#include <boost/variant/variant.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mihf {

////////////////////////////////////////////////////////////////////////////////
class user;
class sap;

typedef boost::shared_ptr<user> user_ptr;
typedef boost::shared_ptr<sap> sap_ptr;

struct none { };

typedef boost::variant<
	none,
	user_ptr,
	sap_ptr,
	std::string
> endpoint;

typedef std::vector<endpoint> endpoints;

////////////////////////////////////////////////////////////////////////////////
} /* namespace mihf */ } /* namespace odtone */

////////////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIHF_ENDPOINT__HPP_ */
