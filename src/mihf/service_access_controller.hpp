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

#ifndef ODTONE_MIHF_SERVICE_ACCESS_CONTROLLER_HPP
#define ODTONE_MIHF_SERVICE_ACCESS_CONTROLLER_HPP

///////////////////////////////////////////////////////////////////////////////
#include "service_management.hpp"
#include "event_service.hpp"
#include "command_service.hpp"
#include "information_service.hpp"

#include <odtone/base.hpp>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <map>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

typedef boost::function<bool (mih::message_ptr&, mih::message_ptr&)> handler_t;

class service_access_controller {
public:

	static service_access_controller *instance();
	~service_access_controller();

	bool process(mih::message_ptr& in, mih::message_ptr& out);
	void dispatch(mih::message_ptr& in);

private:
	service_access_controller();
	static service_access_controller *ptr_instance;

	service_management	_sm;
	event_service		_mies;
	command_service		_mics;
	information_service _miis;

	std::map<uint, handler_t> _callbacks;
};

#define sac service_access_controller::instance()

} /* namespace mihf */ } /* namespace odtone */

#endif
