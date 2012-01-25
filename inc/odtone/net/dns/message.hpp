//=============================================================================
// Brief   : DNS Message
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

#ifndef ODTONE_DNS_MESSAGE__HPP_
#define ODTONE_DNS_MESSAGE__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <vector>

#include <odtone/base.hpp>
#include <odtone/net/dns/frame.hpp>
#include <odtone/net/dns/types.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace dns {


/**
 * DNS Message
 *
 * The odtone::dns::message is high level representation of an DNS message. It
 * provides access to all fields of the DNS message header and to all resource records
 * presented on the DNS Message.
 *
 * The odtone::dns::message can be set from an odtone::dns::frame that was
 * received or it can create an odtone::dns::frame ready to be sent.
 */
class message {
public:
	/**
	 * Construct a default DNS Message.
	 *
	 * The defaults for each field are:
	 *    tid 		= 0;
	 *    qr 		= false;
	 *    opcode 	= 0;
	 *    aa 		= false;
	 *    tc 		= false;
	 *    rd 		= false;
	 *    ra 		= false;
	 *    z 		= false;
	 *    rcode 	= false;
	 *    nquery 	= false;
	 *    nanswer 	= false;
	 *    nauth 	= false;
	 *    nadd	 	= false;
	 */
	message();

	/**
	 * Construct a DNS Message parsing all fields from a frame.
	 *
	 * @param fm odtone::dns::frame from which to parse information.
	 */
	message(const frame& fm);

	/**
	 * Destruct a DNS Message.
	 */
	~message();

	/**
	 * Extract the DNS Message fields from a given odtone::dns::frame.
	 *
	 * @param fm odtone::dns::frame from which to extract information.
	 * @return odtone::dns::message with the fields updated.
	 */
	message& operator=(const frame& fm);

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
	 * Set the DNS Message Question list.
	 *
	 * @param query The value of the DNS Message Question list.
	 */
	void query(std::vector<question> query);

	/**
	 * Set the DNS Message Answer Record list.
	 *
	 * @param answer The value of the DNS Message Answer Record list.
	 */
	void answer(std::vector<resource_record> answer);

	/**
	 * Set the DNS Message Authority Record list.
	 *
	 * @param auth The value of the DNS Message Authority Record list.
	 */
	void auth(std::vector<resource_record> auth);

	/**
	 * Set the DNS Message Additional Record list.
	 *
	 * @param add The value of the DNS Message Additional Record Count list.
	 */
	void add(std::vector<resource_record> add);

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
	 * Get the DNS Message Question list.
	 *
	 * @return The DNS Message Question list.
	 */
	std::vector<question> query();

	/**
	 * Get the DNS Message Answer Record list.
	 *
	 * @return The DNS Message Answer Record list.
	 */
	std::vector<resource_record> answer();

	/**
	 * Get the DNS Message Authority Record list.
	 *
	 * @return The DNS Message Authority Record list.
	 */
	std::vector<resource_record> auth();

	/**
	 * Get the DNS Message Additional Record list.
	 *
	 * @return The DNS Message Additional Record Count list.
	 */
	std::vector<resource_record> add();

	/**
	 * Get the DNS Message Frame.
	 *
	 * @param fm A dynamic frame buffer to store the information.
	 */
	void get_frame(frame_vla& fm) const;

private:
	uint16 _tid;							/**< Transaction identifier.		*/
	bool _qr;								/**< Query/Response flag.			*/
	uint8 _opcode;							/**< Operation code.				*/
	bool _aa;								/**< Authoritative answer flag.		*/
	bool _tc;								/**< Truncation flag.				*/
	bool _rd;								/**< Recursion desired.				*/
	bool _ra;								/**< Recursion available.			*/
	bool _z;								/**< Reserved.						*/
	uint8 _rcode;							/**< Response code.					*/
	uint16 _nquery;							/**< Question records count.		*/
	uint16 _nanswer;						/**< Answer records count.			*/
	uint16 _nauth;							/**< Authentication records count.	*/
	uint16 _nadd;							/**< Additional record count.		*/
	std::vector<question> _query;			/**< Query Record list.				*/
	std::vector<resource_record> _answer;	/**< Answer Record list.			*/
	std::vector<resource_record> _auth;		/**< Authentication Record list.	*/
	std::vector<resource_record> _add;		/**< Additional Record list.		*/
};

/**
 * Set the DNS Message Transaction Identifier.
 *
 * @param tid The value of the DNS Message Transaction Identifier field.
 */
inline void message::tid(uint16 tid)
{
	_tid = tid;
}

/**
 * Set the DNS Message Query/Response Flag.
 *
 * @param qr The value of the DNS Message Query/Response Flag field.
 */
inline void message::qr(bool qr)
{
	_qr = qr;
}

/**
 * Set the DNS Message Operation Code.
 *
 * @param opcode The value of the DNS Message Operation Code field.
 */
inline void message::opcode(uint8 opcode)
{
	_opcode = opcode;
}

/**
 * Set the DNS Message Authoritative Answer Flag.
 *
 * @param aa The value of the DNS Message Authoritative Answer Flag field.
 */
inline void message::aa(bool aa)
{
	_aa = aa;
}

/**
 * Set the DNS Message Truncation Flag.
 *
 * @param tc The value of the DNS Message Truncation Flag field.
 */
inline void message::tc(bool tc)
{
	_tc = tc;
}

/**
 * Set the DNS Message Recursion Desired.
 *
 * @param rd The value of the DNS Message Recursion Desired field.
 */
inline void message::rd(bool rd)
{
	_rd = rd;
}

/**
 * Set the DNS Message Recursion Available.
 *
 * @param ra The value of the DNS Message Recursion Available field.
 */
inline void message::ra(bool ra)
{
	_ra = ra;
}

/**
 * Set the DNS Message Zero.
 *
 * @param z The value of the DNS Message Zero field.
 */
inline void message::z(bool z)
{
	_z = z;
}

/**
 * Set the DNS Message Response Code.
 *
 * @param rcode The value of the DNS Message Response Code field.
 */
inline void message::rcode(uint8 rcode)
{
	_rcode = rcode;
}

/**
 * Set the DNS Message Question list.
 *
 * @param query The value of the DNS Message Question list.
 */
inline void message::query(std::vector<question> query)
{
	_nquery = query.size();
	_query = query;
}

/**
 * Set the DNS Message Answer Record list.
 *
 * @param answer The value of the DNS Message Answer Record list.
 */
inline void message::answer(std::vector<resource_record> answer)
{
	_nanswer = answer.size();
	_answer = answer;
}

/**
 * Set the DNS Message Authority Record list.
 *
 * @param auth The value of the DNS Message Authority Record list.
 */
inline void message::auth(std::vector<resource_record> auth)
{
	_nauth = auth.size();
	_auth = auth;
}

/**
 * Set the DNS Message Additional Record list.
 *
 * @param add The value of the DNS Message Additional Record Count list.
 */
inline void message::add(std::vector<resource_record> add)
{
	_nadd = add.size();
	_add = add;
}

/**
 * Get the DNS Message Transaction Identifier.
 *
 * @return The value of the DNS Message Transaction Identifier field.
 */
inline uint16 message::tid() const
{
	return _tid;
}

/**
 * Get the DNS Message Query/Response Flag.
 *
 * @return The value of the DNS Message Query/Response Flag field.
 */
inline bool message::qr() const
{
	return _qr;
}

/**
 * Get the DNS Message Operation Code.
 *
 * @return The value of the DNS Message Operation Code field.
 */
inline uint8 message::opcode() const
{
	return _opcode;
}

/**
 * Get the DNS Message Authoritative Answer Flag.
 *
 * @return The value of the DNS Message Authoritative Answer Flag field.
 */
inline bool message::aa() const
{
	return _aa;
}

/**
 * Get the DNS Message Truncation Flag.
 *
 * @return The value of the DNS Message Truncation Flag field.
 */
inline bool message::tc() const
{
	return _tc;
}

/**
 * Get the DNS Message Recursion Desired.
 *
 * @return The value of the DNS Message Recursion Desired field.
 */
inline bool message::rd() const
{
	return _rd;
}

/**
 * Get the DNS Message Recursion Available.
 *
 * @return The value of the DNS Message Recursion Available field.
 */
inline bool message::ra() const
{
	return _ra;
}

/**
 * Get the DNS Message Zero.
 *
 * @return The value of the DNS Message Zero field.
 */
inline bool message::z() const
{
	return _z;
}

/**
 * Get the DNS Message Response Code.
 *
 * @return The value of the DNS Message Response Code field.
 */
inline uint8 message::rcode() const
{
	return _rcode;
}

/**
 * Get the DNS Message Question Count.
 *
 * @return The value of the DNS Message Question Count field.
 */
inline uint16 message::nquery() const
{
	return _nquery;
}

/**
 * Get the DNS Message Answer Record Count.
 *
 * @return The value of the DNS Message Answer Record Count field.
 */
inline uint16 message::nanswer() const
{
	return _nanswer;
}

/**
 * Get the DNS Message Authority Record Count.
 *
 * @return The value of the DNS Message Authority Record Count field.
 */
inline uint16 message::nauth() const
{
	return _nauth;
}

/**
 * Get the DNS Message Additional Record Count.
 *
 * @return The value of the DNS Message Additional Record Count field.
 */
inline uint16 message::nadd() const
{
	return _nadd;
}

/**
 * Get the DNS Message Question list.
 *
 * @return The DNS Message Question list.
 */
inline std::vector<question> message::query()
{
	return _query;
}

/**
 * Get the DNS Message Answer Record list.
 *
 * @return The DNS Message Answer Record list.
 */
inline std::vector<resource_record> message::answer()
{
	return _answer;
}

/**
 * Get the DNS Message Authority Record list.
 *
 * @return The DNS Message Authority Record list.
 */
inline std::vector<resource_record> message::auth()
{
	return _auth;
}

/**
 * Get the DNS Message Additional Record list.
 *
 * @return The DNS Message Additional Record Count list.
 */
inline std::vector<resource_record> message::add()
{
	return _add;
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace dns */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_DNS_MESSAGE__HPP_ */
