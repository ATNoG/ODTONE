//=============================================================================
// Brief   : MIH Binary Information Query Response Types
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

#ifndef ODTONE_MIH_TYPES_BIN_RESPONSE__HPP_
#define ODTONE_MIH_TYPES_BIN_RESPONSE__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/mih/types/base.hpp>
#include <odtone/mih/tlv.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
class ir_bin_data {
public:
	ir_bin_data()
	{ }

	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & _ar.buffer();
	}

	otlv output() { return otlv(_ar); }
	itlv input()  { return itlv(_ar); }

private:
	archive _ar;
};

typedef std::vector<ir_bin_data> ir_bin_data_list;

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /*namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_TYPES_BIN_RESPONSE__HPP_ */
