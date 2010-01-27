//=============================================================================
// Brief   : Bind RValues
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

#ifndef ODTONE_BINDRV__HPP_
#define ODTONE_BINDRV__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <boost/move/move.hpp>
#include <boost/utility/enable_if.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone {

///////////////////////////////////////////////////////////////////////////////
template<class T>
class bindrv_t : public T {
	ODTONE_STATIC_ASSERT(boost::is_movable<T>::value, "T must be movable");

public:
	bindrv_t(const bindrv_t& r) : T(boost::forward<boost::rv<T> >(r))
	{ }

	bindrv_t& operator=(const bindrv_t& r)
	{
		static_cast<T&>(*this) = boost::forward<boost::rv<T> >(r);

		return *this;
	}
};

template<class T>
inline typename boost::enable_if<boost::is_movable<T>, bindrv_t<T>&>::type bindrv(T& r)
{
	return static_cast<bindrv_t<T>&>(r);
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_BINDRV__HPP_ */
