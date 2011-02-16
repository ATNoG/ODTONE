//=============================================================================
// Brief   : MIH Identification Types
// Authors : Bruno Santos <bsantos@av.it.pt>
//           Simao Reis   <sreis@av.it.pt>
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

#ifndef ODTONE_MIH_TYPES_IDENTIFICATION__HPP_
#define ODTONE_MIH_TYPES_IDENTIFICATION__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/debug.hpp>
#include <odtone/mih/types/base.hpp>
#include <odtone/mih/types/link.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
/**
 * Define MIHF_ID data type.
 */
class id {
public:
	id() { }

	explicit id(const octet_string& id) : _id(id) { }

	void assign(const octet_string& id) { _id = id; }

	const mih::octet_string& to_string() const { return _id; }

	bool operator==(const id& other) const
	{
		return (_id.compare(other.to_string()) == 0);
	}

	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & _id;
	}

private:
	octet_string _id;
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /*namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_TYPES_IDENTIFICATION__HPP_ */
