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

#ifndef LINK_SAP_INTERFACE_GENERIC__HPP_
#define LINK_SAP_INTERFACE_GENERIC__HPP_

///////////////////////////////////////////////////////////////////////////////
#include "../base.hpp"
#include <odtone/string.hpp>
#include <boost/utility.hpp>
#include <boost/array.hpp>
#include <boost/logic/tribool.hpp>
#include <boost/intrusive/rbtree.hpp>
#include <boost/type_traits/is_pod.hpp>
#include <boost/mpl/equal.hpp>
#include <odtone/mih/types/link.hpp>
#include <algorithm>
#include <cstring>

///////////////////////////////////////////////////////////////////////////////
namespace link_sap { namespace nic {

///////////////////////////////////////////////////////////////////////////////
/**
 * This class identifier the interface.
 */
class if_id {

#ifdef _WIN32
	typedef boost::array<uint32, 4> value_type;
#else
	typedef int                     value_type;
#endif

public:
	/**
	 * Construct an empty interface identifier.
	 */
	if_id()
		: _id()
	{ }

	/**
	 * Construct an interface identifier.
	 *
	 * @param id The interface identifier value.
	 */
	explicit if_id(const value_type& id)
		: _id(id)
	{ }

	/**
	 * Construct an interface identifier.
	 *
	 * @param pod The interface identifier value.
	 */
	template<class T>
	explicit if_id(const T* pod)
	{
		ODTONE_STATIC_ASSERT(sizeof(T) == sizeof(value_type), "T must be the same size as if_id underlying type");
		ODTONE_STATIC_ASSERT(boost::is_pod<T>::value, "T must be a POD");
		_id = reinterpret_cast<const value_type&>(*pod);
	}

	/**
	 * Check if the interface identifier is less than another interface
	 * identifier.
	 *
	 * @param lhs The interface identifier to compare to.
	 * @return True if it is less or false otherwise.
	 */
	bool operator<(if_id const& lhs) const
	{
		return (_id < lhs._id);
	}

	/**
	 * Check if the interface identifier is equal to or less than another interface
	 * identifier.
	 *
	 * @param lhs The interface identifier to compare to.
	 * @return True if it is equal or less or false otherwise.
	 */
	bool operator<=(if_id const& lhs) const
	{
		return (_id <= lhs._id);
	}

	/**
	 * Check if the interface identifier is higher than another interface
	 * identifier.
	 *
	 * @param lhs The interface identifier to compare to.
	 * @return True if it is higher or false otherwise.
	 */
	bool operator>(if_id const& lhs) const
	{
		return (_id > lhs._id);
	}

	/**
	 * Check if the interface identifier is equal to or higher than another interface
	 * identifier.
	 *
	 * @param lhs The interface identifier to compare to.
	 * @return True if it is equal or higher or false otherwise.
	 */
	bool operator>=(if_id const& lhs) const
	{
		return (_id >= lhs._id);
	}

	/**
	 * Check if the interface identifier is equal to another interface
	 * identifier.
	 *
	 * @param lhs The interface identifier to compare to.
	 * @return True if they are equal or false otherwise.
	 */
	bool operator==(if_id const& lhs) const
	{
		return (_id == lhs._id);
	}

	/**
	 * Check if the interface identifier is different from another
	 * interface identifier.
	 *
	 * @param lhs The interface identifier to compare to.
	 * @return True if they are different or false otherwise.
	 */
	bool operator!=(if_id const& lhs) const
	{
		return (_id != lhs._id);
	}

private:
	value_type _id;
};

///////////////////////////////////////////////////////////////////////////////
/**
 * This class stores information about a generic interface.
 */
class interface : boost::noncopyable {
	friend class interface_map;

public:
	/**
	 * Construct a generic interface.
	 *
	 * @param id Generic interface identifier.
	 * @param type The interface technology type. 
	 */
	interface(if_id const& id, odtone::mih::link_type type);

	/**
	 * Destruct a generic interface.
	 */
	virtual ~interface();

	/**
	 * Get the generic interface identifier.
	 *
	 * @return The generic interface identifier.
	 */
	if_id const& id() const
	{
		return _id;
	}
	
	/**
	 * Get the generic interface technology type.
	 *
	 * @return The generic interface technology type.
	 */
	odtone::mih::link_type type() const
	{
		return _type;
	}

	/**
	 * Get the state of the generic interface.
	 *
	 * @return The state of the generic interface.
	 */
	const boost::tribool& up() const
	{
		return _up;
	}
	
	/**
	 * Get the name of the generic interface.
	 *
	 * @return The name of the generic interface.
	 */
	const odtone::string& name() const
	{
		return _name;
	}
	
	/**
	 * Get the address of the generic interface.
	 *
	 * @return The address of the generic interface.
	 */
	const odtone::mih::link_addr& link_addr() const
	{
		return _link_addr;
	}

	/**
	 * Set the state of the generic interface.
	 *
	 * @param tb The state of the generic interface.
	 * @return The resulting state of the generic interface.
	 */
	boost::logic::tribool up(const boost::logic::tribool& tb);

	/**
	 * Set the name of the generic interface.
	 *
	 * @param name The name of the generic interface.
	 */
	void name(const odtone::string& name);

	/**
	 * Set the address of the generic interface.
	 *
	 * @param tb The address of the generic interface.
	 */
	void link_addr(const odtone::mih::link_addr& link_addr);

private:
	boost::intrusive::set_member_hook<> _node;	/**< Interface node hook.		*/
	odtone::mih::link_type              _type;	/**< Interface technology type.	*/

protected:
	if_id		           _id;			/**< Interface identifier.	*/
	boost::logic::tribool  _up;			/**< Interface state.		*/
	odtone::string         _name;		/**< Interface name.		*/
	odtone::mih::link_addr _link_addr;	/**< Interface address.		*/
};

///////////////////////////////////////////////////////////////////////////////
/**
 * This class represents an interface map. It is a kind of associative
 * container that stores elements formed by the combination of a key
 * value (interface identifier) and a mapped value (interface state).
 */
class interface_map {
	typedef boost::intrusive::member_hook<interface, boost::intrusive::set_member_hook<>, &interface::_node>
		hook_option;

	/**
	 * Compares two interfaces.
	 */
	struct compare {
		/**
		 * Compares two interfaces.
		 *
		 * @param a The first interface.
		 * @param b The second interface.
		 * @return True if the identifier of a is lower that the identifier of b.
		 */
		bool operator()(const interface& a, const interface& b) const
		{
			return a._id < b._id;
		}

		/**
		 * Compares two interfaces.
		 *
		 * @param a The first interface.
		 * @param b The second interface.
		 * @return True if the identifier of a is lower that the identifier of b.
		 */
		bool operator()(const interface& a, if_id const& id) const
		{
			return a._id < id;
		}

		/**
		 * Compares two interfaces.
		 *
		 * @param a The first interface.
		 * @param b The second interface.
		 * @return True if the identifier of a is lower that the identifier of b.
		 */
		bool operator()(if_id const& id, const interface& b) const
		{
			return id < b._id;
		}
	};
	typedef boost::intrusive::compare<compare> compare_option;

	typedef boost::intrusive::rbtree<interface, compare_option, hook_option> map;

public:
	typedef map::iterator       iterator;
	typedef map::const_iterator const_iterator;

	/**
	 * Construct an empty interface map.
	 */
	interface_map();

	/**
	 * Destruct an empty interface map.
	 */
	~interface_map();

	/**
	 * Insert a new interface in the container.
	 *
	 * @param i The interface to insert in the container.
	 * @return The inserted record.
	 */
	std::pair<iterator, bool> insert(interface& i);

	/**
	 * Delete an interface from the container.
	 *
	 * @param i Iterator pointing to a single element to be removed.
	 */
	void erase(const_iterator i);

	/**
	 * Delete an interface from the container.
	 *
	 * @param id The interface identifier to be removed.
	 */
	void erase(if_id const& id);

	/**
	 * Searchs for an interface.
	 *
	 * @param id The interface identifier to be searched for.
	 * @return An iterator to the element, if the specified key value
	 * is found, or map::end if the specified key is not found in the
	 * container.
	 */
	iterator find(if_id const& id);

	/**
	 * Searchs for an interface.
	 *
	 * @param id The interface identifier to be searched for.
	 * @return An iterator to the element, if the specified key value
	 * is found, or map::end if the specified key is not found in the
	 * container.
	 */
	const_iterator find(if_id const& id) const;

	/**
	 * Returns an iterator referring to the first element in the map
	 * container.
	 *
	 * @return An iterator to the first element in the container.
	 */
	iterator begin();

	/**
	 * Returns an iterator referring to the past-the-end element in
	 * the map container.
	 *
	 * @return An iterator to the element past the end of the container.
	 */
	iterator end();

	/**
	 * Returns an iterator referring to the first element in the map
	 * container.
	 *
	 * @return An iterator to the first element in the container.
	 */
	const_iterator begin() const;

	/**
	 * Returns an iterator referring to the past-the-end element in
	 * the map container.
	 *
	 * @return An iterator to the element past the end of the container.
	 */
	const_iterator end() const;

private:
	map _map;	/**< The interface map.	*/
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace nic */ } /* namespace link_sap */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* LINK_SAP_INTERFACE_GENERIC__HPP_ */
