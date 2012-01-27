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

#include "win32.hpp"
#include <odtone/cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/system/system_error.hpp>
#include <boost/bind.hpp>
#include <boost/scoped_ptr.hpp>
#include <cstring>

#pragma comment(lib, "wlanapi.lib")

///////////////////////////////////////////////////////////////////////////////
namespace link_sap { namespace win32 { namespace detail {

///////////////////////////////////////////////////////////////////////////////
static void wlan_close(void* h)
{
	::WlanCloseHandle(h, nullptr);
}

static void WINAPI wlan_notify_handler(PWLAN_NOTIFICATION_DATA data, void* context)
{
	wlan_register_notification_handler* pcb = reinterpret_cast<wlan_register_notification_handler*>(context);
	wlan_register_notification_handler& cb = *pcb;

	if (data->NotificationSource == WLAN_NOTIFICATION_SOURCE_NONE) {
		delete pcb;
		return;
	}

	if (cb)
		cb(*data);
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace detail */

///////////////////////////////////////////////////////////////////////////////
handle wlan_open()
{
	DWORD res;
	DWORD ver;
	HANDLE h;

	res = ::WlanOpenHandle(WLAN_API_VERSION, nullptr, &ver, &h);
	if (res != ERROR_SUCCESS)
		boost::throw_exception(boost::system::system_error(res,
														   boost::system::get_system_category(),
														   "win::wlan_open"));

	return handle(h, detail::wlan_close);
}

void wlan_register_notification(handle const& h, wlan_register_notification_handler const& handler)
{
	wlan_register_notification_handler* cb = new wlan_register_notification_handler(handler);
	DWORD res;

	res = ::WlanRegisterNotification(h.get(), WLAN_NOTIFICATION_SOURCE_ALL, TRUE,
									 detail::wlan_notify_handler, cb,
									 nullptr, nullptr);
	if (res == ERROR_SUCCESS)
		return;

	delete cb;
	boost::throw_exception(boost::system::system_error(res,
													   boost::system::get_system_category(),
													   "win::wlan_register_notification"));
}

wlan_if_list wlan_enum_interfaces(handle const& h)
{
	WLAN_INTERFACE_INFO_LIST* iflist = nullptr;
	DWORD res;

	res = ::WlanEnumInterfaces(h.get(), nullptr, &iflist);
	if (res == ERROR_SUCCESS)
		return wlan_if_list(iflist, ::WlanFreeMemory);

	boost::throw_exception(boost::system::system_error(res,
													   boost::system::get_system_category(),
													   "win::wlan_enum_interfaces"));
	return wlan_if_list();
}

MIB_IF_ROW2 get_interface_info(const GUID& guid)
{
    MIB_IF_ROW2 iinf;

    std::memset(&iinf, 0, sizeof(iinf));
        
    DWORD res = ::ConvertInterfaceGuidToLuid(&guid, &iinf.InterfaceLuid);
    if(res != NO_ERROR)
        boost::throw_exception(boost::system::system_error(res,
														   boost::system::get_system_category(),
														   "ConvertInterfaceGuidToLuid"));
    res = ::GetIfEntry2(&iinf);
    if(res != NO_ERROR)
        boost::throw_exception(boost::system::system_error(res,
														   boost::system::get_system_category(),
														   "GetIfEntry2"));
    return iinf;
}

///////////////////////////////////////////////////////////////////////////////
std::string wstring_to_string(wchar_t const* str, size_t len)
{
	std::string tmp;
	int res;

	res = ::WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, str, odtone::truncate_cast<int>(len), nullptr, 0, nullptr, FALSE);
	if (res > 0) {
		tmp.resize(res);
		::WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, str, odtone::truncate_cast<int>(len), &tmp[0], res, nullptr, FALSE);
		tmp.resize(res - 1);

	} else {
		boost::throw_exception(boost::system::system_error(::GetLastError(),
														   boost::system::get_system_category(),
														   "win::wstring_to_string"));
	}

	return tmp;
}

std::string wstring_to_string(wchar_t const* str)
{
	return wstring_to_string(str, std::wcslen(str));
}

std::string wstring_to_string(std::wstring const& str)
{
	return wstring_to_string(str.c_str(), str.size());
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace win32 */ } /* namespace link_sap */

// EOF ////////////////////////////////////////////////////////////////////////
