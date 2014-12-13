if HAVE_LD_VERSION_SCRIPT
    VERSION_LDFLAGS = -Wl,--version-script=$(top_srcdir)/lib/complearn.map
else
    VERSION_LDFLAGS = -export-symbols $(top_srcdir)/lib/complearn.sym
endif

lib_LTLIBRARIES = libcomplearn.la
libcomplearn_la_SOURCES = compressor_base.c
libcomplearn_la_CPPFLAGS = -I$(top_srcdir)/include
libcomplearn_la_LDFLAGS = $(VERSION_LDFLAGS)
