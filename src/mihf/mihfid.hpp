//
// Copyright (c) 2007-2009 2009 Universidade Aveiro - Instituto de
// Telecomunicacoes Polo Aveiro
// This file is part of ODTONE - Open Dot Twenty One.
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//
// Author:     Simao Reis <sreis@av.it.pt>
//

#ifndef ODTONE_MIHF_ID_HPP
#define ODTONE_MIHF_ID_HPP

///////////////////////////////////////////////////////////////////////////////
#include <odtone/mih/types/identification.hpp>
///////////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

class mihfid_t
{
public:
  static mih::id* instance();
  ~mihfid_t();
  // void assign (const char *id);

private:
  mihfid_t();
  static mih::id *ptr_instance;
};

#define mihfid *mihfid_t::instance()

} /* namespace mihf */ } /* namespace odtone */

#endif
