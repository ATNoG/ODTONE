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
static const char* const kConf_Tec               = "link.tec";
static const char* const kConf_Interface_Addr    = "link.link_addr_list";
static const char* const kConf_Evt_List          = "link.event_list";
static const char* const kConf_Cmd_List          = "link.command_list";

static const char* const kConf_MIHF_Id		 = "mihf.id";
static const char* const kConf_MIHF_Ip		 = "mihf.ip";
static const char* const kConf_MIHF_Local_Port	 = "mihf.local_port";

static const char* const kConf_File               = "conf.file";
static const char* const kConf_Receive_Buffer_Len = "conf.recv_buff_len";


///////////////////////////////////////////////////////////////////////////////
/**
 * Link SAP IO Service.
 *
 * This module handles the comunication between User SAP implementations and
 * the MIHF. After being initialized it must be running by invoking the run()
 * method of the provided boost::asio::io_service.
 */
class link : public sap {
	typedef boost::function<void(mih::message& pm, const boost::system::error_code& ec)> default_handler;
	typedef boost::function<void(const boost::system::error_code& ec)> handler;

public:
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
	link(const mih::config& cfg, boost::asio::io_service& io, const default_handler& h);

	/**
	 * Destruct a Link SAP IO Service.
	 */
	~link();

	/**
	 * Send the MIH message to the local MIHF asynchronously.
	 * After the message is sended, the callback is called to report the success or failure in delivering the message to the MIHF. This method retuns immediately.
	 *
	 * @param msg MIH message to send.
	 * @param h completion callback handler as a function pointer/object.
	 */
	void async_send(mih::message& p, const handler& h = handler());

	/**
	 * Send the MIH message to the local MIHF synchronously.
	 * After the message is sended, the callback is called to report
	 * the success or failure in delivering the message to the MIHF. This method retuns immediately.
	 *
	 * @param msg MIH message to send
	 * @param h Completion callback handler as a function pointer/object
	 */
	void sync_send(mih::message& p);

private:
	/**
	 * Received message handler.
	 *
	 * @param buff message byte buffer.
	 * @param rbytes number of bytes of the message.
	 * @param ec error code.
	 */
	void recv_handler(buffer<uint8>& buff, size_t rbytes, const boost::system::error_code& ec);

	/**
	 * Sent message handler.
	 *
	 * @param fm message sent.
	 * @param sbytes number of bytes of the message.
	 * @param ec error code.
	 */
	void send_handler(mih::frame_vla& fm, const handler& h, size_t sbytes, const boost::system::error_code& ec);

private:
	default_handler                 _handler;
	boost::asio::ip::udp::socket    _sock;
	boost::asio::ip::udp::endpoint  _ep;
	odtone::mih::id                 _link_id;
	odtone::mih::id                 _mihf_id;
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace sap */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_SAP_LINK__HPP_ */
