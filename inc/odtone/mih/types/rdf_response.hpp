//=============================================================================
// Brief   : MIH RDF Information Query Response Types
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

#ifndef ODTONE_MIH_TYPES_RDF_RESPONSE__HPP_
#define ODTONE_MIH_TYPES_RDF_RESPONSE__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/mih/types/base.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
/**
 * IR_RDF_SCHEM_URL data type.
 */
typedef octet_string                  ir_rdf_schem_url;

/**
 * LIST(IR_RDF_SCHEM_URL) data type.
 */
typedef std::vector<ir_rdf_schem_url> ir_rdf_schem_url_list;

///////////////////////////////////////////////////////////////////////////////
/**
 * IR_RDF_DATA data type.
 */
struct ir_rdf_data {
	/**
	 * Construct a IR_RDF_DATA data type.
	 */
	ir_rdf_data() : _mime(null())
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
 * LIST(IR_RDF_DATA) data type.
 */
typedef std::vector<ir_rdf_data> ir_rdf_data_list;

///////////////////////////////////////////////////////////////////////////////
/**
 * IR_RDF_SCHEM data type.
 */
struct ir_rdf_schem {
	/**
	 * Construct a IQ_RDF_SCHEM data type.
	 */
	ir_rdf_schem() : _mime(null())
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
 * LIST(IR_RDF_SCHEM) data type.
 */
typedef std::vector<ir_rdf_schem> ir_rdf_schem_list;

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /*namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_TYPES_RDF_RESPONSE__HPP_ */
