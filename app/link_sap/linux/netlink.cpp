//=============================================================================
// Brief   : Netlink
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

///////////////////////////////////////////////////////////////////////////////
#include "netlink.hpp"
#include <boost/throw_exception.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <sys/socket.h>
#include <linux/netlink.h>

///////////////////////////////////////////////////////////////////////////////
ODTONE_STATIC_ASSERT(netlink::route == NETLINK_ROUTE, "");

inline void throw_error(const boost::system::error_code& ec)
{
	boost::system::system_error e(ec);

	boost::throw_exception(e);
}

///////////////////////////////////////////////////////////////////////////////
netlink::data::data() : _msg(nullptr)
{
}

netlink::data::data(message& msg) : _msg(&msg)
{
}

netlink::data& netlink::data::operator=(message& msg)
{
	_msg = &msg;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////
netlink::message::message() : _pos(nullptr), _len(0)
{
	_buf.size(4096);
}

bool netlink::message::next()
{
	if (NLMSG_OK(reinterpret_cast<nlmsghdr*>(_pos), _len))
		_pos = NLMSG_NEXT(reinterpret_cast<nlmsghdr*>(_pos), _len);

	return NLMSG_OK(reinterpret_cast<nlmsghdr*>(_pos), _len);
}

uint netlink::message::type() const
{
	return reinterpret_cast<nlmsghdr*>(_pos)->nlmsg_type;
}

std::pair<const void*, size_t> netlink::message::payload() const
{
	nlmsghdr* nl = reinterpret_cast<nlmsghdr*>(_pos);

	return std::pair<const void*, size_t>(NLMSG_DATA(nl), NLMSG_PAYLOAD(nl, _len));
}

///////////////////////////////////////////////////////////////////////////////
netlink::netlink(family fm, uint subscriptions)
{
	::sockaddr_nl addr;
	int res;

	_fd = ::socket(PF_NETLINK, SOCK_RAW, fm);
	if (_fd < 0)
		throw_error(boost::system::error_code(errno, boost::system::get_system_category()));

	addr.nl_family = AF_NETLINK;
	addr.nl_pid = 0;
	addr.nl_groups = subscriptions;

	res = ::bind(_fd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
	if (res < 0)
		throw_error(boost::system::error_code(errno, boost::system::get_system_category()));
}

netlink::~netlink()
{
	::close(_fd);
}

void netlink::send(const message& msg)
{
	::ssize_t res;

	res = ::send(_fd, msg._buf.get(), msg._buf.size(), 0);
	if (res < 0)
		throw_error(boost::system::error_code(errno, boost::system::get_system_category()));
}

void netlink::recv(message& msg)
{
	::ssize_t res;

	res = ::recv(_fd, msg._buf.get(), msg._buf.size(), 0);
	if (res < 0)
		throw_error(boost::system::error_code(errno, boost::system::get_system_category()));

	msg._pos = msg._buf.get();
	msg._len = res;
}

// EOF ////////////////////////////////////////////////////////////////////////
