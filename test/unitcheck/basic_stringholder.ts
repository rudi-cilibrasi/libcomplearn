/* A complete test example */

#include <stdio.h>
#include <stringholder.h>

#test stringholder_test
	struct StringHolder sh;
  newStringHolder(&sh);
  ck_assert(0 == getStringHolderCount(&sh));
  freeStringHolder(&sh);
  newStringHolder(&sh);
  ck_assert(0 == getStringHolderCount(&sh));
  pushStringHolder(&sh, "cat");
  ck_assert(1 == getStringHolderCount(&sh));
  ck_assert(0 != getStringHolderData(&sh));
  ck_assert(0 == strcmp("cat", getStringHolderData(&sh)[0]));
  pushStringHolder(&sh, "dog");
  ck_assert(2 == getStringHolderCount(&sh));
  ck_assert(0 != getStringHolderData(&sh));
  ck_assert(0 == strcmp("dog", getStringHolderData(&sh)[1]));
  ck_assert(0 == strcmp("cat", getStringHolderData(&sh)[0]));
  freeStringHolder(&sh);
