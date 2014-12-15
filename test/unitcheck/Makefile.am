
if HAVE_CHECKMK

bin_PROGRAMS=lctest lcutiltest

lctest_SOURCES=basic_complete.c
lctest_CPPFLAGS=-I../../libcl/include -Wall @CHECK_CFLAGS@ -I../../libclutil -g
lctest_LDADD =../../libcl/libcomplearn.la ../../libclutil/libclutil.la -lm @CHECK_LIBS@

lcutiltest_SOURCES=basic_clutil.c
lcutiltest_CPPFLAGS=-I../../libcl/include -Wall @CHECK_CFLAGS@ -I../../libclutil -g
lcutiltest_LDADD =../../libcl/libcomplearn.la ../../libclutil/libclutil.la -lm @CHECK_LIBS@

.ts.c:
	checkmk $< >$@

endif

EXTRA_DIST=basic_complete.ts \
  basic_clutil.ts
