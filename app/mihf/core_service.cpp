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

#include "core_service.hpp"
#include <boost/bind.hpp>
#include <boost/utility.hpp>
#include <algorithm>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mihf {

///////////////////////////////////////////////////////////////////////////////
core_service::core_service()
{
}

core_service::~core_service()
{
}

bool core_service::indication(message const& msg)
{
	typedef std::vector<user_ptr>::iterator iterator;

	for (iterator i = _users.begin(), e = _users.end(); i != e; ++i)
		if ((*i)->indication(msg))
			return true;

	return false;
}

bool core_service::indication(message const& msg, response resp)
{
	typedef std::vector<user_ptr>::iterator iterator;

	for (iterator i = _users.begin(), e = _users.end(); i != e; ++i)
		if ((*i)->indication(msg, resp))
			return true;

	return false;
}

bool core_service::request(message const& msg, response resp)
{
	typedef std::vector<sap_ptr>::iterator iterator;

	for (iterator i = _saps.begin(), e = _saps.end(); i != e; ++i)
		if ((*i)->request(msg, resp))
			return true;

	return false;
}

bool core_service::add(user_ptr u)
{
	if (std::find(_users.begin(), _users.end(), u) != _users.end())
		return false;

	_users.push_back(u);
	return true;
}

bool core_service::add(sap_ptr s)
{
	if (std::find(_saps.begin(), _saps.end(), s) != _saps.end())
		return false;

	_saps.push_back(s);
	return true;
}

bool core_service::remove(user_ptr u)
{
	typedef std::vector<user_ptr>::iterator iterator;

	iterator i = std::find(_users.begin(), _users.end(), u);
	if (i == _users.end())
		return false;

	_users.erase(i);
	return true;
}

bool core_service::remove(sap_ptr s)
{
	typedef std::vector<sap_ptr>::iterator iterator;

	iterator i = std::find(_saps.begin(), _saps.end(), s);
	if (i == _saps.end())
		return false;

	_saps.erase(i);
	return true;
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace mihf */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
