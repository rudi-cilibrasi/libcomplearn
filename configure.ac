AC_PREREQ([2.69])
AC_INIT([libcomplearn], [0.7.1], [rudi@morefuntechnologies.com])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_LIBOBJ_DIR([portable])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE()
LT_INIT()
LT_PREREQ([2.2])
AC_PROG_CC()
AC_CONFIG_SRCDIR([tools/ncd.c])
AC_CONFIG_HEADERS([config.h])
AC_PROG_CC
RRA_LD_VERSION_SCRIPT
AC_CONFIG_FILES([Makefile
                 libcl/Makefile
                 tools/Makefile
                ])
AC_CHECK_HEADER([zlib.h], [ flag_header_zlib_found=1 ])
if test "x$flag_header_zlib_found" = "x" ; then
	echo "Must have zlib.h header"
fi
AC_OUTPUT
