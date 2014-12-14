
if HAVE_CHECKMK

bin_PROGRAMS=lctest
lctest_SOURCES=basic_complete.c
lctest_CPPFLAGS=-I../../libcl/include -Wall @CHECK_CFLAGS@
lctest_LDADD =../../libcl/libcomplearn.la -lm @CHECK_LIBS@

.ts.c:
	checkmk $< >$@

endif

EXTRA_DIST=basic_complete.ts
