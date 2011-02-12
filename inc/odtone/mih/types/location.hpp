//=============================================================================
// Brief   : MIH Location Types
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

#ifndef ODTONE_MIH_TYPES_LOCATION__HPP_
#define ODTONE_MIH_TYPES_LOCATION__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/mih/types/base.hpp>
#include <odtone/mih/types/address.hpp>
#include <odtone/mih/types/information.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
/**
 * Define XML_CIVIC_LOCATION data type.
 */
typedef octet_string xml_civic_location;

/**
 * Define CIVIC_ADDR data type.
 */
typedef octet_string civic_addr;

/**
 * Define BIN_GEO_LOCATION data type.
 */
typedef boost::array<uint8, 16> bin_geo_location;

/**
 * Define XML_GEO_LOCATION data type.
 */
typedef octet_string xml_geo_location;

///////////////////////////////////////////////////////////////////////////////
/**
 * Define BIN_CIVIC_LOCATION data type.
 */
struct bin_civic_location {
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & _country_code;
		ar & _civic_addr;
	}


	cntry_code	_country_code;
	civic_addr  _civic_addr;
};

///////////////////////////////////////////////////////////////////////////////
/**
 * Define CIVIC_LOCATION data type.
 */
typedef boost::variant<bin_civic_location,
					   xml_civic_location> civic_location;

///////////////////////////////////////////////////////////////////////////////
/**
 * Define GEO_LOCATION data type.
 */
typedef boost::variant<bin_geo_location,
					   xml_geo_location> geo_location;

///////////////////////////////////////////////////////////////////////////////
/**
 * Define LOCATION data type.
 */
typedef boost::variant<civic_location,
					   geo_location,
					   cell_id> location;

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /*namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_TYPES_LOCATION__HPP_ */
