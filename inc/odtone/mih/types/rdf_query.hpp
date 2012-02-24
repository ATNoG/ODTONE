//=============================================================================
// Brief   : MIH RDF Query Types
// Authors : Bruno Santos <bsantos@av.it.pt>
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

#ifndef ODTONE_MIH_TYPES_RDF_QUERY__HPP_
#define ODTONE_MIH_TYPES_RDF_QUERY__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/mih/types/base.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
/**
 * IQ_RDF_SCHEMA data type.
 */
typedef octet_string               iq_rdf_schema;

/**
 * LIST(IQ_RDF_SCHEMA) data type.
 */
typedef std::vector<iq_rdf_schema> iq_rdf_schema_list;

///////////////////////////////////////////////////////////////////////////////
/**
 * IQ_RDF_DATA data type.
 */
struct iq_rdf_data {
	/**
	 * Construct a IQ_RDF_DATA data type.
	 */
	iq_rdf_data() : _mime(null())
	{ }

	/**
	 * Serialize/deserialize the IQ_RDF_DATA data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & _mime;
		ar & _data;
	}

	boost::variant<null, octet_string> _mime;	/**< MIME type.			*/
	octet_string                       _data;	/**< Value of the MIME.	*/
};

/**
 * LIST(IQ_RDF_DATA) data type.
 */
typedef std::vector<iq_rdf_data> iq_rdf_data_list;

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /*namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_TYPES_RDF_QUERY__HPP_ */
