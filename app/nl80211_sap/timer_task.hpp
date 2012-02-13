//=============================================================================
// Brief   : Timer Task
// Authors : André Prata <aprata@av.it.pt>
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

#include <boost/function.hpp>
#include <boost/asio.hpp>

#ifndef TIMER_TASK__HPP_
#define TIMER_TASK__HPP_


/**
 * This class allows the creation of asynchronous timed tasks, that run at specific intervals.
 */
class timer_task : boost::noncopyable
{
private:
	bool _running;
	boost::asio::deadline_timer _timer;
	const unsigned int _period;
	const boost::function<void()> _task;

	void task_handler(const boost::system::error_code& e);

public:
	/**
	 * Construct the Timer Task.
	 * 
	 * @param ios the io_service that the underlying deadline_timer will use.
	 * @param period the time period between task triggers, in milliseconds.
	 * @param task the task that will be ran at the specified interval.
	 */
	timer_task(boost::asio::io_service& ios, uint period, const boost::function<void()>& task);

	~timer_task();

	/**
	 * Run the Timer Task. The first task run will only occurr /period/ ms after calling.
	 */
	void start();

	/**
	 * Stop the Timer Task. To resume, just call start again.
	 */
	void stop();

	/**
	 * Check if the Timer Task is active.
	 * 
	 * @return True if the task is scheduled to run, false if the Timer Task is stopped.
	 */
	bool running();
};

#endif // TIMER_TASK__HPP_
