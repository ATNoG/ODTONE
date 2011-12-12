//==============================================================================
// Brief   : UDP Listener
// Authors : Simao Reis <sreis@av.it.pt>
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

#include "udp_listener.hpp"
#include "meta_message.hpp"
#include "log.hpp"
#include <odtone/mih/frame.hpp>
#include <odtone/bind_rv.hpp>
#include <boost/bind.hpp>

namespace odtone { namespace mihf {

/**
 * Construct a UDP Listener.
 *
 * @param io The io_service object that Link SAP I/O Service will use to
 * dispatch handlers for any asynchronous operations performed on
 * the socket.
 * @param buff_size The receive buffer length.
 * @param ipv The IP protocol type.
 * @param ip The IP address to be aware.
 * @param port The listening port.
 * @param d The dispatch function.
 */
udp_listener::udp_listener(io_service& io,
			   uint16 buff_size,
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
	_sock.set_option(boost::asio::socket_base::receive_buffer_size(buff_size));
}

/**
 * Start the UDP listener socket.
 */
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

		_sock.async_receive_from(boost::asio::buffer(rbuff, rlen),
					 _rmt_endp,
					 boost::bind(&udp_listener::handle_receive,
						this,
						bind_rv(buff),
						placeholders::bytes_transferred,
						placeholders::error));
	}
}

/**
 * Handle the reception of an asynchronous message.
 *
 * @param buff The input message bytes.
 * @param rbytes The number of bytes of the input message.
 * @param error The error code.
 */
void udp_listener::handle_receive(buffer<uint8>&			 buff,
				  size_t				 rbytes,
				  const boost::system::error_code&	 e)

{
	using namespace boost;

	if (!e) {
		ODTONE_LOG(1, "(udp) received ", rbytes, " bytes.");
		ODTONE_LOG(0, "(udp) from ", _rmt_endp.address().to_string(),
		    ":", _rmt_endp.port());

		mih::frame *pud = mih::frame::cast(buff.get(), rbytes);

		if(pud) {
			mih::octet_string ip(_rmt_endp.address().to_string());
			uint16 port = _rmt_endp.port();

			meta_message_ptr in(new meta_message(ip, port, *pud));
			ODTONE_LOG(4, *pud);
			_dispatch(in);
                }

		void *rbuff = buff.get();
		size_t rlen = buff.size();

		_sock.async_receive_from(asio::buffer(rbuff, rlen),
					 _rmt_endp,
					 bind(&udp_listener::handle_receive,
					      this,
					      bind_rv(buff),
					      asio::placeholders::bytes_transferred,
					      asio::placeholders::error));
        }
}


} /* namespace mihf */ } /* namespace odtone */
