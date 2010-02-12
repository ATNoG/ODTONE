#==============================================================================
# brief : odtone project configuration script
#=============================================================================

# prelude
AC_PREREQ(2.61)
AC_INIT([odtone], [0.1.1], [odtone@hng.av.it.pt])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

# check for programs
AC_PROG_CC
AC_PROG_CXX

# add directory with m4 macros
AC_CONFIG_MACRO_DIR([m4])


# check for libraries
AX_ODTONE_BASE

AX_BOOST_BASE([1.37])
AX_BOOST_THREAD
AX_BOOST_ASIO
AX_BOOST_SYSTEM
AX_BOOST_PROGRAM_OPTIONS

AX_LIB_SQLITE3([3.5.9])

# check for header files
# check for typedefs, structures, and compiler characteristics
# check for library functions

# config flags
AC_SUBST(CPPFLAGS)
AC_SUBST(LDFLAGS)

# config files
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile src/sap/Makefile src/mihf/Makefile src/mih/Makefile src/utils/Makefile src/link_sap/Makefile tests/mih/Makefile])
AC_PROG_RANLIB

# output files
AC_OUTPUT
