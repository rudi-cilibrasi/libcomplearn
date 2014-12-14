if HAVE_LD_VERSION_SCRIPT
    VERSION_LDFLAGS = -Wl,--version-script=$(top_srcdir)/lib/complearn.map
else
    VERSION_LDFLAGS = -export-symbols $(top_srcdir)/lib/complearn.sym
endif

lib_LTLIBRARIES = libcomplearn.la
libcomplearn_la_SOURCES = compressor_base.c cmod_zlib.c cmod_xz.c \
  libcl.c clpopen.c clpopen.h
libcomplearn_la_CPPFLAGS = -I$(top_srcdir)/include -Wall
libcomplearn_la_LDFLAGS = $(VERSION_LDFLAGS)
libcomplearn_la_LIBADD = -lz
include_HEADERS =   include/complearn.h

pubincludedir = $(includedir)/complearn
pubinclude_HEADERS =                                         \
                       include/complearn/cltop.h             \
                       include/complearn/compressor_base.h   \
                       include/complearn/libcl.h
