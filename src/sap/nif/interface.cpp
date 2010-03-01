//=============================================================================
// Brief   : Generic Network Interface
// Authors : Bruno Santos <bsantos@av.it.pt>
//
//
// Copyright (C) 2009 Universidade Aveiro - Instituto de Telecomunicacoes Polo Aveiro
//
// This file is part of ODTONE - Open Dot Twenty One.
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//=============================================================================

#include <odtone/debug.hpp>
#include <odtone/sap/nif/interface.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace sap { namespace nif {

///////////////////////////////////////////////////////////////////////////////
interface::interface(if_id const& id, odtone::mih::link_type type)
	: _id(id), _type(type)
{
}

interface::~interface()
{
}

boost::logic::tribool interface::up(const boost::logic::tribool& tb)
{
	boost::logic::tribool prev = _up;

	_up = tb;
	return prev;
}

void interface::name(const string& name)
{
	_name = name;
}

///////////////////////////////////////////////////////////////////////////////
interface_map::interface_map()
{
}

interface_map::~interface_map()
{
	ODTONE_ASSERT(_map.empty());
}

bool interface_map::insert(interface& i)
{
	return _map.insert_unique(i).second;
}

bool interface_map::remove(interface& i)
{
	return (_map.erase(i));
}

bool interface_map::remove(if_id const& id)
{
	return (_map.erase(id, compare()));
}

interface& interface_map::find(if_id const& id)
{
	map::iterator i = _map.find(id, compare());

	if (i != _map.end())
		return *i;

	return nullref;
}

const interface& interface_map::find(if_id const& id) const
{
	map::const_iterator i = _map.find(id, compare());

	if (i != _map.end())
		return *i;

	return nullref;
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace nif */ } /* namespace sap */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
