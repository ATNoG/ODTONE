//=============================================================================
// Brief   : Ethernet Protocol
// Authors : Bruno Santos <bsantos@av.it.pt>
// ----------------------------------------------------------------------------
// ODTOne - Open Dot Twenty One
//
// Copyright (C) 2010-2011 Universidade de Aveiro
// Copyrigth (C) 2010-2011 Instituto de Telecomunicações - Pólo de Aveiro
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//=============================================================================

#ifndef ODTONE_NET_LINK_ETHERNET__HPP_
#define ODTONE_NET_LINK_ETHERNET__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/net/link/address_mac.hpp>
#include <boost/asio/basic_datagram_socket.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace net { namespace link {

///////////////////////////////////////////////////////////////////////////////
class ethernet {
public:
	enum protocols {
		ipv4 = 0x0800,
		ipv6 = 0x86DD
	};

	typedef boost::asio::basic_datagram_socket<ethernet> socket;

	class endpoint {
	public:
		typedef ethernet protocol_type;

		enum pk_type {
			host,
			broadcast,
			otherhost,
			outgoing,
			loopback
		};

	public:
		endpoint();
		endpoint(uint16 proto, uint ifindex);
		endpoint(uint16 proto, uint ifindex, pk_type pktp, const mac_address& destination);

		protocol_type     protocol() const       { return protocol_type(_protocol); }
		::sockaddr*       data()                 { return reinterpret_cast< ::sockaddr*>(this); }
		const ::sockaddr* data() const           { return reinterpret_cast<const ::sockaddr*>(this); }
		std::size_t       size() const           { return sizeof(*this); }
		std::size_t       capacity() const       { return sizeof(*this); }
		void              resize(std::size_t sz) { BOOST_ASSERT(sz <= sizeof(*this)); }

	private:
		ushort _family;
		uint16 _protocol; //big-endian
		uint   _ifindex;
		ushort _hatype;
		uchar  _pkttype;
		uchar  _halen;
		uchar  _addr[8];
	};

public:
	ethernet(uint16 proto)
		: _protocol(htons(proto))
	{ }

	int family() const   { return 17/*AF_PACKET*/; }
	int type() const     { return SOCK_DGRAM; }
	int protocol() const { return _protocol; }

private:
	uint16 _protocol; //big-endian
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace link */ } /* namespace net */ } /* namespace odtone */

///////////////////////////////////////////////////////////////////////////////
extern template class boost::asio::basic_datagram_socket<odtone::net::link::ethernet>;

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* OPMIP_NET_LINK_ETHERNET__HPP_ */
