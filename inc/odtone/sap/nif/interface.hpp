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
#include <odtone/mih/types/link.hpp>
#include <string>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace sap { namespace nif {

///////////////////////////////////////////////////////////////////////////////
class interface : boost::noncopyable {
	friend class interface_map;

public:
	interface(uint index, odtone::mih::link_type type, const std::string& name, const odtone::mih::link_addr& link_addr);
	virtual ~interface();

	uint                          index() const     { return _index; }
	odtone::mih::link_type        type() const      { return _type; }
	const boost::tribool&         up() const        { return _up; }
	const std::string&            name() const      { return _name; }
	const odtone::mih::link_addr& link_addr() const { return _link_addr; }

	boost::logic::tribool up(const boost::logic::tribool& tb);

private:
	boost::intrusive::set_member_hook<> _node;

	uint                   _index;
	odtone::mih::link_type _type;
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
			return a._index < b._index;
		}

		bool operator()(const interface& a, const uint index) const
		{
			return a._index < index;
		}

		bool operator()(const uint index, const interface& b) const
		{
			return index < b._index;
		}
	};
	typedef boost::intrusive::compare<compare> compare_option;

	typedef boost::intrusive::rbtree<interface, compare_option, hook_option> map;

public:
	interface_map();
	~interface_map();

	bool insert(interface& i);

	bool remove(interface& i);
	bool remove(uint index);

	interface&       find(uint index);
	const interface& find(uint index) const;

private:
	map _map;
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace nif */ } /* namespace sap */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_SAP_NIF_INTERFACE__HPP_ */
