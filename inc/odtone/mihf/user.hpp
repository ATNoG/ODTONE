//==============================================================================
// Brief   : SAP
// Authors : Bruno Santos <bsantos@av.it.pt>
// -----------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2013 Universidade Aveiro
// Copyright (C) 2013 Instituto de Telecomunicações - Pólo Aveiro
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//==============================================================================

#ifndef ODTONE_MIHF_USER__HPP_
#define ODTONE_MIHF_USER__HPP_

////////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/mihf/service.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mihf {

////////////////////////////////////////////////////////////////////////////////
class service::user : boost::noncopyable {
protected:
	user(service& core)
		: core(core)
	{ }

public:
	virtual ~user()
	{ }

	virtual bool indication(message const& msg) = 0;
	virtual bool indication(message const& msg, response& resp) = 0;

public:
	service& core;
};

typedef boost::shared_ptr<service::user> user_ptr;

////////////////////////////////////////////////////////////////////////////////
} /* namespace mihf */ } /* namespace odtone */

////////////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIHF_USER__HPP_ */
