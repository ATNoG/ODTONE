//=============================================================================
// Brief   : MIHF Main Entry Point
// Authors : Bruno Santos <bsantos@av.it.pt>
// ----------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2012-2013 Universidade Aveiro
// Copyright (C) 2012-2013 Instituto de Telecomunicações - Pólo Aveiro
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//=============================================================================

#include "core.hpp"
#include <boost/thread/thread.hpp>
#include <boost/asio/io_service.hpp>
#include <exception>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mihf {

///////////////////////////////////////////////////////////////////////////////
send_message_functor send_message;

///////////////////////////////////////////////////////////////////////////////
void main()
{
	size_t                  hc(boost::thread::hardware_concurrency());
	boost::asio::io_service ios(hc);
	boost::thread_group     tg;
	core                    cs("hmm");

	//TODO: init MIHF

	for (size_t i = 1; i < hc; ++i)
		tg.create_thread(boost::bind(&boost::asio::io_service::run, &ios));

	ios.run();
	tg.join_all();
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace mihf */ } /* namespace odtone */

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
	try {
		odtone::mihf::main();

	} catch (std::exception& e) {
		std::printf("fatal: %s\n", e.what());
		return 1;
	}

	return 0;
}

// EOF ////////////////////////////////////////////////////////////////////////
