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

#include <odtone/buffer.hpp>
#include <odtone/mihf/sqlite_handler.hpp>

///////////////////////////////////////////////////////////////////////////

namespace odtone { namespace mihf {

    sqlite_handler *sqlite_handler::ptr_instance = NULL;

    sqlite_handler::sqlite_handler()
    {
    }

    sqlite_handler *sqlite_handler::instance()
    {
      if (ptr_instance == NULL)
        ptr_instance = new sqlite_handler();

      return ptr_instance;
    }

    void sqlite_handler::init(const char *path)
    {
      int rc;
      rc = sqlite3_open(path, &_db);
      if(rc != SQLITE_OK)
        {
          std::cout << "Can't open database "
                    << sqlite3_errmsg(_db) << std::endl;
          exit(EXIT_FAILURE);
        }
    }


    sqlite_handler::~sqlite_handler()
    {
      sqlite3_close(_db);

      if (ptr_instance)
        delete ptr_instance;
    }

    int sqlite_handler::execute(const char *arg, ...)
    {
      va_list ap;
      va_start(ap, arg);
      char *qry = sqlite3_vmprintf(arg, ap);
      va_end(ap);

      char *err_msg = 0;
      int rc;
      std::cout << "SQL: " << qry << std::endl;
      rc = sqlite3_exec(_db, qry, 0, 0, &err_msg);
      if (err_msg)
        std::cout << "SQL ERROR: " << err_msg << std::endl;

      sqlite3_free(qry);
      sqlite3_free(err_msg);
      return rc;
    }

    long sqlite_handler::getval(const char *arg, ...)
    {
      va_list ap;
      va_start(ap, arg);

      sqlite_result *r = get_vmresult(arg, ap);
      va_end(ap);

      long n = 0;
      if (r)
        {
          if (fetch_row(r))
            {
              n = getval(r);
            }
        }

      free_result(r);
      return n;
    }

    std::string sqlite_handler::getstr(const char *arg, ...)
    {
      va_list ap;
      va_start(ap, arg);

      sqlite_result *r = get_vmresult(arg, ap);
      va_end(ap);

      std::string str;
      if (r)
        {
          if (fetch_row(r))
            {
              str = getstr(r);
            }
        }

      free_result(r);
      return str;
    }


    sqlite_result *sqlite_handler::get_vmresult(const char *arg, va_list ap)
    {
      sqlite_result *r = NULL;

      if (arg && ap)
        {
          char *qry = sqlite3_vmprintf(arg, ap);

          r = new sqlite_result();

          const char *s = 0;

          int rc = sqlite3_prepare(_db, qry, strlen(qry), &r->res, &s);

          if ((rc != SQLITE_OK) || !(r->res))
            {
              r->res = NULL;
              return r;
            }

          sqlite3_free(qry);
        }

      return r;
    }

    sqlite_result *sqlite_handler::get_result(const char *arg, ...)
    {
      va_list ap;
      va_start(ap, arg);

      sqlite_result *r = get_vmresult(arg, ap);
      va_end(ap);

      return r;

    }

    void sqlite_handler::free_result(sqlite_result *r)
    {
      if (r)
        {
          sqlite3_finalize(r->res);
          delete r;
        }
    }

    bool sqlite_handler::fetch_row(sqlite_result *r)
    {
      if(r && r->res)
        {
          int rc = sqlite3_step(r->res);
          r->row = 0;

          switch (rc)
            {
            case SQLITE_BUSY:
            case SQLITE_ERROR:
            case SQLITE_MISUSE:
            case SQLITE_DONE:
              return false;
            case SQLITE_ROW:
            case SQLITE_OK:
              return true;
            }
        }

      return false;
    }

    long sqlite_handler::getval(sqlite_result *r)
    {
      if (r && r->res)
        {
          return sqlite3_column_int(r->res, r->row++);
        }
      return 0;
    }


    std::string sqlite_handler::getstr(sqlite_result *r)
    {
      std::string str;
      if (r && r->res)
        {
          const unsigned char *tmp = sqlite3_column_text(r->res, r->row++);
          if (tmp)
            str.assign((const char *) tmp);
        }
      return str;
    }

	void sqlite_handler::getblob(sqlite_result *r,
								 std::vector<uint8> &blob)
	{
	  if (r && r->res)
		{
		  buffer<uint8> bytes(sqlite3_column_bytes(r->res, r->row++));

		  memcpy(bytes.get(), sqlite3_column_blob(r->res, r->row - 1), bytes.size());
		  blob.assign(bytes.get(), bytes.get() + bytes.size());
		}
	}


  } /* namespace mihf */ } /* namespace odtone */
///////////////////////////////////////////////////////////////////////////
