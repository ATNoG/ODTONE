//==============================================================================
// Brief   : MIH User SAP IO Service
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

#include <odtone/sap/user.hpp>
#include <odtone/buffer.hpp>
#include <odtone/bind_rv.hpp>
#include <boost/bind.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace sap {

namespace ip = boost::asio::ip;

///////////////////////////////////////////////////////////////////////////////
/**
 * Construct a MIH-User SAP I/O Service.
 * The defined callback is invoked when a request message is received
 * The signature of the callback is:
 * void(odtone::mih::message&, const boost::system::error_code&).
 *
 * @param cfg Configuration parameters.
 * @param io The io_service object that MIH-User SAP I/O Service will use to
	         dispatch handlers for any asynchronous operations performed on
	         the socket.
 * @param h Message processing handler.
 */
user::user(const mih::config& cfg, boost::asio::io_service& io, const handler& h)
	: _handler(h), _sock(io, ip::udp::endpoint(ip::udp::v4(), cfg.get<ushort>(kConf_Port))),
	  _ep(ip::address::from_string(cfg.get<std::string>(kConf_MIHF_Ip)), cfg.get<ushort>(kConf_MIHF_Local_Port)),
	  _user_id(odtone::mih::id(cfg.get<std::string>(kConf_MIH_SAP_id)))
{
	buffer<uint8> buff(cfg.get<uint>(kConf_Receive_Buffer_Len));
	void* rbuff = buff.get();
	size_t rlen = buff.size();

	_sock.async_receive(boost::asio::buffer(rbuff, rlen),
						boost::bind(&user::recv_handler,
									this,
									bind_rv(buff),
									boost::asio::placeholders::bytes_transferred,
									boost::asio::placeholders::error));
}

/**
 * Construct a MIH-User SAP I/O Service.
 * The defined callback is invoked when a request message is received
 * The signature of the callback is:
 * void(odtone::mih::message&, const boost::system::error_code&).
 *
 * @param io The io_service object that MIH-User SAP I/O Service will use to
 * dispatch handlers for any asynchronous operations performed on
 * the socket.
 * @param h Message processing handler.
 * @param cfg Configuration parameters.
 */
user::user(boost::asio::io_service& io, const handler& h, const config& cfg)
	: _handler(h), _sock(io, ip::udp::endpoint(ip::udp::v4(), cfg.port)),
	  _ep(cfg.mihf_address, cfg.mihf_port), _user_id(odtone::mih::id(cfg.id))
{
	buffer<uint8> buff(cfg.buffer_length);
	void* rbuff = buff.get();
	size_t rlen = buff.size();

	_sock.async_receive(boost::asio::buffer(rbuff, rlen),
						boost::bind(&user::recv_handler,
									this,
									bind_rv(buff),
									boost::asio::placeholders::bytes_transferred,
									boost::asio::placeholders::error));
}

/**
 * Destruct a MIH-User SAP I/O Service.
 */
user::~user()
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
void user::async_send_(mih::message& msg, handler&& h)
{
	if (msg.opcode() == mih::operation::request) {
		uint16 id = std::rand() & 0x0FFF; //12 bits transaction id

		boost::mutex::scoped_lock sl(_mutex);
		rmap::iterator ie = _rmap.end();

		if (!_rmap.empty())
			id = uint16(_rmap.rbegin()->first) + 1;
		id = (id >= 0x0FFF) ? 1 : id;

		while (_rmap.find(id) != ie) {
			id += 1;
			id = (id >= 0x0FFF) ? 1 : id;
		}

		msg.tid(id);
		_rmap[id] = std::move(h);
		h.clear();
	}

	mih::frame_vla fm;
	void* sbuff;
	size_t slen;

	msg.source(_user_id);
	msg.get_frame(fm);

	sbuff = fm.get();
	slen = fm.size();

	_sock.async_send_to(boost::asio::buffer(sbuff, slen),
			    _ep,
					 boost::bind(&user::send_handler,
								 this,
								 bind_rv(fm),
								 std::move(h),
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
void user::recv_handler(buffer<uint8>& buff, size_t rbytes, const boost::system::error_code& ec)
{
	if (ec) {
		mih::message pm;

		_handler(pm, ec);

	} else {
		mih::frame* fm = mih::frame::cast(buff.get(), rbytes);

		if (fm) {
			mih::message pm(*fm);

			if (fm->opcode() == mih::operation::confirm) {
				handler h;

				get_handler(fm->tid(), h);
				if (h) {
					h(pm, ec);
				// Unsolicited MIH capability discover reception
				} else if(fm->sid() == mih::service::management &&
				        fm->aid() == mih::action::capability_discover) {
					_handler(pm, ec);
				} else {
					_handler(pm, boost::system::errc::make_error_code(boost::system::errc::bad_message));
				}
			} else if (fm->opcode() != mih::operation::indication) {
				_handler(pm, boost::system::errc::make_error_code(boost::system::errc::bad_message));
			} else {
				_handler(pm, ec);
			}
		}
	}

	void* rbuff = buff.get();
	size_t rlen = buff.size();

	_sock.async_receive(boost::asio::buffer(rbuff, rlen),
						boost::bind(&user::recv_handler,
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
 * @param ec Error code.
 */
void user::send_handler(mih::frame_vla& fm, handler& h, const boost::system::error_code& ec)
{
	if (ec && !h)
		get_handler(fm->tid(), h);

	if (h) {
		mih::message pm(*fm);

		h(pm, ec);
	}
}

/**
 * Get the message handler function of the message.
 *
 * @param tid Transaction ID of the message.
 * @param h Reference to the message handler.
 */
void user::get_handler(uint tid, handler& h)
{
	boost::mutex::scoped_lock sl(_mutex);
	rmap::iterator i = _rmap.find(tid);

	if (i != _rmap.end()) {
		std::swap(h, i->second);
		_rmap.erase(i);
	}
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace sap */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
