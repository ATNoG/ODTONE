
include $(top_srcdir)/common.mk

## Add the headers we want to supply in the odtone package
EXTRA_DIST = \
	link_sap.hpp \
	link_sap.conf \
	interface/ethernet.hpp \
	interface/if_802_11.hpp \
	interface/interface.hpp \
	linux/netlink.hpp \
	linux/rtnetlink.hpp \
	base.hpp

##
## Where to install link_sap config file
##
link_sapdir=$(sysconfdir)/odtone
link_sap_DATA = link_sap.conf

bin_PROGRAMS = link_sap

link_sap_SOURCES =				\
	link_sap.cpp				\
	linux/main.cpp				\
	linux/netlink.cpp			\
	linux/rtnetlink.cpp			\
	interface/interface.cpp		\
	interface/ethernet.cpp		\
	interface/if_802_11.cpp

link_sap_CPPFLAGS = @LINK_SAP_CONFIG@
link_sap_LDADD   = ../odtone/mih/libodtone_mih.a ../odtone/sap/libodtone_sap.a ../odtone/libodtone_base.a
link_sap_LDFLAGS = @BOOST_THREAD_LIB@ @BOOST_SYSTEM_LIB@ @BOOST_PROGRAM_OPTIONS_LIB@

