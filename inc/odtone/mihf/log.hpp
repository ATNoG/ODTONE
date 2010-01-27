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

#ifndef ODTONE_MIHF_LOG_HPP
#define ODTONE_MIHF_LOG_HPP

#include <odtone/logger.hpp>

namespace odtone { namespace mihf {

class log_t
{
public:
	static logger* instance();
	~log_t();

private:
	static logger		*ptr_instance;
};

#define log (*log_t::instance())

} /* namespace mihf */ } /* namespace odtone */

#endif
