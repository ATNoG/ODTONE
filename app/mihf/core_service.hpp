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
#include <odtone/mihf/service.hpp>
#include <odtone/mihf/user.hpp>
#include <odtone/mihf/sap.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mihf {

////////////////////////////////////////////////////////////////////////////////
class core_service : public service {
public:
	core_service();
	~core_service();

	bool indication(message const& msg);
	bool indication(message const& msg, response resp);
	bool request(message const& msg, response resp);

	bool add(user_ptr u);
	bool add(sap_ptr s);
	bool remove(user_ptr u);
	bool remove(sap_ptr s);

private:
	std::vector<user_ptr> _users;
	std::vector<sap_ptr>  _saps;
};

////////////////////////////////////////////////////////////////////////////////
} /* namespace mihf */ } /* namespace odtone */

////////////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIHF_CORE__HPP_ */
