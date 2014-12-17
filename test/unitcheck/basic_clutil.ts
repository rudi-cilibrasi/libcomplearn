/* A complete test example */

#include <stdio.h>
#include <clutil.h>

#test charholder_test
	struct CharHolder ch;
  newCharHolder(&ch);
  ck_assert(0 == getCharHolderCount(&ch));
  freeCharHolder(&ch);
  newCharHolder(&ch);
  ck_assert(0 == getCharHolderCount(&ch));
  pushCharHolder(&ch, 15);
  ck_assert(1 == getCharHolderCount(&ch));
  ck_assert(15 == getCharHolderData(&ch)[0]);
  pushCharHolder(&ch, 11);
  ck_assert(15 == getCharHolderData(&ch)[0]);
  ck_assert(2 == getCharHolderCount(&ch));
  ck_assert(11 == getCharHolderData(&ch)[1]);

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
