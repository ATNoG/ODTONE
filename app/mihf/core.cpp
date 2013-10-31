//=============================================================================
// Brief   : Core Service
// Authors : Bruno Santos <bsantos@av.it.pt>
// ----------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2012-2013 Universidade Aveiro
// Copyright (C) 2012-2013 Instituto de Telecomunicações - Pólo Aveiro
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//=============================================================================

#include "core.hpp"
#include <odtone/mihf/endpoint.hpp>

#include <algorithm>

#include <boost/utility.hpp>
#include <boost/variant/apply_visitor.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mihf {

///////////////////////////////////////////////////////////////////////////////
struct endpoint_visitor : boost::static_visitor<>
{
	endpoint_visitor(message& msg)
	: _msg(msg)
	{ }

	void operator()(none&) const
	{
	}

	void operator()(user_ptr& p) const
	{
		p->indication(_msg);
	}

	void operator()(sap_ptr& p) const
	{
		p->request(_msg);
	}

	void operator()(std::string& str) const
	{
		//TODO: not implemented
	}

	message& _msg;
};

///////////////////////////////////////////////////////////////////////////////
core::core(std::string id)
: _id(std::move(id))
{
}

core::~core()
{
}

void core::operator()(message& msg) const
{
	rule key(msg.service(), msg.opcode(), msg.action());
	service_map::const_iterator i = _services.lower_bound(key);
	service_map::const_iterator ie = _services.upper_bound(key);
	endpoints eps;

	while (i != ie)
	{
		if (!i->second->dispatch(msg, eps))
			return;
		++i;
	}

	for (endpoints::iterator i = eps.begin(), ie = eps.end(); i != ie; ++i)
		boost::apply_visitor(endpoint_visitor(msg), *i);
}

bool core::add(rule key, service& u)
{
	return _services.insert(std::make_pair(key, u.shared_from_this())).second;
}

bool core::remove(rule key)
{
	service_map::iterator i = _services.find(key);
	if (i == _services.end())
		return false;

	_services.erase(i);
	return true;
}

bool core::add(user& u)
{
	if (!_users.insert(u.shared_from_this()).second)
		return false;

	for (service_map::const_iterator i = _services.begin(), ie = _services.end(); i != ie; ++i)
		i->second->event_add_user(u);

	return true;
}

bool core::add(sap& s)
{
	if (!_saps.insert(s.shared_from_this()).second)
		return false;

	for (service_map::const_iterator i = _services.begin(), ie = _services.end(); i != ie; ++i)
		i->second->event_add_sap(s);

	return true;
}

bool core::remove(user& u)
{
	user_set::iterator i = _users.find(u.shared_from_this());
	if (i == _users.end())
		return false;

	for (service_map::const_iterator i = _services.begin(), ie = _services.end(); i != ie; ++i)
		i->second->event_remove_user(u);

	_users.erase(i);
	return true;
}

bool core::remove(sap& s)
{
	sap_set::iterator i = _saps.find(s.shared_from_this());
	if (i == _saps.end())
		return false;

	for (service_map::const_iterator i = _services.begin(), ie = _services.end(); i != ie; ++i)
		i->second->event_remove_sap(s);

	_saps.erase(i);
	return true;
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace mihf */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
