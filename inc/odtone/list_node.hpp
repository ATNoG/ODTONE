//=============================================================================
// Brief   : Linked List Support
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

#ifndef ODTONE_LIST_NODE__HPP_
#define ODTONE_LIST_NODE__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone {

///////////////////////////////////////////////////////////////////////////////
/**
 * Double linked list, which provides operations to add or remove elements,
 * to get and swap elements and to reverse the elements order.
 * Each node contains, besides the next-node link, a second link field pointing
 * to the previous node in the sequence.
 */
class list_node {
public:
	/**
	 * Initialize the double linked list with a single element.
	 */
	void init() { _next = _prev = this; }

	/**
	 * Insert a new element in the first position of the double linked list.
	 *
	 * @param node The element to insert in the double linked list.
	 */
	void push_front(list_node* node)
	{
		_next->_prev = node;
		node->_prev = this;
		node->_next = _next;
		_next = node;
	}

	/**
	 * Insert a new element in the last position of the double linked list.
	 *
	 * @param node The element to insert in the double linked list.
	 */
	void push_back(list_node* node)
	{
		_prev->_next = node;
		node->_next = this;
		node->_prev = _prev;
		_prev = node;
	}

	/**
	 * Remove and return the first element of the double linked list.
	 *
	 * @return The first element of the double linked list.
	 */
	list_node* pop_front()
	{
		list_node* node = _next;
		node->remove();
		return node;
	}

	/**
	 * Remove and return the last element of the double linked list.
	 *
	 * @return The last element of the double linked list.
	 */
	list_node* pop_back()
	{
		list_node* node = _prev;
		node->remove();
		return node;
	}

	/**
	 * Return the first element of the double linked list without removing it.
	 *
	 * @return The first element of the double linked list.
	 */
	list_node* front()
	{
		return _next;
	}

	/**
	 * Return the last element of the double linked list without removing it.
	 *
	 * @return The last element of the double linked list.
	 */
	list_node* back()
	{
		return _prev;
	}

	/**
	 * Return the first element of the double linked list without removing it.
	 *
	 * @return The first element of the double linked list.
	 */
	const list_node* front() const
	{
		return _next;
	}

	/**
	 * Return the last element of the double linked list without removing it.
	 *
	 * @return The last element of the double linked list without removing it.
	 */
	const list_node* back() const
	{
		return _prev;
	}

	/**
	 * Swap the position of two elements of the double linked list.
	 *
	 * @param y The element with which will exchange the position.
	 */
	void swap(list_node& y)
	{
		list_node* n = _next;
		list_node* p = _prev;

		_next = y._next;
		_prev = y._prev;
		y._next = n;
		y._prev = p;
	}

	/**
	 * Reverse the element order in the double linked list. In other words,
	 * it exchange the previous element with the next element of the checkpoint
	 * that calls this method.
	 */
	void reverse()
	{
		list_node* n = _next;

		_next = _prev;
		_prev = n;
	}

	/**
	 * Remove an element from the double linked list.
	 */
	void remove()
	{
		_prev->_next = _next;
		_next->_prev = _prev;
	}

	/**
	 * Check if the element is the single one in the double linked list.
	 *
	 * @return True if the element is the single one in the double linked list
	 *         or false otherwise.
	 */
	bool empty() const
	{
		return (_next == this);
	}

private:
	list_node* _next;	/**< Pointer to the next element.		*/
	list_node* _prev;	/**< Pointer to the previous element.	*/
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_LIST_NODE__HPP_ */
