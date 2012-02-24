//=============================================================================
// Brief   : Object Warping for Binding with Move Semantics
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

#ifndef ODTONE_BIND_RV__HPP_
#define ODTONE_BIND_RV__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_convertible.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone {

///////////////////////////////////////////////////////////////////////////////
template<class T>
struct bind_rv_ : T {
	bind_rv_(const bind_rv_& rv)
		: T(static_cast<T&&>(const_cast<bind_rv_&>(rv)))
	{
	}

	operator T&&() { return *this; }

private:
	bind_rv_& operator=(const bind_rv_&)/* = delete*/;
};

template<class T>
bind_rv_<T>& bind_rv(T& rv)
{
	return static_cast<bind_rv_<T>&>(rv);
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_BIND_RV__HPP_ */
