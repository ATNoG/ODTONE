
include $(top_srcdir)/common.mk

bin_PROGRAMS = mih_usr
mih_usr_SOURCES = mih_usr.cpp
mih_usr_LDADD   = ../odtone/mih/libodtone_mih.a ../odtone/libodtone_base.a  ../odtone/sap/libodtone_sap.a
mih_usr_LDFLAGS = @BOOST_THREAD_LIB@ @BOOST_SYSTEM_LIB@ @BOOST_PROGRAM_OPTIONS_LIB@
