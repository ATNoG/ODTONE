//=============================================================================
// Brief   : MIH Identification Types
// Authors : Bruno Santos <bsantos@av.it.pt>
//           Simao Reis   <sreis@av.it.pt>
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
 * MIHF_ID data type.
 */
class id {
public:
	/**
	 * Construct an empty MIHF_ID.
	 */
	id() { }

	/**
	 * Construct a MIHF_ID.
	 *
	 * @param id MIHF ID string.
	 */
	explicit id(const octet_string& id) : _id(id) { }

	/**
	 * Assign the MIHF ID.
	 *
	 * @param id MIHF ID string.
	 */
	void assign(const octet_string& id)
	{
		_id = id;
	}

	/**
	 * Get the MIHF_ID.
	 *
	 * @return The MIHF ID string.
	 */
	const mih::octet_string& to_string() const
	{
		return _id;
	}

	/**
	 * Check if the MIHF_ID is equal to another MIHF_ID.
	 *
	 * @param other MIHF ID to compare with.
	 * @return True if they are equal or false otherwise.
	 */
	bool operator==(const id& other) const
	{
		return (_id.compare(other.to_string()) == 0);
	}

	/**
	 * Check if the MIHF_ID is different of another MIHF_ID.
	 *
	 * @param other MIHF ID to compare with.
	 * @return True if they are different or false otherwise.
	 */
	bool operator!=(const id& other) const
	{
		return (_id.compare(other.to_string()) != 0);
	}

	/**
	 * Serialize/deserialize the MIHF_ID data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & _id;
	}

private:
	octet_string _id;	/**< MIHF ID string.	*/
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /*namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_TYPES_IDENTIFICATION__HPP_ */
