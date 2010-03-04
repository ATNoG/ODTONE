//=============================================================================
// Brief   : Archive details
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

#ifndef ODTONE_MIH_DETAIL_ARCHIVE__HPP_
#define ODTONE_MIH_DETAIL_ARCHIVE__HPP_

///////////////////////////////////////////////////////////////////////////////
#include <odtone/cast.hpp>
#include <boost/array.hpp>
#include <boost/variant/variant.hpp>
#include <boost/variant/get.hpp>
#include <vector>
#include <list>

///////////////////////////////////////////////////////////////////////////////
namespace odtone { namespace mih { namespace detail {

///////////////////////////////////////////////////////////////////////////////
template<class T>
struct serialize {
	template<class ArchiveT>
	void operator()(ArchiveT& ar, T& val) const
	{
		val.serialize(ar);
	}
};

template<class T>
struct serialize<std::vector<T> > {
	void operator()(iarchive& ar, std::vector<T>& val) const
	{
		uint pos = ar.position();
		uint len = ar.list_length();

		val.resize(len);
		try {
			typename std::vector<T>::iterator it = val.begin();

			while (len--) {
				ar & *it;
				++it;
			}

		} catch (...) {
			val.clear();
			ar.rewind(pos);
			throw;
		}
	}

	void operator()(oarchive& ar, std::vector<T>& val) const
	{
		typename std::vector<T>::iterator it = val.begin();
		uint len = truncate_cast<uint>(val.size());
		uint pos = ar.position();

		ar.list_length(len);
		try {
			while (len--) {
				ar & *it;
				++it;
			}

		} catch (...) {
			ar.rewind(pos);
			throw;
		}
	}
};

template<class T>
struct serialize<std::list<T> > {
	void operator()(iarchive& ar, std::list<T>& val) const
	{
		uint pos = ar.position();
		uint len = ar.list_length();

		val.resize(len);
		try {
			typename std::list<T>::iterator it = val.begin();

			while (len--) {
				ar & *it;
				++it;
			}

		} catch (...) {
			val.clear();
			ar.rewind(pos);
			throw;
		}
	}

	void operator()(oarchive& ar, std::list<T>& val) const
	{
		typename std::list<T>::iterator it = val.begin();
		uint len = truncate_cast<uint>(val.size());
		uint pos = ar.position();

		ar.list_length(len);
		try {
			while (len--) {
				ar & *it;
				++it;
			}

		} catch (...) {
			ar.rewind(pos);
			throw;
		}
	}
};

template<class T1>
struct serialize<boost::variant<T1> > {
	void operator()(iarchive& ar, boost::variant<T1>& val) const
	{
		octet selector;

		ar & selector;
		switch (selector) {
		case 0:
			val = T1();
			ar & boost::get<T1>(val);
			break;

	//	default:
	//		ODTONE_NEVER_HERE;
		}
	}

	void operator()(oarchive& ar, boost::variant<T1>& val) const
	{
		octet selector = val.which();

		ar & selector;
		switch (selector) {
		case 0:
			ar & boost::get<T1>(val);
			break;

	//	default:
	//		ODTONE_NEVER_HERE;
		}
	}
};

template<class T1, class T2>
struct serialize<boost::variant<T1, T2> > {
	void operator()(iarchive& ar, boost::variant<T1, T2>& val) const
	{
		octet selector;

		ar & selector;
		switch (selector) {
		case 0:
			val = T1();
			ar & boost::get<T1>(val);
			break;

		case 1:
			val = T2();
			ar & boost::get<T2>(val);
			break;

	//	default:
	//		ODTONE_NEVER_HERE;
		}
	}

	void operator()(oarchive& ar, boost::variant<T1, T2>& val) const
	{
		octet selector = val.which();

		ar & selector;
		switch (selector) {
		case 0:
			ar & boost::get<T1>(val);
			break;

		case 1:
			ar & boost::get<T2>(val);
			break;

	//	default:
	//		ODTONE_NEVER_HERE;
		}
	}
};

template<class T1, class T2, class T3>
struct serialize<boost::variant<T1, T2, T3> > {
	void operator()(iarchive& ar, boost::variant<T1, T2, T3>& val) const
	{
		octet selector;

		ar & selector;
		switch (selector) {
		case 0:
			val = T1();
			ar & boost::get<T1>(val);
			break;

		case 1:
			val = T2();
			ar & boost::get<T2>(val);
			break;

		case 2:
			val = T3();
			ar & boost::get<T3>(val);
			break;

	//	default:
	//		ODTONE_NEVER_HERE;
		}
	}

	void operator()(oarchive& ar, boost::variant<T1, T2, T3>& val) const
	{
		octet selector = val.which();

		ar & selector;
		switch (selector) {
		case 0:
			ar & boost::get<T1>(val);
			break;

		case 1:
			ar & boost::get<T2>(val);
			break;

		case 2:
			ar & boost::get<T3>(val);
			break;

	//	default:
	//		ODTONE_NEVER_HERE;
		}
	}
};

template<class T1, class T2, class T3, class T4>
struct serialize<boost::variant<T1, T2, T3, T4> > {
	void operator()(iarchive& ar, boost::variant<T1, T2, T3, T4>& val) const
	{
		octet selector;

		ar & selector;
		switch (selector) {
		case 0:
			val = T1();
			ar & boost::get<T1>(val);
			break;

		case 1:
			val = T2();
			ar & boost::get<T2>(val);
			break;

		case 2:
			val = T3();
			ar & boost::get<T3>(val);
			break;

		case 3:
			val = T4();
			ar & boost::get<T4>(val);
			break;

	//	default:
	//		ODTONE_NEVER_HERE;
		}
	}

	void operator()(oarchive& ar, boost::variant<T1, T2, T3, T4>& val) const
	{
		octet selector = val.which();

		ar & selector;
		switch (selector) {
		case 0:
			ar & boost::get<T1>(val);
			break;

		case 1:
			ar & boost::get<T2>(val);
			break;

		case 2:
			ar & boost::get<T3>(val);
			break;

		case 3:
			ar & boost::get<T4>(val);
			break;

	//	default:
	//		ODTONE_NEVER_HERE;
		}
	}
};

template<class T1, class T2, class T3, class T4, class T5>
struct serialize<boost::variant<T1, T2, T3, T4, T5> > {
	void operator()(iarchive& ar, boost::variant<T1, T2, T3, T4, T5>& val) const
	{
		octet selector;

		ar & selector;
		switch (selector) {
		case 0:
			val = T1();
			ar & boost::get<T1>(val);
			break;

		case 1:
			val = T2();
			ar & boost::get<T2>(val);
			break;

		case 2:
			val = T3();
			ar & boost::get<T3>(val);
			break;

		case 3:
			val = T4();
			ar & boost::get<T4>(val);
			break;

		case 4:
			val = T5();
			ar & boost::get<T5>(val);
			break;

	//	default:
	//		ODTONE_NEVER_HERE;
		}
	}

	void operator()(oarchive& ar, boost::variant<T1, T2, T3, T4, T5>& val) const
	{
		octet selector = val.which();

		ar & selector;
		switch (selector) {
		case 0:
			ar & boost::get<T1>(val);
			break;

		case 1:
			ar & boost::get<T2>(val);
			break;

		case 2:
			ar & boost::get<T3>(val);
			break;

		case 3:
			ar & boost::get<T4>(val);
			break;

		case 4:
			ar & boost::get<T5>(val);
			break;

	//	default:
	//		ODTONE_NEVER_HERE;
		}
	}
};

template<class T1, class T2, class T3, class T4, class T5, class T6>
struct serialize<boost::variant<T1, T2, T3, T4, T5, T6> > {
	void operator()(iarchive& ar, boost::variant<T1, T2, T3, T4, T5, T6>& val) const
	{
		octet selector;

		ar & selector;
		switch (selector) {
		case 0:
			val = T1();
			ar & boost::get<T1>(val);
			break;

		case 1:
			val = T2();
			ar & boost::get<T2>(val);
			break;

		case 2:
			val = T3();
			ar & boost::get<T3>(val);
			break;

		case 3:
			val = T4();
			ar & boost::get<T4>(val);
			break;

		case 4:
			val = T5();
			ar & boost::get<T5>(val);
			break;

		case 5:
			val = T6();
			ar & boost::get<T6>(val);
			break;

	//	default:
	//		ODTONE_NEVER_HERE;
		}
	}

	void operator()(oarchive& ar, boost::variant<T1, T2, T3, T4, T5, T6>& val) const
	{
		octet selector = val.which();

		ar & selector;
		switch (selector) {
		case 0:
			ar & boost::get<T1>(val);
			break;

		case 1:
			ar & boost::get<T2>(val);
			break;

		case 2:
			ar & boost::get<T3>(val);
			break;

		case 3:
			ar & boost::get<T4>(val);
			break;

		case 4:
			ar & boost::get<T5>(val);
			break;

		case 5:
			ar & boost::get<T6>(val);
			break;

	//	default:
	//		ODTONE_NEVER_HERE;
		}
	}
};

///////////////////////////////////////////////////////////////////////////////
} /* namspace detail */

///////////////////////////////////////////////////////////////////////////////
template<class T>
inline iarchive& operator&(iarchive& ar, T& val)
{
	detail::serialize<T>()(ar, val);
	return ar;
}

template<class T>
inline oarchive& operator&(oarchive& ar, T& val)
{
	detail::serialize<T>()(ar, val);
	return ar;
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace mih */ } /*namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
#endif /* ODTONE_MIH_DETAIL_ARCHIVE__HPP_ */
