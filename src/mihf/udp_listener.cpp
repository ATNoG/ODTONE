//
// Copyright (c) 2007-2009 2009 Universidade Aveiro - Instituto de
// Telecomunicacoes Polo Aveiro
// This file is part of ODTONE - Open Dot Twenty One.
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//
// Author:     Simao Reis <sreis@av.it.pt>
//

#include "udp_listener.hpp"
#include "meta_message.hpp"
#include "log.hpp"

#include <odtone/mih/frame.hpp>
#include <odtone/bindrv.hpp>

#include <boost/bind.hpp>

namespace odtone { namespace mihf {

udp_listener::udp_listener(io_service& io,
			   ip::udp ipv,
			   const char *ip,
			   uint16 port,
			   dispatch_t &d)
	: _io(io),
	  _sock(io),
	  _dispatch(d)
{
	ip::udp::endpoint endpoint(ip::address::from_string(ip), port);
	_sock.open(ipv);
	_sock.bind(endpoint);
}

void udp_listener::start()
{
	// TODO: read concurrency from config file
	uint16 concurrency = 1;

	buffer<uint8> buff;
	void* rbuff;
	size_t rlen;

	for (uint i = 0; i < concurrency; ++i) {
		buff = buffer<uint8>(1500);

		rbuff = buff.get();
		rlen = buff.size();

		_sock.async_receive(boost::asio::buffer(rbuff, rlen),
				    boost::bind(&udp_listener::handle_receive,
						this,
						bindrv(buff),
						placeholders::bytes_transferred,
						placeholders::error));
	}
}


void udp_listener::handle_receive(buffer<uint8>&			 buff,
				  size_t				 rbytes,
				  const boost::system::error_code&	 e)

{
	using namespace boost;

	if (!e) {
		log(1, "(udp) received ", rbytes, " bytes.");
		log(0, "(udp) from ", _rmt_endp.address().to_string(),
		    ":", _rmt_endp.port());

		mih::frame *pud = mih::frame::cast(buff.get(), rbytes);

		if(pud) {
			meta_message_ptr in(new meta_message(*pud));
			log(4, *pud);
			_dispatch(in);
                }

		void *rbuff = buff.get();
		size_t rlen = buff.size();

		_sock.async_receive(asio::buffer(rbuff, rlen),
				    bind(&udp_listener::handle_receive,
					 this,
					 bindrv(buff),
					 asio::placeholders::bytes_transferred,
					 asio::placeholders::error));
        }
}


} /* namespace mihf */ } /* namespace odtone */
