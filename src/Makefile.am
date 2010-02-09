
include $(top_srcdir)/common.mk

##
## Where to install odtone config file
##
odtonedir=$(sysconfdir)/odtone
odtone_DATA = odtone.conf

EXTRA_DIST = \
	odtone.conf \
	mih_usr.conf

bin_PROGRAMS = odtone client mih_usr dummyserver

odtone_SOURCES = main.cpp


odtone_CPPFLAGS = @ODTONE_CONFIG@
odtone_LDADD = mihf/libodtone_mihf.a mih/libodtone_mih.a utils/libodtone_utils.a
odtone_LDFLAGS = @BOOST_THREAD_LIB@ @BOOST_SYSTEM_LIB@ @BOOST_PROGRAM_OPTIONS_LIB@ @SQLITE3_LDFLAGS@

client_SOURCES = client.cpp
client_LDADD = mih/libodtone_mih.a utils/libodtone_utils.a
client_LDFLAGS = @BOOST_THREAD_LIB@ @BOOST_SYSTEM_LIB@ @BOOST_PROGRAM_OPTIONS_LIB@

dummyserver_SOURCES = dummyserver.cpp
dummyserver_LDADD = mihf/libodtone_mihf.a mih/libodtone_mih.a utils/libodtone_utils.a
dummyserver_LDFLAGS = @BOOST_THREAD_LIB@ @BOOST_SYSTEM_LIB@ @BOOST_PROGRAM_OPTIONS_LIB@


##
## Where to install mih_usr config file
##
mih_usrdir=$(sysconfdir)/odtone
mih_usr_DATA = mih_usr.conf

mih_usr_SOURCES = mih_usr.cpp
mih_usr_CPPFLAGS = @MIH_USR_CONFIG@
mih_usr_LDADD   = mih/libodtone_mih.a sap/libodtone_sap.a utils/libodtone_utils.a
mih_usr_LDFLAGS = @BOOST_THREAD_LIB@ @BOOST_SYSTEM_LIB@ @BOOST_PROGRAM_OPTIONS_LIB@
