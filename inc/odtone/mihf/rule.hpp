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

#ifndef ODTONE_MIHF_RULE__HPP_
#define ODTONE_MIHF_RULE__HPP_

////////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mihf {

////////////////////////////////////////////////////////////////////////////////
class service;
class message;

////////////////////////////////////////////////////////////////////////////////
class rule {
	friend class service_map;

public:
	rule(uchar service, uchar opcode, ushort action)
		: _service(service), _opcode(opcode), _action(action, action + 1)
	{ }

	rule(uchar service, uchar opcode, ushort action_begin, ushort action_end)
		: _service(service), _opcode(opcode), _action(action_begin, action_end)
	{ }

	friend bool operator<(rule const& a, rule const& b);

private:
	uchar _service;
	uchar _opcode;
	std::pair<ushort, ushort> _action;
};

inline bool operator<(rule const& a, rule const& b)
{
	if (a._service < b._service)
		return true;
	if (a._service > b._service)
		return false;

	if (a._opcode < b._opcode)
		return true;

	if (a._opcode > b._opcode)
		return false;

	if (a._action.first < b._action.first || a._action.second >= b._action.second)
		return false;

	return true;
}

////////////////////////////////////////////////////////////////////////////////
} /* namespace mihf */ } /* namespace odtone */

////////////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIHF_RULE__HPP_ */
