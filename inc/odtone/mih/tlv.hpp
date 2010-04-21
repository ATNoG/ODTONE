//=============================================================================
// Brief   : MIH TLV Serialization DSL
// Authors : Bruno Santos <bsantos@av.it.pt>
// ----------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2009-2010 Universidade de Aveiro
// Copyrigth (C) 2009-2010 Instituto de Telecomunicações - Pólo de Aveiro
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//=============================================================================

#ifndef ODTONE_MIH_TLV__HPP_
#define ODTONE_MIH_TLV__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/base.hpp>
#include <odtone/exception.hpp>
#include <odtone/mih/archive.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/optional.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih {

///////////////////////////////////////////////////////////////////////////////
struct bad_tlv : virtual public exception {
	bad_tlv() : exception("odtone::mih::tlv_fwd::serialize(iarchive&): TLV missmatch")
	{ }
};

///////////////////////////////////////////////////////////////////////////////
template<class ValueT, ValueT Value>
struct base_tlv_ {
	template<class T>
	static bool serialize(iarchive& ar, T& val)
	{
		uint pos = ar.position();
		ValueT tp;

		ar & tp;
		if (tp != Value) {
			ar.rewind(pos);
			return false;
		}

		archive tmp;

		ar & tmp.buffer();
		tmp.input() & val;
		return true;
	}

	template<class T>
	static void serialize(oarchive& ar, T& val)
	{
		archive tmp;

		tmp.output() & val;
		ar & Value;
		ar & tmp.buffer();
	}
};

template<uint8 Value>
struct tlv_ : base_tlv_<uint8, Value> {
	typedef tlv_<Value> tlv_serializer;
};

template<uint32 Value>
struct tlv4_ : base_tlv_<uint32, Value> {
	typedef tlv4_<Value> tlv_serializer;
};

template<uint8 A, uint8 B, uint8 C>
struct oui_ {
	typedef oui_<A, B, C> tlv_serializer;

	template<class T>
	static bool serialize(iarchive& ar, T& val)
	{
		uint pos = ar.position();
		uint8 tp;

		ar & tp;
		if (tp != 100) {
			ar.rewind(pos);
			return false;
		}


		uint8 oui[3];

		ar & oui[0];
		ar & oui[1];
		ar & oui[2];

		if (oui[0] != A || oui[1] != B || oui[2] != C) {
			ar.rewind(pos);
			return false;
		}


		archive tmp;

		ar & tmp.buffer();
		tmp.input() & val;

		return true;
	}

	template<class T>
	static void serialize(oarchive& ar, T& val)
	{
		archive tmp;
		uint8 tp = 100;

		tmp.output() & A;
		tmp.output() & B;
		tmp.output() & C;
		tmp.output() & val;
		ar & tp;
		ar & tmp.buffer();
	}
};

///////////////////////////////////////////////////////////////////////////////
template<class T, class TLV>
class tlv_type_ {
	typedef typename TLV::tlv_serializer impl;

public:
	typedef tlv_type_<T, TLV> tlv_type;

public:
	tlv_type_(T& val)
		: _val(val)
	{ }

	void serialize(iarchive& ar) const
	{
		bool res = impl::serialize(ar, _val);
		if (!res)
			boost::throw_exception(bad_tlv());
	}

	void serialize(oarchive& ar) const
	{
		impl::serialize(ar, _val);
	}

private:
	mutable T& _val;
};

template<class T, class TLV>
class tlv_type_<boost::optional<T>, TLV> {
	typedef typename TLV::tlv_serializer impl;

public:
	typedef tlv_type_<boost::optional<T>, TLV> tlv_type;

public:
	tlv_type_(boost::optional<T>& val)
		: _val(val)
	{ }

	void serialize(iarchive& ar) const
	{
		//if (ar.position() >= ar.length())
		//	return;

		T tmp;

		bool res = impl::serialize(ar, tmp);
		if (!res)
			boost::throw_exception(bad_tlv());
		else
			_val = tmp;
	}

	void serialize(oarchive& ar) const
	{
		if (_val)
			impl::serialize(ar, _val.get());
	}

private:
	mutable boost::optional<T>& _val;
};

///////////////////////////////////////////////////////////////////////////////
template<class T, class TLV>
class tlv_cast_ {
	typedef typename tlv_type_<T, TLV>::tlv_type                  tlv_type;
	typedef typename tlv_type_<boost::optional<T>, TLV>::tlv_type tlv_optional_type;

public:
	tlv_type operator()(const T& val) const
	{
		return tlv_type(const_cast<T&>(val));
	}

	tlv_optional_type operator()(const boost::optional<T>& val) const
	{
		return tlv_optional_type(const_cast<boost::optional<T>&>(val));
	}
};

///////////////////////////////////////////////////////////////////////////////
template<class T, class ValueT>
struct tlv_fwd;

template<class T, uint8 Value>
struct tlv_fwd<T, tlv_<Value> > : boost::noncopyable {
	typedef uint8 tlv_type;
	static const tlv_type value = Value;


	explicit tlv_fwd(const T& val)
		: _val(const_cast<T*>(&val)), _is_optional(false)
	{ }

	explicit tlv_fwd(const boost::optional<T>& val)
		: _optval(const_cast<boost::optional<T>*>(&val)), _is_optional(true)
	{ }

	void serialize(iarchive& ar) const
	{
		uint pos = ar.position();
		uint8 tp;

		ar & tp;
		if (tp == value) {
			archive tmp;

			ar & tmp.buffer();

			if (_is_optional) {
				*_optval = T();
				tmp.input() & (*_optval).get();

			} else {
				tmp.input() & *_val;
			}

		} else {
			if (_is_optional)
				ar.rewind(pos);
			else
				boost::throw_exception(bad_tlv());
		}
	}

	void serialize(oarchive& ar) const
	{
		if (!_is_optional || *_optval) {
			archive tmp;

			tmp.output() & (_is_optional ? (*_optval).get() : *_val);
			ar & value;
			ar & tmp.buffer();
		}
	}

protected:
	union {
		mutable T*                  _val;
		mutable boost::optional<T>* _optval;
	};
	bool _is_optional;
};

template<class T, uint8 A, uint8 B, uint8 C>
struct tlv_fwd<T, oui_<A, B, C> > : boost::noncopyable {
	typedef uint8 tlv_type;
	static const tlv_type value = 100;


	explicit tlv_fwd(const T& val)
		: _val(const_cast<T*>(&val)), _is_optional(false)
	{ }

	explicit tlv_fwd(const boost::optional<T>& val)
		: _optval(const_cast<boost::optional<T>*>(&val)), _is_optional(true)
	{ }

	void serialize(iarchive& ar) const
	{
		uint pos = ar.position();
		uint8 tp;

		ar & tp;
		if (tp == value) {
			uint8 oui[3];

			ar & oui[0];
			ar & oui[1];
			ar & oui[2];

			if (oui[0] == A && oui[1] == B && oui[2] == C) {
				archive tmp;

				ar & tmp.buffer();

				*_optval = T();
				tmp.input() & (*_optval).get();

			} else {
				ar.rewind(pos);
			}

		} else {
			if (_is_optional)
				ar.rewind(pos);
			else
				boost::throw_exception(bad_tlv());
		}
	}

	void serialize(oarchive& ar) const
	{
		if (!_is_optional || *_optval) {
			archive tmp;

			tmp.output() & A;
			tmp.output() & B;
			tmp.output() & C;
			tmp.output() & (_is_optional ? (*_optval).get() : *_val);
			ar & value;
			ar & tmp.buffer();
		}
	}

protected:
	union {
		mutable T*                  _val;
		mutable boost::optional<T>* _optval;
	};
	bool _is_optional;
};

template<class T>
class is_tlv_fwd {
	typedef char true_t;
	class false_t { char dummy[2]; };

	template<class U> static true_t  test(typename U::tlv_type* = 0);
	template<class U> static false_t test(...);

public:
	static const bool value = sizeof(test<T>(0)) == sizeof(true_t);
};

template<class T, uint32 Value>
struct tlv_fwd<T, tlv4_<Value> > : boost::noncopyable {
	typedef uint32 tlv_type;
	static const tlv_type value = Value;


	explicit tlv_fwd(const T& val)
		: _val(const_cast<T*>(&val)), _is_optional(false)
	{ }

	explicit tlv_fwd(const boost::optional<T>& val)
		: _optval(const_cast<boost::optional<T>*>(&val)), _is_optional(true)
	{ }

	void serialize(iarchive& ar) const
	{
		uint pos = ar.position();
		uint32 tp;

		ar & tp;
		if (tp == value) {
			archive tmp;

			ar & tmp.buffer();

			if (_is_optional) {
				*_optval = T();
				tmp.input() & (*_optval).get();

			} else {
				tmp.input() & *_val;
			}

		} else {
			if (_is_optional)
				ar.rewind(pos);
			else
				boost::throw_exception(bad_tlv());
		}
	}

	void serialize(oarchive& ar) const
	{
		if (!_is_optional || *_optval) {
			archive tmp;

			tmp.output() & (_is_optional ? (*_optval).get() : *_val);
			ar & value;
			ar & tmp.buffer();
		}
	}

protected:
	union {
		mutable T*                  _val;
		mutable boost::optional<T>* _optval;
	};
	bool _is_optional;
};

///////////////////////////////////////////////////////////////////////////////
class otlv {
public:
	otlv(archive& ar) : _ar(ar.output()) {}
	otlv(oarchive& ar) : _ar(ar) {}

#ifdef ODTONE_DOXYGEN_INVOKED
	template<class T, uint8 Value>
	otlv& operator&(const tlv_fwd<T, tlv_<Value> >& val);

	template<class T, uint8 A, uint8 B, uint8 C>
	otlv& operator&(const tlv_fwd<T, oui_<A, B, C> >& val);


	template<class T, uint32 Value>
	otlv& operator&(const tlv_fwd<T, tlv4_<Value> >& val);

#else
	template<class T>
	typename boost::enable_if<is_tlv_fwd<T>, otlv&>::type operator&(const T& val)
	{
		val.serialize(_ar);

		return *this;
	}
#endif

private:
	oarchive& _ar;
};

///////////////////////////////////////////////////////////////////////////////
class itlv {
public:
	itlv(archive& ar) : _ar(ar.input()) {}
	itlv(iarchive& ar) : _ar(ar) {}

#ifdef ODTONE_DOXYGEN_INVOKED
	template<class T, uint8 Value>
	itlv& operator&(const tlv_fwd<T, tlv_<Value> >& val);

	template<class T, uint8 A, uint8 B, uint8 C>
	itlv& operator&(const tlv_fwd<T, oui_<A, B, C> >& val);

	template<class T, uint32 Value>
	itlv& operator&(const tlv_fwd<T, tlv4_<Value> >& val);

#else
	template<class T>
	typename boost::enable_if<is_tlv_fwd<T>, itlv&>::type operator&(const T& val)
	{
		val.serialize(_ar);

		return *this;
	}
#endif

private:
	iarchive& _ar;
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_TLV__HPP_ */
