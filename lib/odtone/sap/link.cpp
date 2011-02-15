//=============================================================================
// Brief   : MIH Link SAP IO Service
// Authors : Bruno Santos <bsantos@av.it.pt>
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

#include <odtone/sap/link.hpp>
#include <odtone/buffer.hpp>
#include <boost/bind.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace sap {

namespace ip = boost::asio::ip;

///////////////////////////////////////////////////////////////////////////////
/**
 * Construct a Link SAP IO Service.
 * The handler callback is invoked when a mensage is received such as a request
 * mensage. The signature of the callback is: void(odtone::mih::message&, const boost::system::error_code&).
 *
 * @param cfg configuration with the parameters for MIH Link SAP port, MIHF ip:port and receive buffer size.
 * @param io  generic IO service.
 * @param h   handler callback as a function pointer/object.
 * @throws boost::system::error_code
 */
link::link(const mih::config& cfg, boost::asio::io_service& io, const default_handler& h)
	: _handler(h), _sock(io, ip::udp::endpoint(ip::udp::v4(), cfg.get<ushort>(kConf_Port))),
	  _ep(ip::address::from_string(cfg.get<std::string>(kConf_MIHF_Ip)),
	      cfg.get<ushort>(kConf_MIHF_Local_Port)),
	  _link_id(odtone::mih::id(cfg.get<std::string>(kConf_MIH_SAP_id))),
	  _mihf_id(odtone::mih::id(cfg.get<std::string>(kConf_MIHF_Id)))
{
	buffer<uint8> buff(cfg.get<uint>(kConf_Receive_Buffer_Len));
	void* rbuff = buff.get();
	size_t rlen = buff.size();

	//_sock.connect(ep);
	_sock.async_receive(boost::asio::buffer(rbuff, rlen),
						boost::bind(&link::recv_handler,
									this,
									move(buff),
									boost::asio::placeholders::bytes_transferred,
									boost::asio::placeholders::error));
}

/**
 * Destruct a Link SAP IO Service.
 */
link::~link()
{
}

/**
 * Send the MIH message to the local MIHF asynchronously.
 * After the message is sended, the callback is called to report the success or failure in delivering the message to the MIHF. This method retuns immediately.
 *
 * @param msg MIH message to send.
 * @param h completion callback handler as a function pointer/object.
 */
void link::async_send(mih::message& msg, const handler& h)
{
	mih::frame_vla fm;
	void* sbuff;
	size_t slen;

	msg.source(_link_id);
	msg.destination(_mihf_id);

	msg.get_frame(fm);

	sbuff = fm.get();
	slen = fm.size();

	_sock.async_send_to(boost::asio::buffer(sbuff, slen),
			    _ep,
			    boost::bind(&link::send_handler,
					this,
					move(fm),
					h,
					boost::asio::placeholders::bytes_transferred,
					boost::asio::placeholders::error));
}

/**
 * Send the MIH message to the local MIHF synchronously.
 * After the message is sent, the callback is called to report
 * the success or failure in delivering the message to the MIHF. This method retuns immediately.
 *
 * @param msg MIH message to send
 * @param h Completion callback handler as a function pointer/object
 */
void link::sync_send(mih::message& msg)
{
	mih::frame_vla fm;
	void* sbuff;
	size_t slen;

	msg.source(_link_id);
	msg.destination(_mihf_id);
	msg.get_frame(fm);

	sbuff = fm.get();
	slen = fm.size();

	_sock.send_to(boost::asio::buffer(sbuff, slen), _ep);
}

/**
 * Received message handler.
 *
 * @param buff message byte buffer.
 * @param rbytes number of bytes of the message.
 * @param ec error code.
 */
void link::recv_handler(buffer<uint8>& buff, size_t rbytes, const boost::system::error_code& ec)
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
						boost::bind(&link::recv_handler,
									this,
									move(buff),
									boost::asio::placeholders::bytes_transferred,
									boost::asio::placeholders::error));
}

/**
 * Sent message handler.
 *
 * @param fm message sent.
 * @param sbytes number of bytes of the message.
 * @param ec error code.
 */
void link::send_handler(mih::frame_vla& /*fm*/, const handler& h, size_t /*sbytes*/, const boost::system::error_code& ec)
{
	if (h)
		h(ec);
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace sap */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
