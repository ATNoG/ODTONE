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

#include <odtone/mihf/transaction_ack_service.hpp>

namespace odtone { namespace mihf {

transaction_ack_service *transaction_ack_service::ptr_instance = NULL;

transaction_ack_service::transaction_ack_service()
{
}


transaction_ack_service::~transaction_ack_service()
{
  if (ptr_instance)
    delete ptr_instance;
}


transaction_ack_service *transaction_ack_service::instance()
{
  if (ptr_instance == NULL)
    ptr_instance = new transaction_ack_service();

  return ptr_instance;
}

  } /* namespace mihf */   } /* namespace odtone */
