//=============================================================================
// Brief   : Move Emulation
// Authors : Bruno Santos <bsantos@av.it.pt>
//------------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2009-2011 Universidade Aveiro
// Copyright (C) 2009-2011 Instituto de Telecomunicações - Pólo Aveiro
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//==============================================================================

#ifndef ODTONE_MOVE__HPP_
#define ODTONE_MOVE__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_convertible.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone {

///////////////////////////////////////////////////////////////////////////////
template<class T>
struct move_ : public T {
	typedef move_<T> self_type;

	move_(const self_type& r)
		: T(const_cast<self_type&>(r))
	{ }
};

template<class T>
inline typename boost::enable_if<boost::is_convertible<move_<T>, T>, move_<T>&>::type move(T& from)
{
	return static_cast<move_<T>&>(from);
}

///////////////////////////////////////////////////////////////////////////////
#define ODTONE_MOVABLE_BUT_NOT_COPYABLE(TYPE)             \
	private:                                              \
	TYPE(TYPE &);                                         \
	TYPE& operator=(TYPE &);                              \
	public:                                               \
	operator odtone::move_<TYPE>&()                      \
	{ return static_cast<odtone::move_<TYPE>&>(*this); } \
	private:

///////////////////////////////////////////////////////////////////////////////
} /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MOVE__HPP_ */
