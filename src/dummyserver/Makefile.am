
include $(top_srcdir)/common.mk
bin_PROGRAMS = dummyserver
dummyserver_SOURCES = dummyserver.cpp
dummyserver_LDADD = ../odtone/mihf/libodtone_mihf.a ../odtone/mih/libodtone_mih.a ../odtone/libodtone_base.a 
dummyserver_LDFLAGS = @BOOST_THREAD_LIB@ @BOOST_SYSTEM_LIB@ @BOOST_PROGRAM_OPTIONS_LIB@

