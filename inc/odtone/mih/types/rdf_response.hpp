//=============================================================================
// Brief   : MIH RDF Information Query Response Types
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

#ifndef ODTONE_MIH_TYPES_RDF_RESPONSE__HPP_
#define ODTONE_MIH_TYPES_RDF_RESPONSE__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/mih/types/base.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
typedef octet_string                  ir_rdf_schem_url;
typedef std::vector<ir_rdf_schem_url> ir_rdf_schem_url_list;

///////////////////////////////////////////////////////////////////////////////
struct ir_rdf_data {
	ir_rdf_data() : _mime(null())
	{ }

	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & _mime;
		ar & _data;
	}

	boost::variant<null, octet_string> _mime;
	octet_string                       _data;
};

typedef std::vector<ir_rdf_data> ir_rdf_data_list;

///////////////////////////////////////////////////////////////////////////////
struct ir_rdf_schem {
	ir_rdf_schem() : _mime(null())
	{ }

	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & _mime;
		ar & _data;
	}

	boost::variant<null, octet_string> _mime;
	octet_string                       _data;
};

typedef std::vector<ir_rdf_schem> ir_rdf_schem_list;

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /*namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_TYPES_RDF_RESPONSE__HPP_ */
