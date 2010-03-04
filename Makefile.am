SUBDIRS = . src/mih src/sap src/mihf src/utils src/link_sap src tests/mih
ACLOCAL_AMFLAGS = -I m4

## Add other files when building the package
EXTRA_DIST = \
	inc \
	build \
	3rdparty \
	LICENSE \
	autogen.sh

#
#   hideous hack
#
#   When a user unpacks the tarball the ODTONE_CONFIG macro points to
#   the src/odtone.conf configuration file. When the user does a make
#   install the macro is recalculated to the final destination.
#
#   What this code does is substitute the macro definition in the
#   Makefiles and then does a recompilation of the projects and then
#   proceeds to install it.
#
install-exec-local:
	rm -f src/odtone-main.o src/odtone
	rm -f src/mih_usr-mih_usr.o src/mih_usr
	rm -f src/link_sap/link_sap-main.o src/link_sap/link_sap
	mv src/Makefile src/Makefile.tmp ;
	sed -e 's#^odtone_CPPFLAGS.*#odtone_CPPFLAGS = -DODTONE_CONFIG=\\"$(sysconfdir)/odtone/odtone.conf\\"#g' \
	    -e 's#^mih_usr_CPPFLAGS.*#mih_usr_CPPFLAGS = -DMIH_USR_CONFIG=\\"$(sysconfdir)/odtone/mih_usr.conf\\"#g' \
	    src/Makefile.tmp > src/Makefile ;
	mv src/link_sap/Makefile src/link_sap/Makefile.tmp ;
	sed -e 's#^link_sap_CPPFLAGS.*#link_sap_CPPFLAGS = -DLINK_SAP_CONFIG=\\"$(sysconfdir)/odtone/link_sap.conf\\"#g'  \
	    src/link_sap/Makefile.tmp > src/link_sap/Makefile ;
	make ;
	mv src/Makefile.tmp src/Makefile ;
	mv src/link_sap/Makefile.tmp src/link_sap/Makefile ;

