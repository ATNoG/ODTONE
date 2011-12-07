//=============================================================================
// Brief   : IP One's Complemente Checksum
// Authors : Bruno Santos <bsantos@av.it.pt>
// ----------------------------------------------------------------------------
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
//=============================================================================

#ifndef ODTONE_NET_IP_CHECKSUM__HPP_
#define ODTONE_NET_IP_CHECKSUM__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <opmip/base.hpp>
#include <opmip/exception.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace net { namespace ip {

///////////////////////////////////////////////////////////////////////////////
class checksum {
public:
	checksum()
		: _sum(0)
	{ }

	void update(const void* data, size_t len)
	{
		if (len % 2)
			ODTONE_THROW_EXCEPTION(exception(boost::system::errc::invalid_argument,
			                                boost::system::get_generic_category(),
			                                __func__));

		update(reinterpret_cast<const uint16*>(data), len / 2);
	}

	void update(const uint16* data, size_t len)
	{
		uint32 sum = _sum;

		for (size_t i = 0; i < len; ++i)
			sum += data[i];

		while (sum >> 16)
			sum = (sum & 0xffff) + (sum >> 16);

		_sum = static_cast<uint16>(sum);
	}

	uint16 final() const
	{
		return ~_sum;
	}

	void clear()
	{
		_sum = 0;
	}

private:
	uint16 _sum;
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace ip */ } /* namespace net */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_IP_CHECKSUM__HPP_ */
