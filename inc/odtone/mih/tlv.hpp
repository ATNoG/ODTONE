//=============================================================================
// Brief   : Archive for MIH TLV Serialization
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

template<uint8 Value>
struct tlv_ {
};

template<uint8 A, uint8 B, uint8 C>
struct oui_ {
};

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

		///////////////////////////////////////////////////////////

		template<uint32 Value>
		struct ie_tlv_ {
		};

		template<uint32 A, uint8 B, uint8 C>
		struct ie_oui_ {
		};

		template<class T, class ValueT>
		struct ie_tlv_fwd;

		template<class T, uint32 Value>
		struct ie_tlv_fwd<T, ie_tlv_<Value> > : boost::noncopyable {
			typedef uint32 ie_tlv_type;
			static const ie_tlv_type value = Value;


			explicit ie_tlv_fwd(const T& val)
				: _val(const_cast<T*>(&val)), _is_optional(false)
			{ }

			explicit ie_tlv_fwd(const boost::optional<T>& val)
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

		template<class T, uint32 A, uint8 B, uint8 C>
		struct ie_tlv_fwd<T, ie_oui_<A, B, C> > : boost::noncopyable {
			typedef uint32 ie_tlv_type;
			static const ie_tlv_type value = 100;


			explicit ie_tlv_fwd(const T& val)
				: _val(const_cast<T*>(&val)), _is_optional(false)
			{ }

			explicit ie_tlv_fwd(const boost::optional<T>& val)
				: _optval(const_cast<boost::optional<T>*>(&val)), _is_optional(true)
			{ }

			void serialize(iarchive& ar) const
			{
				uint pos = ar.position();
				uint32 tp;

				ar & tp;
				if (tp == value) {
					uint32 ie_oui1;
					uint8 ie_oui[2];

					ar & ie_oui1;
					ar & ie_oui[0];
					ar & ie_oui[1];


					if (ie_oui1 == A && ie_oui[0] == B && ie_oui[1] == C) {
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
		class is_ie_tlv_fwd {
			typedef char true_t;
			class false_t { char dummy[2]; };

			template<class U> static true_t  test(typename U::ie_tlv_type* = 0);
			template<class U> static false_t test(...);

		public:
			static const bool value = sizeof(test<T>(0)) == sizeof(true_t);
		};

		///////////////////////////////////////////////////////////

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
	otlv& operator&(const ie_tlv_fwd<T, tlv_<Value> >& val);

	template<class T, uint32 A, uint8 B, uint8 C>
	otlv& operator&(const ie_tlv_fwd<T, oui_<A, B, C> >& val);

#else
	template<class T>
	typename boost::enable_if<is_ie_tlv_fwd<T>, otlv&>::type operator&(const T& val)
	{
		val.serialize(_ar);

		return *this;
	}

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
	itlv& operator&(const ie_tlv_fwd<T, tlv_<Value> >& val);

	template<class T, uint32 A, uint8 B, uint8 C>
	itlv& operator&(const ie_tlv_fwd<T, oui_<A, B, C> >& val);

#else
	template<class T>
	typename boost::enable_if<is_ie_tlv_fwd<T>, itlv&>::type operator&(const T& val)
	{
		val.serialize(_ar);

		return *this;
	}

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
