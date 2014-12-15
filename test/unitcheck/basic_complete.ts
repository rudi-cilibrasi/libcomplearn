/* A complete test example */

#include <stdio.h>
#include <complearn.h>

#test cldatum_test
	struct CLDatum clda, cldb, cldc;
  clNewDatum(&clda, "comp", 4);
  clNewDatum(&cldb, "learn", 6);
  cldc = clCatDatum(clda, cldb);
  clFreeDatum(&clda);
  clFreeDatum(&cldb);
  ck_assert(clSizeDatum(cldc) == 10);
  ck_assert(strcmp((char *) clBytesDatum(cldc), "complearn") == 0);
  clFreeDatum(&cldc);
  ck_assert(clBytesDatum(cldc) == NULL);
  ck_assert(clSizeDatum(cldc) == 0);
