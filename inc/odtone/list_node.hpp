//=============================================================================
// Brief   : Linked List Support
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

#ifndef ODTONE_LIST_NODE__HPP_
#define ODTONE_LIST_NODE__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone {

///////////////////////////////////////////////////////////////////////////////
class list_node {
public:
	void init() { _next = _prev = this; }

	void push_front(list_node* node)
	{
		_next->_prev = node;
		node->_prev = this;
		node->_next = _next;
		_next = node;
	}

	void push_back(list_node* node)
	{
		_prev->_next = node;
		node->_next = this;
		node->_prev = _prev;
		_prev = node;
	}

	list_node* pop_front()
	{
		list_node* node = _next;
		node->remove();
		return node;
	}

	list_node* pop_back()
	{
		list_node* node = _prev;
		node->remove();
		return node;
	}

	list_node* front()	{ return _next; }
	list_node* back()	{ return _prev; }

	const list_node* front() const	{ return _next; }
	const list_node* back() const	{ return _prev; }

	void swap(list_node& y)
	{
		list_node* n = _next;
		list_node* p = _prev;

		_next = y._next;
		_prev = y._prev;
		y._next = n;
		y._prev = p;
	}

	void reverse()
	{
		list_node* n = _next;

		_next = _prev;
		_prev = n;
	}

	void remove()
	{
		_prev->_next = _next;
		_next->_prev = _prev;
	}

	bool empty() const { return (_next == this); }

private:
	list_node* _next;
	list_node* _prev;
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_LIST_NODE__HPP_ */
