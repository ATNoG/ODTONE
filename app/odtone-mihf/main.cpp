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

#include <iostream>
#include <odtone/debug.hpp>
#include <odtone/mih/config.hpp>
#include <odtone/mihf/mihf.hpp>

// This file defines a macro that contains the path to the default
// configuration file
#ifndef ODTONE_CONFIG
#define ODTONE_CONFIG "odtone.conf"
#endif

int
main(int argc, char **argv)
{
  odtone::setup_crash_handler();

  odtone::mih::config cfg(argc, argv, ODTONE_CONFIG);
  odtone::mihf::mihf mihf;

  std::cout << ODTONE_CONFIG << std::endl;

  mihf.init(cfg);
  mihf.run();

  return EXIT_SUCCESS;
}
