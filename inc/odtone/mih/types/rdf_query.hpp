//=============================================================================
// Brief   : MIH RDF Query Types
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

#ifndef ODTONE_MIH_TYPES_RDF_QUERY__HPP_
#define ODTONE_MIH_TYPES_RDF_QUERY__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/mih/types/base.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
/**
 * Define IQ_RDF_SCHEMA data type.
 */
typedef octet_string               iq_rdf_schema;

/**
 * Define LIST(IQ_RDF_SCHEMA) data type.
 */
typedef std::vector<iq_rdf_schema> iq_rdf_schema_list;

///////////////////////////////////////////////////////////////////////////////
/**
 * Define IQ_RDF_DATA data type.
 */
struct iq_rdf_data {
	iq_rdf_data() : _mime(null())
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

/**
 * Define LIST(IQ_RDF_DATA) data type.
 */
typedef std::vector<iq_rdf_data> iq_rdf_data_list;

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /*namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_TYPES_RDF_QUERY__HPP_ */
