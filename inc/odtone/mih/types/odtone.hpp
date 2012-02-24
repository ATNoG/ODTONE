//=============================================================================
// Brief   : MIH ODTONE Specific Types
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

#ifndef ODTONE_MIH_TYPES_ODTONE__HPP_
#define ODTONE_MIH_TYPES_ODTONE__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/mih/types/base.hpp>
#include <odtone/mih/types/identification.hpp>
#include <odtone/mih/types/address.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////

/**
 * Define MOS_INFO data type.
 */
struct mos_info {
	/**
	 * Serialize/deserialize the MOS_INFO data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & id;
		ar & ip;
		ar & port;
	}

	/**
	 * Check if the MOS_INFO is equal to another MOS_INFO.
	 *
	 * @param other The MOS_INFO to compare with.
	 * @return True if they are equal or false otherwise.
	 */
	bool operator==(const mos_info& other) const
	{
		return ((id == other.id) || (ip == other.ip && port == other.port));
	}

	mih::id id;		/**< PoS identifier.	*/
	ip_addr ip;		/**< PoS IP address.	*/
	uint16 port;	/**< PoS listening port.*/
};

/**
 * Define MOS_DSCV data type.
 */
struct mos_dscv {
	/**
	 * Serialize/deserialize the MOS_DSCV data type.
	 *
	 * @param ar The archive to/from where serialize/deserialize the data type.
	 */
	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & is;
		ar & cs;
		ar & es;
	}

	std::vector<mos_info> is;	/**< List of PoS providing IS.	*/
	std::vector<mos_info> cs;	/**< List of PoS providing CS.	*/
	std::vector<mos_info> es;	/**< List of PoS providing ES.	*/
};

} /* namespace mih */ } /*namespace odtone */

#endif /* ODTONE_MIH_TYPES_ODTONE__HPP_ */
