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

#include "interface.hpp"
#include <odtone/debug.hpp>

///////////////////////////////////////////////////////////////////////////////
interface::interface(uint index, odtone::mih::link_type type, const std::string& name, const odtone::mih::link_addr& link_addr)
	: _index(index), _type(type), _up(boost::logic::indeterminate), _name(name),
	_link_addr(link_addr)
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

bool interface_map::remove(uint index)
{
	return (_map.erase(index, compare()));
}

interface& interface_map::find(uint index)
{
	map::iterator i = _map.find(index, compare());

	if (i != _map.end())
		return *i;

	return nullref;
}

const interface& interface_map::find(uint index) const
{
	map::const_iterator i = _map.find(index, compare());

	if (i != _map.end())
		return *i;

	return nullref;
}

// EOF ////////////////////////////////////////////////////////////////////////
