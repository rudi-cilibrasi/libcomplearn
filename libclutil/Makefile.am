if HAVE_LD_VERSION_SCRIPT
    VERSION_LDFLAGS = -Wl,--version-script=$(top_srcdir)/lib/clutil.map
else
    VERSION_LDFLAGS = -export-symbols $(top_srcdir)/lib/clutil.sym
endif

lib_LTLIBRARIES = libclutil.la
libclutil_la_SOURCES = stringholder.c stringholder.h clutil.h \
                       doubleholder.c doubleholder.h          \
                         charholder.c   charholder.h          \
                        ncditerator.c  ncditerator.h          \
                        ncditeratortype.h                     \
                   directoryiterator.c directoryiterator.h    \
                   singlefileiterator.c singlefileiterator.h  \
                   filenamelistiterator.c filenamelistiterator.h  \
                      filehelper.c     filehelper.h

libclutil_la_CPPFLAGS = -I$(top_srcdir)/libcl/include -Wall
libclutil_la_LDFLAGS = $(VERSION_LDFLAGS)
