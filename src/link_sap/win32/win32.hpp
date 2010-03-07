//=============================================================================
// Brief   : Win32 API Warpers
// Authors : Bruno Santos <bsantos@av.it.pt>
//
//
// Copyright (C) 2009 Universidade Aveiro - Instituto de Telecomunicacoes Polo Aveiro
//
// This file is part of ODTONE - Open Dot Twenty One.
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//=============================================================================

#ifndef LINK_SAP_WIN32__HPP_
#define LINK_SAP_WIN32__HPP_

///////////////////////////////////////////////////////////////////////////////
#include "../base.hpp"
#include <odtone/sap/nif/interface.hpp>
#include <boost/utility.hpp>
#include <boost/function.hpp>
#include <boost/logic/tribool.hpp>
#include <boost/shared_ptr.hpp>
#include <string>
#include <Windows.h>
#include <Wlanapi.h>

///////////////////////////////////////////////////////////////////////////////
namespace win {

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
handle wlan_open();

typedef boost::function<void(const WLAN_NOTIFICATION_DATA&)> wlan_register_notification_handler;

void wlan_register_notification(const handle& h, const wlan_register_notification_handler& handler);

std::string wstring_to_string(const wchar_t* str, size_t len);

std::string wstring_to_string(const wchar_t* str);

///////////////////////////////////////////////////////////////////////////////
typedef boost::shared_ptr<WLAN_INTERFACE_INFO_LIST> wlan_if_list;

wlan_if_list wlan_enum_interfaces(handle const& h);

///////////////////////////////////////////////////////////////////////////////
typedef boost::shared_ptr<WLAN_PROFILE_INFO_LIST> wlan_profile_list;

wlan_profile_list wlan_get_profile_list(const handle& h, const odtone::sap::nif::if_id& id);

///////////////////////////////////////////////////////////////////////////////
} /* namespace win */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* LINK_SAP_BASE__HPP_ */
