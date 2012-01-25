//=============================================================================
// Brief   : Cast Utilities
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
/**
 * Bad cast exception.
 */
struct bad_cast : virtual public exception {
};

/**
 * Bad truncate cast exception.
 */
struct bad_truncate_cast : virtual public bad_cast {
	/**
	 * Construct a bad truncate cast exception.
	 */
	bad_truncate_cast() : exception("odtone::truncate_cast: bad cast")
	{ }
};

///////////////////////////////////////////////////////////////////////////////
namespace detail {

///////////////////////////////////////////////////////////////////////////////
/**
 * Cast operation, which can convert a class object into another class type.
 */
template<class T, class U, bool Check>
struct cast;

/**
 * Cast operation, which can convert a class object into another class type.
 * @note Check the convertion.
 */
template<class T, class U>
struct cast<T, U, true> {
	/**
	 * Truncate the cast operation.
	 *
	 * @param from The class object to convert to.
	 * @return The converted object.
	 */
	static T truncate(U from)
	{
		if (U(T(from)) != from)
			boost::throw_exception(bad_truncate_cast());

		return T(from);
	}
};

/**
 * Cast operation, which can convert a class object into another class type.
 * @note Does not check the convertion.
 */
template<class T, class U>
struct cast<T, U, false> {
	/**
	 * Truncate the cast operation.
	 *
	 * @param from The class object to convert to.
	 * @return The converted object.
	 */
	static T truncate(U from)
	{
		return T(from);
	}
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace detail */

///////////////////////////////////////////////////////////////////////////////
/**
 * Cast operation, which can convert a class object into another class type.
 * @note T and U must be an integral type.
 *
 * @param The class object to convert to.
 * @return The converted object.
 */
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
