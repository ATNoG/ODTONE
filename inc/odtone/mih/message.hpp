//=============================================================================
// Brief   : MIH Message
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
/**
 * Message Identifier (MID) data type.
 */
template<uint ServiceId, uint Opcode, uint ActionId>
struct msg_id {
	static const uint16 value = ((ServiceId << 12) | (Opcode << 10) | ActionId);
};

///////////////////////////////////////////////////////////////////////////////
/**
 * MIH Message.
 *
 * This class is a high level representation of an MIH message. It
 * provides access to all fields of the MIH message header, the destination and
 * sources ID's (which is part of payload but common to all messages), and it 
 * also provides serialization/deserialization operations.
 */
class message : boost::noncopyable {
public:
	/**
	 * Construct an empty MIH Message.
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
	 * Construct a MIH Message by extracting the data from a frame.
	 *
	 * @param fm The frame from which extract the information.
	 */
	message(const frame& fm);

	/**
	 * Destruct a MIH Message.
	 */
	~message();

	/**
	 * Extract the message data from a frame.
	 *
	 * @param fm The frame from which extract the information.
	 * @return The message with updated data.
	 */
	message& operator=(const frame& fm);

	/**
	 * Clear the payload.
	 */
	void reset()
	{
		_payload.clear();
		_in.reset(_payload);
		_out.reset(_payload);
	}

	/**
	 * Set the MIH Message Version.
	 *
	 * @param v The value of the MIH Message Version field.
	 */
	void version(uint8 v);

	/**
	 * Set the MIH Message Acknowledge Request Flag.
	 *
	 * @param v The value of the MIH Message Acknowledge Request Flag field.
	 */
	void ackreq(bool v);

	/**
	 * Set the MIH Message Acknowledge Response Flag.
	 *
	 * @param v The value of the MIH Message Acknowledge Response Flag field.
	 */
	void ackrsp(bool v);

	/**
	 * Set the MIH Message Unauthenticated Information Request Flag.
	 *
	 * @param v The value of the MIH Message Unauthenticated Information Request Flag.
	 */
	void uir(bool v);

	/**
	 * Set the MIH Message More Fragment Flag.
	 *
	 * @param v The value of the MIH Message More Fragment Flag.
	 */
	void m(bool v);

	/**
	 * Set the MIH Message Fragment Number.
	 *
	 * @param v The value of the MIH Message Fragment Number.
	 */
	void fn(uint8 v);

	/**
	 * Set the MIH Message ID Service Identifier.
	 *
	 * @param v The value of the MIH Message ID Service Identifier.
	 */
	void sid(service::type v);

	/**
	 * Set the MIH Message ID Operation Code.
	 *
	 * @param v The value of the MIH Message ID Operation Code.
	 */
	void opcode(operation::type v);

	/**
	 * Set the MIH Message ID Action Identifier.
	 *
	 * @param v The value of the MIH Message ID Action Identifier.
	 */
	void aid(action::type v);

	/**
	 * Set the MIH Message ID.
	 *
	 * @param v The value of the MIH Message Message ID.
	 */
	void mid(uint16 v);

	/**
	 * Set the MIH Message Transaction ID.
	 *
	 * @param v The value of the MIH Message Transaction ID.
	 */
	void tid(uint16 v);

	/**
	 * Set the MIH Message Source ID.
	 *
	 * @param id The value of the MIH Message Source MIHF ID.
	 */
	void source(const id& id);

	/**
	 * Set the MIH Message Destination ID.
	 *
	 * @param id The value of the MIH Message Destination MIHF ID.
	 */
	void destination(const id& id);

	/**
	 * Set the message payload by copying it from another message.
	 * @note The source and destination TLVs are not copied.
	 *
	 * @param msg The message from which extract the payload.
	 */
	void payload(const message& msg);

	/**
	 * Get the MIH Message Version.
	 *
	 * @return The value of the MIH Message Version field.
	 */
	uint8 version() const;

	/**
	 * Get the MIH Message Acknowledge Request Flag.
	 *
	 * @return The value of the MIH Message Acknowledge Request Flag.
	 */
	bool ackreq() const;

	/**
	 * Get the MIH Message Acknowledge Response Flag.
	 *
	 * @return The value of the MIH Message Acknowledge Response Flag field.
	 */
	bool ackrsp() const;

	/**
	 * Get the MIH Message Unauthenticated Information Request Flag.
	 *
	 * @return The value of the MIH Message Unauthenticated Information Request Flag.
	 */
	bool uir() const;

	/**
	 * Get the MIH Message More Fragment Flag.
	 *
	 * @return The value of the MIH Message More Fragment Flag.
	 */
	bool m() const;

	/**
	 * Get the MIH Message Fragment Number.
	 *
	 * @return The value of the MIH Message Fragment Number.
	 */
	uint8 fn() const;

	/**
	 * Get the MIH Message ID Service Identifier.
	 *
	 * @return The value of the MIH Message ID Service Identifier.
	 */
	service::type sid() const;

	/**
	 * Get the MIH Message ID Operation Code.
	 *
	 * @return The value of the MIH Message ID Operation Code.
	 */
	operation::type opcode() const;

	/**
	 * Get the MIH Message ID Action Identifier.
	 *
	 * @return The value of the MIH Message ID Action Identifier.
	 */
	action::type aid() const;

	/**
	 * Get the MIH Message ID.
	 *
	 * @return The value of the MIH Message ID.
	 */
	uint16 mid() const;

	/**
	 * Get the MIH Message Transaction ID.
	 *
	 * @return The value of the MIH Message Transaction ID.
	 */
	uint16 tid() const;

	/**
	 * Get the MIH Message Source ID.
	 *
	 * @return The value of the MIH Message Source MIHF ID.
	 */
	const id& source() const;

	/**
	 * Get the MIH Message Destination ID.
	 *
	 * @return The value of the MIH Message Destination MIHF ID.
	 */
	const id& destination() const;

	/**
	 * Get the message's input archive.
	 *
	 * @return The message's input archive.
	 */
	iarchive& input();

	/**
	 * Get the message's output archive.
	 *
	 * @return The message's output archive.
	 */
	oarchive& output()
	{
		return _out;
	}

	/**
	 * Get the MIH Message Frame.
	 *
	 * @param fm A dynamic frame buffer to store the information.
	 */
	void get_frame(frame_vla& fm) const;

	/**
	 * Check if the MIH Message has service specific TLVs
	 *
	 * @return True if has service specific TLVs or false otherwise.
	 */
	bool has_service_specific_tlv();

protected:
	uint8           _version;		/**< MIH Message Version.				*/
	bool            _ackreq : 1;	/**< MIH Message Acknowledge Request Flag.*/
	bool            _ackrsp : 1;	/**< MIH Message Acknowledge Response Flag.*/
	bool            _uir : 1;		/**< MIH Message Unauthenticated Information Request Flag.*/
	bool            _m : 1;			/**< MIH Message More Fragments Flag.	*/
	uint8           _fn;			/**< MIH Message Fragment Number.		*/
	uint16          _mid;			/**< MIH Message ID.					*/
	uint16          _tid;			/**< MIH Message Transaction ID.		*/
	id              _src;			/**< MIH Message Source MIHF ID.		*/
	id              _dst;			/**< MIH Message Destination MIHF ID.	*/
	mutable archive _payload;		/**< MIH message payload.				*/
	iarchive        _in;			/**< Input archive.						*/
	oarchive        _out;			/**< Output archive.					*/
};

/**
 * Set the MIH Message Version.
 *
 * @param v The value of the MIH Message Version field.
 */
inline void message::version(uint8 v)
{
	_version = v;
}

/**
 * Set the MIH Message Acknowledge Request Flag.
 *
 * @param v The value of the MIH Message Acknowledge Request Flag field.
 */
inline void message::ackreq(bool v)
{
	_ackreq = v;
}

/**
 * Set the MIH Message Acknowledge Response Flag.
 *
 * @param v The value of the MIH Message Acknowledge Response Flag field.
 */
inline void message::ackrsp(bool v)
{
	_ackrsp = v;
}

/**
 * Set the MIH Message Unauthenticated Information Request Flag.
 *
 * @param v The value of the MIH Message Unauthenticated Information Request Flag.
 */
inline void message::uir(bool v)
{
	_uir = v;
}

/**
 * Set the MIH Message More Fragment Flag.
 *
 * @param v The value of the MIH Message More Fragment Flag.
 */
inline void message::m(bool v)
{
	_m = v;
}

/**
 * Set the MIH Message Fragment Number.
 *
 * @param v The value of the MIH Message Fragment Number.
 */
inline void message::fn(uint8 v)
{
	_fn = v;
}

/**
 * Set the MIH Message ID Service Identifier.
 *
 * @param v The value of the MIH Message ID Service Identifier.
 */
inline void message::sid(service::type v)
{
	_mid = (_mid & 0x0fff) | (v << 12);
}

/**
 * Set the MIH Message ID Operation Code.
 *
 * @param v The value of the MIH Message ID Operation Code.
 */
inline void message::opcode(operation::type v)
{
	_mid = (_mid & 0xf3ff) | (v << 10);
}

/**
 * Set the MIH Message ID Action Identifier.
 *
 * @param v The value of the MIH Message ID Action Identifier.
 */
inline void message::aid(action::type v)
{
	_mid = (_mid & 0xfc00) | v;
}

/**
 * Set the MIH Message ID.
 *
 * @param v The value of the MIH Message Message ID.
 */
inline void message::mid(uint16 v)
{
	_mid = v;
}

/**
 * Set the MIH Message Transaction ID.
 *
 * @param v The value of the MIH Message Transaction ID.
 */
inline void message::tid(uint16 v)
{
	_tid = v;
}

/**
 * Set the MIH Message Source ID.
 *
 * @param id The value of the MIH Message Source MIHF ID.
 */
inline void message::source(const id& id)
{
	_src = id;
}

/**
 * Set the MIH Message Destination ID.
 *
 * @param id The value of the MIH Message Destination MIHF ID.
 */
inline void message::destination(const id& id)
{
	_dst = id;
}

/**
 * Get the MIH Message Version.
 *
 * @return The value of the MIH Message Version field.
 */
inline uint8 message::version() const
{
	return _version;
}

/**
 * Get the MIH Message Acknowledge Request Flag.
 *
 * @return The value of the MIH Message Acknowledge Request Flag.
 */
inline bool message::ackreq() const
{
	return _ackreq;
}

/**
 * Get the MIH Message Acknowledge Response Flag.
 *
 * @return The value of the MIH Message Acknowledge Response Flag field.
 */
inline bool message::ackrsp() const
{
	return _ackrsp;
}

/**
 * Get the MIH Message Unauthenticated Information Request Flag.
 *
 * @return The value of the MIH Message Unauthenticated Information Request Flag.
 */
inline bool message::uir() const
{
	return _uir;
}

/**
 * Get the MIH Message More Fragment Flag.
 *
 * @return The value of the MIH Message More Fragment Flag.
 */
inline bool message::m() const
{
	return _m;
}

/**
 * Get the MIH Message Fragment Number.
 *
 * @return The value of the MIH Message Fragment Number.
 */
inline uint8 message::fn() const
{
	return _fn;
}

/**
 * Get the MIH Message ID Service Identifier.
 *
 * @return The value of the MIH Message ID Service Identifier.
 */
inline service::type message::sid() const
{
	return service::type((_mid & 0xf000) >> 12);
}

/**
 * Get the MIH Message ID Operation Code.
 *
 * @return The value of the MIH Message ID Operation Code.
 */
inline operation::type message::opcode() const
{
	return operation::type((_mid & 0x0c00) >> 10);
}

/**
 * Get the MIH Message ID Action Identifier.
 *
 * @return The value of the MIH Message ID Action Identifier.
 */
inline action::type message::aid() const
{
	return action::type(_mid & 0x03ff);
}

/**
 * Get the MIH Message ID.
 *
 * @return The value of the MIH Message ID.
 */
inline uint16 message::mid() const
{
	return _mid;
}

/**
 * Get the MIH Message Transaction ID.
 *
 * @return The value of the MIH Message Transaction ID.
 */
inline uint16 message::tid() const
{
	return _tid;
}

/**
 * Get the MIH Message Source ID.
 *
 * @return The value of the MIH Message Source MIHF ID.
 */
inline const id& message::source() const
{
	return _src;
}

/**
 * Get the MIH Message Destination ID.
 *
 * @return The value of the MIH Message Destination MIHF ID.
 */
inline const id& message::destination() const
{
	return _dst;
}

/**
 * Get the message's input archive.
 *
 * @return The message's input archive.
 */
inline iarchive& message::input()
{
	_payload.position(0);
	_in.reset(_payload);
	return _in;
}

///////////////////////////////////////////////////////////////////////////////
/**
 * Parsing/generating MIH messages is done using helper classes and operator
 * overloading.
 */
class message_helper : boost::noncopyable {
protected:
	/**
	 * Construct a MIH Message helper.
	 *
	 * @param mid The value of the MIH Message ID.
	 * @param dst The value of the MIH Message Destination MIHF ID.
	 */
	message_helper(uint16 mid, const id* dst) : _mid(mid), _dst(dst)
	{ }

	/**
	 * Serialize a MIH message.
	 *
	 * @param msg MIH message to where serialize the data.
	 * @param mh The message helper.
	 * @return The resulting output archive.
	 */
	friend oarchive& operator<<(message& msg, const message_helper& mh);

	/**
	 * Deserialize a MIH message.
	 *
	 * @param msg MIH message from where deserialize the data.
	 * @param mh The message helper.
	 * @return The resulting input archive.s
	 */
	friend iarchive& operator>>(message& msg, const message_helper& mh);

private:
	uint16    _mid;	/**< MIH Message ID.					*/
	const id* _dst;	/**< MIH Message Destination MIHF ID.	*/
};

/**
 * Serialize a MIH message.
 *
 * @param msg MIH message to where serialize the data.
 * @param mh The message helper.
 * @return The resulting output archive.
 */
inline oarchive& operator<<(message& msg, const message_helper& mh)
{
	msg.reset();
	msg.mid(mh._mid);
	if (mh._dst)
		msg.destination(*mh._dst);

	return msg.output();
}

/**
 * Deserialize a MIH message.
 *
 * @param msg MIH message from where deserialize the data.
 * @param mh The message helper.
 * @return The resulting input archive.
 */
inline iarchive& operator>>(message& msg, const message_helper& mh)
{
	ODTONE_ASSERT(mh._mid == msg.mid() || !mh._mid);
	ODTONE_ASSERT(!mh._dst);

	return msg.input();
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_MESSAGE__HPP_ */
