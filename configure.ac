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
                 libclutil/Makefile
                 tools/Makefile
                 test/Makefile
                 test/unitcheck/Makefile
                ])
AC_CHECK_HEADER([zlib.h], [ flag_header_zlib_found=1 ])
AC_CHECK_HEADER([getopt.h], [ flag_header_getopt_found=1 ])
AC_CHECK_LIB([z], [deflate], [ flag_library_zlib_found=1 ])

if test "x$flag_header_getopt_found" = "x" ; then
  AC_ERROR([Must have getopt.h header])
fi

if test "x$flag_header_zlib_found" = "x" ; then
  AC_ERROR([Must have zlib.h header])
fi

if test "x$flag_library_zlib_found" = "x" ; then
  AC_ERROR([Must have zlib library])
fi

AC_PATH_PROG([HAVE_CHECKMK_PATH], [checkmk], [notfound])
AC_PATH_PROG([HAVE_XZ_PATH], [xz], [notfound])

if test "x$HAVE_XZ_PATH" = "xnotfound" ; then
  AC_ERROR([Must have xz-utils package installed. Please install xz.])
fi

AM_CONDITIONAL([HAVE_CHECKMK], [ test ! "x$HAVE_CHECKMK_PATH" = "xnotfound" ])

if test "x$HAVE_CHECKMK_PATH" = "xnotfound" ; then
  AC_WARN([checkmk not found please install "check" package for unit tests])
else
  CHECK_CFLAGS=$(pkg-config check --cflags)
  CHECK_LIBS=$(pkg-config check --libs)
fi

COMPLEARN1_LIBS="-lz"

AC_SUBST([COMPLEARN1_LIBS])
AC_SUBST([CHECK_CFLAGS])
AC_SUBST([CHECK_LIBS])

AC_OUTPUT
