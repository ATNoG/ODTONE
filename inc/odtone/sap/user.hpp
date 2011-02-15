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

static const char* const kConf_File               = "conf.file";
static const char* const kConf_Port               = "conf.port";
static const char* const kConf_Receive_Buffer_Len = "conf.recv_buff_len";

static const char* const kConf_MIH_Handover = "user.handover";

static const char* const kConf_MIH_SAP_id   = "user.id";
static const char* const kConf_MIH_SAP_dest = "dest";

static const char* const kConf_MIHF_Id         = "mihf.id";
static const char* const kConf_MIHF_Ip         = "mihf.ip";
static const char* const kConf_MIHF_Local_Port = "mihf.local_port";

///////////////////////////////////////////////////////////////////////////////
/**
 * User SAP IO Service
 *
 * This module handles the comunication between User SAP implementations and
 * the MIHF. After being initialized it must be running by invoking the run()
 * method of the provided boost::asio::io_service.
 */
class user : public sap {
	typedef boost::function<void(mih::message& pm, const boost::system::error_code&)> handler;
	typedef std::map<uint, handler> rmap;

public:
	/**
	 * Construct an User SAP IO Service.
	 *
	 * @param  cfg configuration with the parameters for MIH User port, MIHF ip:port and receive buffer size.
	 * @param  io generic IO service.
	 * @param  h handler callback as a function pointer/object. The handler callback is invoked when an message is received, offering a simple way to process incoming messages. The signature of the callback is: void(odtone::mih::message&, const boost::system::error_code&).
	 * @throws boost::system::error_code
	 */
	user(const mih::config& cfg, boost::asio::io_service& io, const handler& h);

	/**
	 * Destruct an User SAP IO Service.
	 */
	~user();

	/**
	 * Send the MIH message to the local MIHF asynchronously.
	 * After the message is sended, the callback is called with the
	 * response message or to report failure in delivering the message
	 * to the MIHF.This method retuns immediately.
	 *
	 * @param msg MIH message to send.
	 * @param h Completion/Response callback handler as a function pointer/object.
	 */
	void async_send(mih::message& pm, const handler& h);

	/**
	 * Send the MIH message to the local MIHF synchronously.
	 * After the message is sent, the callback is called to report
	 * the success or failure in delivering the message to the MIHF. This method retuns immediately.
	 *
	 * @param msg MIH message to send
	 * @param h Completion callback handler as a function pointer/object
	 */
	void sync_send(mih::message& msg);

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
	void send_handler(mih::frame_vla& fm, size_t sbytes, const boost::system::error_code& ec);

private:
	handler                        _handler;
	boost::asio::ip::udp::socket   _sock;
	mih::id                        _id;
	boost::asio::ip::udp::endpoint _ep;
	odtone::mih::id                _user_id;
	odtone::mih::id                _mihf_id;
	bool                           handover;

	boost::mutex _mutex;
	rmap         _rmap;
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace sap */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_SAP_USER__HPP_ */
