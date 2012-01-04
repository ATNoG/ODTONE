//=============================================================================
// Brief   : DNS Message
// Authors : Carlos Guimaraes <cguimaraes@av.it.pt>
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

#include <odtone/net/dns/message.hpp>
#include <odtone/net/dns/utils.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace dns {

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
message::message()
	: _tid(0), _qr(false), _opcode(0), _aa(false), _tc(false),
	_rd(false), _ra(false), _z(false), _rcode(false),
	_nquery(0), _nanswer(0), _nauth(0), _nadd(0)
{
}

/**
 * Construct a DNS Message parsing all fields from a frame.
 *
 * @param fm odtone::dns::frame from which to parse information.
 */
message::message(const frame& fm)
{
	*this = fm;
}

/**
 * Destruct a DNS Message.
 */
message::~message()
{
}

/**
 * Extract the DNS Message fields from a given odtone::dns::frame.
 *
 * @param fm odtone::dns::frame from which to extract information.
 * @return odtone::dns::message with the fields updated.
 */
message& message::operator=(const frame& fm)
{
	_tid = fm.tid();
	_qr = fm.qr();
	_opcode = fm.opcode();
	_aa = fm.aa();
	_tc = fm.tc();
	_rd = fm.rd();
	_ra = fm.ra();
	_z = fm.z();
	_rcode = fm.rcode();
	_nquery = fm.nquery();
	_nanswer = fm.nanswer();
	_nauth = fm.nauth();
	_nadd = fm.nadd();

	const unsigned char *p = fm.payload();
	int pos = 0;
	for(int i = 0; i < _nquery; ++i) {
		std::string qname = parse_domain_name(p, pos);
		uint16 qtype = parse_uint16(p, pos);
		uint16 qclass = parse_uint16(p, pos);

		dns::question question(qname, qtype, qclass);
		_query.push_back(question);
	}

	for(int i = 0; i < _nanswer; ++i) {
		std::string qname = parse_domain_name(p, pos);
		uint16 qtype = parse_uint16(p, pos);
		uint16 qclass = parse_uint16(p, pos);
		uint32 qttl = parse_uint32(p, pos);
		uint16 qlength = parse_uint16(p, pos);
		std::vector<uint8> qdata = parse_data(p, pos, qlength);

		dns::resource_record rr(qname, qtype, qclass, qttl, qlength, qdata);
		_answer.push_back(rr);

	}

	for(int i = 0; i < _nauth; ++i) {
		std::string qname = parse_domain_name(p, pos);
		uint16 qtype = parse_uint16(p, pos);
		uint16 qclass = parse_uint16(p, pos);
		uint32 qttl = parse_uint32(p, pos);
		uint16 qlength = parse_uint16(p, pos);
		std::vector<uint8> qdata = parse_data(p, pos, qlength);

		dns::resource_record rr(qname, qtype, qclass, qttl, qlength, qdata);
		_auth.push_back(rr);
	}

	for(int i = 0; i < _nadd; ++i) {
		std::string qname = parse_domain_name(p, pos);
		uint16 qtype = parse_uint16(p, pos);
		uint16 qclass = parse_uint16(p, pos);
		uint32 qttl = parse_uint32(p, pos);
		uint16 qlength = parse_uint16(p, pos);
		std::vector<uint8> qdata = parse_data(p, pos, qlength);

		dns::resource_record rr(qname, qtype, qclass, qttl, qlength, qdata);
		_add.push_back(rr);
	}

	return *this;
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace dns */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
