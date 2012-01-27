//=============================================================================
// Brief   : ICMP Parser
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


#include <odtone/net/ip/icmp/icmp_parser.hpp>

#include <odtone/net/ip/icmp/icmp.hpp>
#include <odtone/net/ip/icmp/icmp_options.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace net { namespace ip {

///////////////////////////////////////////////////////////////////////////////
/**
 * Create an ICMP Router Solicitation packet.
 *
 * @param buffer The byte buffer.
 * @param length The byte buffer length.
 * @param source_link_layer Source link layer option value.
 */
bool icmp_rs_parse(uchar* buffer, size_t length, link::address_mac& source_link_layer)
{
	using namespace odtone::net::ip;

	icmp::router_solicitation* rs = icmp::header::cast<icmp::router_solicitation>(buffer, length);
	if (!rs)
		return false;

	size_t pos = sizeof(icmp::router_solicitation);

	while (pos < length) {
		option*                opt = option::cast(buffer + pos, length - pos);
		opt_source_link_layer* sll = opt_source_link_layer::cast(opt);
		size_t                 len = option::size(opt);

		if (!len)
			break;

		if (sll) {
			source_link_layer = sll->to_mac();
			return true;
		}
		pos += len;
	}

	return false;
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace ip */ } /* namespace net */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
