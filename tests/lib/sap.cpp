//==============================================================================
// Brief   : Test SAP IO Service
// Authors : Carlos Guimarães <cguimaraes@av.it.pt>
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

#include "sap.hpp"

#include <odtone/buffer.hpp>
#include <odtone/bind_rv.hpp>
#include <boost/bind.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace test {

namespace ip = boost::asio::ip;

///////////////////////////////////////////////////////////////////////////////
/**
 * Construct a Test SAP I/O Service.
 * The defined callback is invoked when a request message is received
 * The signature of the callback is:
 * void(odtone::mih::message&, const boost::system::error_code&).
 *
 * @param io The io_service object that Test SAP I/O Service will use to
             dispatch handlers for any asynchronous operations performed on
             the socket.
 * @param cfg Configuration parameters.
 * @param h Message processing handler.
 */
test::test(boost::asio::io_service& io, const mih::config& cfg, const default_handler& h)
	: _handler(h), _sock(io, ip::udp::endpoint(ip::udp::v4(), cfg.get<ushort>(kConf_Port))),
	  _ep1(ip::address::from_string("127.0.0.1"),
	      cfg.get<ushort>(kConf_MIHF1_Local_Port)),
	  _ep2(ip::address::from_string("127.0.0.1"),
	      cfg.get<ushort>(kConf_MIHF2_Local_Port)),
	  _link_id(odtone::mih::id("Test"))
{
	buffer<uint8> buff(cfg.get<uint>(kConf_Receive_Buffer_Len));
	void* rbuff = buff.get();
	size_t rlen = buff.size();

	//_sock.connect(ep);
	_sock.async_receive(boost::asio::buffer(rbuff, rlen),
						boost::bind(&test::recv_handler,
									this,
									bind_rv(buff),
									boost::asio::placeholders::bytes_transferred,
									boost::asio::placeholders::error));
}

/**
 * Destruct a Test SAP I/O Service.
 */
test::~test()
{
}

/**
 * Asynchronously send a MIH message to the local MIHF.
 * After sending the message, the callback is called to report the
 * success or failure in delivering the message to the local MIHF.
 * This method retuns immediately.
 *
 * @param msg MIH message to send.
 * @param h Response handler function.
 */
void test::async_send_mihf1(mih::message& msg, const handler& h)
{
	mih::frame_vla fm;
	void* sbuff;
	size_t slen;

	msg.source(_link_id);

	msg.get_frame(fm);

	sbuff = fm.get();
	slen = fm.size();

	_sock.async_send_to(boost::asio::buffer(sbuff, slen),
			    _ep1,
			    boost::bind(&test::send_handler,
					this,
					bind_rv(fm),
					h,
					boost::asio::placeholders::bytes_transferred,
					boost::asio::placeholders::error));
}

/**
 * Asynchronously send a MIH message to the local MIHF.
 * After sending the message, the callback is called to report the
 * success or failure in delivering the message to the local MIHF.
 * This method retuns immediately.
 *
 * @param msg MIH message to send.
 * @param h Response handler function.
 */
void test::async_send_mihf2(mih::message& msg, const handler& h)
{
	mih::frame_vla fm;
	void* sbuff;
	size_t slen;

	msg.source(_link_id);

	msg.get_frame(fm);

	sbuff = fm.get();
	slen = fm.size();

	_sock.async_send_to(boost::asio::buffer(sbuff, slen),
			    _ep2,
			    boost::bind(&test::send_handler,
					this,
					bind_rv(fm),
					h,
					boost::asio::placeholders::bytes_transferred,
					boost::asio::placeholders::error));
}

/**
 * Received message callback. This function is executed to process the
 * received messages. If this is a valid message, the message is
 * dispatched to the handler defined by the user.
 *
 * @param buff Message byte buffer.
 * @param rbytes Size of the message.
 * @param ec Error code.
 */
void test::recv_handler(buffer<uint8>& buff, size_t rbytes,
						const boost::system::error_code& ec)
{
	if (ec) {
		mih::message pm;

		_handler(pm, ec);

	} else {
		mih::frame* fm = mih::frame::cast(buff.get(), rbytes);

		if (fm) {
			mih::message pm(*fm);

			_handler(pm, ec);
		}
	}

	void* rbuff = buff.get();
	size_t rlen = buff.size();

	_sock.async_receive(boost::asio::buffer(rbuff, rlen),
						boost::bind(&test::recv_handler,
									this,
									bind_rv(buff),
									boost::asio::placeholders::bytes_transferred,
									boost::asio::placeholders::error));
}

/**
 * Sent message handler. After sending the message, this function is called to
 * report the success or failure in delivering the message to the local MIHF.
 *
 * @param fm MIH message sent.
 * @param h Message handler.
 * @param sbytes Size of the message.
 * @param ec Error code.
 */
void test::send_handler(mih::frame_vla& fm, const handler& h, size_t sbytes, const boost::system::error_code& ec)
{
	if (h)
		h(ec);
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace test */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
