//=============================================================================
// Brief   : MIH Link SAP IO Service
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

static const char* const kConf_MIH_SAP_id		= "link.id";
static const char* const kConf_Port				= "link.port";
static const char* const kConf_Tec				= "link.tec";
static const char* const kConf_Interface_Addr	= "link.link_addr";
static const char* const kConf_Evt_List			= "link.event_list";
static const char* const kConf_Cmd_List			= "link.command_list";

static const char* const kConf_MIHF_Id			= "mihf.id";
static const char* const kConf_MIHF_Ip			= "mihf.ip";
static const char* const kConf_MIHF_Local_Port	= "mihf.local_port";

static const char* const kConf_File					= "conf.file";
static const char* const kConf_Receive_Buffer_Len	= "conf.recv_buff_len";


///////////////////////////////////////////////////////////////////////////////
/**
 * Link SAP I/O Service.
 *
 * This module handles the comunication between Link SAP and its local the
 * MIHF. After being initialized, and in order to run this service, it must
 * be invoked the run() method of the boost::asio::io_service associated.
 */
class link : public sap {
	typedef boost::function<void(mih::message& pm, const boost::system::error_code& ec)> default_handler;
	typedef boost::function<void(const boost::system::error_code& ec)> handler;

public:
	/**
	 * Construct a Link SAP I/O Service.
	 * The defined callback is invoked when a request message is received
	 * The signature of the callback is:
	 * void(odtone::mih::message&, const boost::system::error_code&).
	 *
	 * @param cfg Configuration parameters.
	 * @param io The io_service object that Link SAP I/O Service will use to
		         dispatch handlers for any asynchronous operations performed on
		         the socket.
	 * @param h Message processing handler.
	 */
	link(const mih::config& cfg, boost::asio::io_service& io, const default_handler& h);

	/**
	 * Destruct a Link SAP I/O Service.
	 */
	~link();

	/**
	 * Asynchronously send a MIH message to the local MIHF.
	 * After sending the message, the callback is called to report the
	 * success or failure in delivering the message to the local MIHF.
	 * This method retuns immediately.
	 *
	 * @param msg MIH message to send.
	 * @param h Response handler function.
	 */
	void async_send(mih::message& msg, const handler& h = handler());

private:
	/**
	 * Received message callback. This function is executed to process the
	 * received messages. If this is a valid message, the message is
	 * dispatched to the handler defined by the user.
	 *
	 * @param buff Message byte buffer.
	 * @param rbytes Size of the message.
	 * @param ec Error code.
	 */
	void recv_handler(buffer<uint8>& buff, size_t rbytes,
					  const boost::system::error_code& ec);

	/**
	 * Sent message handler. After sending the message, this function is called to
	 * report the success or failure in delivering the message to the local MIHF.
	 *
	 * @param fm MIH message sent.
	 * @param h Message handler.
	 * @param sbytes Size of the message.
	 * @param ec Error code.
	 */
	void send_handler(mih::frame_vla& fm, const handler& h, size_t sbytes,
					  const boost::system::error_code& ec);

private:
	default_handler                 _handler;	/**< User defined handler.	*/
	boost::asio::ip::udp::socket    _sock;		/**< Link SAP socket.		*/
	boost::asio::ip::udp::endpoint  _ep;		/**< Local MIHF endpoint.	*/
	odtone::mih::id                 _link_id;	/**< Link SAP MIH ID.		*/
	odtone::mih::id                 _mihf_id;	/**< Local MIHF ID. 		*/
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace sap */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_SAP_LINK__HPP_ */
