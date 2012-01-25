//==============================================================================
// Brief   : Win32 API Warpers
// Authors : Bruno Santos <bsantos@av.it.pt>
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

#ifndef LINK_SAP_WIN32__HPP_
#define LINK_SAP_WIN32__HPP_

///////////////////////////////////////////////////////////////////////////////
#include "../base.hpp"
#include "../interface/interface.hpp"
#include <boost/utility.hpp>
#include <boost/function.hpp>
#include <boost/logic/tribool.hpp>
#include <boost/shared_ptr.hpp>
#include <ws2tcpip.h>
#include <Iphlpapi.h>
#include <string>
#include <Wlanapi.h>
#pragma comment(lib, "iphlpapi.lib")

///////////////////////////////////////////////////////////////////////////////
namespace link_sap { namespace win32 {

///////////////////////////////////////////////////////////////////////////////
class handle {
public:
	handle() : _h(nullptr)
	{ }

	template<class CloseHandle>
	handle(void* h, CloseHandle ch)
		: _h(h), _close_handle(ch)
	{ }

	~handle()
	{
		if (_close_handle)
			_close_handle(_h);
	}

	handle(handle& h) : _h(h._h)
	{
		h._h = nullptr;
		std::swap(_close_handle, h._close_handle);
	}

	handle& operator=(handle& h)
	{
		if (this != &h) {
			std::swap(_h, h._h);
			std::swap(_close_handle, h._close_handle);
			h.close();
		}

		return *this;
	}

	void close()
	{
		if (_close_handle)
			_close_handle(_h);

		_h = nullptr;
		_close_handle = 0;
	}

	void* get() const { return _h; }

private:
	void*                        _h;
	boost::function<void(void*)> _close_handle;
};

///////////////////////////////////////////////////////////////////////////////
typedef boost::function<void(const WLAN_NOTIFICATION_DATA&)> wlan_register_notification_handler;
typedef boost::shared_ptr<WLAN_INTERFACE_INFO_LIST>          wlan_if_list;

handle       wlan_open();
void       	 wlan_register_notification(handle const& h, wlan_register_notification_handler const& handler);
wlan_if_list wlan_enum_interfaces(handle const& h);
MIB_IF_ROW2  get_interface_info(const GUID& guid);


///////////////////////////////////////////////////////////////////////////////
std::string wstring_to_string(wchar_t const* str);
std::string wstring_to_string(wchar_t const* str, size_t len);
std::string wstring_to_string(std::wstring const& str);

///////////////////////////////////////////////////////////////////////////////
} /* namespace win32 */ } /* namespace link_sap */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* LINK_SAP_BASE__HPP_ */
