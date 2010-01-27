//=============================================================================
// Brief   : MIH Location Types
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

#ifndef ODTONE_MIH_TYPES_LOCATION__HPP_
#define ODTONE_MIH_TYPES_LOCATION__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/mih/types/base.hpp>
#include <odtone/mih/types/address.hpp>
#include <odtone/mih/types/information.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
typedef octet_string            xml_civic_location;
typedef octet_string            civic_addr;
typedef boost::array<uint8, 16> bin_geo_location;
typedef octet_string            xml_geo_location;

///////////////////////////////////////////////////////////////////////////////
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
typedef boost::variant<bin_civic_location,
					   xml_civic_location> civic_location;

///////////////////////////////////////////////////////////////////////////////
typedef boost::variant<bin_geo_location,
					   xml_geo_location> geo_location;

///////////////////////////////////////////////////////////////////////////////
typedef boost::variant<civic_location,
					   geo_location,
					   cell_id> location;

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /*namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_TYPES_LOCATION__HPP_ */
