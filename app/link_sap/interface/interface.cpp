//==============================================================================
// Brief   : Generic Network Interface
// Authors : Bruno Santos <bsantos@av.it.pt>
//------------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2009-2012 Universidade Aveiro
// Copyright (C) 2009-2012 Instituto de Telecomunicações - Pólo Aveiro
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//==============================================================================

#include <odtone/debug.hpp>
#include "interface.hpp"

///////////////////////////////////////////////////////////////////////////////
namespace link_sap { namespace nic {

///////////////////////////////////////////////////////////////////////////////
namespace detail {

///////////////////////////////////////////////////////////////////////////////
/**
 * Disposes an interface.
 *
 * @param p The interface to dispose.
 */
static void interface_disposer(interface* p)
{
	delete p;
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace detail */

///////////////////////////////////////////////////////////////////////////////
/**
 * Construct a generic interface.
 *
 * @param id Generic interface identifier.
 * @param type The interface technology type. 
 */
interface::interface(if_id const& id, odtone::mih::link_type type)
	: _type(type), _id(id)
{
}

/**
 * Destruct a generic interface.
 */
interface::~interface()
{
}

/**
 * Set the state of the generic interface.
 *
 * @param tb The state of the generic interface.
 * @return The resulting state of the generic interface.
 */
boost::logic::tribool interface::up(const boost::logic::tribool& tb)
{
	boost::logic::tribool prev = _up;

	_up = tb;
	return prev;
}

/**
 * Set the name of the generic interface.
 *
 * @param name The name of the generic interface.
 */
void interface::name(const odtone::string& name)
{
	_name = name;
}

/**
 * Set the address of the generic interface.
 *
 * @param tb The address of the generic interface.
 */
void interface::link_addr(const odtone::mih::link_addr& link_addr)
{
	_link_addr = link_addr;
}

///////////////////////////////////////////////////////////////////////////////
/**
 * Construct an empty interface map.
 */
interface_map::interface_map()
{
}

/**
 * Destruct an empty interface map.
 */
interface_map::~interface_map()
{
	ODTONE_ASSERT(_map.empty());
}

/**
 * Insert a new interface in the container.
 *
 * @param i The interface to insert in the container.
 * @return The inserted record.
 */
std::pair<interface_map::iterator, bool> interface_map::insert(interface& i)
{
	return _map.insert_unique(i);
}

/**
 * Delete an interface from the container.
 *
 * @param i Iterator pointing to a single element to be removed.
 */
void interface_map::erase(const_iterator i)
{
	_map.erase_and_dispose(i, detail::interface_disposer);
}

/**
 * Delete an interface from the container.
 *
 * @param id The interface identifier to be removed.
 */
void interface_map::erase(if_id const& id)
{
	_map.erase_and_dispose(id, compare(), detail::interface_disposer);
}

/**
 * Searchs for an interface.
 *
 * @param id The interface identifier to be searched for.
 * @return An iterator to the element, if the specified key value
 * is found, or map::end if the specified key is not found in the
 * container.
 */
interface_map::iterator interface_map::find(if_id const& id)
{
	return _map.find(id, compare());
}

/**
 * Searchs for an interface.
 *
 * @param id The interface identifier to be searched for.
 * @return An iterator to the element, if the specified key value
 * is found, or map::end if the specified key is not found in the
 * container.
 */
interface_map::const_iterator interface_map::find(if_id const& id) const
{
	return _map.find(id, compare());
}

/**
 * Returns an iterator referring to the first element in the map
 * container.
 *
 * @return An iterator to the first element in the container.
 */
interface_map::iterator interface_map::begin()
{
	return _map.begin();
}

/**
 * Returns an iterator referring to the past-the-end element in
 * the map container.
 *
 * @return An iterator to the element past the end of the container.
 */
interface_map::iterator interface_map::end()
{
	return _map.end();
}

/**
 * Returns an iterator referring to the first element in the map
 * container.
 *
 * @return An iterator to the first element in the container.
 */
interface_map::const_iterator interface_map::begin() const
{
	return _map.begin();
}

/**
 * Returns an iterator referring to the past-the-end element in
 * the map container.
 *
 * @return An iterator to the element past the end of the container.
 */
interface_map::const_iterator interface_map::end() const
{
	return _map.end();
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace nic */ } /* namespace link_sap */

// EOF ////////////////////////////////////////////////////////////////////////
