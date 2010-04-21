//=============================================================================
// Brief   : MIH Message
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

#ifndef ODTONE_MIH_MESSAGE__HPP_
#define ODTONE_MIH_MESSAGE__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/mih/frame.hpp>
#include <odtone/mih/archive.hpp>
#include <odtone/mih/types/identification.hpp>
#include <boost/utility.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
template<uint ServiceId, uint Opcode, uint ActionId>
struct msg_id {
	static const uint16 value = ((ServiceId << 12) | (Opcode << 10) | ActionId);
};

///////////////////////////////////////////////////////////////////////////////
/**
 * \brief MIH Message

 *
 * The odtone::mih::message is high level representation of an MIH message, it
 * provides access to all fields of the MIH message header, the destination and
 * sources ID's that is part of payload but common to all messages, and also
 * provides serialization/deserialization for all the other payload data types
 * (see odtone::mih::archive).
 *
 * The odtone::mih::message can be set from an odtone::mih::frame that was
 * received or it can create an odtone::mih::frame ready to be sended.
 * To send or receive MIH message frames an IO Service is required such as the
 * odtone::sap::user and odtone::sap::link.
 *
 * Parsing/Generating MIH messages is done with helper classes (odtone::mih::request,
 * odtone::mih::response, odtone::mih::indication, odtone::mih::tlv_fwd) and operator
 * overloading. This basicaly defines a mini DSL for parsing and generating MIH
 * messages.
 *
 *
 * \b Examples:
 *
 * To generate and send a MIH message:
 * \code
 * odtone::mih::message msg;
 * odtone::mih::link_tuple_id li;
 * odtone::mih::event_list evts;
 *
 * //...
 *
 * msg << odtone::mih::request(odtone::mih::request::event_subscribe)
 *     & odtone::mih::tlv_link_identifier(li)
 *     & odtone::mih::tlv_event_list(evts);
 *
 * io_service.async_send(msg, &event_subscribe_response_handler);
 * \endcode
 *
 * Notice that we start with the message and then we use the operator << to
 * begin the generation of the message, followed by on of the message_helper
 * classes (odtone::mih::request, odtone::mih::response, odtone::mih::indication)
 * and then we can pass the parameters starting with the operator & followed by
 * the tlv_fwd helper classes.
 *
 *
 * To receive and parse a MIH message:
 * \code
 *     //...
 *
 *     msg << odtone::mih::request(odtone::mih::request::capability_discover);
 *
 *     user_sap_ios.async_send(msg, &capability_discover_response);
 *
 *     //...
 *
 * void capability_discovery_response(odtone::mih::message& msg, const boost::system::error_code& ec)
 * {
 *     if (ec) {
 *         // do something with the error and don't parse the msg or else,
 *         // an iarchive_eof_error exception is thrown
 *
 *         return;
 *     }
 *
 *     odtone::mih::status st;
 *     boost::optional<odtone::mih::net_type_addr_list> ntal;
 *     boost::optional<odtone::mih::event_list> evt;
 *
 *     msg >> odtone::mih::response()
 *         & odtone::mih::tlv_status(st)
 *         & odtone::mih::tlv_net_type_addr_list(ntal)
 *         & odtone::mih::tlv_event_list(evt);
 *
 *     //...
 * }
 * \endcode
 *
 * In this case, to begin parsing we use operator >>. Everything else is
 * similar to generating a message.
 *
 * Notice that we warp the MIH types with \a boost::optional to get optional
 * parameters!
 */
class message : boost::noncopyable {
public:
	message();
	message(const frame& fm);
	~message();

	message& operator=(const frame& fm);

	void version(uint8 v);
	void ackreq(bool v);
	void ackrsp(bool v);
	void uir(bool v);
	void m(bool v);
	void fn(uint8 v);
	void sid(service::type v);
	void opcode(operation::type v);
	void aid(action::type v);
	void mid(uint16 v);
	void tid(uint16 v);
	void source(const id& id);
	void destination(const id& id);

	uint8           version() const;
	bool            ackreq() const;
	bool            ackrsp() const;
	bool            uir() const;
	bool            m() const;
	uint8           fn() const;
	service::type   sid() const;
	operation::type opcode() const;
	action::type    aid() const;
	uint16          mid() const;
	uint16          tid() const;
	const id&       source() const;
	const id&       destination() const;

	iarchive& input()  { return _payload.input(); }
	oarchive& output() { return _payload.output(); }

	void get_frame(frame_vla& fm) const;

private:
	uint8           _version;
	bool            _ackreq : 1;
	bool            _ackrsp : 1;
	bool            _uir : 1;
	bool            _m : 1;
	uint8           _fn;
	uint16          _mid;
	uint16          _tid;
	id              _src;
	id              _dst;
	mutable archive _payload;
};

/**
 * \brief Set the MIH Message Version
 */
inline void message::version(uint8 v)
{
	_version = v;
}

/**
 * \brief Set the MIH Message Acknowledge Request Flag
 */
inline void message::ackreq(bool v)
{
	_ackreq = v;
}

/**
 * \brief Set the MIH Message Acknowledge Response Flag
 */
inline void message::ackrsp(bool v)
{
	_ackrsp = v;
}

/**
 * \brief Set the MIH Message Unauthenticated Information Request Flag
 */
inline void message::uir(bool v)
{
	_uir = v;
}

/**
 * \brief Set the MIH Message More Fragment Flag
 */
inline void message::m(bool v)
{
	_m = v;
}

/**
 * \brief Set the MIH Message Fragment Number
 */
inline void message::fn(uint8 v)
{
	_fn = v;
}

/**
 * \brief Set the MIH Message ID Service Identifier
 */
inline void message::sid(service::type v)
{
	_mid = (_mid & 0x0fff) | (v << 12);
}

/**
 * \brief Set the MIH Message ID Operation Code
 */
inline void message::opcode(operation::type v)
{
	_mid = (_mid & 0xf3ff) | (v << 10);
}

/**
 * \brief Set the MIH Message ID Action Identifier
 */
inline void message::aid(action::type v)
{
	_mid = (_mid & 0xfc00) | v;
}

/**
 * \brief Set the MIH Message ID
 */
inline void message::mid(uint16 v)
{
	_mid = v;
}

/**
 * \brief Set the MIH Message Transaction ID
 */
inline void message::tid(uint16 v)
{
	_tid = v;
}

/**
 * \brief Set the MIH Message Source ID
 */
inline void message::source(const id& id)
{
	_src = id;
}

/**
 * \brief Set the MIH Message Destination ID
 */
inline void message::destination(const id& id)
{
	_dst = id;
}

/**
 * \brief Get the MIH Message Version
 */
inline uint8 message::version() const
{
	return _version;
}

/**
 * \brief Get the MIH Message Acknowledge Request Flag
 */
inline bool message::ackreq() const
{
	return _ackreq;
}

/**
 * \brief Get the MIH Message Acknowledge Response Flag
 */
inline bool message::ackrsp() const
{
	return _ackrsp;
}

/**
 * \brief Get the MIH Message Unauthenticated Information Request Flag
 */
inline bool message::uir() const
{
	return _uir;
}

/**
 * \brief Get the MIH Message More Fragment Flag
 */
inline bool message::m() const
{
	return _m;
}

/**
 * \brief Get the MIH Message Fragment Number
 */
inline uint8 message::fn() const
{
	return _fn;
}

/**
 * \brief Get the MIH Message ID Service Identifier
 */
inline service::type message::sid() const
{
	return service::type((_mid & 0xf000) >> 12);
}

/**
 * \brief Get the MIH Message ID Operation Code
 */
inline operation::type message::opcode() const
{
	return operation::type((_mid & 0x0c00) >> 10);
}

/**
 * \brief Get the MIH Message ID Action Identifier
 */
inline action::type message::aid() const
{
	return action::type(_mid & 0x03ff);
}

/**
 * \brief Get the MIH Message ID
 */
inline uint16 message::mid() const
{
	return _mid;
}

/**
 * \brief Get the MIH Message Transaction ID
 */
inline uint16 message::tid() const
{
	return _tid;
}

/**
 * \brief Get the MIH Message Source ID
 */
inline const id& message::source() const
{
	return _src;
}

/**
 * \brief Get the MIH Message Destination ID
 */
inline const id& message::destination() const
{
	return _dst;
}

///////////////////////////////////////////////////////////////////////////////
class message_helper : boost::noncopyable {
protected:
	message_helper(uint16 mid, const id* dst) : _mid(mid), _dst(dst)
	{ }

	friend oarchive& operator<<(message& msg, const message_helper& mh);
	friend iarchive& operator>>(message& msg, const message_helper& mh);

private:
	uint16    _mid;
	const id* _dst;
};

/**
 * \brief Serialize parameters to an MIH Message
 * \param msg destination odtone::mih::message
 * \param mh message helper
 * \return output TLV archive
 */
inline oarchive& operator<<(message& msg, const message_helper& mh)
{
	msg.mid(mh._mid);
	if (mh._dst)
		msg.destination(*mh._dst);

	return msg.output();
}

/**
 * \brief Deserialize parameters from an MIH Message
 * \param msg destination odtone::mih::message
 * \param mh message helper
 * \return input TLV archive
 */
inline iarchive& operator>>(message& msg, const message_helper& mh)
{
	ODTONE_ASSERT(mh._mid == msg.mid() || !mh._mid);
	ODTONE_ASSERT(mh._dst == nullptr);

	return msg.input();
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_MESSAGE__HPP_ */
