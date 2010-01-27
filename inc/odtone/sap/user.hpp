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

#ifndef ODTONE_SAP_USER__HPP_
#define ODTONE_SAP_USER__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/buffer.hpp>
#include <odtone/mih/message.hpp>
#include <odtone/mih/config.hpp>
#include <odtone/sap/sap.hpp>
#include <boost/function.hpp>
#include <boost/asio.hpp>
#include <boost/thread/mutex.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace sap {

///////////////////////////////////////////////////////////////////////////////
/**
 * \brief User SAP IO Service
 *
 * This module handles the comunication between User SAP implementations and
 * the MIHF. After being initialized it must be running by invoking the run()
 * method of the provided boost::asio::io_service.
 */
class user : public sap {
	typedef boost::function<void(mih::message& pm, const boost::system::error_code&)> handler;
	typedef std::map<uint, handler> rmap;

public:
	user(const mih::config& cfg, boost::asio::io_service& io, const handler& h);
	~user();

	void async_send(mih::message& pm, const handler& h);

private:
	void recv_handler(buffer<uint8>& buff, size_t rbytes, const boost::system::error_code& ec);
	void send_handler(mih::frame_vla& fm, size_t sbytes, const boost::system::error_code& ec);

private:
	handler								_handler;
	boost::asio::ip::udp::socket		_sock;
	mih::id								_id;

	boost::mutex _mutex;
	rmap         _rmap;
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace sap */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_SAP_USER__HPP_ */
