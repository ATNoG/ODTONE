//=============================================================================
// Brief   : MIH Message Frame
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

#ifndef ODTONE_MIH_FRAME__HPP_
#define ODTONE_MIH_FRAME__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/debug.hpp>
#include <odtone/buffer.hpp>
#include <boost/utility.hpp>
#include <ostream>

#ifdef BOOST_MSVC
#	pragma warning(push)
#	pragma warning(disable : 4800)
#endif

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
/**
 * Service identifier (SID). It identifies the different MIH services.
 */
struct service {
	/**
	 * Service identifier enumeration.
	 */
	enum type {
		management  = 1,	/**< Management service.	*/
		event       = 2,	/**< Event service.			*/
		command     = 3,	/**< Command service.		*/
		information = 4		/**< Information service.	*/
	};
};

/**
 * Operation code (Opcode). Type of operation to be performed with respect
 * to the SID.
 */
struct operation {
	/**
	 * Operation code enumeration.
	 */
	enum type {
		confirm    = 0,	/**< Confirm.		*/
		request    = 1,	/**< Request.		*/
		response   = 2,	/**< Response.		*/
		indication = 3	/**< Indication.	*/
	};
};

/**
 * Action identifier (AID). This indicates the action to be taken with
 * regard to the SID.
 */
struct action {
	/**
	 * Action identifier enumeration.
	 */
	enum type {
		capability_discover = 1,	/**< Capability Discover.	*/
		mih_register        = 2,	/**< Register.				*/
		mih_deregister      = 3,	/**< De-register.			*/
		event_subscribe     = 4,	/**< Event subscribe.		*/
		event_unsubscsribe   = 5,	/**< Event unsubscribe.		*/

		link_detected          = 1,	/**< Link detected.				*/
		link_up                = 2,	/**< Link up.					*/
		link_down              = 3,	/**< Link down.					*/
		link_parameters_report = 5,	/**< Link parameters report.	*/
		link_going_down        = 6,	/**< Link going down.			*/
		link_handover_imminent = 7,	/**< Link handover imminent.	*/
		link_handover_complete = 8,	/**< Link handover complete.	*/

		link_get_parameters       = 1,	/**< Link get parameters.			*/
		link_configure_thresholds = 2,	/**< Link configure thresholds.		*/
		link_actions              = 3,	/**< Link actions.					*/
		net_ho_candidate_query    = 4,	/**< Net handover candidate query.	*/
		mn_ho_candidate_query     = 5,	/**< MN handover candidate query.	*/
		n2n_ho_query_resources    = 6,	/**< N2N handover query resources.	*/
		mn_ho_commit              = 7,	/**< MN handover commit.			*/
		net_ho_commit             = 8,	/**< Net handover commit.			*/
		n2n_ho_commit             = 9,	/**< N2N handover commit.			*/
		mn_ho_complete            = 10,	/**< MN handover complete.			*/
		n2n_ho_complete           = 11, /**< N2N handover complete.			*/

		get_information  = 1,			/**< Get information.				*/
		push_information = 2,			/**< Push information.				*/
	};
};

/**
 * MIH message frame. This class provides access to all fields of the
 * MIH message header.
 */
struct frame {
	static const uint8 mask_version = 0xf0;	/**< MIH Message Version mask.									*/
	static const uint8 mask_ackreq  = 0x08;	/**< MIH Message Acknowledge Request Flag mask.					*/
	static const uint8 mask_ackrsp  = 0x04;	/**< MIH Message Acknowledge Response Flag mask.				*/
	static const uint8 mask_uir     = 0x02;	/**< MIH Message Unauthenticated Information Request Flag mask.	*/
	static const uint8 mask_m       = 0x01;	/**< MIH Message More Fragment Flag mask.						*/
	static const uint8 mask_fn      = 0xfe;	/**< MIH Message Fragment Number mask.							*/
	static const uint8 mask_rsvd1   = 0x01;	/**< MIH Message Reserved Bit 1 mask.							*/
	static const uint8 mask_sid     = 0xf0;	/**< MIH Message ID Service Identifier mask.					*/
	static const uint8 mask_opcode  = 0x0d;	/**< MIH Message ID Operation Code mask.						*/
	static const uint8 mask_aid     = 0x03;	/**< Message ID Action Identifier mask.							*/
	static const uint8 mask_rsvd2   = 0xf0;	/**< MIH Message Reserved Bit 2 mask.							*/
	static const uint8 mask_tid     = 0xff;	/**< Message ID Transaction Identifier mask.					*/

	/**
	 * Convert a byte buffer to a frame.
	 *
	 * @param buff The byte buffer.
	 * @param len The size of the byte buffer.
	 * @return The pointer of the returning frame.
	 */
	static frame* cast(void* buff, size_t len)
	{
		frame* fm = reinterpret_cast<frame*>(buff);

		if (len < sizeof(frame) || len < fm->length())
			return nullptr;

		return fm;
	}

	/**
	 * Convert a byte buffer to a frame.
	 *
	 * @param buff The byte buffer.
	 * @param len The size of the byte buffer.
	 * @return The pointer of the returning frame.
	 */
	static const frame* cast(const void* buff, size_t len)
	{
		const frame* fm = reinterpret_cast<const frame*>(buff);

		if (len < sizeof(frame) || len < fm->length())
			return nullptr;

		return fm;
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
	 * Set the message payload length.
	 *
	 * @param v The value of the message payload length.
	 */
	void plength(uint16 v);

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
	 * Get the MIH Reserved Bit 1.
	 *
	 * @return The value of the MIH Reserved Bit 1.
	 */
	bool rsvd1() const;

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
	 * Get the MIH Reserved Bit 2.
	 *
	 * @return The value of the MIH Reserved Bit 2.
	 */
	uint8 rsvd2() const;

	/**
	 * Get the MIH Message Transaction ID.
	 *
	 * @return The value of the MIH Message Transaction ID.
	 */
	uint16 tid() const;

	/**
	 * Get the message payload length.
	 *
	 * @return The message payload length.
	 */
	uint16 plength() const;

	/**
	 * Get the pointer of the message payload.
	 *
	 * @return The pointer of the message payload.
	 */
	uint8* payload();

	/**
	 * Get the pointer of the message payload.
	 *
	 * @return The pointer of the message payload.
	 */
	const uint8* payload() const;

	/**
	 * Get the length of the frame.
	 *
	 * @return The length of the frame.
	 */
	size_t length() const;

	uint8 hdr[8];	/**< Frame bytes. */
};

typedef buffer_vla<frame> frame_vla;

/**
 * Frame output.
 *
 * @param os ostream.
 * @param fm Frame.
 * @return ostream reference.
 */
inline std::ostream& operator<<(std::ostream& os, const frame& fm)
{
	os << "mih frame: "
	   << "\n  version = " << uint(fm.version())
	   << "\n  ackreq  = " << uint(fm.ackreq())
	   << "\n  ackrsp  = " << uint(fm.ackrsp())
	   << "\n  uir     = " << uint(fm.uir())
	   << "\n  m       = " << uint(fm.m())
	   << "\n  fn      = " << uint(fm.fn())
	   << "\n  rsvd1   = " << uint(fm.rsvd1())
	   << "\n  mid     = " << std::hex << uint(fm.mid()) << std::dec
	   << "\n   sid    = " << uint(fm.sid())
	   << "\n   opcode = " << uint(fm.opcode())
	   << "\n   aid    = " << uint(fm.aid())
	   << "\n  rsvd2   = " << uint(fm.rsvd2())
	   << "\n  tid     = " << uint(fm.tid())
	   << "\n  plength = " << uint(fm.plength())
	   << "\n  length  = " << fm.length();

	return os;
}

///////////////////////////////////////////////////////////////////////////////
/**
 * Set the MIH Message Version.
 *
 * @param v The value of the MIH Message Version field.
 */
inline void frame::version(uint8 v)
{
	ODTONE_ASSERT(!(v & ~(mask_version >> 4)));

	hdr[0] = (hdr[0] & ~mask_version) | (v << 4);
}

/**
 * Set the MIH Message Acknowledge Request Flag.
 *
 * @param v The value of the MIH Message Acknowledge Request Flag field.
 */
inline void frame::ackreq(bool v)
{
	hdr[0] = (hdr[0] & ~mask_ackreq) | (uint8(v) << 3);
}

/**
 * Set the MIH Message Acknowledge Response Flag.
 *
 * @param v The value of the MIH Message Acknowledge Response Flag field.
 */
inline void frame::ackrsp(bool v)
{
	hdr[0] = (hdr[0] & ~mask_ackrsp) | (uint8(v) << 2);
}

/**
 * Set the MIH Message Unauthenticated Information Request Flag.
 *
 * @param v The value of the MIH Message Unauthenticated Information Request Flag.
 */
inline void frame::uir(bool v)
{
	hdr[0] = (hdr[0] & ~mask_uir) | (uint8(v) << 1);
}

/**
 * Set the MIH Message More Fragment Flag.
 *
 * @param v The value of the MIH Message More Fragment Flag.
 */
inline void frame::m(bool v)
{
	hdr[0] = (hdr[0] & ~mask_m) | uint8(v);
}

/**
 * Set the MIH Message Fragment Number.
 *
 * @param v The value of the MIH Message Fragment Number.
 */
inline void frame::fn(uint8 v)
{
	ODTONE_ASSERT(!(v & ~(mask_fn >> 1)));

	hdr[1] = (hdr[1] & ~mask_fn) | (v << 1);
}

/**
 * Set the MIH Message ID Service Identifier.
 *
 * @param v The value of the MIH Message ID Service Identifier.
 */
inline void frame::sid(service::type v)
{
	ODTONE_ASSERT(!(v & ~(mask_sid >> 4)));

	hdr[2] = (hdr[2] & ~mask_sid) | (v << 4);
}

/**
 * Set the MIH Message ID Operation Code.
 *
 * @param v The value of the MIH Message ID Operation Code.
 */
inline void frame::opcode(operation::type v)
{
	ODTONE_ASSERT(!(v & ~(mask_opcode >> 2)));

	hdr[2] = (hdr[2] & ~mask_opcode) | (v << 2);
}

/**
 * Set the MIH Message ID Action Identifier.
 *
 * @param v The value of the MIH Message ID Action Identifier.
 */
inline void frame::aid(action::type v)
{
	ODTONE_ASSERT(!(v & (uint16(~mask_aid) << 8)));

	hdr[2] = (hdr[2] & ~mask_aid) | uint8(v >> 8);
	hdr[3] = uint8(v & 0xff);
}

/**
 * Set the MIH Message ID.
 *
 * @param v The value of the MIH Message Message ID.
 */
inline void frame::mid(uint16 v)
{
	hdr[2] = uint8(v >> 8  );
	hdr[3] = uint8(v & 0xff);
}

/**
 * Set the MIH Message Transaction ID.
 *
 * @param v The value of the MIH Message Transaction ID.
 */
inline void frame::tid(uint16 v)
{
	ODTONE_ASSERT(!(v & (uint16(~mask_tid) << 8)));

	hdr[4] = (hdr[4] & ~mask_tid) | uint8(v >> 8);
	hdr[5] = uint8(v & 0xff);
}

/**
 * Set the message payload length.
 *
 * @param v The value of the message payload length.
 */
inline void frame::plength(uint16 v)
{
	hdr[6] = uint8(v >> 8  );
	hdr[7] = uint8(v & 0xff);
}

/**
 * Get the MIH Message Version.
 *
 * @return The value of the MIH Message Version field.
 */
inline uint8 frame::version() const
{
	return (hdr[0] & mask_version) >> 4;
}

/**
 * Get the MIH Message Acknowledge Request Flag.
 *
 * @return The value of the MIH Message Acknowledge Request Flag.
 */
inline bool frame::ackreq() const
{
	return (hdr[0] & mask_ackreq) >> 3;
}

/**
 * Get the MIH Message Acknowledge Response Flag.
 *
 * @return The value of the MIH Message Acknowledge Response Flag field.
 */
inline bool frame::ackrsp() const
{
	return (hdr[0] & mask_ackrsp) >> 2;
}

/**
 * Get the MIH Message Unauthenticated Information Request Flag.
 *
 * @return The value of the MIH Message Unauthenticated Information Request Flag.
 */
inline bool frame::uir() const
{
	return (hdr[0] & mask_uir) >> 1;
}

/**
 * Get the MIH Message More Fragment Flag.
 *
 * @return The value of the MIH Message More Fragment Flag.
 */
inline bool frame::m() const
{
	return (hdr[0] & mask_m);
}

/**
 * Get the MIH Message Fragment Number.
 *
 * @return The value of the MIH Message Fragment Number.
 */
inline uint8 frame::fn() const
{
	return (hdr[1] & mask_fn) >> 1;
}

/**
 * Get the MIH Reserved Bit 1.
 *
 * @return The value of the MIH Reserved Bit 1.
 */
inline bool frame::rsvd1() const
{
	return (hdr[1] & mask_rsvd1);
}

/**
 * Get the MIH Message ID Service Identifier.
 *
 * @return The value of the MIH Message ID Service Identifier.
 */
inline service::type frame::sid() const
{
	return service::type((hdr[2] & mask_sid) >> 4);
}

/**
 * Get the MIH Message ID Operation Code.
 *
 * @return The value of the MIH Message ID Operation Code.
 */
inline operation::type frame::opcode() const
{
	return operation::type((hdr[2] & mask_opcode) >> 2);
}

/**
 * Get the MIH Message ID Action Identifier.
 *
 * @return The value of the MIH Message ID Action Identifier.
 */
inline action::type frame::aid() const
{
	return action::type((uint16(hdr[2] & mask_aid) << 8) | hdr[3]);
}

/**
 * Get the MIH Message ID.
 *
 * @return The value of the MIH Message ID.
 */
inline uint16 frame::mid() const
{
	return (uint16(hdr[2]) << 8) | hdr[3];
}

/**
 * Get the MIH Reserved Bit 2.
 *
 * @return The value of the MIH Reserved Bit 2.
 */
inline uint8 frame::rsvd2() const
{
	return (hdr[4] & mask_rsvd2) >> 4;
}

/**
 * Get the MIH Message Transaction ID.
 *
 * @return The value of the MIH Message Transaction ID.
 */
inline uint16 frame::tid() const
{
	return (uint16(hdr[4] & mask_tid) << 8) | hdr[5];
}

/**
 * Get the message payload length.
 *
 * @return The message payload length.
 */
inline uint16 frame::plength() const
{
	return (uint16(hdr[6]) << 8) | hdr[7];
}

/**
 * Get the pointer of the message payload.
 *
 * @return The pointer of the message payload.
 */
inline uint8* frame::payload()
{
	return &hdr[8];
}

/**
 * Get the pointer of the message payload.
 *
 * @return The pointer of the message payload.
 */
inline const uint8* frame::payload() const
{
	return &hdr[8];
}

/**
 * Get the length of the frame.
 *
 * @return The length of the frame.
 */
inline size_t frame::length() const
{
	return sizeof(frame) + plength();
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /* namespace odtone */

#ifdef BOOST_MSVC
#	pragma warning(pop)
#endif

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_FRAME__HPP_ */
