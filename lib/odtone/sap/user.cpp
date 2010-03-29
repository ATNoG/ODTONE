//=============================================================================
// Brief   : MIH User SAP IO Service
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

#include <odtone/sap/user.hpp>
#include <odtone/buffer.hpp>
#include <odtone/bindrv.hpp>
#include <boost/bind.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace sap {

namespace ip = boost::asio::ip;

///////////////////////////////////////////////////////////////////////////////
/**
 * \brief Construct an User SAP IO Service
 *
 * \param cfg configuration with the parameters for MIH User port,
 *            MIHF ip:port and receive buffer size.
 * \param io generic IO service
 * \param h handler callback as a function pointer/object
 *
 * The handler callback is invoked when an indication mensage is received.
 *
 * The signature of the callback is:
 * \code void(odtone::mih::message&, const boost::system::error_code&) \endcode
 *
 * \throws boost::system::error_code
 */
user::user(const mih::config& cfg, boost::asio::io_service& io, const handler& h)
	: _handler(h), _sock(io, ip::udp::endpoint(ip::udp::v4(), cfg.get<ushort>(kConf_Port))),
	  _ep(ip::address::from_string(cfg.get<std::string>(kConf_MIHF_Ip)), cfg.get<ushort>(kConf_MIHF_Local_Port))
{
	// ip::udp::endpoint
	buffer<uint8> buff(cfg.get<uint>(kConf_Receive_Buffer_Len));
	void* rbuff = buff.get();
	size_t rlen = buff.size();

	mih::octet_string id = cfg.get<mih::octet_string>(kConf_MIH_SAP_id);
	_id.assign(id);

	// _sock.connect(ep);
	_sock.async_receive(boost::asio::buffer(rbuff, rlen),
						boost::bind(&user::recv_handler,
									this,
									bindrv(buff),
									boost::asio::placeholders::bytes_transferred,
									boost::asio::placeholders::error));
}

user::~user()
{
}

/**
 * \brief Send the MIH message to the local MIHF asynchronously
 * \param msg MIH message to send
 * \param h Completion/Response callback handler as a function
 *          pointer/object
 *
 * After the message is sended, the callback is called with the
 * response message or to report failure in delivering the message
 * to the MIHF.
 *
 * \remarks This method retuns immediately.
 */
void user::async_send(mih::message& msg, const handler& h)
{
	uint16 id = std::rand() & 0x0FFF; //12 bits transaction id

	{
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
		_rmap[id] = h;
	}

	mih::frame_vla fm;
	void* sbuff;
	size_t slen;

	msg.source(_id);
	msg.get_frame(fm);

	sbuff = fm.get();
	slen = fm.size();

	_sock.async_send_to(boost::asio::buffer(sbuff, slen),
			    _ep,
					 boost::bind(&user::send_handler,
								 this,
								 bindrv(fm),
								 boost::asio::placeholders::bytes_transferred,
								 boost::asio::placeholders::error));
}

void user::recv_handler(buffer<uint8>& buff, size_t rbytes, const boost::system::error_code& ec)
{
	if (ec) {
		mih::message pm;

		_handler(pm, ec);

	} else {
		mih::frame* fm = mih::frame::cast(buff.get(), rbytes);

		if (fm) {
			handler rh;
			{
				boost::mutex::scoped_lock sl(_mutex);
				rmap::iterator i = _rmap.find(fm->tid());

				if (i != _rmap.end()) {
					std::swap(rh, i->second);
					_rmap.erase(i);
				}
			}
			mih::message pm(*fm);

			if (rh)
				rh(pm, ec);
			else
				_handler(pm, ec);
		}
	}

	void* rbuff = buff.get();
	size_t rlen = buff.size();

	_sock.async_receive(boost::asio::buffer(rbuff, rlen),
						boost::bind(&user::recv_handler,
									this,
									bindrv(buff),
									boost::asio::placeholders::bytes_transferred,
									boost::asio::placeholders::error));
}

void user::send_handler(mih::frame_vla& fm, size_t /*sbytes*/, const boost::system::error_code& ec)
{
	if (ec) {
		mih::message pm;
		handler rh;

		{
			boost::mutex::scoped_lock sl(_mutex);
			rmap::iterator i = _rmap.find(fm->tid());

			std::swap(rh, i->second);
			_rmap.erase(i);
		}

		rh(pm, ec);
	}
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace sap */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
