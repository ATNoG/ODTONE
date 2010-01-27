
include $(top_srcdir)/common.mk

bin_PROGRAMS = units

units_SOURCES = units.cpp t1000.cpp t1001.cpp
units_LDADD = $(top_srcdir)/src/mih/libodtone_mih.a $(top_srcdir)/src/utils/libodtone_utils.a
units_LDFLAGS = @BOOST_SYSTEM_LIB@ @BOOST_PROGRAM_OPTIONS_LIB@
