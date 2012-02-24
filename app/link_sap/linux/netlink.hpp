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

#ifndef LINK_SAP_LINUX_NETLINK__HPP
#define LINK_SAP_LINUX_NETLINK__HPP

///////////////////////////////////////////////////////////////////////////////
#include "../base.hpp"
#include <odtone/buffer.hpp>
#include <boost/utility.hpp>

///////////////////////////////////////////////////////////////////////////////
class netlink : boost::noncopyable {
public:
	class message : boost::noncopyable {
		friend class netlink;

	public:
		message();

		bool next();
		uint type() const;

		const void*                    header() const { return _pos; }
		std::pair<const void*, size_t> payload() const;

	private:
		void*                 _pos;
		size_t                _len;
		odtone::buffer<odtone::uchar> _buf;
	};

	class data : boost::noncopyable {
	public:
		data();
		data(message& msg);

		data& operator=(message& msg);

	protected:
		message* _msg;
	};

	enum family {
		route = 0
	};

	netlink(family fm, uint subscriptions = 0);
	~netlink();

	void send(const message& msg);
	void recv(message& msg);

private:
	int _fd;
};

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* LINK_SAP_LINUX_NETLINK__HPP */
