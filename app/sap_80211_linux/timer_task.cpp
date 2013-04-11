//=============================================================================
// Brief   : Run a task at specific intervals
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

#include "timer_task.hpp"

#include <boost/bind.hpp>

void timer_task::task_handler(const boost::system::error_code& e)
{
	if (!e) {
		_task();
		_timer.expires_from_now(boost::posix_time::milliseconds(_period));
		_timer.async_wait(boost::bind(&timer_task::task_handler, this, boost::asio::placeholders::error));
	}
}

timer_task::timer_task(boost::asio::io_service& ios, odtone::uint period, const boost::function<void()>& task)
	: _running(false), _timer(ios), _period(period), _task(task)
{
}

timer_task::~timer_task()
{
	//_timer.cancel();
}

void timer_task::start()
{
	_timer.expires_from_now(boost::posix_time::milliseconds(_period));
	_timer.async_wait(boost::bind(&timer_task::task_handler, this, boost::asio::placeholders::error));
	_running = true;
}

void timer_task::stop()
{
	_timer.cancel();
	_running = false;
}

bool timer_task::running()
{
	return _running;
}

odtone::uint timer_task::period()
{
	return _period;
}
