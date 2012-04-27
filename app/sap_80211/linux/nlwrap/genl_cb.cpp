//=============================================================================
// Brief   : GENetlink callback RAI wrapper
// Authors : André Prata <andreprata@av.it.pt>
//-----------------------------------------------------------------------------
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

#include "genl_cb.hpp"
#include <stdexcept>

namespace nlwrap {

int no_seq_check(::nl_msg *msg, void *arg)
{
    return NL_OK;
}

int error_handler(::sockaddr_nl *nla, ::nlmsgerr *err, void *arg)
{
	int *ret = (int *)arg;
	*ret = err->error;
	return NL_STOP;
}

int finish_handler(::nl_msg *msg, void *arg)
{
	int *ret = (int *)arg;
	*ret = 0;
	return NL_SKIP;
}

int ack_handler(::nl_msg *msg, void *arg)
{
	int *ret = (int *)arg;
	*ret = 0;
	return NL_STOP;
}

genl_cb::genl_cb() : _err(1)
{
	_cb = ::nl_cb_alloc(NL_CB_DEFAULT);
	if (!_cb) {
		throw std::runtime_error("Error allocating nl_cb");
	}

	if (::nl_cb_set(_cb, NL_CB_SEQ_CHECK, NL_CB_CUSTOM, no_seq_check, NULL)) {
		throw std::runtime_error("Error setting no_sequence_check callback");
	}

	if (::nl_cb_set(_cb, NL_CB_FINISH, NL_CB_CUSTOM, finish_handler, static_cast<void *>(&_err))) {
		throw std::runtime_error("Error setting finish_handler callback");
	}

	if (::nl_cb_set(_cb, NL_CB_ACK, NL_CB_CUSTOM, ack_handler, static_cast<void *>(&_err))) {
		throw std::runtime_error("Error setting ack_handler callback");
	}

	if (::nl_cb_err(_cb, NL_CB_CUSTOM, error_handler, static_cast<void *>(&_err))) {
		throw std::runtime_error("Error setting error_handler callback");
	}
}

genl_cb::genl_cb(::nl_recvmsg_msg_cb_t func, void *arg) : _err(1)
{
	_cb = ::nl_cb_alloc(NL_CB_DEFAULT);
	if (!_cb) {
		throw std::runtime_error("Error allocating nl_cb");
	}

	if (::nl_cb_set(_cb, NL_CB_SEQ_CHECK, NL_CB_CUSTOM, no_seq_check, NULL)) {
		throw std::runtime_error("Error setting no_sequence_check callback");
	}

	if (::nl_cb_set(_cb, NL_CB_FINISH, NL_CB_CUSTOM, finish_handler, static_cast<void *>(&_err))) {
		throw std::runtime_error("Error setting finish_handler callback");
	}

	if (::nl_cb_set(_cb, NL_CB_ACK, NL_CB_CUSTOM, ack_handler, static_cast<void *>(&_err))) {
		throw std::runtime_error("Error setting ack_handler callback");
	}

	if (::nl_cb_err(_cb, NL_CB_CUSTOM, error_handler, static_cast<void *>(&_err))) {
		throw std::runtime_error("Error setting error_handler callback");
	}

	if (::nl_cb_set(_cb, NL_CB_VALID, NL_CB_CUSTOM, func, arg)) {
		throw std::runtime_error("Error setting custom callback");
	}
}

genl_cb::~genl_cb()
{
	if (_cb) {
		::nl_cb_put(_cb);
	}
}

void genl_cb::custom(::nl_recvmsg_msg_cb_t func, void *arg)
{
	if (::nl_cb_set(_cb, NL_CB_VALID, NL_CB_CUSTOM, func, arg)) {
		throw std::runtime_error("Error setting custom callback");
	}
}

bool genl_cb::finish()
{
	return _err <= 0;
}

bool genl_cb::error()
{
	return _err < 0;
}

int genl_cb::error_code()
{
	return _err;
}

genl_cb::operator ::nl_cb *()
{
	return _cb;
}

}

