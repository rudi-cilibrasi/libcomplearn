/* A complete test example */

#include <stdio.h>

#test the_test
	int nc;
	const char msg[] = "\n\n    Hello, world!\n";

	nc = printf("%s", msg);
	ck_assert(nc == (sizeof(msg) - 1)); /* for terminating NUL. */
