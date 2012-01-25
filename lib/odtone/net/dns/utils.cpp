//=============================================================================
// Brief   : DNS Utils
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

#include <odtone/net/dns/utils.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace dns {

/**
 * Parse a domain name. In the end the position is pointing to the
 * next byte after the domain name end.
 *
 * @param p Byte array containing the information.
 * @param pos Position in the byte array where to start parsing.
 * @return The domain name in the string form.
 */
std::string parse_domain_name(const unsigned char* p, int& pos)
{
	int nlen;
	bool pointer = false;
	std::string qname = "";

	for (int tmp = pos; p[tmp] != '\0'; ++tmp) {
		nlen = p[tmp];

		// It is a pointer
		if((nlen >> 6) == 0x3) {
			if(!pointer) {
				pos += 2;
			}
			tmp = (parse_uint16(p, tmp) & 0x3fff) - 12;
			nlen = p[tmp];
			pointer = true;
		}

		if(!pointer) {
			// String length + Lenght byte
			pos += nlen + 1;
		}

		// Parse String
		while(nlen > 0) {
			++tmp;
			qname += p[tmp];
			--nlen;
		}
		qname += ".";
	}
	// Erase dot inserted on the end
	if(qname.size() > 0)
		qname.erase(qname.size() - 1, 1);

	// Due to the "\0" string terminator
	if(!pointer) {
		++pos;
	}

	return qname;
}

/**
 * Parse a string. In the end the position is pointing to the
 * next byte after the string end.
 *
 * @param p Byte array containing the information.
 * @param pos Position in the byte array where to start parsing.
 * @return The string value.
 */
std::string parse_string(const unsigned char* p, int& pos)
{
	std::string str = "";

	// String size
	int nlen = p[pos];
	++pos;

	// Parse string
	for(int i = 0; i < nlen; ++i) {
		str += p[i + pos];
	}
	pos += nlen;

	return str;
}

/**
 * Parse an unsigned int16. In the end the position is pointing to the
 * next byte after the unsigned int16 end.
 *
 * @param p Byte array containing the information.
 * @param pos Position in the byte array where to start parsing.
 * @return The unsigned int16 value.
 */
uint16 parse_uint16(const unsigned char* p, int& pos)
{
	#define	UINT16(p)	(((p)[0] << 8) | (p)[1])
	uint16 qtype = UINT16(&p[pos]);
	pos += 2;
	return qtype;
}

/**
 * Parse an unsigned int32. In the end the position is pointing to the
 * next byte after the unsigned int32 end.
 *
 * @param p Byte array containing the information.
 * @param pos Position in the byte array where to start parsing.
 * @return The unsigned int32 value.
 */
uint32 parse_uint32(const unsigned char* p, int& pos)
{
	#define	UINT32(p)	(((p)[0] << 24) | ((p)[1] << 16) | ((p)[2] << 8) | (p)[3])
	uint32 qtype = UINT32(&p[pos]);
	pos += 4;
	return qtype;
}

/**
 * Parse a byte array. In the end the position is pointing to the
 * next byte after the byte array end.
 *
 * @param p Byte array containing the information.
 * @param pos Position in the byte array where to start parsing.
 * @param len Length of the byte array.
 * @return The byte array value.
 */
std::vector<uint8> parse_data(const unsigned char* p, int& pos, int len)
{
	std::vector<uint8> data;
	for(int i = 0; i < len; ++i) {
		uint8 tmp = p[pos + i];
		data.push_back(tmp);
	}
	pos += len;

	return data;
}

/**
 * Parse a A Resource Record. In the end the position is pointing to the
 * next byte after the A Resource Record end.
 *
 * @param p Byte array containing the information.
 * @param pos Position in the byte array where to start parsing.
 * @param len Length of the A Resource Record.
 * @return The A Resource Record value.
 */
dns::a_record parse_a_record(const unsigned char* p, int pos, int len)
{
	boost::asio::ip::address_v4::bytes_type bytes_value;
	for(int i = 0; i < len; ++i)
		bytes_value[i] = p[i + pos];

	boost::asio::ip::address_v4 ipv4(bytes_value);
	std::string ip = ipv4.to_string();

	dns::a_record record(ip);
	return record;
}

/**
 * Parse a AAAA Resource Record. In the end the position is pointing to the
 * next byte after the AAAA Resource Record end.
 *
 * @param p Byte array containing the information.
 * @param pos Position in the byte array where to start parsing.
 * @param len Length of the AAAA Resource Record.
 * @return The AAAA Resource Record value.
 */
dns::aaaa_record parse_aaaa_record(const unsigned char* p, int pos, int len)
{
	boost::asio::ip::address_v6::bytes_type bytes_value;
	for(int i = 0; i < len; ++i)
		bytes_value[i] = p[i + pos];

	boost::asio::ip::address_v6 ipv6(bytes_value);
	std::string ip = ipv6.to_string();

	dns::aaaa_record record(ip);

	return record;
}

/**
 * Parse a NAPTR Resource Record. In the end the position is pointing to the
 * next byte after the NAPTR Resource Record end.
 *
 * @param p Byte array containing the information.
 * @param pos Position in the byte array where to start parsing.
 * @param len Length of the NAPTR Resource Record.
 * @return The NAPTR Resource Record value.
 */
dns::naptr_record parse_naptr_record(const unsigned char* p, int pos, int len)
{
	uint16 order = parse_uint16(p, pos);
	uint16 preference = parse_uint16(p, pos);
	std::string flags = parse_string(p, pos);
	std::string service = parse_string(p, pos);
	std::string regex = parse_string(p, pos);
	std::string replacement = parse_domain_name(p, pos);

	dns::naptr_record record(order, preference, flags, service, regex, replacement);

	return record;
}

/**
 * Parse a SRV Resource Record. In the end the position is pointing to the
 * next byte after the SRV Resource Record end.
 *
 * @param p Byte array containing the information.
 * @param pos Position in the byte array where to start parsing.
 * @param len Length of the SRV Resource Record.
 * @return The SRV Resource Record value.
 */
dns::srv_record parse_srv_record(const unsigned char* p, int pos, int len)
{
	uint16 priority = parse_uint16(p, pos);
	uint16 weight = parse_uint16(p, pos);
	uint16 port = parse_uint16(p, pos);
	std::string target = parse_domain_name(p, pos);

	dns::srv_record record(priority, weight, port, target);

	return record;
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace dns */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
