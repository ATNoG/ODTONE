//=============================================================================
// Brief   : Cast Utilities
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

#ifndef ODTONE_CAST__HPP_
#define ODTONE_CAST__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/exception.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/type_traits/is_integral.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone {

///////////////////////////////////////////////////////////////////////////////
struct bad_cast : virtual public exception {
};

struct bad_truncate_cast : virtual public bad_cast {
	bad_truncate_cast() : exception("odtone::truncate_cast: bad cast")
	{ }
};

///////////////////////////////////////////////////////////////////////////////
namespace detail {

///////////////////////////////////////////////////////////////////////////////
template<class T, class U, bool Check>
struct cast;

template<class T, class U>
struct cast<T, U, true> {
	static T truncate(U from)
	{
		if (U(T(from)) != from)
			boost::throw_exception(bad_truncate_cast());

		return T(from);
	}
};

template<class T, class U>
struct cast<T, U, false> {
	static T truncate(U from)
	{
		return T(from);
	}
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace detail */

///////////////////////////////////////////////////////////////////////////////
template<class T, class U>
inline T truncate_cast(U from)
{
	ODTONE_STATIC_ASSERT(boost::is_integral<T>::value
						 && boost::is_integral<U>::value, "T and U must be an integral type");

	typedef typename detail::cast<T,
								  U,
								  boost::mpl::less<boost::mpl::sizeof_<T>,
												   boost::mpl::sizeof_<U>
												  >::value
								 > impl;

	return impl::truncate(from);
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_BASE__HPP_ */
