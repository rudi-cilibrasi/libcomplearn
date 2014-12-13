dnl Check whether the linker supports --version-script.
dnl
dnl Probes whether the linker supports --version-script with a simple version
dnl script that only defines a single version.  Sets the Automake conditional
dnl HAVE_LD_VERSION_SCRIPT based on whether it is supported.
dnl
dnl Written by Russ Allbery <rra@stanford.edu>
dnl Based on the gnulib ld-version-script macro from Simon Josefsson
dnl Copyright 2010 Board of Trustees, Leland Stanford Jr. University
dnl Copyright (C) 2008, 2009, 2010 Free Software Foundation, Inc.
dnl
dnl This file is free software; the Free Software Foundation gives unlimited
dnl permission to copy and/or distribute it, with or without modifications, as
dnl long as this notice is preserved.

AC_DEFUN([RRA_LD_VERSION_SCRIPT],
[AC_CACHE_CHECK([if -Wl,--version-script works], [rra_cv_ld_version_script],
    [save_LDFLAGS="$LDFLAGS"
     LDFLAGS="$LDFLAGS -Wl,--version-script=conftest.map"
     cat > conftest.map <<EOF
VERSION_1 {
    global:
        sym;

    local:
        *;
};
EOF
     AC_LINK_IFELSE([AC_LANG_PROGRAM([], [])],
        [rra_cv_ld_version_script=yes], [rra_cv_ld_version_script=no])
     rm -f conftest.map
     LDFLAGS="$save_LDFLAGS"])
 AM_CONDITIONAL([HAVE_LD_VERSION_SCRIPT],
    [test x"$rra_cv_ld_version_script" = xyes])])
