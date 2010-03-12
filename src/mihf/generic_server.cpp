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

#include <odtone/mih/frame.hpp>
#include <odtone/mihf/generic_server.hpp>
#include <odtone/mihf/transaction_manager.hpp>
#include <odtone/mihf/mihfid.hpp>
#include <odtone/bindrv.hpp>
#include <boost/bind.hpp>
#include <odtone/mihf/log.hpp>
#include <odtone/mihf/utils.hpp>

namespace odtone { namespace mihf {

generic_server::generic_server(boost::asio::io_service& io)
	: _sock(io)
{
}

void generic_server::init(const char   *ip,
						  const uint16	port,
						  uint			concurrency)
{
	using namespace boost::asio;

	ip::udp::endpoint endpoint(ip::address::from_string(ip), port);
	buffer<uint8> buff;
	void* rbuff;
	size_t rlen;

	_sock.open(ip::udp::v4());
	_sock.bind(endpoint);

	for (uint i = 0; i < concurrency; ++i) {
        buff = buffer<uint8>(1500);

        rbuff = buff.get();
        rlen = buff.size();

        _sock.async_receive(boost::asio::buffer(rbuff, rlen),
                            boost::bind(&generic_server::handle_receive,
                                        this,
                                        bindrv(buff),
                                        placeholders::bytes_transferred,
                                        placeholders::error));
	}
}


generic_server::~generic_server()
{
}


boost::asio::io_service& generic_server::get_io_service()
{
	return _sock.get_io_service();
}


void generic_server::handle_receive(buffer<uint8>&					 buff,
									size_t							 rbytes,
									const boost::system::error_code& e)

{
	using namespace boost;

	if (!e)
        {
			log(1, "(generic server) received ", rbytes, " bytes.");
			mih::frame *pud = mih::frame::cast(buff.get(), rbytes);

            if(pud)
                {
                    mih::message_ptr in(new mih::message(*pud));
                    process_message(in);
                }
			void *rbuff = buff.get();
			size_t rlen = buff.size();

			_sock.async_receive(asio::buffer(rbuff, rlen),
								bind(&generic_server::handle_receive,
									 this,
									 bindrv(buff),
									 asio::placeholders::bytes_transferred,
									 asio::placeholders::error));
        }
}

void send_handler(size_t, const boost::system::error_code &ec)
{
	if (ec)
		{
			log(1, "(generic_server) error sending message. Error code: ", ec);
		}
}

void generic_server::send_to(mih::message_ptr &msg, const char *ip, uint16 port)
{
	using namespace boost::asio;

	ip::udp::endpoint ep(ip::address::from_string(ip), port);

	//	msg->source(mihfid);
	mih::frame_vla fm;
	void *sbuff;
	size_t slen;

	msg->get_frame(fm);
	sbuff = fm.get();
	slen = fm.size();

	_sock.async_send_to(boost::asio::buffer(sbuff, slen),
						ep,
						boost::bind((&send_handler), placeholders::bytes_transferred, placeholders::error));
}


} /* namespace mihf */ } /* namespace odtone */
