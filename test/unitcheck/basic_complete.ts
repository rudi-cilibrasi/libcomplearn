/* A complete test example */

#include <stdio.h>
#include <complearn.h>

#test the_test
	int nc;
	const char msg[] = "\n\n    Hello, CompLearn!\n";
  clInit();

	nc = printf("%s", msg);
	ck_assert(nc == (sizeof(msg) - 1)); /* for terminating NUL. */
