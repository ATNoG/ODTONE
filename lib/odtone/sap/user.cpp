//=============================================================================
// Brief   : MIH User SAP IO Service
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

#include <odtone/sap/user.hpp>
#include <odtone/buffer.hpp>
#include <odtone/bind_rv.hpp>
#include <boost/bind.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace sap {

namespace ip = boost::asio::ip;

///////////////////////////////////////////////////////////////////////////////
/**
 * Construct an User SAP IO Service.
 *
 * @param  cfg configuration with the parameters for MIH User port, MIHF ip:port and receive buffer size.
 * @param  io generic IO service.
 * @param  h handler callback as a function pointer/object. The handler callback is invoked when an message is received, offering a simple way to process incoming messages. The signature of the callback is: void(odtone::mih::message&, const boost::system::error_code&).
 * @throws boost::system::error_code
 */
user::user(const mih::config& cfg, boost::asio::io_service& io, const handler& h)
	: _handler(h), _sock(io, ip::udp::endpoint(ip::udp::v4(), cfg.get<ushort>(kConf_Port))),
	  _ep(ip::address::from_string(cfg.get<std::string>(kConf_MIHF_Ip)), cfg.get<ushort>(kConf_MIHF_Local_Port)),
	  _user_id(odtone::mih::id(cfg.get<std::string>(kConf_MIH_SAP_id))),
	  _mihf_id(odtone::mih::id(cfg.get<std::string>(kConf_MIHF_Id)))
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

user::user(boost::asio::io_service& io, const handler& h, const config& cfg)
	: _handler(h), _sock(io, ip::udp::endpoint(ip::udp::v4(), cfg.port)),
	  _ep(cfg.mihf_address, cfg.mihf_port), _user_id(odtone::mih::id(cfg.id)),
	  _mihf_id(odtone::mih::id(cfg.mihf_id))
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
 * Destruct an User SAP IO Service.
 */
user::~user()
{
}

/**
 * Send the MIH message to the local MIHF asynchronously.
 * After the message is sent, the callback is called with the
 * response message or to report failure in delivering the message
 * to the MIHF.This method retuns immediately.
 *
 * @param msg MIH message to send.
 * @param h Completion/Response callback handler as a function pointer/object.
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
	msg.destination(_mihf_id);
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
 * Received message handler.
 *
 * @param buff message byte buffer.
 * @param rbytes number of bytes of the message.
 * @param ec error code.
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

			if (fm->opcode() == mih::operation::response) {
				handler h;

				get_handler(fm->tid(), h);
				if (h)
					h(pm, ec);
				else
					_handler(pm, boost::system::errc::make_error_code(boost::system::errc::bad_message));

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
 * Sent message handler.
 *
 * @param fm message sent.
 * @param sbytes number of bytes of the message.
 * @param ec error code.
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
