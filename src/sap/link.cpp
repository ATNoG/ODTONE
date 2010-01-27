//=============================================================================
// Brief   : MIH Link SAP IO Service
// Authors : Bruno Santos <bsantos@av.it.pt>
//
//
// Copyright (C) 2009 Universidade Aveiro - Instituto de Telecomunicacoes Polo Aveiro
//
// This file is part of ODTONE - Open Dot Twenty One.
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//=============================================================================

#include <odtone/sap/link.hpp>
#include <odtone/bindrv.hpp>
#include <boost/bind.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace sap {

namespace ip = boost::asio::ip;

///////////////////////////////////////////////////////////////////////////////
/**
 * \brief Construct a Link SAP IO Service
 *
 * \param cfg configuration with the parameters for MIH Link SAP port,
 *            MIHF ip:port and receive buffer size.
 * \param io generic IO service
 * \param h handler callback as a function pointer/object
 *
 * The handler callback is invoked when a mensage is received such as a request
 * mensage.
 *
 * The signature of the callback is:
 * \code void(odtone::mih::message&, const boost::system::error_code&) \endcode
 *
 * \throws boost::system::error_code
 */
link::link(const mih::config& cfg, boost::asio::io_service& io, const default_handler& h)
	: _handler(h), _sock(io, ip::udp::endpoint(ip::udp::v4(), cfg.get<ushort>(mih::kConf_Port)))
{
	ip::udp::endpoint ep(ip::address::from_string(cfg.get<std::string>(mih::kConf_MIHF_Ip)),
						 cfg.get<ushort>(mih::kConf_MIHF_Local_Port));
	buffer<uint8> buff(cfg.get<uint>(mih::kConf_Receive_Buffer_Len));
	void* rbuff = buff.get();
	size_t rlen = buff.size();

	_sock.connect(ep);
	_sock.async_receive(boost::asio::buffer(rbuff, rlen),
						boost::bind(&link::recv_handler,
									this,
									bindrv(buff),
									boost::asio::placeholders::bytes_transferred,
									boost::asio::placeholders::error));
}

link::~link()
{
}

/**
 * \brief Send the MIH message to the local MIHF asynchronously
 * \param msg MIH message to send
 * \param h Completion callback handler as a function pointer/object
 *
 * After the message is sended, the callback is called to report
 * the success or failure in delivering the message to the MIHF.
 *
 * \remarks This method retuns immediately.
 */
void link::async_send(mih::message& msg, const handler& h)
{
	mih::frame_vla fm;
	void* sbuff;
	size_t slen;

	msg.source(odtone::mih::id("link"));
	msg.get_frame(fm);

	sbuff = fm.get();
	slen = fm.size();

	_sock.async_send(boost::asio::buffer(sbuff, slen),
					 boost::bind(&link::send_handler,
								 this,
								 bindrv(fm),
								 h,
								 boost::asio::placeholders::bytes_transferred,
								 boost::asio::placeholders::error));
}

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
									bindrv(buff),
									boost::asio::placeholders::bytes_transferred,
									boost::asio::placeholders::error));
}

void link::send_handler(mih::frame_vla& /*fm*/, const handler& h, size_t /*sbytes*/, const boost::system::error_code& ec)
{
	h(ec);
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace sap */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
