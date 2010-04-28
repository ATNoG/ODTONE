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

#ifndef ODTONE_SAP_LINK__HPP_
#define ODTONE_SAP_LINK__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/buffer.hpp>
#include <odtone/mih/message.hpp>
#include <odtone/mih/config.hpp>
#include <odtone/sap/sap.hpp>
#include <boost/function.hpp>
#include <boost/asio.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace sap {

static const char* const kConf_MIH_SAP_id	 = "link.id";
static const char* const kConf_Port              = "link.port";

static const char* const kConf_MIHF_Id		 = "mihf.id";
static const char* const kConf_MIHF_Ip		 = "mihf.ip";
static const char* const kConf_MIHF_Local_Port	 = "mihf.local_port";

static const char* const kConf_File               = "conf.file";
static const char* const kConf_Receive_Buffer_Len = "conf.recv_buff_len";


///////////////////////////////////////////////////////////////////////////////
/**
 * \brief Link SAP IO Service
 *
 * This module handles the comunication between User SAP implementations and
 * the MIHF. After being initialized it must be running by invoking the run()
 * method of the provided boost::asio::io_service.
 */
class link : public sap {
	typedef boost::function<void(mih::message& pm, const boost::system::error_code& ec)> default_handler;
	typedef boost::function<void(const boost::system::error_code& ec)> handler;

public:
	link(const mih::config& cfg, boost::asio::io_service& io, const default_handler& h);
	~link();

	void async_send(mih::message& p, const handler& h = handler());

private:
	void recv_handler(buffer<uint8>& buff, size_t rbytes, const boost::system::error_code& ec);
	void send_handler(mih::frame_vla& fm, const handler& h, size_t sbytes, const boost::system::error_code& ec);

private:
	default_handler			_handler;
	boost::asio::ip::udp::socket	_sock;
	boost::asio::ip::udp::endpoint	_ep;
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace sap */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_SAP_USER__HPP_ */
