//=============================================================================
// Brief   : MIH Message
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
 * MIH Message
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
 * odtone::mih::response, odtone::mih::indication, odtone::mih::confirm,
 * odtone::mih::tlv_fwd) and operator overloading. This basicaly defines a mini
 * DSL for parsing and generating MIH messages.
 *
 * Examples:
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
	/**
	* Construct a default MIH Message.
	*
	* The defaults for each field are:
	*    version = 1;
	*    ackreq  = false;
	*    ackrsp  = false;
	*    uir     = false;
	*    m       = false;
	*    fn      = 0;
	*    mid     = 0;
	*    tid     = 0;
	*/
	message();

	/**
	 * Construct a MIH Message parsing all fields from a frame.
	 *
	 * @param fm odtone::mih::frame from which to parse information.
	 */
	message(const frame& fm);

	/**
	 * Destruct a MIH Message.
	 */
	~message();

	/**
	 * Extract the MIH Message fields from a given odtone::mih::frame.
	 *
	 * @param fm odtone::mih::frame from which to extract information.
	 * @return odtone::mih::message with the fields updated.
	 */
	message& operator=(const frame& fm);

	/**
	 * Set the MIH Message Version.
	 *
	 * @param v value of MIH Message Version field.
	 */
	void version(uint8 v);

	/**
	 * Set the MIH Message Acknowledge Request Flag.
	 *
	 * @param v value of MIH Message Acknowledge Request Flag field.
	 */
	void ackreq(bool v);

	/**
	 * Set the MIH Message Acknowledge Response Flag.
	 *
	 * @param v value of MIH Message Acknowledge Response Flag field.
	 */
	void ackrsp(bool v);

	/**
	 * Set the MIH Message Unauthenticated Information Request Flag.
	 *
	 * @param v value of MIH Message Unauthenticated Information Request Flag.
	 */
	void uir(bool v);

	/**
	 * Set the MIH Message More Fragment Flag.
	 *
	 * @param v value of MIH Message More Fragment Flag.
	 */
	void m(bool v);

	/**
	 * Set the MIH Message Fragment Number.
	 *
	 * @param v value of MIH Message Fragment Number.
	 */
	void fn(uint8 v);

	/**
	 * Set the MIH Message ID Service Identifier.
	 *
	 * @param v value of MIH Message ID Service Identifier (odtone::mih::service::type).
	 */
	void sid(service::type v);

	/**
	 * Set the MIH Message ID Operation Code.
	 *
	 * @param v value of MIH Message ID Operation Code (odtone::mih::operation::type).
	 */
	void opcode(operation::type v);

	/**
	 * Set the MIH Message ID Action Identifier.
	 *
	 * @param v value of MIH Message ID Action Identifier (odtone::mih::action::type).
	 */
	void aid(action::type v);

	/**
	 * Set the MIH Message ID.
	 *
	 * @param v value of MIH Message Message ID.
	 */
	void mid(uint16 v);

	/**
	 * Set the MIH Message Transaction ID.
	 *
	 * @param v value of MIH Message Transaction ID.
	 */
	void tid(uint16 v);

	/**
	 * Set the MIH Message Source ID.
	 *
	 * @param v MIH Message Source MIHF ID.
	 */
	void source(const id& id);

	/**
	 * Set the MIH Message Destination ID.
	 *
	 * @param v MIH Message Destination MIHF ID.
	 */
	void destination(const id& id);

	/**
	 * Get the MIH Message Version.
	 *
	 * @return Value of MIH Message Version field.
	 */
	uint8 version() const;

	/**
	 * Get the MIH Message Acknowledge Request Flag.
	 *
	 * @return Value of MIH Message Acknowledge Request Flag.
	 */
	bool ackreq() const;

	/**
	 * Get the MIH Message Acknowledge Response Flag.
	 *
	 * @return Value of MIH Message Acknowledge Response Flag field.
	 */
	bool ackrsp() const;

	/**
	 * Get the MIH Message Unauthenticated Information Request Flag.
	 *
	 * @return Value of MIH Message Unauthenticated Information Request Flag.
	 */
	bool uir() const;

	/**
	 * Get the MIH Message More Fragment Flag.
	 *
	 * @return Value of MIH Message More Fragment Flag.
	 */
	bool m() const;

	/**
	 * Get the MIH Message Fragment Number.
	 *
	 * @return Value of MIH Message Fragment Number.
	 */
	uint8 fn() const;

	/**
	 * Get the MIH Message ID Service Identifier.
	 *
	 * @return Value of MIH Message ID Service Identifier (odtone::mih::service::type).
	 */
	service::type sid() const;

	/**
	 * Get the MIH Message ID Operation Code.
	 *
	 * @return Value of MIH Message ID Operation Code (odtone::mih::operation::type).
	 */
	operation::type opcode() const;

	/**
	 * Get the MIH Message ID Action Identifier.
	 *
	 * @return Value of MIH Message ID Action Identifier (odtone::mih::action::type).
	 */
	action::type aid() const;

	/**
	 * Get the MIH Message ID.
	 *
	 * @return Value of MIH Message ID.
	 */
	uint16 mid() const;

	/**
	 * Get the MIH Message Transaction ID.
	 *
	 * @return Value of MIH Message Transaction ID.
	 */
	uint16 tid() const;

	/**
	 * Get the MIH Message Source ID.
	 *
	 * @return MIH Message Source MIHF ID.
	 */
	const id&       source() const;

	/**
	 * Get the MIH Message Destination ID.
	 *
	 * @return MIH Message Destination MIHF ID.
	 */
	const id&       destination() const;

	/**
	 * Get the input archive (odtone::mih::iarchive).
	 *
	 * @return The input archive (odtone::mih::iarchive).
	 */
	iarchive& input();

	/**
	 * Get the output archive (odtone::mih::oarchive).
	 *
	 * @return The output archive (odtone::mih::oarchive).
	 */
	oarchive& output() { return _out; }

	/**
	 * Get the MIH Message Frame (odtone::mih::frame).
	 *
	 * @param fm a dynamic frame buffer to fill.
	 */
	void get_frame(frame_vla& fm) const;

	/**
	 * Check if the MIH Message has service specific TLVs
	 *
	 * @return true if has service specific TLVs or false otherwise.
	 */
	bool has_service_specific_tlv();

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
	iarchive        _in;
	oarchive        _out;
};

/**
 * Set the MIH Message Version.
 *
 * @param v value of MIH Message Version field.
 */
inline void message::version(uint8 v)
{
	_version = v;
}

/**
 * Set the MIH Message Acknowledge Request Flag.
 *
 * @param v value of MIH Message Acknowledge Request Flag field.
 */
inline void message::ackreq(bool v)
{
	_ackreq = v;
}

/**
 * Set the MIH Message Acknowledge Response Flag.
 *
 * @param v value of MIH Message Acknowledge Response Flag field.
 */
inline void message::ackrsp(bool v)
{
	_ackrsp = v;
}

/**
 * Set the MIH Message Unauthenticated Information Request Flag.
 *
 * @param v value of MIH Message Unauthenticated Information Request Flag.
 */
inline void message::uir(bool v)
{
	_uir = v;
}

/**
 * Set the MIH Message More Fragment Flag.
 *
 * @param v value of MIH Message More Fragment Flag.
 */
inline void message::m(bool v)
{
	_m = v;
}

/**
 * Set the MIH Message Fragment Number.
 *
 * @param v value of MIH Message Fragment Number.
 */
inline void message::fn(uint8 v)
{
	_fn = v;
}

/**
 * Set the MIH Message ID Service Identifier.
 *
 * @param v value of MIH Message ID Service Identifier (odtone::mih::service::type).
 */
inline void message::sid(service::type v)
{
	_mid = (_mid & 0x0fff) | (v << 12);
}

/**
 * Set the MIH Message ID Operation Code.
 *
 * @param v value of MIH Message ID Operation Code (odtone::mih::operation::type).
 */
inline void message::opcode(operation::type v)
{
	_mid = (_mid & 0xf3ff) | (v << 10);
}

/**
 * Set the MIH Message ID Action Identifier.
 *
 * @param v value of MIH Message ID Action Identifier (odtone::mih::action::type).
 */
inline void message::aid(action::type v)
{
	_mid = (_mid & 0xfc00) | v;
}

/**
 * Set the MIH Message ID.
 *
 * @param v value of MIH Message Message ID.
 */
inline void message::mid(uint16 v)
{
	_mid = v;
}

/**
 * Set the MIH Message Transaction ID.
 *
 * @param v value of MIH Message Transaction ID.
 */
inline void message::tid(uint16 v)
{
	_tid = v;
}

/**
 * Set the MIH Message Source ID.
 *
 * @param v MIH Message Source MIHF ID.
 */
inline void message::source(const id& id)
{
	_src = id;
}

/**
 * Set the MIH Message Destination ID.
 *
 * @param v MIH Message Destination MIHF ID.
 */
inline void message::destination(const id& id)
{
	_dst = id;
}

/**
 * Get the MIH Message Version.
 *
 * @return Value of MIH Message Version field.
 */
inline uint8 message::version() const
{
	return _version;
}

/**
 * Get the MIH Message Acknowledge Request Flag.
 *
 * @return Value of MIH Message Acknowledge Request Flag.
 */
inline bool message::ackreq() const
{
	return _ackreq;
}

/**
 * Get the MIH Message Acknowledge Response Flag.
 *
 * @return Value of MIH Message Acknowledge Response Flag field.
 */
inline bool message::ackrsp() const
{
	return _ackrsp;
}

/**
 * Get the MIH Message Unauthenticated Information Request Flag.
 *
 * @return Value of MIH Message Unauthenticated Information Request Flag.
 */
inline bool message::uir() const
{
	return _uir;
}

/**
 * Get the MIH Message More Fragment Flag.
 *
 * @return Value of MIH Message More Fragment Flag.
 */
inline bool message::m() const
{
	return _m;
}

/**
 * Get the MIH Message Fragment Number.
 *
 * @return Value of MIH Message Fragment Number.
 */
inline uint8 message::fn() const
{
	return _fn;
}

/**
 * Get the MIH Message ID Service Identifier.
 *
 * @return Value of MIH Message ID Service Identifier (odtone::mih::service::type).
 */
inline service::type message::sid() const
{
	return service::type((_mid & 0xf000) >> 12);
}

/**
 * Get the MIH Message ID Operation Code.
 *
 * @return Value of MIH Message ID Operation Code (odtone::mih::operation::type).
 */
inline operation::type message::opcode() const
{
	return operation::type((_mid & 0x0c00) >> 10);
}

/**
 * Get the MIH Message ID Action Identifier.
 *
 * @return Value of MIH Message ID Action Identifier (odtone::mih::action::type).
 */
inline action::type message::aid() const
{
	return action::type(_mid & 0x03ff);
}

/**
 * Get the MIH Message ID.
 *
 * @return Value of MIH Message ID.
 */
inline uint16 message::mid() const
{
	return _mid;
}

/**
 * Get the MIH Message Transaction ID.
 *
 * @return Value of MIH Message Transaction ID.
 */
inline uint16 message::tid() const
{
	return _tid;
}

/**
 * Get the MIH Message Source ID.
 *
 * @return MIH Message Source MIHF ID.
 */
inline const id& message::source() const
{
	return _src;
}

/**
 * Get the MIH Message Destination ID.
 *
 * @return MIH Message Destination MIHF ID.
 */
inline const id& message::destination() const
{
	return _dst;
}

/**
 * Get the input archive (odtone::mih::iarchive).
 *
 * @return The input archive (odtone::mih::iarchive).
 */
inline iarchive& message::input()
{
	_in.reset(_payload);
	return _in;
}

///////////////////////////////////////////////////////////////////////////////
/**
 * Parsing/Generating MIH messages is done with helper classes
 * (odtone::mih::request, odtone::mih::response, odtone::mih::indication,
 * odtone::mih::confirm) and operator overloading.
 * This will be the base class to odtone::mih::request, odtone::mih::response,
 * odtone::mih::indication and odtone::mih::confirm, as is documented later in
 * this document.
 *
 * This class derive from boost::noncopyable in order to prohibit copy construction
 * and copy assignment. Thus, odtone::mih::message_helper class has protected
 * constructor and destructor members and should be used only as a base class.
 */
class message_helper : boost::noncopyable {
protected:
	/**
	 * Construct a MIH Message helper.
	 *
	 * @param mid value of MIH Message ID.
	 * @param dst MIH Message Destination MIHF ID.
	 */
	message_helper(uint16 mid, const id* dst) : _mid(mid), _dst(dst)
	{ }

	/**
	 * Serialize parameters to an MIH Message
	 *
	 * @param msg destination odtone::mih::message
	 * @param mh message helper
	 * @return output TLV archive
	 */
	friend oarchive& operator<<(message& msg, const message_helper& mh);

	/**
	 * Deserialize parameters from an MIH Message
	 * @param msg destination odtone::mih::message
	 * @param mh message helper
	 * @return input TLV archive
	 */
	friend iarchive& operator>>(message& msg, const message_helper& mh);

private:
	uint16    _mid;
	const id* _dst;
};

/**
 * Serialize parameters to an MIH Message
 *
 * @param msg destination odtone::mih::message
 * @param mh message helper
 * @return output TLV archive
 */
inline oarchive& operator<<(message& msg, const message_helper& mh)
{
	msg.mid(mh._mid);
	if (mh._dst)
		msg.destination(*mh._dst);

	return msg.output();
}

/**
 * Deserialize parameters from an MIH Message
 * @param msg destination odtone::mih::message
 * @param mh message helper
 * @return input TLV archive
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
