//=============================================================================
// Brief   : MIH Address Types
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

#ifndef ODTONE_MIH_TYPES_ADDRESS__HPP_
#define ODTONE_MIH_TYPES_ADDRESS__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/mih/types/base.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
typedef uint32 cell_id;

///////////////////////////////////////////////////////////////////////////////
class transport_addr {
protected:
	transport_addr(uint16 type) : _type(type)
	{ }

	transport_addr(uint16 type, const void* raw, size_t len)
		: _type(type), _addr(reinterpret_cast<const char*>(raw), len)
	{ }

public:
	uint16 type() const { return _type; }

	const void* get() const    { return _addr.data(); }
	size_t      length() const { return _addr.length(); }

	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & _type;
		ar & _addr;
	}

protected:
	uint16       _type;
	octet_string _addr;
};

///////////////////////////////////////////////////////////////////////////////
class mac_addr : public transport_addr {
public:
	mac_addr() : transport_addr(6)
	{ }

	explicit mac_addr(const octet_string& addr) : transport_addr(6)
	{
		this->address(addr);
	}

	mac_addr(const void* raw, size_t len) : transport_addr(6, raw, len)
	{ }

	octet_string address() const;
	void         address(const octet_string& addr);

	friend std::ostream& operator<<(std::ostream& os, const mac_addr& tp)
	{
		os << "\ntype: " << tp.type();
		os << "\naddress: " << tp.address();

		return os;
	}

	bool operator==(const mac_addr& other) const
	{
		return ((type() == other.type()) && (address().compare(other.address()) == 0));
	}
};

///////////////////////////////////////////////////////////////////////////////
struct l2_3gpp_2g_cell_id {
	uint8  plmn_id[3];
	uint8  lac[2];
	uint16 ci;

	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & plmn_id[0];
		ar & plmn_id[1];
		ar & plmn_id[2];
		ar & lac[0];
		ar & lac[1];
		ar & ci;
	}

	friend std::ostream& operator<<(std::ostream& out, const l2_3gpp_2g_cell_id&)
	{
		return out;
	}
};

struct l2_3gpp_3g_cell_id {
	uint8  plmn_id[3];
	uint32 cell_id;

	template<class ArchiveT>
	void serialize(ArchiveT& ar)
	{
		ar & plmn_id[0];
		ar & plmn_id[1];
		ar & plmn_id[2];
		ar & cell_id;
	}

	friend std::ostream& operator<<(std::ostream& out, const l2_3gpp_3g_cell_id&)
	{
		return out;
	}

	bool operator==(const l2_3gpp_3g_cell_id& other) const
	{
		return ((cell_id == other.cell_id)
				&& (plmn_id[0] == other.plmn_id[0])
				&& (plmn_id[1] == other.plmn_id[1])
				&& (plmn_id[2] == other.plmn_id[2]));
	}
};

///////////////////////////////////////////////////////////////////////////////
typedef octet_string l2_3gpp_addr;
typedef octet_string l2_3gpp2_addr;
typedef octet_string other_l2_addr;

///////////////////////////////////////////////////////////////////////////////
typedef boost::variant<mac_addr,
					   l2_3gpp_3g_cell_id //,
					   // l2_3gpp_2g_cell_id,
					   // l2_3gpp_addr,
					   // l2_3gpp2_addr,
					   // other_l2_addr
					   > link_addr;

typedef std::vector<link_addr> link_addr_list;

///////////////////////////////////////////////////////////////////////////////
class ip_addr : public transport_addr {
public:
	enum type {
		none = 0,
		ipv4 = 1,
		ipv6 = 2,
	};

	ip_addr(type tp = none) : transport_addr(tp)
	{ }

	ip_addr(type tp, const void* raw, size_t len)
		: transport_addr(tp, raw, len)
	{ }

//	octet_string address() const;
//	void         address(const octet_string& addr);
};

typedef ip_addr dhcp_serv;
typedef ip_addr fn_agent;
typedef ip_addr acc_rtr;

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /*namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_TYPES_ADDRESS__HPP_ */
