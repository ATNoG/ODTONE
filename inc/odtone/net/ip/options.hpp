//=============================================================================
// Brief   : IPv6 Options Base Class
// Authors : Bruno Santos <bsantos@av.it.pt>
// ----------------------------------------------------------------------------
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
//=============================================================================

#ifndef ODTONE_NET_IP_OPTIONS__HPP_
#define ODTONE_NET_IP_OPTIONS__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace net { namespace ip {

///////////////////////////////////////////////////////////////////////////////
/**
 * This class represents the base IPv6 Options.
 */
class option {
public:
	/**
	 * Convert a byte buffer to an IPv6 Options.
	 *
	 * @param data The byte buffer.
	 * @param len The size of the byte buffer.
	 * @return The pointer of the returning IPv6 Options.
	 */
	static option* cast(void* data, size_t len)
	{
		option* opt = reinterpret_cast<option*>(data);

		if (len < sizeof(option) || len < (opt->_length * 8))
			return nullptr;

		return opt;
	}

	/**
	 * Convert an IPv6 Options to an template class.
	 *
	 * @param Input IPv6 Option.
	 * @return The pointer of the returning class.
	 */
	template<class T>
	static T* cast(option* opt)
	{
		if (!opt || T::type_value != opt->_type || T::static_size > (opt->_length * 8))
			return nullptr;

		return static_cast<T*>(opt);
	}

	/**
	 * Get the IPv6 Options type.
	 *
	 * @param Input IPv6 Option.
	 * @return The IPv6 Options type.
	 */
	static uint8 type(const option* opt)
	{
		return opt->_type;
	}

	/**
	 * Get the IPv6 Options size.
	 *
	 * @param Input IPv6 Option.
	 * @return The IPv6 Options size.
	 */
	static size_t size(const option* opt)
	{
		return opt->_length * 8;
	}

public:
	/**
	 * Construct an IPv6 Options.
	 *
	 * @param type The IPv6 Options type.
	 * @param length The IPv6 Options length.
	 */
	option(uint8 type, uint8 length)
		: _type(type), _length(length / 8)
	{
		BOOST_ASSERT((_length * 8) == length);
	}

protected:
	uint8 _type;	/**< IPv6 Options type.	*/
	uint8 _length;	/**< IPv6 Options size. */
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace ip */ } /* namespace net */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_NET_IP_OPTIONS__HPP_ */
