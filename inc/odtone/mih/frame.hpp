//=============================================================================
// Brief   : MIH Message Frame
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

#ifndef ODTONE_MIH_FRAME__HPP_
#define ODTONE_MIH_FRAME__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/debug.hpp>
#include <odtone/buffer.hpp>
#include <boost/utility.hpp>
#include <ostream>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
struct service {
	enum type {
		management  = 1,
		event       = 2,
		command     = 3,
		information = 4
	};
};

struct operation {
	enum type {
		confirm    = 0,
		request    = 1,
		response   = 2,
		indication = 3
	};
};

struct action {
	enum type {
		capability_discover = 1,
		mih_register        = 2,
		mih_deregister      = 3,
		event_subscribe     = 4,
		event_unsubscribe   = 5,

		link_detected          = 1,
		link_up                = 2,
		link_down              = 3,
		link_parameters_report = 5,
		link_going_down        = 6,
		link_handover_imminent = 7,
		link_handover_complete = 8,

		link_get_parameters       = 1,
		link_configure_thresholds = 2,
		link_actions              = 3,
		net_ho_candidate_query    = 4,
		mn_ho_candidate_query     = 5,
		n2n_ho_query_resources    = 6,
		mn_ho_commit              = 7,
		net_ho_commit             = 8,
		n2n_ho_commit             = 9,
		mn_ho_complete            = 10,
		n2n_ho_complete           = 11,

		get_information  = 1,
		push_information = 2,
	};
};

struct frame {
	static const uint8 mask_version = 0xf0;
	static const uint8 mask_ackreq  = 0x08;
	static const uint8 mask_ackrsp  = 0x04;
	static const uint8 mask_uir     = 0x02;
	static const uint8 mask_m       = 0x01;
	static const uint8 mask_fn      = 0xfe;
	static const uint8 mask_rsvd1   = 0x01;
	static const uint8 mask_sid     = 0xf0;
	static const uint8 mask_opcode  = 0x0d;
	static const uint8 mask_aid     = 0x03;
	static const uint8 mask_rsvd2   = 0xf0;
	static const uint8 mask_tid     = 0xff;


	static frame* cast(void* buff, size_t len)
	{
		frame* fm = reinterpret_cast<frame*>(buff);

		if (len < sizeof(frame) || len < fm->length())
			return nullptr;

		return fm;
	}

	static const frame* cast(const void* buff, size_t len)
	{
		const frame* fm = reinterpret_cast<const frame*>(buff);

		if (len < sizeof(frame) || len < fm->length())
			return nullptr;

		return fm;
	}

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
	void plength(uint16 v);

	uint8           version() const;
	bool            ackreq() const;
	bool            ackrsp() const;
	bool            uir() const;
	bool            m() const;
	uint8           fn() const;
	bool            rsvd1() const;
	service::type   sid() const;
	operation::type opcode() const;
	action::type    aid() const;
	uint16          mid() const;
	uint8           rsvd2() const;
	uint16          tid() const;
	uint16          plength() const;

	uint8*       payload();
	const uint8* payload() const;

	size_t length() const;

	uint8 hdr[8];
};

typedef buffer_vla<frame> frame_vla;

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
inline void frame::version(uint8 v)
{
	ODTONE_ASSERT(!(v & ~(mask_version >> 4)));

	hdr[0] = (hdr[0] & ~mask_version) | (v << 4);
}

inline void frame::ackreq(bool v)
{
	hdr[0] = (hdr[0] & ~mask_ackreq) | (uint8(v) << 3);
}

inline void frame::ackrsp(bool v)
{
	hdr[0] = (hdr[0] & ~mask_ackrsp) | (uint8(v) << 2);
}

inline void frame::uir(bool v)
{
	hdr[0] = (hdr[0] & ~mask_uir) | (uint8(v) << 1);
}

inline void frame::m(bool v)
{
	hdr[0] = (hdr[0] & ~mask_ackreq) | uint8(v);
}

inline void frame::fn(uint8 v)
{
	ODTONE_ASSERT(!(v & ~(mask_fn >> 1)));

	hdr[1] = (hdr[1] & ~mask_fn) | (v << 1);
}

inline void frame::sid(service::type v)
{
	ODTONE_ASSERT(!(v & ~(mask_sid >> 4)));

	hdr[2] = (hdr[2] & ~mask_sid) | (v << 4);
}

inline void frame::opcode(operation::type v)
{
	ODTONE_ASSERT(!(v & ~(mask_opcode >> 2)));

	hdr[2] = (hdr[2] & ~mask_opcode) | (v << 2);
}

inline void frame::aid(action::type v)
{
	ODTONE_ASSERT(!(v & (uint16(~mask_aid) << 8)));

	hdr[2] = (hdr[2] & ~mask_aid) | uint8(v >> 8);
	hdr[3] = uint8(v & 0xff);
}

inline void frame::mid(uint16 v)
{
	hdr[2] = uint8(v >> 8  );
	hdr[3] = uint8(v & 0xff);
}

inline void frame::tid(uint16 v)
{
	ODTONE_ASSERT(!(v & (uint16(~mask_tid) << 8)));

	hdr[4] = (hdr[4] & ~mask_tid) | uint8(v >> 8);
	hdr[5] = uint8(v & 0xff);
}

inline void frame::plength(uint16 v)
{
	hdr[6] = uint8(v >> 8  );
	hdr[7] = uint8(v & 0xff);
}

inline uint8 frame::version() const
{
	return (hdr[0] & mask_version) >> 4;
}

inline bool frame::ackreq() const
{
	return (hdr[0] & mask_ackreq) >> 3;
}

inline bool frame::ackrsp() const
{
	return (hdr[0] & mask_ackrsp) >> 2;
}

inline bool frame::uir() const
{
	return (hdr[0] & mask_uir) >> 4;
}

inline bool frame::m() const
{
	return (hdr[0] & mask_m);
}

inline uint8 frame::fn() const
{
	return (hdr[1] & mask_fn) >> 1;
}

inline bool frame::rsvd1() const
{
	return (hdr[1] & mask_rsvd1);
}

inline service::type frame::sid() const
{
	return service::type((hdr[2] & mask_sid) >> 4);
}

inline operation::type frame::opcode() const
{
	return operation::type((hdr[2] & mask_opcode) >> 2);
}

inline action::type frame::aid() const
{
	return action::type((uint16(hdr[2] & mask_aid) << 8) | hdr[3]);
}

inline uint16 frame::mid() const
{
	return (uint16(hdr[2]) << 8) | hdr[3];
}

inline uint8 frame::rsvd2() const
{
	return (hdr[4] & mask_rsvd2) >> 4;
}

inline uint16 frame::tid() const
{
	return (uint16(hdr[4] & mask_tid) << 8) | hdr[5];
}

inline uint16 frame::plength() const
{
	return (uint16(hdr[6]) << 8) | hdr[7];
}

inline uint8* frame::payload()
{
	return &hdr[8];
}

inline const uint8* frame::payload() const
{
	return &hdr[8];
}

inline size_t frame::length() const
{
	return sizeof(frame) + plength();
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_FRAME__HPP_ */
