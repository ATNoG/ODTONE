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

#include <odtone/net/dns/message.hpp>
#include <odtone/net/dns/utils.hpp>

#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace dns {

///////////////////////////////////////////////////////////////////////////////
void serialize_query_record(std::vector<uint8> &payload, uint16 &payload_len, dns::question query)
{
	std::vector<std::string> split_domain;

	boost::split(split_domain, query._domain, boost::is_any_of("."));
	BOOST_FOREACH(std::string tmp, split_domain) {
		payload.push_back(tmp.size());
		for(unsigned int i = 0; i < tmp.size(); ++i) {
			payload.push_back(tmp[i]);
			payload_len++;
		}
	}
	payload.push_back(0);	// Domain name terminator

	// Query Type
	payload.push_back((query._type >>  8) & 0xFF);
	payload.push_back((query._type      ) & 0xFF);

	// Query Class
	payload.push_back((query._class >>  8) & 0xFF);
	payload.push_back((query._class      ) & 0xFF);

	payload_len += 5;
}

void serialize_resource_record(std::vector<uint8> &payload, uint16 &payload_len, dns::resource_record rr)
{
	std::vector<std::string> split_domain;

	boost::split(split_domain, rr._name, boost::is_any_of("."));
	BOOST_FOREACH(std::string tmp, split_domain) {
		payload.push_back(tmp.size());
		for(unsigned int i = 0; i < tmp.size(); ++i) {
			payload.push_back(tmp[i]);
			payload_len++;
		}
	}
	payload.push_back(0);	// Domain name terminator

	// Resource Record Type
	payload.push_back((rr._type >>  8) & 0xFF);
	payload.push_back((rr._type      ) & 0xFF);

	// Resource Record Class
	payload.push_back((rr._class >>  8) & 0xFF);
	payload.push_back((rr._class      ) & 0xFF);

	// Resource Record Time to Live
	payload.push_back((rr._ttl >>  24) & 0xFF);
	payload.push_back((rr._ttl >>  16) & 0xFF);
	payload.push_back((rr._ttl >>   8) & 0xFF);
	payload.push_back((rr._ttl       ) & 0xFF);

	// Resource Record Data Length
	payload.push_back((rr._rr_len >>  8) & 0xFF);
	payload.push_back((rr._rr_len      ) & 0xFF);

	payload_len += 10;

	// Resource Record Data Length
	payload.insert(payload.end(), rr._rr_data.begin(), rr._rr_data.end());
	payload_len += rr._rr_len;
}
///////////////////////////////////////////////////////////////////////////////

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

	// Query Record List
	for(int i = 0; i < _nquery; ++i) {
		std::string qname = parse_domain_name(p, pos);
		uint16 qtype = parse_uint16(p, pos);
		uint16 qclass = parse_uint16(p, pos);

		dns::question question(qname, qtype, qclass);
		_query.push_back(question);
	}

	// Answer Record List
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

	// Authentication Record List
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

	// Additional Record List
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

/**
 * Get the MIH Message Frame.
 *
 * @param fm A dynamic frame buffer to store the information.
 */
void message::get_frame(frame_vla& fm) const
{
	// TODO optimize by using domain name pointers
	std::vector<uint8> payload;
	uint16 payload_len = 0;

	// Query Record List
	BOOST_FOREACH(dns::question query, _query) {
		serialize_query_record(payload, payload_len, query);
	}

	// Answer Record List
	BOOST_FOREACH(dns::resource_record rr, _answer) {
		serialize_resource_record(payload, payload_len, rr);
	}

	// Authentication Record List
	BOOST_FOREACH(dns::resource_record rr, _auth) {
		serialize_resource_record(payload, payload_len, rr);
	}

	// Additional Record List
	BOOST_FOREACH(dns::resource_record rr, _add) {
		serialize_resource_record(payload, payload_len, rr);
	}

	fm.size(12 + payload_len);	// Header length + Payload length
	fm.zero();

	fm->tid(_tid);
	fm->qr(_qr);
	fm->opcode(_opcode);
	fm->aa(_aa);
	fm->tc(_tc);
	fm->rd(_rd);
	fm->ra(_ra);
	fm->z(_z);
	fm->rcode(_rcode);
	fm->nquery(_nquery);
	fm->nanswer(_nanswer);
	fm->nauth(_nauth);
	fm->nadd(_nadd);

	std::copy(payload.begin(), payload.end(), fm->payload());
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace dns */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
