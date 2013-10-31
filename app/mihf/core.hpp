//==============================================================================
// Brief   : Core Service
// Authors : Bruno Santos <bsantos@av.it.pt>
// -----------------------------------------------------------------------------
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
//==============================================================================

#ifndef ODTONE_MIHF_CORE__HPP_
#define ODTONE_MIHF_CORE__HPP_

////////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/mihf/rule.hpp>
#include <odtone/mihf/service.hpp>
#include <odtone/mihf/user.hpp>
#include <odtone/mihf/sap.hpp>

#include <map>
#include <set>

////////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mihf {

////////////////////////////////////////////////////////////////////////////////
class core : boost::noncopyable {
	typedef std::map<rule, service_ptr> service_map;
	typedef std::set<user_ptr> user_set;
	typedef std::set<sap_ptr> sap_set;

public:
	core(std::string id);
	~core();

	void operator()(message& msg) const;

	bool add(rule key, service& u);
	bool remove(rule key);

	bool add(user& u);
	bool add(sap& s);
	bool remove(user& u);
	bool remove(sap& s);

private:
	std::string _id;
	service_map _services;
	user_set    _users;
	sap_set     _saps;
};

////////////////////////////////////////////////////////////////////////////////
} /* namespace mihf */ } /* namespace odtone */

////////////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIHF_CORE__HPP_ */
