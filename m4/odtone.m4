# LICENSE
#
#   Copyright (c) 2008 Simao Reis <sreis@av.it.pt>
#
#   Copying and distribution of this file, with or without modification, are
#   permitted in any medium without royalty provided the copyright notice
#   and this notice are preserved.

AC_DEFUN([AX_ODTONE_BASE],
[
        ODTONE_CONFIG='-DODTONE_CONFIG=\"`pwd`/odtone.conf\"'
        MIH_USR_CONFIG='-DMIH_USR_CONFIG=\"`pwd`/mih_usr.conf\"'
        LINK_SAP_CONFIG='-DLINK_SAP_CONFIG=\"`pwd`/link_sap.conf\"'
        AC_SUBST(ODTONE_CONFIG)
        AC_SUBST(MIH_USR_CONFIG)
        AC_SUBST(LINK_SAP_CONFIG)
])
