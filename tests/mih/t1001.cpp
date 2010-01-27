//=============================================================================
// Brief     : Base Serialization Unit Tests
// Copyright : © 2009 Instituto de Telecomunicações
//=============================================================================

#include <odtone/debug.hpp>
#include <odtone/mih/indication.hpp>
#include <odtone/mih/tlv_types.hpp>
#include <algorithm>
#include <cstdlib>
#include <cassert>
#include <string>
#include <list>

///////////////////////////////////////////////////////////////////////////////
void t1001()
{
	using namespace odtone;

	mih::link_det_info_list arg1;
	mih::link_det_info_list arg2;
	mih::message msg1;
	mih::message msg2;
	mih::frame_vla fm;
	mih::frame* frame;

	msg1 << mih::indication(mih::indication::link_detected)
		 & mih::tlv_link_det_info_list(arg1);

	msg1.get_frame(fm);
	frame = mih::frame::cast(fm.get(), fm.size());
	ODTONE_ASSERT_PTR(frame);
	msg2 = *frame;

	msg2 >> mih::indication()
		 & mih::tlv_link_det_info_list(arg2);
}

// EOF ////////////////////////////////////////////////////////////////////////
