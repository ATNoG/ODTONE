//=============================================================================
// Brief   : Archive for MIH Types Serialization
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

#include <odtone/mih/archive.hpp>
#include <odtone/cast.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
archive::archive() : _pos(0)
{
}

archive::~archive()
{
}

void archive::clear()
{
	_buf.resize(0);
	_pos = 0;
}

void archive::swap(std::vector<uint8>& buffer)
{
	_buf.swap(buffer);
	_pos = 0;
}

void archive::buffer(const uint8* buf, size_t len)
{
	_buf.resize(len);
	_pos = 0;
	std::copy(buf, buf + len, _buf.begin());
}

std::vector<uint8>& archive::buffer()
{
	return _buf;
}

void archive::rewind(uint pos)
{
	_pos = pos;
}

///////////////////////////////////////////////////////////////////////////////
iarchive& iarchive::operator&(bool& val)
{
	uint8 tmp;

	*this & tmp;
	val = bool(tmp);

	return *this;
}

iarchive& iarchive::operator&(uint8& val)
{
	if ((_pos + 1) > _buf.size())
		boost::throw_exception(iarchive_eof_error());

	val = _buf[_pos];
	_pos += 1;

	return *this;
}

iarchive& iarchive::operator&(uint16& val)
{
	if ((_pos + 2) > _buf.size())
		boost::throw_exception(iarchive_eof_error());

	val = (uint16(_buf[_pos    ]) <<  8)
		| (uint16(_buf[_pos + 1])      );
	_pos += 2;

	return *this;
}

iarchive& iarchive::operator&(uint32& val)
{
	if ((_pos + 4) > _buf.size())
		boost::throw_exception(iarchive_eof_error());

	val = (uint32(_buf[_pos    ]) << 24)
		| (uint32(_buf[_pos + 1]) << 16)
		| (uint32(_buf[_pos + 2]) <<  8)
		| (uint32(_buf[_pos + 3])      );
	_pos += 4;

	return *this;
}

iarchive& iarchive::operator&(uint64& val)
{
	if ((_pos + 8) > _buf.size())
		boost::throw_exception(iarchive_eof_error());

	val = (uint64(_buf[_pos    ]) << 56)
		| (uint64(_buf[_pos + 1]) << 48)
		| (uint64(_buf[_pos + 2]) << 40)
		| (uint64(_buf[_pos + 3]) << 32)
		| (uint64(_buf[_pos + 4]) << 24)
		| (uint64(_buf[_pos + 5]) << 16)
		| (uint64(_buf[_pos + 6]) <<  8)
		| (uint64(_buf[_pos + 7])      );
	_pos += 8;

	return *this;
}

iarchive& iarchive::operator&(sint8& val)
{
	uint8 tmp;

	if (val < 0) {
		tmp = -val;
		tmp = ~tmp + 1;
	} else {
		tmp = val;
	}

	return *this & tmp;
}

iarchive& iarchive::operator&(sint16& val)
{
	uint16 tmp;

	if (val < 0) {
		tmp = -val;
		tmp = ~tmp + 1;
	} else {
		tmp = val;
	}

	return *this & tmp;
}


iarchive& iarchive::operator&(sint32& val)
{
	uint32 tmp;

	if (val < 0) {
		tmp = -val;
		tmp = ~tmp + 1;
	} else {
		tmp = val;
	}

	return *this & tmp;
}

iarchive& iarchive::operator&(sint64& val)
{
	uint64 tmp;

	if (val < 0) {
		tmp = -val;
		tmp = ~tmp + 1;
	} else {
		tmp = val;
	}

	return *this & tmp;
}

iarchive& iarchive::operator&(octet_string& val)
{
	uint pos = _pos;
	uint len = list_length();

	if ((pos + len) >= _buf.size()) {
		_pos = pos;
		boost::throw_exception(iarchive_eof_error());
	}

	try {
		val.resize(len);

	} catch (...) {
		_pos = pos;
		throw;
	}
	std::copy(_buf.begin() + _pos, _buf.begin() + _pos + len, val.begin());
	_pos += len;

	return *this;
}

iarchive& iarchive::operator&(std::vector<uint8>& buf)
{
	uint pos = _pos;
	uint len = list_length();

	if ((pos + len) >= _buf.size()) {
		_pos = pos;
		boost::throw_exception(iarchive_eof_error());
	}

	try {
		buf.resize(len);

	} catch (...) {
		_pos = pos;
		throw;
	}
	std::copy(_buf.begin() + _pos, _buf.begin() + _pos + len, buf.begin());
	_pos += len;

	return *this;
}

uint iarchive::list_length()
{
	size_t size = _buf.size();
	uint pos = _pos;
	uint len;
	uint8 n;

	if (pos >= size)
		boost::throw_exception(iarchive_eof_error());

	n = _buf[pos++];
	if (n > 128) {
		n &= 0x7F;
		if ((pos + n) >= size)
			boost::throw_exception(iarchive_eof_error());
		len = 128;
		while (n--)
			len += _buf[pos++];

	} else {
		len = n;
	}
	_pos = pos;

	return len;
}

///////////////////////////////////////////////////////////////////////////////
oarchive& oarchive::operator&(bool val)
{
	_buf.resize(_pos + 1);
	_buf[_pos] = uint8(val);
	_pos += 1;

	return *this;
}

oarchive& oarchive::operator&(uint8 val)
{
	_buf.resize(_pos + 1);
	_buf[_pos] = val;
	_pos += 1;

	return *this;
}

oarchive& oarchive::operator&(uint16 val)
{
	_buf.resize(_pos + 2);
	_buf[_pos    ] = (val >>  8) & 0xFF;
	_buf[_pos + 1] = (val      ) & 0xFF;
	_pos += 2;

	return *this;
}

oarchive& oarchive::operator&(uint32 val)
{
	_buf.resize(_pos + 4);
	_buf[_pos    ] = (val >> 24) & 0xFF;
	_buf[_pos + 1] = (val >> 16) & 0xFF;
	_buf[_pos + 2] = (val >>  8) & 0xFF;
	_buf[_pos + 3] = (val      ) & 0xFF;
	_pos += 4;

	return *this;
}

oarchive& oarchive::operator&(uint64 val)
{
	_buf.resize(_pos + 8);
	_buf[_pos    ] = (val >> 56) & 0xFF;
	_buf[_pos + 1] = (val >> 48) & 0xFF;
	_buf[_pos + 2] = (val >> 40) & 0xFF;
	_buf[_pos + 3] = (val >> 32) & 0xFF;
	_buf[_pos + 4] = (val >> 24) & 0xFF;
	_buf[_pos + 5] = (val >> 16) & 0xFF;
	_buf[_pos + 6] = (val >>  8) & 0xFF;
	_buf[_pos + 7] = (val      ) & 0xFF;
	_pos += 8;

	return *this;
}

oarchive& oarchive::operator&(sint8 val)
{
	uint8 tmp;

	*this & tmp;

	if (tmp & (1 << 7))
		val = -(sint8(~tmp) + 1);
	else
		val = tmp;

	return *this;
}

oarchive& oarchive::operator&(sint16 val)
{
	uint16 tmp;

	*this & tmp;

	if (tmp & (1 << 15))
		val = -(sint16(~tmp) + 1);
	else
		val = tmp;

	return *this;
}

oarchive& oarchive::operator&(sint32 val)
{
	uint32 tmp;

	*this & tmp;

	if (tmp & (1 << 31))
		val = -(sint32(~tmp) + 1);
	else
		val = tmp;

	return *this;
}

oarchive& oarchive::operator&(sint64 val)
{
	uint64 tmp;

	*this & tmp;

	if (tmp & (1ll << 63))
		val = -(sint64(~tmp) + 1);
	else
		val = tmp;

	return *this;
}

oarchive& oarchive::operator&(octet_string& val)
{
	uint len = truncate_cast<uint>(val.length());
	uint pos = _pos;

	list_length(len);
	try {
		_buf.resize(_pos + len);

	} catch (...) {
		_pos = pos;
		throw;
	}
	std::copy(val.begin(), val.end(), _buf.begin() + _pos);
	_pos += len;

	return *this;
}

oarchive& oarchive::operator&(std::vector<uint8>& buf)
{
	uint len = truncate_cast<uint>(buf.size());
	uint pos = _pos;

	list_length(len);
	try {
		_buf.resize(_pos + len);

	} catch (...) {
		_pos = pos;
		throw;
	}
	std::copy(buf.begin(), buf.end(), _buf.begin() + _pos);
	_pos += len;

	return *this;
}

void oarchive::list_length(uint len)
{
	uint pos = _pos;

	if (len <= 128) {
		_buf.resize(pos + 1);
		_buf[pos++] = uint8(len);

	} else {
		uint r = (len - 128) % 255;
		uint n = (len - 128) / 255 + bool(r);

		_buf.resize(pos + n + 1);
		_buf[pos++] = 0x80 | uint8(n);

		while (--n)
			_buf[pos++] = 255;

		if (r)
			_buf[pos++] = r;
		else
			_buf[pos++] = 255;
	}
	_pos = pos;
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
