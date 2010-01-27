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

#ifndef ODTONE_SQLITE_HANDLER
#define ODTONE_SQLITE_HANDLER

#include <sqlite3.h>
#include <string>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <cstdarg>
#include <vector>

#include <odtone/base.hpp>

namespace odtone { namespace mihf {

    class sqlite_result
    {
    public:

      sqlite_result()
        : row(0)
      {
        res = NULL;
      }

      sqlite3_stmt *res;
      unsigned long row;
    };

    class sqlite_handler
    {
    public:

      static sqlite_handler *instance();

      ~sqlite_handler();

      void init(const char *path);

      int execute(const char *, ...);

      long getval(const char *, ...);
      std::string getstr(const char *, ...);

      sqlite_result *get_result(const char *, ...);

      void free_result(sqlite_result *r);
      bool fetch_row(sqlite_result *);

      long getval(sqlite_result *r);
      std::string getstr(sqlite_result *r);
	  void getblob(sqlite_result *r, std::vector<uint8> &blob);

      sqlite3 *_db;

    private:
      sqlite_handler();
      static sqlite_handler *ptr_instance;

      sqlite_result *get_vmresult(const char *, va_list);

    };

#define db sqlite_handler::instance()

  } /* namespace mihf */ } /* namespace odtone */

#endif
