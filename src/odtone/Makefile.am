include $(top_srcdir)/common.mk

lib_LIBRARIES = libodtone_base.a

libodtone_base_a_SOURCES = debug.cpp debug_linux.cpp strutil.cpp logger.cpp

bin_PROGRAMS = odtone
odtone_SOURCES = main.cpp
odtone_LDADD   = mihf/libodtone_mihf.a mih/libodtone_mih.a libodtone_base.a 
odtone_LDFLAGS = @BOOST_THREAD_LIB@ @BOOST_SYSTEM_LIB@ @BOOST_PROGRAM_OPTIONS_LIB@
