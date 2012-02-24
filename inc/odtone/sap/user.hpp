//=============================================================================
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

static const char* const kConf_MIH_SAP_id   = "user.id";
static const char* const kConf_MIH_SAP_dest = "dest";

static const char* const kConf_MIHF_Ip         = "mihf.ip";
static const char* const kConf_MIHF_Local_Port = "mihf.local_port";

///////////////////////////////////////////////////////////////////////////////
/**
 * MIH-User SAP I/O Service
 *
 * This module handles the comunication between MIH-User SAP and its local the
 * MIHF. After being initialized, and in order to run this service, it must
 * be invoked the run() method of the boost::asio::io_service associated.
 */
class user : public sap {
	typedef boost::function<void(mih::message& pm, const boost::system::error_code&)> handler;
	typedef boost::asio::ip::address ip_address;
	typedef std::map<uint, handler> rmap;

public:
	/**
	 * MIH-User SAP configurations structure.
	 */
	struct config {
		config()
			: id("user"), port(1234), mihf_address(boost::asio::ip::address_v4::loopback()),
			  mihf_port(1025), buffer_length(4096)
		{ }

		std::string id;				/**< Identifier.			*/
		uint        port;			/**< Listening port.		*/
		ip_address  mihf_address;	/**< MIHF IP address.		*/
		uint        mihf_port;		/**< MIHF listening port.	*/
		size_t      buffer_length;	/**< Receive Buffer Length.	*/
	};

	/**
	 * Construct a MIH-User SAP I/O Service.
	 * The defined callback is invoked when a request message is received
	 * The signature of the callback is:
	 * void(odtone::mih::message&, const boost::system::error_code&).
	 *
	 * @param cfg Configuration parameters.
	 * @param io The io_service object that Link SAP I/O Service will use to
	 * dispatch handlers for any asynchronous operations performed on
	 * the socket.
	 * @param h Message processing handler.
	 */
	user(const mih::config& cfg, boost::asio::io_service& io, const handler& h);

	/**
	 * Construct a MIH-User SAP I/O Service.
	 * The defined callback is invoked when a request message is received
	 * The signature of the callback is:
	 * void(odtone::mih::message&, const boost::system::error_code&).
	 *
	 * @param io The io_service object that Link SAP I/O Service will use to
	 * dispatch handlers for any asynchronous operations performed on
	 * the socket.
	 * @param h Message processing handler.
	 * @param cfg Configuration parameters.
	 */
	user(boost::asio::io_service& io, const handler& h, const config& cfg = config());

	/**
	 * Destruct a MIH-User SAP I/O Service.
	 */
	~user();

	/**
	 * Asynchronously send a MIH message to the local MIHF.
	 * After sending the message, the callback is called to report the
	 * success or failure in delivering the message to the local MIHF.
	 * This method retuns immediately.
	 *
	 * @param pm MIH message to send.
	 * @param h Response handler function.
	 */
	template<class CompletionHandler>
	void async_send(mih::message& pm, CompletionHandler h)
	{
		async_send_(pm, handler(h));
	}

private:
	/**
	 * Asynchronously send a MIH message to the local MIHF.
	 * After sending the message, the callback is called to report the
	 * success or failure in delivering the message to the local MIHF.
	 * This method retuns immediately.
	 *
	 * @param msg MIH message to send.
	 * @param h Response handler function.
	 */
	void async_send_(mih::message& msg, handler&& h);

	/**
	 * Received message callback. This function is executed to process the
	 * received messages. If this is a valid message, the message is
	 * dispatched to the handler defined by the user.
	 *
	 * @param buff Message byte buffer.
	 * @param rbytes Size of the message.
	 * @param ec Error code.
	 */
	void recv_handler(buffer<uint8>& buff, size_t rbytes, const boost::system::error_code& ec);

	/**
	 * Sent message handler. After sending the message, this function is called to
	 * report the success or failure in delivering the message to the local MIHF.
	 *
	 * @param fm MIH message sent.
	 * @param h Message handler.
	 * @param ec Error code.
	 */
	void send_handler(mih::frame_vla& fm, handler& h, const boost::system::error_code& ec);

	/**
	 * Get the message handler function of the message.
	 *
	 * @param tid Transaction ID of the message.
	 * @param h Reference to the message handler.
	 */
	void get_handler(uint tid, handler& h);

private:
	handler                        _handler;	/**< User defined handler.	*/
	boost::asio::ip::udp::socket   _sock;		/**< Link SAP socket.		*/
	boost::asio::ip::udp::endpoint _ep;			/**< Local MIHF endpoint.	*/
	odtone::mih::id                _user_id;	/**< MIH-User MIH ID.		*/

	boost::mutex _mutex;	/**< Mutex to avoid the simultaneous use of a
								 common resource. */
	rmap _rmap;				/**< Transactions map.		*/
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace sap */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_SAP_USER__HPP_ */
