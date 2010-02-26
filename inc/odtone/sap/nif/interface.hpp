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

#ifndef ODTONE_SAP_NIF_INTERFACE__HPP_
#define ODTONE_SAP_NIF_INTERFACE__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <boost/utility.hpp>
#include <boost/logic/tribool.hpp>
#include <boost/intrusive/rbtree.hpp>
#include <boost/type_traits/is_pod.hpp>
#include <odtone/mih/types/link.hpp>
#include <algorithm>
#include <string>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace sap { namespace nif {

///////////////////////////////////////////////////////////////////////////////
class if_id {
public:
	if_id();

	template<class T>
	explicit if_id(const T* guid);

	bool operator<(if_id const& lhs) const
	{
		return std::memcmp(_guid, lhs._guid, sizeof(_guid)) < 0;
	}

	bool operator<=(if_id const& lhs) const
	{
		return std::memcmp(_guid, lhs._guid, sizeof(_guid)) <= 0;
	}

	bool operator>(if_id const& lhs) const
	{
		return std::memcmp(_guid, lhs._guid, sizeof(_guid)) > 0;
	}

	bool operator>=(if_id const& lhs) const
	{
		return std::memcmp(_guid, lhs._guid, sizeof(_guid)) >= 0;
	}

	bool operator==(if_id const& lhs) const
	{
		return std::memcmp(_guid, lhs._guid, sizeof(_guid)) == 0;
	}

	bool operator!=(if_id const& lhs) const
	{
		return std::memcmp(_guid, lhs._guid, sizeof(_guid)) != 0;
	}

private:
	uint32 _guid[4];
};

inline if_id::if_id()
{
	std::fill(_guid, _guid + sizeof(_guid), 0);
}

template<class T>
inline if_id::if_id(T const* raw)
{
	ODTONE_STATIC_ASSERT(sizeof(T) == sizeof(_guid), "T must be the same size as if_id underlying type");
	ODTONE_STATIC_ASSERT(boost::is_pod<T>::value, "T must be a POD");
	uint32 const* guid = reinterpret_cast<uint32 const*>(raw);

	std::copy(guid, guid + ODTONE_COUNT_OF(_guid), _guid);
}

///////////////////////////////////////////////////////////////////////////////
class interface : boost::noncopyable {
	friend class interface_map;

public:
	interface(if_id const& id, odtone::mih::link_type type);
	virtual ~interface();

	if_id const&                  id() const        { return _id; }
	odtone::mih::link_type        type() const      { return _type; }
	const boost::tribool&         up() const        { return _up; }
	const std::string&            name() const      { return _name; }
	const odtone::mih::link_addr& link_addr() const { return _link_addr; }

	boost::logic::tribool up(const boost::logic::tribool& tb);

private:
	boost::intrusive::set_member_hook<> _node;
	odtone::mih::link_type              _type;

protected:
	if_id		           _id;
	boost::logic::tribool  _up;
	std::string            _name;
	odtone::mih::link_addr _link_addr;
};

///////////////////////////////////////////////////////////////////////////////
class interface_map {
	typedef boost::intrusive::member_hook<interface, boost::intrusive::set_member_hook<>, &interface::_node>
		hook_option;

	struct compare {
		bool operator()(const interface& a, const interface& b) const
		{
			return a._id < b._id;
		}

		bool operator()(const interface& a, if_id const& id) const
		{
			return a._id < id;
		}

		bool operator()(if_id const& id, const interface& b) const
		{
			return id < b._id;
		}
	};
	typedef boost::intrusive::compare<compare> compare_option;

	typedef boost::intrusive::rbtree<interface, compare_option, hook_option> map;

public:
	interface_map();
	~interface_map();

	bool insert(interface& i);

	bool remove(interface& i);
	bool remove(if_id const& id);

	interface&       find(if_id const& id);
	const interface& find(if_id const& id) const;

private:
	map _map;
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace nif */ } /* namespace sap */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_SAP_NIF_INTERFACE__HPP_ */
