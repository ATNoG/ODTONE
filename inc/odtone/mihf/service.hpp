//==============================================================================
// Brief   : Core Service
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

#ifndef ODTONE_MIHF_SERVICE__HPP_
#define ODTONE_MIHF_SERVICE__HPP_

////////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/mihf/message.hpp>
#include <odtone/mihf/endpoint.hpp>
#include <boost/utility.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/optional.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mihf {

////////////////////////////////////////////////////////////////////////////////
class sap;
class user;

////////////////////////////////////////////////////////////////////////////////
class service : boost::noncopyable, public boost::enable_shared_from_this<service> {
	typedef boost::shared_ptr<user> user_ptr;
	typedef boost::shared_ptr<sap>  sap_ptr;

public:
	virtual ~service()
	{ }

	virtual bool dispatch(message& msg, endpoints& eps) = 0;

	//events
	virtual void event_add_user(user& u);
	virtual void event_add_sap(sap& u);
	virtual void event_remove_user(user& u);
	virtual void event_remove_sap(sap& u);
};

typedef boost::shared_ptr<service> service_ptr;

////////////////////////////////////////////////////////////////////////////////
} /* namespace mihf */ } /* namespace odtone */

////////////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIHF_SERVICE__HPP_ */
