/* A complete test example */

#include <stdio.h>
#include <clutil.h>

#test doubleholder_test
	struct DoubleHolder dh;
  newDoubleHolder(&dh);
  ck_assert(0 == getDoubleHolderCount(&dh));
  freeDoubleHolder(&dh);
  newDoubleHolder(&dh);
  ck_assert(0 == getDoubleHolderCount(&dh));
  pushDoubleHolder(&dh, 17);
  ck_assert(1 == getDoubleHolderCount(&dh));
  ck_assert(17 == getDoubleHolderData(&dh)[0]);
  pushDoubleHolder(&dh, 11);
  ck_assert(17 == getDoubleHolderData(&dh)[0]);
  ck_assert(2 == getDoubleHolderCount(&dh));
  ck_assert(11 == getDoubleHolderData(&dh)[1]);

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
