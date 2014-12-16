ACLOCAL_AMFLAGS = -I m4
SUBDIRS = libcl libclutil tools test

EXTRA_DIST = lib/complearn.map lib/complearn.sym lib/clutil.map lib/clutil.sym \
             lib/libcomplearn.pc.in
dist_man_MANS = man/ncd.1

pkgconfigdir = $(libdir)/pkgconfig
nodist_pkgconfig_DATA = lib/libcomplearn.pc

lib/libcomplearn.pc: $(srcdir)/lib/libcomplearn.pc.in
	sed -e 's![@]prefix[@]!$(prefix)!g' \
			-e 's![@]exec_prefix[@]!$(exec_prefix)!g' \
			-e 's![@]includedir[@]!$(includedir)!g' \
			-e 's![@]libdir[@]!$(libdir)!g' \
			-e 's![@]PACKAGE_VERSION[@]!$(PACKAGE_VERSION)!g' \
			-e 's![@]COMPLEARN1_LDFLAGS[@]!$(COMPLEARN1_LDFLAGS)!g' \
			-e 's![@]COMPLEARN1_LIBS[@]!$(COMPLEARN1_LIBS)!g' \
			$(srcdir)/lib/libcomplearn.pc.in > $@
