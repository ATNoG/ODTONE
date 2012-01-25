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

#ifndef ODTONE_DNS_UTILS__HPP_
#define ODTONE_DNS_UTILS__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <string>
#include <vector>

#include <odtone/base.hpp>
#include <odtone/net/dns/types.hpp>

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
std::string parse_domain_name(const unsigned char* p, int& pos);

/**
 * Parse a string. In the end the position is pointing to the
 * next byte after the string end.
 *
 * @param p Byte array containing the information.
 * @param pos Position in the byte array where to start parsing.
 * @return The string value.
 */
std::string parse_string(const unsigned char* p, int& pos);

/**
 * Parse an unsigned int16. In the end the position is pointing to the
 * next byte after the unsigned int16 end.
 *
 * @param p Byte array containing the information.
 * @param pos Position in the byte array where to start parsing.
 * @return The unsigned int16 value.
 */
uint16 parse_uint16(const unsigned char* p, int& pos);

/**
 * Parse an unsigned int32. In the end the position is pointing to the
 * next byte after the unsigned int32 end.
 *
 * @param p Byte array containing the information.
 * @param pos Position in the byte array where to start parsing.
 * @return The unsigned int32 value.
 */
uint32 parse_uint32(const unsigned char* p, int& pos);

/**
 * Parse a byte array. In the end the position is pointing to the
 * next byte after the byte array end.
 *
 * @param p Byte array containing the information.
 * @param pos Position in the byte array where to start parsing.
 * @param len Length of the byte array.
 * @return The byte array value.
 */
std::vector<uint8> parse_data(const unsigned char* p, int& pos, int len);

/**
 * Parse a A Resource Record. In the end the position is pointing to the
 * next byte after the A Resource Record end.
 *
 * @param p Byte array containing the information.
 * @param pos Position in the byte array where to start parsing.
 * @param len Length of the A Resource Record.
 * @return The A Resource Record value.
 */
a_record parse_a_record(const unsigned char* p, int pos, int len);

/**
 * Parse a AAAA Resource Record. In the end the position is pointing to the
 * next byte after the AAAA Resource Record end.
 *
 * @param p Byte array containing the information.
 * @param pos Position in the byte array where to start parsing.
 * @param len Length of the AAAA Resource Record.
 * @return The AAAA Resource Record value.
 */
aaaa_record parse_aaaa_record(const unsigned char* p, int pos, int len);

/**
 * Parse a NAPTR Resource Record. In the end the position is pointing to the
 * next byte after the NAPTR Resource Record end.
 *
 * @param p Byte array containing the information.
 * @param pos Position in the byte array where to start parsing.
 * @param len Length of the NAPTR Resource Record.
 * @return The NAPTR Resource Record value.
 */
naptr_record parse_naptr_record(const unsigned char* p, int pos, int len);

/**
 * Parse a SRV Resource Record. In the end the position is pointing to the
 * next byte after the SRV Resource Record end.
 *
 * @param p Byte array containing the information.
 * @param pos Position in the byte array where to start parsing.
 * @param len Length of the SRV Resource Record.
 * @return The SRV Resource Record value.
 */
srv_record parse_srv_record(const unsigned char* p, int pos, int len);

///////////////////////////////////////////////////////////////////////////////
} /* namespace dns */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_DNS_UTILS__HPP_ */
