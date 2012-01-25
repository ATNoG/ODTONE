//=============================================================================
// Brief   : DNS Message Frame
// Authors : Carlos Guimaraes <cguimaraes@av.it.pt>
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

#ifndef ODTONE_DNS_FRAME__HPP_
#define ODTONE_DNS_FRAME__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/buffer.hpp>

#ifdef BOOST_MSVC
#	pragma warning(push)
#	pragma warning(disable : 4800)
#endif

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace dns {

/**
 * DNS message frame. This class provides access to all fields of the
 * DNS message header.
 */
struct frame {
	static const uint8 mask_qr		= 0x80;	/**< DNS Message Query/Response Flag mask.		*/
	static const uint8 mask_opcode	= 0x78;	/**< DNS Message Operation Code mask.			*/
	static const uint8 mask_aa		= 0x04;	/**< DNS Message Authoritative Answer Flag mask.*/
	static const uint8 mask_tc		= 0x02;	/**< DNS Message Truncation Flag mask.			*/
	static const uint8 mask_rd		= 0x01;	/**< DNS Message Recursion Desired mask.		*/
	static const uint8 mask_ra		= 0x80;	/**< DNS Message Recursion Available mask.		*/
	static const uint8 mask_z		= 0x40;	/**< DNS Message Zero mask.						*/
	static const uint8 mask_rcode	= 0x0f;	/**< DNS Message Response Code mask.			*/

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

		return fm;
	}

	/**
	 * Set the DNS Message Transaction Identifier.
	 *
	 * @param tid The value of the DNS Message Transaction Identifier field.
	 */
	void tid(uint16 tid);

	/**
	 * Set the DNS Message Query/Response Flag.
	 *
	 * @param qr The value of the DNS Message Query/Response Flag field.
	 */
	void qr(bool qr);

	/**
	 * Set the DNS Message Operation Code.
	 *
	 * @param opcode The value of the DNS Message Operation Code field.
	 */
	void opcode(uint8 opcode);

	/**
	 * Set the DNS Message Authoritative Answer Flag.
	 *
	 * @param aa The value of the DNS Message Authoritative Answer Flag field.
	 */
	void aa(bool aa);

	/**
	 * Set the DNS Message Truncation Flag.
	 *
	 * @param tc The value of the DNS Message Truncation Flag field.
	 */
	void tc(bool tc);

	/**
	 * Set the DNS Message Recursion Desired.
	 *
	 * @param rd The value of the DNS Message Recursion Desired field.
	 */
	void rd(bool rd);

	/**
	 * Set the DNS Message Recursion Available.
	 *
	 * @param ra The value of the DNS Message Recursion Available field.
	 */
	void ra(bool ra);

	/**
	 * Set the DNS Message Zero.
	 *
	 * @param z The value of the DNS Message Zero field.
	 */
	void z(bool z);

	/**
	 * Set the DNS Message Response Code.
	 *
	 * @param rcode The value of the DNS Message Response Code field.
	 */
	void rcode(uint8 rcode);

	/**
	 * Set the DNS Message Question Count.
	 *
	 * @param nquery The value of the DNS Message Question Count field.
	 */
	void nquery(uint16 nquery);

	/**
	 * Set the DNS Message Answer Record Count.
	 *
	 * @param nanswer The value of the DNS Message Answer Record Count field.
	 */
	void nanswer(uint16 nanswer);

	/**
	 * Set the DNS Message Authority Record Count.
	 *
	 * @param nauth The value of the DNS Message Authority Record Count field.
	 */
	void nauth(uint16 nauth);

	/**
	 * Set the DNS Message Additional Record Count.
	 *
	 * @param nadd The value of the DNS Message Additional Record Count field.
	 */
	void nadd(uint16 nadd);

	/**
	 * Get the DNS Message Transaction Identifier.
	 *
	 * @return The value of the DNS Message Transaction Identifier field.
	 */
	uint16 tid() const;

	/**
	 * Get the DNS Message Query/Response Flag.
	 *
	 * @return The value of the DNS Message Query/Response Flag field.
	 */
	bool qr() const;

	/**
	 * Get the DNS Message Operation Code.
	 *
	 * @return The value of the DNS Message Operation Code field.
	 */
	uint8 opcode() const;

	/**
	 * Get the DNS Message Authoritative Answer Flag.
	 *
	 * @return The value of the DNS Message Authoritative Answer Flag field.
	 */
	bool aa() const;

	/**
	 * Get the DNS Message Truncation Flag.
	 *
	 * @return The value of the DNS Message Truncation Flag field.
	 */
	bool tc() const;

	/**
	 * Get the DNS Message Recursion Desired.
	 *
	 * @return The value of the DNS Message Recursion Desired field.
	 */
	bool rd() const;

	/**
	 * Get the DNS Message Recursion Available.
	 *
	 * @return The value of the DNS Message Recursion Available field.
	 */
	bool ra() const;

	/**
	 * Get the DNS Message Zero.
	 *
	 * @return The value of the DNS Message Zero field.
	 */
	bool z() const;

	/**
	 * Get the DNS Message Response Code.
	 *
	 * @return The value of the DNS Message Response Code field.
	 */
	uint8 rcode() const;

	/**
	 * Get the DNS Message Question Count.
	 *
	 * @return The value of the DNS Message Question Count field.
	 */
	uint16 nquery() const;

	/**
	 * Get the DNS Message Answer Record Count.
	 *
	 * @return The value of the DNS Message Answer Record Count field.
	 */
	uint16 nanswer() const;

	/**
	 * Get the DNS Message Authority Record Count.
	 *
	 * @return The value of the DNS Message Authority Record Count field.
	 */
	uint16 nauth() const;

	/**
	 * Get the DNS Message Additional Record Count.
	 *
	 * @return The value of the DNS Message Additional Record Count field.
	 */
	uint16 nadd() const;

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
	 * Get the pointer of the message payload.
	 *
	 * @return The pointer of the message payload.
	 */
	uint8* get();

	/**
	 * Get the pointer of the message payload.
	 *
	 * @return The pointer of the message payload.
	 */
	const uint8* get() const;

	uint8 hdr[12];	/**< Frame bytes. */
};

typedef buffer_vla<frame> frame_vla;

///////////////////////////////////////////////////////////////////////////////
/**
 * Set the DNS Message Transaction Identifier.
 *
 * @param tid The value of the DNS Message Transaction Identifier field.
 */
inline void frame::tid(uint16 tid)
{
	hdr[0] = uint8(tid >> 8  );
	hdr[1] = uint8(tid & 0xff);
}

/**
 * Set the DNS Message Query/Response Flag.
 *
 * @param qr The value of the DNS Message Query/Response Flag field.
 */
inline void frame::qr(bool qr)
{
	hdr[2] = (hdr[2] & ~mask_qr) | (uint8(qr) << 7);
}

/**
 * Set the DNS Message Operation Code.
 *
 * @param opcode The value of the DNS Message Operation Code field.
 */
inline void frame::opcode(uint8 opcode)
{
	hdr[2] = (hdr[2] & ~mask_opcode) | (uint8(opcode) << 6);
}

/**
 * Set the DNS Message Authoritative Answer Flag.
 *
 * @param aa The value of the DNS Message Authoritative Answer Flag field.
 */
inline void frame::aa(bool aa)
{
	hdr[2] = (hdr[2] & ~mask_qr) | (uint8(aa) << 2);
}

/**
 * Set the DNS Message Truncation Flag.
 *
 * @param tc The value of the DNS Message Truncation Flag field.
 */
inline void frame::tc(bool tc)
{
	hdr[2] = (hdr[2] & ~mask_qr) | (uint8(tc) << 1);
}

/**
 * Set the DNS Message Recursion Desired.
 *
 * @param rd The value of the DNS Message Recursion Desired field.
 */
inline void frame::rd(bool rd)
{
	hdr[2] = (hdr[2] & ~mask_qr) | (uint8(rd));
}

/**
 * Set the DNS Message Recursion Available.
 *
 * @param ra The value of the DNS Message Recursion Available field.
 */
inline void frame::ra(bool ra)
{
	hdr[3] = (hdr[3] & ~mask_ra) | (uint8(ra) << 7);
}

/**
 * Set the DNS Message Zero.
 *
 * @param z The value of the DNS Message Zero field.
 */
inline void frame::z(bool z)
{
	hdr[3] = (hdr[3] & ~mask_z) | (uint8(z) << 6);
}

/**
 * Set the DNS Message Response Code.
 *
 * @param rcode The value of the DNS Message Response Code field.
 */
inline void frame::rcode(uint8 rcode)
{
	hdr[3] = (hdr[3] & ~mask_rcode) | (uint8(rcode));
}

/**
 * Set the DNS Message Question Count.
 *
 * @param nquery The value of the DNS Message Question Count field.
 */
inline void frame::nquery(uint16 nquery)
{
	hdr[4] = uint8(nquery >> 8  );
	hdr[5] = uint8(nquery & 0xff);
}

/**
 * Set the DNS Message Answer Record Count.
 *
 * @param nanswer The value of the DNS Message Answer Record Count field.
 */
inline void frame::nanswer(uint16 nanswer)
{
	hdr[6] = uint8(nanswer >> 8  );
	hdr[7] = uint8(nanswer & 0xff);
}

/**
 * Set the DNS Message Authority Record Count.
 *
 * @param nauth The value of the DNS Message Authority Record Count field.
 */
inline void frame::nauth(uint16 nauth)
{
	hdr[8] = uint8(nauth >> 8  );
	hdr[9] = uint8(nauth & 0xff);
}

/**
 * Set the DNS Message Additional Record Count.
 *
 * @param nadd The value of the DNS Message Additional Record Count field.
 */
inline void frame::nadd(uint16 nadd)
{
	hdr[10] = uint8(nadd >> 8  );
	hdr[11] = uint8(nadd & 0xff);
}

/**
 * Get the DNS Message Transaction Identifier.
 *
 * @return The value of the DNS Message Transaction Identifier field.
 */
inline uint16 frame::tid() const
{
	return (uint16(hdr[0]) << 8) | hdr[1];
}

/**
 * Get the DNS Message Query/Response Flag.
 *
 * @return The value of the DNS Message Query/Response Flag field.
 */
inline bool frame::qr() const
{
	return (hdr[2] & mask_qr) >> 7;
}

/**
 * Get the DNS Message Operation Code.
 *
 * @return The value of the DNS Message Operation Code field.
 */
inline uint8 frame::opcode() const
{
	return (hdr[2] & mask_opcode) >> 6;
}

/**
 * Get the DNS Message Authoritative Answer Flag.
 *
 * @return The value of the DNS Message Authoritative Answer Flag field.
 */
inline bool frame::aa() const
{
	return (hdr[2] & mask_aa) >> 2;
}

/**
 * Get the DNS Message Truncation Flag.
 *
 * @return The value of the DNS Message Truncation Flag field.
 */
inline bool frame::tc() const
{
	return (hdr[2] & mask_tc) >> 1;
}

/**
 * Get the DNS Message Recursion Desired.
 *
 * @return The value of the DNS Message Recursion Desired field.
 */
inline bool frame::rd() const
{
	return (hdr[2] & mask_rd);
}

/**
 * Get the DNS Message Recursion Available.
 *
 * @return The value of the DNS Message Recursion Available field.
 */
inline bool frame::ra() const
{
	return (hdr[3] & mask_ra) >> 7;
}

/**
 * Get the DNS Message Zero.
 *
 * @return The value of the DNS Message Zero field.
 */
inline bool frame::z() const
{
	return (hdr[3] & mask_z) >> 6;
}

/**
 * Get the DNS Message Response Code.
 *
 * @return The value of the DNS Message Response Code field.
 */
inline uint8 frame::rcode() const
{
	return (hdr[3] & mask_rcode);
}

/**
 * Get the DNS Message Question Count.
 *
 * @return The value of the DNS Message Question Count field.
 */
inline uint16 frame::nquery() const
{
	return (uint16(hdr[4]) << 8) | hdr[5];
}

/**
 * Get the DNS Message Answer Record Count.
 *
 * @return The value of the DNS Message Answer Record Count field.
 */
inline uint16 frame::nanswer() const
{
	return (uint16(hdr[6]) << 8) | hdr[7];
}

/**
 * Get the DNS Message Authority Record Count.
 *
 * @return The value of the DNS Message Authority Record Count field.
 */
inline uint16 frame::nauth() const
{
	return (uint16(hdr[8]) << 8) | hdr[9];
}

/**
 * Get the DNS Message Additional Record Count.
 *
 * @return The value of the DNS Message Additional Record Count field.
 */
inline uint16 frame::nadd() const
{
	return (uint16(hdr[10]) << 8) | hdr[11];
}

/**
 * Get the pointer of the message payload.
 *
 * @return The pointer of the message payload.
 */
inline uint8* frame::payload()
{
	return &hdr[12];
}

/**
 * Get the pointer of the message payload.
 *
 * @return The pointer of the message payload.
 */
inline const uint8* frame::payload() const
{
	return &hdr[12];
}

/**
 * Get the pointer of the message payload.
 *
 * @return The pointer of the message payload.
 */
inline uint8* frame::get()
{
	return &hdr[0];
}

/**
 * Get the pointer of the message payload.
 *
 * @return The pointer of the message payload.
 */
inline const uint8* frame::get() const
{
	return &hdr[0];
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace dns */ } /* namespace odtone */

#ifdef BOOST_MSVC
#	pragma warning(pop)
#endif

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_DNS_FRAME__HPP_ */
