
include $(top_srcdir)/common.mk
bin_PROGRAMS = client
client_SOURCES = client.cpp
client_LDADD = ../odtone/mih/libodtone_mih.a ../odtone/libodtone_base.a
client_LDFLAGS = @BOOST_THREAD_LIB@ @BOOST_SYSTEM_LIB@ @BOOST_PROGRAM_OPTIONS_LIB@

